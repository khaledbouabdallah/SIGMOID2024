#ifndef DATA_HPP
#define DATA_HPP

#include <vector>
using std::vector;

class DataPoint {
private:
    float timestamp;
    int c;
    float* data;

public:
    DataPoint(float timestamp, int c, float* data);
    float Get_timestamp() const;
    int Get_c() const;
    float* Get_data() const;
    void Set_timestamp(float timestamp);
    void Set_c(int c);
    void Set_data(float* data);
};

/**
 * @brief The `DataBase` class represents a collection of data points.
 * 
 * This class provides methods to manipulate and access the data points stored in the database.
 */
class DataBase {
private:
    vector<DataPoint> data_points; /**< The vector to store the data points. */

public:
    /**
     * @brief Constructs a new `DataBase` object with the given data points.
     * 
     * @param data_points The initial data points to be stored in the database.
     */
    DataBase(vector<DataPoint> data_points);

    DataBase();

    /**
     * @brief Returns the vector of data points stored in the database.
     * 
     * @return The vector of data points.
     */
    vector<DataPoint> Get_data_points() const;

    /**
     * @brief Sets the data points in the database to the given vector.
     * 
     * @param data_points The vector of data points to set.
     */
    void Set_data_points(vector<DataPoint> data_points);

    /**
     * @brief Adds a new data point to the database.
     * 
     * @param data_point The data point to add.
     */
    void Add_data_point(DataPoint data_point);

    /**
     * @brief Removes the data point at the specified index from the database.
     * 
     * @param index The index of the data point to remove.
     */
    void Remove_data_point(int index);

    /**
     * @brief Updates the data point at the specified index with the given data point.
     * 
     * @param index The index of the data point to update.
     * @param data_point The new data point to update with.
     */
    void Update_data_point(int index, DataPoint data_point);

    /**
     * @brief Returns the data point at the specified index.
     * 
     * @param index The index of the data point to retrieve.
     * @return The data point at the specified index.
     */
    DataPoint Get_data_point(int index);

    /**
     * @brief Returns the number of data points stored in the database.
     * 
     * @return The number of data points.
     */
    int Get_size();

    /**
     * @brief Clears all the data points from the database.
     */
    void Clear();

    /**
     * @brief Destroys the `DataBase` object and frees any allocated resources.
     */
    ~DataBase();
};

#endif // DATA_HPP
