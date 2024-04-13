#include "SDStorage.h"

File currentFile;
Sd2Card card;
SdVolume volume;
SdFile root;

bool InitialiseSD(int PIN_CS) {
    if (!SD.begin(PIN_CS)) {
        return true;
    }

    return false;
}

void SDInformation(int PIN_CS) {
    String Type;
    String FileSystem;
    String Clusters;
    String Blocks;
    String TotalBlocks;
    String FSName;
    String SizeKb;
    String SizeMb;
    String SizeGb;

    if (!card.init(SPI_HALF_SPEED, PIN_CS)) {
        OutputToConsole(F("SD Card Error"));
    }
    
    switch (card.type()) {
        case SD_CARD_TYPE_SD1:
            Type = F("SD1");
            break;
        case SD_CARD_TYPE_SD2:
            Type = F("SD2");
            break;
        case SD_CARD_TYPE_SDHC:
            Type = F("SDHC");
            break;
        default:
            Type = F("Unknown");
    }

    if (!volume.init(card)) {
        FileSystem = F("File System not recognised.");
        OutputToConsole("SD Card Information: ------------------------ \nType: " + Type + "\nFile System: " + FileSystem + "\n---------------------------------------------\n");
    }
    else
    {
        Clusters = volume.clusterCount();
        Blocks = volume.blocksPerCluster();
        TotalBlocks = volume.blocksPerCluster() * volume.clusterCount();
        FSName = String(volume.fatType(), DEC);
        SizeKb = String((volume.blocksPerCluster() * volume.clusterCount()) / 2);
        SizeMb = String(((volume.blocksPerCluster() * volume.clusterCount()) / 2) / 1024);
        SizeGb = String((float)(((volume.blocksPerCluster() * volume.clusterCount()) / 2) / 1024) / 1024);

        OutputToConsole(F("SD Card Information: ------------------------"));
        OutputToConsole("Type: " + Type);
        OutputToConsole("Clusters: " + Clusters);
        OutputToConsole("Blocks: " + Blocks);
        OutputToConsole("Total Blocks:" + TotalBlocks);
        OutputToConsole("File System: " + FSName);
        OutputToConsole("Size (Kb): " + SizeKb);
        OutputToConsole("Size (Mb): " + SizeMb);
        OutputToConsole("Size (Gb): " + SizeGb);
        OutputToConsole(F("---------------------------------------------"));
        OutputToConsole(F(""));
    }
}

bool OpenFile(String Path) {
    currentFile = SD.open(Path.c_str(), FILE_WRITE);

    if (currentFile) {
        return true;
    }

    return false;
}