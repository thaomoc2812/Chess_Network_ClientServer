#include "quanco.hpp"

// BOARD
int board[8][8] =
	{
		{8, 7, 9, 11, 10, 9, 7, 8},
		{12, 12, 12, 12, 12, 12, 12, 12},
		{13, 13, 13, 13, 13, 13, 13, 13},
		{13, 13, 13, 13, 13, 13, 13, 13},
		{13, 13, 13, 13, 13, 13, 13, 13},
		{13, 13, 13, 13, 13, 13, 13, 13},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{2, 1, 3, 4, 5, 3, 1, 2}};

const char *getPieceImagePath(int pieceValue)
{
	switch (pieceValue)
	{
	case 1:
		return "image/quancocopy/KnightW.png";
	case 2:
		return "image/quancocopy/RookW.png";
	case 3:
		return "image/quancocopy/BishopW.png";
	case 4:
		return "image/quancocopy/QueenW.png";
	case 5:
		return "image/quancocopy/KingW.png";
	case 6:
		return "image/quancocopy/PawnW.png";

	case 7:
		return "image/quancocopy/KnightB.png";
	case 8:
		return "image/quancocopy/RookB.png";
	case 9:
		return "image/quancocopy/BishopB.png";
	case 10:
		return "image/quancocopy/KingB.png";
	case 11:
		return "image/quancocopy/QueenB.png";
	case 12:
		return "image/quancocopy/PawnB.png";

		// case 13:
		// 	return "image/nentrangfake.png";

	default:
		return "image/nentrangfake.png"; // Đường dẫn cho trường hợp mặc định (empty)
	}
}

void printBoard(int board[8][8])
{
    int line, column;

    for (line = 0; line < 8; line++)
    {
        for (column = 0; column < 8; column++)
        {
            ImageInfo quanco;
            const char *imagePath = getPieceImagePath(board[line][column]);
            if (loadMedia(&quanco, imagePath, 38 + column * 52, line * 55))
            {
                SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
            }
            close(&quanco);
        }
    }

    // SDL_UpdateWindowSurface(gWindow);
}

