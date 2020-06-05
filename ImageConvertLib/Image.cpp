#include "pch.h"
#include "Image.h"

#include <Magick++.h>

ImageIc::ImageIc()
	: m_image(nullptr)
{
}

ImageIc::~ImageIc()
{
}

bool ImageIc::load(const std::string& path)
{
	try
	{
		m_image.reset(new Magick::Image(path));
	}
	catch (...) //@todo
	{
		return false;
	}

	return !isEmpty();
}

bool ImageIc::store(const std::string& path) const
{
	if (isEmpty())
	{
		return false;
	}

	try
	{
		m_image->write(path);
	}
	catch (...) //@todo
	{
		return false;
	}

	return true;
}

bool ImageIc::isEmpty() const
{
	return !static_cast<bool>(m_image);
}

bool ImageIc::blurTo(ImageIc& image, int v) const 
{ 
	if (isEmpty())
	{
		*image.m_image = {};
		return false;
	}

	try
	{
		image.m_image.reset(new Magick::Image(*m_image));
		image.m_image->blur(double(v));
	}
	catch (...)
	{
		image.m_image.reset();
		return false;
	}
	return true;
}

bool ImageIc::resizeTo(ImageIc& image, size_t width, size_t height) const
{
	if (isEmpty())
	{
		*image.m_image = {};
		return false;
	}

	auto geom = m_image->size();
	geom.width(width);
	geom.height(height);
	try
	{
		image.m_image.reset(new Magick::Image(*m_image));
		image.m_image->resize(geom);
	}
	catch (...)
	{
		image.m_image.reset();
		return false;
	}
	return true;
}
