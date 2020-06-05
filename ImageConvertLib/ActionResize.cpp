#include "pch.h"

#include "ActionResize.h"
#include "Image.h"

EActionResult ActionResize::run(const std::string& s, std::string* errorString)
{
	// resize img1 img1b 123 536
	size_t iS, iE;

	if (s.empty() || !getWord(s, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionResize: Image Source Name not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto imgSrc = s.substr(iS, iE - iS);

	auto itSrc = m_images.find(imgSrc);

	if (itSrc == m_images.end())
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionResize: Source Image not found";
		}
		return EActionResult::BLURERR;

	}

	const auto sTmp = s.substr(iE);

	if (sTmp.empty() || !getWord(sTmp, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionResize: Image Source Name not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto imgDst = sTmp.substr(iS, iE - iS);

	auto itDst = m_images.find(imgDst);

	if (itDst != m_images.end())
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionResize: warning: image dst replaced";
		}
	}

	const auto sWidth = sTmp.substr(iE);

	if (sWidth.empty() || !getWord(sWidth, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionResize: Image Width Value not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto widthValue = sWidth.substr(iS, iE - iS);
	int wValue;
	try
	{
		wValue = std::stoi(widthValue);
	}
	catch (...)
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionResize: Image Width Value no integer";
		}
		return EActionResult::ARG;
	}

	const auto sHeight = sWidth.substr(iE);

	if (sHeight.empty() || !getWord(sHeight, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionResize: Image Width Value not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto heightValue = sHeight.substr(iS, iE - iS);
	int hValue;
	try
	{
		hValue = std::stoi(heightValue);
	}
	catch (...)
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionResize: Image Height Value no integer";
		}
		return EActionResult::ARG;
	}

	if (!itSrc->second.resizeTo(m_images[imgDst], wValue, hValue))
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionResize: can't blur to img: "; //@todo
		}
		return EActionResult::RESIZEERR;
	}

	return EActionResult::OK;
}
