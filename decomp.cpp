#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* A possibly rotated rectangle vertices given in a mixed (random) order.
 Write a routine to decompose it into two complementary triangle pairs.*/

struct Vertex {
    float x, y, z;
};

pair<vector<Vertex>, vector<Vertex>> decomp(const vector<Vertex>& vertices) {
    Vertex A = vertices[0], B = vertices[1],
           C = vertices[2], D = vertices[3];

    // iki nokta arasındaki mesafenin karesini hesapla
    auto dist = [](Vertex p1, Vertex p2) {
        float dx = p1.x-p2.x, dy = p1.y-p2.y, dz = p1.z-p2.z;
        return dx*dx + dy*dy + dz*dz;
    };

    // A'dan en uzak nokta köşegen ortağı
    float dAB = dist(A,B), dAC = dist(A,C), dAD = dist(A,D);

    Vertex diag1, diag2, other1, other2;
    if (dAB > dAC && dAB > dAD) {
        diag1=A; diag2=B; other1=C; other2=D;
    } else if (dAC > dAB && dAC > dAD) {
        diag1=A; diag2=C; other1=B; other2=D;
    } else {
        diag1=A; diag2=D; other1=B; other2=C;
    }

    vector<Vertex> tri1 = {diag1, diag2, other1};
    vector<Vertex> tri2 = {diag1, diag2, other2};

    return {tri1, tri2};
}

int main() {
    // Dikdörtgen köşeleri karışık sırada
    vector<Vertex> rect = {
        {0, 0, 0},  // A
        {2, 0, 0},  // B
        {2, 1, 0},  // C
        {0, 1, 0}   // D
    };

    auto [tri1, tri2] = decomp(rect);

    cout << "Üçgen 1:" << endl;
    for (auto& v : tri1)
        cout << "  (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;

    cout << "Üçgen 2:" << endl;
    for (auto& v : tri2)
        cout << "  (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;

    return 0;
}