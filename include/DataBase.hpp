#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include "DataPoint.hpp"
#include <vector>

/**
 * @brief Represents a database of data points.
 */
class DataBase {
private:
      /**< The vector of data points. */
      std::vector<DataPoint> _data_points;
      
      //indices of points sorted by category then TS
      int* sortedIndByCatAndTS;
      
      //indices of point sorted solely by TS
      int* sortedIndByTS;
      
      int _countPoints;

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
     
     void SortByCatAndTS();

private:
     
     void SiftByCatAndTS(int i, int n);

};

#endif 
