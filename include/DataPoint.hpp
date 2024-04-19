#ifndef _DATAPOINT_HPP
#define _DATAPOINT_HPP

#include <fstream>
#include <vector>
#include <bitset>

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
     std::bitset<nombres_de_bits >* sax ;
     
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
    
    std::bitset<nombres_de_bits >* DataPoint::Getsax() const ;

    void DataPoint::Setsax(std::bitset<nombres_de_bits >* Sax) const ;
    
    ~DataPoint();
};

#endif

