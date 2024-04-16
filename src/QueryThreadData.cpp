#include "QueryThreadData.hpp"
#include "Query.hpp"
#include <iostream>

QueryThreadData::QueryThreadData() :
	_switchTask(0), _crtQuery(0), _queries(0), _allDone(0), _threadIndex(-1) {}

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
	//cout<<"thread "<<_threadIndex<<" next query of indice "<<_queryIndices[_crtQuery]<<" "<<endl;
	if (!retq) 
	     _allDone = 1;
	return retq;
}

void QueryThreadData::feedWithQueries(int threadIndex, Query** queries, int countQueries, int countThreads) {
     _queries = queries;
     _threadIndex = threadIndex;
     for (int i = threadIndex; i<countQueries; i+=countThreads)
          _queryIndices.push_back(i);
     
}
	
	
