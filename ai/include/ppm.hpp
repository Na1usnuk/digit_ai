#pragma once
#include <cstdio>
#include <vector>
#include <string>
#include "data.hpp"

constexpr const char* ppm_header = "P6 28 28 255\n";


void save_ppm_to_file(const data& d)
{
	FILE* file;
	fopen_s(&file, "../data_set/img.ppm", "wb");

	fwrite(ppm_header, 1, 13, file);

	std::vector<unsigned char> pix;
	pix.reserve(28 * 28 * 3);

	for (int i = 0; i < d.size(); ++i)
	{
		pix.emplace_back(d.pixels()[i]);
		pix.emplace_back(d.pixels()[i]);
		pix.emplace_back(d.pixels()[i]);
	}
		

	fwrite(pix.data(), 1, pix.size(), file);
}
