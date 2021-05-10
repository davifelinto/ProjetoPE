#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "color.h"
//--------------------------ENTIDADES--------------------------

typedef struct {
	char nome[20];
    int valor;
	char marcado;
}skill;
typedef struct {
	char nome[30];  // chave primaria
	char raca[10];
	char classe[20];
	int nivel;
	int CA;
	skill habil[6];
	skill pericias[18];
	char notas[200];	
	int codJogador; // chave estrangeira - Jogador	
	char deletado; // *=deletado ' '=nao deletado
}tPersonagem;
typedef struct {
	char nome[30]; // chave primaria
	char tier;
	char descr[200];
	char deletado; // *=deletado ' '=nao deletado
}tItens;
typedef struct {
	int codigo; // chave primaria
	char nome[30];
	char deletado; // *=deletado ' '=nao deletado
}tJogador;
//-----------------------FUNCOES--------------------------------------
void iniciaHab(skill habilidades[]){
    int i;
    strcpy(habilidades[0].nome, "Forca");
    strcpy(habilidades[1].nome, "Destreza");
    strcpy(habilidades[2].nome, "Constituicao");
    strcpy(habilidades[3].nome, "Inteligencia");
    strcpy(habilidades[4].nome, "Sabedoria");
    strcpy(habilidades[5].nome, "Carisma");
    for(i = 0; i < 6; i++){
        habilidades[i].valor = 8;
        habilidades[i].marcado = ' ';
    }
}
void iniciaPericias(skill pericias[]){
    int i;
    strcpy(pericias[0].nome, "Atletismo");
	strcpy(pericias[1].nome, "Acrobacia");
	strcpy(pericias[2].nome, "Furtividade");
	strcpy(pericias[3].nome, "Prestidigitacao");
	strcpy(pericias[4].nome, "Arcanismo");
	strcpy(pericias[5].nome, "Historia");
	strcpy(pericias[6].nome, "Investigacao");
	strcpy(pericias[7].nome, "Natureza");
	strcpy(pericias[8].nome, "Religiao");
	strcpy(pericias[9].nome, "Adestrar Animais");
	strcpy(pericias[10].nome, "Intuicao");
	strcpy(pericias[11].nome, "Medicina");
	strcpy(pericias[12].nome, "Percepcao");
	strcpy(pericias[13].nome, "Sobrevivencia");
	strcpy(pericias[14].nome, "Atuacao");
	strcpy(pericias[15].nome, "Enganacao");
	strcpy(pericias[16].nome, "Intimidacao");
	strcpy(pericias[17].nome, "Persuasao");
	for(i = 0; i<18; i++){
		pericias[i].marcado = ' ';
	}
}
void alteraPericias(skill pericias[]){
	char setas;
	int tam = 18, opcao = 0, i;
	do{	
		printf("Marque suas pericias treinadas: (x para marcar e desmarcar), e (enter para terminar as escolhas)\n");
		for (i = 0; i < tam; ++i) {
			if(pericias[i].marcado != ' '){
				backgroundcolor(GREEN);
			}
			else
				backgroundcolor(0);
			if(i == opcao)
				textcolor(RED);
			else
				textcolor(LIGHTGRAY);
			printf("%s\n", pericias[i].nome);
		}
		if(opcao == 17 || pericias[17].marcado == '*'){
			backgroundcolor(0);
			textcolor(LIGHTGRAY);	
		}
		do{
			setas = _getch();
		}while(setas != 'x' && setas != 'X' && setas != 72 && setas != 80 && setas != 13);
		if(setas == 'x' || setas == 'X'){
			if(pericias[opcao].marcado == '*')
				pericias[opcao].marcado = ' ';
			else
				pericias[opcao].marcado = '*';
		}
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % tam;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = tam-1;
		}	
		system("cls");
	}while(setas != 13);
	for(i = 0; i <tam; i++){
		if(pericias[i].marcado == '*'){
			printf("A pericia %s possui especializacao de ladino ou Aptidao de bardo?(s para confirmar)\n", pericias[i].nome);
			setas = _getch();
			if(setas == 's' || setas == 'S')
				pericias[i].marcado == '!';
		}
	}
}
void alteraHabilidades(skill habilidades[]){
    int i, tam = 6, opcao = 0;
    char setas;
    do
    {
        for(i = 0; i < tam; i++){
            if(i == opcao){
                textcolor(GREEN);
            }else{
                textcolor(LIGHTGRAY);
            }
              printf("%-12s : <%.2i>\n", habilidades[i].nome, habilidades[i].valor); 
        }
        do{
			setas = _getch();
		}while(setas != 77 && setas != 75 && setas != 72 && setas != 80 && setas != 13);
		switch(setas){
			case 77://direita
                    if(habilidades[opcao].valor < 20)
					    habilidades[opcao].valor += 1;
				break;
			case 75://esquerda
					habilidades[opcao].valor -= 1;
				break;
			case 80://seta para baixo
				opcao = (opcao + 1) % tam;
				break;
			case 72://seta para cima
				opcao = opcao - 1;
				if(opcao == -1) 
					opcao = tam-1;
		}
        system("cls");
    } while (setas != 13);
}
void valorDePericia (skill pericia[], skill habilidade[], int lvl){
	int prof= (1 + ((lvl + 3) / 4));
    int i;
	for (i=0; i<18; i++){ //for
		if (i==0)
			pericia[i].valor = (habilidade[i].valor/2) - 5;
		if (0<i<4) //dex
			pericia[i].valor = (habilidade[1].valor/2) - 5;
		if (3<i<9) //int
			pericia[i].valor = (habilidade[3].valor/2) - 5;
		if (8<i<14) //sab
			pericia[i].valor = (habilidade[4].valor/2) - 5;
		if (i>13) //car
			pericia[i].valor = (habilidade[5].valor/2) - 5;
	}
	for (i=0; i<18; i++){
		if (pericia[i].marcado == '*')
			pericia[i].valor += prof;
		if (pericia[i].marcado == '!')
			pericia[i].valor += 2*prof;
	}
}
int main(){
    int i;
    tPersonagem personagem;
    iniciaHab(personagem.habil);
    alteraHabilidades(personagem.habil);
    iniciaPericias(personagem.pericias);
    alteraPericias(personagem.pericias);
    personagem.nivel = 3;
    valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
    ///////////////////////////         TEMPORARIO      /////////////////////////////////////////////////////////////
    ///////////////////////////VISUALIZAR PREENCHIMENTO /////////////////////////////////////////////////////////////
    system("COLOR E0");
    system("cls");
    for(i = 0; i < 6; i++){
        printf("%3.3s : %.2i\t", personagem.habil[i].nome, personagem.habil[i].valor);
    }
    printf("\n\n");
    for(i = 0; i <9; i++){
		printf("\t\t\t%-18s= %i\t", personagem.pericias[i].nome, personagem.pericias[i].valor);
		printf("%-18s = %i\n", personagem.pericias[i+9].nome, personagem.pericias[i+9].valor);
	}
    system("\npause");
    return 0;
}