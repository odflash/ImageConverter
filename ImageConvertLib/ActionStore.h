#pragma once
#include "IAction.h"

#include <string>

class ActionStore : public IAction
{
public:
	EActionResult run(const std::string& s, std::string* errorString) final;

};

