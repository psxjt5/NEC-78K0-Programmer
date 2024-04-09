#pragma once

#include "ConsoleLog.h"

#include <Arduino.h>

// Programmer Pins
# pragma region PROG_PINS
extern int     PROG_SCK;       // Connects to: TX
extern int     PROG_RX;        // Connects to: SO10
extern int     PROG_TX;        // Connects to: RX
extern int     PROG_RESET;     // Connects to: RESET
extern int     PROG_EN;        // Connects to: VPP
extern int     PROG_VDD;       // Connects to: VDD
# pragma endregion PROG_PINS

// Timings
enum PROG_DELAY {
    PROG_DELAY_PROGMODE     =       30,         // Delay between pulsing the VPP line to select the programming mode. Measure in Microseconds.
    PROG_DELAY_POWERON      =       2,          // Delay between powering on Microcontroller pins to put the chip into Programming Mode.
    PROG_DELAY_CHIPINIT     =       100,        // Delay between selecting the communications mode, and performing Synchronisation Detection Processing.
    PROG_DELAY_SCKFREQ      =       10,         // Frequency of the Software (Programmers) Clock.
    PROG_DELAY_COMACK       =       900,        // Delay between sending a command and attempting to read the response from the Microcontroller.
    PROG_DELAY_ACKCOM       =       170         // Delay between receiving a response from the Microcontroller and attempting to send another command.
};

// Programmer Communication Modes
enum PROG_MODE {
    PROG_MODE_3IO_C0        = 0,        // 3-Wire Serial I/O (Channel 0)
    PROG_MODE_3IO_C1        = 1,        // 3-Wire Serial I/O (Channel 1)
    PROG_MODE_3IO_C2        = 2,        // 3-Wire Serial I/O (Channel 2)
    PROG_MODE_3IO_C3_HS     = 3,        // 3-Wire Serial I/O With Handshaking (Channel 3)
    PROG_MODE_IIC_C0        = 4,        // IIC Communications (Channel 0)
    PROG_MODE_IIC_C1        = 5,        // IIC Communications (Channel 1)
    PROG_MODE_IIC_C2        = 6,        // IIC Communications (Channel 2)
    PROG_MODE_IIC_C3        = 7,        // IIC Communications (Channel 3)
    PROG_MODE_UART_C0       = 8,        // UART Communications (Channel 0)
    PROG_MODE_UART_C1       = 9,        // UART Communications (Channel 1)
    PROG_MODE_UART_C2       = 10,       // UART Communications (Channel 2)
    PROG_MODE_UART_C3       = 11,       // UART Communications (Channel 3)
    PROG_MODE_P_3IO_PA      = 12,       // Pseudo 3-Wire Serial I/O (Port A)
    PROG_MODE_P_3IO_PB      = 13,       // Pseudo 3-Wire Serial I/O (Port B)
    PROG_MODE_P_3IO_PC_HS   = 14        // Pseudo 3-Wire Serial I/O (Port C)
};

// Programmer Commands
enum PROG_CMD {
    PROG_CMD_RESET          = 0x00,     // Initialises the Flash Mode and Confirms Synchronisation.
    PROG_CMD_OSC_FREQ       = 0x90,     // Notifies the Microcontroller of its Operating Clock.
    PROG_CMD_ERASE_TIME     = 0x95,     // Sets the Microcontroller's Erase Time.
    PROG_CMD_BAUD_RATE      = 0x9A,     // Sets the Baud Rate (UART Mode only).
    PROG_CMD_PRE_WRITE      = 0x48,     // Sets the program area to 0x00 to prepare for erasure.
    PROG_CMD_ERASE          = 0x20,     // Erases the Microcontrollers Flash.
    PROG_CMD_HS_WRITE       = 0x40,     // Writes data to the Flash Memory.
    PROG_CMD_CONT_WRITE     = 0x44,     // Writes data to the next location after a HS_WRITE command.
    PROG_CMD_INT_VERIFY     = 0x18,     // Checks the depth of the write level after a write operation.
    PROG_CMD_VERIFY         = 0x11,     // Compares the contents of the Flash memory with a supplied image.
    PROG_CMD_BLANK_CHK      = 0x30,     // Checks if the Microcontroller's Flash has been erased.
    PROG_CMD_SIL_SIG        = 0xC0,     // Gets the Microcontroller's Device Information.
    PROG_CMD_STATUS_CHK     = 0x70      // Gets the Microcontroller's Internal Command Execution Status.
};

// Microcontroller Return Commands
enum PROG_CMD_RETURN {
    PROG_CMD_RETURN_ACK     = 0x3C,     // Acknowledgement.
    PROG_CMD_RETURN_NACK    = 0xFF      // Non-Acknowledgement.
};

// Programming Routines
void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD);
void PowerOnChip();
void SelectCommunicationMethod(PROG_MODE ProgrammingMode);
bool SynchronisationDetectionProcessing();
void OscillationFrequencySetting();
void PowerDownChip();

// Utility Subroutines
void Delay(PROG_DELAY Delay, bool Microseconds = false);
void ClockPulse();
void SendCommand(PROG_CMD Command);
bool ReceiveCommand(PROG_CMD_RETURN ReturnCode);