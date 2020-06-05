#include "pch.h"
#include "ActionStore.h"
#include "Image.h"

EActionResult ActionStore::run(const std::string& s, std::string* errorString)
{
	// store img1b image2.jpg
	size_t iS, iE;
	if (s.empty() || !getWord(s, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionStore: Image Name not defined";
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
				*errorString = "ActionStore: File Name not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto fileName = sTmp.substr(iS, iE - iS);

	auto it = m_images.find(imgName);

	if (it == m_images.end() || it->second.isEmpty())
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionLoad: try store empty image";
			return EActionResult::STOREERR;
		}
	}

	if (!it->second.store(fileName))
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionLoad: can't load file at path: "; //@todo
		}
		return EActionResult::STOREERR;
	}

	return EActionResult::OK;
}
