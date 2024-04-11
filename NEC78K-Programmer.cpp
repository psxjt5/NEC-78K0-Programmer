#include "NEC78K-Programmer.h"

int     PROG_PIN_SCK;       // Connects to: TX
int     PROG_PIN_RX;        // Connects to: SO10
int     PROG_PIN_TX;        // Connects to: RX
int     PROG_PIN_RESET;     // Connects to: RESET
int     PROG_PIN_EN;        // Connects to: VPP
int     PROG_PIN_VDD;       // Connects to: VDD

void InitialiseProgrammer(int PIN_SCK, int PIN_RX, int PIN_TX, int PIN_RESET, int PIN_VPP, int PIN_VDD) {
    
    OutputToConsole("Initialising Programmer.");

    // Assign the Pins.
    PROG_PIN_SCK = PIN_SCK;
    PROG_PIN_RX = PIN_RX;
    PROG_PIN_TX = PIN_TX;
    PROG_PIN_RESET = PIN_RESET;
    PROG_PIN_EN = PIN_VPP;
    PROG_PIN_VDD = PIN_VDD;

    // Set the Pin Modes.
    pinMode(PROG_PIN_EN, OUTPUT);
    pinMode(PROG_PIN_VDD, OUTPUT);
    pinMode(PROG_PIN_RESET, OUTPUT);
    pinMode(PROG_PIN_SCK, OUTPUT);
    pinMode(PROG_PIN_TX, OUTPUT);
    pinMode(PROG_PIN_RX, INPUT);

}

void PowerOnChip() {
    
    OutputToConsole("Powering On Chip in Programming Mode.");

    // Connect the RESET pin to ground.
    OutputToConsoleDebug("RESET = LOW");
    digitalWrite(PROG_PIN_RESET, LOW);
    Delay(PROG_DELAY_POWERON);

    // Apply power to the VDD Pin.
    OutputToConsoleDebug("VDD = HIGH");
    digitalWrite(PROG_PIN_VDD, HIGH);
    Delay(PROG_DELAY_POWERON);

    // Apply power to the SCK Pin.
    OutputToConsoleDebug("SCK = HIGH");
    digitalWrite(PROG_PIN_SCK, HIGH);

    // Apply 10V to the VPP (Write Enable) Pin.
    OutputToConsoleDebug("VPP (ENABLE) = HIGH");
    digitalWrite(PROG_PIN_EN, HIGH);
    Delay(PROG_DELAY_POWERON);

    // Connect RESET to VDD to clear the reset.
    OutputToConsoleDebug("RESET = HIGH");
    digitalWrite(PROG_PIN_RESET, HIGH);
    Delay(PROG_DELAY_POWERON);

}

void SelectCommunicationMethod(PROG_MODE ProgrammingMode) {

    OutputToConsoleDebug("Selecting Communication Method: " + String(ProgrammingMode) + ".");

    for (int i = 0; i < ProgrammingMode; i++)
    {
        OutputToConsoleDebug("VPP (ENABLE) = LOW");
        digitalWrite(PROG_PIN_EN, LOW);
        Delay(PROG_DELAY_PROGMODE, true);
        OutputToConsoleDebug("VPP (ENABLE) = HIGH");
        digitalWrite(PROG_PIN_EN, HIGH);
        Delay(PROG_DELAY_PROGMODE, true);
    }    
}

bool SynchronisationDetectionProcessing() {
    
    // Wait for the chip to Initialise.
    OutputToConsole("Waiting for Chip Initialisation");
    Delay(PROG_DELAY_CHIPINIT);

    // Send the Reset Command.
    for (int i = 0; i < 16; i++)
    {
        OutputToConsoleDebug("Sending Reset Command, Attempt: " + String(int(i + 1)));
        SendCommand(PROG_CMD_RESET);
        Delay(PROG_DELAY_COMACK);

        if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
            Delay(PROG_DELAY_ACKCOM);
            OutputToConsole("Received Acknowledgement Response from Microcontroller.");
            return true;
        }

        Delay(PROG_DELAY_ACKCOM);
        return false;
    }
    
    // An issue has occurred
    OutputToConsole("Acknowledgement not received from Microcontroller.");
    return false;

}

