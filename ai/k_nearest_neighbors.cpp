#include "k_nearest_neighbors.hpp"


k_nearest_neighbors::k_nearest_neighbors(unsigned int k)
	: m_k(k)
{
	m_data_handler.load_all_data();
}

k_nearest_neighbors::k_nearest_neighbors()
	: m_k(0)
{
	m_data_handler.load_all_data();
}

void k_nearest_neighbors::find_k_nearest(const data& query_point)
{
	double min = std::numeric_limits<double>::max();
	double previos_min = min;
	int index = 0;


	for (int ii = 0; ii < m_data_handler.training_data().size(); ++ii)
	{
		double distance = calculate_distance(query_point, m_data_handler.training_data()[ii]);
		m_data_handler.training_data()[ii].set_distance(distance);
		if (distance < min)
		{
			min = distance;
			index = ii;
		}
	}
	m_neighbors.push_back(m_data_handler.training_data()[index]);
	previos_min = min;
	min = std::numeric_limits<double>::max();

	for (unsigned i = 0; i < m_k; i++)
	{
		for (int ii = 0; ii < m_data_handler.training_data().size(); ++ii)
		{
			double distance = m_data_handler.training_data()[ii].distance();
			if (distance > previos_min and distance < min)
			{
				min = distance;
				index = ii;
			}
		}
		m_neighbors.push_back(m_data_handler.training_data()[index]);
		previos_min = min;
		min = std::numeric_limits<double>::max();
	}
}

int k_nearest_neighbors::whats_on_image(const data& img)
{
	find_k_nearest(img);
	return predict();
}
	
int k_nearest_neighbors::predict()
{
	std::map<uint8_t, int> class_freq;
	for (int i = 0; i < m_neighbors.size(); ++i)
		if (class_freq.find(m_neighbors[i].label()) == class_freq.end())
			class_freq[m_neighbors[i].label()] = 1;
		else
			class_freq[m_neighbors[i].label()]++;
	int best = 0;
	int max = 0;
	for (auto kv : class_freq)
		if (kv.second > max)
		{
			max = kv.second;
			best = kv.first;
		}
	m_neighbors.clear();
	return best;
}

double k_nearest_neighbors::calculate_distance(const data& query_point, const data& input)
{
	if (query_point.size() != input.size())
		throw std::runtime_error("[ERROR] Data size mismatch.");

	double distance = 0.0;

	for (unsigned i = 0; i < query_point.size(); ++i)
		distance += std::pow(query_point.pixels()[i] - input.pixels()[i], 2);
	distance = std::sqrt(distance);

	return distance;
}

double k_nearest_neighbors::test_perfomance()
{
	double current_perf = 0;
	int count = 0;
	int data_index = 0;
	for (data query_point : m_data_handler.test_data())
	{
		find_k_nearest(query_point);
		int prediction = predict();
		std::cout << prediction << " -> " << int(query_point.label()) << std::endl;
		if (prediction == query_point.label())
			++count;
		data_index++;
		std::cout << "Current perfomance -- " << double(double(count * 100.00) / double(data_index)) << '%' << std::endl;
	}
	current_perf = double(double(count * 100.00) / double(m_data_handler.training_data().size()));
	std::cout << "Test Perfomance -- " << current_perf << '%' << std::endl;
	return current_perf;
}

void k_nearest_neighbors::set_k(unsigned int val)
{
	m_k = val;
}
