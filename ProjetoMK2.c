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
}tItens;
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
			printf("A pericia %s localsui especializacao de ladino ou Aptidao de bardo?(s para confirmar)\n", pericias[i].nome);
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
//-----------------------ALTERA O VALOR DAS PERICIAS --------------------------------------------------------------------------
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
//-----------------------MENUS-------------------------------------------------------------------------------------------------
int menu(void){
    int esc;
    printf("\n\n*** MENU ***\n\n");
    printf("1. Personagem\n");
    printf("2. Jogador\n");
    printf("3. Itens\n");
    printf("4. Esvaziar lixeira\n");
    printf("0. Sair\n\n");
    printf("O que quer fazer? ");
    scanf("%d", &esc);
    return esc;
}
int submenu(char entidade[]){
    int esc;
    printf("\n\n*** %s ***\n\n", entidade);
    printf("1. Incluir\n");
    printf("2. Listar\n");
    printf("3. Consultar\n");
    printf("4. Alterar\n");
    printf("5. Excluir\n");
    printf("0. Voltar\n\n");
    printf("O que quer fazer? ");
    scanf("%d", &esc);
    return esc;
}
//-----------------------MANIPULACOES DE ARQUIVO-------------------------------------------------------------------------------
//CHECK
FILE *abrirArquivo(char arquivo[]){
	FILE *arq = fopen(arquivo, "r+b");
	if(arq == NULL)
		arq = fopen(arquivo, "w+b");
	return arq;
}

// - - - - - Jogadores - - - - -// Aparentemente funcionando todos

tJogador lerJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
 	return player;
}
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
void listarJogadores(FILE *arq) {
	tJogador player;
	fseek(arq, 0, SEEK_SET);
   	printf("Coigo\tNOME\n");
   	printf("------------------------------------\n");
    while (fread(&player, sizeof(player), 1, arq))
    	if (player.deletado != '*')
    		printf("%5d\t%-30s\n", player.codigo, player.nome);
}
void gravarJogador(tJogador player, int local, FILE *arq) {
	if (local <= 0) {
		player.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof(player), SEEK_SET);
	fwrite(&player, sizeof(player), 1, arq);
}
void excluirJogador(int local, FILE *arq) {
	tJogador player;
	fseek(arq, (local-1)*sizeof(player), SEEK_SET);
    fread(&player, sizeof(player), 1, arq);
    player.deletado = '*';
	fseek(arq, -sizeof(player), SEEK_CUR);
	fwrite(&player, sizeof(player), 1, arq);
}

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


// - - - - - Personagens - - - - -//
//Ta dando ruim (nao ta pegando os valores certos, talvez problema de posicionamento do cursor no arquivo)//
tPersonagem lerPersonagem(int local, FILE *arq){
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
	fread(&persona, sizeof(persona), 1, arq);
	return persona;
}

void salvarPersonagem(tPersonagem persona, int local, FILE *arq){
	if (local <= 0) {
		persona.deletado = ' ';
		fseek(arq, 0, SEEK_END);
	}
	else
		fseek(arq, (local-1)*sizeof (persona), SEEK_SET);
	fwrite(&persona, sizeof (persona), 1, arq);
}

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
}