bool OscillationFrequencySetting(int High, int Mid, int Low, int Exp) {
    
    OutputToConsole("Setting Oscillation Frequency.");

    // Send the Oscillation Frequency command.
    OutputToConsoleDebug("Sending Oscillation Frequency Setting Command.");
    SendCommand(PROG_CMD_OSC_FREQ);
    Delay(PROG_DELAY_COMACK);
    
    // Check if the command was acknowledged.
    if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
        OutputToConsoleDebug("Received Oscillation Frequency Setting Acknowledgement.");

        Delay(PROG_DELAY_ACKDAT);

        OutputToConsoleDebug("Sending High Byte: " + String(High));
        SendData(High);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Mid Byte: " + String(Mid));
        SendData(Mid);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Low Byte: " + String(Low));
        SendData(Low);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Exponent Byte: " + String(Exp));
        SendData(Exp);
        Delay(PROG_DELAY_FRQCAL);

        OutputToConsoleDebug("Sending Oscillation Frequency Set Command.");
        if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
            OutputToConsoleDebug("Received Oscillation Frequency Setting Acknowledgement.");
            Delay(PROG_DELAY_ACKCOM);
            OutputToConsole("Oscillation Frequency Set.");
            return true;
        }
    }
    
    Delay(PROG_DELAY_ACKCOM);
    OutputToConsole("Oscillation Frequency Setting Failed.");
    return false;

}

bool FlashEraseTimeSetting(int High, int Mid, int Low, int Exp) {

    OutputToConsole("Setting Flash Erase Time.");

    // Send the Oscillation Frequency command.
    OutputToConsoleDebug("Sending Flash Erase Time Command.");
    SendCommand(PROG_CMD_ERASE_TIME);
    Delay(PROG_DELAY_COMACK);
    
    // Check if the command was acknowledged.
    if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
        OutputToConsoleDebug("Received Flash Erase Time Acknowledgement.");

        Delay(PROG_DELAY_ACKDAT);

        OutputToConsoleDebug("Sending High Byte: " + String(High));
        SendData(High);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Mid Byte: " + String(Mid));
        SendData(Mid);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Low Byte: " + String(Low));
        SendData(Low);
        Delay(PROG_DELAY_DATDAT);
        
        OutputToConsoleDebug("Sending Exponent Byte: " + String(Exp));
        SendData(Exp);
        Delay(PROG_DELAY_ERASETMSET);

        OutputToConsoleDebug("Sending Flash Erase Time Set Command.");
        if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
            OutputToConsoleDebug("Received Flash Erase Time Setting Acknowledgement.");
            Delay(PROG_DELAY_ACKCOM);
            OutputToConsole("Flash Erase Time Set.");
            return true;
        }
    }
    
    Delay(PROG_DELAY_ACKCOM);
    OutputToConsole("Flash Erase Time Setting Failed.");
    return false;

}

bool GetSiliconSignatureData() {

    OutputToConsole("Requesting Silicon Signature.");

    // Send the Silicon Signature command.
    OutputToConsole("Sending Silicon Signature Command.");
    SendCommand(PROG_CMD_SIL_SIG);
    Delay(PROG_DELAY_COMACK);

    // Check if the command was acknowledged
    if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
        OutputToConsole("Received Silicon Signature Acknowledgement.");
        Delay(PROG_DELAY_ACKDAT);

        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_VENDOR = ReceiveData();
        Delay(PROG_DELAY_DATDAT);

        OutputToConsoleDebug("Reading ID Code Data");
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_ID = ReceiveData();
        Delay(PROG_DELAY_DATDAT);

        OutputToConsoleDebug("Reading Electrical Information Data");
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_ELEC_INFO = ReceiveData();
        Delay(PROG_DELAY_DATDAT);

        OutputToConsoleDebug("Reading Last Address Data");
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_LAST_ADDR[0] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_LAST_ADDR[1] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_LAST_ADDR[2] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);

        OutputToConsoleDebug("Reading Device Name Data");
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[0] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[1] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[2] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[3] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[4] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[5] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[6] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[7] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[8] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_DEV_NAME[9] = ReceiveData();
        Delay(PROG_DELAY_DATDAT);
    
        OutputToConsoleDebug("Reading Block Info Data");
        PROG_SIL_SIG_TABLE.PROG_SIL_SIG_BLOCK_INFO = ReceiveData();
        Delay(PROG_DELAY_DATACK);

        if (ReceiveCommand(PROG_CMD_RETURN_ACK)) {
            Delay(PROG_DELAY_ACKCOM);
            OutputToConsoleDebug("Received Silicon Signature Successfully.");
            return true;
        }
    }

    Delay(PROG_DELAY_ACKCOM);
    OutputToConsole("Silicon Signature Request Failed.");
    return false;

}

