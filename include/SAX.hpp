#ifndef _ISAX_HPP
#define _ISAX_HPP

#include "globals.hpp"
#include "DataBase.hpp"
#include <vector>

using std::vector;

class SAX {

    private:

    int _wordSize; // the word length (number of segments)
    int _alphaSize; // the alphabet size (number of symbols in the alphabet)
    float* _breakpoints; // the breakpoints of the alphabet

    public:
    
        SAX(int wordSize,int alphaSize);
        
        // float vector to be transformed into a PAA representation
        float* ToPAA(float* vector);

        // float vector to be transformed into a SAX representation (binary)
        int ToSAX(float* paa);

        // SAX of a whole database
        int* ToSAX(float* vector, DataBase& db);

        ~SAX();

    private:
        
        // splits the data into segments for PAA
        int* splitsX(int wordSize);


};



#endif 