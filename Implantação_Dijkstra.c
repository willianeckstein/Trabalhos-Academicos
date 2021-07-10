//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

//Vari�veis globais
int vertices = 0, *custos = NULL, origem, destino, custo;

//Prototipa��o da fun��es
void menu(void);
void criaGrafo(void);
void calcularRotas(void);
void dijkstra(int vertices, int origem, int destino, int *custos);

//Fun��o principal
int main() {
	setlocale(LC_ALL, "Portuguese");
	int opt = -1;
	//La�o de op��es do menu
	do {
		menu();
		scanf("%d", &opt);
		switch(opt) {
			case 1 :
				//Insere a quantidade de v�rtices
				criaGrafo();
			break;
			case 2 :
				//Calcular rotas
				calcularRotas();
			break;
		}
	} while (opt != 0);
	printf("\nSistema finalizado...\n\n");
	return(0);
}

void menu(void) {
	system("cls");
	printf("------ Dijkstra ------\n\n");
	printf("Op��es do sistema:\n\n");
	printf("\t 1 - Inserir as informa��es do grafo\n");
	printf("\t 2 - Calcular as rotas e imprimir os pesos\n");
	printf("\t 0 - Sair\n");
	printf("\nDigite a op��o desejada: ");
}

void criaGrafo(void) {
	//Setar o n�mero de v�rtices
	if(vertices == 0) {
		int num;
		system("cls");
		printf("------ Dijkstra ------\n\n");
		printf("\nDigite o n�mero de v�rtices do grafo (5): ");
		scanf("%d", &num);
		if(num != 5) {
			do{
				printf("\nO n�mero de v�rtices deve ser 5!\n");
				printf("Digite novamente: ");
				scanf("%d", &num);
			} while(num != 5);
		} 	
		vertices = num;
		printf("\nN�mero de v�rtices atribu�do!\n");
		system("pause");	
	} else {
		system("cls");
		printf("------ Atividade MAPA - Estrutura de dados 1 - RA 20000514-5 ------\n\n");
		printf("\nA quantidade de v�rtices do grafo j� foi selecionada.\n");
		system("pause");
	}
	
	//Aloca��o dinamica para a matriz de custos
	if(!custos) {
		free(custos);
	}
	custos = (int *) malloc(sizeof(int) * vertices * vertices);
	if(custos == NULL) {
		system("color fc");
		printf("**Erro: Mem�ria insuficiente**");
		exit(-1);
	}
	
	//Preenchendo a matriz de custos
	int i;
	for(i = 0; i <= vertices * vertices; i++) {
		custos[i] = -1;
	}
	int opt = -1;
	do {
		system("cls");
		printf("------ Dijkstra ------\n\n");
		printf("\nEntre com as informa��es das arestas e seus custos: ");
		printf("\nAresta: ");
		printf("\nOrigem (Entre 1 e %d): ", vertices);
		scanf("%d", &origem);
		if(origem < 1 || origem > vertices) {
			do {
				printf("\nN�o existe o v�rtice %d!", origem);
				printf("\nDigite um v�rtice de origem v�lido entre 1 e %d: ", vertices);
				scanf("%d", &origem);
			} while (origem < 1 || origem > vertices);
		}
		printf("\nDestino (Entre 1 e %d, menos %d): ", vertices, origem);
		scanf("%d", &destino);
		do {
			if(destino == origem) {
				printf("\nDestino n�o pode ser igual a origem!");
				printf("\nDigite um valor diferente da origem (%d): ", origem);
				scanf("%d", &destino);
			} else if (destino < 1 || destino > 5) {
				printf("\nN�o existe o v�rtice %d!", destino);
				printf("\nDigite um v�rtice de origem v�lido entre 1 e %d: ", vertices);
				scanf("%d", &destino);
			}
		} while (destino == origem || destino < 1 || destino > 5);
		printf("\nCusto (Positivo) da rota do vertice %d ao %d: ", origem, destino);
		scanf("%d", &custo);
		if(custo < 0) {
			do {
				printf("\nCusto deve ser positivo!");
				printf("\nDigite um novo valor:");
				scanf("%d", &custo);
			} while(custo < 0);
		}
		if(custos[(origem - 1) * vertices + destino - 1] != -1) {
			int aux;
			printf("\nA aresta inserida j� possue o custo definido: %d", custos[(origem - 1) * vertices + destino - 1]);
			printf("\nDeseja atualizar pelo novo valor (%d)?", custo);
			printf("\nDigite 1 - sim e 0 - n�o: ");
			scanf("%d", &aux);
			if(aux == 1) {
				custos[(origem - 1) * vertices + destino - 1] = custo;
				printf("\nCusto da aresta atualizado com sucesso!");
				printf("\nDeseja inserir novo registro?");
				printf("\nDigite 1 - sim e 0 - n�o: ");
				scanf("%d", &opt);
			} else {
				printf("\nDeseja inserir novo registro?");
				printf("\nDigite 1 - sim e 0 - n�o: ");
				scanf("%d", &opt);
			}
		} else {
			custos[(origem - 1) * vertices + destino - 1] = custo;
			printf("\nAresta inserida com sucesso!");
			printf("\nDeseja inserir novo registro?");
			printf("\nDigite 1 - sim e 0 - n�o: ");
			scanf("%d", &opt);
		}		
	} while (opt);
}

