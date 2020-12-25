#pragma once

namespace gol
{
	class Cell
	{
	public:
		bool isAlive;
		int neighboursCount;

		Cell()
		{
			isAlive = false;
			neighboursCount = 0;
		}
	};
}
