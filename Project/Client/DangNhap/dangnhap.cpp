#include "dangnhap.hpp"

void indangnhap()
{
	ImageInfo image;

	// Load thông tin cho mỗi ảnh
	if (!loadMedia(&image, "image/login.jpg", 150, 150))
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

//===================== text =======================
// Tạo texture từ chuỗi ký tự
SDL_Texture *createTextTexture(const char *text)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
	SDL_FreeSurface(textSurface);
	return textTexture;
}

// Hiển thị form nhập liệu
void displayForm()
{
	SDL_RenderClear(gRenderer);

	// Hiển thị các trường nhập liệu và nút OK
	SDL_Texture *usernameLabel = createTextTexture("Username:");
	SDL_Texture *passwordLabel = createTextTexture("Password:");
	SDL_Texture *okButton = createTextTexture("OK");

	int inputBoxWidth = 200;
	int inputBoxHeight = 30;
	int inputBoxX = 300;
	int inputBoxY = 100;
	int spacing = 40;

	SDL_Rect usernameRect = {inputBoxX, inputBoxY, inputBoxWidth, inputBoxHeight};
	SDL_Rect passwordRect = {inputBoxX, inputBoxY + spacing, inputBoxWidth, inputBoxHeight};
	SDL_Rect okButtonRect = {inputBoxX, inputBoxY + 2 * spacing, inputBoxWidth, inputBoxHeight};

	// Vẽ các trường nhập liệu và nút OK
	SDL_RenderCopy(gRenderer, usernameLabel, NULL, &usernameRect);
	SDL_RenderCopy(gRenderer, passwordLabel, NULL, &passwordRect);
	SDL_RenderCopy(gRenderer, okButton, NULL, &okButtonRect);

	// Hiển thị dữ liệu người dùng nhập vào
	SDL_Texture *usernameText = createTextTexture(username);
	SDL_Texture *passwordText = createTextTexture(password);

	SDL_Rect usernameTextRect = {inputBoxX + inputBoxWidth + 10, inputBoxY, inputBoxWidth, inputBoxHeight};
	SDL_Rect passwordTextRect = {inputBoxX + inputBoxWidth + 10, inputBoxY + spacing, inputBoxWidth, inputBoxHeight};

	SDL_RenderCopy(gRenderer, usernameText, NULL, &usernameTextRect);
	SDL_RenderCopy(gRenderer, passwordText, NULL, &passwordTextRect);

	SDL_DestroyTexture(usernameLabel);
	SDL_DestroyTexture(passwordLabel);
	SDL_DestroyTexture(okButton);
	SDL_DestroyTexture(usernameText);
	SDL_DestroyTexture(passwordText);

	SDL_RenderPresent(gRenderer);
	printf("hahaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
}

// Xử lý sự kiện nhập liệu từ bàn phím
void handleInputEvent(SDL_Event *e)
{
	if (e->type == SDL_TEXTINPUT)
	{
		// Nếu sự kiện là nhập liệu từ bàn phím
		if (strlen(username) < sizeof(username) - 1 && activeInput == 0)
		{
			// Nếu chiều dài của username chưa vượt quá giới hạn và đang nhập vào ô username
			strcat(username, e->text.text);
		}
		else if (strlen(password) < sizeof(password) - 1 && activeInput == 1)
		{
			// Nếu chiều dài của password chưa vượt quá giới hạn và đang nhập vào ô password
			strcat(password, e->text.text);
		}
	}
	else if (e->type == SDL_KEYDOWN)
	{
		// Nếu người dùng nhấn phím Enter
		if (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_KP_ENTER)
		{
			// Lưu dữ liệu khi nhấn Enter
			printf("Username: %s\n", username);
			printf("Password: %s\n", password);

			// Đặt lại dữ liệu
			username[0] = '\0';
			password[0] = '\0';
		}
		else if (e->key.keysym.sym == SDLK_BACKSPACE)
		{
			// Nếu người dùng nhấn phím Backspace
			if (activeInput == 0 && strlen(username) > 0)
			{
				// Xóa ký tự cuối cùng trong username
				username[strlen(username) - 1] = '\0';
			}
			else if (activeInput == 1 && strlen(password) > 0)
			{
				// Xóa ký tự cuối cùng trong password
				password[strlen(password) - 1] = '\0';
			}
		}
		else if (e->key.keysym.sym == SDLK_TAB)
		{
			// Nếu người dùng nhấn phím Tab, chuyển sang ô nhập liệu khác
			activeInput = (activeInput + 1) % 2;
		}
	}
}

void inlogin()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		// return 0;
	}

	if (TTF_Init() < 0)
	{
		fprintf(stderr, "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		SDL_Quit();
		// return 0;
	}

	// gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	// Kiểm tra xem người dùng có click vào nút OK không
	if (mouseX >= 300 && mouseX <= 500 && mouseY >= 240 && mouseY <= 270)
	{
		// Lưu dữ liệu khi nhấn nút OK
		printf("Username: %s\n", username);
		printf("Password: %s\n", password);

		// Đặt lại dữ liệu
		username[0] = '\0';
		password[0] = '\0';
	}
	displayForm();
}
