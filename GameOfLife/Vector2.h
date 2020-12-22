#pragma once

namespace gol
{
	class Vector2
	{
	public:
		int x;
		int y;

		Vector2() = default;
		Vector2(int x, int y) { this->x = x; this->y = y; }
		
		bool operator== (Vector2 right) const
		{
			return this->x == right.x && this->y == right.y;
		}
	};
}

