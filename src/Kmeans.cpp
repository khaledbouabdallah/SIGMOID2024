// #pragma once

#include <iostream>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>
#include <Kmeans.hpp>
#include <globals.hpp>
#include <chrono>
#include <Utils.hpp>
#include <string>
#include "SortUtils.hpp"

// Todo std::array to float*
// Todo handle Datapoint class
// Todo remove templates
// TODO follow Kmeans hpp signature

// Todo : Switch from std::array to float*

void Cluster::MakeAndSortIndices(DataBase& db) {
     //first, make indices arrays
     _countPoints = _points.size();
     _sortedIndByCatAndTS = new int[_countPoints];
     _sortedIndByTS = new int[_countPoints];
     for (int i = 0; i<_countPoints; ++i)
          _sortedIndByCatAndTS[i] = _sortedIndByTS[i] = _points[i];
          
     //then sort
     SortIndices(_sortedIndByCatAndTS, db.GetPoints(), _countPoints, CompareByCatAndTS);
     SortIndices(_sortedIndByTS, db.GetPoints(), _countPoints, CompareByTS);
}

void Cluster::getSearchRange(const DataBase& db, int cat, int tsl, int tsr, int*&indices, int& start, int&end) {
     int first = 0;
     int last = _countPoints;
     start = 0;
     end = _countPoints;
     if (cat != -1) {
          indices = _sortedIndByCatAndTS;
          first = GetFirstPositionCategory(cat, indices, db.GetPoints(),0,_countPoints);
          if (first >= _countPoints || db.GetPoint(first).GetC() != cat) {
               start = end = -1; //no result here
               return;
          }  
          last = GetLastPositionCategory(cat, indices, db.GetPoints(),0,_countPoints)+1; //this should be valid, else there is a bug !!! : p
     }
     else indices = _sortedIndByTS;
     if (tsl != -1) {
          start = GetFirstPositionGETS(tsl, indices, db.GetPoints(), first, last);
          if (start >= _countPoints) { //no result here
               start = end = -1;
               return;
          }
    }
    if (tsr != -1) {
          end = GetLastPositionLETS(tsr, indices, db.GetPoints(), start, last);
          if (end < 0) { //no result here
               start = end = -1;
               return;
          }
          end++;
    }     
}

std::vector<float *> random_simple(const std::vector<DataPoint> &data, uint32_t k, uint64_t seed)
{
	assert(k > 0);
	assert(data.size() > 0);
	std::vector<float *> means;
	std::mt19937 rand_engine(seed);
	std::uniform_int_distribution<size_t> uniform_generator(0, data.size() - 1);
	for (uint32_t i = 0; i < k; ++i)
	{
		means.push_back(data[uniform_generator(rand_engine)].GetData());
	}
	return means;
}

std::vector<float *> random_plusplus(const std::vector<DataPoint> &data, uint32_t k, uint64_t seed, const int verbose_level)
{
	assert(k > 0);
	assert(data.size() > 0);
	using input_size_t = typename std::array<float, 100>::size_type;
	std::vector<float *> means;
	// Using a very simple PRBS generator, parameters selected according to
	// https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
	std::linear_congruential_engine<uint64_t, 6364136223846793005, 1442695040888963407, UINT64_MAX> rand_engine(seed);

	// Select first mean at random from the set
	{
		std::uniform_int_distribution<input_size_t> uniform_generator(0, data.size() - 1);
		means.push_back(data[uniform_generator(rand_engine)].GetData());
	}

	float *distances = new float[data.size()];
	size_t num = data.size();
	;
	for (uint32_t count = 1; count < k; ++count)
	{
		// Calculate the distance to the closest mean for each data point
		auto start = std::chrono::high_resolution_clock::now();
		closest_distance(means, data, distances);
		auto end = std::chrono::high_resolution_clock::now();
		// Calculate the duration
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (verbose_level > 1)
		{
			std::cout << count << " closest_distance Execution time: " << duration.count() / 1000 << " ms" << std::endl;
		}
		start = std::chrono::high_resolution_clock::now();
// Pick a random point weighted by the distance from existing means
// This might convert floating point weights to ints, distorting the distribution for small weights
#if !defined(_MSC_VER) || _MSC_VER >= 1900
		std::discrete_distribution<input_size_t> generator(distances, &distances[num - 1]);
		// std::discrete_distribution<input_size_t> generator(distances.begin(), distances.end());
#else // MSVC++ older than 14.0
		input_size_t i = 0;
		std::discrete_distribution<input_size_t> generator(distances.size(), 0.0, 0.0, [&distances, &i](double)
														   { return distances[i++]; });
#endif
		means.push_back(data[generator(rand_engine)].GetData());

		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		if (verbose_level > 1)
		{
			std::cout << count << " random_plusplus Execution time: " << duration.count() / 1000 << " ms" << std::endl;
			std::cout << "====================" << std::endl;
		}
	}

	return means;
}

