#include "dsonl.hpp"

void indsonl(){
    ImageInfo image, image1;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image, "image/dsonl.jpg", 0, 0) || !loadMedia(&image1, "image/thoat.jpg", 380, 620) )
	{
		printf("Failed to load media!\n");
	}
	else
	{
		// Sao chép hình ảnh vào khu vực đích với kích thước và vị trí đã đặt
		SDL_BlitSurface(image.surface, NULL, gScreenSurface, &image.position);
		SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
	}
	close(&image);
}
