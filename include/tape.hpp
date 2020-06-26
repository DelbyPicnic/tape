#pragma once

typedef struct  TapeHeader{
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned long       riffChunkSize;  // RIFF Chunk Size  
    char                TAPE[4];        // WAVE Header      
    char                fmt[4];         // FMT header       
    unsigned long       fmtChunkSize;   // Size of the fmt chunk                                
    unsigned short      format;         // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      numChannels;    // Number of channels 1=Mono 2=Sterio                   
    unsigned long       sampleFreq;     // Sampling Frequency in Hz                             
    unsigned long       bytesPerSec;    // bytes per second 
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;  // Number of bits per sample      
    char                dataChunkID[4]; // "data"  string   
    unsigned long       Subchunk2Size;  // Sampled data length

}tape_hdr;

class Tape 
{
public:
    Tape();
    bool loadTape(std::string tpath);
    bool ejectTape();
    void _flush();


private:
    int getTapeSize();
    uint32_t sampleRate;
    FILE* tapeFile;
    

};