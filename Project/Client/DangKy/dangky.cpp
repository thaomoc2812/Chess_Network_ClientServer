#include "dangky.hpp"

void indangky(){
    ImageInfo image;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image, "image/reges.jpg", 150, 150) )
	{
		printf("Failed to load media!\n");
	}
	else
	{
		// Sao chép hình ảnh vào khu vực đích với kích thước và vị trí đã đặt
		SDL_BlitSurface(image.surface, NULL, gScreenSurface, &image.position);
	}
	close(&image);
}
