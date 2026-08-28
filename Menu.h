#pragma once


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

enum AcaoMenu
{
	NENHUMA,
	JOGAR,
	SAIR
};

AcaoMenu Menu(int largura_window, int altura_window);

bool startbotao(botao* startbotao, Vector2 posicaoMouse);

