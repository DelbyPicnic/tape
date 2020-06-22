#include <audio.hpp>
#include <math.h>

/*
Audio Subsystem for RtAudio
Adapted from VCV Rack source by Andrew Belt
https://github.com/VCVRack/Rack/blob/v1/src/audio.cpp
*/

AudioDevice::AudioDevice()
{
    set_driver_id(RtAudio::UNSPECIFIED);
}
AudioDevice::~AudioDevice()
{
    stop();
}

std::vector<int> AudioDevice::get_driver_ids()
{
    std::vector<RtAudio::Api> apis;
    RtAudio::getCompiledApi(apis);
    std::vector<int> drivers;
    for (RtAudio::Api api : apis){
        drivers.push_back((int) api);
    }
    return drivers;
}

std::string AudioDevice::get_driver_name(int driver_id)
{
    switch (driver_id) {
		case RtAudio::UNSPECIFIED: return "Unspecified";
		case RtAudio::LINUX_ALSA: return "ALSA";
		case RtAudio::LINUX_PULSE: return "PulseAudio";
		case RtAudio::LINUX_OSS: return "OSS";
		case RtAudio::UNIX_JACK: return "JACK";
		case RtAudio::MACOSX_CORE: return "Core Audio";
		case RtAudio::WINDOWS_WASAPI: return "WASAPI";
		case RtAudio::WINDOWS_ASIO: return "ASIO";
		case RtAudio::WINDOWS_DS: return "DirectSound";
		case RtAudio::RTAUDIO_DUMMY: return "Dummy Audio";
		default: return "Unknown";
	}
}

void AudioDevice::set_driver_id(int driver_id)
{
    // close device and driver
    set_device_id(-1, 0);
    if (rtaudio){
        delete rtaudio;
        rtaudio = NULL;
    }
    this->driver_id = 0;

    // open driver
    if (driver_id >= 0){
        rtaudio = new RtAudio((RtAudio::Api) driver_id);
        this->driver_id = (int) rtaudio->getCurrentApi();
    }
}

int AudioDevice::get_n_devices()
{
    if (rtaudio){
        return rtaudio->getDeviceCount();
    }
    return 0;
}

bool AudioDevice::get_device_info(int device_id, RtAudio::DeviceInfo* device_info)
{
    if (!device_info)
        return false;
    if (rtaudio){
        if (device_id == this->device_id){
            *device_info = this->device_info;
        }else{
            try {
                *device_info = rtaudio->getDeviceInfo(device_id);
                return true;
            }catch(RtAudioError &err){
                std::cerr << "Failed to get audio device info: " << err.what() << std::endl;
            }
        }
    }
    return false;
}

int AudioDevice::get_n_channels(int device_id)
{
    if (device_id < 0){
        return 0;
    }
    if (rtaudio) {
        RtAudio::DeviceInfo info;
        if (get_device_info(device_id, &info)){
            return std::max((int) info.inputChannels, (int) info.outputChannels);
        }
    }
    return 0;
}

std::string AudioDevice::get_device_name(int device_id)
{
    if (device_id < 0){
        return 0;
    }
    if (rtaudio) {
        RtAudio::DeviceInfo info;
        if (get_device_info(device_id, &info)){
            return info.name;
        }
    }
    return "";
}

void AudioDevice::set_device_id(int device_id, int offset)
{
    stop();
    this->device_id = device_id;
    this->offset = offset;
    start();
}

std::vector<int> AudioDevice::get_sample_rates()
{
    if (rtaudio) {
        try{
            RtAudio::DeviceInfo info = rtaudio->getDeviceInfo(device_id);
            std::vector<int> sample_rates(info.sampleRates.begin(), info.sampleRates.end());
            return sample_rates;
        }catch (RtAudioError &err){
            std::cerr << "Failed to get audio device info: " << err.what() << std::endl;
        }
    }
    return {};
}

void AudioDevice::set_sample_rate(int sample_rate)
{
    if (sample_rate == this->sample_rate)
        return;
    stop();
    this->sample_rate = sample_rate;
    start();
}