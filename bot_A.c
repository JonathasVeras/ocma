/********************************************************************
  Bot-exemplo

  Após receber as informações iniciais do jogo, a cada rodada esse
  bot irá se movimentar para esquerda.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_STR 50

typedef struct robalo
{
	int x;
	int y;
	int quant;
}Robalo;

typedef struct cioba
{
	int x;
	int y;
	int quant;
}Cioba;

typedef struct tainha
{
	int x;
	int y;
	int quant;
}Tainha;
typedef struct porto
{
	int x;
	int y;
}Porto;

int limite_barco = 0;
int primeiraChecagem = 1;

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int v[h][w], char myId[MAX_STR], int *myX, int *myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], Porto portos[100])
{
	//h=ALTURA e w=LARGURA
	char id[MAX_STR];
	int n, x, y;
	int v[h][w];
	int contadorRobalo=0, contadorCioba=0, contadorTainha=0, contadorPorto=0;
	// lê os dados da área de pesca
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			scanf("%i", &v[i][j]);
			if(v[i][j] > 1)
			{
				if((int)(v[i][j]/10) == 1){//Tainha
					tainha[contadorTainha].x=i;
					tainha[contadorTainha].y=j;
					tainha[contadorTainha].quant=(int)(v[i][j]%10);
				}
				if((int)(v[i][j]/10) == 2){//Cioba
					cioba[contadorCioba].x=i;
					cioba[contadorCioba].y=j;
					cioba[contadorCioba].quant=(int)(v[i][j]%10);
				}
				if((int)(v[i][j]/10) == 3){//Robalo
					robalo[contadorRobalo].x=i;
					robalo[contadorRobalo].y=j;
					robalo[contadorRobalo].quant=(int)(v[i][j]%10);
				}
			}
			else if (v[i][j] == 1 && primeiraChecagem) //Info dos portos.
			{
				portos[contadorPorto].x == i;
				portos[contadorPorto].y == j;
				primeiraChecagem==0;
			}
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

void buscar_area_pesca(int altura, int largura, int v[altura][largura], int myX, int myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], Porto portos[100])
{

}

int produto_vetorial(int xBarco, int yBarco, int xPeixe, int yPeixe)
{
	return((xBarco+xPeixe)*(xBarco+xPeixe))-((yBarco+yPeixe)*(yBarco+yPeixe));
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
	Robalo robalo[100];
	Cioba cioba[100];
	Tainha tainha[100];
	Porto portos[100];
	int altura, largura;
	// === INÍCIO DA PARTIDA ===
	scanf("AREA %i %i", &altura, &largura); // lê a dimensão da área de pesca: altura (h) x largura (w)
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
		int v[altura][largura];
		int myX, myY;

		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		readData(altura, largura, v, myId, &myX, &myY, robalo, cioba, tainha, portos);

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