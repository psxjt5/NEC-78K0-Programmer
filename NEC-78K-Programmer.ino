/*
    Arduino-Based NEC 78K Programmer
    06/04/2024
    James.Todd@nottingham.ac.uk
*/

#include "NEC-78K-Programmer.h"

// Pin Definitons
#define     PROG_SCK        2       // Connects to: TX
#define     PROG_RX         3       // Connects to: SO10
#define     PROG_TX         4       // Connects to: RX
#define     PROG_RESET      5       // Connects to: RESET
#define     PROG_EN         6       // Connects to: VPP
#define     PROG_VDD        7       // Connects to: VDD

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    InitialiseProgrammer(PROG_SCK, PROG_RX, PROG_TX, PROG_RESET, PROG_EN, PROG_VDD);
    PowerOnChip();
}

void loop() {
}