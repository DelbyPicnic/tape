/*
    based on:
    https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
*/

#pragma once
#include <memory>
#include <cstdio>
#include <math.h>
#include <mutex>
#include <wave.hpp>

template <typename T>
class Tape 
{
public:
    explicit Tape(size_t size) : data(std::unique_ptr<T[]>(new T[size])), maxSize(size){};
    bool loadFile(const std::string fname);
    bool saveFile(const std::string fname);
    void clear();
    size_t getAvailable() const;
    size_t getSize() const;

private:
    // for loading to and from file
    FILE* wavFile;
    wav_hdr waveHeader;

    // for managing internal data
    std::mutex mtx;
    std::unique_ptr<T[]> data;
    const size_t maxSize;
    size_t sampleRate;
    size_t start = 0;
    size_t end = 0;
    size_t head = 0;
};

template<typename T>
bool Tape<T>::loadFile(const std::string fname)
{
    wavFile = fopen(fname.c_str(), "r");
    if (wavFile == nullptr){
        std::cout << "could not load tape." << std::endl;
        return false;
    }

    int headerSize = sizeof(wav_hdr);
    int fileLength = 0;
    size_t samplesRead = fread(&waveHeader, 1, headerSize, wavFile);

    if (samplesRead > 0){
        if (waveHeader.Subchunk2Size > maxSize){
            std::cerr << waveHeader.Subchunk2Size << " - selected file is larger than allocated memory" << std::endl;
            exit(1);
        }else{

            uint16_t bytesPerSample = waveHeader.bitsPerSample / 8;  
            uint64_t numSamples = waveHeader.ChunkSize / bytesPerSample;
            static const uint16_t BUFFER_SIZE = 4096;
            T* buffer = new T[BUFFER_SIZE];
            T* t_data = data.get();

            while ((samplesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE, wavFile)) > 0)
            {
                memcpy(t_data + end, buffer, sizeof(buffer[0]) * samplesRead);
                end += samplesRead * sizeof(buffer[0]);
                
            }
        
            std::cout << end << " bytes read." << std::endl;

            delete [] buffer;
            buffer = nullptr;
            fclose(wavFile);

            // set tape head position
            head = 0; //for now

            return true;
        }
    }
    
    return false;
}

template<typename T>
bool Tape<T>::saveFile(const std::string fname)
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
