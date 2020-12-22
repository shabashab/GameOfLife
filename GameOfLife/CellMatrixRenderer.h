#pragma once
#include "IRenderer.h"
#include "CellMatrix.h"
#include "Vector2.h"

namespace gol
{
	class CellMatrixRenderer : gol::IRenderer
	{
	private:
		std::shared_ptr<gol::CellMatrix> cell_matrix_;
		gol::Vector2 cell_size_	{};
		olc::Pixel alive_cell_color_;
	public:
		explicit CellMatrixRenderer(std::shared_ptr<gol::CellMatrix> matrix, gol::Vector2 cell_size,
		                            olc::Pixel alive_cell_color = olc::BLACK);
		void Render(olc::PixelGameEngine& engine) override;
	};
}

