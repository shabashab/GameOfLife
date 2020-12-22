#pragma once
#include <memory>
#include "Game/Cell.h"

class ICellRule
{
public:
	virtual ~ICellRule() = default;
	virtual bool getNewCellState(Cell cell) = 0;
};

typedef std::shared_ptr<ICellRule> ICellRulePtr;