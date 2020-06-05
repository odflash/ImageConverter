#pragma once

#include <string>
#include <unordered_map>

class ImageIc;
typedef std::unordered_map<std::string, ImageIc> TImages;

enum class EActionResult : int
{
	OK = 0
	, ERROR
	, EMPTY
	, ARG
	, NOCMD
	, LOADERR
	, STOREERR
	, BLURERR
	, RESIZEERR
	, NEEDTERMINATE
	, HELP
};

inline bool getWord(const std::string& s, size_t& iS, size_t& iE)
{
	static const std::string delim{ " \t" };

	iS = s.find_first_not_of(delim);
	if (iS == std::string::npos)
	{
		return false;
	}

	iE = s.find_first_of(delim, iS);
	return true;
}

class IAction
{
public:
	virtual ~IAction() = default;

	virtual EActionResult run(const std::string& s, std::string* errorString = nullptr) = 0;

protected:
	static TImages m_images;
};

