#pragma once
#include "olcPixelGameEngine.h"

namespace gol
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;
		virtual void Render(olc::PixelGameEngine& engine) = 0;
	};
}
