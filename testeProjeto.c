#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include "color.h"
//-------------------------- ENTIDADES ------------------------------------------------------------------------------------
typedef struct {
	char nome[20];
    int valor;
	char marcado;
}skill;
typedef struct {
	char nome[30];  // chave primaria
	char raca[30];
	char classe[30];
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
}tItem;
typedef struct {
	int codigo; // chave primaria
	char nome[30];
	char deletado; // *=deletado ' '=nao deletado
}tJogador;
//-----------------------FUNCOES-------------------------------------------------------------------------------------------
//-----------------------INICIA O NOME, VALOR E OS MARCADORES DAS HABILIDADES ---------------------------------------------
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
//-----------------------INICIA O NOME E OS MARCADORES DAS PERICIAS -------------------------------------------------------
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
//-----------------------ALTERA O MARCADOR DAS PERICIAS -------------------------------------------------------------------
void alteraPericias(skill pericias[]){
	char setas;
	int tam = 18, opcao = 0, i, curX, curY;
	printf("\nPericias: \n\t\t(X para treinadas e C para Especializacao de ladino ou Aptidao de bardo)\n");
	curX = GetconsoleCursorX();
	curY = GetconsoleCursorY();
	do{
		gotoxy(curX, curY);
		for (i = 0; i < tam; ++i) {
			if(pericias[i].marcado == '*'){
				backgroundcolor(WHITE);
			}
			else	
				if(pericias[i].marcado == '!'){
					backgroundcolor(MAGENTA);
				}
			if(i == opcao)
				textcolor(RED);
			printf("%s\n", pericias[i].nome);
			backgroundcolor(0);
			textcolor(LIGHTGRAY);
		}
		do{
			setas = _getch();
		}while(setas != 'x' && setas != 'X' && setas != 'c' && setas != 'C' && setas != 72 && setas != 80 && setas != 13);
		switch(setas){
			case 'x':
			case 'X':
				if(pericias[opcao].marcado == '*')
					pericias[opcao].marcado = ' ';
				else
					pericias[opcao].marcado = '*';
				break;
			case 'c':
			case 'C':
				if(pericias[opcao].marcado == '!')
					pericias[opcao].marcado = ' ';
				else
					pericias[opcao].marcado = '!';
				break;
			case 80://seta para baixo
				opcao = (opcao + 1) % tam;
				break;
			case 72://seta para cima
				opcao = opcao - 1;
				if(opcao == -1) 
					opcao = tam-1;
		}
	}while(setas != 13);
}
//-----------------------ALTERA O VALOR DAS HABILIDADES -------------------------------------------------------------------
void alteraHabilidades(skill habilidades[]){
	int i, tam = 6, opcao = 0, curX, curY;
	char setas;
	
	printf("\nValores de habilidades do personagem: \n");
	curX = GetconsoleCursorX();
	curY = GetconsoleCursorY();
	for(i = 0; i < tam; i++){
		do{
			for(i = 0; i < tam; i++){
				if(i == opcao)
					textcolor(GREEN);
				printf("%-12s : <%.2i>\n", habilidades[i].nome, habilidades[i].valor);
				textcolor(LIGHTGRAY);
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
					if(habilidades[opcao].valor > 6)
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
			gotoxy(curX, curY);
		} while (setas != 13);
	}
	for(i = 0; i < tam; i++){
		textcolor(GREEN);
		printf("%-12s : <%.2i>\n", habilidades[i].nome, habilidades[i].valor);
	}
	textcolor(LIGHTGRAY);
}
//-----------------------ALTERA O VALOR DAS PERICIAS ----------------------------------------------------------------------
void valorDePericia (skill pericia[], skill habilidade[], int lvl){
	int prof= (1 + ((lvl + 3) / 4));
    int i;
	for (i=0; i<18; i++){ //for
		if (i == 0)
			pericia[i].valor = (habilidade[i].valor/2) - 5;
		if (0 < i && i < 4) //dex
			pericia[i].valor = (habilidade[1].valor/2) - 5;
		if (3 < i && i < 9) //int
			pericia[i].valor = (habilidade[3].valor/2) - 5;
		if (8<i && i < 14) //sab
			pericia[i].valor = (habilidade[4].valor/2) - 5;
		if (i > 13) //car
			pericia[i].valor = (habilidade[5].valor/2) - 5;
	}
	for (i=0; i<18; i++){
		if (pericia[i].marcado == '*')
			pericia[i].valor += prof;
		if (pericia[i].marcado == '!')
			pericia[i].valor += 2*prof;
	}
}
//---------------------ESCOLHE A CLASSE -----------------------------------------------------------------------------------
const char * escolheClasse(){
	char setas;
	int tam = 12, opcao = 0, i;
	//Se for char, a variavel ?? deletada antes de retornar para main
	static char classe[12][20] = {"Barbaro", "Bardo", "Bruxo", "Clerigo", "Druida",
	 "Feiticeiro", 	"Guardiao", "Guerreiro", "Ladino",	"Mago", "Monge", "Paladino"};
	printf("Classe do personagem: \n");
	do{
		textcolor(CYAN);
		printf("%-20s", classe[opcao]);
		printf("\r");
		do{
			setas = _getch();
		}while(setas != 72 && setas != 80 && setas != 13);
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % tam;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = tam-1;
		}
	}while(setas != 13);
	textcolor(LIGHTGRAY);
	printf("\n");
	
	return (classe[opcao]);
}
//---------------------ESCOLHE A RA??A -------------------------------------------------------------------------------------
const char * escolheRaca(){
	char setas;
	//Se for char, a variavel ?? deletada antes de retornar para main
	static char raca[14][20] = {"Anao da Colina", "Anao da Montanha", "Draconato", "Elfo (Alto)",  "Elfo (Drow)", "Elfo da Floresta",
	"Gnomo da Floresta", "Gnomo das Rochas", "Halfling Pes Leves", "Halfling Robusto", "Humano", "Meio-Elfo",	"Meio-Orc", "Tiefling"};
	int tam = 14, opcao = 0, i;	
	printf("Raca do personagem: \n");
	do{
		textcolor(BLUE);
		printf("%-20s", raca[opcao]);
		printf("\r");
		do{
			setas = _getch();
		}while(setas != 72 && setas != 80 && setas != 13);
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % tam;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = tam-1;
		}
	}while(setas != 13);
	textcolor(LIGHTGRAY);
	printf("\n");
	return (raca[opcao]);
}
//----------------------- ESCOLHER JOGADOR --------------------------------------------------------------------------------
int escolheJogador(FILE *arq){
	int opcao = 0, i, curX, curY;;
	char setas;
	tJogador jogador;
	fseek(arq, 0, SEEK_SET);
	if(!(fread(&jogador, sizeof(jogador), 1, arq))){
		printf("E necessario criar um jogador antes de acessar essa funcao: \n");
		printf("Nome do Jogador: ");
		fflush(stdin);
		do{
			gets(jogador.nome);
			if(strcmp(jogador.nome, "") == 0){
				textcolor(RED);
				printf("O nome nao deve ficar vazio!\n");
				textcolor(LIGHTGRAY);
			}
		}while(strcmp(jogador.nome, "") == 0);
		jogador.codigo = 1;
		fwrite(&jogador, sizeof(jogador), 1, arq);
		return jogador.codigo;
	}
	printf("Escolha o jogador: \n");
	curX = GetconsoleCursorX();
	curY = GetconsoleCursorY();
	do{
		gotoxy(curX, curY);
		fseek(arq, 0, SEEK_SET);
		i = 0;
		while (fread(&jogador, sizeof(jogador), 1, arq)){
			if(jogador.deletado != '*'){
				if(i == opcao)
					textcolor(RED);
				printf("%s\n", jogador.nome);
				textcolor(LIGHTGRAY);
				i++;
			}
		}
		do{
			setas = _getch();
		}while(setas != 72 && setas != 80 && setas != 13);
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % i;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = i-1;
		}
	}while(setas != 13);
	fseek(arq, (sizeof(jogador)*(opcao)), SEEK_SET);
	fread(&jogador, sizeof(jogador), 1, arq);
	return jogador.codigo;
}
//----------------------- ALTERA AS NOTAS DO PERSONAGEM--------------------------------------------------------------------
void deleteSymbol(char *s, size_t position){
    size_t i, len = strlen(s);

    for(i = position; i < len; i++)
        s[i] = s[i+1];
}
int insertInStr(char **s, size_t position, char c){
    __int64 i;

	if((*s = realloc(*s, strlen(*s) +1 +1)) == 0)//realoca e se der erro retorna para funcao
        return 0;
	for(i = strlen(*s)+1; i >= position; i--){
   		if(i == position)
   			(*s)[i] = c;
   		else
   			(*s)[i] = (*s)[i-1];
	}

    return 1;
}
void printText(char *s, size_t position, int *linha){
    size_t currPos, length = strlen(s);;
    char q[200];
    strcpy(q, s);
    
	if(length == 72 && *linha == 1){
		gotoxy(GetconsoleCursorX(), GetconsoleCursorY()+1);
		*linha = 2;
	}else if(length == 143 && *linha == 2){
		gotoxy(GetconsoleCursorX(), GetconsoleCursorY()+1);
		*linha = 3;
	}else if(length < 72 && *linha == 2){
		putchar(' ');
		gotoxy(GetconsoleCursorX()-1, GetconsoleCursorY()-1);
		*linha = 1;
	}else if(length < 143 && *linha == 3){
		putchar(' ');
		gotoxy(GetconsoleCursorX()-1, GetconsoleCursorY()-1);
		*linha = 2;
	}
	if(strlen(s) > 71){
		strcpy(q, s + 71);
		position %= 71;
		length = strlen(q);
	}
	if(strlen(s) > 142){
		strcpy(q, s + 142);
		position %= 71;
		length = strlen(q);
	}
    for(currPos = 0; currPos <= length; currPos++){
        putchar(q[currPos]);
    }
}
void alteraString(char *TEXT){
    unsigned char c;
    char *s = malloc(strlen(TEXT)+1);
    __int64 pos;
	int linha;
	
    strcpy(s, TEXT);
    pos = strlen(s);
	linha = (pos/71) + 1;
	
	printf("\n-----------------------------------------------------------------------\n");
	printf("\n\n\n-----------------------------------------------------------------------\n");
	gotoxy(GetconsoleCursorX(), GetconsoleCursorY()-4);
	printf("%.71s", s);
	if(pos > 71)
		printf("\n%.71s", &s[71]);
	if(pos > 142)
		printf("\n%.71s", &s[142]);
    while((c = getch())!= 13){
        putchar('\r');
        if(strlen(s) <= 1){
        	putchar('\0');
			gets(TEXT);
			return;
		}
        switch(c)
        {
        case 224:
            c = getch();
            break;
        case 8:
                deleteSymbol(s, --pos);
            break;
        default:
            if(strlen(s) < 200){
                insertInStr(&s, pos++, c);
            }
        }
        printText(s, pos, &linha);
    }
    strcpy(TEXT, s);
	free(s);
	gotoxy(GetconsoleCursorX(), GetconsoleCursorY()+5-linha);
    return;
}
//----------------------- MENU --------------------------------------------------------------------------------------------
int menu(char *texto[], int tam, char string[]){
	int opcao = 0, i, getT;
	char esc;
	printf("\n*** %s ***\n\n", string);
	for (i = 0; i < tam; ++i) {
		getT = (i+1) - (((i+1) / tam)*(i+1));
		printf("%i. %s\n", getT,texto[i]);
	}
	esc = _getch();	
	
	return esc - 48;
}

