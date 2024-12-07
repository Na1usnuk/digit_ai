#include "../include/data_handler.hpp"


void data_handler::read_data(const std::string& path, std::vector<data>& dest)
{
	int32_t header[4];
	std::array<uint8_t, 4> bytes;

	FILE* file;
	fopen_s(&file, path.c_str(), "rb");
	if (file)
	{
		for (int i = 0; i < 4; ++i)
			if (fread(bytes.data(), sizeof(bytes), 1, file))
				header[i] = convert_to_little_endian(bytes);
			else 
				throw std::runtime_error("[ERROR] Reading from file failed.");

		std::cout << "Done getting data file header." << std::endl;

		dest.resize(header[1]);
		int image_size = header[2] * header[3];
		for (int i = 0; i < header[1]; ++i)
		{
			data d;
			uint8_t pixel[1];

			for (int ii = 0; ii < image_size; ++ii)
				if (fread(pixel, sizeof(pixel), 1, file))
					d.append(pixel[0]);
				else
					throw std::runtime_error("[ERROR] Reading from file failed.");

			dest[i].set_pixels(d.pixels());
		}

		std::cout << "Successfully read and store " << header[1] << " images." << std::endl;

	}
	else
		throw std::runtime_error("[ERROR] Could not find file.");

	fclose(file);
}

void data_handler::read_labels(const std::string& path, std::vector<data>& dest)
{
	int32_t header[2];
	std::array<uint8_t, 4> bytes;

	FILE* file;
	fopen_s(&file, path.c_str(), "rb");
	if (file)
	{
		for (int i = 0; i < 2; ++i)
			if (fread(bytes.data(), sizeof(bytes), 1, file))
				header[i] = convert_to_little_endian(bytes);

		std::cout << "Done getting label file header." << std::endl;

		for (int i = 0; i < header[1]; ++i)
		{
			uint8_t label[1];
			if (fread(label, sizeof(label), 1, file))
				dest[i].set_label(label[0]);
			else
				throw std::runtime_error("[ERROR] Reading from file failed.");
		}

		std::cout << "Successfully read and store " << header[1] << " labels." << std::endl;

	}
	else
		throw std::runtime_error("[ERROR] Could not find file.");

	fclose(file);
}

void data_handler::count_classes()
{
	int count = 0;
	for (unsigned i = 0; i < m_training_data.size(); ++i)
		if (m_class_map.find(m_training_data[i].label()) == m_class_map.end())
		{
			m_class_map[m_training_data[i].label()] = count;
			m_training_data[i].set_enum_label(count++);
		}
	std::cout << "Successfully extracted " << m_class_map.size() << " classes." << std::endl;
}

void data_handler::load_all_data()
{
	//std::thread train_data(std::bind(&data_handler::read_data, this, TRAINING_DATA_FILE, m_training_data));
	//std::thread train_labels(std::bind(&data_handler::read_labels, this, TRAINING_LABELS_FILE, m_training_data));
	read_data(TRAINING_DATA_FILE, m_training_data);
	read_labels(TRAINING_LABELS_FILE, m_training_data);
	read_data(TEST_DATA_FILE, m_test_data);
	read_labels(TEST_LABELS_FILE, m_test_data);
	//std::thread test_data(std::bind(&data_handler::read_data, this, TEST_DATA_FILE, m_test_data));
	//std::thread test_labels(std::bind(&data_handler::read_labels, this, TEST_LABELS_FILE, m_test_data));
	//train_data.join();
	//train_labels.join();
	//test_data.join();
	//test_labels.join();
	count_classes();
}

int32_t data_handler::convert_to_little_endian(std::array<uint8_t, 4> bytes)
{
	return (int32_t)((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | (bytes[3]));
}

std::vector<data>& data_handler::training_data()
{
	return m_training_data;
}

std::vector<data>& data_handler::test_data()
{
	return m_test_data;
}

