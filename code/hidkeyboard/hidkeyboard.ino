#include "Keyboard.h"



int i;
int v;
int test = A0;

void setup() {
        i = 0;
        Serial.begin(9600);
}

const size_t n = 10;
const char symbs[n] = "[]{}()'+-*=";

void greet(){
        Keyboard.print("bonjour; je suis un CLAVIER et je tape vite !!!");
        delay(3000);
}

void loop() {
        //if (Serial.available() > 0) {
        //        char x = Serial.read();
        //        if (x=='@') for (int i=0; i<30; i++)Keyboard.print('i');
        //}
        v = analogRead(test);
        if (v > 1000) {
                greet();
        }
}
