#include "Janela.hpp"

Janela::Janela(int largura, int altura)
{
	largura_ = largura;
	altura_ = altura;
}

Janela::~Janela()
{
	delete(this);
}

void Janela::iniciar()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(largura_, altura_, 0, &window_, &renderer_);
	SDL_SetRenderDrawColor(renderer_, (Uint8)255, (Uint8)255, (Uint8)255, 255);
	SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
}

int Janela::aguardEdestruir()
{
	SDL_RenderPresent(renderer_);

	//salvarImagem();

	while (1) {
		if (SDL_PollEvent(&event_) && event_.type == SDL_QUIT)
			break;
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
	return EXIT_SUCCESS;
}

void Janela::desenharLinha(int x1, int y1, int x2, int y2, int cor[3])
{
	SDL_PollEvent(&event_);
	SDL_SetRenderDrawColor(renderer_, (Uint8)cor[0], (Uint8)cor[1], (Uint8)cor[2], 255);
	SDL_RenderDrawLine(renderer_, x1 * 50 + 50, (9 - y1) * 50 + 50, x2 * 50 + 50, (9 - y2) * 50 + 50);
	SDL_RenderDrawLine(renderer_, x1 * 50 + 51, (9 - y1) * 50 + 51, x2 * 50 + 51, (9 - y2) * 50 + 51);
	SDL_RenderDrawLine(renderer_, x1 * 50 + 52, (9 - y1) * 50 + 52, x2 * 50 + 52, (9 - y2) * 50 + 52);

	SDL_RenderPresent(renderer_);
}

void Janela::desenharRet(int x, int y, int cor[3])
{
	SDL_PollEvent(&event_);
	SDL_SetRenderDrawColor(renderer_, (Uint8)cor[0], (Uint8)cor[1], (Uint8)cor[2], 255);
	

	SDL_Rect *a = new SDL_Rect();
	a->h = 10;
	a->w = 10;
	a->x = (50*x) + 45;
	a->y = (50*(9-y) ) + 45;

	SDL_RenderFillRect(renderer_, a);
	//SDL_RenderDrawRect(renderer_, a);
	SDL_RenderPresent(renderer_);
}

void Janela::desenharTexto(int x1, int y1, int x2, int y2) {

	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 50); //this opens a font style and sets a size

	SDL_Color preto = { 0, 0, 0,0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "put your text here", preto); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer_, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);
	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 100;  //controls the rect's x coordinate 
	Message_rect.y = 100; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 50; // controls the height of the rect

						  //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

						  //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer_, Message, NULL, &Message_rect);
	SDL_RenderPresent(renderer_);
}

void Janela::salvarImagem()
{
	SDL_Surface* imagemSalva = SDL_CreateRGBSurface(0, largura_, altura_, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	if (imagemSalva) {
		SDL_RenderReadPixels(renderer_, NULL, SDL_GetWindowPixelFormat(window_), imagemSalva->pixels, imagemSalva->pitch);
		SDL_SaveBMP(imagemSalva, "imagem_Salva.bmp");
		SDL_FreeSurface(imagemSalva);
		cout << "Imagem Salva";
	}
}
