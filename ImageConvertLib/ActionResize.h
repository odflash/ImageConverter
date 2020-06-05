#pragma once
#include "IAction.h"
class ActionResize : public IAction
{
public:
	EActionResult run(const std::string& s, std::string* errorString) final;
};
