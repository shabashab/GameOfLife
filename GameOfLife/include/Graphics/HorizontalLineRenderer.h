#pragma once
#include "Graphics/LineRenderer.h"

namespace gol
{
	class HorizontalLineRenderer : gol::LineRenderer
	{
	public:
		HorizontalLineRenderer() = default;
		HorizontalLineRenderer(olc::Pixel color, int screen_w, int y_pos = 0);
	public:
		void Render(olc::PixelGameEngine& engine) override;
	public:
		int getYPos() const;
		void setYPos(int y_pos, int screen_w);
	};
}