void pausa(){
	printf("\n\n\nPressione qualquer tecla para continuar.");
	_getch();
}

//-----------------------MANIPULACOES DE ARQUIVO (CRUDS)-------------------------------------------------------------------
FILE *abrirArquivo(char arquivo[]){
	FILE *arq = fopen(arquivo, "r+b");
	if(arq == NULL)
		arq = fopen(arquivo, "w+b");
	return arq;
}
// - - - - - JOGADORES - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////	LER O ARQUIVO DE JOGADORES	///////////////////////////////////////////////////////////////////////////////
tJogador lerJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
 	return player;
}
////////////	CONSULTAR O ARQUIVO DE JOGADORES	///////////////////////////////////////////////////////////////////////
int consultarJogador(int cod, FILE *arq) {
	tJogador player;
	int local=0;
	fseek(arq, 0, SEEK_SET);
    while (fread(&player, sizeof(player), 1, arq)) {
    	local++;
    	if ((player.codigo == cod) && (player.deletado != '*'))
    		return local;
	}
	return -1;
}
////////////	LISTAR OS JOGADORES DO ARQUIVO	///////////////////////////////////////////////////////////////////////////
void listarJogadores(FILE *arqJogador, FILE *arqPersonagem) {
	tJogador player;
	tPersonagem persona;
	int primeiro;
	
	fseek(arqJogador, 0, SEEK_SET);
   	printf("Codigo|             NOME              |Personagens\n");
   	printf("-------------------------------------------------------------\n");
    while (fread(&player, sizeof(player), 1, arqJogador)){
    	if (player.deletado != '*'){
    		primeiro = 0;
    		printf("%6d|\t%-30s|", player.codigo, player.nome);
    		fseek(arqPersonagem, 0, SEEK_SET);
    		while (fread(&persona, sizeof(persona), 1, arqPersonagem)){
	    		if(persona.codJogador == player.codigo){
	    			if(primeiro == 0)
						printf("%s", persona.nome);
					else
						printf(", %s", persona.nome);
					primeiro++;
				}	
			}
			printf("\n");
    	}

	}
}
////////////	GRAVA OS JOGADORES NO ARQUIVO	///////////////////////////////////////////////////////////////////////////
void gravarJogador(tJogador player, int local, FILE *arq) {
	if (local <= 0) {
		player.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof(player), SEEK_SET);
	fwrite(&player, sizeof(player), 1, arq);
}
////////////	MARCA O JOGADOR COM A FLAG DE EXCLUSAO	///////////////////////////////////////////////////////////////////
void excluirJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
    player.deletado = '*';
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
	fwrite(&player, sizeof(player), 1, arq);
}
////////////	EXCLUI OS JOGADORES DO ARQUIVO	///////////////////////////////////////////////////////////////////////////
void excluirFisicamenteJogador(FILE **arq, char arquivo[]) {
	tJogador player;
	FILE *arqTemp = fopen("jogadores.aux", "wb");
	if (arqTemp == NULL)
		return;
	fseek(*arq, 0, SEEK_SET);
    while (fread(&player, sizeof(player), 1, *arq))
    	if (player.deletado != '*')
			fwrite(&player, sizeof(player), 1, arqTemp);
	fclose(*arq);
	fclose(arqTemp);
	remove(arquivo);
	rename("jogadores.aux", arquivo);
	*arq = abrirArquivo(arquivo);
}

