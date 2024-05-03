#pragma once
#ifndef _KMEANS_H
#define _KMEANS_H

#include <vector>
#include "globals.hpp"
#include "DataPoint.hpp"
#include "DataBase.hpp"
#include <string>

// for testing
// class clustering_parameters {
// public:
// 	explicit clustering_parameters(uint32_t k) :
// 	_k(k),
// 	_has_max_iter(false), _max_iter(),
// 	_has_min_delta(false), _min_delta(),
// 	_has_rand_seed(false), _rand_seed()
// 	{}s

// 	void set_max_iteration(uint64_t max_iter)
// 	{
// 		_max_iter = max_iter;
// 		_has_max_iter = true;
// 	}

// 	void set_min_delta(float min_delta)
// 	{
// 		_min_delta = min_delta;
// 		_has_min_delta = true;
// 	}

// 	void set_random_seed(uint64_t rand_seed)
// 	{
// 		_rand_seed = rand_seed;
// 		_has_rand_seed = true;
// 	}

// 	bool has_max_iteration() const { return _has_max_iter; }
// 	bool has_min_delta() const { return _has_min_delta; }
// 	bool has_random_seed() const { return _has_rand_seed; }

// 	uint32_t get_k() const { return _k; };
// 	uint64_t get_max_iteration() const { return _max_iter; }
// 	float get_min_delta() const { return _min_delta; }
// 	uint64_t get_random_seed() const { return _rand_seed; }

// private:
// 	uint32_t _k;
// 	bool _has_max_iter;
// 	uint64_t _max_iter;
// 	bool _has_min_delta;
// 	float _min_delta;
// 	bool _has_rand_seed;
// 	uint64_t _rand_seed;
// };
//

float distance_squared(float *point_a, float *point_b);

float distance(float *point_a, float *point_b);

void closest_distance(const std::vector<float *> &means, const std::vector<DataPoint> &data, float *distances);
// std::vector<float> closest_distance(const std::vector<float*>& means, const std::vector<DataPoint>& data);

uint32_t closest_mean(float *point, std::vector<float *> means);

std::vector<uint32_t> calculate_clusters(
	const std::vector<float *> &data, const std::vector<float *> &means);

std::vector<float *> calculate_means(const std::vector<float *> &data,
									 const std::vector<uint32_t> &clusters,
									 const std::vector<float *> &old_means,
									 uint32_t k);

std::vector<float> deltas(
	const std::vector<float *> &old_means, const std::vector<float *> &means);

bool deltas_below_limit(const std::vector<float> &deltas, float min_delta);
//
// std::tuple<std::vector<float*>, std::vector<uint32_t>> kmeans_lloyd(
// 	const std::vector<float*>& data, const clustering_parameters& parameters);

class Cluster : public DataBase
{

private:
	std::vector<int> _points;
	float *_centroid;
	int _id;
	int _countPoints;
	//int *_categories;

	//indices of points sorted by category then TS
     int* _sortedIndByCatAndTS;
      
     //indices of point sorted solely by TS
     int* _sortedIndByTS;

public:
	inline Cluster(int id) : _id(id), _countPoints(0){};
	int GetId() { return _id; }
	void AddPoint(int index_point)
	{
		_points.push_back(index_point);
		_countPoints++;
	}
	void SetCentroid(float *centroid) { _centroid = centroid; }
	float *GetCentroid() { return _centroid; }
	int GetSize() { return _countPoints; }
	std::vector<int> GetPoints() { return _points; }
	int getPoint(int i) { return _points[i]; }
	~Cluster();
	
	//here we feed the category and the ts limits (may be -1 ! )
	//and we get as output a vector of indices to sort, as well as a range (start and end)
     void getSearchRange(DataBase& db, int cat, int tsl, int tlr, int*&indices, int& start, int&end);
     
     void MakeAndSortIndices(DataBase& db);
};

class Kmeans
{
private:
	int _k;
	std::vector<Cluster *> _clusters;

	int _max_iteration;
	bool _has_max_iteration;

	uint64_t _random_seed;
	bool _has_random_seed;

	float _min_delta;
	bool _has_min_delta;
	int _verbose_level;

public:
	inline Kmeans(int k) : _k(k) {}
	void fit(const std::vector<DataPoint> &data, std::string initialization);
	std::vector<Cluster *> getClusters(float *point, int k);

	int get_k() const { return _k; };
	uint64_t get_random_seed() const { return _random_seed; };
	float get_min_delta() const { return _min_delta; };
	bool has_random_seed() const { return _has_random_seed; };
	bool has_max_iteration() const { return _has_max_iteration; };
	uint64_t get_max_iteration() const { return _max_iteration; };
	void set_max_iteration(uint64_t max_iter)
	{
		_max_iteration = max_iter;
		_has_max_iteration = true;
	}
	void set_min_delta(float min_delta)
	{
		_min_delta = min_delta;
		_has_min_delta = true;
	}
	void set_random_seed(uint64_t rand_seed)
	{
		_random_seed = rand_seed;
		_has_random_seed = true;
	}
	bool has_min_delta() const { return _has_min_delta; };
	Cluster *getCluster(int i) { return _clusters[i]; }

	void set_verbose_level(int level) { _verbose_level = level; }

	~Kmeans();
};

#endif
