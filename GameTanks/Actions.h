#pragma once

#include "Levels.h"

class BaseAction {
public:
	virtual bool RunAction(BaseLevel Action_for_level);
};

class MenuLeveNewGame : BaseAction
{
	bool RunAction(BaseLevel Action_for_level) override;
};