#ifndef _QUERYRUNMANAGER_HPP
#define _QUERYRUNMANAGER_HPP

class QueryThreadData;
class Query;
class QueryQueue;

class QueryRunManager
{
private:
	Query** _queries;
	int _countQueries;
	int _countThreads;
	QueryThreadData* _threadData;
	int _withIncr;
	int _qassignType;
	QueryQueue* _queryQ;
public:
	QueryRunManager(Query** queries, int countQueries, int countthreads, int withIncr, int qassignType);
	~QueryRunManager();
	void run();
	void stop();
private:
     void runWithIncr();
     void runNoIncr();
};

#endif
