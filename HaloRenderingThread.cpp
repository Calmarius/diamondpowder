DEFINE_EVENT_TYPE(wxEVT_HALO_RENDERING_THREAD_NOTIFY)

void HaloRenderingThread::sendNotifyString(const wxString &str, int terminate)
{
    wxCommandEvent evt(wxEVT_HALO_RENDERING_THREAD_NOTIFY, wxID_ANY);
    evt.SetString(str);
    evt.SetInt(terminate);
    setupStruct.notifee->AddPendingEvent(evt);
}

Matrix HaloRenderingThread::getOrientationMatrix(CrystalDescriptor::OrientationType orientation)
{
    Matrix m;
    switch (orientation)
    {
        case CrystalDescriptor::OT_RANDOM:
        {
            /* First rotate the crystal around the Z axis:*/
            Matrix zRot = createRotationMatrix(Vector3(0, 0, 1), randFloat(-3.14159265, 3.14159265));
            /* Then rotate the Z axis into an uniformly distributed position*/
            const Vector3 newAxis = getRandomVector();
            Vector3 rotAxis = Vector3(0, 0, 1) % newAxis;
            Matrix axisRot = getIdentityMatrix();
            if (rotAxis * rotAxis != 0)
            {
                rotAxis /= ~rotAxis;
                double rotAngle = acos(Vector3(0, 0, 1) * newAxis);
                axisRot = createRotationMatrix(rotAxis, rotAngle);
            }

            return zRot % axisRot;
        }
        break;
        case CrystalDescriptor::OT_PARRY:
        {
            m = createRotationMatrix(Vector3(0, 1, 0), randFloat(0, 3.1415926536));
        }
        break;
        case CrystalDescriptor::OT_COLUMN:
        {
            Matrix n = createRotationMatrix(Vector3(0, 0, 1), randFloat(0, 3.1415926536));
            Matrix o = createRotationMatrix(Vector3(0, 1, 0), randFloat(0, 3.1415926536));
            m = n % o;
        }
        break;
        case CrystalDescriptor::OT_PLATE:
        {
            m = createRotationMatrix(Vector3(1, 0, 0), 3.14159265636 * 0.5) % createRotationMatrix(Vector3(0, 1, 0), randFloat(0, 3.1415926536));
        }
        break;
        case CrystalDescriptor::OT_LOWITZ:
        {
            m =
                createRotationMatrix(Vector3(1, 0, 0), 3.14159265636 * randFloat(-3.1415 * 0.5, 3.1415 * 0.5)) %
                createRotationMatrix(Vector3(0, 1, 0), randFloat(0, 3.1415926536));
        }
        break;
        default:
        {
            sendNotifyString(wxT("Invalid orientation type."), 1);
        }
    }
    return m;
}

void HaloRenderingThread::freeBuffer(uint32_t *ptr)
{
    delete[] ptr;
}

void HaloRenderingThread::freeMap(std::map<RayPathId, RayPathDescriptor> *ptr)
{
    delete ptr;
}


