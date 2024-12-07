#pragma once


class index_buffer
{
public:

	index_buffer(const unsigned int* data, unsigned int count);
	~index_buffer();

	void bind() const;
	void unbind() const;

	inline unsigned int count() const { return m_count; }

private:

	unsigned int m_id;
	unsigned int m_count;
};