void calcularRotas(void) {
	int i, j;
	system("cls");
	printf("------ Dijkstra ------\n\n");
	if (custos == NULL) {
		printf("\nGrafo n�o preenchido! Preencha as informa��es primeiro!\n");
		system("pause");
	} else {
		printf("Calculando as rotas com o algoritmo de Dijkstra...\n");
		//Executando Dijkstra na matriz
		for(i = 1; i <= vertices; i++) {
			for(j = 1; j <= vertices; j++) {
				dijkstra(vertices, i, j, custos);
			}
			printf("\n");
		}
		system("pause");
	}
}

void dijkstra(int vertices, int origem, int destino, int *custos) {
	int i, v, cont = 0;
	int *ant, *tmp;
	int *z; //vertices para os quais se conhece o caminho minimo
	double min;
	double dist[vertices]; //vetor com os custos dos caminhos
	//Aloca��o para as linhas da matriz
	ant = (int *) calloc(vertices, sizeof(int *));
	if(ant == NULL) {
		system("color fc");
		printf("**Erro: Memoria insuficiente **");
		exit(-1);
	}
	tmp = (int *) calloc(vertices, sizeof(int *));
	if(tmp == NULL) {
		system("color fc");
		printf("**Erro: Memoria insuficiente **");
		exit(-1);
	}
	z = (int *) calloc(vertices, sizeof(int *));
	if(z == NULL) {
		system("color fc");
		printf("**Erro: Memoria insuficiente **");
		exit(-1);
	}
	for(i = 0; i < vertices; i++) {
		if(custos[(origem - 1) * vertices + i] != -1) {
			ant[i] = origem - 1;
			dist[i] = custos[(origem - 1) * vertices + i];
		} else {
			ant[i] = -1;
			dist[i] = HUGE_VAL;
		}
		z[i] = 0;
	}
	z[origem - 1] = 1;
	dist[origem - 1] = 0;
	//La�o principal
	do {
		//Encontrando o vertice que deve entrar em z
		min = HUGE_VAL;
		for(i = 0; i < vertices; i++) {
			if(!z[i]) {
				if(dist[i] >= 0 && dist[i] < min) {
					min = dist[i];
					v = i;
				}
			}
		}
		//Calculando as distancias dos novos vizinhos de z
		if(min != HUGE_VAL && v != (destino -1)) {
			z[v] = 1;
			for(i = 0; i < vertices; i++) {
				if(!z[i]) {
					if(custos[v * vertices + i] != -1 && (dist[v] + custos[v * vertices + i]) < dist[i]) {
						dist[i] = dist[v] + custos[v * vertices + i];
						ant[i] = v;
					}
				}
			}
		}
	} while(v != (destino - 1) && min != HUGE_VAL);
	
	//Mostra os resultados da busca
	printf("\tDe %d para %d: \t", origem, destino);
	if(min == HUGE_VAL) {
		printf("Nao existe\n");
		printf("\tCusto: \t- \n");
	} else {
		i = destino;
		i = ant[i - 1];
		while(i != -1) {
			tmp[cont] = i+1;
			cont++;
			i = ant[i];
		}
		for(i = cont; i > 0; i--) {
			printf("%d -> ", tmp[i - 1]);
		}
		printf("%d", destino);
		printf("\n\tCusto: %d\n", (int) dist[destino - 1]);
	}
}
