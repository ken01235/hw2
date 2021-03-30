// EE240500 Embedded System Homework2
// 108061207 陳伯丞
#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bottom1(D6);
DigitalIn bottom2(D7);
DigitalIn bottom3(D8);
AnalogOut aout(PA_5);

uLCD_4DGL uLCD(D1, D0, D2);

void print_the_space(void);
void print_the_options(int);

int main() {
    int bt1 = 0;
    int bt2 = 0;
    int num = 0;
    int fq = 0;

    print_the_space();
    print_the_options(0);
    while(1){
        if (!bt1 && bottom1) {
            num = (num + 9) % 10;
            print_the_space();
            print_the_options(num);
            bt1 = bottom1;
        } else if (bt1 && !bottom1) {
            bt1 = bottom1;
        }
        if (!bt2 && bottom2) {
            num = (num + 1) % 10;
            print_the_space();
            print_the_options(num);
            bt2 = bottom2;
        } else if (bt2 && !bottom2) {
            bt2 = bottom2;
        }
        if (bottom3) break;
        ThisThread::sleep_for(100ms);
    }
    uLCD.cls();
    fq = (num + 1) * 100;
    // S = 5
    uint16_t output = 0;
    while (1) {
        for (int i = 0; i < 300; i++) {
            output = (uint16_t)(65535 * 3 / 3.3 * i / 300);
            aout.write_u16(output);
            printf("%d ", output);
        }
        for (int i = 0; i < 300; i++) {
            output = (uint16_t)(65535 * 3 / 3.3 - 65535 * 3 / 3.3 * i / 300);
            aout.write_u16(output);
            printf("%d ", output);
        }
    }
}

void print_the_space(void) {
    uLCD.cls();
    uLCD.background_color(BLACK);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(3);
    uLCD.text_height(3);
    uLCD.printf("\n\n");
}

void print_the_options(int num) {
    uLCD.printf("%2d00Hz", num + 1);
}

