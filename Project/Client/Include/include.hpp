#ifndef __include_H__
#define __include_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 680;

// Dữ liệu người dùng nhập vào
extern char username[256];
extern char password[256];
// Biến để kiểm tra xem người dùng đang nhập vào ô nào
extern int activeInput; // 0 là username, 1 là password

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;
extern SDL_Renderer *gRenderer;
extern TTF_Font* gFont;
extern SDL_Color textColor;

// Định nghĩa cấu trúc để lưu trữ thông tin của mỗi ảnh
typedef struct
{
	SDL_Surface *surface;
	SDL_Rect position;
} ImageInfo;

int init();
int loadMedia(ImageInfo *imageInfo, const char *imagePath, int x, int y);
void close(ImageInfo *imageInfo);

#endif 