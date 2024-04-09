#ifndef DATA_HPP
#define DATA_HPP

const int X = 240;

#include <vector>

/**
 * @brief Represents a data point.
 */
class DataPoint {
private:
    float timestamp; /**< The timestamp of the data point. */
    int c; /**< The value of c. */
    float* data; /**< The data array. */

public:
    /**
     * @brief Constructs a DataPoint object.
     * @param timestamp The timestamp of the data point.
     * @param c The value of c.
     * @param data The data array.
     */
    DataPoint(float timestamp, int c, float* data);

    /**
     * @brief Gets the timestamp of the data point.
     * @return The timestamp.
     */
    float Get_timestamp() const;

    /**
     * @brief Gets the value of c.
     * @return The value of c.
     */
    int Get_c() const;

    /**
     * @brief Gets the data array.
     * @return The data array.
     */
    float* Get_data() const;

    /**
     * @brief Sets the timestamp of the data point.
     * @param timestamp The timestamp to set.
     */
    void Set_timestamp(float timestamp);

    /**
     * @brief Sets the value of c.
     * @param c The value of c to set.
     */
    void Set_c(int c);

    /**
     * @brief Sets the data array.
     * @param data The data array to set.
     */
    void Set_data(float* data);

};

/**
 * @brief Represents a database of data points.
 */
class DataBase {
private:
    std::vector<DataPoint> data_points; /**< The vector of data points. */

public:
    /**
     * @brief Constructs a DataBase object.
     * @param data_points The vector of data points.
     */
    DataBase(std::vector<DataPoint> data_points);

    /**
     * @brief Gets the vector of data points.
     * @return The vector of data points.
     */
    std::vector<DataPoint> Get_data_points() const;

    /**
     * @brief Sets the vector of data points.
     * @param data_points The vector of data points to set.
     */
    void Set_data_points(std::vector<DataPoint> data_points);

    /**
     * @brief Adds a data point to the database.
     * @param data_point The data point to add.
     */
    void Add_data_point(DataPoint data_point);

    /**
     * @brief Gets a data point from the database at the specified index.
     * @param index The index of the data point to get.
     * @return The data point at the specified index.
     */
    DataPoint Get_data_point(int index);

    /**
     * @brief Gets the size of the database.
     * @return The size of the database.
     */
    int Get_size();

    /**
     * @brief Reads data from a file and populates the database.
     * @param filename The name of the file to read data from.
     */
    void Read_data_from_file(const char* filename);

    /**
     * @brief Destroys the DataBase object.
     */
    ~DataBase();
};

#endif // DATA_HPP
