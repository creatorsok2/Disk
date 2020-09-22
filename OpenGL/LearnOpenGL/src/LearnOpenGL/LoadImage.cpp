#include "LoadImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

CLoadImage & CLoadImage::GetInstance()
{
	static CLoadImage instance;
	return instance;
}

CLoadImage::~CLoadImage() = default;

CLoadImage::CLoadImage() = default;

unsigned char * CLoadImage::load(const char * path, int& width, int& height, int& nrChannels, int req_comp)
{
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	return stbi_load(path, &width, &height, &nrChannels, req_comp);
}

void CLoadImage::image_free(unsigned char * data)
{
	stbi_image_free(data);
}