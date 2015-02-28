#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int linha_valida (char ** c, double p, int n, int m){
	//Validar Cliente e produto
	if ((p > 0.0) && (n > 0) && (!strcmp(c[3],"N") || !strcmp(c[3],"P")) && ((m >= 1) || (m <= 12))) {
		return 1;
	}
	else return 0;
}

void leitura (char * nome_fich) {
	FILE * ficheiro;
	
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";

	int linhas = 0;
	int linhas_val = 0;
	int i = 0;
	int nr;
	int mes;
	double preco;
	char * compra[6];

	ficheiro = fopen(nome_fich, "r");
	while ((string = fgets (str, 100, ficheiro)) != NULL) {
		linhas++;
		
		if (!strcmp(nome_fich, "FichClientes.txt")){
			token = strtok(string, limit);
			token[strlen(token)-2] = '\0';
			printf("Cliente: %s \n",token);
			linhas_val++;
		}
		else if (!strcmp(nome_fich, "FichProdutos.txt")){
			token = strtok(string, limit);
			token[strlen(token)-2] = '\0';
			printf("Produto: %s \n",token);
			linhas_val++;
		}
		else if (!strcmp(nome_fich, "Compras.txt")){
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 6; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			}
			//compra[5][strlen(compra[5])-2] = '\0';
			
			preco = strtod(compra[1], &compra[1]);
			nr = atoi(compra[2]);
			mes = atoi(compra[5]);
			if (linha_valida(compra, preco, nr, mes)){
				linhas_val++;
				printf("Produto: %s Preço: %f Nr comprados: %d Tipo: %s Cliente: %s Mes: %d\n", compra[0], preco, nr, compra[3], compra[4], mes);
			}
		}


		token = strtok(NULL, limit);
	}
	printf("Ficheiro lido: %s , número de linhas lidas: %d , nr de linhas válidas: %d\n", nome_fich, linhas, linhas_val);

}


int main (){
	
	leitura("Compras.txt");
	return 0;
}
