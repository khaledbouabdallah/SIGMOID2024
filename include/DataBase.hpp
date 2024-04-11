#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include "DataPoint.hpp"
#include "globals.hpp"
#include <vector>

/**
 * @brief Represents a database of data points.
 */
class DataBase {
private:
      /**< The vector of data points. */
      std::vector<DataPoint> _data_points;
      
      //indices of points sorted by category then TS
      int* _sortedIndByCatAndTS;
      
      //indices of point sorted solely by TS
      int* _sortedIndByTS;
      
      /**< The number of points. */
      int _countPoints;

      float* _means;

      float* _stds;

public:
     /**
     * @brief Constructs a DataBase object.
     * @param data_points The vector of data points.
     */
     DataBase(const char* filename);
      /**
     * @brief Destroys the DataBase object.
     */
    ~DataBase();
    
  
     /**
     * @brief Gets the vector of data points.
     * @return The vector of data points.
     */
     std::vector<DataPoint>& GetPoints();
     
     /**
     * @brief Gets a data point from the database at the specified index.
     * @param index The index of the data point to get.
     * @return The data point at the specified index. 
     */
     DataPoint& GetPoint(int index);
     /**
     * @brief Gets the size of the database.
     * @return The size of the database.
     */
     int GetSize();
     
     /**
     * @brief Creates indices array by sorting on category and timestamp
     */
     void SortByCatAndTS();
     
      /**
     * @brief Provides indices array and range (start and end) for the answers of a query
     * @param cat The query category
     * @param lts The lower ts range value, -1 if this does not apply
     * @param rts The higher ts range value, -1 if this does not apply
     * @param start Output, the first indice in the range
     * @param end Output, the last indice in the range
     */  
     int* GetByCatAndTS(int cat, int lts, int rts, int&start, int& end);

private:
     
     void SiftByCatAndTS(int i, int n);
          
     int isGreaterByCatAndTS(int i, int j);

     void ComputeMeans();

     void ComputeStds();

     void NormalizeData();

};

#endif 
