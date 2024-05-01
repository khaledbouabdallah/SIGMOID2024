#include "../include/QueryQueue.hpp"
#include "pthread.h"

pthread_mutex_t qMutex;

//type can be 1 or 2 ; 1 is vector, 2 is linkedlist
QueryQueue::QueryQueue(int type, int* queryIndices, int countQueries) : _type(type), _countQueries(countQueries) {
	if (type == 1) {
     		_allQueries = new int[countQueries];
     		for (int i = 0; i<_countQueries; ++i)
          		_allQueries[i] = queryIndices[i];
     		_first = 0;
	}
	else {
		_firste = _laste = NULL;
		_allEntries = new LLEntry*[countQueries];
		for (int i = 0; i<_countQueries; ++i) 
		     _allEntries[i] = new LLEntry(i, NULL, NULL);
		for (int i = 0; i<_countQueries; ++i) 
			PushBack(queryIndices[i]);
	}
		
}
 
QueryQueue::~QueryQueue(){
}

int QueryQueue::PopFront(){
	if (_type == 1) { //vector
     		int res = -1;
     		pthread_mutex_lock(&qMutex);
     		if (_first<_countQueries) {
          		res = _allQueries[_first];
          		_first++;
     		}
     		pthread_mutex_unlock(&qMutex); 
     		return res;
	} else {
		int res = -1;
		pthread_mutex_lock(&qMutex);
		if (_firste != NULL) {
			res = _firste->_queryIndex;
			_firste = _firste->_next;
               if (_firste == NULL)
                    _laste = NULL;
		}
		pthread_mutex_unlock(&qMutex);
		return res;
	}
}

void QueryQueue::PushBack(int indice){
	if (_type == 1) return;
	pthread_mutex_lock(&qMutex);
	LLEntry* entry = _allEntries[indice];
	entry->_next = NULL;
	entry->_prev = _laste;
	if (_firste == NULL) 
		_firste = entry;
	else 
		_laste->_next = entry;
	_laste = entry;
	pthread_mutex_unlock(&qMutex);
}
