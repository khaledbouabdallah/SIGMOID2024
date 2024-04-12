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
      
      //indices of points sorted by normal order
      int* _sortedIndNormal;
      
      //indices of points sorted by category then TS
      int* _sortedIndByCatAndTS;
      
      //indices of point sorted solely by TS
      int* _sortedIndByTS;
      
      /**< The number of points. */
      int _countPoints;

      float* _means;

      float* _stds;
      
      //categories
      int* _catstart;
      int* _catend;
      int _countCategories;

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
     const DataPoint& GetPoint(int index) const;
     /**
     * @brief Gets the size of the database.
     * @return The size of the database.
     */
     int GetSize() const;
     
     /**
     * @brief Creates indices array by sorting on category and timestamp
     */
     void SortByCatAndTS();
     
       
     /**
     * @brief Creates indices array by sorting on timestamp
     */
     void SortByTS();
     
      /**
     * @brief Provides indices array and range (start and end) for the answers of a query
     * @param cat The query category
     * @param lts The lower ts range value, -1 if this does not apply
     * @param rts The higher ts range value, -1 if this does not apply
     * @param start Output, the first indice in the range
     * @param end Output, the last indice in the range
     */  
     
     int* GetNormalIndices() const;
     
     int* GetIndicesSortedByCatAndTS() const;
     
     int* GetIndicesSortedByTS() const;
     
     void GetCatRange(int cat, int& start, int& end) const;
     
     void GetTSRange(float lts, float rts, int& start, int& end) const;
     
     void GetCatAndTSRange(int cat, float lts, float rts, int& start, int& end) const;

     void NormalizeData();

private:
     
     void SiftIndices(int*, int i, int n, int (*funccomp)(const DataPoint&, const DataPoint&));
          
     static int CompareByCatAndTS(const DataPoint& p1, const DataPoint& p2);;
     
     int GetFirstPositionGE(float ts, int* indices, int start, int end) const;
     
     int GetLastPositionLE(float ts, int* indices, int start, int end) const;

     void ComputeMeans();

     void ComputeStds();


};

#endif 