/*
Calculate the square of the distance between two points.
*/
float distance_squared(float *point_a, float *point_b)
{
	float d_squared = 0;
	for (int i = 0; i < DATA_SIZE; ++i)
	{
		d_squared += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
	}
	return d_squared;
}

float distance(float *point_a, float *point_b)
{
	return std::sqrt(distance_squared(point_a, point_b));
}

// /*
// Calculate the smallest distance between each of the data points and any of the input means.
// */
// std::vector<float> closest_distance(
// 	const std::vector<float*>& means, const std::vector<DataPoint>& data) {
// 	std::vector<float> distances;
// 	distances.reserve(data.size());
// 	for (auto& d : data) {
// 		float closest = distance_squared(d.GetData(), means[0]);
// 		for (auto& m : means) {
// 			float distance = distance_squared(d.GetData(), m);
// 			if (distance < closest)
// 				closest = distance;
// 		}
// 		distances.push_back(closest);
// 	}
// 	return distances;
// }

/*
Calculate the smallest distance between each of the data points and any of the input means.
*/
void closest_distance(
	const std::vector<float *> &means, const std::vector<DataPoint> &data, float *distances)
{

#pragma omp parallel for
	for (int i = 0; i < data.size(); ++i)
	{
		float closest = distance_squared(data[i].GetData(), means[0]);
		for (auto &m : means)
		{
			float distance = distance_squared(data[i].GetData(), m);
			if (distance < closest)
				closest = distance;
		}
		distances[i] = closest;
	}
}

uint32_t closest_mean(float *point, std::vector<float *> means)
{
	assert(!means.empty());
	float smallest_distance = distance_squared(point, means[0]);
	uint32_t index = 0;
	float distance;
	for (uint32_t i = 1; i < means.size(); ++i)
	{
		distance = distance_squared(point, means[i]);
		if (distance < smallest_distance)
		{
			smallest_distance = distance;
			index = i;
		}
	}
	return index;
}

// todo
/*
Calculate the index of the mean each data point is closest to (euclidean distance).
*/


	struct ThreadArgs
	{
		const std::vector<DataPoint> *data;
		const std::vector<float *> *means;
		std::vector<uint32_t> *clusters;
		size_t start_index;
		size_t end_index;
	};

	void *thread_function(void *arg)
	{
		ThreadArgs *args = static_cast<ThreadArgs *>(arg);
		for (size_t i = args->start_index; i < args->end_index; ++i)
		{
			(*args->clusters)[i] = closest_mean((*args->data)[i].GetData(), *args->means);
		}
		return nullptr;
	}
	std::vector<uint32_t> calculate_clusters(
		const std::vector<DataPoint> &data, const std::vector<float *> &means)
	{
		std::vector<uint32_t> clusters(data.size());

		// Define the number of threads (adjust this as needed)
		const int num_threads = 16;
		pthread_t threads[num_threads];
		ThreadArgs thread_args[num_threads];

		// Calculate the number of data points per thread
		size_t points_per_thread = data.size() / num_threads;

		// Create and start the threads
		for (int i = 0; i < num_threads; ++i)
		{
			thread_args[i].data = &data;
			thread_args[i].means = &means;
			thread_args[i].clusters = &clusters;
			thread_args[i].start_index = i * points_per_thread;
			thread_args[i].end_index = (i == num_threads - 1) ? data.size() : (i + 1) * points_per_thread;

			pthread_create(&threads[i], nullptr, thread_function, &thread_args[i]);
		}

		// Wait for all threads to finish
		for (int i = 0; i < num_threads; ++i)
		{
			pthread_join(threads[i], nullptr);
		}

		return clusters;
	}


