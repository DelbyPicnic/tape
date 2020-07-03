#include <iostream>
#include <cstdint>
#include <tape.hpp>
#include <math.h>

int main(int argc, char** argv)
{
    size_t buffSize = 8249344;
    Tape<short> myTape(buffSize);
    myTape.loadFile("sordid_affair.wav");
    return 0;
}