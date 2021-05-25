#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "color.h"
//-------------------------- ENTIDADES -----------------------------------------------------------------------------------------
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
//-----------------------FUNCOES-----------------------------------------------------------------------------------------------
//-----------------------INICIA O NOME, VALOR E OS MARCADORES DAS HABILIDADES -------------------------------------------------
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
//-----------------------INICIA O NOME E OS MARCADORES DAS PERICIAS -----------------------------------------------------------
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
//-----------------------ALTERA O MARCADOR DAS PERICIAS -----------------------------------------------------------------------
void alteraPericias(skill pericias[]){
	char setas;
	int tam = 18, opcao = 0, i;
	do{	
		printf("Marque suas pericias treinadas: (x para marcar e desmarcar), e (enter para terminar as escolhas)\n");
		for (i = 0; i < tam; ++i) {
			if(pericias[i].marcado != ' '){
				backgroundcolor(GREEN);
			}
			if(i == opcao)
				textcolor(RED);
			printf("%s\n", pericias[i].nome);
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
				pericias[i].marcado = '!';
		}
	}
}
//-----------------------ALTERA O VALOR DAS HABILIDADES -----------------------------------------------------------------------
void alteraHabilidades(skill habilidades[]){
	int i, tam = 6, opcao = 0;
	char setas;
	do{
		printf("Informe os valores das habilidades do personagem: \n");
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
		system("cls");
	} while (setas != 13);
}
//-----------------------ALTERA O VALOR DAS PERICIAS --------------------------------------------------------------------------
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
//---------------------ESCOLHE A CLASSE ---------------------------------------------------------------------------------------
const char * escolheClasse(){
	char setas;
	int tam = 12, opcao = 0, i;
	//Se for char, a variavel é deletada antes de retornar para main
	static char classe[12][20] = {"Barbaro", "Bardo", "Bruxo", "Clerigo", "Druida",
	 "Feiticeiro", 	"Guardiao", "Guerreiro", "Ladino",	"Mago", "Monge", "Paladino"};
	do{	
		printf("Escolha a classe do personagem: (Enter Para Confirmar)\n");
		for (i = 0; i < tam; ++i) {
			if(i == opcao)
				textcolor(RED);
			printf("%s\n", classe[i]);
			textcolor(LIGHTGRAY);
		}
		do{
			setas = _getch();
		}while(setas != 72 && setas != 80 && setas != 13);
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % tam;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = tam-1;
		}
		system("cls");
	}while(setas != 13);
	return (classe[opcao]);
}
//---------------------ESCOLHE A RAÇA ---------------------------------------------------------------------------------------
const char * escolheRaca(){
	char setas;
	//Se for char, a variavel é deletada antes de retornar para main
	static char raca[14][20] = {"Anao da Colina", "Anao da Montanha", "Draconato", "Elfo (Alto)",  "Elfo (Drow)", "Elfo da Floresta",
	"Gnomo da Floresta", "Gnomo das Rochas", "Halfling Pes Leves", "Halfling Robusto", "Humano", "Meio-Elfo",	"Meio-Orc", "Tieflings"};
	int tam = 14, opcao = 0, i;	
	do{
		printf("Escolha a Raca do personagem: (Enter Para Confirmar)\n");
		for (i = 0; i < tam; ++i) {
			if(i == opcao)
				textcolor(RED);
			printf("%s\n", raca[i]);
			textcolor(LIGHTGRAY);
		}
		do{
			setas = _getch();
		}while(setas != 72 && setas != 80 && setas != 13);
		if(setas == 80)//seta para baixo
			opcao = (opcao + 1) % tam;
		else if(setas == 72){//seta para cima
			opcao = opcao - 1;
			if(opcao == -1) opcao = tam-1;
		}
		system("cls");
	}while(setas != 13);
	return (raca[opcao]);
}
//----------------------- ESCOLHER JOGADOR ------------------------------------------------------------------------------------
int escolheJogador(FILE *arq){
	int opcao = 0, i;
	char setas;
	tJogador jogador;
	if(!(fread(&jogador, sizeof(jogador), 1, arq))){
		printf("E necessario criar um jogador antes de acessar essa funcao: \n");
		printf("Nome do Jogador: ");
		fflush(stdin);
		gets(jogador.nome);
		printf("\nCodigo do Jogador: ");
		scanf("%i", &jogador.codigo);
		fwrite(&jogador, sizeof(jogador), 1, arq);
		return jogador.codigo;
	}
	do{
		printf("Escolha o jogador: (enter para confirmar)\n");
		fseek(arq, 0, SEEK_SET);
		i = 0;
		while (fread(&jogador, sizeof(jogador), 1, arq)){
				if(i == opcao)
					textcolor(RED);
				printf("%s\n", jogador.nome);
				textcolor(LIGHTGRAY);
				i++;
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
		system("cls");
	}while(setas != 13);
	fseek(arq, (sizeof(jogador)*opcao), SEEK_SET);
	fread(&jogador, sizeof(jogador), 1, arq);
	return jogador.codigo;
}
//----------------------- MENU -------------------------------------------------------------------------------------------------
int menu(char *texto[], int tam, char string[]){
	int opcao = 0, i, getT;
	char esc;
	printf("\n\n*** %s ***\n\n", string);
	for (i = 0; i < tam; ++i) {
		getT = (i+1) - (((i+1) / tam)*(i+1));
		printf("%i. %s\n", getT,texto[i]);
	}
	do{
		esc = _getch();	
	}while(esc < 48 && esc > 57);
	
	return esc - 48;
}

//-----------------------MANIPULACOES DE ARQUIVO (CRUDS)-----------------------------------------------------------------------
//Funcao generica pra abertura de arquivos
FILE *abrirArquivo(char arquivo[]){
	FILE *arq = fopen(arquivo, "r+b");
	if(arq == NULL)
		arq = fopen(arquivo, "w+b");
	return arq;
}

// - - - - - Jogadores - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////// LER UM JOGADOR DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
tJogador lerJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
 	return player;
}
////////////// CONSULTAR O ARQUIVO DE JOGADORES ////////////////////////////////////////////////////////////////////////////////////
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
////////////// LISTAR OS JOGADORES DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void listarJogadores(FILE *arq) {
	tJogador player;
	fseek(arq, 0, SEEK_SET);
   	printf("Codigo\tNOME\n");
   	printf("------------------------------------\n");
    while (fread(&player, sizeof(player), 1, arq))
    	if (player.deletado != '*')
    		printf("%5d\t%-30s\n", player.codigo, player.nome);
}
////////////// GRAVA OS JOGADORES NO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void gravarJogador(tJogador player, int local, FILE *arq) {
	if (local <= 0) {
		player.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof(player), SEEK_SET);
	fwrite(&player, sizeof(player), 1, arq);
}
////////////// MARCA O JOGADOR COM A FLAG DE EXCLUSAO ////////////////////////////////////////////////////////////////////////////////////
void excluirJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
    player.deletado = '*';
	//fseek(arq, -sizeof(player), SEEK_CUR); // se der errador trocar por esse
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
	fwrite(&player, sizeof(player), 1, arq);
}
////////////// EXCLUI O JOGADOR DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
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

