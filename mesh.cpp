using namespace std;

void initMesh(Mesh &mesh)
{
    mesh.vertices.clear();
    mesh.faces.clear();
}

int loadMeshFromObjFile(Mesh &mesh, const char *filename)
{
    FILE *f = fopen(filename, "rt");
    FILE *log = fopen("log.txt", "wt");
    const int MAX_LINE_LENGTH = 100;
    char line[MAX_LINE_LENGTH];

    if (!f) return -1;

    while (!feof(f))
    {
        if (!fgets(line, MAX_LINE_LENGTH, f)) break;
        if (line[0] == 'f')
        {
            char indextriplet[30];
            vector<int> faceindices;
            const char *lineptr = line + 1;
            int nConsumedChars;

            fprintf(log, "Face: ");
            // The current line is a face, so read face vertex indices
            while (sscanf(lineptr, "%29s%n", indextriplet, &nConsumedChars) >= 1)
            {
                int vertexIndex;

                sscanf(indextriplet, "%d", &vertexIndex);
                faceindices.push_back(vertexIndex - 1);
                fprintf(log, "%d ", vertexIndex);

                lineptr += nConsumedChars;
            }
            // Store it.
            fprintf(log, "\n");
            fflush(log);
            mesh.faces.push_back(faceindices);
        }
        else if (line[0] == 'v')
        {
            double x, y, z;
            // The current line is a vertex.
            sscanf(line + 2, "%lf%lf%lf", &x, &y, &z);
            mesh.vertices.push_back(Vector3(x, y, z));
            fprintf(log, "Vertex: %f %f %f\n", x, y, z);
            fflush(log);
        }
        // Other cases are ignored.

    }

    fclose(f);
    fclose(log);
    return 0;
}

