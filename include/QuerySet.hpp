#ifndef _QUERYSET_HPP
#define _QUERYSET_HPP

#include <numeric>
#include <string>

class Query;

/**
 * @brief Represents a query set.
 */
class QuerySet {
private:
      /**< The queries*/
      Query** _queries;
      /**< The query count*/
      uint32_t _queryCount;

public:
     /**
     * @brief Constructs a QuerySet object by reading from a file
     * @param filename The file name
     */
     QuerySet(const char* filename);
     /**
     * @brief Gets the query count of the database.
     * @return The query count of the database.
     */
     int GetQueryCount();
     /**
     * @brief Destroys the DataBase object.
     */
    ~QuerySet();
};

#endif 
