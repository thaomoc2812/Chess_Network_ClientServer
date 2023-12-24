#ifndef __dangnhap_H__
#define __dangnhap_H__

#include "../Include/include.hpp"

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;

void indangnhap();

//===================== text =======================
SDL_Texture *createTextTexture(const char *text);
void displayForm();
void handleInputEvent(SDL_Event *e);
void inlogin();


#endif 