/********************************************************************
  Bot-exemplo

  Após receber as informações iniciais do jogo, a cada rodada esse
  bot irá se movimentar para esquerda.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_STR 50

int limite_barco = 0;

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int v[h][w], char myId[MAX_STR], int *myX, int *myY)
{
	char id[MAX_STR];
	int n, x, y;
	int v[h][w];

	// lê os dados da área de pesca
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			scanf("%i", &v[i][j]);
		}
	}
	// lê os dados dos bots
	scanf(" BOTS %i", &n);
	// o " " antes de BOTS é necessário para ler o '\n' da linha anterior
	for (int i = 0; i < n; i++)
	{
		scanf("%s %i %i", id, &x, &y);
		if (strcmp(id, myId) == 0)
		{
			myX = x;
			myY = y;
		}
	}
}

void ir_ao_porto(int h, int w, int v[h][w], int myX, int myY)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			
		}
	}
	
}

int main()
{
	char line[MAX_STR]; // dados temporários
	char myId[MAX_STR]; // identificador do bot em questão

	setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
	setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
	setbuf(stderr, NULL);

	// === INÍCIO DA PARTIDA ===
	int h, w;
	scanf("AREA %i %i", &h, &w); // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);		 // ...e o id do bot
	// obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

	// Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
	// Esse dado não será enviado para o simulador, apenas para o terminal.
	// A linha seguinte é um exemplo. Pode removê-la se desejar.
	fprintf(stderr, "Meu id = %s\n", myId);

	// === PARTIDA ===
	// O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
	// o processo quando o jogo terminar.
	while (1)
	{
		int v[h][w];
		int myX, myY;

		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		readData(h, w, v, myId, &myX, &myY);

		// INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
		if (limite_barco == 10)
		{
			ir_ao_porto();
		}
		else
		{
			buscar_area_pesca();
		}

		// envia a ação escolhida (nesse exemplo, ir para esquerda)
		printf("LEFT\n");

		// lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
		scanf("%s", line);
	}

	return 0;
}