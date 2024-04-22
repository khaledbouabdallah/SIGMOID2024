#ifndef _DATABASE_HPP
#define _DATABASE_HPP

#include "DataPoint.hpp"
#include "globals.hpp"
#include <vector>

using namespace std;

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

      //stats
      float* _means;
      float* _stds;
      float _globalMean;
      float _globalStd;
      
      //categories
      int* _catstart;
      int* _catend;
      int _countCategories;
      int* _categories;
  
public:    
      //bp distances, sqaured, with scale factor !
      float _saxDistances[256][256];
      
public:
     //sax
     vector<float> _breakpoints;
     
     float _scaleFactor;

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
     * @brief Creates data for categories range
     */
     void ProcessCategories();
     
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

     void NormalizeData_Axis1(); // columns

     void NormalizeData_Axis0(); // rows

     void NormalizeData_Global();

     inline float GetGlobalMean() const {return _globalMean;}
     
     inline float GetGlobalStd() const {return _globalStd;}
     
     float GetSAXDistance(uint64_t* sax1, uint64_t* sax2) const;

private:

     void ComputeMeans();

     void ComputeStds();
     
     void ComputeGlobalMean();
     
     void ComputeGlobalStd();
     
     int GetIndCat(int cat) const;
     
     void ComputeSaxDistances();
     
};

#endif 
