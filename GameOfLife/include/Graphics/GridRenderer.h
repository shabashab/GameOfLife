#pragma once
#include "Utils/Vector2.h"
#include "Graphics/IColoredRenderer.h"
#include "Graphics/VerticalLineRenderer.h"
#include "Graphics/HorizontalLineRenderer.h"

namespace gol
{
	class GridRenderer final : public gol::IColoredRenderer
	{
	private:
		gol::Vector2 cell_size_ {};
		gol::VerticalLineRenderer v_line_renderer_;
		gol::HorizontalLineRenderer h_line_renderer_;
	private:
		void draw_vertical_lines(olc::PixelGameEngine& engine) ;
		void draw_horizontal_lines(olc::PixelGameEngine& engine) ;
	public:
		GridRenderer() = default;
		GridRenderer(gol::Vector2 cell_size, gol::Vector2 screen_size, olc::Pixel color);
		void Render(olc::PixelGameEngine& engine) override;
	};
};