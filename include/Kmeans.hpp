#ifndef _KMEANS_H
#define _KMEANS_H


#include <vector>
#include "globals.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"

// for testing 

float distance_squared(float* point_a, float* point_b);

std::vector<float> closest_distance(const std::vector<float*>& means, const std::vector<float*>& data);
	

//

class Cluster: public DataBase {

    private:
        std::vector<DataPoint> _points;
        DataPoint _centroid;
        int _id;
        int _countPoints;
        int* _categories;
        // ?? =>
        int* _catstart;
        int* _catend;
        // timestamp begin and end ??

};



class Kmeans
{
private:

    int _k;
    std::vector<Cluster> _clusters;
    int _maxIter;
    float _tolerance;


public:

    inline Kmeans(int k, int maxIter, float tolerance) : _k(k), _maxIter(maxIter), _tolerance(tolerance) {}
    void fit(std::vector<DataPoint>& data);
    std::vector<Cluster> getClusters(float* point, int nprob);
    
    ~Kmeans();

};


template <typename T>
class clustering_parameters {
public:
	explicit clustering_parameters(uint32_t k) :
	_k(k),
	_has_max_iter(false), _max_iter(),
	_has_min_delta(false), _min_delta(),
	_has_rand_seed(false), _rand_seed()
	{}

	void set_max_iteration(uint64_t max_iter)
	{
		_max_iter = max_iter;
		_has_max_iter = true;
	}

	void set_min_delta(T min_delta)
	{
		_min_delta = min_delta;
		_has_min_delta = true;
	}

	void set_random_seed(uint64_t rand_seed)
	{
		_rand_seed = rand_seed;
		_has_rand_seed = true;
	}

	bool has_max_iteration() const { return _has_max_iter; }
	bool has_min_delta() const { return _has_min_delta; }
	bool has_random_seed() const { return _has_rand_seed; }

	uint32_t get_k() const { return _k; };
	uint64_t get_max_iteration() const { return _max_iter; }
	T get_min_delta() const { return _min_delta; }
	uint64_t get_random_seed() const { return _rand_seed; }

private:
	uint32_t _k;
	bool _has_max_iter;
	uint64_t _max_iter;
	bool _has_min_delta;
	T _min_delta;
	bool _has_rand_seed;
	uint64_t _rand_seed;
};
#endif