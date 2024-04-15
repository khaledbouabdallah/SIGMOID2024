#include "QueryRunManager.hpp"

#include <unistd.h>
#include <pthread.h>
#include "QueryThreadData.hpp"
#include "Query.hpp"
#include "globals.hpp"
#include <iostream>

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
		if (!crtQuery) break; //no more queries to run for this thread
		crtQuery->run(data->_switchTask);
	}				 
	return NULL;
}

void QueryRunManager::run(){
	pthread_t* threads = new pthread_t[_countThreads];

	//launch threads
     for (int  i = 0; i < _countThreads; ++i)
		pthread_create(&threads[i], NULL, queryThreadTask, (void*) &_threadData[i]);
		
     while (!done) {
     }	
     //join the other threads
     for (int  i = 0; i < _countThreads; ++i)
		pthread_join(threads[i], NULL);
		
	cout<<"all joined"<<endl;
}

void QueryRunManager::stop(){
}