wxThread::ExitCode  HaloRenderingThread::Entry()
{
    wxCommandEvent evt(wxEVT_HALO_RENDERING_THREAD_NOTIFY, wxID_ANY);

    setupStruct.resultValid = false;
    setupStruct.imageBuffer = 0;
    setupStruct.rayPaths = new map<RayPathId, RayPathDescriptor>;

    if (setupStruct.crystals.size() == 0)
    {
        evt.SetString(wxT("No crystal population set up."));
        evt.SetInt(1);
        setupStruct.notifee->AddPendingEvent(evt);
        return 0;
    }

    // Cast rays on crystals and refracted rays will form a pixel.

    int crystalTypeIndex = 0;
    CrystalDescriptor *currentDescriptor = &setupStruct.crystals[0];
    const int N_CRYSTAL_TYPES = setupStruct.crystals.size();
    int crystalsRemaining = currentDescriptor->populationWeight;
    Mesh currentMesh;
    size_t percentStep = setupStruct.crystalCount / 100;
    if (percentStep < 1) percentStep = 1;
    Vector3 sunPos(0, 0, -100000);
    rotate2d(sunPos.y, sunPos.z, setupStruct.solarAltitude * 3.14159265636 / 180.0);
    // Two prependicular vector
    Vector3 prepX = sunPos % Vector3(0, 1, 0); // FIXME: Sun on the zenith
    Vector3 prepY = sunPos % prepX;
    prepX /= ~prepX;
    prepY /= ~prepY;
    setupStruct.deleteBuffer = freeBuffer;
    setupStruct.deleteMap = freeMap;
    size_t size = setupStruct.imageSize;
    setupStruct.imageBuffer = new uint32_t[size * size * 6];
    memset(setupStruct.imageBuffer, 0, size * size * 6 * sizeof(uint32_t));
    uint32_t *leftPlane = setupStruct.imageBuffer; // 0th plane
    uint32_t *rightPlane = setupStruct.imageBuffer + size * size; // 1st plane
    uint32_t *topPlane = setupStruct.imageBuffer + 2 * size * size; // 2nd plane
    uint32_t *bottomPlane = setupStruct.imageBuffer + 3 * size * size; // 3rd plane
    uint32_t *backPlane = setupStruct.imageBuffer + 4 * size * size; // 4th plane
    uint32_t *frontPlane = setupStruct.imageBuffer + 5 * size * size; // 5th plane
    double halfImageSize = size * 0.5;
    int maxRays = (setupStruct.maxRayCastInfoSize * 1000000) / (sizeof(RayPathDescriptor) + sizeof(RayPathId));
    if (maxRays == 0) maxRays = 1;
    int recordRayModulus = setupStruct.crystalCount / maxRays;
    if (!recordRayModulus) recordRayModulus = 1;

    struct RefractionColor
    {
        int rgb;
        double refractionIndex;
    };

    RefractionColor colors[] =
    {
        { 0x0000FF, 1.3072 },
        { 0x0080FF, 1.3094 },
        { 0x00FFFF, 1.31 },
        { 0x00FF80, 1.3107 },
        { 0x00FF00, 1.3114 },
        { 0x80FF00, 1.3125 },
        { 0xFFFF00, 1.3136 },
        { 0xFF8000, 1.3147 },
        { 0xFF0000, 1.3158 },
        { 0xFF0040, 1.3172 },
        { 0xFF0080, 1.32 },
    };

    const int N_COLORS = sizeof(colors) / sizeof(colors[0]);

    for (size_t i = 0; i < setupStruct.crystalCount; i++)
    {
        if (setupStruct.cancelled)
        {
            delete[] setupStruct.imageBuffer;
            setupStruct.imageBuffer = 0;
            return 0;
        }
        if (!crystalsRemaining)
        {
            crystalTypeIndex++;
            if (crystalTypeIndex >= N_CRYSTAL_TYPES) crystalTypeIndex = 0;
            currentDescriptor = &setupStruct.crystals[crystalTypeIndex];
            crystalsRemaining = currentDescriptor->populationWeight;
        }
        // Get the raw mesh
        currentMesh = currentDescriptor->mesh;
        // Rotate it according to the orientation.
        Matrix orientationMatrix = getOrientationMatrix(currentDescriptor->orientation);
        // Apply wobbliness
        Vector3 wobbleRotationAxis(1, 0, 0);
        rotate2d(wobbleRotationAxis.x, wobbleRotationAxis.z, randFloat(0, 3.1415));
        double wobblinessLimit = currentDescriptor->wobbliness * 3.1415 / 180.0;
        Matrix wobbleMatrix = createRotationMatrix(
            wobbleRotationAxis,
            randFloatNormal(
                0,
                wobblinessLimit
            )
        );
        Matrix transformation = orientationMatrix % wobbleMatrix;
        transformMesh(currentMesh, transformation);

        // Crystal created, now cast a ray on it.
        Vector3 offset = prepX * randFloat(-1, 1) + prepY * randFloat(-1, 1);
        vector<RayPath> rayPaths;
        // Compute color here
        double colorCode = randFloat(0, N_COLORS - 1);
        RefractionColor prev = colors[(int)(floor(colorCode))];
        RefractionColor next = colors[(int)(ceil(colorCode))];
        double kColor = colorCode - floor(colorCode);
        RefractionColor currentColor;
        currentColor.rgb = prev.rgb;
        currentColor.refractionIndex = (1 - kColor) * prev.refractionIndex + kColor * next.refractionIndex;
        // Compute real poisition of the ray (Sun is a disk)
        Vector3 realSunPos = sunPos;
        Vector3 rayRotVector;
        double rayRotVectorLength;
        do
        {
            rayRotVector = realSunPos % getRandomVector();
            rayRotVectorLength = ~rayRotVector;
        }
        while (rayRotVectorLength == 0);
        rayRotVector /= rayRotVectorLength;
        realSunPos = transformVector(
            createRotationMatrix(
                rayRotVector,
                randFloat(
                    0,
                    setupStruct.solarDiskRadius * 3.1415926536 / 180.0
                )
            ),
            realSunPos
        );
        computeRayPathInGlassMesh(currentMesh, currentColor.refractionIndex, realSunPos + offset, -realSunPos, 0.01, rayPaths);
        for (size_t j = 0; j < rayPaths.size(); j++)
        {
            RayPath &current = rayPaths[j];
            size_t pathLength = current.size();

            Vector3 exitDir = current[pathLength - 1].first - current[pathLength - 2].first;
            Vector3 projectionDir = -exitDir;
            /*log_var(RAYCASTING_LOG, projectionDir);
            log_var(RAYCASTING_LOG, ~projectionDir);*/

            double xPos, yPos;
            // select the plane to project on.
            uint32_t *plane;
            double xm = 1, ym = 1;
            int planeId;
            if ((fabs(projectionDir.x) > fabs(projectionDir.y)) && (fabs(projectionDir.x) > fabs(projectionDir.z)))
            {
                if (projectionDir.x < 0)
                {
                    plane = leftPlane;
                    planeId = 0;
                    xm = -1;
                }
                else
                {
                    plane = rightPlane;
                    planeId = 1;
                }
                xPos = xm * projectionDir.z / fabs(projectionDir.x) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.y / fabs(projectionDir.x) * halfImageSize + halfImageSize;
            }
            if ((fabs(projectionDir.y) > fabs(projectionDir.x)) && (fabs(projectionDir.y) > fabs(projectionDir.z)))
            {
                if (projectionDir.y < 0)
                {
                    plane = bottomPlane;
                    planeId = 3;
                    ym = -1;
                }
                else
                {
                    plane = topPlane;
                    planeId = 2;
                }
                xPos = xm * projectionDir.x / fabs(projectionDir.y) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.z / fabs(projectionDir.y) * halfImageSize + halfImageSize;
            }
            if ((fabs(projectionDir.z) > fabs(projectionDir.x)) && (fabs(projectionDir.z) > fabs(projectionDir.y)))
            {
                if (projectionDir.z < 0)
                {
                    plane = frontPlane;
                    planeId = 5;
                }
                else
                {
                    plane = backPlane;
                    planeId = 4;
                    xm = -1;
                }
                xPos = xm * projectionDir.x / fabs(projectionDir.z) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.y / fabs(projectionDir.z) * halfImageSize + halfImageSize;
            }
            xPos = clampInInt(xPos, 0, size - 1);
            yPos = clampInInt(yPos, 0, size - 1);
            int prevPixel = plane[(int)(yPos) * size + (int)(xPos)];
            int nextPixel = 0;
            double intensity = current[pathLength - 2].second * 20;
            for (int j = 0; j < 3; j++)
            {
                int currentSaturation = (prevPixel >> (8 * j)) & 0xFF;
                int toAdd = (int)(((currentColor.rgb >> (8 * j)) & 0xFF) * intensity) >> 8;
                int nextSaturation;
                if (currentSaturation + toAdd > 255) nextSaturation = 255;
                else nextSaturation = currentSaturation + toAdd;
                nextPixel += (1 << (8 * j)) * nextSaturation * setupStruct.pixelIntensity;
            }
            plane[(int)(yPos) * size + (int)(xPos)] = nextPixel;
            // Record the ray if needed
            if (!(i % recordRayModulus))
            {
                RayPathId pixelId(planeId, (int)xPos, (int)yPos);
                RayPathDescriptor theDescriptor(
                    &currentDescriptor->mesh,
                    transformation,
                    realSunPos + offset,
                    -realSunPos,
                    intensity
                );
                map<RayPathId, RayPathDescriptor>::iterator it = setupStruct.rayPaths->find(pixelId);
                if (it == setupStruct.rayPaths->end())
                {
                    // If not found, insert it as new
                    setupStruct.rayPaths->insert(
                        make_pair(
                            pixelId,
                            theDescriptor
                        )
                    );
                }
                else if (it->second.intensity < intensity)
                {
                    // If found, update it if the current ray is more intense
                    it->second = theDescriptor;
                }
            }
        }

        if (i % percentStep == 0)
        {
            sendNotifyString(wxString::Format(wxT("Casting rays: %d%%"), i / percentStep));
        }

        crystalsRemaining--;
    }


    evt.SetString(wxT("Completed."));
    evt.SetInt(1);
    setupStruct.resultValid = true;
    setupStruct.notifee->AddPendingEvent(evt);
    return 0;
}
