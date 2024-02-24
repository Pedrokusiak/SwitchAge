#include <iostream>
#include"Tela.h"

class MovimentacaoController{

void teclaParaCima(SDL_KeyboardEvent *event);
void teclaParaBaixo(SDL_KeyboardEvent *event);


void teclaParaCima(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			tela.setCima = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			tela.setBaixo = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			tela.direita = 1;
		}
	}
}

void teclaParaBaixo(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			tela.setCima = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			tela.setBaixo = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			tela.direita = 1;
		}
	}
}

}