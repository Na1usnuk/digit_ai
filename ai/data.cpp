#include "data.hpp"
#include <iostream>

data::data() :
	m_enum_label(0),
	m_label(0),
	m_distance(0)
{
}

data::data(uint8_t* buff, unsigned size) :
	m_enum_label(0),
	m_label(0),
	m_distance(0)
{
	set_pixels(buff, size);
}

data::data(std::vector<uint8_t> data) :
	m_enum_label(0),
	m_label(0),
	m_distance(0)
{
	set_pixels(data);
}

void data::convert_to_gray()
{
	std::vector<uint8_t> img;
	img.reserve(size() / 3);

	for (unsigned i = 0; i < m_pixels.size(); i = i + 3)
		img.push_back(uint8_t(0.3 * m_pixels[i] + 0.59 * m_pixels[i + 1] + 0.11 * m_pixels[i + 2]));

	FILE* f;
	fopen_s(&f, "img_gray", "wb");

	fwrite(img.data(), 1, img.size(), f);

	set_pixels(img);
}

void data::set_pixels(std::vector<uint8_t> pixels)
{
	m_pixels = pixels;
}

void data::set_pixels(uint8_t* buff, unsigned size)
{
	m_pixels.reserve(size);

	for (unsigned i = 0; i < size; ++i)
		m_pixels.push_back(buff[i]);
}

void data::append(uint8_t pixel)
{
	m_pixels.push_back(pixel);
}

void data::set_label(uint8_t label)
{
	m_label = label;
}

void data::set_enum_label(int enm)
{
	m_enum_label = enm;
}

void data::set_distance(double val)
{
	m_distance = val;
}

std::vector<uint8_t>::size_type data::size() const
{
	return m_pixels.size();
}

uint8_t data::label() const
{
	return m_label;
}

double data::distance() const
{
	return m_distance;
}

uint8_t data::enum_label() const
{
	return m_enum_label;
}

const std::vector<uint8_t>& data::pixels() const
{
	return m_pixels;
}
