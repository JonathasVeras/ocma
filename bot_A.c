/********************************************************************
  Bot-exemplo

  Após receber as informações iniciais do jogo, a cada rodada esse
  bot irá se movimentar para esquerda.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_STR 50

typedef struct coordenada
{
	int x;
	int y;
	int quant;
}Coordenada;

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
int tenho_area_de_pesca = 0;
Coordenada coordenadas_marcadas[1000];
int contador_marcadas = 0;

int checar_coordenada_com_marcadas(int x, int y);
/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int h, int w, int mapa[h][w], char myId[MAX_STR], int *myX, int *myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], Porto portos[100], int *contadorRobalo, int *contadorCioba, int *contadorTainha, int *contadorPorto)
{
	//h=ALTURA e w=LARGURA
	char id[MAX_STR];
	int n, x, y;
	*contadorRobalo=0;
	*contadorCioba=0;
	*contadorTainha=0;
	*contadorPorto=0;
	// lê os dados da área de pesca
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			scanf("%i", &mapa[i][j]);
			if(mapa[i][j] > 1)
			{
				if((int)(mapa[i][j]/10) == 1){//Tainha
					tainha[*contadorTainha].x=i;
					tainha[*contadorTainha].y=j;
					tainha[*contadorTainha].quant=(int)(mapa[i][j]%10);
					contadorTainha++;
				}
				if((int)(mapa[i][j]/10) == 2){//Cioba
					cioba[*contadorCioba].x=i;
					cioba[*contadorCioba].y=j;
					cioba[*contadorCioba].quant=(int)(mapa[i][j]%10);
					contadorCioba++;
					fprintf(stderr, "cioba: %d\n", *contadorCioba);
				}
				if((int)(mapa[i][j]/10) == 3){//Robalo
					robalo[*contadorRobalo].x=i;
					robalo[*contadorRobalo].y=j;
					robalo[*contadorRobalo].quant=(int)(mapa[i][j]%10);
					contadorRobalo++;
				}
			}
			else if (mapa[i][j] == 1 && primeiraChecagem) //Info dos portos.
			{
				portos[*contadorPorto].x == i;
				portos[*contadorPorto].y == j;
				contadorPorto++;
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
			*myX = x;
			*myY = y;
		}
	}
	primeiraChecagem==0;
}

Coordenada buscar_area_pesca(int altura, int largura, int mapa[altura][largura], int myX, int myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], int contadorRobalo, int contadorCioba, int contadorTainha);

int produto_vetorial(int xBarco, int yBarco, int xPeixe, int yPeixe);

void mover(int xBarco, int yBarco, int *quant_peixe, int xLocal, int yLocal, int *estou_no_local, int porto_ou_pesca);

Coordenada achar_porto(int h, int w, int v[h][w], int myX, int myY, Porto portos[100], int contadorPorto);

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
	int contadorRobalo=0, contadorCioba=0, contadorTainha=0, contadorPorto=0;
	Coordenada indoPraLa;
	int estou_em_area_de_pesca = 0;
	int estou_no_porto = 0;
	int tenho_porto = 0;
	// === INÍCIO DA PARTIDA ===
	scanf("AREA %i %i", &altura, &largura); // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);		 // ...e o id do bot
	// obs: o " " antes de ID é necessário para ler o '\n' da linha anterior
	int mapa[altura][largura];
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
		fprintf(stderr, "limite barco %d\n", limite_barco);

		// LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
		readData(altura, largura, mapa, myId, &myX, &myY, robalo, cioba, tainha, portos, &contadorRobalo, &contadorCioba, &contadorTainha, &contadorPorto);
		fprintf(stderr, "POSICAO DO BARCO = myX: %d e myY: %d\n", myX, myY);
		// INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
		if (limite_barco == 10)
		{
			estou_em_area_de_pesca=0;
			tenho_area_de_pesca=0;
			if (tenho_porto == 0)
			{
				indoPraLa = achar_porto(largura,altura, mapa, myX, myY, portos, contadorPorto);
				mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_no_porto, 1);
			}
			else
			{
				mover(myX, myY,&indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_no_porto, 1);
			}
			
		}
		else if(estou_em_area_de_pesca==0)
		{
			if (tenho_area_de_pesca==0)
			{
				indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
				fprintf(stderr, "destino X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				fprintf(stderr, "quantidade de peixe precoce %d\n", indoPraLa.quant);
				mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
				tenho_area_de_pesca=1;
			}
			else
			{
				mover(myX, myY,&indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
			}

		}
		else
		{
			if(indoPraLa.quant >1)
			{
				indoPraLa.quant--;
				fprintf(stderr, "quantidade de peixe %d\n", indoPraLa.quant);
				printf("FISH\n");
				fprintf(stderr, "Pescando1\n");
				limite_barco++;
			}
			else{
				fprintf(stderr, "PAREI DE PESCAR1\n");
				tenho_area_de_pesca=0;
				estou_em_area_de_pesca=0;
				indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
				fprintf(stderr, "destino X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				fprintf(stderr, "quantidade de peixe precoce %d\n", indoPraLa.quant);
				mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
				tenho_area_de_pesca=1;
			}
		}

		// lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
		scanf("%s", line);
	}

	return 0;
}

int produto_vetorial(int xBarco, int yBarco, int xPeixe, int yPeixe)
{
	return((xBarco+xPeixe)*(xBarco+xPeixe))-((yBarco+yPeixe)*(yBarco+yPeixe));
}

void mover(int xBarco, int yBarco, int *quant_peixe, int xLocal, int yLocal, int *estou_no_local, int porto_ou_pesca)
{
	if (xBarco != xLocal || yBarco != yLocal)
	{
		if (xBarco>xLocal)
		{
			fprintf(stderr, "Barco indo para %d, %d\n", xBarco-1, yBarco);
			fprintf(stderr, "UP\n");
			printf("UP\n");
		}
		else if (xBarco<xLocal)
		{
			fprintf(stderr, "Barco indo para %d, %d\n", xBarco+1, yBarco);
			fprintf(stderr, "DOWN\n");
			printf("DOWN\n");
		}
		else
		{
			if (yBarco>yLocal)
			{
				fprintf(stderr, "Barco indo para %d, %d\n", xBarco, yBarco-1);
				fprintf(stderr, "LEFT\n");
				printf("LEFT\n");
			}
			else
			{
				fprintf(stderr, "Barco indo para %d, %d\n", xBarco, yBarco+1);
				fprintf(stderr, "RIGHT\n");
				printf("RIGHT\n");
			}
			
		}
		
	}
	else
	{
		*estou_no_local = 1;
		if(porto_ou_pesca == 0)//pesca
		{
			if(*quant_peixe >1)
			{
				limite_barco++;
				*quant_peixe = *quant_peixe-1;
				fprintf(stderr, "quantidade de peixe %d\n", *quant_peixe);
				printf("FISH\n");
				fprintf(stderr, "Pescando\n");
				
			}
			else{
				fprintf(stderr, "PAREI DE PESCAR2\n");
				tenho_area_de_pesca=0;
				*estou_no_local=0;
			}
		}
		else
		{
			printf("SELL\n");	
			limite_barco=0;
		}
	}
	
}

Coordenada achar_porto(int h, int w, int v[h][w], int myX, int myY, Porto portos[100], int contadorPorto)
{
	Coordenada coordenada_buscada;
	Porto maisProximoPorto=portos[0];
	int pV_do_mais_proximo = produto_vetorial(myX, myY, portos[0].x, portos[0].y);
	for (size_t i = 1; i < contadorPorto; i++)
	{
		int pVatual = produto_vetorial(myX, myY, portos[i].x, portos[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			maisProximoPorto = portos[i];
			pV_do_mais_proximo = pVatual;
		}
	}
	coordenada_buscada.x = maisProximoPorto.x;
	coordenada_buscada.y = maisProximoPorto.y;
	return coordenada_buscada;
}

Coordenada buscar_area_pesca(int altura, int largura, int mapa[altura][largura], int myX, int myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], int contadorRobalo, int contadorCioba, int contadorTainha)
{
	for (size_t i = 0; i < contador_marcadas; i++)
	{
		fprintf(stderr, "Coordenada marcada: X:%d Y:%d\n", coordenadas_marcadas[i].x, coordenadas_marcadas[i].y);
	}
	
	Coordenada coordenada_buscada;
	//Nesse algoritmo os "maisProximoCioba, etc" serão achados para ser feita uma comparação depois de qual está mais perto.
	Cioba maisProximoCioba=cioba[0];
	int pV_do_mais_proximo = produto_vetorial(myX, myY, cioba[0].x, cioba[0].y);
	for (size_t i = 1; i < contadorCioba; i++)
	{
		int pVatual = produto_vetorial(myX, myY, cioba[i].x, cioba[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			fprintf(stderr, "oi1\n");
			fprintf(stderr, "(%d)\n", checar_coordenada_com_marcadas(cioba[i].x, cioba[i].y));
			if (checar_coordenada_com_marcadas(cioba[i].x, cioba[i].y)==0)
			{
				maisProximoCioba = cioba[i];
				pV_do_mais_proximo = pVatual;
			}
		}
	}
	int pV_do_Cioba_mais_proximo = pV_do_mais_proximo;

	Robalo maisProximoRobalo=robalo[0];
	pV_do_mais_proximo = produto_vetorial(myX, myY, robalo[0].x, robalo[0].y);
	for (size_t i = 1; i < contadorRobalo; i++)
	{
		int pVatual = produto_vetorial(myX, myY, robalo[i].x, robalo[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			fprintf(stderr, "oi2\n");
			fprintf(stderr, "(r:%d)\n", checar_coordenada_com_marcadas(robalo[i].x, robalo[i].y));
			if (checar_coordenada_com_marcadas(robalo[i].x, robalo[i].y)==0)
			{
				maisProximoRobalo = robalo[i];
				pV_do_mais_proximo = pVatual;
			}
		}
	}
	int pV_do_Robalo_mais_proximo = pV_do_mais_proximo;
	
	Tainha maisProximoTainha=tainha[0];
	pV_do_mais_proximo = produto_vetorial(myX, myY, tainha[0].x, tainha[0].y);
	for (size_t i = 1; i < contadorTainha; i++)
	{
		int pVatual = produto_vetorial(myX, myY, tainha[i].x, tainha[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			fprintf(stderr, "oi3\n");
			fprintf(stderr, "(t:%d)\n", checar_coordenada_com_marcadas(tainha[i].x, tainha[i].y));
			if (checar_coordenada_com_marcadas(tainha[i].x, tainha[i].y)==0)
			{
				maisProximoTainha = tainha[i];
				pV_do_mais_proximo = pVatual;
			}
		}
	}
	int pV_da_Tainha_mais_proximo = pV_do_mais_proximo;
	//========================================================
	//Achando definitivamente a coordenada que meu barco deve ir para ir pescar.
	if(pV_da_Tainha_mais_proximo <= pV_do_Cioba_mais_proximo && pV_da_Tainha_mais_proximo <= pV_do_Robalo_mais_proximo)
	{
		coordenada_buscada.x = maisProximoTainha.x;
		coordenada_buscada.y = maisProximoTainha.y;
		coordenada_buscada.quant = maisProximoTainha.quant;
	}
	else if (pV_do_Cioba_mais_proximo <= pV_da_Tainha_mais_proximo && pV_do_Cioba_mais_proximo <= pV_do_Robalo_mais_proximo)
	{
		coordenada_buscada.x = maisProximoCioba.x;
		coordenada_buscada.y = maisProximoCioba.y;
		coordenada_buscada.quant = maisProximoCioba.quant;
	}
	else{
		coordenada_buscada.x = maisProximoRobalo.x;
		coordenada_buscada.y = maisProximoRobalo.y;
		coordenada_buscada.quant = maisProximoRobalo.quant;
	}
	coordenadas_marcadas[contador_marcadas] = coordenada_buscada;
	contador_marcadas++;
	return coordenada_buscada;
}
int checar_coordenada_com_marcadas(int x, int y)
{
	for (size_t i = 0; i < contador_marcadas; i++)
	{
		if (x==coordenadas_marcadas[i].x && y==coordenadas_marcadas[i].y)
		{
			return 1;
		}
	}
	return 0;
}