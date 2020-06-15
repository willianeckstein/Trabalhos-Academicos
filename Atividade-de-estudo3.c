#include <stdio.h>
#include <stdlib.h>

float calcCusto (float valorFab, int porcentRev, int porcentImp) {
	float result;
	result = valorFab + (valorFab*porcentRev/100) + (valorFab*porcentImp/100);
	return(result);
}

int main() {
	float custoFab, total;
	int pRevendedor, pImposto;
	printf("Digite o custo de fábrica do carro: ");
	scanf("%f", &custoFab);
	pRevendedor = 28;
	pImposto = 45;
	total = calcCusto(custoFab, pRevendedor, pImposto);
	printf("\nCusto ao consumidor do carro: R$ %.2f", total);
	return(0);
}
