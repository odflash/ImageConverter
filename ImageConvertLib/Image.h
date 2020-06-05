#pragma once

#include <string>
#include <memory>

namespace Magick
{
	class Image;
}


class ImageIc
{
public:
	ImageIc();
	~ImageIc();
	bool load(const std::string& path);
	bool store(const std::string& path) const;
	bool isEmpty() const;
	bool blurTo(ImageIc& image, int v) const;
	bool resizeTo(ImageIc& image, size_t width, size_t height) const;

private:
	std::unique_ptr<Magick::Image> m_image;
};

