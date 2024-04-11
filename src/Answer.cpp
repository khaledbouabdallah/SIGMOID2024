#include "Answer.hpp"

Answer::Answer(){
     for (int i = 0; i<DATA_SIZE; ++i)
          nns[i]._indice = i;
}

Answer::~Answer(){
}

void Answer::InitWithIndices(int* indices, int start) {
     for (int i = 0; i<DATA_SIZE; ++i)
          nns[i]._indice = indices[start+i];
}

void Answer::ComputeInitDistances(){
     //to fill
}
