#ifndef _QUERYSET_HPP
#define _QUERYSET_HPP

#include <numeric>
#include <string>

class Query;
class DataBase;

/**
 * @brief Represents a query set.
 */
class QuerySet {
public:
     int* _queryIndices;
private:
      /**< The queries*/
      Query** _queries;
      /**< The query count*/
      uint32_t _queryCount;
      /**< The database*/
      const DataBase& _db;

public:
     /**
     * @brief Constructs a QuerySet object by reading from a file
     * @param filename The file name
     */
     QuerySet(const char* filename, const DataBase& db, int queryType);
     
     /**
     * @brief Gets the query count of the database.
     * @return The query count of the database.
     */
     int GetQueryCount();
     
     /**
     * @brief Gets the queries
     * @return The queries
     */
     Query** GetQueries() const;
     
     /**
     * @brief Writes query results in the output file.
     */
     void WriteOutput(const char* filename);
          
     /**
     * @brief Destroys the DataBase object.
     */
     ~QuerySet();
     
     /**
     * @brief Computes SAX representations for queries
     */
     void ComputeSAXStuff();
};


#endif 
