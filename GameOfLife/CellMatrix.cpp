#include "CellMatrix.h"

void gol::CellMatrix::reset_cells_neighbours_count()
{
	for(int x = 0; x < width_; x++)
		for(int y = 0; y < height_; y++)
			this->cells_[x][y].neighboursCount = 0;
}

void gol::CellMatrix::reset_alive_cells_positions_array()
{
	this->alive_cells_positions_ = create_empty_alive_cells_positions_array();
}

void gol::CellMatrix::reset_cells_matrix()
{
	this->cells_ = create_empty_cells_matrix(this->width_, this->height_);
}

gol::CellMatrix::cells_matrix_t gol::CellMatrix::create_empty_cells_matrix(const size_t width, const size_t height)
{
	return cells_matrix_t(width, cell_vector_t(height));
}

gol::CellMatrix::cells_positions_vector_t  gol::CellMatrix::create_empty_alive_cells_positions_array()
{
	return cells_positions_vector_t();
}

bool gol::CellMatrix::get_new_cell_state(Cell& cell)
{
	if (cell.isAlive && (cell.neighboursCount == 2 || cell.neighboursCount == 3))
		return true;
	if (!cell.isAlive && cell.neighboursCount == 3)
		return true;
	return false;
}

void gol::CellMatrix::reset()
{
	this->reset_cells_matrix();
	this->reset_alive_cells_positions_array();
}

void gol::CellMatrix::setCell(const Vector2 position, const bool value)
{
	this->cells_[position.x][position.y].isAlive = value;
	const auto value_pos = std::find(this->alive_cells_positions_.begin(), this->alive_cells_positions_.end(), position);
	const auto exists = value_pos != this->alive_cells_positions_.end();
	
	if (value && !exists)
		this->alive_cells_positions_.push_back(position);
	else if (!value && exists)
		this->alive_cells_positions_.erase(value_pos);
}

Cell gol::CellMatrix::getCell(Vector2 position)
{
	return this->cells_[position.x][position.y];
}

gol::CellMatrix::cells_positions_vector_t gol::CellMatrix::getAliveCells() const
{
	return this->alive_cells_positions_;
}

void gol::CellMatrix::step()
{
	
	this->reset_cells_neighbours_count();

	for(auto const& value: this->alive_cells_positions_)
	{
		for(int x_offset = -1; x_offset <= 1; x_offset++)
			for(int y_offset = -1; y_offset <= 1; y_offset++)
			{
				if (x_offset == 0 && y_offset == 0) continue;
				if ((value.x + x_offset >= this->width_) || (value.x + x_offset < 0)) continue;
				if ((value.y + y_offset >= this->height_) || (value.y + y_offset < 0)) continue;

				this->cells_[value.x + x_offset][value.y + y_offset].neighboursCount++;
			}
	}

	this->reset_alive_cells_positions_array();

	for(int x = 0; x < width_; x++)
		for(int y = 0; y < height_; y++)
		{
			const bool new_state = this->get_new_cell_state(cells_[x][y]);
			this->cells_[x][y].isAlive = new_state;
			if(new_state)
				this->alive_cells_positions_.push_back(gol::Vector2(x, y));
		}
}

size_t gol::CellMatrix::width() const
{
	return width_;
}

size_t gol::CellMatrix::height() const
{
	return height_;
}

gol::CellMatrix::CellMatrix(const int width, const int height):
	width_(width), height_(height)
{
	this->reset();
}
