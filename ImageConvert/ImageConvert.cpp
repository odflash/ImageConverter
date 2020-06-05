#include <iostream>

#include <Magick++.h>

#include "..\ImageConvertLib\IAction.h"
#include "..\ImageConvertLib\Actions.h"

int main(int argc, char** argv)
{
	//Magick::InitializeMagick(*argv);
	std::string s;
	std::string errorString;

	while (true)
	{
		std::getline(std::cin, s);
		EActionResult result = Actions::run(s, &errorString);
		std::cout << errorString << std::endl;
		if (result == EActionResult::NEEDTERMINATE)
		{
			break;
		}
	}
	return 0;
}