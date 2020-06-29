#include <iostream>
#include <tape.hpp>
#include <math.h>



int main(int argc, char** argv)
{
    /*
    Tape* myTape = new Tape();
    myTape->loadTape("bwaaaa.wav");
    myTape->testFunc();
    return 0;
    */
    int a = 42;
    int b = -20;
    int c = 0;
    if (signbit(a))
        std::cout << "a = yes" << std::endl;

    if (signbit(b))
        std::cout << "b = yes" << std::endl;

    if (signbit(c))
        std::cout << "c = yes" << std::endl;

}