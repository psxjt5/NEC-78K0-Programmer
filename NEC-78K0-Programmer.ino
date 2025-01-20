/*
    Arduino-Based NEC 78K Programmer
    06/04/2024
    James.Todd@nottingham.ac.uk
*/

#include "NEC78K0-Programmer.h"
#include "ConsoleLog.h"
#include "SDStorage.h"

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

    // Initialise SD
    // SDInitialise(10);

    // Output SD Information
    // SDInformation(10);

    // Define Pins.
    InitialiseProgrammer(PIN_SCK, PIN_RX, PIN_TX, PIN_RESET, PIN_EN, PIN_VDD);

    OutputToConsole(F("Ready to begin..."));
}

void loop() {

    while (Serial.available() > 0) {
        // Power on and select Comms Mode.
        // PowerOnChip();
        // SelectCommunicationMethod(PROG_MODE_3IO_C0);

        // // Synchronisation Detection Processing.
        // if (!SynchronisationDetectionProcessing()) {
        //     PowerDownChip();
        //     return;
        // }
        
        // // Set the Oscillation Frequency.
        // if (!OscillationFrequencySetting(1, 0, 0, 5)) {
        //     PowerDownChip();
        //     return;
        // }

        // Find the Blank Areas
        // FindBlankAreas();

        // Request the Silicon Signature Data
        // if (!GetSiliconSignatureData()) {
        //     //PowerDownChip();
        //     //return;
        // }

        // Output the Silicon Signature Data
        // PrintSiliconSignature();

        // Write to a Memory Location
        // if (!Write(0, 0, 0, 0xFF)) {
        //     PowerDownChip();
        //     return;
        // }

        // Set the Flash Erase Time Frequency.
        // if (!FlashEraseTimeSetting(2, 0, 0, 1)) {
        //     PowerDownChip();
        //     return;
        // }

        // // Request Status
        // if (!GetCurrentStatus()) {
        //     PowerDownChip();
        //     return;
        // }

        // // Output the Current Status
        // PrintCurrentStatus();

        // Power Down the Chip Safely.
        // PowerDownChip();
    }
}