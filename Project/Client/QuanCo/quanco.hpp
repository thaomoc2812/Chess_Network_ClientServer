#ifndef __quanco_H__
#define __quanco_H__

#include "../Include/include.hpp"

extern SDL_Window *gWindow;
extern SDL_Surface *gScreenSurface;

extern int board[8][8];

const char *getPieceImagePath(int pieceValue);
void printBoard(int board[8][8]);

#endif 