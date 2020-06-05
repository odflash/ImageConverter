#include "pch.h"
#include "Actions.h"

#include "IAction.h"
#include "ActionLoad.h"
#include "ActionStore.h"
#include "ActionBlur.h"
#include "ActionResize.h"
#include "ActionHelp.h"
#include "ActionTerminate.h"

static ActionLoad actionLoad;
static ActionStore actionStore;
static ActionBlur actionBlur;
static ActionResize actionResize;
static ActionHelp actionHelp;
static ActionTerminate actionTerminate;

TActions Actions::actions{
	{"load", actionLoad}
	, {"ld", actionLoad}
	, {"store", actionStore}
	, {"s", actionStore}
	, {"blur", actionBlur}
	, {"resize", actionResize}
	, {"help", actionHelp}
	, {"h", actionHelp}
	, {"exit", actionTerminate}
	, {"quit", actionTerminate}
	, {"q", actionTerminate}
};

EActionResult Actions::run(const std::string& s, std::string* errorString)
{
	if (errorString != nullptr)
	{
		errorString->clear();
	}

	size_t iS, iE;
	if (!getWord(s, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "string is empty";
			}
			return EActionResult::EMPTY;
		}
	}

	auto it = actions.find(s.substr(iS, iE - iS));
	if (it == actions.end())
	{
		if (errorString != nullptr)
		{
			*errorString = "command not found";
		}
		return EActionResult::NOCMD;
	}

	EActionResult result = EActionResult::OK;
	if (iE == std::string::npos)
	{
		result = it->second.run({}, errorString);
	}
	else
	{
		result = it->second.run(s.substr(iE), errorString);
	}

	if (result == EActionResult::OK)
	{
		if (errorString != nullptr && errorString->empty())
		{
			*errorString = "ok";
		}
	}
	return result;
}
