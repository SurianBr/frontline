#include "Cell.h"

#include "raylib.h"


Cell::Cell(float x, float y, float z) {
    //       +Y (Up)
    //          |
    //          |   -Z (Forward / Depth into screen)
    //          |  /
    //          | /
    //          |/____________ +X (Right / Horizontal)
    //         /
    //        /
    //       /
    //    +Z (Backward / Out of screen toward you)

    this->x = x;
    this->y = y;
    this->z = z;

    this->generateMesh();
}

void Cell::generateMesh() {
    // Generate a mesh array for 2 triangles (6 vertices) using the calculated vertices, normals, and texture coordinates
    this->mesh = { 0 };
    this->mesh.triangleCount = 2;
    this->mesh.vertexCount = this->mesh.triangleCount*3;
    this->mesh.vertices = (float *)MemAlloc(this->mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    this->mesh.texcoords = (float *)MemAlloc(this->mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    this->mesh.normals = (float *)MemAlloc(this->mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    // First triangle
    // Top-Left 
    this->mesh.vertices[0] = this->x;
    this->mesh.vertices[1] = this->y;
    this->mesh.vertices[2] = this->z;
    this->mesh.normals[0] = 0;
    this->mesh.normals[1] = 1.0f;
    this->mesh.normals[2] = 0;
    this->mesh.texcoords[0] = this->x;
    this->mesh.texcoords[1] = this->z;

    // Bottom-Left
    this->mesh.vertices[3] = this->x;
    this->mesh.vertices[4] = this->y;
    this->mesh.vertices[5] = this->z + 1;
    this->mesh.normals[3] = 0;
    this->mesh.normals[4] = 1.0f;
    this->mesh.normals[5] = 0;
    this->mesh.texcoords[2] = this->x;
    this->mesh.texcoords[3] = this->z + 1;

    // Bottom-Right
    this->mesh.vertices[6] = this->x + 1;
    this->mesh.vertices[7] = this->y;
    this->mesh.vertices[8] = this->z + 1;
    this->mesh.normals[6] = 0;
    this->mesh.normals[7] = 1.0f;
    this->mesh.normals[8] = 0;
    this->mesh.texcoords[4] = this->x + 1;
    this->mesh.texcoords[5] = this->z + 1;

    // Second triangle
    // Bottom-Right
    this->mesh.vertices[9] = this->x + 1;
    this->mesh.vertices[10] = this->y;
    this->mesh.vertices[11] = this->z + 1;
    this->mesh.normals[9] = 0;
    this->mesh.normals[10] = 1.0f;
    this->mesh.normals[11] = 0;
    this->mesh.texcoords[6] = this->x + 1;
    this->mesh.texcoords[7] = this->z + 1;

    // Top-Right
    this->mesh.vertices[12] = this->x + 1;
    this->mesh.vertices[13] = this->y;
    this->mesh.vertices[14] = this->z;
    this->mesh.normals[12] = 0;
    this->mesh.normals[13] = 1.0f;
    this->mesh.normals[14] = 0;
    this->mesh.texcoords[8] = this->x + 1;
    this->mesh.texcoords[9] = this->z;

    // Top-Left
    this->mesh.vertices[15] = this->x;
    this->mesh.vertices[16] = this->y;
    this->mesh.vertices[17] = this->z;
    this->mesh.normals[15] = 0;
    this->mesh.normals[16] = 1.0f;
    this->mesh.normals[17] = 0;
    this->mesh.texcoords[10] = this->x;
    this->mesh.texcoords[11] = this->z;

    UploadMesh(&this->mesh, false);

}