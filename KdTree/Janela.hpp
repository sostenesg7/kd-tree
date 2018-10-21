#pragma once

#include <iostream>
#include <vector>
#include "sdl2\SDL.h"
#include "SDL_ttf.h"

using namespace std;

class Janela {
private:
	SDL_Event event_;
	SDL_Renderer *renderer_;
	SDL_Window *window_;
	int largura_, altura_;
	int corFundo_[3];

public:

	Janela(int, int);

	~Janela();

	void iniciar();

	int aguardEdestruir();

	void desenharLinha(int x1, int y1, int x2, int y2, int cor[3]);

	void desenharRet(int x, int y, int cor[3]);

	void salvarImagem();

	void desenharTexto(int x1, int y1, int x2, int y2);

};