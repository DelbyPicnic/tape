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

    std::cout << tapeHeader.SamplesPerSec << std::endl;

    if (bytesRead > 0)
    {
        uint16_t bytesPerSample = tapeHeader.bitsPerSample / 8;      
        uint64_t numSamples = tapeHeader.ChunkSize / bytesPerSample;
        static const uint16_t BUFFER_SIZE = 4096;
        int16_t* buffer = new int16_t[BUFFER_SIZE];

        std::cout << sizeof buffer[0] << std::endl;
        
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE, tapeFile)) > 0)
        {
            std::cout << bytesRead << std::endl;
        }
        

        delete [] buffer;
        buffer = nullptr;
        fileLength = getTapeSize(tapeFile);

    }
    fclose(tapeFile);

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
