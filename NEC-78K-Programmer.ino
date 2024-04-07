/*
    Arduino-Based NEC 78K Programmer
    06/04/2024
    James.Todd@nottingham.ac.uk
*/

// Pin Definitons
#define     PROG_SCK        2       // Connects to: TX
#define     PROG_RX         3       // Connects to: SO10
#define     PROG_TX         4       // Connects to: RX
#define     PROG_RESET      5       // Connects to: RESET
#define     PROG_EN         6       // Connects to: VPP
#define     PROG_VDD        7       // Connects to: VDD

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PROG_EN, OUTPUT);
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    //digitalWrite(PROG_EN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    //digitalWrite(PROG_EN, LOW);
    delay(1000);
}