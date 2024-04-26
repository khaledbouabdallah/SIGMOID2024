#ifndef _QUERYQUEUE_HPP
#define QUERYQUEUE_HPP

class LLEntry{
public:
	int _queryIndex;
	LLEntry* _next;
     LLEntry* _prev;
public:
	inline LLEntry(int indice, LLEntry* prev, LLEntry* next) : _queryIndex(indice), _next(next), _prev(prev){}
};


class QueryQueue {

private:
     int _type; //0 array, 1 linked list
     int* _allQueries;
     LLEntry** _allEntries;
     int _first;
     int _countQueries;

     LLEntry*	_firste;
     LLEntry*	_laste;

public:
     QueryQueue(int type, int* queryIndices, int countQueries);
     ~QueryQueue();
     
     int PopFront();
     void PushBack(int indice);
     
};

#endif
