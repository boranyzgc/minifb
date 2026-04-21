#include <iostream>
#include <cmath>
using namespace std;

/*Write a program to yield the parametrised form of the plane. Your program
 should take the coefficients A, B, C, and D from the command line.*/

int main(int argc, char* argv[]) {

    // komut satırından A,B,C,D al
    // çalıştırma: program.exe 1 2 3 4
    float A = stof(argv[1]);
    float B = stof(argv[2]);
    float C = stof(argv[3]);
    float D = stof(argv[4]);

    // düzlem üzerinde bir nokta bul
    // x=0, y=0 koy → Cz = -D → z = -D/C
    // C=0 olabilir, kontrol et
    float x0=0, y0=0, z0=0;
    if (fabs(C) > 1e-6)         // C sıfır değil
        z0 = -D/C;
    else if (fabs(B) > 1e-6)    // C sıfır, B sıfır değil
        y0 = -D/B;
    else                         // C ve B sıfır, A sıfır değil
        x0 = -D/A;

    // normal vektör: N = (A, B, C)
    float nx=A, ny=B, nz=C;

    // birinci yön vektörü: N'e dik
    // N × (1,0,0) = (0, nz, -ny)
    // ama N=(1,0,0) ise sıfır çıkar, o zaman N × (0,1,0) kullan
    float v1x, v1y, v1z;
    if (fabs(nx) < 0.9f) {
        v1x = 0;
        v1y = nz;
        v1z = -ny;
    } else {
        v1x = -nz;
        v1y = 0;
        v1z = nx;
    }

    // ikinci yön vektörü: N × V1
    // bu hem N'e hem V1'e dik → düzlem üzerinde
    float v2x = ny*v1z - nz*v1y;
    float v2y = nz*v1x - nx*v1z;
    float v2z = nx*v1y - ny*v1x;

    // sonucu yazdır
    cout << "P0 = (" << x0 << ", " << y0 << ", " << z0 << ")" << endl;
    cout << "V1 = (" << v1x << ", " << v1y << ", " << v1z << ")" << endl;
    cout << "V2 = (" << v2x << ", " << v2y << ", " << v2z << ")" << endl;
    cout << "Parametrik form: P = P0 + s*V1 + t*V2" << endl;

    return 0;
}