#pragma once

namespace gol
{
	
template<typename T>
class Vector2
{
public:
	T x;
	T y;

	Vector2() = default;
	Vector2(T x, T y) { this->x = x; this->y = y; }
	
	bool operator== (Vector2 right) const
	{
		return this->x == right.x && this->y == right.y;
	}
};

typedef Vector2<int> Vector2i;
typedef Vector2<size_t> Vector2s;
	
}

