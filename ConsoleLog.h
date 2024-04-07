#include <Arduino.h>

extern bool Enabled;
extern bool Debug;

void InitialiseConsole(int BaudRate = 9600, bool DebugOutput = false);
void OutputToConsole(String Text);
void OutputToConsoleDebug(String Text);