#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <math.h>
#include <iostream> 

using namespace std;
/*Write a C++ function vector<Vertex> gen_unit_cube() which generates 
all the vertex coordinates of a unit cube whose lower corner is origin 
and top corner is (1, 1, 1). Use a single loop and bitwise operators.*/

struct Vertex {
    float x;
    float y;
    float z;
};

vector<Vertex> gen_unit_cube() {
    vector<Vertex> vertices;
    for (int i = 0; i < 8; i++) {
        Vertex v;
        v.x = (i & 1) ? 1.0f : 0.0f;       // bit 0
        v.y = (i & 2) ? 1.0f : 0.0f;       // bit 1
        v.z = (i & 4) ? 1.0f : 0.0f;       // bit 2
        vertices.push_back(v);
    }
    return vertices;
}

int main() {
    vector<Vertex> cube = gen_unit_cube();
    for (size_t i = 0; i < cube.size(); i++) {
        cout << "Köşe " << i << ": ("
             << cube[i].x << ", "
             << cube[i].y << ", "
             << cube[i].z << ")" << endl;
    }
    return 0;
}