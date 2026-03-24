#include <stdlib.h>
#include <stdio.h>
#include <windows.h> // Necesario para SetConsoleCursorPosition
#include <time.h>

#define MAX_VAL 25

#define ESI 218
#define ESD 191
#define EII 192
#define EID 217
#define COL 179
#define FIL 196

#define UP  72
#define DN  80
#define RT  77
#define LF  75

#define PIX  5
#define PIY  2
#define PFX  28
#define PFY  26

void gotoxy           (int x, int y); 
void fnCreaMarco      (int pxi, int pyi, int pxf, int pyf);
int  fnCapturaTeclaEsp();
void fnCrearBoard     ();
void fnDespliegaFigura(); 
void fnTrasladaFiguraH(int mov);  // -1 = Izquierda; +1 = derecha
void fnRotarFiguraH   (int mov);  // -1 = Izquierda; +1 = derecha
void fnTrasladaFiguraV();

int  x,y;
char ch;
int  teclaDigitada;
int  NewX, NewY;
int  pieza[4][4] = {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}; // Figura Z
int  PAX, PAY;

void main() 
{
	fnCrearBoard();
	NewX = 6;
	NewY = 3;
//	gotoxy(6,3);
	
	fnDespliegaFigura();  Sleep (300); 
	teclaDigitada = 1;
	while (teclaDigitada != 0)
	{
		teclaDigitada = fnCapturaTeclaEsp();
		switch (teclaDigitada)
		{
			case DN : fnTrasladaFiguraV(  ); Sleep (200); break;  
			case UP : fnRotarFiguraH   ( 0); 
			          fnTrasladaFiguraH( 0); Sleep (200); break;
			case RT : fnTrasladaFiguraH( 1); Sleep (200); break;
			case LF : fnTrasladaFiguraH(-1); Sleep (200); break;
			default : break;
		}
/*
		gotoxy (NewX, NewY);
		printf ("*");*/
	}
	return;
}

void fnCrearBoard()
{
	int i,j;
	fnCreaMarco(   1,   1, 100,  27);   // Marco principal
	fnCreaMarco(  29,   2,  40,   8);    // Marco pieza
 	fnCreaMarco( PIX, PIY, PFX, PFY);

	// Puntos en el background del board
 	for (i = (PIY + 1); i < (PFY); i++)
 	   for ( j = (PIX + 1); j< (PFX); j++) { gotoxy(j,i); printf ("%c",250); }

    //sleep (1);
    return ;
}

void gotoxy(int x, int y) 
{
    HANDLE hCon;
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void fnCreaMarco(int pxi, int pyi, int pxf, int pyf)
{
int cnt;
	// Impresion de esquinas
	gotoxy (pxi, pyi); printf ("%c",ESI);
	gotoxy (pxi, pyf); printf ("%c",EII);
	gotoxy (pxf, pyi); printf ("%c",ESD);
	gotoxy (pxf, pyf); printf ("%c",EID);

	// Impresion de filas
	for (cnt =  (pxi + 1);cnt <= (pxf - 1);cnt++)
	{
		gotoxy (cnt, pyi); printf ("%c",FIL);
		gotoxy (cnt, pyf); printf ("%c",FIL);
	}
	//Impresion de columnas
	for (cnt =  (pyi + 1);cnt <= (pyf - 1);cnt++)
	{
		gotoxy (pxi,cnt); printf ("%c",COL);
		gotoxy (pxf,cnt); printf ("%c",COL);
	}
	return;
}

/*
	srand((unsigned int)time(NULL));
 	for (x = 1; x <= 40; x++)
 	{
		 y = rand() % MAX_VAL;
		 gotoxy (x,y); printf ("*");
		 Sleep (500);		
	 }
*/ 	

int fnCapturaTeclaEsp()
{
	int tecla, retorno;
    
	tecla = getch();
    if (tecla == 0  || tecla == 224)
	{
        tecla  = getch(); 
        retorno = tecla;
    } 
	else retorno = 0;
	return retorno;
}

void fnDespliegaFigura() 
{
	int cx, cy;
	int i,j;
	cx  = ((PIX + PFX) / 2) - 4;
	cy  = PIY + 1;

	// Toma valores para el despliegue Inicial 
	PAX = cx;
	PAY = cy;
	
	for (i = 0; i <= 3; i++)
	{
		gotoxy (cx,cy);
		for (j = 0; j <= 3; j++)
		{
			if (pieza [i][j] == 0) printf ("%c%c",250,250); else printf ("%c%c", 219, 219);
		} 
		cy++;
	}
		
	return;
}

void fnTrasladaFiguraH(int mov)  // -1 = Izquierda; +1 = derecha
{
	int cx, cy;
	int i,j;

	cx = PAX; 
	cy = PAY;
	for (i = 0; i <= 3; i++)
	{
		gotoxy (cx,cy);
		for (j = 0; j <= 3; j++) printf ("%c%c",250,250); 
		cy++;
	}
	
	switch (mov)
	{
		case -1 : {  if ( PAX > (PIX+1))      PAX -= 2; break; }
		case  1 : {  if ((PAX + 8) < PFX) PAX += 2; break; }
		case  0 : break;
		default : break;
	}

	cx = PAX; 
	cy = PAY;
	for (i = 0; i <= 3; i++)
	{
		gotoxy (cx,cy);
		for (j = 0; j <= 3; j++)
		{
			if (pieza [i][j] == 0) printf ("%c%c",250,250); else printf ("%c%c", 219, 219);
		} 
		cy++;
	}
	return;
}

void fnRotarFiguraH(int mov)  // -1 = Izquierda; +1 = derecha
{
    int tmpPieza[4][4]; 
	int i,j;

	// Rotar derecha
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++) tmpPieza[j][2-i] = pieza [i][j];
	}

	// Copiar lo rotado
	for (i = 0; i <= 2; i++)
	{
		for (j = 0; j <= 2; j++)
			pieza [i][j] = tmpPieza [i][j]; 
	} 
	
	return;
}

void fnTrasladaFiguraV() 
{
	int cx, cy;
	int i,j;

	cx = PAX; 
	cy = PAY;
	for (i = 0; i <= 3; i++)
	{
		gotoxy (cx,cy);
		for (j = 0; j <= 3; j++) printf ("%c%c",250,250); 
		cy++;
	}

	if ( PAY < (PFY-4))      PAY++;

	cx = PAX; 
	cy = PAY;
	for (i = 0; i <= 3; i++)
	{
		gotoxy (cx,cy);
		for (j = 0; j <= 3; j++)
		{
			if (pieza [i][j] == 0) printf ("%c%c",250,250); else printf ("%c%c", 219, 219);
		} 
		cy++;
	}
	return;
}


