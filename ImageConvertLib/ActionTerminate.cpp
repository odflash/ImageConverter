#include "pch.h"
#include "ActionTerminate.h"

EActionResult ActionTerminate::run(const std::string& s, std::string* errorString) 
{ 
	if (errorString != nullptr)
	{
		*errorString = "Terminate & exit";
	}

	return EActionResult::NEEDTERMINATE; 
}
