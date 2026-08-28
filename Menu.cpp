#include "raylib.h"
#include "raygui.h"

#include "Menu.h"
#include <iostream>


botao::botao(const char *textura_path, Vector2 posicaoImagem, float escala)
{
	Image imagem = LoadImage(textura_path);

	int originalAltura = imagem.height;
	int originalLargura = imagem.width;

	int novaAltura = static_cast<int>(originalAltura * escala);
	int novaLargura = static_cast<int>(originalLargura * escala);

	ImageResize(&imagem, novaLargura, novaAltura);
	textura = LoadTextureFromImage(imagem);
	UnloadImage(imagem);
	posicao = posicaoImagem;
}

botao::~botao() 
{
	UnloadTexture(textura);
}

void botao::desenhaBotao()
{
	DrawTextureV(textura, posicao, WHITE);
}	


bool botao::pressionado(Vector2 posicaoMouse, bool mousePressionado)
{

	Rectangle retanguloBotao = { posicao.x, posicao.y, static_cast<float>(textura.width), static_cast<float>(textura.height) };
	if (mousePressionado)
	{
		if (CheckCollisionPointRec(posicaoMouse, retanguloBotao) && mousePressionado)
		{
			return true;
		}
	}
	return false;
}



void Menu(int largura_window, int altura_window)
{



	Vector2 posicaoMouse = GetMousePosition();
	bool mousePressionado = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);



	BeginDrawing();
		ClearBackground(BLACK);
	Vector2 posicao = {
	(largura_window / 3.5f),
	(altura_window / 2)
	};

	Texture2D fundo = LoadTexture("background.png");
	botao startbotao("start_button.png", posicao, 0.65f);


	if (startbotao.pressionado(posicaoMouse, IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
	{
		std::cout << "\n\n\nBotão pressionado!\n\n\n";
	}

		DrawTexture(fundo, largura_window/2 - fundo.width/2, altura_window/2 - fundo.height/2, WHITE);
		startbotao.desenhaBotao();

		EndDrawing();




}