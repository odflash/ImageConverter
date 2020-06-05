#include "pch.h"
#include "ActionLoad.h"
#include "Image.h"

EActionResult ActionLoad::run(const std::string& s, std::string* errorString)
{
	// ld img1 image.jpg
	size_t iS, iE;
	if (s.empty() || !getWord(s, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionLoad: Image Name not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto imgName = s.substr(iS, iE - iS);
	
	const auto sTmp = s.substr(iE);

	if (sTmp.empty() || !getWord(sTmp, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionLoad: File Name not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto fileName = sTmp.substr(iS, iE - iS);

	auto &image = m_images[imgName];
	
	if (!image.isEmpty())
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionLoad: warning: image replaced";
		}
	}

	if (!image.load(fileName))
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionLoad: can't load file at path: "; //@todo
		}
		return EActionResult::LOADERR;
	}

	return EActionResult::OK;
}