// - - - - - PERSONAGENS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
////////////// LER UM PERSONAGEM DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
tPersonagem lerPersonagem(int local, FILE *arq){
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
	fread(&persona, sizeof(persona), 1, arq);
	return persona;
}
////////////// ESCREVE O PERSONAGEM NO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void salvarPersonagem(tPersonagem persona, int local, FILE *arq){
	if (local <= 0) {
		persona.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof (persona), SEEK_SET);
	fwrite(&persona, sizeof (persona), 1, arq);
}
////////////// MOSTRA O PERSONAGEM NO TERMINAL ////////////////////////////////////////////////////////////////////////////////////
void mostrarPersonagem(tPersonagem persona, tJogador player) {
	int mod[6], i;

	if (persona.deletado != '*'){
		for (i=0;i<6;i++){
			mod[i]=(persona.habil[i].valor/2) - 5;
		}
		printf("-----------------------------------------------------------------INICIO\n");
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
			if(persona.pericias[i].marcado == '*' || persona.pericias[i].marcado == '*')
				printf("%s +%d; ", persona.pericias[i].nome, persona.pericias[i].valor);
		}
		printf("\nPercepcao passiva: %d\n", (persona.habil[12].valor+10));
		printf("-----------------------------------------------------------------------\n");
		printf("Equipamento/Pertences: %-200s\n", persona.notas);
		printf("--------------------------------------------------------------------FIM\n");
	}
}
////////////// LISTAR OS PERSONAGENS DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void listarPersonagems(FILE *arqPersona, FILE *arqJogador) {
	tPersonagem persona;
	tJogador player;
	int local = 0;
	fseek(arqPersona, 0, SEEK_SET);
	while (fread(&persona, sizeof(persona), 1, arqPersona)) {
		if (persona.deletado != '*') {
			player = lerJogador(consultarJogador(persona.codJogador, arqJogador), arqJogador);
			mostrarPersonagem(persona, player);
			}
	}
	printf("\n\n\nPressione qualquer tecla para continuar.");
	_getch();
}
////////////// CONSULTAR O ARQUIVO DE PERSONAGENS ////////////////////////////////////////////////////////////////////////////////////
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
////////////// MARCA O PERSONAGEM COM A FLAG DE EXCLUSAO ////////////////////////////////////////////////////////////////////////////////////
void excluirPersonagem(int local, FILE *arq) {
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
    fread(&persona, sizeof(persona), 1, arq);
    persona.deletado = '*';
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
	//fseek(arq, -sizeof(persona), SEEK_CUR); // se nao funcionar trocar por essa
	fwrite(&persona, sizeof(persona), 1, arq);
}
//////////////////////// EXCLUI O PERSONAGEM LIGADO AO JOGADOR QUE VAI SER DELETADO //////////////////////////////////////////
void excluiPersonagemLigado(int cod, FILE *arq) {
	tPersonagem persona;
	int local=0;
	fseek(arq, 0, SEEK_SET);
    while (fread(&persona, sizeof(persona), 1, arq)) {
    	local++;
    	if ((persona.codJogador == cod) && (persona.deletado != '*'))
    		excluirPersonagem(local, arq);
	}
}
////////////// EXCLUI O PERSONAGEM DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
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
////////////// LER UM JOGADOR DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
tItem lerItem(int local, FILE *arq) {
	tItem objeto;
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
    fread(&objeto, sizeof(objeto), 1, arq);
 	return objeto;
}
////////////// CONSULTAR O ARQUIVO DE ITENS ////////////////////////////////////////////////////////////////////////////////////
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
////////////// LISTAR OS ITENS DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void listarItens(FILE *arq) {
	tItem objeto;
	fseek(arq, 0, SEEK_SET);
    while (fread(&objeto, sizeof(objeto), 1, arq))
    	if (objeto.deletado != '*'){
			printf("-----------------------------------------------------------------INICIO\n");
			printf("Nome: %s\nTier: %c\n", objeto.nome, objeto.tier);
   			printf("------------------------------------\n");
    		printf("Descricao: %-200s\n", objeto.descr);
			printf("--------------------------------------------------------------------FIM\n\n");
		}
}
////////////// GRAVA OS OBJETOS NO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
void gravarJogador(tItem objeto, int local, FILE *arq) {
	if (local <= 0) {
		objeto.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
	fwrite(&objeto, sizeof(objeto), 1, arq);
}
////////////// MARCA O ITEM COM A FLAG DE EXCLUSAO ////////////////////////////////////////////////////////////////////////////////////
void excluirItem(int local, FILE *arq) {
	tItem objeto;
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
    fread(&objeto, sizeof(objeto), 1, arq);
    objeto.deletado = '*';
	fseek(arq, (local-1)*sizeof(objeto), SEEK_SET);
	fwrite(&objeto, sizeof(objeto), 1, arq);
}
////////////// EXCLUI O ITEM DO ARQUIVO ////////////////////////////////////////////////////////////////////////////////////
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


int main(){
    int escolha1, escolha2, escolhaM, codigo, local;
    char *menu1[]= {"Personagem", "Jogador", "Item", "Esvaziar lixeira", "Sair"};
	char *menu2[]= {"Incluir", "Listar", "Consultar", "Alterar","Excluir", "Voltar"};
	char *menuMod[]= {"Habilidades", "Pericias", "Nivel", "Classe de Armadura", "Equipamento/Pertences", "Voltar"};
	int tam1 = 5, tam2 = 6, tamM = 6;
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
		escolha1 = menu(menu1, tam1, "MENU"); // escolha de submenu
		system("cls");
		switch (escolha1){
			case 1:	// ---------------- menu personagens ----------------
				iniciaHab(personagem.habil);
				iniciaPericias(personagem.pericias);
				do {
					escolha2 = menu(menu2, tam2, "Personagem");
					system("cls");
					switch (escolha2){
						case 1: 
							system("cls");
							printf("---> Inclusao de Personagem <---\n\n");
							jogador.codigo = escolheJogador(arqJogador);
							personagem.codJogador = jogador.codigo;
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							do{
								gets(personagem.nome);
								if(strcmp(personagem.nome, "") == 0){
									printf("O nome nao deve ficar vazio!\n");
								}
								if(consultarPersonagem(personagem.nome, arqPersonagem) > 0){
									printf("Esse personagem ja existe!\n");
								}
							}while(consultarPersonagem(personagem.nome, arqPersonagem) > 0 || strcmp(personagem.nome, "") == 0);
							strcpy(personagem.raca, escolheRaca());
							strcpy(personagem.classe, escolheClasse());
							printf("\nInforme o nivel do personagem: ");
							do{
								scanf("%d", &personagem.nivel);
								if(personagem.nivel > 20){
									printf("O nivel maximo de um personagem deve ser 20: ");
								}
							}while(personagem.nivel > 20);
							printf("\nInforme a CA do personagem: ");
							scanf("%d", &personagem.CA);
							system("cls");
							alteraHabilidades(personagem.habil);
							alteraPericias(personagem.pericias);
							valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
							printf("\nInforme, resumidamente, o equipamento do personagem: ");
							fflush(stdin);
							gets(personagem.notas);
							salvarPersonagem(personagem, -1, arqPersonagem);
							break;
						case 2:
							printf("\n\n---> Listagem de Personagem <---\n\n");
							listarPersonagems(arqPersonagem, arqJogador);
							break;
						case 3: 
							printf("\n\n---> Consulta de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							local = consultarPersonagem(personagem.nome, arqPersonagem);
							if (local > 0) {
								personagem = lerPersonagem(local, arqPersonagem);
								local = consultarJogador(personagem.codJogador, arqJogador);
								jogador = lerJogador(local, arqJogador);
								mostrarPersonagem(personagem, jogador);
							}
							else
								printf("Personagem nao encontrado!\n");
							break;
						case 4:
							printf("\n\n---> Alteracao de Personagem <---\n\n");
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
											printf("\nEquipamento/Pertences: %s\n",  personagem.notas);
											printf("Informe novamente, com as alteracoes: ");
											fflush(stdin);
											gets(personagem.notas);
									}
								}while(escolhaM != 0);
								salvarPersonagem(personagem, local, arqPersonagem);
							}
							else
								printf("Personagem nao encontrado!\n");
							break;
				        case 5:
							printf("\n\n---> Exclusao de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							local = consultarPersonagem(personagem.nome, arqPersonagem);
							if (local > 0)
								excluirPersonagem(local, arqPersonagem);
							else
								printf("Personagem nao encontrado!\n");
							break;
					}
				}while (escolha2 != 0);
				break;
			case 2: // ---------------- menu jogador ----------------
				do {
					escolha2 = menu(menu2, tam2, "Jogador");
					system("cls");
					switch (escolha2) {
						case 1: 
							printf("\n\n---> Registro de Jogador <---\n\n");	
							printf("Digite o codigo do jogador: ");
							scanf("%d", &jogador.codigo);
							while(consultarJogador(jogador.codigo, arqJogador) > 0){
								printf("Codigo ja existe, tente novamente: \n");
								scanf("%d", &jogador.codigo);
							}
							printf("\nDigite o nome do jogador: ");
							fflush(stdin);
							gets(jogador.nome);
							gravarJogador(jogador, -1, arqJogador);
							break;
						case 2: 
							printf("\n\n---> Listagem de Jogador <---\n\n");
							listarJogadores(arqJogador);
							break;
						case 3: 
							printf("\n\n---> Consulta de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0) {
								jogador = lerJogador(local, arqJogador);
								printf("Nome...........: %s\n",  jogador.nome);
							}
							else
								printf("Codigo nao encontrado!\n");
							break;
						case 4: 
							printf("\n\n---> Alteracao de Jogador <---\n\n");
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
							break;
						case 5: 
							printf("\n\n---> Exclusao de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0){
								printf("Deseja continuar? Personagens ligados a esse jogador serao excluidos\n");
								printf("\t\t(Pressione enter para confirmar)");
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
				        }
				    } while (escolha2 != 0);
				break;
			case 3: // ---------------- menu item ----------------
				do {
					escolha2 = menu(menu2, tam2, "Item");
					system("cls");
					switch (escolha2) {
						case 1:
							printf("\n\n---> Registro de Item <---\n\n");	
							printf("\nDigite o nome do item: ");
							fflush(stdin);
							gets(item.nome);
							while(consultarItem(item.nome, arqItem) > 0){
								printf("\nItem ja existe, tente novamente: \n");
								gets(item.nome);
							}
							printf("\nDigite o tier do item (F=Comum; E=Incomum; D=Raro; C=Muito Raro; B= Lendario; A=Artefato): ");
							do{
								scanf("%c", &item.tier);
								if (item.tier == 'a')
									item.tier = 'A';
								if (item.tier == 'b')
									item.tier = 'B';
								if (item.tier == 'c')
									item.tier = 'C';
								if (item.tier == 'd')
									item.tier = 'D';
								if (item.tier == 'e')
									item.tier = 'E';
								if (item.tier == 'f')
									item.tier = 'F';
								if(item.tier != 'A' || item.tier != 'B' || item.tier != 'C' || item.tier != 'D' || item.tier != 'E' || item.tier != 'F')
									printf("\nErro! Digite uma letra valida:");
							} while(item.tier != 'A' || item.tier != 'B' || item.tier != 'C' || item.tier != 'D' || item.tier != 'E' || item.tier != 'F');
							printf("\nInforme, resumidamente, a descricao do item: ");
							fflush(stdin);
							gets(item.descr);
							gravarItem(item, -1, arqItem);
							break;
						case 2: 
							printf("\n\n---> Listagem de Item <---\n\n");
							listarItens(arqItem);
							break;
						case 3: 
							printf("\n\n---> Consulta de Item <---\n\n");
							printf("Digite o nome do Item: ");
							fflush(stdin);
							gets(item.nome);
							local = consultarItem(item.nome, arqItem);
							if (local > 0) {
								item = lerItem(local, arqItem);
								system("cls");
								printf("-----------------------------------------------------------------INICIO\n");
								printf("Nome: %s\nTier: %c\n", item.nome, item.tier);
   								printf("------------------------------------\n");
    							printf("Descricao: %-200s\n", item.descr);
								printf("--------------------------------------------------------------------FIM\n\n");
							}
							else
								printf("Item nao encontrado!\n");
							break;
						case 4: 
							printf("\n\n---> Alteracao de Item <---\n\n");
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
								gravarItem(item, local, arqItem);
							}
							else
								printf("Codigo nao encontrado!\n");
							break;
						case 5: 
							printf("\n\n---> Exclusao de Jogador <---\n\n");
							printf("Digite o codigo: ");
							scanf("%d", &codigo);
							local = consultarJogador(codigo, arqJogador);
							if (local > 0){
								printf("Deseja continuar? Personagens ligados a esse jogador serao excluidos\n");
								printf("\t\t(Pressione enter para confirmar)");
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
				        }
				    } while (escolha2 != 0);
				break;
			case 4:
				break;
		}
	}while(escolha1 != 0);
	fclose(arqPersonagem);
	fclose(arqJogador);
	fclose(arqItem);
    return 0;
}
