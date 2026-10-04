#ifndef CELL_H
#define CELL_H

#include "raylib.h"

class Cell {

    public:
        Cell(float x, float y, float z);

        float x;
        float y;
        float z;

        Mesh mesh;

    private:

        void calculateVertices();

        void generateMesh();

};
    
#endif