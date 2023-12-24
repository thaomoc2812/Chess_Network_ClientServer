#include "../QuanCo/quanco.hpp"
#include "../BanCo/banco.hpp"
#include "../Menu/menu.hpp"
#include "../ClickChuot/clickChuot.hpp"
#include "../DangNhap/dangnhap.hpp"
#include "../DangKy/dangky.hpp"
#include "../DanhSachOnl/dsonl.hpp"

int showMenu = 1;
int showInDangNhap = 0;
int showInDangKy = 0;
int showDSOnl = 0;
int showBanco = 0;
int showinlogin = 0;

// Dữ liệu người dùng nhập vào
char username[256] = "";
char password[256] = "";
// Biến để kiểm tra xem người dùng đang nhập vào ô nào
int activeInput = 0; // 0 là username, 1 là password

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 24);
SDL_Color textColor = {255, 255, 255, 255};

void home()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{		
		SDL_Event e;
		int quit = 0;
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = 1;
				else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX, mouseY;
					SDL_GetMouseState(&mouseX, &mouseY);

					// ======================= man hinh dang nhap =========================

					// Kiểm tra xem chuột có nằm trong dang ky
					if (isMouseInsideRect(mouseX, mouseY, 380, 80, 100, 50) && showMenu == 1)
					{
						// Chuột nằm trong dang ky
						showMenu = 0;
						SDL_DestroyWindow(gWindow);
						init();

						indangky();
						showInDangKy = 1;
					}

					// Kiểm tra xem chuột có nằm trong dang nhap
					else if (isMouseInsideRect(mouseX, mouseY, 380, 180, 100, 50) && showMenu == 1)
					{
						// Chuột nằm trong dang nhap
						showMenu = 0;
						SDL_DestroyWindow(gWindow);
						init();

						indangnhap();

						showInDangNhap = 1;

						inlogin();

						showinlogin = 1;
						// =========================================

						// =========================================
					}

					// Kiểm tra xem chuột có nằm trong ds onl
					else if (isMouseInsideRect(mouseX, mouseY, 380, 260, 100, 50) && showMenu == 1)
					{
						// Chuột nằm trong ds onl
						showMenu = 0;
						SDL_DestroyWindow(gWindow);
						init();

						indsonl();
						showDSOnl = 1;
					}

					// Kiểm tra xem chuột có nằm trong thoat
					else if (isMouseInsideRect(mouseX, mouseY, 380, 350, 100, 50) && showMenu == 1)
					{
						exit(0);
					}

					// ======================= man hinh dang ky =========================

					else if (isMouseInsideRect(mouseX, mouseY, 300, 450, 130, 60) && showInDangKy == 1)
					{
						// Chuột nằm trong dang ky
						showInDangKy = 0;
						SDL_DestroyWindow(gWindow);
						init();

						inMenu();
						showMenu = 1;
					}

					// ======================= man hinh dang nhap =========================

					else if (isMouseInsideRect(mouseX, mouseY, 300, 350, 130, 60) && showInDangNhap == 1)
					{
						// Chuột nằm trong dang nhap
						showInDangNhap = 0;
						SDL_DestroyWindow(gWindow);
						init();

						inBanCo();
						printBoard(board);
					}

					else if (showInDangNhap == 0 && showDSOnl == 0 && showInDangKy == 0 && showMenu == 0)
					{
						int line, column;
						for (line = 0; line < 8; line++)
						{
							for (column = 0; column < 8; column++)
							{
								int x, y, w, h;
								x = 50 + column * 50;
								y = 50 + line * 50;
								w = 50;
								h = 50;
								ImageInfo oCo, quanco;
								if (isMouseInsideRect(mouseX, mouseY, x, y, w, h))
								{
									char img[100];
									sprintf(img, "image/quanco/banco_%d_%d.png", line, column);
									if (loadMedia(&oCo, "image/quandangchon.png", x, y))
									{
										SDL_BlitSurface(oCo.surface, NULL, gScreenSurface, &oCo.position);
										if (loadMedia(&quanco, img, 38 + column * 52, line * 55))
											SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
									}
								}
								// close(&oCo);
							}
						}

						// an nut thoat quay lai menu
						if (isMouseInsideRect(mouseX, mouseY, 660, 430, 70, 40))
						{
							SDL_DestroyWindow(gWindow);
							init();
							inMenu();
							showMenu = 1;
						}
					}

					// ======================= man hinh ds onl =========================

					else if (isMouseInsideRect(mouseX, mouseY, 380, 620, 100, 50) && showDSOnl == 1)
					{
						// Chuột nằm trong dang nhap
						showDSOnl = 0;
						SDL_DestroyWindow(gWindow);
						init();

						inMenu();
						showMenu = 1;
					}

					// =====================================================================
				}
				if (showInDangNhap)
				{
					// Xử lý sự kiện nhập liệu từ bàn phím username password
					handleInputEvent(&e);
				}

				if (showMenu)
					inMenu();
			}
			
			SDL_UpdateWindowSurface(gWindow);
		}
		TTF_CloseFont(gFont);
		TTF_Quit();
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		SDL_Quit();
		
	}
}
