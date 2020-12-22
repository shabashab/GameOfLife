#include "Game/GameOfLifeCellRule.h"

ICellRulePtr GameOfLifeCellRule::instance_ = nullptr;

ICellRulePtr GameOfLifeCellRule::getInstance()
{
	if (GameOfLifeCellRule::instance_ == nullptr)
		GameOfLifeCellRule::instance_ = std::make_shared<GameOfLifeCellRule>();
	return GameOfLifeCellRule::instance_;
}

bool GameOfLifeCellRule::getNewCellState(Cell cell)
{
	if (cell.isAlive && (cell.neighboursCount == 3 || cell.neighboursCount == 2))
		return true;
	if (!cell.isAlive && cell.neighboursCount == 3)
		return true;
	return false;
}
