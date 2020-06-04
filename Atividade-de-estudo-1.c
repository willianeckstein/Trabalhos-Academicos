/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	/* variaveis */
	int codLanche;
	
	/* Entrada */
	printf ("Menu:");
	printf ("\n1 - X-Bacon");
	printf ("\n2 - X-Salada");
	printf ("\nDigite sua opcao: ");
	scanf ("%d", &codLanche);
	
	/* Processamento/saida */
	switch (codLanche)
	{
		case 1:
			printf ("\nSua escolha: ");
			printf ("\nX-Bacon - R$ 18.00");
			break;
		case 2:
			printf ("\nSua escolha: ");
			printf ("\nX-Salada - R$ 15.00");
			break;
		default:
			printf ("\nCodigo do lanche invalido!");
			break;
	}
	
	return(0);
}