// std::vector<uint32_t> calculate_clusters(
// 	const std::vector<DataPoint>& data, const std::vector<float*>& means) {
// 	std::vector<uint32_t> clusters;
// 	for (auto& point : data) {
// 		clusters.push_back(closest_mean(point.GetData(), means));
// 	}
// 	return clusters;
// }

// todo
/*
Calculate means based on data points and their cluster assignments.
*/
std::vector<float *> calculate_means(const std::vector<DataPoint> &data,
									 const std::vector<uint32_t> &clusters,
									 const std::vector<float *> &old_means,
									 uint32_t k)
{
	std::vector<float *> means(k);

	for (size_t i = 0; i < k; ++i)
	{
		means[i] = new float[DATA_SIZE];
		for (size_t j = 0; j < DATA_SIZE; ++j)
		{
			means[i][j] = 0;
		}
	}

	std::vector<float> count(k, float());
	for (size_t i = 0; i < std::min(clusters.size(), data.size()); ++i)
	{
		auto &mean = means[clusters[i]];
		count[clusters[i]] += 1;
		for (size_t j = 0; j < DATA_SIZE; ++j)
		{
			mean[j] += data[i].GetData()[j];
		}
	}
	for (size_t i = 0; i < k; ++i)
	{
		if (count[i] == 0)
		{
			means[i] = old_means[i];
		}
		else
		{
			for (size_t j = 0; j < DATA_SIZE; ++j)
			{
				means[i][j] /= count[i];
			}
		}
	}
	return means;
}

// todo
std::vector<float> deltas(
	const std::vector<float *> &old_means, const std::vector<float *> &means)
{
	std::vector<float> distances;
	distances.reserve(means.size());
	assert(old_means.size() == means.size());
	for (size_t i = 0; i < means.size(); ++i)
	{
		distances.push_back(distance(means[i], old_means[i]));
	}
	return distances;
}

float sum(const std::vector<float> &deltas)
{
	float sum = 0;
	for (float d : deltas)
	{
		sum += d;
	}
	return sum;
}

bool deltas_below_limit(const std::vector<float> &deltas, float min_delta)
{
	for (float d : deltas)
	{
		if (d > min_delta)
		{
			return false;
		}
	}
	return true;
}

