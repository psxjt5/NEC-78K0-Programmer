#include "NEC-78K-Programmer.h"

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD) {
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
    // Connect the RESET pin to ground.
    digitalWrite(PROG_RESET, LOW);
    delay(2);

    // Apply power to the VDD Pin.
    digitalWrite(PROG_VDD, HIGH);
    delay(2);

    // Apply 10V to the VPP (Write Enable) Pin.
    digitalWrite(PROG_EN, HIGH);
    delay(2);

    // Connect RESET to VDD to clear the reset.
    digitalWrite(PROG_RESET, HIGH);
    delay(2);
}

void SelectCommunicationMethod(PROG_MODE ProgrammingMode) {
    for (int i = 0; i <= ProgrammingMode; i++)
    {
        digitalWrite(PROG_EN, LOW);
        delayMicroseconds(30);
        digitalWrite(PROG_EN, HIGH);
        delayMicroseconds(30);
    }    
}