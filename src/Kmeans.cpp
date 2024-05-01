//#pragma once

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

	for (uint32_t count = 1; count < k; ++count) {
		// Calculate the distance to the closest mean for each data point
		auto distances = closest_distance(means, data);
		// Pick a random point weighted by the distance from existing means
		// TODO: This might convert floating point weights to ints, distorting the distribution for small weights
        #if !defined(_MSC_VER) || _MSC_VER >= 1900
        		std::discrete_distribution<input_size_t> generator(distances.begin(), distances.end());
        #else  // MSVC++ older than 14.0
        		input_size_t i = 0;
        		std::discrete_distribution<input_size_t> generator(distances.size(), 0.0, 0.0, [&distances, &i](double) { return distances[i++]; });
        #endif
        		means.push_back(data[generator(rand_engine)]);
	}
	return means;
}


/*
Calculate the square of the distance between two points.
*/
float distance_squared(float* point_a, float* point_b) {
	float d_squared = 0;
	// todo change to 100 = DATA_SIZE
	for (int i = 0; i < 10; ++i) {
		d_squared += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
	}
	return std::sqrt(d_squared);
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


// todo
template <typename T, size_t N>
uint32_t closest_mean(const std::array<T, N>& point, const std::vector<std::array<T, N>>& means) {
	assert(!means.empty());
	T smallest_distance = distance_squared(point, means[0]);
	typename std::array<T, N>::size_type index = 0;
	T distance;
	for (size_t i = 1; i < means.size(); ++i) {
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
template <typename T, size_t N>
std::vector<uint32_t> calculate_clusters(
	const std::vector<std::array<T, N>>& data, const std::vector<std::array<T, N>>& means) {
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
template <typename T, size_t N>
std::vector<std::array<T, N>> calculate_means(const std::vector<std::array<T, N>>& data,
	const std::vector<uint32_t>& clusters,
	const std::vector<std::array<T, N>>& old_means,
	uint32_t k) {
	std::vector<std::array<T, N>> means(k);
	std::vector<T> count(k, T());
	for (size_t i = 0; i < std::min(clusters.size(), data.size()); ++i) {
		auto& mean = means[clusters[i]];
		count[clusters[i]] += 1;
		for (size_t j = 0; j < std::min(data[i].size(), mean.size()); ++j) {
			mean[j] += data[i][j];
		}
	}
	for (size_t i = 0; i < k; ++i) {
		if (count[i] == 0) {
			means[i] = old_means[i];
		} else {
			for (size_t j = 0; j < means[i].size(); ++j) {
				means[i][j] /= count[i];
			}
		}
	}
	return means;
}


// todo
template <typename T, size_t N>
std::vector<T> deltas(
	const std::vector<std::array<T, N>>& old_means, const std::vector<std::array<T, N>>& means)
{
	std::vector<T> distances;
	distances.reserve(means.size());
	assert(old_means.size() == means.size());
	for (size_t i = 0; i < means.size(); ++i) {
		distances.push_back(distance(means[i], old_means[i]));
	}
	return distances;
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
template <typename T, size_t N>
std::tuple<std::vector<std::array<T, N>>, std::vector<uint32_t>> kmeans_lloyd(
	const std::vector<std::array<T, N>>& data, const clustering_parameters<T>& parameters) {
	static_assert(std::is_arithmetic<T>::value && std::is_signed<T>::value,
		"kmeans_lloyd requires the template parameter T to be a signed arithmetic type (e.g. float, double, int)");
	assert(parameters.get_k() > 0); // k must be greater than zero
	assert(data.size() >= parameters.get_k()); // there must be at least k data points
	std::random_device rand_device;
	uint64_t seed = parameters.has_random_seed() ? parameters.get_random_seed() : rand_device();
	std::vector<std::array<T, N>> means = random_plusplus(data, parameters.get_k(), seed);

	std::vector<std::array<T, N>> old_means;
	std::vector<std::array<T, N>> old_old_means;
	std::vector<uint32_t> clusters;
	// Calculate new means until convergence is reached or we hit the maximum iteration count
	uint64_t count = 0;
	do {
		clusters = calculate_clusters(data, means);
		old_old_means = old_means;
		old_means = means;
		means = calculate_means(data, clusters, old_means, parameters.get_k());
		++count;
	} while (means != old_means && means != old_old_means
		&& !(parameters.has_max_iteration() && count == parameters.get_max_iteration())
		&& !(parameters.has_min_delta() && deltas_below_limit(deltas(old_means, means), parameters.get_min_delta())));

	return std::tuple<std::vector<std::array<T, N>>, std::vector<uint32_t>>(means, clusters);
}