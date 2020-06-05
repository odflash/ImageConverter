#pragma once
#include "IAction.h"

#include <string>

class ActionLoad : public IAction
{
public:
    EActionResult run(const std::string& s, std::string* errorString = nullptr) final;
};

