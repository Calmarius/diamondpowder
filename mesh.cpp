/*
Copyright (c) 2012, Dávid Csirmaz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file mesh.cpp
 *
 * Some mesh functions go here.
 */

using namespace std;

void initMesh(Mesh &mesh)
{
    mesh.vertices.clear();
    mesh.faces.clear();
}

int loadMeshFromObjFile(Mesh &mesh, const char *filename)
{
    // Loads only faces and vertices, nothing else.
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

