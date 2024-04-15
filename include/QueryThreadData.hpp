#ifndef _QUERYTHREADDATA_HPP
#define QUERYTHREADDTA_HPP

#include <vector>
class Query;

using namespace std;

class QueryThreadData
{
private:
     vector<int> 	_queryIndices;
	Query** 		_queries;
	int 		     _crtQuery;	
	int            _threadIndex;

public:
	int 		     _switchTask;
	int            _allDone;
	
public:
	QueryThreadData();
	~QueryThreadData();
	
	void setSwitchTaskOn();
	void setSwitchTaskOff();
	
	Query* getNextQuery();
	
	void feedWithQueries(int threadIndex, Query** queries, int countQueries, int countThreads);
};

#endif
