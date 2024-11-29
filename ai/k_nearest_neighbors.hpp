#pragma once


#include <vector>
#include <cmath>
#include <limits>
#include <map>
#include <stdint.h>
#include "data.hpp"
#include "data_handler.hpp"


class k_nearest_neighbors
{
public:

	k_nearest_neighbors(unsigned int);
	k_nearest_neighbors();
	~k_nearest_neighbors() = default;

	void set_k(unsigned int);

	void find_k_nearest(const data&);
	int predict();
	double calculate_distance(const data&, const data&);
	//double validate_perfomance();
	double test_perfomance();
	int whats_on_image(const data&);

private:

	unsigned int m_k;
	std::vector<data> m_neighbors;
	data_handler m_data_handler;

};