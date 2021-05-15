#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

#define _TAM_NOME_ 30
#define _TAM_TELEFONE_ 30
#define _TAM_EMAIL_ 40

#define _MAX_CONTATOS_ 100

typedef struct {
   char nome[_TAM_NOME_];
   char telefone[_TAM_TELEFONE_];
   char email[_TAM_EMAIL_];
} TContato;

typedef struct{
  TContato v[_MAX_CONTATOS_];
  int    qtd; 
} TAgenda;

void LerString(char str[], int max){
	fgets(str,max,stdin);
	str[strlen(str)-1]='\0';
}

void ler_cont(TContato *c){
	printf("\nEntre com o nome:\n");
	LerString((*c).nome, _TAM_NOME_);
	printf("\nEntre com o telefone:\n");
	LerString((*c).telefone, _TAM_TELEFONE_);
	printf("\nEntre com o email:\n");
	LerString((*c).email, _TAM_EMAIL_);	
}

void inicializar(TAgenda *a){
	(*a).qtd = 0;
}

int obterIndice(TAgenda a, char info[] ){
	int achou,i;
	achou = 0;
	i=0;
	while(!achou && i<a.qtd)
		if(strcmp(a.v[i].email, info) == 0)
			achou = 1;
		else
			i++;
		
	return achou?i:-1;
}

void inserir(TAgenda *a, TContato c){
	(*a).v[(*a).qtd] = c;
	(*a).qtd++;
}

int remover(TAgenda *a, char info[]){
	int pos = obterIndice(*a, info);
	if (pos>-1){
		(*a).v[pos] = (*a).v[(*a).qtd-1];
		(*a).qtd--;
		return 1;
	}else {
		return 0;
		printf("\n\ncontato nao encontrado\n");
	}
}

void listar(TAgenda a){ 
	int i;
	printf("\n%s %30s %30s %30s\n\n"," * ", "Nome", "Telefone", "Email" );

	for(i=0; i<a.qtd; i++)
			printf("%i %31s %31s %31s\n\n", i+1, a.v[i].nome, a.v[i].telefone, a.v[i].email);
}


void listar_nome(TAgenda a){
		
	for(int i=0; i<a.qtd; i++)
		printf("\n%i %s\n\n", i+1, a.v[i].nome);
}

void listar_telefone(TAgenda a){
	
	for(int i=0; i<a.qtd; i++)
		printf("\n%i %s\n\n", i+1, a.v[i].telefone);	
}

void listar_email(TAgenda a){
		
	for(int i=0; i<a.qtd; i++)
		printf("\n%i %s\n\n", i+1, a.v[i].email);	
}



int menu(){
	
	int opc;
	
	do{
	system("cls");
	printf("\tBem vindo a sua agenda pessoal de contatos!\n");
	printf("\tEscolha uma das opcoes abaixo:\n\n");
	printf("\t1 - Inserir contato \n");
	printf("\t2 - remover contato \n");
	printf("\t3 - listar contatos \n");
	printf("\t4 - listar contatos por parte \n");
	printf("\t5 - sair \n\n");
	scanf("%i", &opc);
	}while(opc<1 || opc>6);
	
	fflush(stdin);	
	return opc;
}

int main(void){
	
	SetConsoleTitle("PRC - 01");
	
	FILE * pFile;
	pFile = fopen ("PRC_01.txt", "rt");
	
	TAgenda agenda;
	TContato ficha;
	
	char aux[_TAM_EMAIL_];
	int acabou = 0;
	int listalocal;
	inicializar(&agenda);
	
	while(!acabou){
		
		switch(menu()){
			
			case 1:
				ler_cont(&ficha);
				inserir(&agenda,ficha);
				printf("Contato adicionado.");
				system("pause");
				break;
			case 2:
				printf("insira o email do contato para remove-lo.\n");
				LerString(aux, _TAM_EMAIL_);
				if(remover(&agenda, aux))
					printf("Contato removido com sucesso!\n");
				else
					printf("\nContato nao encontrado!\n");
				system("pause");	
				break;
			case 3:
				listar(agenda);
				system("pause");
				break;
			case 4:
				printf("\ninsira qual o tipo de dado de contato deseja:\n");
				printf("1 - nome | 2 - telefone | 3 - email\n\n");
				scanf("%d", &listalocal);
				
				if(listalocal = 1){
					listar_nome(agenda);
				}
				else if(listalocal = 2){
					listar_telefone(agenda);
				}
				else if(listalocal = 3){
					listar_email(agenda);
				}
				else {
					printf("opcao invalida!");	
				}
				system("pause");
				break;	
			case 5:				
				acabou=1;
				break;
			default:
				printf("opcao invalida!\n");
				system("pause");
				break;				
		}
	}
}

