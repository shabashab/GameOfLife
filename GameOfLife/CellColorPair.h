#pragma once
#include "olcPixelGameEngine.h"

namespace gol
{
	class CellColorPair
	{
	public:
		olc::Pixel aliveColor;
		olc::Pixel emptyColor;

		CellColorPair() = default;
		CellColorPair(olc::Pixel alive_color, olc::Pixel empty_color)
		{ aliveColor = alive_color; emptyColor = empty_color; }
	};
}

