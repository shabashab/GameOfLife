#pragma once
#include "Game/ICellRule.h"

class GameOfLifeCellRule : public ICellRule
{
private:
	static ICellRulePtr instance_ ;
public:
	static ICellRulePtr getInstance();

	GameOfLifeCellRule() = default;
	bool getNewCellState(Cell cell) override;
};
