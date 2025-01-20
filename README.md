# NEC 78K/0 Programmer
An Arduino-Based Programmer for the NEC/Renesas 78K/0 Microcontoller Series.

## Capabilities

### Programmer Functions
- ```InitialiseProgrammer``` - Initialises the Programmer.
- ```PowerOnChip``` - Powers on the connected 78K/0.
- ```SelectCommunicationsMethod``` - Selects the 78K/0 into Programming mode.
- ```SynchronisationDetectionProcessing``` - Performs Synchronisation Detection Processing.
- ```OscillationFrequencySetting``` - Sets the Oscillation Frequency.
- ```FlashEraseTimeSetting``` - Sets the Flash Erase Time.
- ```GetSiliconSignatureData``` - Gets the Silicon Signature from the connected 78K/0.
- ```GetCurrentStatus``` - Gets the status of the connected 78K/0.
- ```Write``` - Writes data to the specified location within Flash, on the connected 78K/0.
- ```PowerDownChip``` - Powers down the connected 78K/0.

### RE Functions
- ```PrintSiliconSignature``` - Locates blank areas in flash (areas containing ```0xFF```), on the connected 78K/0. Outputs this to the console (SD card output code output commented).

### Console Output
- ```FindBlankAreas``` - Prints the Solicon Signature Data.
- ```PrintCurrentStatus``` - Prints the status of the connected 78K/0.

## Circuitry
![78K0ProgrammerSchematic](https://github.com/user-attachments/assets/8c9592f7-980f-4928-a4e6-9960cc3ada82)

![Programmer](https://github.com/user-attachments/assets/9eb82d6f-0c51-472b-aa00-cde0c601fff3)
