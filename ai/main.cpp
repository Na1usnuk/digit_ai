#include <limits>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "data_handler.hpp"
#include "k_nearest_neighbors.hpp"


int main(int argc, char** argv)
{

	if (argc > 1)
	{
		int k = 1;
		for (int i = 1; i < argc; ++i)
		{
			std::string arg(argv[i]);
			if (arg.find("-k=") != std::string::npos)
				k = std::stoi(arg.substr(3));
		}

		k_nearest_neighbors knn(k);

		FILE* f;
		fopen_s(&f, argv[1], "rb");

		if (!f)
		{
			std::cerr << "[ERROR] Could not open file." << std::endl;
			return -1;
		}

		int x, y, n;

		uint8_t *image_buffer = stbi_load_from_file(f, &x, &y, &n, 0);

		if (!image_buffer)
		{
			std::cerr << "[ERROR] Could not load image." << std::endl;
			return -1;
		}

		data img(image_buffer, x * y * n);

		if (n > 1)
		{
			std::cout << "Image size: " << x * y
				<< "\nNumber of channels: " << n
				<< "\nImage has to much channels.\nConverting to gray." << std::endl;
			img.convert_to_gray();
		}

		std::cout << "I think it`s number: " << knn.whats_on_image(img) << std::endl;

		return 0;
	}

	k_nearest_neighbors knn(5);
	knn.test_perfomance();
}