#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define _TAM_ESTOQUE_ 200

#define _TAM_CATEGORIA_ 20
#define _TAM_NOME_ 30

#define _TAM_COD_  20
#define _TAM_PRE_ 10
#define _TAM_QUANT_ 20

typedef struct { 
	char categoria[_TAM_CATEGORIA_];
	char nome[_TAM_NOME_];
	
	char codigo[_TAM_COD_];
	char preco[_TAM_PRE_];
	char quantidade[_TAM_QUANT_];
} TBrinquedo;

typedef struct {
	TBrinquedo v[_TAM_ESTOQUE_];
	int qtd; 
} TEstoque;


void LerString(char str[], int max){
	fgets(str,max,stdin);
	str[strlen(str)-1]='\0';
}

void Inserir_Brinquedo(TBrinquedo *c){
	printf("\nInsira a categoria do brinquedo:\n");
	LerString((*c).categoria,_TAM_CATEGORIA_ );
	printf("\nInsira o nome do brinquedo:\n");
	LerString((*c).nome,_TAM_NOME_ );
	printf("\nInsira o codigo do brinquedo:\n");
	LerString((*c).codigo,_TAM_COD_);
	printf("\nInsira o preco do brinquedo:\n");
	LerString((*c).preco,_TAM_PRE_);
	printf("\nInsira a quantidade do brinquedo:\n");
	LerString((*c).quantidade,_TAM_QUANT_);
}


void inicializar(TEstoque *a){
	(*a).qtd = 0;
}


int obterIndice(TEstoque *a, char info[]){
	int achou,i;
	achou = 0;
	i=0;
	while(!achou && i<(*a).qtd)
		if(strcmp(a->v[i].codigo,info) ==0 || strcmp(a->v[i].quantidade,info) == 0)
			achou = 1;
		else
			i++;
		
	return achou?i:-1;
}

void inserir(TEstoque *a, TBrinquedo c){
	(*a).v[(*a).qtd] = c;
	(*a).qtd++;
}


int remover(TEstoque *a, char info[]){
	int pos = obterIndice(a, info);
	if (pos>-1){
		(*a).v[pos] = (*a).v[(*a).qtd-1];
		(*a).qtd--;	
		return 1;
	}else {	
		printf("\n\nBrinquedo nao encontrado\n");
		return 0;
	}
}

int Atualizar(TEstoque *a, char info[], TBrinquedo c){
	int pos = obterIndice (a, info);
	if (pos>-1){
		(*a).v[pos] = c;
		return 1;	
	}else {
		printf("\n\nBrinquedo nao encontrado\n");
		return 0;
	}
}

void listar(TEstoque a){ 
	int i;
	printf("\n%3s %25s %25s %25s %25s %25s\n\n"," * ", "Codigo", "Categoria", "Nome", "Preco", "Quantidade" );

	for(i=0; i<a.qtd; i++)
			printf("%3i %24s %24s %24s %24s %24s\n\n", i+1, a.v[i].codigo, a.v[i].categoria, a.v[i].nome, a.v[i].preco, a.v[i].quantidade);
}


void listar_categoria(TEstoque a){
	
	for(int i=0; i<a.qtd; i++)
		printf("\n%i %s\n\n", i+1, a.v[i].categoria);	
}


void filtrando(TEstoque a, char info[]){
	int i,j;
	printf("\n%s %30s %30s \n\n"," * ", "Categoria", "Nome");

	for(i=0,j=0; i<a.qtd; i++)
		if(strstr(a.v[i].categoria, info) != NULL || strstr(a.v[i].nome, info))
			printf("%i %31s %31s \n\n", ++j, a.v[i].categoria, a.v[i].nome);
}




int menu(){
	
	int opc;
	
	do{
	system("cls");
	printf("\tBem vindo ao estoque de brinquedos!\n");
	printf("\tEscolha uma das opcoes abaixo:\n\n");
	printf("\t1 - Inserir brinquedo \n");
	printf("\t2 - remover brinquedo \n");
	printf("\t3 - atualizar dados do brinquedo\n");
	printf("\t4 - listar brinquedos \n");
	printf("\t5 - listar brinquedos por categoria \n");
	printf("\t6 - listar por filtro de nome ou categoria \n");
	printf("\t7 - sair\n\n");
	scanf("%i", &opc);
	}while(opc<1 || opc>7);
	
	fflush(stdin);	
	return opc;
}

int main(void){
	
	//SetConsoleTitle("PRC - 02");
	
	FILE * pFile;
	pFile = fopen ("PRC_02.txt", "tr");
	
	TEstoque estocados;
	TBrinquedo produto;
	
	int acabou = 0;
	int listalocal;
	char aux[_TAM_ESTOQUE_];
	inicializar(&estocados);
	
	
	while(!acabou){
		
		switch(menu()){
			
			case 1:
				Inserir_Brinquedo(&produto);
				inserir(&estocados,produto);
				system("pause");
				break;
			case 2:
				printf("Insira o codigo e a quantidade do brinquedo para remove-lo!\n");
				LerString(aux,_TAM_ESTOQUE_ );			
				if(remover(&estocados, aux) )
					printf("Contato removido com sucesso!\n");
				system("pause");
				break;
			case 3:
				printf("Entre com codigo ou quantidade do brinquedo para atualiza-lo!\n");
				LerString(aux,_TAM_ESTOQUE_);
				Inserir_Brinquedo(&produto);
				if (Atualizar(&estocados, aux, produto))
					printf("Dados alterados com sucesso!\n");
				else
					printf("Brinquedo nao encontrado!\n");	
				system("pause");
				break;
			case 4:
				listar(estocados);
				system("pause");
				break;
			case 5:
				listar_categoria(estocados);
				system("pause");
				break;		
			case 6:
				printf("Entre com um dado do brinquedo a ser filtrado!");
				LerString(aux,_TAM_ESTOQUE_ );
				filtrando(estocados,aux);
				system("pause");
				break;
			case 7:
				acabou = 1;
				system("pause");
				break;	
			default: 
				printf("opcao invalida!\n");
				system("pause");
				break;				
		}
	}
}


