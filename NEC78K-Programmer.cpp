#include "NEC78K-Programmer.h"

int     PROG_SCK;       // Connects to: TX
int     PROG_RX;        // Connects to: SO10
int     PROG_TX;        // Connects to: RX
int     PROG_RESET;     // Connects to: RESET
int     PROG_EN;        // Connects to: VPP
int     PROG_VDD;       // Connects to: VDD

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD) {
    
    OutputToConsole("Initialising Programmer.");

    // Assign the Pins.
    PROG_SCK = PIN_SCK;
    PROG_RX = PIN_RX;
    PROG_TX = PIN_TX;
    PROG_RESET = PIN_RESET;
    PROG_EN = PIN_VPP;
    PROG_VDD = PIN_VDD;

    // Set the Pin Modes.
    pinMode(PROG_EN, OUTPUT);
    pinMode(PROG_VDD, OUTPUT);
    pinMode(PROG_RESET, OUTPUT);

}

void PowerOnChip() {
    
    OutputToConsole("Powering On Chip in Programming Mode.");

    // Connect the RESET pin to ground.
    OutputToConsoleDebug("RESET = LOW");
    digitalWrite(PROG_RESET, LOW);
    delay(2);

    // Apply power to the VDD Pin.
    OutputToConsoleDebug("VDD = HIGH");
    digitalWrite(PROG_VDD, HIGH);
    delay(2);

    // Apply 10V to the VPP (Write Enable) Pin.
    OutputToConsoleDebug("VPP (ENABLE) = HIGH");
    digitalWrite(PROG_EN, HIGH);
    delay(2);

    // Connect RESET to VDD to clear the reset.
    OutputToConsoleDebug("RESET = HIGH");
    digitalWrite(PROG_RESET, HIGH);
    delay(2);

}

void SelectCommunicationMethod(PROG_MODE ProgrammingMode) {

    OutputToConsoleDebug("Selecting Communication Method: " + String(ProgrammingMode) + ".");

    for (int i = 0; i <= ProgrammingMode; i++)
    {
        OutputToConsoleDebug("VPP (ENABLE) = LOW");
        digitalWrite(PROG_EN, LOW);
        delayMicroseconds(30);
        OutputToConsoleDebug("VPP (ENABLE) = HIGH");
        digitalWrite(PROG_EN, HIGH);
        delayMicroseconds(30);
    }    
}