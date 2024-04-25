#include "QueryQueue.hpp"
#include "pthread.h"

pthread_mutex_t qMutex;

QueryQueue::QueryQueue(int type, int* queryIndices, int countQueries) : _type(type), _countQueries(countQueries) {
     _allQueries = new int[countQueries];
     for (int i = 0; i<_countQueries; ++i)
          _allQueries[i] = queryIndices[i];
     _first = 0; 
}
 
QueryQueue::~QueryQueue(){
}

int QueryQueue::PopFront(){
     int res = -1;
     pthread_mutex_lock(&qMutex);
     if (_first<_countQueries) {
          res = _allQueries[_first];
          _first++;
     }
     pthread_mutex_unlock(&qMutex); 
     return res;
}

void QueryQueue::PushBack(int indice){
}