// - - - - - PERSONAGENS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////	LER UM PERSONAGEM DO ARQUIVO	///////////////////////////////////////////////////////////////////////////
tPersonagem lerPersonagem(int local, FILE *arq){
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
	fread(&persona, sizeof(persona), 1, arq);
	return persona;
}
////////////	SALVAR PERSONAGEM	///////////////////////////////////////////////////////////////////////////////////////
void salvarPersonagem(tPersonagem persona, int local, FILE *arq){
	if (local <= 0) {
		persona.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof (persona), SEEK_SET);
	fwrite(&persona, sizeof (persona), 1, arq);
}
////////////	MOSTRA OS PERSONAGENS NO TERMINAL	///////////////////////////////////////////////////////////////////////
void mostrarPersonagem(tPersonagem persona, tJogador player) {
	int mod[6], i, curX, curY, tamLin = 10, length;
	aleaBackground();
	textcolor(0);
	curX = GetconsoleCursorX();
	curY = GetconsoleCursorY();
	for(i = 0; i < 18; i++)
		printf("%-71s\n", "");
	gotoxy(curX, curY);
	if (persona.deletado != '*'){
		for (i=0;i<6;i++){
			mod[i]=(persona.habil[i].valor/2) - 5;
		}
		printf("-----------------------------------------------------------------------\n");
		printf("%s\n", persona.nome);
		printf("%s, %s\n", persona.raca, persona.classe);
		printf("Jogador %d: %s\n", player.codigo, player.nome);
		printf("-----------------------------------------------------------------------\n");
		printf("Nivel: %i\n", persona.nivel);
		printf("Classe de armadura: %i\n", persona.CA);
		printf("-----------------------------------------------------------------------\n");
		printf("\tFOR\tDES\tCON\tINT\tSAB\tCAR\n");
		for(i=0;i<6;i++){
			printf("\t%i(%i)", persona.habil[i].valor, mod[i]);
		}
		printf("\n-----------------------------------------------------------------------\n");
		printf("Pericias: ");
		for(i=0;i<18;i++){
			if(persona.pericias[i].marcado != ' '){
				if(tamLin + strlen(persona.pericias[i].nome) + 5 <= 71){
					printf("%s +%d; ", persona.pericias[i].nome, persona.pericias[i].valor);
					tamLin += strlen(persona.pericias[i].nome) + 5;
				}else{
					length = 71 - tamLin;
					printf("%.*s", length-1, persona.pericias[i].nome);
					if(strlen(persona.pericias[i].nome) > length)
						printf("-\n%s ", &persona.pericias[i].nome[length-1]);
					else
						printf("\n");
					printf("+%d; ", persona.pericias[i].valor);
					tamLin += strlen(persona.pericias[i].nome) + 6;
					tamLin %= 71;
				}
			}
		}
		printf("\nPercepcao passiva: %d\n", (persona.habil[12].valor+10));
		printf("-----------------------------------------------------------------------\n");
		printf("Equipamento/Pertences:%.49s\n", persona.notas);
		if(strlen(persona.notas) > 49)
			printf("%.71s\n", &persona.notas[49]);
		if(strlen(persona.notas) > 120)
			printf("%.71s\n", &persona.notas[120]);
		printf("-----------------------------------------------------------------------\n");
	}
}
////////////	LISTAR PERSONAGEM	///////////////////////////////////////////////////////////////////////////////////////
void listarPersonagems(FILE *arqPersona, FILE *arqJogador) {
	tPersonagem persona;
	tJogador player;
	int local = 0;
	
	fseek(arqPersona, 0, SEEK_SET);
	while (fread(&persona, sizeof(persona), 1, arqPersona)) {
		if (persona.deletado != '*'){
			player = lerJogador(consultarJogador(persona.codJogador, arqJogador), arqJogador);
			mostrarPersonagem(persona, player);
		}
	}
	backgroundcolor(BLACK);
	textcolor(LIGHTGRAY);
}
////////////	CONSULTAR PERSONAGEM	///////////////////////////////////////////////////////////////////////////////////
int consultarPersonagem(char nome[], FILE *arq) {
	tPersonagem persona;
	int local=0;
	
	fseek(arq, 0, SEEK_SET);
    while (fread(&persona, sizeof(persona), 1, arq)) {
    	local++;
    	if ((strcmp(persona.nome, nome) == 0) && (persona.deletado != '*'))
    		return local;
	}
	return -1;
}
////////////	MARCA PERSONAGEM COM A FLAG DE EXCLUSAO		///////////////////////////////////////////////////////////////
void excluirPersonagem(int local, FILE *arq) {
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
    fread(&persona, sizeof(persona), 1, arq);
    persona.deletado = '*';
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
	fwrite(&persona, sizeof(persona), 1, arq);
}
////////////	EXCLUI O PERSONAGEM LIGADO AO JOGADOR QUE VAI SER DELETADO		///////////////////////////////////////////
void excluiPersonagemLigado(int cod, FILE *arq) {
	tPersonagem persona;
	int local=0;
	fseek(arq, 0, SEEK_SET);
    while (fread(&persona, sizeof(persona), 1, arq)) {
    	local++;	
		if ((cod == persona.codJogador) && (persona.deletado != '*')){
    		excluirPersonagem(local, arq);
    		printf("%s deletado\n", persona.nome);
			fseek(arq, (local)*sizeof(persona), SEEK_SET);
		}
	}
}
////////////	EXCLUIR FISICAMENTE PERSONAGEM		///////////////////////////////////////////////////////////////////////
void excluirFisicamentePersonagem(FILE **arq, char arquivo[]) {
	tPersonagem persona;
	FILE *arqTemp = fopen("personagens.aux", "wb");
	if (arqTemp == NULL)
		return;
	fseek(*arq, 0, SEEK_SET);
    while (fread(&persona, sizeof(persona), 1, *arq))
    	if (persona.deletado != '*')
			fwrite(&persona, sizeof(persona), 1, arqTemp);
	fclose(*arq);
	fclose(arqTemp);
	remove(arquivo);
	rename("personagens.aux", arquivo);
	*arq = abrirArquivo(arquivo);
}

