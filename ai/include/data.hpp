#pragma once

#include <vector>
#include <memory>
#include <stdint.h>


class data
{

public:

	data();
	data(uint8_t*, unsigned);
	data(std::vector<uint8_t>);

	void load_from_test_file(unsigned int);
	void convert_to_gray();

	//setters
	void set_pixels(std::vector<uint8_t>);
	void set_pixels(uint8_t*, unsigned);
	void append(uint8_t);
	void set_label(uint8_t);
	void set_enum_label(int);
	void set_distance(double);

	//getters
	std::vector<uint8_t>::size_type size() const;
	double distance() const;
	uint8_t label() const;
	uint8_t enum_label() const;
	const std::vector<uint8_t>& pixels() const;

private:

	std::vector<uint8_t> m_pixels;
	uint8_t m_label;
	int m_enum_label;
	double m_distance;

};

