/*
    based on:
    https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/
*/

#pragma once
#include <memory>
#include <cstdio>
#include <math.h>
#include <mutex>

typedef struct wav_header
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;


template <typename T>
class Tape 
{
public:
    explicit Tape(size_t size) : data(std::unique_ptr<T[]>(new T[size])), maxSize(size){};
    ~Tape();
    bool loadFile();
    bool saveFile();
    void clear();
    size_t getAvailable() const;
    size_t getSize() const;


private:
    // for loading to and from file
    FILE* tapeFile;
    wav_hdr tapeHeader;

    // for managing internal data
    std::mutex mtx;
    std::unique_ptr<T[]> data;
    const size_t maxSize;
    size_t sampleRate;
    size_t start = 0;
    size_t end = 0;
    size_t head = 0;
};