void mostrarPersonagem(tPersonagem persona, tJogador player) {
	int mod[6], i;

	if (persona.deletado != '*'){
		for (i=0;i<7;i++){
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
		for(i=0;i<7;i++){
			printf("\t%i(%i)\t", persona.habil[i].valor, mod[i]);
		}
		printf("\n-----------------------------------------------------------------------\n");
		printf("Pericias: ");
		for(i=0;i<19;i++){
			if(persona.pericias[i].marcado == '*' || persona.pericias[i].marcado == '*')
				printf("%s +%d; ", persona.pericias[i].nome, persona.pericias[i].valor);
		}
		printf("\nPercepcao passiva: %d\n", (persona.habil[12].valor+10));
		printf("-----------------------------------------------------------------------\n");
		printf("Equipamento/Pertences: %-200s\n", persona.notas);
		printf("--------------------------------------------------------------------FIM\n");
	}
}

//passar o nome do personagem como parametro de busca?
int consultarPersonagem(int cod, FILE *arq) {
	tPersonagem persona;
	int local=0;
	fseek(arq, 0, SEEK_SET);
    while (fread(&persona, sizeof(persona), 1, arq)) {
    	local++;
    	if ((persona.codJogador == cod) && (persona.deletado != '*'))
    		return local;
	}
	return -1;
}

void excluirPersonagem(int local, FILE *arq) {
	tPersonagem persona;
	fseek(arq, (local-1)*sizeof(persona), SEEK_SET);
    fread(&persona, sizeof(persona), 1, arq);
    persona.deletado = '*';
	fseek(arq, -sizeof(persona), SEEK_CUR);
	fwrite(&persona, sizeof(persona), 1, arq);
}

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

int main(){
    int escolha1, escolha2, codigo, local;
    tPersonagem personagem;
	tJogador jogador;
	FILE *arqPersonagem, *arqJogador; //, *arqItens;

	arqPersonagem = abrirArquivo("personagens.dat");
	arqJogador = abrirArquivo("jogadores.dat");
	//arqItens = abrirArquivo("itens.dat");
	if ((arqPersonagem == NULL) || (arqJogador == NULL) /*|| (arqitens == NULL)*/) {
		printf("ERRO! O arquivo nao pode ser aberto!");
		return 1;
	}
	do {
		escolha1 = menu (); // escolha de submenu
		switch (escolha1){
			case 1:	// menu personagens
				iniciaHab(personagem.habil);
				iniciaPericias(personagem.pericias);
				do {
					escolha2 = submenu("Personagem");
					switch (escolha2){
						case 1: 
							system("cls");
							printf("---> Inclusao de Personagem <---\n\n");
							printf("Digite o nome do personagem: ");
							fflush(stdin);
							gets(personagem.nome);
							printf("\nInforme a raca do personagem: ");
							fflush(stdin);
							gets(personagem.raca);
							printf("\nInforme a classe do personagem: ");
							fflush(stdin);
							gets(personagem.classe);
							printf("\nInforme o nivel do personagem: ");
							scanf("%d", &personagem.nivel);
							printf("\nInforme os valores das habilidades do personagem: ");
							alteraHabilidades(personagem.habil);
							alteraPericias(personagem.pericias);
							valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
							printf("\nInforme, resumidamente, o equipamento do personagem: ");
							fflush(stdin);
							gets(personagem.notas);
							printf("\nPara finalizar...");
							printf("\nInforme o codigo do jogador deste personagem: ");
							scanf("%d", &jogador.codigo);
/*
							local = consultarJogador(1, arqJogador);
							jogador = lerJogador(local, arqJogador);
							mostrarPersonagem(personagem, jogador);
*/
							salvarPersonagem(personagem, -1, arqPersonagem);
							break;
						case 2:
							printf("\n\n---> Listagem de Personagem <---\n\n");
							listarPersonagems(arqPersonagem, arqJogador);
							break;
						case 3: 
							printf("\n\n---> Consulta de Personagem <---\n\n");
							printf("Digite o codigo : ");
							scanf("%d", &codigo);
							local = consultarPersonagem(codigo, arqPersonagem);
							if (local > 0) {
								mostrarPersonagem(personagem, jogador);
							}
							else
								printf("Personagem nao encontrado!\n");
							break;
						case 4:	//---> Acho que dá pra colocar uns if ou outro switch pra saber o que alterar, e não rodar tudo sempre.
								//---> dar um jeito de passar o nome do personagem e não o codigo do jogador.
							printf("\n\n---> Alteracao de Personagem <---\n\n");
							printf("Digite o codigo do jogador deste personagem: ");
							scanf("%d", &codigo);
							local = consultarPersonagem(codigo, arqPersonagem);
							if (local > 0) {
								personagem = lerPersonagem(local, arqPersonagem);

								printf("\nModificacao nas habilidades\n");
								alteraHabilidades(personagem.habil);

								printf("\nModificacao nas pericias\n");
								alteraPericias(personagem.pericias);

								printf("\nNivel: %i\n", personagem.nivel);
								printf("Digite o novo nivel: ");
								scanf("%d", &personagem.nivel);
								valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);

								printf("\nClasse de armadura: %i\n", personagem.CA);
								printf("Digite a nova armadura: ");
								scanf("%d", &personagem.CA);
							
								printf("\nEquipamento/pertences: %s\n",  personagem.notas);
								printf("Informe novamente, com as alteracoes: ");
								fflush(stdin);
								gets(personagem.notas);

								salvarPersonagem(personagem, local, arqPersonagem);
							}
							else
								printf("Codigo nao encontrado!\n");
							break;
				        case 5: //---> dar um jeito de passar o nome do personagem e não o codigo do jogador.
							printf("\n\n---> Exclusao de Personagem <---\n\n");
							printf("Digite o codigo do jogador que controla o personagem: ");
							scanf("%d", &codigo);
							local = consultarPersonagem(codigo, arqPersonagem);
							if (local > 0)
								excluirPersonagem(local, arqPersonagem);
							else
								printf("Codigo nao encontrado!\n");
							break;
					}
				}while (escolha2 != 0);
				break;
			case 2:
				do {
					escolha2 = submenu("Jogador");
					switch (escolha2) {
						case 1: 
							printf("\n\n---> Inclusao de Jogador <---\n\n");
							printf("Digite o codigo do jogador: ");
							scanf("%d", &jogador.codigo);
							printf("Digite o nome do jogador: ");
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
							if (local > 0)
								excluirJogador(local, arqJogador);
							else
								printf("Codigo nao encontrado!\n");
				        }
				    } while (escolha2 != 0);
				break;
			case 3:
			// menu itens
				break;
			case 4:
				break;
		}
	}while(escolha1 != 0);

	/*
    iniciaHab(personagem.habil);
    alteraHabilidades(personagem.habil);
    iniciaPericias(personagem.pericias);
    alteraPericias(personagem.pericias);
    personagem.nivel = 3;
    valorDePericia(personagem.pericias, personagem.habil, personagem.nivel);
	salvarPersonagem(personagem, -1, arqPersonagem);
	fclose(arqPersonagem);
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
	*/

    return 0;
}