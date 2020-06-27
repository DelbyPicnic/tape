#include <iostream>
#include <tape.hpp>



int main(int argc, char** argv)
{
    Tape* myTape = new Tape();
    myTape->loadTape("sordid_affair.wav");
    return 0;
}