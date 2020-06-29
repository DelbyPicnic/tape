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
