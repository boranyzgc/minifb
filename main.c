// #include <stdio.h>
// #include <stdlib.h>     // malloc, free   
// #include <stdint.h>     // uint32_t, uint8_t 
// #include <MiniFB.h>     // MiniFB library for window management and graphics

// int main() {
//     // "my display" adlı, 800x600 boyutlarında ve yeniden boyutlandırılabilir bir pencere oluştur
//     struct mfb_window *window = mfb_open_ex("my display", 800, 600, WF_RESIZABLE);
//     // Pencere oluşturulamazsa programı sonlandır
//     if (window == NULL)
//         return 0;
//     // Ekran
//     uint32_t *buffer = malloc(800 * 600 * sizeof(uint32_t));

//     // RGB değerleri (0-255 arası)
//     uint8_t r = 120;
//     uint8_t g = 30;
//     uint8_t b = 200;

//     mfb_update_state state;
//     do {

//         // Tüm ekranı tek renk doldur
//         for (int i = 0; i < 800 * 600; i++) {
//             buffer[i] = MFB_ARGB(255, r, g, b);
//         }

//         state = mfb_update_ex(window, buffer, 800, 600);

//         if (state != STATE_OK)
//             break;

//     } while(mfb_wait_sync(window));

//     free(buffer);
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <MiniFB.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    int x;
    int y;
    int size;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Square;

void clearBuffer(uint32_t* buffer) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        buffer[i] = MFB_ARGB(255, 0, 0, 0);
    }
}

void drawCircle(uint32_t* buffer, int cx, int cy, int radius, uint8_t r, uint8_t g, uint8_t b) {
    for (int y = cy - radius; y <= cy + radius; y++) {
        for (int x = cx - radius; x <= cx + radius; x++) {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                float mesafe = sqrt((x-cx)*(x-cx) + (y-cy)*(y-cy));
                if (mesafe <= radius) {
                    buffer[y * WIDTH + x] = MFB_ARGB(255, r, g, b);
                }
            }
        }
    }
}

void drawSquare(uint32_t* buffer, Square square) {
    for (int y = square.y; y < square.y + square.size; y++) {
        for (int x = square.x; x < square.x + square.size; x++) {

            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                buffer[y * WIDTH + x] = MFB_ARGB(255, square.r, square.g, square.b);
            }

        }
    }
}

void moveSquare(Square* square, int speed) {
    square->x += speed; // Kareyi sağa hareket ettir  
    
}

void checkBoundary(Square* square) {
    if (square->x  > WIDTH) {
        square->x = -square->size; // Kare ekranın sağından çıktıysa, sol taraftan tekrar girmesini sağla
    }
}

void Movement(Square* square, int speed) {

    moveSquare(square, speed);

    checkBoundary(square);

}

void Preparations(uint32_t* buffer, Square square) {

    clearBuffer(buffer);

    drawSquare(buffer, square);

}

int main() {

    struct mfb_window* window = mfb_open_ex("Lab 2 - Square", WIDTH, HEIGHT, WF_RESIZABLE);
    if (window == NULL)
        return 0;

    uint32_t* buffer = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    if (buffer == NULL)
        return 0;

    Square square;

    square.size = 100;
    // Square'ı ekranın ortasına yerleştir. WIDTH/2 - square.size/2 → ekranın ortası eksi karenin yarı genişliği.
    square.x = WIDTH / 2 - square.size / 2;
    square.y = HEIGHT / 2 - square.size / 2;

     square.r = 255;
    square.g = 255;
    square.b = 0;


    //initial speed please change ! 
    int speed = 2; 

    mfb_update_state state;

    //do not change anytging inside main.
    do {

       Preparations(buffer, square);

        
        Movement(&square, speed);

      state = mfb_update_ex(window, buffer, WIDTH, HEIGHT);

      if (state != STATE_OK)
            break;

  } while (mfb_wait_sync(window));

   free(buffer);

    return 0;
}




