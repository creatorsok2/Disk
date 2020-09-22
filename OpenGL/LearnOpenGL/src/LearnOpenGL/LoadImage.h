#pragma once

class CLoadImage
{
public:
	static CLoadImage& GetInstance();
	~CLoadImage();

private:
	CLoadImage();

public:
	unsigned char * load(const char* path, int& width, int& height, int& nrChannels, int req_comp = 0);
	void image_free(unsigned char * data);

};