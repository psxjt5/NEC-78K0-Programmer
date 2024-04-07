#pragma once

#include <Arduino.h>

extern int     PROG_SCK;       // Connects to: TX
extern int     PROG_RX;        // Connects to: SO10
extern int     PROG_TX;        // Connects to: RX
extern int     PROG_RESET;     // Connects to: RESET
extern int     PROG_EN;        // Connects to: VPP
extern int     PROG_VDD;       // Connects to: VDD

enum PROG_MODE {
    PROG_MODE_3IO_C0 = 0,
    PROG_MODE_3IO_C1 = 1,
    PROG_MODE_3IO_C2 = 2,
    PROG_MODE_3IO_C3_HS = 3,
    PROG_MODE_IIC_C0 = 4,
    PROG_MODE_IIC_C1 = 5,
    PROG_MODE_IIC_C2 = 6,
    PROG_MODE_IIC_C3 = 7,
    PROG_MODE_UART_C0 = 8,
    PROG_MODE_UART_C1 = 9,
    PROG_MODE_UART_C2 = 10,
    PROG_MODE_UART_C3 = 11,
    PROG_MODE_P_3IO_PA = 12,
    PROG_MODE_P_3IO_PB = 13,
    PROG_MODE_P_3IO_PC_HS = 14
};

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD);
void PowerOnChip();
void SelectCommunicationMethod(PROG_MODE ProgrammingMode);