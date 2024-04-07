#include "ConsoleLog.h"

bool Enabled = false;

void InitialiseConsole(int BaudRate) {
    Serial.begin(BaudRate);
    Enabled = true;
}

void OutputToConsole(String Text) {
    if (Enabled) {
        Serial.println(Text);
    }
}