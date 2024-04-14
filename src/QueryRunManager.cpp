#include "QueryRunManager.hpp"

#include <unistd.h>
#include <pthread.h>
#include "QueryThreadData.hpp"
#include "Query.hpp"
#include "globals.hpp"

QueryRunManager::QueryRunManager(Query** queries, int countQueries, int countThreads):
	_queries(queries), _countQueries(countQueries), _countThreads(countThreads)
{	
	_threadData = new QueryThreadData[_countThreads];
	
	for (int i = 0; i < _countThreads; ++i) 
		_threadData[i].feedWithQueries(i, _queries, _countQueries, _countThreads);
}

QueryRunManager::~QueryRunManager() {}

void *queryThreadTask(void *arg)
{
	QueryThreadData* data = (QueryThreadData*) arg;
	while (!done) {
		data->setSwitchTaskOff();
		Query* crtQuery = data->getNextQuery();
		crtQuery->run(data->_switchTask);
	}				 
	return NULL;
}

void QueryRunManager::run(){
	//launch threads
	
	pthread_t* threads = new pthread_t[_countThreads];
	QueryThreadData* datas = new QueryThreadData[_countThreads];
	
	for (int  i = 0; i < _countThreads; ++i) {
		datas[i].feedWithQueries(i, _queries, _countQueries, _countThreads);
		pthread_create(&threads[i], NULL, queryThreadTask, (void*) &datas[i]);
	}
}

void QueryRunManager::stop(){
}


