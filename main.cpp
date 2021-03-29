#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bottom1(D6); 
DigitalIn bottom2(D7); 
DigitalIn bottom3(D8); 

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

int main() {
    uLCD.cls();
    printf("\n\n\n\n  ");
    uLCD.text_width(3);
    uLCD.text_height(3);
    uLCD.text_underline(true);
    uLCD.printf("A");
    uLCD.text_underline(false);
    uLCD.printf(" B C\n");
    int a;
    while(1){
        a = bottom1;
        printf("%d ", a);
        a = bottom2;
        printf("%d ", a);
        a = bottom3;
        printf("%d\n", a);
        ThisThread::sleep_for(100ms);
    }
}
