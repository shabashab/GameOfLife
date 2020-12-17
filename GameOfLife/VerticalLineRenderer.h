#pragma once
#include "LineRenderer.h"

namespace gol
{
	class VerticalLineRenderer : gol::LineRenderer
	{
	public:
		VerticalLineRenderer() = default;
		VerticalLineRenderer(olc::Pixel color, int screen_h, int x_pos = 0);
	public:
		void setXPos(int x_pos, int screen_h);
		int getXPos() const;
	public:
		void Render(olc::PixelGameEngine& engine) override;
	};
}
