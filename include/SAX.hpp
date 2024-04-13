#ifndef _ISAX_HPP
#define _ISAX_HPP

#include "globals.hpp"
#include <vector>

using std::vector;

class SAX {

    private:

    int _wordSize; // the word length (number of segments)
    int _alphaSize; // the alphabet size (number of symbols in the alphabet)
    float* _breakpoints; // the breakpoints of the alphabet

    public:
    
        SAX(int wordSize,int alphaSize, float* breakpoints);

        float* PAA(float* vector, int alphaSize);

        float* getBreakpoints(int cardinality);

        void indexToWord(int index, int wordSize, int alphaSize, int* word);

        ~SAX();


};



#endif 