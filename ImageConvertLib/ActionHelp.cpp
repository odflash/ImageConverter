#include "pch.h"
#include "ActionHelp.h"

EActionResult ActionHelp::run(const std::string& s, std::string* errorString)
{
	if (errorString != nullptr)
	{
		*errorString =
			"load, ld      -  load <name> <filename> \n"
			"store, s      -  store <name> <filename> \n"
			"blur          -  blur <name> <to_name> <size>\n"
			"resize        -  resize <name> <to_name> <width> <height>\n"
			"help, h       -  echo help\n"
			"exit, quit, q -  echo help\n"
			;
	}
	return EActionResult::HELP;
}
