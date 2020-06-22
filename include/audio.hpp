#pragma once
#include <RtAudio.h>

/*
Audio Subsystem for RtAudio
Adapted from VCV Rack source by Andrew Belt
https://github.com/VCVRack/Rack/blob/v1/src/audio.cpp
*/

struct AudioDevice {
    int driver_id = 0;
    int device_id = -1;
    int offset = 0;
    int sample_rate = 44100;
    int chunk_size = 512;
    int n_outputs = 0;
    int n_inputs = 0;
    RtAudio* rtaudio = NULL;
    RtAudio::DeviceInfo device_info;

    AudioDevice();
    virtual ~AudioDevice();

    std::vector<int> get_driver_ids();
    std::string get_driver_name(int driver_id);
    void set_driver_id(int driver_id);

    int get_n_devices();
    bool get_device_info(int device_id, RtAudio::DeviceInfo* device_info);
    int get_n_channels(int device_id);
    std::string get_device_name(int device_id);
    void set_device_id(int device_id, int offset);

    std::vector<int> get_sample_rates();
    void set_sample_rate(int sample_rate);
    std::vector<int> get_chunk_sizes();
    void set_chunk_size(int chunk_size);

    void set_channels(int n_outputs, int n_inputs);

    void start();
    void stop();
    virtual void process(const float* input, float* output, int frames) {}
    virtual void on_start() {}
    virtual void on_stop() {}
    virtual void ch_changed() {}
};
