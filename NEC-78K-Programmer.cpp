#include "NEC-78K-Programmer.h"

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD) {
    PROG_SCK = PIN_SCK;
    PROG_RX = PIN_RX;
    PROG_TX = PIN_TX;
    PROG_RESET = PIN_RESET;
    PROG_EN = PIN_VPP;
    PROG_VDD = PIN_VDD;
}

void PowerOnChip() {
    
}