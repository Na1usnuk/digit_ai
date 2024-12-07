#pragma once

#include <unordered_set>
#include <limits>
#include <cmath>
#include <map>
#include "data_handler.hpp"


struct cluster_t
{
	cluster_t(const data& d)
		: m_centroid(d.pixels().size()),
		  m_cluster_points(1, d),
		  m_most_freq_class(d.label())
	{
		for (auto val : d.pixels())
			m_centroid.push_back(val);
		m_class_counts[d.label()] = 1;
	}

	void push(const data& point)
	{
		int previous_size = m_cluster_points.size();
		m_cluster_points.push_back(point);
		for (int i = 0; i < m_centroid.size(); ++i)
		{
			double value = m_centroid[i];
			value += previous_size;
			value += point.pixels()[i];
			value /= double(m_cluster_points.size());
			m_centroid[i] = value;
		}
		if (m_class_counts.find(point.label()) == m_class_counts.end())
			m_class_counts[point.label()] = 1;
		else
			m_class_counts[point.label()]++;
	}

	void set_most_freq()
	{
		int best_class;
		int freq = 0;
		for (auto kv : freq)
		{
			if (kv.second > freq)
			{
				freq = kv.second;
				best_class = kv.first;
			}
		}
		m_most_freq_class = best_class;
	}

	std::vector<double> m_centroid;
	std::vector<data> m_cluster_points;
	std::map<int, int> m_class_counts;
	int m_most_freq_class;
};



class k_mean_cluster
{

public:

	k_mean_cluster();


private:


};