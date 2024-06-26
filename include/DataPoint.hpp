#ifndef _DATAPOINT_HPP
#define _DATAPOINT_HPP

#include <fstream>
#include <vector>
#include <bitset>
#include "globals.hpp"

/**
 * @brief Represents a data point.
 */
class DataPoint 
{

private:
     /**< The timestamp of the data point. */
     float _timestamp; 
     /**< The value of category. */
     uint32_t _c; 
     /**< The poitn data. */
     float* _data;
     /**< SAX representation*/
     uint64_t*  sax ;
     float* _paa;
     
public:    
    /**
     * @brief Constructs a DataPoint object from a binary input stream
     * @param ifs The inoput stream
     */
    DataPoint(std::ifstream& ifs);
    
    DataPoint(const DataPoint& other);

    /**
     * @brief Gets the timestamp of the data point.
     * @return The timestamp.
     */
    float GetTS() const;

    /**
     * @brief Gets the value of c.
     * @return The value of c.
     */
    int GetC() const;

    /**
     * @brief Gets the data array.
     * @return The data array.
     */
    float* GetData() const;
    
    uint64_t*  Getsax() const ;

    void Setsax(uint64_t*  Sax)  ;
    
    inline float* GetPaa() const {return _paa;}
     
    inline void SetPaa(float* paa) {_paa = paa;}
    
    ~DataPoint();
};

#endif

