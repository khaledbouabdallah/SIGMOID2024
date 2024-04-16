#include <vector>
#include "SAX.hpp"
#include "globals.hpp"
#include "Utils.hpp"
#include <iostream>

using std::vector;

SAX::SAX(int wordSize,int alphaSize) {
    _wordSize = wordSize;
    _alphaSize = alphaSize;
    _breakpoints = getBreakPoints(alphaSize);

}


float* SAX::ToPAA(float* vector, int taille) {
   
     float *paa = new float[_wordSize];
     int segmentSize = taille/_wordSize;  

     for(int i=0; i<_wordSize; i++){

          paa[i]=calculateMean(vector, i*segmentSize, (i+1)*segmentSize-1); }
     
     return paa;
}

/**int* SAX::ToSAX(float* paa, int taille) {
     
     int* sax = new int[taille];
     int middle = _breakpoints.size()/2;
     for(int i=0; i<taille; i++)
     {

     int low = 0;
     int high = _breakpoints.size();
     int mid;

     if (paa[i] < _breakpoints[0]) {
          sax[i] = 0;
          continue;
     } else if (paa[i] > _breakpoints[_breakpoints.size()-1]) {
          sax[i] = _breakpoints.size();
          continue;
          }

     while (low <= high) {

          mid = (low + high) / 2;

          
          if (paa[i] < _breakpoints[mid]) {
               high = mid ;
          } else if (paa[i] > _breakpoints[mid]){
               low = mid ;
          } else if ( paa[i]== _breakpoints[mid]) {
               break;}
          if (high - low <= 1) {
               mid = high;
               break;
          }
     }

     sax[i] = mid;
     }

     

     return sax;
}*/
std::bitset<sizeof(int) >* SAX::ToSAX(float* paa, int taille) {
    std::bitset<sizeof(int) >* sax = new std::bitset<sizeof(int) >[taille];
    int breakpointsSize = _breakpoints.size();

    for(int i = 0; i < taille; i++) {
        int low = 0;
        int high = breakpointsSize;
        int mid;

        if (paa[i] < _breakpoints[0]) {
            sax[i] = std::bitset<sizeof(int) >(0); // Store 0 as binary
            continue;
        } else if (paa[i] > _breakpoints[breakpointsSize - 1]) {
            std::bitset<sizeof(int) > tmp = std::bitset<sizeof(int) >(breakpointsSize);
            sax[i] = tmp; // Store breakpointsSize as binary
            continue;
        }

        while (low <= high) {
            mid = (low + high) / 2;

            if (paa[i] < _breakpoints[mid]) {
                high = mid;
            } else if (paa[i] > _breakpoints[mid]) {
                low = mid;
            } else {
                break;
            }

            if (high - low <= 1) {
                mid = high;
                break;
            }
        }

        // Convert mid to a binary string and then to an integer
        sax[i] = std::bitset<sizeof(int) >(mid);
    }

    return sax;
}


     
int* SAX::ToSAX(float* vector, DataBase& db) {
     return NULL;
}

SAX::~SAX() {

}

int* SAX::splitsX(int wordSize) {
     return NULL;
}
