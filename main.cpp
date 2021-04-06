// EE240500 Embedded System Homework2
// 108061207 陳伯丞
#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bottom1(D6);
DigitalIn bottom2(D7);
DigitalIn bottom3(D8);
AnalogOut aout(PA_5);
AnalogIn ain(A0);

uLCD_4DGL uLCD(D1, D0, D2);

int main()
{
    int bt1 = 0;
    int bt2 = 0;
    int bt3 = 0;
    int num = 71;
    int fq = num + 1;
    int i = 0, j = 501;
    float data[500];

    uLCD.background_color(BLACK);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(3);
    uLCD.text_height(3);
    uLCD.locate(0, 2);
    uLCD.printf("%3dHz", num + 1);
    while(1){
        if (!bt1 && bottom1) {
            num = (num + 126) % 144;
            uLCD.locate(0, 2);
            uLCD.printf("%3dHz", num + 1);
            bt1 = bottom1;
        } else if (bt1 && !bottom1) {
            bt1 = bottom1;
        }

        if (!bt2 && bottom2) {
            num = (num + 18) % 144;
            uLCD.locate(0, 2);
            uLCD.printf("%3dHz", num + 1);
            bt2 = bottom2;
        } else if (bt2 && !bottom2) {
            bt2 = bottom2;
        }

        if (!bt3 && bottom3) {
            fq = num + 1;
            uLCD.locate(0, 2);
            uLCD.color(RED);
            uLCD.printf("%3dHz", num + 1);
            uLCD.color(GREEN);
            j = 0;
            bt3 = bottom3;
        } else if (bt3 && !bottom3) {
            bt3 = bottom3;
        }

        int T = 1000 * 2 / fq;
        int output = 0;
        if (i < T) {
            i++;
        } else {
            i = 0;
        }
        if (i < (T / 2)) {
            output = 65535 * 3 / 3.3 * i / T * 2;
            write_u16(output);
        } else if (i >= (T / 2)) {
            output = 65565 * 3 / 3.3 - 65535 * 3 / 3.3 * i / T * 2;
            write_u16(output);
        }

        if (j < 500) {
            data[j] = ain.read();
            j++;
        } else if (j == 500) {
            for (int k = 0; k < 500; k++) {
                printf("%f\n", data[k]);
            }
            j++;
        }

        wait_us(500);
    }
}

// int main() {
//     int bt1 = 0;
//     int bt2 = 0;
//     int num = 71;
// 
//     uLCD.background_color(BLACK);
//     uLCD.textbackground_color(BLACK);
//     uLCD.text_width(3);
//     uLCD.text_height(3);
//     uLCD.locate(0, 2);
//     uLCD.printf("%3dHz", num + 1);
//     while(1){
//         if (!bt1 && bottom1) {
//             num = (num + 126) % 144;
//             uLCD.locate(0, 2);
//             uLCD.printf("%3dHz", num + 1);
//             bt1 = bottom1;
//         } else if (bt1 && !bottom1) {
//             bt1 = bottom1;
//         }
//         if (!bt2 && bottom2) {
//             num = (num + 18) % 144;
//             uLCD.locate(0, 2);
//             uLCD.printf("%3dHz", num + 1);
//             bt2 = bottom2;
//         } else if (bt2 && !bottom2) {
//             bt2 = bottom2;
//         }
//         if (bottom3) break;
//         ThisThread::sleep_for(100ms);
//     }
//     uLCD.locate(0, 2);
//     uLCD.textbackground_color(WHITE);
//     uLCD.printf("%3dHz", num + 1);
//     float input_serial[500] = {0};
//     fq = (num + 1);
//     thread.start(generate_triangle);
//     ThisThread::sleep_for(500ms);
//     for (int i = 0; i < 500; i++) {
//         input_serial[i] = ain;
//         wait_us(500);
//     }
//     for (int i = 0; i < 500; i++) {
//         printf("%f\n", input_serial[i]);
//         ThisThread::sleep_for(100ms);
//     }
// }
// 
// void generate_triangle(void) {
//     // S = 5
//     uint16_t output = 0;
//     int T = 52001 / fq / 20;
//     while (1) {
//         for (int i = 0; i < T; i++) {
//             output = (uint16_t)(65535 * 3 / 3.3 * i / T);
//             aout.write_u16(output);
//         }
//         for (int i = 0; i < T; i++) {
//             output = (uint16_t)(65535 * 3 / 3.3 - 65535 * 3 / 3.3 * i / T);
//             aout.write_u16(output);
//         }
//     }
// }
// 
