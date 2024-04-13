#include <SPI.h>
#include <SD.h>

#include "ConsoleLog.h"

extern File currentFile;
extern Sd2Card card;
extern SdVolume volume;
extern SdFile root;

bool InitialiseSD(int PIN_CS);
void SDInformation(int PIN_CS);
bool OpenFile(String Path);