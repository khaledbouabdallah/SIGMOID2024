#include "Answer.hpp"

Answer::Answer(): _countPoints(0) {
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
     // a toi de jouer Jb : p
}

void Answer::SiftDown(int indice) {
     // a toi de jouer Jb : p
}
