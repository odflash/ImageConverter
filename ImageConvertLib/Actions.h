#pragma once

#include <unordered_map>
#include <memory>
#include <string>

class IAction;
enum class EActionResult: int;

typedef std::unordered_map<std::string, IAction&> TActions;

class Actions
{
public:
	static EActionResult run(const std::string& s, std::string* errorString = nullptr);
	static TActions actions;
};

