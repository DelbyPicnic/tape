#pragma once
#include <memory.h>
#include <math.h>
#include <atomic>

typedef struct  TAPE_HEADER
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
} tape_hdr;

typedef struct TAPE_DATA
{
    
} tape_data;

class Tape 
{
public:
    Tape();
    ~Tape();
    bool loadTape(std::string tpath);
    bool ejectTape();
    void _flush();

    void testFunc();
private:
    int getTapeSize(FILE* tapeFile);
    unsigned long getTapeLength();
    long moveHeadBy(long amount);
    long moveHeadTo(long position);

    static const long MAX_TAPE_SIZE = 1e7;
    std::atomic<bool> loaded = false;

    FILE* tapeFile;
    tape_hdr tapeHeader;
    
    uint32_t sampleRate;
    int16_t* tapeData;
    unsigned int channels;
    unsigned long _start;
    unsigned long _end;
    unsigned long _head;
};