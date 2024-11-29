#pragma once

constexpr const char* TRAINING_DATA_FILE = "../data_set/train-images.idx3-ubyte";
constexpr const char* TRAINING_LABELS_FILE = "../data_set/train-labels.idx1-ubyte";
constexpr const char* TEST_DATA_FILE = "../data_set/t10k-images.idx3-ubyte";
constexpr const char* TEST_LABELS_FILE = "../data_set/t10k-labels.idx1-ubyte";

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <exception>
#include "data.hpp"
#include <vector>
#include <array>
#include <memory>
#include <string>
#include <map>
#include <unordered_set>
#include <thread>
#include <functional>

class data_handler
{

public:

	data_handler() = default;
	~data_handler() = default;

	void load_all_data();

	int32_t convert_to_little_endian(std::array<uint8_t, 4>);

	std::vector<data>& training_data();
	std::vector<data>& test_data();

private:

	void read_data(const std::string&, std::vector<data>&);
	void read_labels(const std::string&, std::vector<data>&);
	void count_classes();

private:

	std::vector<data> m_training_data;
	std::vector<data> m_test_data;
	std::map<uint8_t, int> m_class_map;
	
	static constexpr double TRAIN_SET_PERCENT = 0.75;
	static constexpr double TEST_SET_PERCENT = 0.20;
	static constexpr double VALIDATION_SET_PERCENT = 0.05;

};