bool GetCurrentStatus() {
    
}

void PowerDownChip() {

    OutputToConsole("Powering Down Chip.");

    // Connect the RESET pin to ground.
    OutputToConsoleDebug("RESET = LOW");
    digitalWrite(PROG_PIN_RESET, LOW);

    OutputToConsoleDebug("SCK = LOW");
    digitalWrite(PROG_PIN_SCK, LOW);

    // Disconnect power from the VPP Pin.
    OutputToConsoleDebug("VPP (ENABLE) = LOW");
    digitalWrite(PROG_PIN_EN, LOW);

    // Disconnect power from the VDD Pin.
    OutputToConsoleDebug("VDD = LOW");
    digitalWrite(PROG_PIN_VDD, LOW);

}


void Delay(PROG_DELAY Delay, bool Microseconds) {

    if (!Microseconds) {
        delay(Delay);
    }
    else
    {
        delayMicroseconds(Delay);
    }

}

void ClockPulse() {

    // Pulse the Clock for one tick.

    // Tick
    digitalWrite(PROG_PIN_SCK, LOW);
    delay(PROG_DELAY_SCKFREQ);
    digitalWrite(PROG_PIN_SCK, HIGH);
    delay(PROG_DELAY_SCKFREQ);
}

void SendCommand(PROG_CMD Command) {

    // Send each bit of the byte, whilst ticking the clock.

    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(PROG_PIN_TX, ((Command >> i) & 0x01));
        ClockPulse();
    }

    // Set the TX Pin back to 0.
    digitalWrite(PROG_PIN_TX, LOW);
}

void SendData(byte Data) {
    
    // Send each bit of the byte, whilst ticking the clock.

    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(PROG_PIN_TX, ((Data >> i) & 0x01));
        ClockPulse();
    }

    // Set the TX Pin back to 0.
    digitalWrite(PROG_PIN_TX, LOW);

}

bool ReceiveCommand(PROG_CMD_RETURN ReturnCode) {

    // Receive each bit of the byte after each clock pulse.

    byte Command = 0;

    for (int i = 7; i >= 0; i--)
    {
        ClockPulse();
        int CurrentByte = digitalRead(PROG_PIN_RX);

        OutputToConsoleDebug("Read (Bit): " + String(CurrentByte));

        if (CurrentByte == 1) {
            bitSet(Command, i);
        }
    }

    OutputToConsoleDebug("Read (Byte): " + String(Command));

    // Check if the response from the Microcontroller is the expected one.
    return Command == ReturnCode;

}

byte ReceiveData() {
    // Receive each bit of the byte after each clock pulse.

    byte Data = 0;

    for (int i = 7; i >= 0; i--)
    {
        ClockPulse();
        int CurrentByte = digitalRead(PROG_PIN_RX);

        OutputToConsoleDebug("Read (Bit): " + String(CurrentByte));

        if (CurrentByte == 1) {
            bitSet(Data, i);
        }
    }

    OutputToConsoleDebug("Read (Byte): " + String(Data));

    return Data;
}

void PrintSiliconSignature() {
    
    // Title
    OutputToConsole("Silicon Signature: ");

    // Vendor Code
    if (PROG_SIL_SIG_TABLE.PROG_SIL_SIG_VENDOR == PROG_VENDOR_NEC) {
        OutputToConsole("Vendor Code: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_VENDOR, HEX) + " (NEC)");
    }
    else
    {
        OutputToConsole("Vendor Code: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_VENDOR, HEX));
    }

    // ID Code
    OutputToConsole("ID Code: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_ID, HEX));

    // Electrical Information
    OutputToConsole("Electrical Information: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_ELEC_INFO, HEX));

    // ID Code
    OutputToConsole("Model Code: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_ID));

    // Block Count
    OutputToConsole("Block Count: " + String(PROG_SIL_SIG_TABLE.PROG_SIL_SIG_BLOCK_INFO));

}