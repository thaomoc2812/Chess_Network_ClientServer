#include "banco.hpp"

void inBanCo()
{
	ImageInfo image1, image2, image3, image4, image5, image6, image7, image8;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image1, "image/banco.jpg", 0, 0) ||
		!loadMedia(&image2, "image/nguoichoi1.jpg", 530, 0) ||
		!loadMedia(&image3, "image/nguoichoi2.jpg", 530, 220) ||
		!loadMedia(&image4, "image/luugame.jpg", 530, 430) ||
		!loadMedia(&image8, "image/thoat.jpg", 660, 430) ||
		!loadMedia(&image5, "image/tamdung.jpg", 10, 590) ||
		!loadMedia(&image6, "image/cauhoa.jpg", 260, 590) ||
		!loadMedia(&image7, "image/chiuthua.jpg", 515, 590))
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
		SDL_BlitSurface(image5.surface, NULL, gScreenSurface, &image5.position);
		SDL_BlitSurface(image6.surface, NULL, gScreenSurface, &image6.position);
		SDL_BlitSurface(image7.surface, NULL, gScreenSurface, &image7.position);
		SDL_BlitSurface(image8.surface, NULL, gScreenSurface, &image8.position);

		// SDL_UpdateWindowSurface(gWindow);
	}
	close(&image1);
	close(&image2);
	close(&image3);
	close(&image4);
	close(&image5);
	close(&image6);
	close(&image7);
	close(&image8);
}

// ===================== in dong ho =====================
bool initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Countdown Clocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }

    gFont = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 48); // Sử dụng font mặc định, ví dụ "arial.ttf"
    if (gFont == NULL)
    {
        cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        return false;
    }

    return true;
}

void closeSDL()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);
    TTF_Quit();
    SDL_Quit();
}

void renderText(const std::string &text, int x, int y)
{
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text.c_str(), textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;

    SDL_Rect renderQuad = {x, y, textWidth, textHeight};
    SDL_RenderCopy(gRenderer, textTexture, NULL, &renderQuad);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

// ===============================================================

// chuwa chayyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
// Thêm hàm vẽ đồng hồ
void veDongHo() {
    // Thêm mã vẽ đồng hồ tại đây
    int countdown1 = 600; // 10 minutes
    int countdown2 = 600; // 10 minutes
    Uint32 startTime = SDL_GetTicks();

	SDL_Event e;
	int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            // Xử lý sự kiện nếu cần thiết
        }

        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - startTime;
        int remainingTime1 = countdown1 - elapsedTime / 1000;
        int remainingTime2 = countdown2 - elapsedTime / 1000;

        if (remainingTime1 <= 0 && remainingTime2 <= 0) {
            quit = true; // Countdowns are over, exit the loop
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);

        stringstream timer1Text;
        timer1Text << "Timer 1: " << remainingTime1 / 60 << ":" << remainingTime1 % 60;
        renderText(timer1Text.str(), 50, 50);

        stringstream timer2Text;
        timer2Text << "Timer 2: " << remainingTime2 / 60 << ":" << remainingTime2 % 60;
        renderText(timer2Text.str(), 50, 150);

        SDL_RenderPresent(gRenderer);
    }
	closeSDL();
}
