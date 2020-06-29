#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <tape.hpp>
#include <audio.hpp>

template<typename T>
Tape<T>::~Tape()
{
    delete [] data;
    data = nullptr;
}

template<typename T>
Tape<T>::loadFile(const std::string fname)
{
    // load data from wav file into buffer
    if (!loaded){
        tapeFile = fopen(tpath.c_str(), "r+");
        if (tapeFile == nullptr){
            std::cout << "could not load tape." << std::endl;
            return false;
        }
    
        int headerSize = sizeof(tape_hdr);
        int fileLength = 0;
        size_t samplesRead = fread(&tapeHeader, 1, headerSize, tapeFile);

        if (samplesRead > 0){
            if (tapeHeader.Subchunk2Size > MAX_TAPE_SIZE){
                std::cerr << tapeHeader.Subchunk2Size << " - selected file is larger than 10mb" << std::endl;
                exit(1);
            }else{

                uint16_t bytesPerSample = tapeHeader.bitsPerSample / 8;      
                uint64_t numSamples = tapeHeader.ChunkSize / bytesPerSample;
                static const uint16_t BUFFER_SIZE = 4096;
                SAMPLE* buffer = new SAMPLE[BUFFER_SIZE];

                

                while ((samplesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE, tapeFile)) > 0)
                {
                    memcpy(data->buffer + _end, buffer, sizeof(buffer[0]) * samplesRead);
                    _end += samplesRead * sizeof(buffer[0]);
                    
                }
                std::cout << "here" << std::endl;
                std::cout << _end << " bytes read." << std::endl;

                delete [] buffer;
                buffer = nullptr;
                fclose(tapeFile);

                // set tape head position
                _head = 0; //for now

                return true;
            }
        }
    }
    return false;
}

template<typename T>
Tape<T>::saveFile(const std::string fname)
{
    // save data from buffer into wav file
}

template<typename T>
void Tape<T>::clear()
{
    std::lock_guard<std::mutex> lock(mtx);
    head = 0;
    start = 0;
    end = 0;
}

template<typename T>
size_t Tape<T>::getAvailable() const
{
    return maxSize - head;
}

template<typename T>
size_t Tape<T>::getSize() const
{
    return maxSize;
}
