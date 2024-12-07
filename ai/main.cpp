#include <limits>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
//#include "include/stb_image.h"

//#include "include/data_handler.hpp"
//#include "include/k_nearest_neighbors.hpp"
//#include "include/ppm.hpp"

#include "include/renderer.hpp"




int main(int argc, char** argv)
{
	if (!glfwInit()) return EXIT_FAILURE;

	GLFWwindow* window = glfwCreateWindow(500, 300, "Digit AI", nullptr, nullptr);

	if (!window) return EXIT_FAILURE;

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK) return EXIT_FAILURE;

	const float data[12] =
	{
		 0.5f, 0.5f, 0.0f,
	 	 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	const unsigned int indices[6] =
	{
		0, 1, 2, 2, 3, 0
	};

	{
		vertex_buffer VBO(data, 12 * sizeof(float));

		index_buffer IBO(indices, 6);

		vertex_buffer_layout VBL;
		VBL.push<float>(3);

		vertex_array VAO;
		VAO.add_buffer(VBO, VBL);

		shader sh("res/shaders/simple.shader");

		renderer r;

		while (!glfwWindowShouldClose(window))
		{
			r.clear();

			r.draw(VAO, IBO, sh);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}



	glfwTerminate();

	/*if (argc > 1)
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
	}*/

}