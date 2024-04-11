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
     Neighbour _nns[DATA_SIZE];
     int _countPoints;
     
public:
     Answer();
     ~Answer();
     
     void CheckAndAdd(int indice, float distance);
     
private:
     void SiftUp(int indice);
     void SiftDown(int indice);
};

#endif