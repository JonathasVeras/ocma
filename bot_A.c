/********************************************************************
  gcc -o bot_A bot_A.c
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
int tenho_porto = 0;
Coordenada coordenadas_marcadas[1000];
int contador_marcadas = 0;
Coordenada bots[1000];
int contador_bots = 0;
int altura_do_mundo;
int largura_do_mundo;

int checar_coordenada_com_marcadas(int x, int y);
int checar_outros_bots(int x, int y);

void readData(int h, int w, int mapa[h][w], char myId[MAX_STR], int *myX, int *myY, Robalo robalo[100], Cioba cioba[100], Tainha tainha[100], Porto portos[100], int *contadorRobalo, int *contadorCioba, int *contadorTainha, int *contadorPorto)
{
	//h=ALTURA e w=LARGURA
	char id[MAX_STR];
	int n, x, y;
	*contadorRobalo=0;
	*contadorCioba=0;
	*contadorTainha=0;
	*contadorPorto=0;
	contador_bots=0;
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
					tainha[*contadorTainha].quant=mapa[i][j]%10;
					*contadorTainha = *contadorTainha + 1;
				}
				if((int)(mapa[i][j]/10) == 2){//Cioba
					cioba[*contadorCioba].x=i;
					cioba[*contadorCioba].y=j;
					cioba[*contadorCioba].quant=mapa[i][j]%10;
					*contadorCioba = *contadorCioba + 1;
					//fprintf(stderr, "cioba: %d\n", *contadorCioba);
				}
				if((int)(mapa[i][j]/10) == 3){//Robalo
					robalo[*contadorRobalo].x=i;
					robalo[*contadorRobalo].y=j;
					robalo[*contadorRobalo].quant=mapa[i][j]%10;
					*contadorRobalo = *contadorRobalo + 1;
				}
			}
			else if (mapa[i][j] == 1 && primeiraChecagem) //Info dos portos.
			{
				portos[*contadorPorto].x = i;
				portos[*contadorPorto].y = j;
				*contadorPorto = *contadorPorto + 1;
			}
		}
	}
	// lê os dados dos bots
	scanf(" BOTS %i", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s %i %i", id, &x, &y);
		if (strcmp(id, myId) == 0)
		{
			*myX = x;
			*myY = y;
		}
		else
		{
			bots[contador_bots].x = x;
			bots[contador_bots].y = y;
			contador_bots++;
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
	// === INÍCIO DA PARTIDA ===
	scanf("AREA %i %i", &altura, &largura); // lê a dimensão da área de pesca: altura (h) x largura (w)
	scanf(" ID %s", myId);		 // ...e o id do bot
	altura_do_mundo=altura;
	largura_do_mundo=largura;
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
		fprintf(stderr, "\n\nlimite barco: %d\n\n", limite_barco);
		fprintf(stderr, "POSICAO DO BARCO = myX: %d e myY: %d\n", myX, myY);
		fprintf(stderr, "estou em area pesca: %d\n", estou_em_area_de_pesca);
		// INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA
		if (limite_barco == 10)
		{
			fprintf(stderr,"DEVO VOLTAR PRA VENDER\n");
			estou_em_area_de_pesca=0;
			tenho_area_de_pesca=0;
			if (tenho_porto == 0)
			{
				indoPraLa = achar_porto(largura,altura, mapa, myX, myY, portos, contadorPorto);
				fprintf(stderr, "destino[PORTO] X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_no_porto, 1);
				tenho_porto=1;
			}
			else
			{
				fprintf(stderr, "destino[PORTO] X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				mover(myX, myY,&indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_no_porto, 1);
			}
			
		}
		else if(estou_em_area_de_pesca==0)
		{
			if (tenho_area_de_pesca==0)
			{
				fprintf(stderr, "ola mundo\n");
				indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
				while(indoPraLa.quant==1)
				{
					indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
				}
				fprintf(stderr, "destino[PESCA] X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				fprintf(stderr, "quantidade de peixe precoce %d\n", indoPraLa.quant);
				if(indoPraLa.quant > 1)
				{
					mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
					tenho_area_de_pesca=1;
				}
			}
			else
			{
				fprintf(stderr, "ola mundo2\n");
				if(indoPraLa.quant > 1)
				{
					mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
					tenho_area_de_pesca=1;
				}
			}

		}
		else
		{
			if(indoPraLa.quant >1)
			{
				indoPraLa.quant--;
				fprintf(stderr, "quantidade de peixe %d\n", indoPraLa.quant);
				limite_barco++;
				printf("FISH\n");
				fprintf(stderr, "Pescando1\n");
			}
			else{
				fprintf(stderr, "PAREI DE PESCAR1\n");
				tenho_area_de_pesca=0;
				estou_em_area_de_pesca=0;
				indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
				while(indoPraLa.quant==1)
				{
					indoPraLa = buscar_area_pesca(altura, largura, mapa, myX, myY, robalo, cioba, tainha, contadorRobalo, contadorCioba, contadorTainha);
					fprintf(stderr, "coordenada bugada: x:%d y:%d\n", indoPraLa.x, indoPraLa.y);
				}
				fprintf(stderr, "destino[PESCA] X: %d e Y: %d\n", indoPraLa.x, indoPraLa.y);
				fprintf(stderr, "quantidade de peixe precoce %d\n", indoPraLa.quant);
				if(indoPraLa.quant > 1)
				{
					mover(myX, myY, &indoPraLa.quant, indoPraLa.x, indoPraLa.y, &estou_em_area_de_pesca, 0);
					tenho_area_de_pesca=1;
				}
				
			}
		}

		// lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
		scanf("%s", line);
	}

	return 0;
}

int produto_vetorial(int xBarco, int yBarco, int xPeixe, int yPeixe)
{
	return((xBarco-xPeixe)*(xBarco-xPeixe))+((yBarco-yPeixe)*(yBarco-yPeixe));
}

void mover(int xBarco, int yBarco, int *quant_peixe, int xLocal, int yLocal, int *estou_no_local, int porto_ou_pesca)
{
	if (xBarco != xLocal || yBarco != yLocal)
	{
		if (xBarco>xLocal)
		{
			if (checar_outros_bots( xBarco-1, yBarco)==0) //tem barco acima
			{
				if (checar_beira_mundo(xBarco-1, yBarco)) //se for true não sai do mapa
				{
					printf("LEFT\n");
				}
				else
				{
					printf("RIGHT\n");
				}
				
			}
			
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
				Coordenada indoPraLa;
				fprintf(stderr, "PAREI DE PESCAR2\n");
				tenho_area_de_pesca=0;
				*estou_no_local=0;
			}
		}
		else
		{
			printf("SELL\n");	
			limite_barco=0;
			tenho_porto=0;
			tenho_area_de_pesca=0;
			*estou_no_local=0;
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
		if (pVatual <= pV_do_mais_proximo && checar_outros_bots(portos[i].x, portos[i].y)==0)
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
	/*for (size_t i = 0; i < contador_marcadas; i++)
	{
		fprintf(stderr, "Coordenada marcada: X:%d Y:%d\n", coordenadas_marcadas[i].x, coordenadas_marcadas[i].y);
	}*/
	Coordenada coordenada_buscada;
	//Nesse algoritmo os "maisProximoCioba, etc" serão achados para ser feita uma comparação depois de qual está mais perto.
	Cioba maisProximoCioba=cioba[0];
	int pV_do_mais_proximo = produto_vetorial(myX, myY, cioba[0].x, cioba[0].y);
	for (size_t i = 0; i < contadorCioba; i++)
	{
		int pVatual = produto_vetorial(myX, myY, cioba[i].x, cioba[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			//fprintf(stderr, "oi1\n");
			//fprintf(stderr, "(%d)\n", checar_coordenada_com_marcadas(cioba[i].x, cioba[i].y));
			/*if (checar_coordenada_com_marcadas(cioba[i].x, cioba[i].y)==0)
			{
				maisProximoCioba = cioba[i];
				pV_do_mais_proximo = pVatual;
			}*/
			if(cioba[i].quant>1)
			{
				maisProximoCioba = cioba[i];
				pV_do_mais_proximo = pVatual;
			}
		}
	}
	fprintf(stderr,"Cioba: %d\n", maisProximoCioba.quant);
	int pV_do_Cioba_mais_proximo = pV_do_mais_proximo;

	Robalo maisProximoRobalo=robalo[0];
	pV_do_mais_proximo = produto_vetorial(myX, myY, robalo[0].x, robalo[0].y);
	for (size_t i = 1; i < contadorRobalo; i++)
	{
		int pVatual = produto_vetorial(myX, myY, robalo[i].x, robalo[i].y);
		if (pVatual <= pV_do_mais_proximo)
		{
			//fprintf(stderr, "oi2\n");
			//fprintf(stderr, "(r:%d)\n", checar_coordenada_com_marcadas(robalo[i].x, robalo[i].y));
			/*if (checar_coordenada_com_marcadas(robalo[i].x, robalo[i].y)==0)
			{
				maisProximoRobalo = robalo[i];
				pV_do_mais_proximo = pVatual;
			}*/
			if (robalo[i].quant>1)
			{
				maisProximoRobalo = robalo[i];
				pV_do_mais_proximo = pVatual;
			}
		}
	}
	fprintf(stderr,"robalo: %d\n", maisProximoRobalo.quant);
	int pV_do_Robalo_mais_proximo = pV_do_mais_proximo;
	
	Tainha maisProximoTainha=tainha[0];
	pV_do_mais_proximo = produto_vetorial(myX, myY, tainha[0].x, tainha[0].y);
	for (size_t i = 1; i < contadorTainha; i++)
	{
		int pVatual = produto_vetorial(myX, myY, tainha[i].x, tainha[i].y);
		if (pVatual <= pV_do_mais_proximo && tainha[i].quant>1)
		{
			//fprintf(stderr, "oi3\n");
			//fprintf(stderr, "(t:%d)\n", checar_coordenada_com_marcadas(tainha[i].x, tainha[i].y));
			/*if (checar_coordenada_com_marcadas(tainha[i].x, tainha[i].y)==0)
			{
				maisProximoTainha = tainha[i];
				pV_do_mais_proximo = pVatual;
			}*/
			maisProximoTainha = tainha[i];
			pV_do_mais_proximo = pVatual;
		}
	}
	fprintf(stderr,"Tainha: %d\n", maisProximoTainha.quant);
	int pV_da_Tainha_mais_proximo = pV_do_mais_proximo;
	//========================================================
	//Achando definitivamente a coordenada que meu barco deve ir para ir pescar.
	if (maisProximoRobalo.quant > 1 && checar_outros_bots(maisProximoRobalo.x, maisProximoRobalo.y)==0){
		coordenada_buscada.x = maisProximoRobalo.x;
		coordenada_buscada.y = maisProximoRobalo.y;
		coordenada_buscada.quant = maisProximoRobalo.quant;
	}
	else if (maisProximoCioba.quant > 1 && checar_outros_bots(maisProximoCioba.x, maisProximoCioba.y)==0)
	{
		coordenada_buscada.x = maisProximoCioba.x;
		coordenada_buscada.y = maisProximoCioba.y;
		coordenada_buscada.quant = maisProximoCioba.quant;
	}
	else if(maisProximoTainha.quant > 1 && checar_outros_bots(maisProximoTainha.x, maisProximoTainha.y)==0)
	{
		coordenada_buscada.x = maisProximoTainha.x;
		coordenada_buscada.y = maisProximoTainha.y;
		coordenada_buscada.quant = maisProximoTainha.quant;
	}
	coordenadas_marcadas[contador_marcadas] = coordenada_buscada;
	contador_marcadas++;
	return coordenada_buscada;
}
int checar_coordenada_com_marcadas(int x, int y)
{
	/*
	Se for 0 é porque elas não são iguais.
	*/
	for (size_t i = 0; i <= contador_marcadas; i++)
	{
		if (x==coordenadas_marcadas[i].x && y==coordenadas_marcadas[i].y)
		{
			return 1;
		}
	}
	return 0;
}
int checar_outros_bots(int x, int y)
{
	/*
	Se for 0 é porque elas não são iguais e estão no mesmo local.
	*/
	for (size_t i = 0; i <= contador_bots; i++)
	{
		if (x==bots[i].x && y==bots[i].y)
		{
			return 1;
		}
	}
	return 0;
}

int checar_beira_mundo(int x, int y)
{
	/*
	Return 1 = Não sai do mapa
	Return 0 = Sai do mapa 
	*/
	if(x<0 || y<0)
	{
		return 0;
	}
	else
	{
		if(x>largura_do_mundo || y>altura_do_mundo)
		{
			return 0;
		}
	}
	return 1;
}