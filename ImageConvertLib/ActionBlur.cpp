#include "pch.h"

#include "ActionBlur.h"
#include "Image.h"

EActionResult ActionBlur::run(const std::string& s, std::string* errorString) 
{ 
	// blur img1 img1b 5
	size_t iS, iE;

	if (s.empty() || !getWord(s, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionBlur: Image Source Name not defined";
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
			*errorString = "ActionBlur: Source Image not found";
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
				*errorString = "ActionBlur: Image Source Name not defined";
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
			*errorString = "ActionBlur: warning: image dst replaced";
		}
	}

	const auto sN = sTmp.substr(iE);

	if (sN.empty() || !getWord(sN, iS, iE))
	{
		if (iS == std::string::npos)
		{
			if (errorString != nullptr)
			{
				*errorString = "ActionBlur: Image Blur Value not defined";
			}
			return EActionResult::ARG;
		}
	}

	const auto blurValue = sN.substr(iS, iE - iS);
	int bValue;
	try
	{
		bValue = std::stoi(blurValue);
	}
	catch (...)
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionBlur: Image Blur Value no integer";
		}
		return EActionResult::ARG;
	}

	if (!itSrc->second.blurTo(m_images[imgDst], bValue))
	{
		if (errorString != nullptr)
		{
			*errorString = "ActionBlur: can't blur to img: "; //@todo
		}
		return EActionResult::BLURERR;
	}

	return EActionResult::OK; 
}
