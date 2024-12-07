#pragma once


class vertex_buffer
{
public:

	vertex_buffer(const void* data, unsigned int size);
	~vertex_buffer();

	void bind() const;
	void unbind() const;

private:

	unsigned int m_id;
};
