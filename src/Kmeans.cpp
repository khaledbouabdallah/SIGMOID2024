//#pragma once

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

// Todo std::array to float*
// Todo handle Datapoint class
// Todo remove templates 
// TODO follow Kmeans hpp signature



// Todo : Switch from std::array to float*

std::vector<float*> random_plusplus(const std::vector<float*>& data, uint32_t k, uint64_t seed) {
	assert(k > 0);
	assert(data.size() > 0);
	using input_size_t = typename std::array<float, 100>::size_type;
	std::vector<float*> means;
	// Using a very simple PRBS generator, parameters selected according to
	// https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use
	std::linear_congruential_engine<uint64_t, 6364136223846793005, 1442695040888963407, UINT64_MAX> rand_engine(seed);

	// Select first mean at random from the set
	{
		std::uniform_int_distribution<input_size_t> uniform_generator(0, data.size() - 1);
		means.push_back(data[uniform_generator(rand_engine)]);
	}

	std::cout << "random_plusplus here1" << std::endl;

	for (uint32_t count = 1; count < k; ++count) {
		// Calculate the distance to the closest mean for each data point
		auto distances = closest_distance(means, data);
		std::cout << "random_plusplus here2 " << count << std::endl;
		// Pick a random point weighted by the distance from existing means
		// TODO: This might convert floating point weights to ints, distorting the distribution for small weights
        #if !defined(_MSC_VER) || _MSC_VER >= 1900
        		std::discrete_distribution<input_size_t> generator(distances.begin(), distances.end());
        #else  // MSVC++ older than 14.0
        		input_size_t i = 0;
        		std::discrete_distribution<input_size_t> generator(distances.size(), 0.0, 0.0, [&distances, &i](double) { return distances[i++]; });
        #endif
        		means.push_back(data[generator(rand_engine)]);

		//distances.clear();
	}
	
	return means;
}


/*
Calculate the square of the distance between two points.
*/
float distance_squared(float* point_a, float* point_b) {
	float d_squared = 0;

	for (int i = 0; i < DATA_SIZE; ++i) {
		d_squared += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
	}
	 return d_squared;
}


float distance(float* point_a, float* point_b) {
	return std::sqrt(distance_squared(point_a, point_b));
}


/*
Calculate the smallest distance between each of the data points and any of the input means.
*/
std::vector<float> closest_distance(
	const std::vector<float*>& means, const std::vector<float*>& data) {
	std::vector<float> distances;
	distances.reserve(data.size());
	for (auto& d : data) {
		float closest = distance_squared(d, means[0]);
		for (auto& m : means) {
			float distance = distance_squared(d, m);
			if (distance < closest)
				closest = distance;
		}
		distances.push_back(closest);
	}
	return distances;
}



uint32_t closest_mean( float* point, std::vector<float*> means) {
	assert(!means.empty());
	float smallest_distance = distance_squared(point, means[0]);
	uint32_t index = 0;
	float distance;
	for (uint32_t i = 1; i < means.size(); ++i) {
		distance = distance_squared(point, means[i]);
		if (distance < smallest_distance) {
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
std::vector<uint32_t> calculate_clusters(
	const std::vector<float*>& data, const std::vector<float*>& means) {
	std::vector<uint32_t> clusters;
	for (auto& point : data) {
		clusters.push_back(closest_mean(point, means));
	}
	return clusters;
}


// todo
/*
Calculate means based on data points and their cluster assignments.
*/
std::vector<float*> calculate_means(const std::vector<float*>& data,
	const std::vector<uint32_t>& clusters,
	const std::vector<float*>& old_means,
	uint32_t k) {
	std::vector<float*> means(k);

	for (size_t i = 0; i < k; ++i) {
		means[i] = new float[DATA_SIZE];
		for (size_t j = 0; j < DATA_SIZE; ++j) {
			means[i][j] = 0;
		}
	}

	std::vector<float> count(k, float());
	for (size_t i = 0; i < std::min(clusters.size(), data.size()); ++i) {
		auto& mean = means[clusters[i]];
		count[clusters[i]] += 1;
		for (size_t j = 0; j < DATA_SIZE; ++j) {
			mean[j] += data[i][j];
		}
	}
	for (size_t i = 0; i < k; ++i) {
		if (count[i] == 0) {
			means[i] = old_means[i];
		} else {
			for (size_t j = 0; j < DATA_SIZE; ++j) {
				means[i][j] /= count[i];
			}
		}
	}
	return means;
}


// todo
std::vector<float> deltas(
	const std::vector<float*>& old_means, const std::vector<float*>& means)
{
	std::vector<float> distances;
	distances.reserve(means.size());
	assert(old_means.size() == means.size());
	for (size_t i = 0; i < means.size(); ++i) {
		distances.push_back(distance(means[i], old_means[i]));
	}
	return distances;
}

float sum(const std::vector<float>& deltas) {
	float sum = 0;
	for (float d : deltas) {
		sum += d;
	}
	return sum;
}

bool deltas_below_limit(const std::vector<float>& deltas, float min_delta) {
	for (float d : deltas) {
		if (d > min_delta) {
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
std::tuple<std::vector<float*>, std::vector<uint32_t>> kmeans_lloyd(
	const std::vector<float*>& data, const clustering_parameters& parameters) {
	assert(parameters.get_k() > 0); // k must be greater than zero
	assert(data.size() >= parameters.get_k()); // there must be at least k data points
	std::random_device rand_device;
	uint64_t seed = parameters.has_random_seed() ? parameters.get_random_seed() : rand_device();

	std::cout << "min delta" << parameters.get_min_delta() << std::endl;
	std::cout << "max iteration" << parameters.get_max_iteration() << std::endl;
	std::cout << "has min delta" << parameters.has_min_delta() << std::endl;
	std::cout << "min delta" << parameters.get_min_delta() << std::endl;
	std::cout << "has random seed" << parameters.has_random_seed() << std::endl;
	std::cout << "random seed" << parameters.get_random_seed() << std::endl;

	std::vector<float*> means = random_plusplus(data, parameters.get_k(), seed);

	std::cout << "kmeans++ init finished" << means.size() << std::endl;	

	std::vector<float*> old_means;
	std::vector<float*> old_old_means;
	std::vector<uint32_t> clusters;



	float min_delta = parameters.has_min_delta() ? parameters.get_min_delta() : 0.0000001;

	return std::tuple<std::vector<float*>, std::vector<uint32_t>>(means, clusters);

	// Calculate new means until convergence is reached or we hit the maximum iteration count
	uint64_t count = 0;
	do {
		clusters = calculate_clusters(data, means);
		old_old_means = old_means;
		old_means = means;
		means = calculate_means(data, clusters, old_means, parameters.get_k());	
		++count;

		std::cout << "Iteration " << count << std::endl;
		std::cout << "delta = " << sum(deltas(old_means, means)) << std::endl;
		std::cout << "====================" << std::endl;

		
	} while (sum(deltas(old_means, means)) > min_delta
		&& !(parameters.has_max_iteration() && count == parameters.get_max_iteration()));
		

	return std::tuple<std::vector<float*>, std::vector<uint32_t>>(means, clusters);
}