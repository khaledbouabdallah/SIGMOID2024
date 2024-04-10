#ifndef _DATAPOINT_HPP
#define _DATAPOINT_HPP

#include <fstream>

/**
 * @brief Represents a data point.
 */
class DataPoint 
{

private:
     /**< The timestamp of the data point. */
     float _timestamp; 
     /**< The value of category. */
     int _c; 
     /**< The poitn data. */
     float* _data; 
     
public:
    /**
     * @brief Constructs a DataPoint object.
     * @param timestamp The timestamp of the data point.
     * @param c The value of c.
     * @param data The data array.
     */
    DataPoint(float timestamp, int c, float* data);
    
    /**
     * @brief Constructs a DataPoint object from a binary input stream
     * @param ifs The inoput stream
     */
    DataPoint(std::ifstream& ifs);

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
};

#endif

