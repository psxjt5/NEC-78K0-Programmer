/*
    Arduino-Based NEC 78K Programmer
    06/04/2024
    James.Todd@nottingham.ac.uk
*/

#include "NEC78K-Programmer.h"
#include "ConsoleLog.h"

// Pin Definitons
#define     PIN_SCK        2       // Connects to: TX
#define     PIN_RX         3       // Connects to: SO10
#define     PIN_TX         4       // Connects to: RX
#define     PIN_RESET      5       // Connects to: RESET
#define     PIN_EN         6       // Connects to: VPP
#define     PIN_VDD        7       // Connects to: VDD

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    // Enable Console Output.
    InitialiseConsole(19200, true);

    // Define Pins.
    InitialiseProgrammer(PIN_SCK, PIN_RX, PIN_TX, PIN_RESET, PIN_EN, PIN_VDD);

    // Power on and select Comms Mode.
    PowerOnChip();
    SelectCommunicationMethod(PROG_MODE_3IO_C0);

    // Synchronisation Detection Processing
    if (SynchronisationDetectionProcessing()) {
        
    }
}

void loop() {
}