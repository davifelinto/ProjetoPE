#ifndef USEFUL_H
#define USEFUL_H
#include <windows.h>
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

void textcolor(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
}
void backgroundcolor(int newcolor){
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
}
int randBackground(int lastBackground){
	int i = 1+(rand() % 15);
	while(i == lastBackground)
		i = 1+(rand() % 15);
	backgroundcolor(i);
	return i;
}
void gotoxy(int x, int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput){
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)){
        return cbsi.dwCursorPosition;
    }
    else{
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}
int GetconsoleCursorY(){
	COORD ponto;
	int Y;
	ponto = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	Y = ponto.Y+1;
	return Y;
}
int GetconsoleCursorX(){
	COORD ponto;
	int X;
	ponto = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
	X = ponto.X+1;
	return X;
}
void showcursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void clear_screen(){
    DWORD n;                         /* Number of characters written */
    DWORD size;                      /* number of visible characters */
    COORD coord = {0};               /* Top left screen position */
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    /* Get a handle to the console */
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );

    GetConsoleScreenBufferInfo ( h, &csbi );

    /* Find the number of characters to overwrite */
    size = csbi.dwSize.X * csbi.dwSize.Y;

    /* Overwrite the screen buffer with whitespace */
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );

    /* Reset the cursor to the top left position */
    SetConsoleCursorPosition ( h, coord );
}
void printC(char string[], int color){
	textcolor(color);
	printf("%s", string);
}
void printDnD(){
	textcolor(RED);
	printf("                                          .:/++o++/:.                                               \n");
	printf("     ``                                 .+ssssssssssso.  ``                                         \n");
	printf("     .oo+//::::::::::::::--.``         -sssss/.`.-ossss- .oo+//::::::::::::::--.``                  \n");
	printf("      .ossssssssssssssssssssso+:.`    `ososs+`    -ssss+  .ossssssssssssssssssssso+:.`              \n");
	printf("       `:ossssssssssssssssssssssso:`   o-.os-/.`: /ssss/   `:ossssssssssssssssssssssso:`            \n");
	printf("          -sssssssssssssssssssssssso-  -`/:/`os/o::osso`      -sssssssssssssssssssssssso-           \n");       
	printf("          `ssssssss+.....-:+sssssssss:`-+sso++osoo+/:/.        +///:--::.....-:+sssssssss/          \n");
	printf("          `ssssssss+        -osssssso+.-ssssssosssooo/`      `..-+/://+/:.`     -ossssssss:         \n");
	printf("          `ssssssss+         .ssss+--/+ssss/:+sssso+ss/     :oo+oooossso++:.     .sssssssso`        \n");
	printf("          `ssssssss+          oss+/:.:.+o+:.:oss+:::sss:: `:++o+///+/:/:          ossssssss.        \n");
	printf("          `ssssssss+          osss/:os`-/+--/-.++.::+/+s: -+ss::ossssss+          ossssssss.        \n");
	printf("          `ssssssss+         -sss+-oss/ossos:` :s/.-ss:-`-oso.`osssssss+         .sssssssso`        \n");
	printf("          `ssssssss+       `-osss-.+sssssss:   -:-  :ssso+/:`  o::+oooo+       `-ossssssss-         \n");
	printf("          `sssssssso-----:/osssss.`ssssssss`         -+sssso/.`+/./`.-/:. .--:/osssssssss:          \n");
	printf("          `ssssssssssssssssssssss+.ssssssss.        .++:/osssso++os-:/:ss+-ossssssssssso..----`     \n");
	printf("          .ssssssssssssssssssssss/.sssssssso-`   `./ssss+./ssssssss--:osss/-yssssssss+-`./:++-/`    \n");
	printf("       `-/ossssssssssssssssss+/-`  :sssssssssoo+oossssso- .sssssssssssssss:/sssss+/-`   `/::/::     \n");
	printf("      `.-----------------..``       ://sssssssssssssss/`  .ss:ssssssssso+.`--..``        `...`      \n");
	printf("                                       `:+sssssssso+-`     -o`-osssss+/-`                           \n");
	printf("                                          ``..-..`             `.:///:.`                            \n");
	textcolor(LIGHTGRAY);
}
void printDrag(){
	textcolor(RED);
	printf("\n");
	printf("           `.oNMMMMMMMMMMMMMMMMNMMMMMMMMNydMMm/                    .-  `:yNMh.:+sydmNNNmdhs+-`      \n");
	printf("        `:sdMMMMMMMMMMMMMNNNNNNMMMMMMMmNMMNMMMMs                `:hh`.omMMMMMMMMMMMMMMMMMMMMMNh+.   \n");
	printf("     `/yNMMMMMMMMMMMMNho//osyhdNMMMMMMh./mMMMMMMo              :dMMNdNNNdyyhdmNMMMMMMMMMMMMMMMMMNh: \n");
	printf("   `+yysydNMMMMMMMMh:` `+hmMMMMMMMMMMMMd:`hMMMMMN            `yMMMNdo++shNMMMMNNNMMMMMMMNmhs+//::::-\n");
	printf("          `sMMMMMMMdh+-  .omMMMMMMMMMMMMMNNMMMMMN.   `      -mMNy/-odMMMNdo/-.``.-/sddo:`           \n");
	printf("       -y/  MMMMMh+-   .yMMMMMMmyo/:----:/dMMMMMMMy /m.    :Nh:`+dMMMMd/`                           \n");
	printf("     -hMM: -MMh/` ..  +NmdmNMMMMMMh  .    hMMMMMMMMNMN    .s..sNMMMMN/                              \n");
	printf("    sMMMM` /+. .omM-  -`    `:yMMM.  do` .osyhdMMMMMM/    `-yMMMMMMh.                               \n");
	printf("  .dMMMMm    :hMMMm   :sdmy`   oMN--`:NNdysso:``yMMM+    .yMMMMMMM+                                 \n");
	printf(" .mMMMMMy  :dMMMMMo:smMMN+     .MMMN  .omMMMMMd``Md:   `oNMMMMMMN:                                  \n");
	printf("`mMMMMMM+-hMMMMMMMNMMMMm-      +MMMm`   `/mMMMM/ -    `hMMMMMMMm.                                   \n");
	printf("yMmMMMMMmNMMMMMMMMMMMMd`     `+mdMMMNd:   .NMMMN+/::-. `:yNMMMd`                                    \n");
	printf("s..MMMMMMMMMMMMMMMMMMm.       `.yMNh+`     dMMMMMMMMNNdo- .odh`                                     \n");
	printf("  oMMMMMMMMMMMMMMMMMM:        .//-`        +MMMMMMMMMMMMNh:```                                      \n");
	printf(" .NMMMMMMMMMMMMMMMMMd                       +NMMMMMMMMMMMMMm+.             `                        \n");
	printf(" oMMMMMMMMMMMMM                                                            +h-     :+s+/-`          \n");
	printf(" dMMMMMMMMMMMMM                                                            yMN/     .+mMNmy/.       \n");
	printf(" NMMMMMMMMMMMMM                                                            MMMN`      .NMMMMmo`     \n");
	printf(" MMMMMMMMMMMMMM                                                            MMMM:       yMMMMMMd-    \n");
	printf(" NMMMMMMMMMMMMM                                                            MMMM-      .mMMMMMMMm.   \n");
	printf(" hMMMMMMMMMMMMM                                                            MMMs     `:dMMMMMMMMMs   \n");
	printf(" /MMMMMMMMMMMMM                                                            MMs-.-:+ydMMMMMMMMMMMh   \n");
	printf("  dMMMMMMMMMMMM                                                            MMNNNMMMMMMMMMMMMMMMMo   \n");
	printf("  -NMMMMMMMMMMM                                                            MMMMMMMMMMMMMMMMMMMMd`   \n");
	printf("   :NMMMNMMMMMM                                                            MMMMMMMMMMMMMMMMMMMh.    \n");
	printf("    -dMh-sNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd:        oMMMMMy/MMMMMMMMMMMMMMMMMMMMMMMMMMm+`     \n");
	printf("     `sh  :dMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMd/          -MMMMm` hMMMMMMMMMMMMMMMMMMMMNNms:`       \n");
	printf("       .    /hNMMMMMMMMMMMMMMMMMMMMMMMMMMMMNy:             +MMMy  `dMMMMMMMMMMMMMNyso+/:.           \n");
	printf("              -odNMMMMMMMMMMMMMMMMMMMMMMNy/`                :dMm`  `yMMMMMMMMMMMMMMdyo//::-         \n");
	printf("                 ./ohmNMMMMMMMMMMMMNhs/-                      :so    :hMMMMMMMMMMMMMMMMMd+`         \n");
	textcolor(LIGHTGRAY);
}
#endif

