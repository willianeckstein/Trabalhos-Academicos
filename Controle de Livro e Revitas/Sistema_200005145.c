#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX 100

typedef struct cadastro{
	int tipo;
    char titulo[100];
    int edicao;
    char nomeAutor[100];
    char editora[50];
    char cod[50];
    int qtdExemp;
    int caixa;
    int ano;
}obra;

int i = 0;

void cadastrarObra(obra obras[]);
void listarLivros(obra obras[]);
void listarRevistas(obra obras[]);
void listarCaixas(obra obras[]);
int lerArquivo(obra obras[]);

int main(void) {
    setlocale(LC_ALL,"Portuguese");
    obra obras[MAX];
    int op;
    char resp;
    
    printf("------------------------------------------------------------------\n");
    printf(">>> Willian Francisco Eckstein <<<\n");
    printf(">>> RA: 20000514-5 <<<\n");
    printf(">>> Engenharia de Software <<<\n");
    printf("------------------------------------------------------------------\n");
    system("pause");
    
    do{
    	system("cls");
    	printf(">>> MENU <<<\n");
        printf("\n1 - Cadastrar novo exemplar");
        printf("\n2 - Listar todos os livros");
        printf("\n3 - Listar todas as revistas");
        printf("\n4 - Listar os exemplares por caixa");
        printf("\n0 - Sair\n");
		printf("\nDigite a op��o desejada: ");
        fflush(stdin);
        scanf("%d", &op);
        switch(op){
            case 1:
            	do{
            		system("cls");
            		i++;
            		cadastrarObra(obras);
            		
            		printf("\nDeseja cadastrar novo exemplar? [s] - sim | [n] - n�o: ");
            		fflush(stdin);
                    scanf("%c", &resp);
                    if ((resp != 's') && (resp != 'S') && (resp != 'n') && (resp != 'N')) {
                    	do {
                    		printf("\nResposta inv�lida digite [s] - Sim e [n] - N�o: ");
                    		fflush(stdin);
                    		scanf("%c", &resp);
						} while((resp != 's') && (resp != 'S') && (resp != 'n') && (resp != 'N'));
					}
				} while((resp=='S')||(resp=='s'));
            break;
            case 2:
                system("cls");
                listarLivros(obras);
            break;
            case 3:
            	system("cls");
                listarRevistas(obras);
            break;
            case 4:
            	do{
            		system("cls");
            		listarCaixas(obras);
            		
            		printf("\nDeseja buscar outra caixa? [s] - sim | [n] - n�o: ");
            		fflush(stdin);
                    scanf("%c", &resp);
                    if ((resp != 's') && (resp != 'S') && (resp != 'n') && (resp != 'N')) {
                    	do {
                    		printf("\nResposta inv�lida digite [s] - Sim e [n] - N�o: ");
                    		fflush(stdin);
                    		scanf("%c", &resp);
						} while((resp != 's') && (resp != 'S') && (resp != 'n') && (resp != 'N'));
					}
				} while((resp=='S')||(resp=='s'));
            break;
            case 0:
                printf("\nSistema encerrado!");
            break;
            default:
                printf("\nOp��o inv�lida!\n");
                system("pause");
            break;
        }
    }while(op!=0);
    
    return 0;
}

void cadastrarObra(obra obras[]){
    FILE *arq;
    
    arq = fopen("arquivo.txt", "a+");
    if(arq != NULL){
    	printf("Digite os dados do exemplar que deseja cadastrar:\n");
    	printf("Digite [1] - Livro e [2] - Revista: ");
    	fflush(stdin);
    	scanf("%d", &obras[i].tipo);
    	if ((obras[i].tipo != 1) && (obras[i].tipo != 2)) {
    		do {
    			printf("Op��o inv�lida digite [1] - Livro e [2] - Revista: ");
    			fflush(stdin);
    			scanf("%d", &obras[i].tipo);
			} while((obras[i].tipo != 1) && (obras[i].tipo != 2));
		}
        printf("T�tulo: ");
        fflush(stdin);
        gets(obras[i].titulo);
        printf("Edi��o: ");
        fflush(stdin);
        scanf("%d", &obras[i].edicao);
        printf("Nome do autor: ");
        fflush(stdin);
        gets(obras[i].nomeAutor);
        printf("Editora: ");
        fflush(stdin);
        gets(obras[i].editora);
        if (obras[i].tipo == 1) {
        	printf("ISBN: ");
        	fflush(stdin);
        	gets(obras[i].cod);
		}
		if (obras[i].tipo == 2) {
			printf("ISSN: ");
        	fflush(stdin);
        	gets(obras[i].cod);
		}
        printf("Quantidade de exemplares: ");
        fflush(stdin);
        scanf("%d", &obras[i].qtdExemp);
        printf("Caixa: ");
        fflush(stdin);
        scanf("%d", &obras[i].caixa);
        printf("Ano: ");
        fflush(stdin);
        scanf("%d", &obras[i].ano);

        fwrite(&obras[i], sizeof(obra), 1, arq);
    }
    else{
        printf("\nN�o foi poss�vel abrir o arquivo!\n");
        system("pause");
        exit(1);
    }
    fclose(arq);
}