/*
Implementation of k-means generic across the data type and the dimension of each data item. Expects
the data to be a vector of fixed-size arrays. Generic parameters are the type of the base data (T)
and the dimensionality of each data point (N). All points must have the same dimensionality.

e.g. points of the form (X, Y, Z) would be N = 3.

Takes a `clustering_parameters` struct for algorithm configuration. See the comments for the
`clustering_parameters` struct for more information about the configuration values and how they
affect the algorithm.

Returns a std::tuple containing:
  0: A vector holding the means for each cluster from 0 to k-1.
  1: A vector containing the cluster number (0 to k-1) for each corresponding element of the input
	 data vector.

Implementation details:
This implementation of k-means uses [Lloyd's Algorithm](https://en.wikipedia.org/wiki/Lloyd%27s_algorithm)
with the [kmeans++](https://en.wikipedia.org/wiki/K-means%2B%2B)
used for initializing the means.

*/
// std::tuple<std::vector<float*>, std::vector<uint32_t>>
// const clustering_parameters& parameters)
void Kmeans::fit(const std::vector<DataPoint> &data, std::string initialization)
{

	std::random_device rand_device;
	uint64_t seed = _has_random_seed ? _random_seed : rand_device();

	if (_verbose_level > 0)
	{
		std::cout << "Starting Kmeans++ initialization" << std::endl;
	}

	auto start_glob = std::chrono::high_resolution_clock::now();

	auto start = std::chrono::high_resolution_clock::now();

	std::vector<float *> means;
	if (initialization == "kmeans++")
	{
		means = random_plusplus(data, _k, seed, _verbose_level);
	}
	else
	{
		means = random_simple(data, _k, seed);
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	// here

	if (_verbose_level > 0)
	{
		std::cout << "kmeans " << initialization << " init finished with k= " << _k << " time: " << duration.count() / 1000 << " ms" << std::endl;
	}

	std::vector<float *> old_means;
	// std::vector<float*> old_old_means;
	std::vector<uint32_t> clusters;
	float min_delta = _has_min_delta ? _min_delta : 0.0000001;
	float delta = 0.0;

	start = std::chrono::high_resolution_clock::now();

	// Calculate new means until convergence is reached or we hit the maximum iteration count

	uint64_t count = 0;
	do
	{
		if (_verbose_level > 1)
		{
			std::cout << "Kmeans Iteration " << count << std::endl;
		}
		auto start1 = std::chrono::high_resolution_clock::now();
		clusters = calculate_clusters(data, means);
		auto end1 = std::chrono::high_resolution_clock::now();
		// old_old_means = old_means;
		auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
		if (_verbose_level > 1)
		{
			std::cout << "calculate_clusters  finished with k= " << _k << " time: " << duration1.count() / 1000 << " ms" << std::endl;
		}
		old_means = means;
		start1 = std::chrono::high_resolution_clock::now();
		means = calculate_means(data, clusters, old_means, _k);
		end1 = std::chrono::high_resolution_clock::now();
		duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
		if (_verbose_level > 1)
		{
			std::cout << "calculate_means finished with k= " << _k << " time: " << duration1.count() / 1000 << " ms" << std::endl;
		}
		++count;

		delta = sum(deltas(old_means, means)) / _k;

		if (_verbose_level > 1)
		{
			std::cout << "delta = " << delta << std::endl;
			std::cout << "====================" << std::endl;
		}

	} while (delta > min_delta && !(_has_max_iteration && count == _max_iteration));

	clusters = calculate_clusters(data, means);

	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	if (_verbose_level > 0)
	{
		std::cout << "kmeans iter part finished in: " << duration.count() / 1000 << " ms ---";
		std::cout << " in " << count << " iteration" << std::endl;
	}

	//  initialize cluster
	// Bug!: double free detected in tcache 2
	for (int i = 0; i < _k; ++i)
	{
		// initialize cluster
		Cluster *c = new Cluster(i);
		c->SetCentroid(means[i]);
		_clusters.push_back(c);
	}

	for (int j = 0; j < clusters.size(); ++j)
	{
		for (int i = 0; i < _k; ++i)
		{
			if (clusters[j] == i)
			{
				_clusters[i]->AddPoint(j);
			}
		}
	}

	auto end_glob = std::chrono::high_resolution_clock::now();
	auto duration_glob = std::chrono::duration_cast<std::chrono::microseconds>(end_glob - start_glob);
	if (_verbose_level > 0)
	{
		std::cout << "kmeans finished in total in: " << duration_glob.count() / 1000 << " ms" << std::endl;
	}

	// // free memory of old means, means and clusters
	// for (auto& m : old_means) {
	// 	delete[] m;
	// }
	// for (auto& m : means) {
	// 	delete[] m;
	// }
}

std::vector<Cluster *> Kmeans::getClusters(float *point, int k)
{

	std::vector<Cluster *> clusters_to_return;

	// calculate the distance between the point and the centroids of the clusters
	std::vector<float> distances = std::vector<float>(_k);

	for (int i = 0; i < _k; ++i)
	{
		distances[i] = distance_squared(point, _clusters[i]->GetCentroid());
	}

	// find the k closest clusters
	std::vector<int> indices = findKMinIndices(distances, k);

	// todo keep track of the classes and timestamps max, min

	// here

	// return the clusters
	for (int i = 0; i < k; ++i)
	{
		clusters_to_return.push_back(_clusters[indices[i]]);
	}

	return clusters_to_return;
}

Cluster::~Cluster()
{
	delete[] _centroid;
}

Kmeans::~Kmeans() {}
