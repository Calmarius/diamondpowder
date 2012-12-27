#ifndef MESH_H
#define MESH_H

struct Mesh
{
    /**
     * Vertices stored as 3D coordinates
     */
    std::vector<Vector3> vertices;
    /**
     * Faces stored as index lists of vertices of the face.
     */
    std::vector<std::vector<int> > faces;

};

/**
 * Clears all vector in the mesh.
 */
void initMesh(Mesh &mesh);

/**
 * Loads the mesh from a wavefront OBJ file.
 */
int loadMeshFromObjFile(Mesh &mesh, const char *filename);



#endif // MESH_H

