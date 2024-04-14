#ifndef _QUERYRUNMANAGER_HPP
#define _QUERYRUNMANAGER_HPP

class QueryThreadData;
class Query;

class QueryRunManager
{
private:
	Query** _queries;
	int _countQueries;
	int _countThreads;
	QueryThreadData* _threadData;
public:
	QueryRunManager(Query** queries, int countQueries, int countthreads);
	~QueryRunManager();
	void run();
	void stop();
};

#endif
