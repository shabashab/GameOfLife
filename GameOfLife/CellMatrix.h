#pragma once
#include <vector>

#include "Vector2.h"
#include "Cell.h"


namespace gol
{
	class CellMatrix
	{
	private:
		typedef std::vector<Cell> cell_vector_t;
		typedef std::vector<cell_vector_t> cells_matrix_t;
		typedef std::vector<gol::Vector2> cells_positions_vector_t;
		
		cells_matrix_t						cells_;
		cells_positions_vector_t	alive_cells_positions_;

		void reset_cells_neighbours_count();
		void reset_alive_cells_positions_array();
		void reset_cells_matrix();
		
		static cells_matrix_t						create_empty_cells_matrix(size_t width, size_t height);
		static cells_positions_vector_t create_empty_alive_cells_positions_array();
		static bool											get_new_cell_state(Cell& cell);
	protected:
		int											width_;
		int											height_;
	public:
		CellMatrix(int width, int height);

		void reset();
		void setCell(Vector2 position, bool value);
		Cell getCell(Vector2 position);
		cells_positions_vector_t  getAliveCells() const;
		void step();
		
		size_t width() const;
		size_t height() const;
		
	};
}

