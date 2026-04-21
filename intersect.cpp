#include <iostream>
using namespace std;

/*Given a line segment, determine whether it intersects a plane.*/

struct Vertex {
    float x, y, z;
};

struct Plane {
    float a, b, c, d;
};

typedef pair<Vertex, Vertex> Segment;

bool intersects(const Plane& p, const Segment& s) {
    // her iki noktayı düzlem denklemine koy
    // Ax + By + Cz + D
    auto eval = [&](const Vertex& v) {
        return p.a*v.x + p.b*v.y + p.c*v.z + p.d;
    };

    float d1 = eval(s.first);   // birinci nokta
    float d2 = eval(s.second);  // ikinci nokta

    // farklı işaretse farklı tarafta → kesişiyor
    // biri sıfırsa düzlem üzerinde → kesişiyor
    return d1 * d2 <= 0.0f;
}

int main() {
    Plane p = {0, 0, 1, 0};  // z=0 düzlemi

    // z=-1 ve z=1 → farklı taraf → kesişmeli
    Segment s1 = {{0, 0, -1}, {0, 0, 1}};

    // z=1 ve z=2 → aynı taraf → kesişmemeli
    Segment s2 = {{0, 0, 1}, {0, 0, 2}};

    // z=0 → düzlem üzerinde → kesişmeli
    Segment s3 = {{0, 0, 0}, {0, 0, 1}};

    cout << "s1 kesiştiriyor mu? " << intersects(p, s1) << endl; // 1
    cout << "s2 kesiştiriyor mu? " << intersects(p, s2) << endl; // 0
    cout << "s3 kesiştiriyor mu? " << intersects(p, s3) << endl; // 1

    return 0;
}