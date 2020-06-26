#include <iostream>
#include <tape.hpp>



int main(int argc, char** argv)
{
    Tape* myTape = new Tape();
    myTape->loadTape("bwaaaa.wav");
    return 0;
}