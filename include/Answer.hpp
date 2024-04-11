#ifndef _ANSWER_H
#define _ANSWER_H

#include "globals.hpp"

class Database;

class Neighbour{
public:
     int _indice;
     float _distance; 
};

class Answer {

private:
     Neighbour nns[DATA_SIZE];
     
public:
     Answer();
     ~Answer();
     
     void InitWithIndices(int* indices, int start);
     
     void ComputeInitDistances(); 
};

#endif
