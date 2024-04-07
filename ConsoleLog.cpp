#include "ConsoleLog.h"

bool Enabled = false;
bool Debug = false;

void InitialiseConsole(int BaudRate, bool DebugOutput) {
    Serial.begin(BaudRate);
    Enabled = true;
    Debug = DebugOutput;
}

void OutputToConsole(String Text) {
    if (Enabled) {
        Serial.println(Text);
    }
}

void OutputToConsoleDebug(String Text) {
    if (Enabled && Debug) {
        Serial.println("DEBUG: " + Text);
    }
}