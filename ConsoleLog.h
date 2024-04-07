#include <Arduino.h>

extern bool Enabled = false;
extern bool DebugOutput = false;

void InitialiseConsole(int BaudRate = 9600, bool DebugOutput = false);
void OutputToConsole(String Text);