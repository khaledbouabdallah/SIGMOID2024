#include "QueryThreadData.hpp"
#include "Query.hpp"

QueryThreadData::QueryThreadData() :
	_switchTask(0), _crtQuery(0), _queries(0) {}

QueryThreadData::~QueryThreadData() {}

void QueryThreadData::setSwitchTaskOn() {
	//this needs a lock !!
	_switchTask = 1;
}

void QueryThreadData::setSwitchTaskOff() {
	//this needs a lock !!
	_switchTask = 0;
}

Query* QueryThreadData::getNextQuery() {
	Query* retq = _queries[_queryIndices[_crtQuery]];
	_crtQuery = (_crtQuery+1)%_queryIndices.size();
	return retq;
}

void QueryThreadData::feedWithQueries(int threadIndex, Query** queries, int countQueries, int countThreads) {
	int queriesperthread = countQueries / countThreads;
	int mod = countQueries % countThreads;
	int start = queriesperthread * threadIndex;
	if (threadIndex<=mod)
		start+=threadIndex;
	int length = queriesperthread;
	if (threadIndex<mod)
		length++;	
}
	
	
