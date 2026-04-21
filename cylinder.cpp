#include <iostream>
#include <cmath>
using namespace std;

/*Write a function which determines whether a Vertex is inside a cylinder.
 Minimise the Cyclomatic Complexity.*/

struct Vertex {
    union {
        struct { float x; float y; float z; };
        float e[3];
    };
};

struct SCylinder {
    unsigned axis : 2;  // 0=x, 1=y, 2=z
    float h;            // yükseklik
    float r;            // yarıçap
    Vertex center;
};

bool is_inside(const SCylinder& cyl, const Vertex& vertex) {
    int a = cyl.axis;        // eksen koordinatı
    int b = (a + 1) % 3;    // birinci dik koordinat
    int c = (a + 2) % 3;    // ikinci dik koordinat

    // yükseklik kontrolü: eksen boyunca merkeze uzaklık h/2'den küçük mü?
    bool in_height = fabs(vertex.e[a] - cyl.center.e[a]) <= cyl.h / 2.0f;

    // daire kontrolü: dik iki koordinatta merkeze uzaklık r'den küçük mü?
    float db = vertex.e[b] - cyl.center.e[b];
    float dc = vertex.e[c] - cyl.center.e[c];
    bool in_circle = (db*db + dc*dc) <= (cyl.r * cyl.r);

    return in_height && in_circle;
}

int main() {
    SCylinder cyl;
    cyl.axis = 2;            // z eksenine paralel
    cyl.h = 4.0f;
    cyl.r = 2.0f;
    cyl.center = {0, 0, 0};

    Vertex v1 = {1, 1, 1};  // içeride
    Vertex v2 = {3, 0, 0};  // dışarıda (yarıçap dışı)
    Vertex v3 = {0, 0, 3};  // dışarıda (yükseklik dışı)

    cout << "v1: " << is_inside(cyl, v1) << endl; // 1
    cout << "v2: " << is_inside(cyl, v2) << endl; // 0
    cout << "v3: " << is_inside(cyl, v3) << endl; // 0

    return 0;
}