#include "../include/QueryRunManager.hpp"

#include <unistd.h>
#include <pthread.h>
#include "../include/QueryThreadData.hpp"
#include "../include/Query.hpp"
#include "../include/globals.hpp"
#include <iostream>
#include "../include/QueryQueue.hpp"
#include <unistd.h> 

volatile int remainingQueries;
pthread_mutex_t remQMutex;

QueryRunManager::QueryRunManager(Query** queries, int* queryIndices, int countQueries, int countThreads, int withIncr, int qassignType):
	_queryQ(NULL), _queries(queries), _countQueries(countQueries), _countThreads(countThreads), _withIncr(withIncr), _qassignType(qassignType)
{	
     //increment is not compatible with query queue by array!!
     //should be checked
     	
	//cout<<"assign type: "<<qassignType<<endl;
     
	_threadData = new QueryThreadData[_countThreads];
	remainingQueries = countQueries;
	
	if (qassignType > 0)
	     _queryQ = new QueryQueue(qassignType, queryIndices, _countQueries);
	
	for (int i = 0; i < _countThreads; ++i) 
		_threadData[i].Init(_qassignType, _queryQ, i, _queries, queryIndices, _countQueries, _countThreads);
}

QueryRunManager::~QueryRunManager() {}

void *queryThreadTask(void *arg)
{
	QueryThreadData* data = (QueryThreadData*) arg;
	
	if (data->_qassignType == 0) { //pack of queries per thread
	     while (!done) {
		     data->setSwitchTaskOff();
		     Query* crtQuery = data->getNextQuery();
		     if (!crtQuery) break; //no more queries to run for this thread
		     crtQuery->run(data->_switchTask);
		     if (crtQuery->IsFinished()){
                    pthread_mutex_lock(&remQMutex);
	               remainingQueries--;
	               //cout<<remainingQueries<<endl;
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
		     //cout<<"done running query "<<indice<<"is finished: "<<crtQuery->IsFinished()<<" remaining: "<<remainingQueries<<endl;
		     if (crtQuery->IsFinished()){
                    pthread_mutex_lock(&remQMutex);
	               remainingQueries--;
	               if (remainingQueries == 0)
	                    done = 1;
	               pthread_mutex_unlock(&remQMutex);   
	          } else 
	               data->_queryQ->PushBack(indice);
	     }	
     }
     
     return NULL;
}

void QueryRunManager::runWithIncr(){
     while (!done) {
          usleep(INCR);
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
		
	//cout<<"all joined"<<endl;
	//cout<<remainingQueries<<endl;
}

void QueryRunManager::stop(){
}


