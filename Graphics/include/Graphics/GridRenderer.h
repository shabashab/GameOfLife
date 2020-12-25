#pragma once
#include "Utils/Vector2.h"
#include "Graphics/IColoredRenderer.h"

namespace gol
{
	class GridRenderer final : public IColoredRenderer
	{
	private:
		Vector2s _cellSize{};
		Vector2s _gridSize{};
	private:
		void drawVerticalLines(olc::PixelGameEngine& engine) const;
		void drawHorizontalLines(olc::PixelGameEngine& engine) const;
	public:
		GridRenderer() = default;
		GridRenderer(Vector2s cellSize, Vector2s gridSize, olc::Pixel color);
		void render(olc::PixelGameEngine& engine) override;
	};
};
