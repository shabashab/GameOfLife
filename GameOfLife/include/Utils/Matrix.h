#pragma once
#include <memory>
#include <functional>

#include "Utils/Vector2.h"

template<typename T>
class Matrix
{
public:
	Matrix(const Matrix& other)
		: _array(other._array),
		  _width(other._width),
		  _height(other._height)
	{
	}

	Matrix(Matrix&& other) noexcept
		: _array(std::move(other._array)),
		  _width(other._width),
		  _height(other._height)
	{
	}

	Matrix& operator=(const Matrix& other)
	{
		if (this == &other)
			return *this;
		_array = other._array;
		_width = other._width;
		_height = other._height;
		return *this;
	}

	Matrix& operator=(Matrix&& other) noexcept
	{
		if (this == &other)
			return *this;
		_array = std::move(other._array);
		_width = other._width;
		_height = other._height;
		return *this;
	}

private:
	std::unique_ptr<T[]> _array;
protected:
	size_t _width;
	size_t _height;
public:
	virtual size_t width() const
	{
		return _width;
	}

	virtual size_t height() const
	{
		return _height;
	}
public:
	Matrix() = default;
	Matrix(size_t width, size_t height, std::function<T(size_t, size_t)> creator_function);
	~Matrix();
	void forEach(std::function<void(size_t, size_t, T&)> function);
	T& at(size_t x, size_t y);
	T& at(gol::Vector2s position);
};

template <typename T>
Matrix<T>::Matrix(size_t width, size_t height, std::function<T(size_t, size_t)> creator_function)
{
	this->_array = std::make_unique<T[]>(width * height);
	for(size_t x = 0; x < width; x++)
		for(size_t y = 0; y < height; y++)
			this->_array[(x * width) + y] = creator_function(x, y);
	
	this->_width = width;
	this->_height = height;
}

template <typename T>
T& Matrix<T>::at(size_t x, size_t y)
{
	return _array[(y * _width) + x];
}

template <typename T>
T& Matrix<T>::at(gol::Vector2s position)
{
	return this->at(position.x, position.y);
}

template <typename T>
Matrix<T>::~Matrix()
{
	_array.reset();
}

template <typename T>
void Matrix<T>::forEach(std::function<void(size_t, size_t, T&)> function)
{
	for(size_t x = 0; x < _width; x++)
		for(size_t y = 0; y < _height; y++)
			function(x, y, this->at(x, y));
}
