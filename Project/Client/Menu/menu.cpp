#include "menu.hpp"

// const int SCREEN_WIDTH = 420;
// const int SCREEN_HEIGHT = 400;

// SDL_Window *gWindow = NULL;
// SDL_Surface *gScreenSurface = NULL;

void inMenu()
{
	ImageInfo image1, image2, image3, image4;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image1, "image/dangky.jpg", 380, 100) ||
		!loadMedia(&image2, "image/dangnhap.jpg", 380, 180) ||
		!loadMedia(&image3, "image/xemds.jpg", 380, 260) ||
		!loadMedia(&image4, "image/thoat.jpg", 380, 340))
	{
		printf("Failed to load media!\n");
	}
	else
	{
		// Sao chép hình ảnh vào khu vực đích với kích thước và vị trí đã đặt
		SDL_BlitSurface(image1.surface, NULL, gScreenSurface, &image1.position);
		SDL_BlitSurface(image2.surface, NULL, gScreenSurface, &image2.position);
		SDL_BlitSurface(image3.surface, NULL, gScreenSurface, &image3.position);
		SDL_BlitSurface(image4.surface, NULL, gScreenSurface, &image4.position);

		// SDL_UpdateWindowSurface(gWindow);
	}
	close(&image1);
	close(&image2);
	close(&image3);
	close(&image4);
}
