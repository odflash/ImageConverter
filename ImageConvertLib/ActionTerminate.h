#pragma once
#include "IAction.h"
class ActionTerminate : public IAction
{
public:
	EActionResult run(const std::string& s, std::string* errorString) final;
};
