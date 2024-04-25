#ifndef _QUERYQUEUE_HPP
#define QUERYQUEUE_HPP


class QueryQueue {

private:
     int _type; //0 array, 1 linked list
     int* _allQueries;
     int _first;
     int _countQueries;
public:
     QueryQueue(int type, int* queryIndices, int countQueries);
     ~QueryQueue();
     
     int PopFront();
     void PushBack(int indice);
     
};

#endif