int lerArquivo(obra obras[]){
    FILE *arq;
    int i = 0;
    obra p;
    
    arq = fopen("arquivo.txt", "r");
    if(arq != NULL){
        while(1){
            size_t r = fread(&p, sizeof(obra), 1,arq);
            if(r < 1)
                break;
            else
                obras[i++] = p;
        }
    }
    else{
    	printf("\nN�o foi poss�vel abrir o arquivo!\n");
    	system("pause");
        exit(1);
    }
    fclose(arq);
    
    return i;
}

void listarLivros(obra obras[]){
    FILE *arq;
    int len_vet = lerArquivo(obras);
    int j, qtdLiv = 0;

	arq = fopen("arquivo.txt", "r");
	if(arq != NULL) {
		fread(obras, sizeof(int), 10, arq);

    	printf("\n>>> Lista de Livros <<<\n");
    
    	for(j = 0; j < len_vet; j++){
    		if (obras[j].tipo == 1) {
    			printf("\n---------------------------------------------------------------\n");
       			printf("T�tulo: %s", obras[j].titulo);
        		printf("\nEdi��o: %d", obras[j].edicao);
       	 		printf("\nNome do autor: %s", obras[j].nomeAutor);
        		printf("\nEditora: %s", obras[j].editora);
				printf("\nISBN: %s", obras[j].cod);
        		printf("\nQuantidade exemplares: %d", obras[j].qtdExemp);
        		printf("\nCaixa: %d", obras[j].caixa);
        		printf("\nAno: %d", obras[j].ano);
        		printf("\n---------------------------------------------------------------\n");
				qtdLiv++;	
			}
    	}
    	if (qtdLiv == 0) {
    		printf("\nN�o h� livros cadastrados!");
		}
		else {
			printf("\nVoc� possui %d livros cadastrados!\n", qtdLiv);
		}	
	}
	else {
		printf("\nN�o foi poss�vel abrir o arquivo!\n");
    	system("pause");
        exit(1);
	}
    fclose(arq);
    getch();
}

void listarRevistas(obra obras[]){
    FILE *arq;
    int len_vet = lerArquivo(obras);
    int j, qtdRev = 0;

	arq = fopen("arquivo.txt", "r");
	if(arq != NULL) {
		fread(obras, sizeof(int), 10, arq);

    	printf("\n>>> Lista de Revistas <<<\n");
    
    	for(j = 0; j < len_vet; j++){
    		if (obras[j].tipo == 2) {
    			printf("\n---------------------------------------------------------------\n");
       			printf("T�tulo: %s", obras[j].titulo);
        		printf("\nEdi��o: %d", obras[j].edicao);
       	 		printf("\nNome do autor: %s", obras[j].nomeAutor);
        		printf("\nEditora: %s", obras[j].editora);
				printf("\nISSN: %s", obras[j].cod);
        		printf("\nQuantidade exemplares: %d", obras[j].qtdExemp);
        		printf("\nCaixa: %d", obras[j].caixa);
        		printf("\nAno: %d", obras[j].ano);
        		printf("\n---------------------------------------------------------------\n");
				qtdRev++;	
			}
    	}
    	if (qtdRev == 0) {
    		printf("\nN�o h� revistas cadastradas!");
		}
		else {
			printf("\nVoc� possui %d revistas cadastradas!\n", qtdRev);
		}	
	}
	else {
		printf("\nN�o foi poss�vel abrir o arquivo!\n");
    	system("pause");
        exit(1);
	}
    fclose(arq);
    getch();
}

void listarCaixas(obra obras[]){
    FILE *arq;
    int len_vet = lerArquivo(obras);
    int j, qtdExemp = 0, caixa, rev = 0, liv = 0;

	printf("\nDigite a caixa que deseja procurar: ");
	fflush(stdin);
	scanf("%d", &caixa);
	
	arq = fopen("arquivo.txt", "r");
	if(arq != NULL) {
		fread(obras, sizeof(int), 10, arq);
    
    	printf("\n>>> Lista de exemplares na caixa %d <<<\n", caixa);
    	for(j = 0; j < len_vet; j++){
    		if (obras[j].caixa == caixa) {
    			printf("\n---------------------------------------------------------------\n");
       			printf("T�tulo: %s", obras[j].titulo);
        		printf("\nEdi��o: %d", obras[j].edicao);
       	 		printf("\nNome do autor: %s", obras[j].nomeAutor);
        		printf("\nEditora: %s", obras[j].editora);
				printf("\nISSN: %s", obras[j].cod);
        		printf("\nQuantidade exemplares: %d", obras[j].qtdExemp);
        		printf("\nCaixa: %d", obras[j].caixa);
        		printf("\nAno: %d", obras[j].ano);
        		printf("\n---------------------------------------------------------------\n");
				qtdExemp++;	
				if (obras[j].tipo == 1) {
					liv++;
				}
				if (obras[j].tipo == 2) {
					rev++;
				}
			}
    	}
    	if (qtdExemp == 0) {
    		printf("\nCaixa n�o cadastrada!");
		}
		else {
			printf("\nVoc� possui %d obras na caixa selecionada!\n", qtdExemp);
			printf("%d Livros\n", liv);
			printf("%d Revistas\n", rev);
		}	
	}
	else {
		printf("\nN�o foi poss�vel abrir o arquivo!\n");
    	system("pause");
        exit(1);
	}
    fclose(arq);
    getch();
}
