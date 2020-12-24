#pragma once
#include "Utils/Vector2.h"
#include "Graphics/IColoredRenderer.h"

namespace gol
{
	class GridRenderer final : public gol::IColoredRenderer
	{
	private:
		gol::Vector2s cell_size_ {};
		gol::Vector2s grid_size_ {};
	private:
		void draw_vertical_lines(olc::PixelGameEngine& engine) const;
		void draw_horizontal_lines(olc::PixelGameEngine& engine) const;
	public:
		GridRenderer() = default;
		GridRenderer(gol::Vector2s cell_size, gol::Vector2s grid_size, olc::Pixel color);
		void Render(olc::PixelGameEngine& engine) override;
	};

};