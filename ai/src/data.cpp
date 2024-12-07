#include "../include/data.hpp"
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

void data::load_from_test_file(unsigned int n = 0)
{
	FILE* img_file;
	fopen_s(&img_file, "../data_set/t10k-images.idx3-ubyte", "rb");
	if (!img_file) return;
	const unsigned int offset = (28 * 28 * n) + 16;
	fseek(img_file, offset, SEEK_SET);
	unsigned char pixel[1];
	m_pixels.reserve(28 * 28);

	for (int i = 0; i < 28 * 28; ++i)
		if(fread(pixel, 1, 1, img_file))
			m_pixels.emplace_back(pixel[0]);
		
	fclose(img_file);
	FILE* label_file;
	fopen_s(&label_file, "../data_set/t10k-labels.idx1-ubyte", "rb");
	if (!label_file) return;
	fseek(label_file, n + 8, SEEK_SET);
	fread(&m_label, 1, 1, label_file);
	fclose(label_file);
}

void data::convert_to_gray()
{
	std::vector<uint8_t> img;
	img.reserve(size() / 3);

	for (unsigned i = 0; i < m_pixels.size(); i = i + 3)
		img.push_back(uint8_t(0.3 * m_pixels[i] + 0.59 * m_pixels[i + 1] + 0.11 * m_pixels[i + 2]));

	FILE* f;
	fopen_s(&f, "img_gray", "wb");

	if (!f) return;

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
