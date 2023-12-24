#ifndef __banco_H__
#define __banco_H__

#include "../Include/include.hpp"

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;

void inBanCo();
void veDongHo();
bool initSDL();
void closeSDL();
void renderText(const string& text, int x, int y);

#endif 