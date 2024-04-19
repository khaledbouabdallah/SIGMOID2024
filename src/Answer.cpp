#include "Answer.hpp"
#include <iostream>
#include "float.h"

using namespace std;

Answer::Answer(): _countPoints(0), _distMax(FLT_MAX) {
}

Answer::~Answer(){
}

void Answer::CheckAndAdd(int indice, float distance) {
   if (_countPoints < DATA_SIZE) {
      _nns[_countPoints]._indice = indice;
      _nns[_countPoints]._distance = distance;
      if (_countPoints)
         SiftUp(_countPoints);
      _countPoints++;
   } else if (distance<_nns[0]._distance) {
      _nns[0]._indice = indice;
      _nns[0]._distance = distance;
      SiftDown(0);
   }
}

void Answer::SiftUp(int indice) {
   while(1) {
      int indmin = indice;
      // check
      if(_nns[(indice-1)/2]._distance < _nns[indice]._distance)
         indmin = (indice-1)/2;
      if(indmin == indice)
         break;
      // swap values
      Neighbour temp_neighbour = _nns[indmin];
      _nns[indmin] = _nns[indice];
      _nns[indice] = temp_neighbour;
      // update the indice
      indice = indmin;
   }
   _distMax = _nns[0]._distance;
}

void Answer::SiftDown(int indice) {
   int n = _countPoints ;
   while(1) {
      int indmax = indice;
      // check
      if(2*indice+1<n && (_nns[2*indice+1]._distance > _nns[indmax]._distance))
         indmax = 2*indice+1;
      if(2*indice+2<n && (_nns[2*indice+2]._distance > _nns[indmax]._distance))
         indmax = 2*indice+2;
      if(indmax == indice)
         break;
      // swap values
      Neighbour temp_neighbour = _nns[indmax];
      _nns[indmax] = _nns[indice];
      _nns[indice] = temp_neighbour;
      // update the indice
      indice = indmax;
   }
   _distMax = _nns[0]._distance;
}

void Answer::FillMissing(){
     if (_countPoints < DATA_SIZE) 
          for (int i = _countPoints; i<DATA_SIZE; ++i)
               _nns[i]._indice = _nns[0]._indice;
}    

void Answer::WriteOutput(ofstream& ofs){
     //for (int i = 0; i < 100; ++i) 
     //     cout<<_nns[i]._indice<<" "<<_nns[i]._distance<<endl;
     for (int i = 0; i < DATA_SIZE; ++i) 
          ofs.write(reinterpret_cast<char const *>(&(_nns[i]._indice)), sizeof(uint32_t));
}
 
