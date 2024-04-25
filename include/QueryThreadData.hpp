#ifndef _QUERYTHREADDATA_HPP
#define QUERYTHREADDTA_HPP

#include <vector>
class Query;
class QueryQueue;

using namespace std;

class QueryThreadData
{
public:
     vector<int> 	_queryIndices;
	int 		     _crtQuery;	
	int            _threadIndex;
	int 		     _switchTask;
	int            _qassignType;
	QueryQueue*    _queryQ;
     Query** 		_queries;
	
public:
	QueryThreadData();
	~QueryThreadData();
	
	void setSwitchTaskOn();
	void setSwitchTaskOff();
	
	Query* getNextQuery();
	
	void Init(int qassignType, QueryQueue* q, int threadIndex, Query** queries, int* queryIndices, int countQueries, int countThreads);
};

#endif
