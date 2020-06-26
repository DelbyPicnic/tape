#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <tape.hpp>
#include <audio.hpp>

typedef signed short SAMPLE;


Tape::Tape()
{
    // constructor

}

bool Tape::loadTape(std::string tpath)
{
    tapeFile = fopen(tpath.c_str(), "r+");
    if (tapeFile == nullptr){
        std::cout << "could not load tape." << std::endl;
        return false;
    }

    int headerSize = sizeof(tape_hdr);
    int fileLength = 0;
    size_t bytesRead = fread(&tapeHeader, 1, headerSize, tapeFile);
    std::cout << "Header Read " << bytesRead << " bytes." << std::endl;

    return true;
}

bool Tape::ejectTape()
{
    return false;
}

void Tape::_flush()
{

}

int Tape::getTapeSize(FILE* tapeFile)
{
    int tapeSize = 0;
    fseek(tapeFile, 0, SEEK_END);
    tapeSize = ftell(tapeFile);
    fseek(tapeFile, 0, SEEK_SET);

    return tapeSize;
}
