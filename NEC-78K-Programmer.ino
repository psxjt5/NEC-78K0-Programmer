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

    OutputToConsole("Ready to begin...");
}

void loop() {

    while (Serial.available() > 0) {

        if (Serial.read() == 'A') {
            // Power on and select Comms Mode.
            PowerOnChip();
            SelectCommunicationMethod(PROG_MODE_3IO_C0);

            // Synchronisation Detection Processing.
            if (!SynchronisationDetectionProcessing()) {
                PowerDownChip();
                return;
            }
          
            // Set the Oscillation Frequency.
            if (!OscillationFrequencySetting(10, 0, 0, 4)) {
                PowerDownChip();
                return;
            }

            // Set the Flash Erase Time Frequency.
            // if (!FlashEraseTimeSetting(2, 0, 0, 1)) {
            //     PowerDownChip();
            //     return;
            // }

            

            // Power Down the Chip Safely.
            PowerDownChip();
        }
    }
}