#pragma once

#include <Arduino.h>

int     PROG_SCK;       // Connects to: TX
int     PROG_RX;        // Connects to: SO10
int     PROG_TX;        // Connects to: RX
int     PROG_RESET;     // Connects to: RESET
int     PROG_EN;        // Connects to: VPP
int     PROG_VDD;       // Connects to: VDD

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD);
void PowerOnChip();