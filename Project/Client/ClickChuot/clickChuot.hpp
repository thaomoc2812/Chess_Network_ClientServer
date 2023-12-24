#ifndef __clickChuot_H__
#define __clickChuot_H__

#include "../Include/include.hpp"

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;

bool isMouseInsideRect(int mouseX, int mouseY, int x, int y, int w, int h);
void clearScreen();

#endif 