#include "raylib.h"
#include <iostream>
#include <math.h>

#include "Menu.h"

using namespace std;

int largura_window = 800;
int altura_window = 600;

int main(void)
{



	//sistema de pontuação
	int pontosJogador = 0;
	int pontosCPU = 0;

	// cronometro da mensagem de perda e ganho
	float cronometro = 0.0f;
	float tempoDeMensagem = 0.75f;

	bool exibirMensagemGanho = false;
	bool exibirMensagemPerda = false;

	//raio, posição inicial e velocidade inicial da bola de ping pong
	Vector2 velocidade = { 5, 5 };
	Vector2 circulo = { 100, 100 };
	float circulo_raio = 15;

	//verificação das colisões antigas da IA
	bool colisaoIAantiga = false;
	bool colisaoIARec = false;

	// retangulo do jogador posição e tamanho
	Vector2 retanguloJogadorTamanho = { 15, 100 };
	Vector2 retanguloJogadorPosicao = { 0, 225 };

	// bools que definem a altura maxima e minima do retangulo do jogador
	bool alturaMaxima = true;
	bool alturaMinima = true;


	//retangulo da IA posição e tamanho
	Vector2 retanguloCpuTamanho = { 15, 100 };
	Vector2 retanguloCpuPosicao = { largura_window - 15, 225 };

	////botões da GUI UI
	bool botaoJogar = false;
	bool botaoMenu = false;
	bool botaoMusica = false;
	bool botaoSair = false;

	InitWindow(largura_window, altura_window, "ping pong do LK");
	SetTargetFPS(60);	//seta a taxa de quadros por segundo (FPS) para 60

	while (WindowShouldClose() == false && botaoSair == false) {
		
		//while (true)
		//{
		//	Menu(largura_window, altura_window);
		//}


		// struct dos retangulos CPU e do jogador
		Rectangle retanguloPlayer{
			retanguloJogadorPosicao.x,
			retanguloJogadorPosicao.y,
			retanguloJogadorTamanho.x,
			retanguloJogadorTamanho.y
		};

		Rectangle retanguloCPU{
			retanguloCpuPosicao.x,
			retanguloCpuPosicao.y,
			retanguloCpuTamanho.x,
			retanguloCpuTamanho.y
		};

		//atribuição da velocidade do circulo
		circulo.x += velocidade.x;
		circulo.y += velocidade.y;

		//colisoão da bola com o retangulo jogador
		bool colisaoRec = false;

		// sistema de movimentação do jogador

		if (retanguloJogadorPosicao.y <= 0) {
			alturaMaxima = false;
		}
		else {
			alturaMaxima = true;
		};

		if (alturaMaxima) {
			if (IsKeyDown(KEY_W)) {
				retanguloJogadorPosicao.y -= 5;
			};
		}

		if (retanguloJogadorPosicao.y + retanguloJogadorTamanho.y >= altura_window ) {
			alturaMinima = false;
		}
		else {
			alturaMinima = true;
		};

		if (alturaMinima) {
			if (IsKeyDown(KEY_S)) {
				retanguloJogadorPosicao.y += 5;
			};
		}

		// sistema de movimentação da IA


		if (retanguloCpuPosicao.y > (circulo.y) - 20) {
			retanguloCpuPosicao.y -= 4.0;

		}

		if (retanguloCpuPosicao.y < (circulo.y - 100)) {
			retanguloCpuPosicao.y += 4.0;

		}

		if (exibirMensagemPerda || exibirMensagemGanho) {
			cronometro += GetFrameTime();

			if (cronometro >= tempoDeMensagem) {
				exibirMensagemPerda = false;
				exibirMensagemGanho = false;
				cronometro = 0;
			}
		}

		if (exibirMensagemPerda) {
			DrawText("voce perdeu ponto", (largura_window / 2) - 200, 190, 50, RED);
		}

		if (exibirMensagemGanho) {
			DrawText("voce fez ponto", (largura_window / 2) - 200, 190, 50, GREEN);
		};

		//mensagem na tela da pontuação do jogador e da maquina

		DrawText(TextFormat("Ponto: %d", pontosJogador), 100, 50, 30, WHITE);
		DrawText(TextFormat("Ponto: %d", pontosCPU), largura_window - 200, 50, 30, WHITE);


		//sistema de colisão da bola com o jogador

		bool colisaoAtual = CheckCollisionCircleRec(circulo, circulo_raio, retanguloPlayer);

		if (colisaoAtual && !colisaoRec) {

			float centro = retanguloJogadorPosicao.y + 50;
			float offset = (circulo.y - centro) / 50;

			velocidade.y = offset * 6;
			velocidade.x = fabs(velocidade.x) * 1.125f;
			if (velocidade.x > 20) {
				velocidade.x = 12.5f;
			}
		}

		colisaoRec = colisaoAtual;

		//colisão da bola com a CPU

		bool colisaoIAAtual = CheckCollisionCircleRec(circulo, circulo_raio, retanguloCPU);

		if (colisaoIAAtual && !colisaoIARec) {

			float centro = retanguloCPU.y + 50;
			float offset = (circulo.y - centro) / 50;

			velocidade.y = offset * 6;
			velocidade.x = -fabs(velocidade.x) * 1.125f;
			if (velocidade.x > 20) {
				velocidade.x = 12.5f;
			}
		}

		colisaoIARec = colisaoIAAtual;

		//colisão da bola com as paredes

		if (circulo_raio + circulo.x >= largura_window || circulo.x - circulo_raio <= 0) {

			if (circulo.x - circulo_raio <= 0) {
				pontosCPU++;
				exibirMensagemPerda = true;
				circulo.x = circulo_raio;
				velocidade.x *= -1;
			}

			if (circulo.x + circulo_raio >= largura_window) {
				pontosJogador++;
				exibirMensagemGanho = true;
				circulo.x = largura_window - circulo_raio;
				velocidade.x *= -1;
			}
			cout << "velocidade X: " << velocidade.x << endl;
		};

		if (circulo_raio + circulo.y >= altura_window || circulo.y - circulo_raio <= 0) {
			velocidade.y *= -1;
			cout << "velocidade Y: " << velocidade.y << endl;
		};

		BeginDrawing();

		ClearBackground(DARKGREEN);

		// todas as linhas do campo
		DrawCircleLines(largura_window/2, altura_window/2, 120, WHITE);
		DrawLine(largura_window/2, 35, largura_window/2, 565, WHITE);
		DrawLine(55, 35, largura_window - 55, 35, WHITE);
		DrawLine(55, 565, largura_window - 55, 565, WHITE);
		DrawLine(55, 35, 55, 565, WHITE);
		DrawLine(largura_window - 55, 35, largura_window - 55, 565, WHITE);

		//retangulo CPU
		DrawRectangleV(retanguloCpuPosicao, retanguloCpuTamanho, DARKBLUE);

		//retangulo jogador
		DrawRectangleV(retanguloJogadorPosicao, retanguloJogadorTamanho, DARKBLUE);

		// bola de ping pong
		DrawCircleV(circulo, circulo_raio, WHITE);

		EndDrawing();
	}
	CloseWindow();
	return 0;
};