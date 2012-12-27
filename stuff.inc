    vector<Vector3> predefined;
    // Left plane
    predefined.push_back(Vector3(-1, 0, 0));
    predefined.push_back(Vector3(-1, 0.33, 0));
    predefined.push_back(Vector3(-1, 0.66, 0));
    predefined.push_back(Vector3(-1, 1, 0));
    predefined.push_back(Vector3(-1, 0, 0));
    predefined.push_back(Vector3(-1, 0, 0.25));
    predefined.push_back(Vector3(-1, 0, 0.5));
    predefined.push_back(Vector3(-1, 0, 0.75));
    predefined.push_back(Vector3(-1, 0, 1));
    // Right plane
    predefined.push_back(Vector3(1, 0, 0));
    predefined.push_back(Vector3(1, 0.33, 0));
    predefined.push_back(Vector3(1, 0.66, 0));
    predefined.push_back(Vector3(1, 1, 0));
    predefined.push_back(Vector3(1, 0, 0));
    predefined.push_back(Vector3(1, 0, 0.25));
    predefined.push_back(Vector3(1, 0, 0.5));
    predefined.push_back(Vector3(1, 0, 0.75));
    predefined.push_back(Vector3(1, 0, 1));
    // Top plane
    predefined.push_back(Vector3(0, 1, 0));
    predefined.push_back(Vector3(0.5, 1, 0));
    predefined.push_back(Vector3(1, 1, 0));
    predefined.push_back(Vector3(0, 1, 0));
    predefined.push_back(Vector3(0, 1, 0.25));
    predefined.push_back(Vector3(0, 1, 0.5));
    predefined.push_back(Vector3(0, 1, 0.75));
    predefined.push_back(Vector3(0, 1, 1));
    // Bottom plane
    predefined.push_back(Vector3(0, -1, 0));
    predefined.push_back(Vector3(0.5, -1, 0));
    predefined.push_back(Vector3(1, -1, 0));
    predefined.push_back(Vector3(0, -1, 0));
    predefined.push_back(Vector3(0, -1, 0.25));
    predefined.push_back(Vector3(0, -1, 0.5));
    predefined.push_back(Vector3(0, -1, 0.75));
    predefined.push_back(Vector3(0, -1, 1));
    //Front plane
    predefined.push_back(Vector3(0, 0, -1));
    predefined.push_back(Vector3(0.5, 0, -1));
    predefined.push_back(Vector3(1, 0, -1));
    predefined.push_back(Vector3(0, 0, -1));
    predefined.push_back(Vector3(0, 0.33, -1));
    predefined.push_back(Vector3(0, 0.66, -1));
    predefined.push_back(Vector3(0, 1, -1));
    //Back plane
    predefined.push_back(Vector3(0, 0, 1));
    predefined.push_back(Vector3(0.5, 0, 1));
    predefined.push_back(Vector3(1, 0, 1));
    predefined.push_back(Vector3(0, 0, 1));
    predefined.push_back(Vector3(0, 0.33, 1));
    predefined.push_back(Vector3(0, 0.66, 1));
    predefined.push_back(Vector3(0, 1, 1));


    for (size_t i = 0; i < predefined.size(); i++)
    {
        Vector3 projectionDir = predefined[i];
            double xPos, yPos;
            // select the plane to project on.
            uint32_t *plane;
            double xm = 1, ym = 1;
            if ((fabs(projectionDir.x) > fabs(projectionDir.y)) && (fabs(projectionDir.x) > fabs(projectionDir.z)))
            {
                plane = projectionDir.x < 0 ? leftPlane : rightPlane;
                if (plane == leftPlane)
                {
                    xm = -1;
                }
                xPos = xm * projectionDir.z / fabs(projectionDir.x) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.y / fabs(projectionDir.x) * halfImageSize + halfImageSize;
            }
            if ((fabs(projectionDir.y) > fabs(projectionDir.x)) && (fabs(projectionDir.y) > fabs(projectionDir.z)))
            {
                plane = projectionDir.y < 0 ? bottomPlane : topPlane;
                if (plane == bottomPlane)
                {
                    ym = -1;
                }
                xPos = xm * projectionDir.x / fabs(projectionDir.y) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.z / fabs(projectionDir.y) * halfImageSize + halfImageSize;
            }
            if ((fabs(projectionDir.z) > fabs(projectionDir.x)) && (fabs(projectionDir.z) > fabs(projectionDir.y)))
            {
                plane = projectionDir.z < 0 ? frontPlane : backPlane;
                if (plane == backPlane)
                {
                    xm = -1;
                }
                xPos = xm * projectionDir.x / fabs(projectionDir.z) * halfImageSize + halfImageSize;
                yPos = -ym * projectionDir.y / fabs(projectionDir.z) * halfImageSize + halfImageSize;
            }
            plane[(int)(yPos) * size + (int)(xPos)] += 1000;
    }
