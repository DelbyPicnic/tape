#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>

#include <tape.hpp>
#include <audio.hpp>

typedef signed short SAMPLE;


Tape::Tape()
{
    tapeData = new int16_t[MAX_TAPE_SIZE];
    _end = 0;
    _head  = 0;
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

    if (bytesRead > 0){
        if (tapeHeader.Subchunk2Size > MAX_TAPE_SIZE){
            std::cerr << tapeHeader.Subchunk2Size << " - selected file is larger than 10mb" << std::endl;
            exit(1);
        }else{

            uint16_t bytesPerSample = tapeHeader.bitsPerSample / 8;      
            uint64_t numSamples = tapeHeader.ChunkSize / bytesPerSample;
            static const uint16_t BUFFER_SIZE = 4096;
            int16_t* buffer = new int16_t[BUFFER_SIZE];
        
            while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE, tapeFile)) > 0)
            {
                memcpy(tapeData + _end, buffer, sizeof(buffer[0]) * bytesRead);
                _end += bytesRead;
            }

            std::cout << _end << " bytes read." << std::endl;

            delete [] buffer;
            buffer = nullptr;
            fileLength = getTapeSize(tapeFile);

            
            fclose(tapeFile);
            return true;
        }
    }
    return false;
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
