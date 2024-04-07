#include <Arduino.h>

extern bool Enabled = false;

void InitialiseConsole(int BaudRate = 9600);
void OutputToConsole(String Text);