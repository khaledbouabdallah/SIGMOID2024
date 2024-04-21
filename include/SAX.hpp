#ifndef _ISAX_HPP
#define _ISAX_HPP

#include "globals.hpp"
#include "DataBase.hpp"
#include <vector>
#include <bitset>
#include <cstdint>

using std::vector;

class SAX {

    private:

    int _wordSize; // the word length (number of segments)
    int _alphaSize; // the alphabet size (number of symbols in the alphabet)
    vector<float> _breakpoints; // the breakpoints of the alphabet

    public:
    
        SAX(int wordSize,int alphaSize, float mean, float stdev);
        
        // float vector to be transformed into a PAA representation
        float* ToPAA(float* vector, int taille);

        // float vector to be transformed into a SAX representation (binary)
        uint64_t* ToSAX(float* paa, int taille);

        // SAX of a whole database
        uint64_t* ToSAX(DataBase& db);

        ~SAX();

    private:
        
        // splits the data into segments for PAA
        int* splitsX(int wordSize);


};



#endif 