// - - - - - ITENS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////// LER UM ITEM DO ARQUIVO /////////////////////////////////////////////////////////////////////////////////////
tItem lerItem(int local, FILE *arq) {
	tItem objeto;
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
    fread(&objeto, sizeof(objeto), 1, arq);
 	return objeto;
}
////////////// CONSULTAR O ARQUIVO DE ITENS ///////////////////////////////////////////////////////////////////////////////
int consultarItem(char nome[], FILE *arq) {
	tItem objeto;
	int local=0;
	fseek(arq, 0, SEEK_SET);
    while (fread(&objeto, sizeof(objeto), 1, arq)) {
    	local++;
    	if ((strcmp(objeto.nome, nome) == 0) && (objeto.deletado != '*'))
    		return local;
	}
	return -1;
}
////////////// 		MOSTRAR	ITEM	 		///////////////////////////////////////////////////////////////////////////////
void mostrarItem(tItem item){
	int curX, curY, i;
	aleaBackground();
	curX = GetconsoleCursorX();
	curY = GetconsoleCursorY();
	for(i = 0; i < 8; i++)
		printf("%-71s\n", "");
	gotoxy(curX, curY);
	textcolor(0);
	printf("-----------------------------------------------------------------------\n");
	printf("Nome: %s\nTier: %c\n", item.nome, item.tier);
   	printf("-----------------------------------------------------------------------\n");
    printf("Descricao: %.60s\n", item.descr);
    if(strlen(item.descr) > 60){
    	printf("%.71s\n", &item.descr[60]);
    	if(strlen(item.descr) > 131)
    		printf("%s\n", &item.descr[131]);
	}
	printf("-----------------------------------------------------------------------\n");	
}
////////////// LISTA OS ITENS DO ARQUIVO //////////////////////////////////////////////////////////////////////////////////
void listarItens(FILE *arq) {
	tItem objeto;
	fseek(arq, 0, SEEK_SET);
    while (fread(&objeto, sizeof(objeto), 1, arq))
    	if (objeto.deletado != '*'){
			mostrarItem(objeto);
	}
	backgroundcolor(BLACK);
	textcolor(LIGHTGRAY);
}
////////////// GRAVA OS OBJETOS NO ARQUIVO ////////////////////////////////////////////////////////////////////////////////
void gravarItem(tItem objeto, int local, FILE *arq) {
	if (local <= 0) {
		objeto.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
	fwrite(&objeto, sizeof(objeto), 1, arq);
}
////////////// MARCA O ITEM COM A FLAG DE EXCLUSAO ////////////////////////////////////////////////////////////////////////
void excluirItem(int local, FILE *arq) {
	tItem objeto;
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
    fread(&objeto, sizeof(objeto), 1, arq);
    objeto.deletado = '*';
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
	fwrite(&objeto, sizeof(objeto), 1, arq);
}
////////////// EXCLUI O ITEM DO ARQUIVO ///////////////////////////////////////////////////////////////////////////////////
void excluirFisicamenteItem(FILE **arq, char arquivo[]) {
	tItem objeto;
	FILE *arqTemp = fopen("itens.aux", "wb");
	if (arqTemp == NULL)
		return;
	fseek(*arq, 0, SEEK_SET);
    while (fread(&objeto, sizeof(objeto), 1, *arq))
    	if (objeto.deletado != '*')
			fwrite(&objeto, sizeof(objeto), 1, arqTemp);
	fclose(*arq);
	fclose(arqTemp);
	remove(arquivo);
	rename("itens.aux", arquivo);
	*arq = abrirArquivo(arquivo);
}

////////////////////////////////////////	CONVERTER PARA XML		///////////////////////////////////////////////////////
void criaXML_P(FILE *arqPersona) {
	int i;
	tPersonagem persona;
	FILE *arqXML = fopen("personagens.xml", "w");
	if (arqXML == NULL) {
		printf("ERRO! O arquivo nao pode ser aberto!");
		return;
	}
	fseek(arqPersona, 0, SEEK_SET);
	fprintf(arqXML, "<?xml version=\"1.0\" ?> \n");
	fprintf(arqXML, "<Personagens>\n");
	while (fread(&persona, sizeof(persona), 1, arqPersona)) {
		if(persona.deletado != '*') {
			fprintf(arqXML, "\t<Personagem>\n");
			fprintf(arqXML, "\t\t<nome>\"%s\"</nome>\n", persona.nome);
			fprintf(arqXML, "\t\t<raca>\"%s\"</raca>\n", persona.raca);
			fprintf(arqXML, "\t\t<classe>\"%s\"</classe>\n", persona.classe);
			fprintf(arqXML, "\t\t<nivel>%i</nivel>\n", persona.nivel);
			for(i = 0; i< 6; i++){
				fprintf(arqXML, "\t\t<habilidade>\n");
				fprintf(arqXML, "\t\t\t<nome>\"%s\"</nome>\n", persona.habil[i].nome);
				fprintf(arqXML, "\t\t\t<valor>%i</valor>\n", persona.habil[i].valor);
				fprintf(arqXML, "\t\t</habilidade>\n");
			}
			for(i = 0; i < 18; i++){
				fprintf(arqXML, "\t\t<pericia>\n");
				fprintf(arqXML, "\t\t\t<nome>\"%s\"</nome>\n", persona.pericias[i].nome);
				fprintf(arqXML, "\t\t\t<valor>%i</valor>\n", persona.pericias[i].valor);
				fprintf(arqXML, "\t\t</pericia>\n");
			}
			fprintf(arqXML, "\t\t<notas>\"%s\"</notas>\n", persona.notas);
			fprintf(arqXML, "\t\t<codJogador>%i</codJogador>\n", persona.codJogador);
			fprintf(arqXML, "\t</Personagem>\n");
		}
	}
	fprintf(arqXML, "</Personagens>\n");
	fclose(arqXML);
	printf("\nExportando \"personagens.xml\"... Pressione qualquer tecla para continuar.");
	_getch();
}
void criaXML_J(FILE *arqJogador) {
	tJogador jogador;
	FILE *arqXML = fopen("jogadores.xml", "w");
	if (arqXML == NULL) {
		printf("ERRO! O arquivo nao pode ser aberto!");
		return;
	}	
	fseek(arqJogador, 0, SEEK_SET);
	fprintf(arqXML, "<?xml version=\"1.0\" ?> \n");
	fprintf(arqXML, "<Jogadores>\n");
	while (fread(&jogador, sizeof(jogador), 1, arqJogador)) {
		if(jogador.deletado != '*') {
			fprintf(arqXML, "\t<Jogador>\n");
			fprintf(arqXML, "\t\t<nome>\"%s\"</nome>\n", jogador.nome);
			fprintf(arqXML, "\t\t<codigo>%i</codigo>\n", jogador.codigo);
			fprintf(arqXML, "\t</Jogador>\n");
		}
	}
	fprintf(arqXML, "</Jogadores>\n");
	fclose(arqXML);
	printf("\nExportando \"jogador.xml\"... Pressione qualquer tecla para continuar.");
	_getch();
}
void criaXML_I(FILE *arqItem) {
	tItem item;
	FILE *arqXML = fopen("itens.xml", "w");
	if (arqXML == NULL) {
		printf("ERRO! O arquivo nao pode ser aberto!");
		return;
	}
	fseek(arqItem, 0, SEEK_SET);
	fprintf(arqXML, "<?xml version=\"1.0\" ?> \n");
	fprintf(arqXML, "<Itens>\n");
	while (fread(&item, sizeof(item), 1, arqItem)) {
		if(item.deletado != '*') {
			fprintf(arqXML, "\t<Item>\n");
			fprintf(arqXML, "\t\t<nome>\"%s\"</nome>\n", item.nome);
			fprintf(arqXML, "\t\t<tier>%c</tier>\n", item.tier);
			fprintf(arqXML, "\t\t<descricao>\"%s\"</descricao>\n", item.descr);
			fprintf(arqXML, "\t</Item>\n");
		}
	}
	fprintf(arqXML, "</Itens>\n");
	fclose(arqXML);
	printf("\nExportando \"itens.xml\"... Pressione qualquer tecla para continuar.");
	_getch();
}
//////////////////////////////////////////////////// MAIN /////////////////////////////////////////////////////////////////
int main(){
    int escolha1, escolha2, escolhaM, codigo, local, CORESCRITA = WHITE, tam1 = 6, tam2 = 6, tamM = 6, primeiro;
    char *menu1[]= {"Personagem", "Jogador", "Item", "Esvaziar lixeira", "Exportar dados para XML", "Sair"};
	char *menu2[]= {"Incluir", "Listar", "Consultar", "Alterar", "Excluir", "Voltar"};
	char *menuMod[]= {"Habilidades", "Pericias", "Nivel", "Classe de Armadura", "Equipamento/Pertences", "Voltar"};
    tPersonagem personagem;
	tJogador jogador;
	tItem item;
	FILE *arqPersonagem, *arqJogador, *arqItem;
	
	arqPersonagem = abrirArquivo("personagens.dat");
	arqJogador = abrirArquivo("jogadores.dat");
	arqItem = abrirArquivo("itens.dat");
	if ((arqPersonagem == NULL) || (arqJogador == NULL) || (arqItem == NULL)) {
		printf("ERRO! O arquivo nao pode ser aberto!");
		return 1;
	}
	do {
		clear_screen();
		escolha1 = menu(menu1, tam1, "MENU"); // escolha de submenu
		switch (escolha1){
			case 1:	// ---------------- menu personagens ----------------
				do {
					clear_screen();
					escolha2 = menu(menu2, tam2, "Personagem");
					switch (escolha2){
						case 1: 
							clear_screen();
							iniciaHab(personagem.habil);
							iniciaPericias(personagem.pericias);
							printf("\t\t\tAtencao!!! Use %c e %c para alternar e Enter para confirmar\n", 24, 25);
							printf("\n---> Inclusao de Personagem <---\n\n");
							jogador.codigo = escolheJogador(arqJogador);
							personagem.codJogador = jogador.codigo;
							printf("\nDigite o nome do personagem: \n");
							fflush(stdin);
							do{
								textcolor(CORESCRITA);
								gets(personagem.nome);
								if(strcmp(personagem.nome, "") == 0){
									textcolor(RED);
									printf("O nome nao deve ficar vazio!\n");
								}
								if(consultarPersonagem(personagem.nome, arqPersonagem) > 0){
									textcolor(RED);
									printf("Esse personagem ja existe!\n");
								}
							}while(consultarPersonagem(personagem.nome, arqPersonagem) > 0 || strcmp(personagem.nome, "") == 0);
							textcolor(LIGHTGRAY);
							printf("\n");
							strcpy(personagem.raca, escolheRaca());
							printf("\n");
							strcpy(personagem.classe, escolheClasse());
							printf("\nInforme o nivel do personagem: ");
							do{
								textcolor(CORESCRITA);
								scanf("%d", &personagem.nivel);
								if(personagem.nivel > 20 || personagem.nivel < 1){
									textcolor(RED);
									printf("O nivel de um personagem deve ser entre 1 e 20: ");
								}
							}while(personagem.nivel > 20 || personagem.nivel < 1);
							textcolor(LIGHTGRAY);
							printf("\nInforme a CA do personagem: ");
							do{
								textcolor(CORESCRITA);
								scanf("%d", &personagem.CA);
								if(personagem.CA < 0){
									textcolor(RED);
									printf("A classe de armadura nao pode ser negativa: ");
								}
							}while(personagem.CA < 0);
							textcolor(LIGHTGRAY);
							alteraHabilidades(personagem.habil);
							alteraPericias(personagem.pericias);
							valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
							printf("\nInforme, resumidamente, o equipamento do personagem: ");
							fflush(stdin);
							textcolor(CORESCRITA);
							gets(personagem.notas);
							textcolor(LIGHTGRAY);
							salvarPersonagem(personagem, -1, arqPersonagem);
							printf("\nO personagem foi salvo!");
							pausa();
							break;
						case 2:
							clear_screen();
							printf("\n---> Listagem de Personagem <---\n\n");
							listarPersonagems(arqPersonagem, arqJogador);
							pausa();
							break;
						case 3: 
							clear_screen();
							printf("\n---> Consulta de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							local = consultarPersonagem(personagem.nome, arqPersonagem);
							if (local > 0) {
								personagem = lerPersonagem(local, arqPersonagem);
								local = consultarJogador(personagem.codJogador, arqJogador);
								jogador = lerJogador(local, arqJogador);
								mostrarPersonagem(personagem, jogador);
								backgroundcolor(BLACK);
								textcolor(LIGHTGRAY);
							}
							else
								printf("\nPersonagem nao encontrado!");
							pausa();
							break;
						case 4:
							clear_screen();
							printf("\n---> Alteracao de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							local = consultarPersonagem(personagem.nome, arqPersonagem);
							if (local > 0) {
								personagem = lerPersonagem(local, arqPersonagem);
								do{
									escolhaM = menu(menuMod, tamM, "O que deseja modificar?");
									switch(escolhaM){
										case 1:
											printf("\nModificacao nas habilidades\n");
											alteraHabilidades(personagem.habil);
											break;
										case 2:
											printf("\nModificacao nas pericias\n");
											alteraPericias(personagem.pericias);
											break;
										case 3:
											printf("\nNivel: %i\n", personagem.nivel);
											printf("Digite o novo nivel: ");
											scanf("%d", &personagem.nivel);
											valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
											break;
										case 4:
											printf("\nClasse de armadura: %i\n", personagem.CA);
											printf("Digite a nova armadura: ");
											scanf("%d", &personagem.CA);
											break;
										case 5:
											printf("\nEquipamento/Pertences: ");
											alteraString(personagem.notas);
											break;
									}
								}while(escolhaM != 0);
								salvarPersonagem(personagem, local, arqPersonagem);
								printf("\nAs alteracoes foram salvas!");
							}else
								printf("Personagem nao encontrado!\n");
							pausa();
							break;
				        case 5:
							clear_screen();
							printf("\n---> Exclusao de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							local = consultarPersonagem(personagem.nome, arqPersonagem);
							if (local > 0){
								excluirPersonagem(local, arqPersonagem);
								printf("Exclusao concluida\n");
							}else
								printf("Personagem nao encontrado!\n");
							pausa();
							break;
					}
				}while (escolha2 != 0);
				break;
			case 2: // ---------------- menu jogador ----------------
				do {
					clear_screen();
					escolha2 = menu(menu2, tam2, "Jogador");
					switch (escolha2) {
						case 1:
							clear_screen();
							printf("\n---> Registro de Jogador <---\n\n");	
							fseek(arqJogador, -(int)sizeof(jogador), SEEK_END);
							if(!fread(&jogador, sizeof(jogador), 1, arqJogador)){
								jogador.codigo = 1;
							}else{
								jogador.codigo++;	
							}
							printf("Jogador %i", jogador.codigo);
							printf("\nDigite o nome do jogador: ");
							fflush(stdin);
							do{
								gets(jogador.nome);
								if(strcmp(jogador.nome, "") == 0){
									printf("O nome nao deve ficar vazio!\n");
								}
							}while(strcmp(jogador.nome, "") == 0);
							gravarJogador(jogador, -1, arqJogador);
							printf("\nO jogador foi salvo!");
							pausa();
							break;
						case 2:
							clear_screen();
							printf("\n---> Listagem de Jogador <---\n\n");
							listarJogadores(arqJogador, arqPersonagem);
							pausa();
							break;
						case 3:
							clear_screen();
							printf("\n---> Consulta de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0){
								jogador = lerJogador(local, arqJogador);
								printf("Nome...........: %s\n",  jogador.nome);
								printf("Personagens....: ");
								fseek(arqPersonagem, 0, SEEK_SET);
								primeiro = 0;
					    		while (fread(&personagem, sizeof(personagem), 1, arqPersonagem)){
						    		if(personagem.codJogador == jogador.codigo){
						    			if(primeiro == 0)
											printf("%s", personagem.nome);
										else
											printf(", %s", personagem.nome);
										primeiro++;
									}
								}
							}
							else
								printf("Codigo nao encontrado!\n");
							pausa();
							break;
						case 4:
							clear_screen();
							printf("\n---> Alteracao de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0) {
								jogador = lerJogador(local, arqJogador);
								printf("Nome..............: %s\n", jogador.nome);
								printf("Digite o nome.....: ");
								fflush(stdin);
								gets(jogador.nome);
								gravarJogador(jogador, local, arqJogador);
							}
							else
								printf("Codigo nao encontrado!\n");
							pausa();
							break;
						case 5:
							clear_screen();
							printf("\n---> Exclusao de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0){
								jogador = lerJogador(local, arqJogador);
								printf("Nome..............: %s\n", jogador.nome);
								printf("Deseja continuar? Personagens ligados a esse jogador serao excluidos\n");
								printf("\t\t(Pressione enter para confirmar)\n");
								if(_getch() == 13){
									excluiPersonagemLigado(codigo, arqPersonagem);
									excluirJogador(local, arqJogador);
									printf("Exclusao concluida");
								}else{
									printf("\nVoltando...");
								}
							}
							else
								printf("Codigo nao encontrado!\n");
				        	pausa();
				    }
				}while (escolha2 != 0);
				break;
			case 3: // ---------------- menu item ----------------
				do {
					clear_screen();
					escolha2 = menu(menu2, tam2, "Item");
					switch (escolha2) {
						case 1:
							clear_screen();
							printf("\n---> Registro de Item <---\n\n");	
							printf("\nDigite o nome do item: ");
							fflush(stdin);
							gets(item.nome);
							while(consultarItem(item.nome, arqItem) > 0){
								printf("\nItem ja existe, tente novamente: \n");
								gets(item.nome);
							}
							printf("\nDigite o tier do item (F=Comum; E=Incomum; D=Raro; C=Muito Raro; B= Lendario; A=Artefato): ");
							do{
								item.tier = _getch();
								item.tier = toupper(item.tier);
								if(item.tier < 65 || item.tier > 70)
									printf("\nErro! Digite uma letra valida:");
							} while(item.tier < 65 || item.tier > 70);
							printf("\nInforme, resumidamente, a descricao do item: ");
							fflush(stdin);
							gets(item.descr);
							gravarItem(item, -1, arqItem);
							printf("\nO item foi salvo!");
							pausa();
							break;
						case 2:
							clear_screen();
							printf("\n---> Listagem de Item <---\n\n");
							listarItens(arqItem);
							pausa();
							break;
						case 3:
							clear_screen();
							printf("\n---> Consulta de Item <---\n\n");
							printf("Digite o nome do Item: ");
							fflush(stdin);
							gets(item.nome);
							local = consultarItem(item.nome, arqItem);
							if (local > 0) {
								item = lerItem(local, arqItem);
								mostrarItem(item);
								backgroundcolor(BLACK);
								textcolor(LIGHTGRAY);
							}
							else
								printf("Item nao encontrado!\n");
							pausa();
							break;
						case 4:
							clear_screen();
							printf("\n---> Alteracao de Item <---\n\n");
							printf("Digite o nome do Item: ");
							fflush(stdin);
							gets(item.nome);
							local = consultarItem(item.nome, arqItem);
							if (local > 0) {
								item = lerItem(local, arqItem);
								printf("Nome..............: %s\n", item.nome);
								printf("Digite o nome.....: ");
								fflush(stdin);
								gets(item.nome);
								printf("\nDescricao: ");
								alteraString(item.descr);
								gravarItem(item, local, arqItem);
								printf("\nItem alterado com sucesso!");
							}
							else
								printf("Codigo nao encontrado!\n");
							pausa();
							break;
						case 5:
							clear_screen();
							printf("\n---> Exclusao de Item <---\n\n");
							printf("Digite o nome do Item: ");
							fflush(stdin);
							gets(item.nome);
							local = consultarItem(item.nome, arqItem);
							if (local > 0){
								excluirItem(local, arqItem);
								printf("Exclusao concluida\n");
							}else
								printf("Item nao encontrado!\n");
							pausa();
							break;
				    }
				}while (escolha2 != 0);
				break;
			case 4:
				excluirFisicamenteJogador(&arqJogador, "jogadores.dat");
				excluirFisicamentePersonagem(&arqPersonagem, "personagens.dat");
				excluirFisicamenteItem(&arqItem, "itens.dat");
				printf("Lixeira esvaziada com sucesso!\n");
				pausa();
				break;
			case 5:
				criaXML_P(arqPersonagem);
				criaXML_J(arqJogador);
				criaXML_I(arqItem);				
		}
	}while(escolha1 != 0);
	fclose(arqPersonagem);
	fclose(arqJogador);
	fclose(arqItem);
    return 0;
}