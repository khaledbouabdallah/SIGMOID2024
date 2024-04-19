#include "QueryRunManager.hpp"

#include <unistd.h>
#include <pthread.h>
#include "QueryThreadData.hpp"
#include "Query.hpp"
#include "globals.hpp"
#include <iostream>
#include "QueryQueue.hpp"

volatile int remainingQueries;
pthread_mutex_t remQMutex;

QueryRunManager::QueryRunManager(Query** queries, int countQueries, int countThreads, int withIncr, int qassignType):
	_queries(queries), _countQueries(countQueries), _countThreads(countThreads), _withIncr(withIncr), _qassignType(qassignType)
{	
     //increment is not compatible with query queue by array!!
     //should be checked
     
	_threadData = new QueryThreadData[_countThreads];
	remainingQueries = countQueries;
	
	_queryQ = new QueryQueue(qassignType,_countQueries);
	
	for (int i = 0; i < _countThreads; ++i) 
		_threadData[i].Init(_qassignType, _queryQ, i, _queries, _countQueries, _countThreads);
}

QueryRunManager::~QueryRunManager() {}

void *queryThreadTask(void *arg)
{
	QueryThreadData* data = (QueryThreadData*) arg;
	
	if (data->_qassignType == 0) {
	     while (!done) {
		     data->setSwitchTaskOff();
		     Query* crtQuery = data->getNextQuery();
		     if (!crtQuery) break; //no more queries to run for this thread
		     crtQuery->run(data->_switchTask);
		     if (crtQuery->IsFinished()){
                    pthread_mutex_lock(&remQMutex);
	               remainingQueries--;
	               if (remainingQueries == 0)
	                    done = 1;
	               pthread_mutex_unlock(&remQMutex);   
	          }
	     }				 
     }
     else {
          while (!done) {
		     data->setSwitchTaskOff();
		     int indice = data->_queryQ->PopFront();
		     if (indice == -1) continue;
		     //cout<<"thread "<<data->_threadIndex<<" next query of indice "<<indice<<" "<<endl;
		     
		     Query* crtQuery = data->_queries[indice];
		     crtQuery->run(data->_switchTask);
		     if (crtQuery->IsFinished()){
                    pthread_mutex_lock(&remQMutex);
	               remainingQueries--;
	               if (remainingQueries == 0)
	                    done = 1;
	               pthread_mutex_unlock(&remQMutex);   
	          }
	          //else push back not done
	     }	
     }
     
     return NULL;
}

void QueryRunManager::runWithIncr(){
     while (!done) {
          sleep(INCR);
          for (int  i = 0; i < _countThreads; ++i) 
               _threadData[i].setSwitchTaskOn();
     }	
}

void QueryRunManager::runNoIncr(){
     while (!done) {
     }	
}

void QueryRunManager::run(){
	pthread_t* threads = new pthread_t[_countThreads];

	//launch threads
     for (int  i = 0; i < _countThreads; ++i)
		pthread_create(&threads[i], NULL, queryThreadTask, (void*) &_threadData[i]);
		
     if (_withIncr) 
          runWithIncr();
          
     else
          runNoIncr();
     
     //join the other threads 
     for (int  i = 0; i < _countThreads; ++i)
		pthread_join(threads[i], NULL);
		
	cout<<"all joined"<<endl;
}

void QueryRunManager::stop(){
}


