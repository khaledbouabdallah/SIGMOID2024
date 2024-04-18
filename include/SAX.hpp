#ifndef _ISAX_HPP
#define _ISAX_HPP

#include "globals.hpp"
#include "DataBase.hpp"
#include <vector>
#include <bitset>

using std::vector;

class SAX {

    private:

    int _wordSize; // the word length (number of segments)
    int _alphaSize; // the alphabet size (number of symbols in the alphabet)
    vector<float> _breakpoints; // the breakpoints of the alphabet

    public:
    
        SAX(int wordSize,int alphaSize);
        
        // float vector to be transformed into a PAA representation
        float* ToPAA(float* vector, int taille);

        // float vector to be transformed into a SAX representation (binary)
        std::bitset<nombres_de_bits >* ToSAX(float* paa, int taille);

        // SAX of a whole database
        int* ToSAX(DataBase& db);

        ~SAX();

    private:
        
        // splits the data into segments for PAA
        int* splitsX(int wordSize);


};



#endif 