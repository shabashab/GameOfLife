#pragma once
#include "Vector2.h"
#include "IColoredRenderer.h"
#include "VerticalLineRenderer.h"
#include "HorizontalLineRenderer.h"

namespace gol
{
	class GridRenderer :
		private gol::HorizontalLineRenderer,
		private gol::VerticalLineRenderer,
		public gol::IColoredRenderer
	{
	private:
		gol::Vector2 cell_size_;
	private:
		void draw_vertical_lines(olc::PixelGameEngine& engine) ;
		void draw_horizontal_lines(olc::PixelGameEngine& engine) ;
	public:
		GridRenderer() = default;
		GridRenderer(gol::Vector2 cell_size, gol::Vector2 screen_size, olc::Pixel color);
		void Render(olc::PixelGameEngine& engine) override;
	};
};