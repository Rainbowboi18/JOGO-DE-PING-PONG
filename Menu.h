#pragma once
#ifndef MENU_H
#define MENU_H

#include "raylib.h"


class botao
{
public:

	 botao(const char* textura_path, Vector2 posicaoImagem, float escala);
	 ~botao();
	 void desenhaBotao();

	 bool pressionado(Vector2 posicaoMouse, bool mousePressionado);

private:
	Texture2D textura;
	Vector2 posicao;

};

void Menu(int largura_window, int altura_window);

#endif
