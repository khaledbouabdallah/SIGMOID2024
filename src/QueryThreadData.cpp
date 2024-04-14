#include "QueryThreadData.hpp"
#include "Query.hpp"
#include <iostream>

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
     //indices should be in a linked list
     Query* retq  = NULL;
     for (int i = 0; i<_queryIndices.size(); ++i) {     
	     Query* qq = _queries[_queryIndices[_crtQuery]];
	     _crtQuery = (_crtQuery+1)%_queryIndices.size();
	     if (!qq->IsFinished()) {
	          retq = qq;
	          break; //this query needs more running
	     }
	}
	cout<<"next query of indice "<<_queryIndices[_crtQuery]<<" "<<endl;
	return retq;
}

void QueryThreadData::feedWithQueries(int threadIndex, Query** queries, int countQueries, int countThreads) {
     _queries = queries;
	int queriesperthread = countQueries / countThreads;
	int mod = countQueries % countThreads;
	int start = queriesperthread * threadIndex;
	if (threadIndex<=mod)
		start+=threadIndex;
	int length = queriesperthread;
	if (threadIndex<mod)
		length++;	
         
     for (int i = start; i<start+length; ++i)
          _queryIndices.push_back(i);
}
	
	
