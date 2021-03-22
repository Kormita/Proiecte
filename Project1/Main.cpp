//Drepturi de autor: Chirila Sabin, Prozoreanu Eduard, Tudose Tudor , IA2 - 2020
#include <iostream>
#include <fstream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <string>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#define null NULL
#define latime 1800
#define inaltime 950
#define tagBeta 0.51231
#define precizie 0
#define tan1 100000
#define tan2 1/sqrt(3)
#define infinit INT_MAX
#define epsi 0.0001
#define MAX 100
#define MAX1 20

using namespace std;


int top1, top2; // varfurile celor doua stive
int erori[2][30];
char eroriDeAfisat[110][100];
char functii[50][10], functiiRomana[50][100], functiiEngleza[50][100];
int numarErori = 0;
bool ExpresieCorecta, ExpresieGresita, NuSePoateCalcula;
char numeVariabila[40];
int limba = 0;
int fereastraActiva = 0;
double valoareaExpresiei = 0;

double Opd[100]; // stiva operanzilor
char Op[100]; // stiva operatorilor

char OperatiiBinare[200] = "+-*/^<>=#&|$mM";
char OperatiiUnare[200] = "~scarelLtNfCTR";
char Operatii[200] = "~+-*/^<>=#scarelLt&|$mMNfCTR";

char expresie[300];
int d = 0;
char variabile[20][20];
char valoriVariabile[20][20];

void CitesteVariabilaDeLaTastatura(char var[]);

struct functie
{
	char expresie[300];
	char vect[MAX + 1][MAX1];
	int lung; // lungimea efectiva a vectorului
}F;

// EDUARD

struct nod {
	char info;
	int nr;
	nod* urm;
};

struct stiva {
	nod* varf;
	int nrElemente;
};

bool esteVida(stiva S)
{
	return S.nrElemente == 0;
}

void initializeaza(stiva& S)
{
	S.varf = NULL; S.nrElemente = 0;
}

void pop(stiva& S)
{
	if (!esteVida(S))
	{
		nod* varf_nou;
		varf_nou = S.varf->urm;
		delete S.varf;
		S.varf = varf_nou;
		S.nrElemente--;
	}
}
void push(stiva& S, char element, int poz)
{
	nod* nod_nou;
	if (esteVida(S))
	{
		S.nrElemente = 1;
		S.varf = new nod;
		S.varf->info = element;
		S.varf->nr = poz;
		S.varf->urm = NULL;
	}
	else
	{
		S.nrElemente++;
		nod_nou = new nod;
		nod_nou->info = element;
		nod_nou->nr = poz;
		nod_nou->urm = S.varf;
		S.varf = nod_nou;
	}
}
void push2(stiva& S, int element)
{
	nod* nod_nou;
	if (esteVida(S))
	{
		S.nrElemente = 1;
		S.varf = new nod;
		S.varf->nr = element;
		S.varf->urm = NULL;
	}
	else
	{
		S.nrElemente++;
		nod_nou = new nod;
		nod_nou->nr = element;
		nod_nou->urm = S.varf;
		S.varf = nod_nou;
	}
}
char top(stiva& S)
{
	if (esteVida(S)) return 0;
	return S.varf->info;
}
int topS2(stiva& S)
{
	if (esteVida(S)) return 0;
	return S.varf->nr;
}

void afisareErori()
{
	int nr = 0;
	for (int i = 0; i < numarErori; i++)
	{
		int numarEroare = erori[0][i];
		int pozitie = erori[1][i];
		char t[10] = "";
		_itoa_s(pozitie, t, 10);

		switch (numarEroare)
		{
		case 0: strcpy_s(eroriDeAfisat[nr], "Paranteza inchisa fara a fi deschisa precedent!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 1: strcpy_s(eroriDeAfisat[nr], "Dupa functie trebuie sa urmeze ''(''!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 2: strcpy_s(eroriDeAfisat[nr], "Lipseste operatia intre cele doua valori!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 3: strcpy_s(eroriDeAfisat[nr], "Doua operatii una langa alta!!    POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 4: strcpy_s(eroriDeAfisat[nr], "Paranteza inchisa cand se astepta o valoare !!  POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 5: strcpy_s(eroriDeAfisat[nr], "Paranteza deschisa fara inchiderea acesteia!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 6: strcpy_s(eroriDeAfisat[nr], "Functia trebuie sa se termine cu o valoare, nu operand!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 7: strcpy_s(eroriDeAfisat[nr], "Paranteza deschisa fara inchiderea acesteia inainte de comparatie!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 8: strcpy_s(eroriDeAfisat[nr], "Inainte de comparatie trebuie sa se afle o valoare, nu operand!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 9: strcpy_s(eroriDeAfisat[nr], "Lipseste operandul inaintea parantezei!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 10: strcpy_s(eroriDeAfisat[nr], "Parantezare incorecta inainte de '',''!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 11: strcpy_s(eroriDeAfisat[nr], "Functia trebuie sa aiba o singura '',''!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 12: strcpy_s(eroriDeAfisat[nr], "Inainte de '','' nu trebuie sa fie o operatie!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 13: strcpy_s(eroriDeAfisat[nr], "Folosire incorecta a '',''!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 14: strcpy_s(eroriDeAfisat[nr], "Dupa paranteza deschisa nu trebuie sa urmeze o operatie!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 15: strcpy_s(eroriDeAfisat[nr], "Caracter fara semnificatie!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 16: strcpy_s(eroriDeAfisat[nr++], "Functie max/min fara al doi-lea argument!!"); break;
		case 17: strcpy_s(eroriDeAfisat[nr], "Dupa punctul zecimal trebuie sa urmeze cifre!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 18: strcpy_s(eroriDeAfisat[nr], "Folosirea parantezelor fara ceva in interiorul acestora!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 19: strcpy_s(eroriDeAfisat[nr], "Exponent prea mare pentru e sau incepe cu 0 !!  POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 20: strcpy_s(eroriDeAfisat[nr], "Perioada nu este inchisa!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 21: strcpy_s(eroriDeAfisat[nr], "Perioada trebuie sa contina doar cifre!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 22: strcpy_s(eroriDeAfisat[nr], "Perioada inchisa prea tarziu!! :(   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 23: strcpy_s(eroriDeAfisat[nr], "Perioada goala!!!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 24: strcpy_s(eroriDeAfisat[nr], "Dupa punctul zecimal nu poate urma 'e'!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 25: strcpy_s(eroriDeAfisat[nr], "Lipseste exponentul dupa 'e'!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 26: strcpy_s(eroriDeAfisat[nr], "Expresia poate avea maxim o comparatie!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);   break;
		case 30: strcpy_s(eroriDeAfisat[nr], "Valoare incorect introdusa, dupa 0 nu poate urma alta cifra!!   POZITIA: "); strcat_s(eroriDeAfisat[nr++], t);   break;
		default: strcpy_s(eroriDeAfisat[nr++], "EXPRESIE GRESITA!!"); break;

		}
	}
}

void Errors()
{
	int nr = 0;
	for (int i = 0; i < numarErori; i++)
	{
		int numarEroare = erori[0][i];
		int pozitie = erori[1][i];
		char t[10] = "";
		_itoa_s(pozitie, t, 10);

		switch (numarEroare)
		{
		case 0: strcpy_s(eroriDeAfisat[nr], "Brackets closed without being previously opened!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 1: strcpy_s(eroriDeAfisat[nr], "After the function must follow ''(''!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 2: strcpy_s(eroriDeAfisat[nr], "The operation between the two values ​​is missing!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 3: strcpy_s(eroriDeAfisat[nr], "Two operations side by side!!    POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 4: strcpy_s(eroriDeAfisat[nr], "Brackets closed when a value was expected!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 5: strcpy_s(eroriDeAfisat[nr], "Oops! You forgot to close the paranthesis!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 6: strcpy_s(eroriDeAfisat[nr], "The function must end with a value, not operand!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 7: strcpy_s(eroriDeAfisat[nr], "Open parenthesis without closing it before comparison!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 8: strcpy_s(eroriDeAfisat[nr], "Before the comparison there must be a value, not an operand!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 9: strcpy_s(eroriDeAfisat[nr], "The operand is missing before the parentheses!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 10: strcpy_s(eroriDeAfisat[nr], "Incorrect parentheses before '',''!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 11: strcpy_s(eroriDeAfisat[nr], "The function must have only one '',''!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 12: strcpy_s(eroriDeAfisat[nr], "You're not allowed to have '','' right after an operand !!  POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 13: strcpy_s(eroriDeAfisat[nr], "Incorrect use of '',''!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 14: strcpy_s(eroriDeAfisat[nr], "After the open parenthesis, no operation must follow!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 15: strcpy_s(eroriDeAfisat[nr], "Character without significance!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 16: strcpy_s(eroriDeAfisat[nr++], "Max / min function without the second argument!!!"); break;
		case 17: strcpy_s(eroriDeAfisat[nr], "After the decimal point must follow numbers!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 18: strcpy_s(eroriDeAfisat[nr], "Using parentheses without anything inside them !!  POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 19: strcpy_s(eroriDeAfisat[nr], "Exponent too big for e or starting with 0 !!  POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 20: strcpy_s(eroriDeAfisat[nr], "The period is not closed !!  POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 21: strcpy_s(eroriDeAfisat[nr], "The period must contain only digits!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 22: strcpy_s(eroriDeAfisat[nr], "You should've closed the period sooner! :(   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 23: strcpy_s(eroriDeAfisat[nr], "Empty period !!!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t); break;
		case 24: strcpy_s(eroriDeAfisat[nr], "After the decimal point it cannot follow 'e'!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 25: strcpy_s(eroriDeAfisat[nr], "Missing exponent after 'e'!!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);  break;
		case 26: strcpy_s(eroriDeAfisat[nr], "The expression can have a maximum of one comparison !!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);   break;
		case 30: strcpy_s(eroriDeAfisat[nr], "Incorrect value entered, after 0 no other digit can follow!   POSITION: "); strcat_s(eroriDeAfisat[nr++], t);   break;
		default: strcpy_s(eroriDeAfisat[nr++], "WRONG EXPRESSION!!");  break;

		}
	}
}

void expresieValida(char e[300])
{
	bool op = true;
	bool var = false;
	bool virgula = false;
	bool cazNegativ = false;
	bool cazNot = false;
	bool cazNot1 = false;
	bool cazPerioada = false;
	bool afisareEroarePerioada = false;
	bool comparatie = false;
	bool cazVariabila = false;
	int nrVirgule = 0;
	int nrVariabile = 0;
	stiva paranteze;
	initializeaza(paranteze);
	stiva parantezeMaxMin;
	initializeaza(parantezeMaxMin);
	stiva parantezeNegativ;
	initializeaza(parantezeNegativ);
	stiva parantezeNot;
	initializeaza(parantezeNot);
	int i;
	d = 1;
	for (int k = 0; k <= MAX; k++)
	{
		for (int l = 0; l <= 10; l++)
		{
			F.vect[k][l] = null;
		}
	}
	F.vect[0][0] = '(';
	F.vect[d++][0] = '(';
	for (i = 0; i < strlen(e); i++)
	{
		//daca functia incepe cu un operator unar
		if (i == 0 && (e[i] == '-' || e[i] == '+' || e[i] == '~'))
		{
			op = true; var = false;
			if (e[i] == '~' && e[i + 1] == '(')
				F.vect[d++][0] = '~';
			if (e[i] == '~' && e[i + 1] != '(')
			{
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				if (e[i + 1] >= '0' && e[i + 1] <= '9')
					cazNot1 = true;
				else
				{
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
			}
			if (e[i] == '-' && e[i + 1] == '(')
				F.vect[d++][0] = 'N';
			if (e[i] == '-' && e[i + 1] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i] == '-' && e[i + 1] == '~')
			{
				if (e[i + 1] == '~' && e[i + 2] == '(')
					F.vect[d++][0] = '~';
				if (e[i + 1] == '~' && e[i + 2] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					if (e[i + 2] >= '1' && e[i + 2] <= '9')
						cazNot1 = true;
					else
						cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i++;
			}
		}
		// paranteze deschise
		else if (e[i] == '(' || e[i] == '[' || e[i] == '{')
		{
			if (var == true)
			{
				erori[0][numarErori] = 9;
				erori[1][numarErori++] = i;
			}
			push(paranteze, e[i], i);
			F.vect[d++][0] = e[i];
			if (e[i + 1] == '-' || e[i + 1] == '+' || e[i + 1] == '~')
			{
				if (e[i + 1] == '~' && (e[i + 2] == '(' || e[i + 2] == '[' || e[i + 2] == '{'))
					F.vect[d++][0] = '~';
				else if (e[i + 1] == '~')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				if (e[i + 1] == '-' && (e[i + 2] == '(' || e[i + 2] == '[' || e[i + 2] == '{'))
					F.vect[d++][0] = 'N';
				else if (e[i + 1] == '-')
				{
					F.vect[d++][0] = 'N';
					F.vect[d++][0] = '(';
					cazNegativ = true;
					push2(parantezeNegativ, paranteze.nrElemente);
				}
				i++;
			}
			if (strchr("*/^%&|$", e[i + 1]))
			{
				erori[0][numarErori] = 14;
				erori[1][numarErori++] = i;
			}
			if (e[i + 1] == ')' || e[i + 1] == ']' || e[i + 1] == '}')
			{
				erori[0][numarErori] = 18;
				erori[1][numarErori++] = i;
			}
		}
		//paranteze inchise
		else if (e[i] == ')')
		{
			if (op == true)
			{
				erori[0][numarErori] = 4;
				erori[1][numarErori++] = i;
			}
			if (cazPerioada)
			{
				erori[0][numarErori] = 22;
				erori[1][numarErori++] = i;
				cazPerioada = false;
				continue;
			}
			if (i == strlen(e) - 1)
			{
				op = false;
			}
			if (cazNegativ && paranteze.nrElemente == parantezeNegativ.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNegativ);
				if (esteVida(parantezeNegativ))
					cazNegativ = false;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (top(paranteze) == '(')
			{
				pop(paranteze);
				F.vect[d++][0] = e[i];
			}
			else
			{
				erori[0][numarErori] = 0;
				erori[1][numarErori++] = i;
			}
		}
		else if (e[i] == ']')
		{
			if (op == true)
			{
				erori[0][numarErori] = 4;
				erori[1][numarErori++] = i;
			}
			if (top(paranteze) == '[')
			{
				pop(paranteze);
				F.vect[d++][0] = e[i];
			}
			else
			{
				erori[0][numarErori] = 0;
				erori[1][numarErori++] = i;
			}
			if (i == strlen(e) - 1)
			{
				op = false;
			}
		}
		else if (e[i] == '}')
		{
			if (op == true)
			{
				erori[0][numarErori] = 4;
				erori[1][numarErori++] = i;
			}
			if (top(paranteze) == '{')
			{
				pop(paranteze);
				F.vect[d++][0] = e[i];
			}
			else
			{
				erori[0][numarErori] = 0;
				erori[1][numarErori++] = i;
			}
			if (i == strlen(e) - 1)
			{
				op = false;
			}
		}
		// numar
		else if (e[i] >= '1' && e[i] <= '9')
		{
			char numar[20] = "";
			int j = 0;
			numar[j++] = e[i];

			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = true; op = false;
			i++;
			while (e[i] >= '0' && e[i] <= '9')
			{
				numar[j++] = e[i];
				i++;
			}
			if (e[i] == '.')
			{
				numar[j++] = e[i];
				i++;
				if (e[i] >= '0' && e[i] <= '9')
				{
					numar[j++] = e[i];
					i++;
					while (e[i] >= '0' && e[i] <= '9')
					{
						numar[j++] = e[i];
						i++;
					}
					i--; //cout << e[i];
				}
				// numere de forma 12.3e2
				if (e[i] == 'e' && e[i - 1] == '.')
				{
					erori[0][numarErori] = 24;
					erori[1][numarErori++] = i;
					goto _nrCuE;
				}
				if (e[i + 1] == 'e')
				{
				_nrCuE:
					i++;
					bool eMinus = false;
					strcpy_s(F.vect[d++], numar);
					if (e[i + 1] == '-')
					{
						eMinus = true; i++;
					}
					if ((e[i + 1] >= '1' && e[i + 1] <= '6') && !(e[i + 2] >= '1' && e[i + 2] <= '9'))
					{
						if (!eMinus)
							F.vect[d++][0] = '*';
						else
							F.vect[d++][0] = '/';
						strcpy_s(F.vect[d++], "10");
						F.vect[d++][0] = '^';
						F.vect[d++][0] = e[i + 1];
						i++; continue;
					}
					if (!(e[i + 1] >= '0' && e[i + 2] <= '9'))
					{
						erori[0][numarErori] = 25;
						erori[1][numarErori++] = i;
					}
					else
					{
						erori[0][numarErori] = 19;
						erori[1][numarErori++] = i;
						while (e[i + 1] >= '0' && e[i + 1] <= '9')
						{
							i++;
						}


					}
				}
				// perioada
				if (e[i] == '(' && e[i - 1] == '.')
				{
					i++;
					goto _perioada;
				}
				if (e[i + 1] == '(')
				{
					i += 2;
				_perioada:
					if (e[i] == ')')
					{
						erori[0][numarErori] = 23;
						erori[1][numarErori++] = i;
						continue;
					}
					cazPerioada = true;
					char perioada[10] = "";
					int k = 0;
					while ((e[i] >= '0' && e[i] <= '9'))
					{
						perioada[k++] = e[i];
						i++;
					}
					k = 0;
					if (e[i] == ')')
					{
						while (strlen(numar) <= 8)
						{
							if (k == strlen(perioada))
								k = 0;
							numar[j++] = perioada[k++];


						}
						cazPerioada = false;
					}
					else
					{
						int z = i;
						if (strchr("-+*/^%&|$", e[i]))
						{
							erori[0][numarErori] = 20;
							erori[1][numarErori++] = i;
							i--; cazPerioada = false; continue;
						}
						if (e[z + 1] >= '0' && e[z + 1] <= '9')
							while ((e[z + 1] >= '0' && e[z + 1] <= '9') || e[z + 1] == '.')
							{
								z++;
							}
						if (e[z + 1] == ')')
						{
							erori[0][numarErori] = 21;
							erori[1][numarErori++] = i;
							i = ++z; cazPerioada = false;
						}
						else
						{
							erori[0][numarErori] = 21;
							erori[1][numarErori++] = i;
							i = z;
						}
					}

				}
				if (e[i - 1] == '.' && !(e[i] >= '0' && e[i] <= '9'))
				{
					erori[0][numarErori] = 17;
					erori[1][numarErori++] = i;
					i--;
				}

			}
			else
			{
				i--;
				strcpy_s(F.vect[d++], numar); continue;
			}
			strcpy_s(F.vect[d++], numar);
		}
		// 0 sau numar subunitar
		else if (e[i] == '0')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			char numar[20] = "";
			int j = 0;
			numar[j++] = e[i];
			var = true; op = false;
			i++;
			if (e[i] >= '0' && e[i] <= '9')
			{
				erori[0][numarErori] = 30;
				erori[1][numarErori++] = i;
				goto _eroare0;
			}
			if (e[i] == '.')
			{
				numar[j++] = e[i];
				i++;
			_eroare0:
				if (e[i] >= '0' && e[i] <= '9')
				{
					numar[j++] = e[i];
					i++;
					while (e[i] >= '0' && e[i] <= '9')
					{
						numar[j++] = e[i];
						i++;
					}
					i--;
				}
				// numere de forma 12.3e2
				if (e[i] == 'e' && e[i - 1] == '.')
				{
					erori[0][numarErori] = 24;
					erori[1][numarErori++] = i;
					goto _nrCuE0;
				}
				if (e[i + 1] == 'e')
				{
				_nrCuE0:
					i++;
					bool eMinus = false;
					strcpy_s(F.vect[d++], numar);
					if (e[i + 1] == '-')
					{
						eMinus = true; i++;
					}
					if ((e[i + 1] >= '1' && e[i + 1] <= '6') && !(e[i + 2] >= '1' && e[i + 2] <= '9'))
					{
						if (!eMinus)
							F.vect[d++][0] = '*';
						else
							F.vect[d++][0] = '/';
						strcpy_s(F.vect[d++], "10");
						F.vect[d++][0] = '^';
						F.vect[d++][0] = e[i + 1];
						i++; continue;
					}
					if (!(e[i + 1] >= '0' && e[i + 2] <= '9'))
					{
						erori[0][numarErori] = 25;
						erori[1][numarErori++] = i;
					}
					else
					{
						erori[0][numarErori] = 19;
						erori[1][numarErori++] = i;
						while (e[i + 1] >= '0' && e[i + 1] <= '9')
						{
							i++;
						}


					}
				}
				// perioada
				if (e[i] == '(' && e[i - 1] == '.')
				{
					i++;
					goto _perioada0;
				}
				if (e[i + 1] == '(')
				{
					i += 2;
				_perioada0:
					if (e[i] == ')')
					{
						erori[0][numarErori] = 23;
						erori[1][numarErori++] = i;
						continue;
					}
					cazPerioada = true;
					char perioada[10] = "";
					int k = 0;
					while ((e[i] >= '0' && e[i] <= '9'))
					{
						perioada[k++] = e[i];
						i++;
					}
					k = 0;
					if (e[i] == ')')
					{
						while (strlen(numar) <= 8)
						{
							if (k == strlen(perioada))
								k = 0;
							numar[j++] = perioada[k++];


						}
						cazPerioada = false;
					}
					else
					{
						int z = i;
						if (strchr("-+*/^%&|$", e[i]))
						{
							erori[0][numarErori] = 20;
							erori[1][numarErori++] = i;
							i--; cazPerioada = false; continue;
						}
						if (e[z + 1] >= '0' && e[z + 1] <= '9')
							while ((e[z + 1] >= '0' && e[z + 1] <= '9') || e[z + 1] == '.')
							{
								z++;
							}
						if (e[z + 1] == ')')
						{
							erori[0][numarErori] = 21;
							erori[1][numarErori++] = i;
							i = ++z; cazPerioada = false;
						}
						else
						{
							erori[0][numarErori] = 21;
							erori[1][numarErori++] = i;
							i = z;
						}
					}

				}
				if (e[i - 1] == '.' && !(e[i] >= '0' && e[i] <= '9'))
				{
					erori[0][numarErori] = 17;
					erori[1][numarErori++] = i;
					i--;
				}

			}
			else
			{
				i--;
				strcpy_s(F.vect[d++], numar); continue;
			}
			strcpy_s(F.vect[d++], numar);
		}
		// operator
		else if (strchr("-+*/^%&|$", e[i]))
		{
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (cazNegativ && paranteze.nrElemente == parantezeNegativ.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNegativ);
				if (esteVida(parantezeNegativ))
					cazNegativ = false;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			F.vect[d++][0] = e[i];
			if (e[i + 1] == '~')
			{
				if (e[i + 1] == '~' && e[i + 2] == '(')
					F.vect[d++][0] = '~';
				if (e[i + 1] == '~' && e[i + 2] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i++;
			}
			if (cazPerioada)
			{
				erori[0][numarErori] = 20;
				erori[1][numarErori++] = i;
				afisareEroarePerioada = true;
			}
		}
		// constanta e
		else if (e[i] == 'e' && !((e[i + 1] >= 'a' && e[i + 1] <= 'z') || (e[i + 1] >= 'A' && e[i + 1] <= 'Z') || (e[i + 1] >= '0' && e[i + 1] <= '9')))
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = true; op = false;
			strcpy_s(F.vect[d++], "e");
		}
		// pi
		else if (e[i] == 'p' && e[i + 1] == 'i')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = true; op = false;
			strcpy_s(F.vect[d++], "q");
			i++;
		}
		// functia sinus
		else if (e[i] == 's' && e[i + 1] == 'i' && e[i + 2] == 'n')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "s");
			i += 2;
		}
		// functia cosinus
		else if (e[i] == 'c' && e[i + 1] == 'o' && e[i + 2] == 's')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "c");
			i += 2;
		}
		// functia tangenta
		else if (e[i] == 't' && e[i + 1] == 'a' && e[i + 2] == 'n')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "t");
			i += 2;
		}
		// functia logaritm natural
		else if (e[i] == 'l' && e[i + 1] == 'n')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 2] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "l");
			i++;
		}
		// functia logaritm in baza 2
		else if (e[i] == 'l' && e[i + 1] == 'o' && e[i + 2] == 'g')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "L");
			i += 2;
		}
		// functia absolut
		else if (e[i] == 'a' && e[i + 1] == 'b' && e[i + 2] == 's')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "a");
			i += 2;
		}
		// functia radical
		else if (e[i] == 's' && e[i + 1] == 'q' && e[i + 2] == 'r' && e[i + 3] == 't')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 4] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "r");
			i += 3;
		}
		// functia ceil
		else if (e[i] == 'c' && e[i + 1] == 'e' && e[i + 2] == 'i' && e[i + 3] == 'l')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 4] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "C");
			i += 3;
		}
		// functia floor
		else if (e[i] == 'f' && e[i + 1] == 'l' && e[i + 2] == 'o' && e[i + 3] == 'o' && e[i + 4] == 'r')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 5] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "f");
			i += 4;
		}
		// functia round
		else if (e[i] == 'r' && e[i + 1] == 'o' && e[i + 2] == 'u' && e[i + 3] == 'n' && e[i + 4] == 'd')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 5] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "R");
			i += 4;
		}
		// functia trunc
		else if (e[i] == 't' && e[i + 1] == 'r' && e[i + 2] == 'u' && e[i + 3] == 'n' && e[i + 4] == 'c')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 5] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "T");
			i += 4;
		}
		// functia maxim
		else if (e[i] == 'm' && e[i + 1] == 'a' && e[i + 2] == 'x')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "M");
			strcpy_s(F.vect[d++], "(");
			push2(parantezeMaxMin, paranteze.nrElemente);
			i += 2;
			virgula = true;
			nrVirgule++;
		}
		// functia minim
		else if (e[i] == 'm' && e[i + 1] == 'i' && e[i + 2] == 'n')
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = false;
			if (e[i + 3] != '(')
			{
				erori[0][numarErori] = 1;
				erori[1][numarErori++] = i;
			}
			strcpy_s(F.vect[d++], "m");
			strcpy_s(F.vect[d++], "(");
			push2(parantezeMaxMin, paranteze.nrElemente);
			i += 2;
			virgula = true;
			nrVirgule++;
		}
		// "," in interiorul functiilor max/min
		else if (e[i] == ',' && nrVirgule)
		{
			if (op == true)
			{
				erori[0][numarErori] = 12;
				erori[1][numarErori++] = i;
			}
			if (nrVirgule != 0)
				virgula = true;
			if (nrVirgule == 0 && !esteVida(parantezeMaxMin))
			{
				erori[0][numarErori] = 13;
				erori[1][numarErori++] = i;
			}
			nrVirgule--;
			if (virgula == false)
			{
				erori[0][numarErori] = 11;
				erori[1][numarErori++] = i;
			}
			else
			{
				op = true; var = false;
				if (topS2(parantezeMaxMin) != (paranteze.nrElemente - 1))
				{
					erori[0][numarErori] = 10;
					erori[1][numarErori++] = i;
				}
				pop(parantezeMaxMin);
				strcpy_s(F.vect[d++], ")");
				F.vect[d++][0] = ',';
				virgula = false;
			}
			if (e[i + 1] == '-' || e[i + 1] == '+' || e[i + 1] == '~')
			{
				if (e[i + 1] == '~' && e[i + 2] == '(')
					F.vect[d++][0] = '~';
				if (e[i + 1] == '~' && e[i + 2] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				if (e[i + 1] == '-' && e[i + 2] == '(')
					F.vect[d++][0] = 'N';
				if (e[i + 1] == '-' && e[i + 2] != '(')
				{
					F.vect[d++][0] = 'N';
					F.vect[d++][0] = '(';
					cazNegativ = true;
					push2(parantezeNegativ, paranteze.nrElemente);
				}
				i++;
			}//-max(4-sin(5),-cos(8-ceil(8.7)))+(-pi)
		}
		// "," in afara functiilor max/min
		else if (e[i] == ',')
		{
			op = true; var = false;
			if (nrVirgule == 0)
			{
				erori[0][numarErori] = 13;
				erori[1][numarErori++] = i;
			}
		}
		// operatorul mai mic
		else if (e[i] == '<' && !(e[i + 1] == '='))
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			F.vect[d++][0] = '<';
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// operatorul mai mare
		else if (e[i] == '>' && !(e[i + 1] == '='))
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			F.vect[d++][0] = '>';
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// operatorul egal
		else if (e[i] == '=')
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			F.vect[d++][0] = '=';
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// operatorul diferit
		else if (e[i] == '#')
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			F.vect[d++][0] = '#';
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// operatorul mai mic egal
		else if (e[i] == '<' && e[i + 1] == '=')
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			strcpy_s(F.vect[d++], "k");
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			i++;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// operatorul mai mare egal
		else if (e[i] == '>' && e[i + 1] == '=')
		{
			if (comparatie)
			{
				erori[0][numarErori] = 26;
				erori[1][numarErori++] = i;
			}
			if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
			{
				F.vect[d++][0] = ')';
				pop(parantezeNot);
				if (esteVida(parantezeNot))
					cazNot = false;
			}
			if (cazNot1)
			{
				F.vect[d++][0] = ')';
				cazNot1 = false;
			}
			strcpy_s(F.vect[d++], ")");
			strcpy_s(F.vect[d++], "K");
			strcpy_s(F.vect[d++], "(");
			comparatie = true;
			i++;
			if (!esteVida(paranteze))
			{
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 7;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
			}
			if (op == true)
			{
				erori[0][numarErori] = 8;
				erori[1][numarErori++] = i;
			}
			if (!var)
			{
				erori[0][numarErori] = 3;
				erori[1][numarErori++] = i;
			}
			op = true; var = false;
			if (e[i + 1] == '~' && e[i + 2] == '(')
			{
				F.vect[d++][0] = '~';
				i++;
				continue;
			}
			if (e[i + 1] == '~' && e[i + 2] != '(')
			{
				i++;
				F.vect[d++][0] = '~';
				F.vect[d++][0] = '(';
				cazNot = true;
				push2(parantezeNot, paranteze.nrElemente);
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] == '(')
			{
				F.vect[d++][0] = 'N';
				i++;
				continue;
			}
			if (e[i + 1] == '-' && e[i + 2] != '(')
			{
				F.vect[d++][0] = 'N';
				F.vect[d++][0] = '(';
				cazNegativ = true;
				push2(parantezeNegativ, paranteze.nrElemente);
			}
			if (e[i + 1] == '-' && e[i + 2] == '~')
			{
				if (e[i + 2] == '~' && e[i + 3] == '(')
				{
					F.vect[d++][0] = '~';
					i += 2;
					continue;
				}
				if (e[i + 2] == '~' && e[i + 3] != '(')
				{
					F.vect[d++][0] = '~';
					F.vect[d++][0] = '(';
					cazNot = true;
					push2(parantezeNot, paranteze.nrElemente);
				}
				i += 2;
			}
		}
		// variabila
		else if ((e[i] >= 'a' && e[i] <= 'z') || (e[i] >= 'A' && e[i] <= 'A'))
		{
			if (var == true)
			{
				erori[0][numarErori] = 2;
				erori[1][numarErori++] = i;
			}
			var = false; op = true;
			cazVariabila = true;
			int poz = i, inceput = i - 1;
			char var[20] = "";
			int j = 0;
			var[j] = e[poz]; j++; poz++;
			while ((e[poz] >= 'a' && e[poz] <= 'z') || (e[poz] >= 'A' && e[poz] <= 'Z') || (e[poz] >= '0' && e[poz] <= '9'))
			{
				var[j] = e[poz];
				poz++; j++;
			}
			//cout << "Care este valoarea variabilei " << var << "?" << endl;
			char var2[40] = "";
			if (cazVariabila)
			{
				for (int q = 0; q < nrVariabile; q++)
				{
					if (strcmp(variabile[q], var) == 0)
					{
						strcpy_s(var2, valoriVariabile[q]);
						goto _schimbare;
					}
				}
			}
			strcpy_s(numeVariabila, 20, var);
			CitesteVariabilaDeLaTastatura(var2);
			strcpy_s(variabile[nrVariabile], var);
			strcpy_s(valoriVariabile[nrVariabile++], var2);
			//cin.get(var2, 40); cin.get();
		_schimbare:
			int y = strlen(var2);
			var2[y + 1] = ')';
			var2[y + 2] = null;
			for (int k = strlen(var2); k > 0; k--)
			{
				var2[k] = var2[k - 1];
			}
			var2[0] = '(';
			int dim1, dim2, z = 0;
			dim1 = strlen(var); dim2 = strlen(var2);
			if (dim1 == dim2)
			{
				while (dim1 != 0)
				{
					e[i++] = var2[z++];
					dim1--;
				}
			}
			else  if (dim1 > dim2)
			{
				int mut = i;
				int l = dim1 - dim2;
				while (dim2 != 0)
				{
					e[i++] = var2[z++];
					dim2--;
				}
				while (e[i] != NULL)
				{
					e[i] = e[i + l];
					i++;
				}
			}
			else if (dim1 < dim2)
			{
				int l = dim2 - dim1;
				for (int j = strlen(e) + l; j > poz; j--)
				{
					e[j] = e[j - l];
				}
				while (dim2 != 0)
				{
					e[i++] = var2[z++];
					dim2--;
				}

			}
			i = inceput;
		}
		// spatiu
		else if (e[i] == ' ')
			continue;
		// caracter fara semnificatie
		else
		{
			erori[0][numarErori] = 15;
			erori[1][numarErori++] = i;
		}
	}
	if (cazNegativ && paranteze.nrElemente == parantezeNegativ.varf->nr)
	{
		F.vect[d++][0] = ')';
		pop(parantezeNegativ);
		if (esteVida(parantezeNegativ))
			cazNegativ = false;
	}
	if (cazNot && paranteze.nrElemente == parantezeNot.varf->nr)
	{
		F.vect[d++][0] = ')';
		pop(parantezeNot);
		if (esteVida(parantezeNot))
			cazNegativ = false;
	}
	if (cazNot1)
	{
		F.vect[d++][0] = ')';
		cazNot1 = false;
	}
	if (cazPerioada && !afisareEroarePerioada)
	{
		erori[0][numarErori] = 20;
		erori[1][numarErori++] = i;
	}
	F.vect[d++][0] = ')';
	F.vect[d][0] = ')';
	if (numarErori == 0 && esteVida(paranteze) && !op && !nrVirgule)
	{
		ExpresieCorecta = true;
	}
	else
	{
		if (nrVirgule != 0)
		{
			erori[0][numarErori] = 16;
			erori[1][numarErori++] = i;
		}
		if (op)
		{
			erori[0][numarErori] = 6;
			erori[1][numarErori++] = i - 1;
		}
		if (!esteVida(paranteze))
		{
			if (paranteze.nrElemente == 1)
			{
				erori[0][numarErori] = 5;
				erori[1][numarErori++] = paranteze.varf->nr;
			}
			else
				while (paranteze.nrElemente)
				{
					erori[0][numarErori] = 5;
					erori[1][numarErori++] = paranteze.varf->nr;
					pop(paranteze);
				}
		}
	}
}
 // SABIN

int Prioritate(char c)  // prioritate operatorilor
{
	if (c == '(' || c == ')')
		return 0;
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '^')
		return 3;
	if (c == '=' || c == '#' || c == '<' || c == '>' || c == '&' || c == '|' || c == '$' || c == 'k' || c == 'K')
		return 4;
	if (c == 'c' || c == 's' || c == 'l' || c == 'e' || c == 't' || c == 'a' || c == 'r' || c == 't' || c == 'f' || c == 'C' || c == 'm' || c == 'M' || 'L' || '~')
		return 5;
	return 100;

}

const float pi = 3.141;

int DifInf(float x)
{
	return fabs(infinit - fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
	if (x > epsi && DifInf(x))
		return log(x);
	else
		return infinit;
}

float Logaritm2(float x)
{
	if (x > epsi && DifInf(x))
		return log2(x);
	else
		return infinit;
}

float Inmultit(float x, float y)
{
	if (fabs(x) < epsi || fabs(y) < epsi) return 0;
	else if (DifInf(x) && DifInf(y)) return x * y;
	else return infinit;
}

float Putere(float x, float y)
{
	// float p;
	if (x == 0) return 0;
	else if (y == 0) return 1;
	else if (x == infinit || y == infinit) return infinit;
	else
		return pow(x, y);
}

float Egal(float x, float y)
{
	return x == y;
}

float Minim(float x, float y)
{
	if (x < y) {

		return x;
	}
	else {

		return y;

	}

}

float Maxim(float x, float y)
{
	if (x > y) {

		return x;
	}
	else {

		return y;

	}

}

float Diferit(float x, float y)
{
	return x != y;
}

float MaiMic(float x, float y)
{
	return x < y;
}

float MaiMicSauEgal(float x, float y)
{
	return x <= y;
}

int MaiMare(float x, float y)
{
	return x > y;
}

int MaiMareSauEgal(float x, float y)
{
	return x >= y;
}

float Plus(float x, float y)
{
	if (DifInf(x) && DifInf(y))  return x + y;
	else return infinit;
}

float Minus(float x, float y)
{
	if (DifInf(x) && DifInf(y))  return x - y;
	else return infinit;
}

float SI(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x & y);
	else return infinit;
}

float SAU(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x | y);
	else return infinit;
}

float XOR(int x, int y)
{
	if (DifInf(x) && DifInf(y))  return (x ^ y);
	else return infinit;
}

float Impartit(float x, float y)
{
	if (fabs(y) > epsi) return x / y;
	else
		return  infinit;


}

float Sinus(float x)
{
	if (DifInf(x))  return sin(x);
	else return infinit;
}

float Neg(int x)
{
	if (DifInf(x))  return ~x;
	else return infinit;
}

float Negativ(float x)
{
	if (DifInf(x))  return (-1) * (x);
	else return infinit;
}

float Tangenta(float x)
{
	if (DifInf(x))  return tan(x);
	else return infinit;
}

float Cosinus(float x)
{
	if (DifInf(x))  return cos(x);
	else return infinit;
}

float Modul(float x)
{
	if (DifInf(x)) return fabs(x);
	else return infinit;
}

float Radical(float x)
{
	if (DifInf(x) && (x > epsi)) return sqrt(x);
	else return infinit;
}

int EsteNumar(char sir[MAX1])
{
	if (sir[0] == '0') return 1;
	return (atof(sir) != 0.0 &&
		strchr("0123456789", sir[0]));
}

void depanare()
{
	cout << "Stiva operanzilor: " << endl;
	for (int i = 1; i <= top1; i++) {
		cout << Opd[i] << " ";
	}
	cout << endl;
	cout << "Stiva operatorilor: " << endl;
	for (int i = 1; i <= top2; i++) {
		cout << Op[i] << " ";
	}
	cout << endl;
}

double ValoareFunctie(functie E)
{
	NuSePoateCalcula = false;
	int i;
	// returneaza valoarea functiei E in punctul x
	double valo, x_1 = 0, x_2 = 0;
	//calculul expresiei
	for (i = 1; i <= 100; i++)
	{
		Opd[i] = 0;
		Op[i] = '@';
	}
	top1 = 0;
	top2 = 1;
	Op[top2] = '(';
	i = 0;
	while (i <= E.lung && top2 > 0)
	{
		i++;
		if (EsteNumar(E.vect[i]))
		{
			top1++;
			valo = atof(E.vect[i]);
			Opd[top1] = valo;
		}
		else
			switch (E.vect[i][0]) {
				/* constanta pi=3.1415926 se da sub forma literei q */
			case 'q': top1++; Opd[top1] = pi; break;
			case 'e': top1++; Opd[top1] = 2.71; break;
			case '(': /* inceput de bloc */ top2++; Op[top2] = '('; break;
			default:
				/* operatii binare si unare */
				while ((top2 > 0) && !(strchr("()", Op[top2])) && Prioritate(Op[top2]) >= Prioritate(E.vect[i][0]))
				{
					if (top1 > 1) x_1 = Opd[top1 - 1];
					x_2 = Opd[top1];
					// depanare();
					/* functii scrise in OPERATII */
					switch (Op[top2]) {
					case '=': valo = Egal(x_1, x_2); break;
					case '#': valo = Diferit(x_1, x_2); break;
					case '<': valo = MaiMic(x_1, x_2); break;
					case 'k': valo = MaiMicSauEgal(x_1, x_2); break;
					case 'K': valo = MaiMareSauEgal(x_1, x_2); break;
					case '>': valo = MaiMare(x_1, x_2); break;
					case '+': valo = Plus(x_1, x_2); break;
					case '-': valo = Minus(x_1, x_2); break;
					case '*': valo = Inmultit(x_1, x_2); break;
					case '/': valo = Impartit(x_1, x_2); break;
					case '^': valo = Putere(x_1, x_2); break;
					case 'm': valo = Minim(x_1, x_2); break;
					case 'M': valo = Maxim(x_1, x_2); break;
					case '&': valo = SI(x_1, x_2); break;
					case '|': valo = SAU(x_1, x_2); break;
					case '$': valo = XOR(x_1, x_2); break;
					case '~': valo = Neg(x_2); break;
					case 's': valo = Sinus(x_2); break;
					case 'c': valo = Cosinus(x_2); break;
					case 'l': valo = Logaritm(x_2); break;
					case 'L': valo = Logaritm2(x_2); break;
					case 'a': valo = Modul(x_2); break;
					case 'N': valo = Negativ(x_2); break;
					case 'C': valo = ceil(x_2); break;
					case 'T': valo = trunc(x_2); break;
					case 'R': valo = round(x_2); break;
					case 'f': valo = floor(x_2); break;
					case 'r': valo = Radical(x_2); break;
					case 't': valo = Tangenta(x_2); break;
					}
					if (strchr(OperatiiBinare, Op[top2])) top1--;
					if (strchr(Operatii, Op[top2])) Opd[top1] = valo;
					top2--;
				}
				//    depanare();
				if (top2 > 0)
					if ((Op[top2] != '(') || (strcmp(E.vect[i], ")")))
					{
						top2++; Op[top2] = E.vect[i][0];
					}
					else top2--;
			}
	}
	if (top2 == 0) {
		if (Opd[1] < infinit) {
			return Opd[1];
		}
		else {
			NuSePoateCalcula = true;
			//cout << "EXPRESIE INCORECTA,NU SE POATE CALCULA REZULTATUL ";
			return 0;
		}
	}


}

// Tudor

sf::RenderWindow window(sf::VideoMode(latime + 100, inaltime), "Evaluator!");
sf::Font font;

struct nodT
{
	char info[10];
	int x, y, r, forma, culoare, dimensiuneText;
	nodT* stanga, * dreapta;
};

struct nodLista
{
	nodT* nodCurent;
	nodLista* nodUrmatorLista;
};

struct lista
{
	nodLista* nodPrim;
	nodLista* nodUltim;
};

typedef nodT* arbore;

arbore arboreCurent;
bool clicked;
int page = 1;
int contorGlobal;

bool EsteNULL(arbore a)
{
	return (a == NULL);
}

void InitArbore(arbore& a)
{
	if (!EsteNULL(a))
	{
		a = NULL;
	}
}

int gasesteParantezaInchisa(functie E, int i)
{
	int cnt = 1;
	while (cnt != 0)
	{
		i++;
		if (E.vect[i][0] == ')')
		{
			cnt--;
		}
		else
		{
			if (E.vect[i][0] == '(')
			{
				cnt++;
			}
		}
	}
	return i;
}

string decodare(char e)
{
	switch (e)
	{
	case 's': return "sin"; break;
	case 'c': return "cos"; break;
	case 't': return "tan"; break;
	case 'l': return "ln"; break;
	case 'L': return "log"; break;
	case 'a': return "abs"; break;
	case 'T': return "trunc"; break;
	case 'r': return "sqrt"; break;
	case 'C': return "ceil"; break;
	case 'R': return "round"; break;
	case 'f': return "floor"; break;
	case 'm': return "max"; break;
	case 'M': return "min"; break;
	case 'N': return "neg"; break;
	case 'k': return "<="; break;
	case 'K': return ">="; break;
	case 'q': return "pi"; break;
	default: return "Error"; break;
	}
}

void CitesteArbore(arbore& a, functie E, int inceput, int sfarsit)
{
	nodT* nodNou;
	char operatorMin = ' ';
	int prioritateOpMin = 100, prioritateOpCurent, pozitieOpMin = 0;
	char functieMin = ' ';
	int pozitieFunctieMin;
	bool functie = false;
	for (int i = inceput; i <= sfarsit; i++)
	{
		if (strchr("~mMsclLaNCTRfrt", E.vect[i][0]))
		{
			i++;
			i = gasesteParantezaInchisa(E, i);
			i++;
		}
		else
		{
			if (E.vect[i][0] == '(')
			{
				if (gasesteParantezaInchisa(E, i) != sfarsit || i != inceput)
				{
					i = gasesteParantezaInchisa(E, i);
					i++;
				}
			}
		}
		if (i <= sfarsit)
		{
			prioritateOpCurent = Prioritate(E.vect[i][0]);
			if (prioritateOpCurent >= 1 && prioritateOpCurent <= 4 && prioritateOpCurent <= prioritateOpMin)
			{
				operatorMin = E.vect[i][0];
				prioritateOpMin = prioritateOpCurent;
				pozitieOpMin = i;
			}
		}
	}
	if (prioritateOpMin == 100)
	{
		for (int i = inceput; i <= sfarsit; i++)
		{
			if (strchr("~sclLaNCTRfrt", E.vect[i][0]))
			{
				nodNou = new nodT;
				if (decodare(E.vect[i][0]) != "Error")
				{
					strcpy_s(nodNou->info, decodare(E.vect[i][0]).c_str());
				}
				else
				{
					strcpy_s(nodNou->info, E.vect[i]);
				}
				a = nodNou;
				a->stanga = null;
				a->dreapta = null;
				i++;
				i = gasesteParantezaInchisa(E, i);
				CitesteArbore(a->stanga, E, inceput + 2, i - 1);
				functie = true;
				break;
			}
			else
			{
				if (strchr("mM", E.vect[i][0]))
				{
					nodNou = new nodT;
					if (decodare(E.vect[i][0]) != "Error")
					{
						strcpy_s(nodNou->info, decodare(E.vect[i][0]).c_str());
					}
					else
					{
						strcpy_s(nodNou->info, E.vect[i]);
					}
					a = nodNou;
					a->stanga = null;
					a->dreapta = null;
					pozitieOpMin = gasesteParantezaInchisa(E, i + 2) + 1;
					i++;
					i = gasesteParantezaInchisa(E, i);
					CitesteArbore(a->stanga, E, inceput + 2, pozitieOpMin - 1);
					CitesteArbore(a->dreapta, E, pozitieOpMin + 1, i - 1);
					functie = true;
					break;
				}
			}
		}
		if (functie == false)
		{
			int i = inceput;
			bool numar = true;
			for (i; i <= sfarsit; i++)
			{
				if (!strchr("0123456789.()qe", E.vect[i][0]))
				{
					numar = false;
					break;
				}
			}
			if (numar)
			{
				i = inceput;
				while (E.vect[i][0] == '(' || E.vect[i][0] == ')') i++;
				nodNou = new nodT;
				if (decodare(E.vect[i][0]) != "Error")
				{
					strcpy_s(nodNou->info, decodare(E.vect[i][0]).c_str());
				}
				else
				{
					strcpy_s(nodNou->info, E.vect[i]);
				}
				a = nodNou;
				a->stanga = null;
				a->dreapta = null;
			}
			else
			{
				CitesteArbore(a, E, inceput + 1, sfarsit);
			}
		}
	}
	else
	{
		nodNou = new nodT;
		strcpy_s(nodNou->info, E.vect[pozitieOpMin]);
		a = nodNou;
		a->stanga = null;
		a->dreapta = null;
		CitesteArbore(a->stanga, E, inceput, pozitieOpMin - 1);
		CitesteArbore(a->dreapta, E, pozitieOpMin + 1, sfarsit);
	}
}

void AfiseazaArbore(arbore a)
{
	if (!EsteNULL(a))
	{
		cout << a->info << " ";
		lista* l = new lista;
		nodLista* nodNouLista;
		nodNouLista = new nodLista;
		nodNouLista->nodCurent = a->stanga;
		l->nodPrim = nodNouLista;
		nodNouLista = new nodLista;
		nodNouLista->nodCurent = a->dreapta;
		l->nodUltim = nodNouLista;
		l->nodPrim->nodUrmatorLista = l->nodUltim;
		while (l->nodPrim->nodUrmatorLista != null)
		{
			if (!EsteNULL(l->nodPrim->nodCurent))
			{
				cout << l->nodPrim->nodCurent->info << " ";
				nodNouLista = new nodLista;
				nodNouLista->nodCurent = l->nodPrim->nodCurent->stanga;
				l->nodUltim->nodUrmatorLista = nodNouLista;
				l->nodUltim = nodNouLista;
				l->nodUltim->nodUrmatorLista = null;
				nodNouLista = new nodLista;
				nodNouLista->nodCurent = l->nodPrim->nodCurent->dreapta;
				l->nodUltim->nodUrmatorLista = nodNouLista;
				l->nodUltim = nodNouLista;
				l->nodUltim->nodUrmatorLista = null;
			}
			l->nodPrim = l->nodPrim->nodUrmatorLista;
		}
	}
	cout << endl;
}

int nrColoane(arbore a)
{
	if (EsteNULL(a))
	{
		return 0;
	}
	else
	{
		if (a->stanga && a->dreapta)
		{
			return 1 + nrColoane(a->stanga) + nrColoane(a->dreapta);
		}
		else
		{
			if (a->stanga)
			{
				return nrColoane(a->stanga);
			}
			else
			{
				return 1;
			}
		}
	}
}

int nrColoaneSt(arbore a)
{
	if (EsteNULL(a))
	{
		return 0;
	}
	else
	{
		if (a->stanga && a->dreapta)
		{
			return 1 + nrColoane(a->stanga);
		}
		else
		{
			if (a->stanga)
			{
				return nrColoaneSt(a->stanga);
			}
			else
			{
				return 1;
			}
		}
	}
}

int nrNiveluri(arbore a)
{
	if (EsteNULL(a))
	{
		return 0;
	}
	else
	{
		return 1 + max(nrNiveluri(a->stanga), nrNiveluri(a->dreapta));
	}
}

void CalculeazaCoordonateleSiRazaNodului(arbore a, int nivelCurent, int numarNiveluri, int numarColoane, int adaosColoanaCurenta)
{
	int coloanaCurenta;
	if (a->dreapta && a->stanga)
	{
		coloanaCurenta = nrColoane(a->stanga) + 1 + adaosColoanaCurenta;
	}
	else
	{
		if (a->stanga)
		{
			coloanaCurenta = nrColoaneSt(a) + adaosColoanaCurenta;
		}
		else
		{
			coloanaCurenta = adaosColoanaCurenta + 1;
		}
	}
	float x, y, r;
	x = latime / numarColoane * coloanaCurenta - latime / (numarColoane * 2);
	y = inaltime / numarNiveluri * nivelCurent - inaltime / (numarNiveluri * 2);
	float minim = min(inaltime / numarNiveluri / 2, latime / numarColoane / 2) / 1.2f;
	r = minim / 2;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(r / 1.2f);
	a->dimensiuneText = r / 1.2f;
	text.setString(a->info);
	sf::FloatRect textRect = text.getLocalBounds();
	r = max(r, textRect.width);
	if (r > minim)
	{
		r = minim;
		while (textRect.width > r)
		{
			text.setCharacterSize(text.getCharacterSize() - 1);
			textRect = text.getLocalBounds();
		}
		a->dimensiuneText = text.getCharacterSize();
	}
	a->x = x, a->y = y, a->r = r, a->forma = 0, a->culoare = 0;
}

void CalculeazaCoordonateleSiRazaNodurilorDinArbore(arbore a, int nivelCurent, int numarNivele, int numarColoane, int adaosColoanaCurenta)
{
	if (!EsteNULL(a))
	{
		CalculeazaCoordonateleSiRazaNodului(a, nivelCurent, numarNivele, numarColoane, adaosColoanaCurenta);
		CalculeazaCoordonateleSiRazaNodurilorDinArbore(a->stanga, nivelCurent + 1, numarNivele, numarColoane, adaosColoanaCurenta);
		CalculeazaCoordonateleSiRazaNodurilorDinArbore(a->dreapta, nivelCurent + 1, numarNivele, numarColoane, adaosColoanaCurenta + nrColoane(a->stanga) + 1);
	}
}

int sgn(float x, float a, float b)
{
	if (x > 0)
		return 1;
	else
		if (x < 0)
			return -1;
		else
		{
			if (a > b)
				return -1;
			else
				return 1;
		}
}

int childAbove(float x, float y)
{
	if (x > y)return -1;
	else return 1;
}

void DeseneazaNod(arbore a)
{
	float x, y, r, forma, culoare, dimensiuneText;
	x = a->x;
	y = a->y;
	r = a->r;
	forma = a->forma;
	culoare = a->culoare;
	dimensiuneText = a->dimensiuneText;

	sf::CircleShape circle(r);
	sf::RectangleShape patrat(sf::Vector2f(r * 2 / sqrt(2), r * 2 / sqrt(2)));
	sf::CircleShape triunghi(r, 3);

	switch ((int)forma)
	{
	case 0:
		circle.setPosition(sf::Vector2f(x - r, y - r));
		switch ((int)culoare)
		{
		case 0:
			circle.setFillColor(sf::Color::White);
			break;
		case 1:
			circle.setFillColor(sf::Color::Blue);
			break;
		case 2:
			circle.setFillColor(sf::Color::Green);
			break;
		case 3:
			circle.setFillColor(sf::Color::Red);
			break;
		}
		window.draw(circle);
		break;
	case 1:
		patrat.setPosition(sf::Vector2f(x - r / sqrt(2), y - r / sqrt(2)));
		switch ((int)culoare)
		{
		case 0:
			patrat.setFillColor(sf::Color::White);
			break;
		case 1:
			patrat.setFillColor(sf::Color::Blue);
			break;
		case 2:
			patrat.setFillColor(sf::Color::Green);
			break;
		case 3:
			patrat.setFillColor(sf::Color::Red);
			break;
		}
		window.draw(patrat);
		break;
	case 2:
		triunghi.setPosition(sf::Vector2f(x - r, y - r));
		switch ((int)culoare)
		{
		case 0:
			triunghi.setFillColor(sf::Color::White);
			break;
		case 1:
			triunghi.setFillColor(sf::Color::Blue);
			break;
		case 2:
			triunghi.setFillColor(sf::Color::Green);
			break;
		case 3:
			triunghi.setFillColor(sf::Color::Red);
			break;
		}
		window.draw(triunghi);
		break;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(dimensiuneText);
	text.setString(a->info);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(sf::Vector2f(textRect.width / 2, textRect.height / 2));
	text.setPosition(sf::Vector2f(x, y));
	text.setFillColor(sf::Color::Black);
	window.draw(text);

	if (!EsteNULL(a->stanga))
	{
		float xs, ys, rs, formas;
		xs = a->stanga->x;
		ys = a->stanga->y;
		rs = a->stanga->r;
		formas = a->stanga->forma;
		float lineStartx, lineStarty, lineFinishx, lineFinishy, pantas;
		pantas = (ys - y) / (xs - x);
		if (xs == x)pantas = 1000;

		switch ((int)forma)
		{
		case 0:
			lineStartx = x + r / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineStarty = y + (r * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
			break;
		case 1: // patrat
			float semilaturaP;
			semilaturaP = r / sqrt(2);

			if (pantas > -1 && pantas < 1 && x < xs) //cadran 1
			{
				lineStartx = x + semilaturaP;
				lineStarty = y + pantas * semilaturaP;
			}
			else
			{
				if ((pantas < -1 || pantas > 1) && y < ys) //cadran 2
				{
					lineStartx = (x * pantas + semilaturaP) / pantas;
					lineStarty = y + semilaturaP;
				}
				else
				{
					if (pantas > -1 && pantas < 1 && x > xs) //cadran 3
					{
						lineStartx = x - semilaturaP;
						lineStarty = y - pantas * semilaturaP;
					}
					else
					{
						if ((pantas < -1 || pantas > 1) && y > ys) //cadran 4
						{
							lineStartx = (x * pantas - semilaturaP) / pantas;
							lineStarty = y - semilaturaP;
						}
						else //mediatoare
						{
							lineStartx = x + r / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineStarty = y + (r * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
						}
					}
				}
			}
			break;
		case 2: //triunghi
			float tAx, tBx, tCx, tAy, tBy, tCy;
			tAx = x, tAy = y - r;
			tBx = x - r * sqrt(3) / 2, tBy = y + r / 2;
			tCx = x + r * sqrt(3) / 2, tCy = y + r / 2;

			if (pantas > (-tan1) && pantas<tan2 && xs > tAx) //cadran 1
			{
				lineStartx = (pantas * x + tAy - tAx * sqrt(3) - y) / (pantas - sqrt(3));
				lineStarty = y + pantas * (lineStartx - x);
			}
			else
			{
				if (pantas < (-tan2) || pantas>tan2 && ys > tAy + r * 3 / 2) //cadran 2
				{
					lineStartx = (r / 2 + pantas * x) / pantas;
					lineStarty = y + r / 2;
				}
				else
				{
					if (pantas<tan1 && pantas>-tan2 && xs < tAx) //cadran 3
					{
						lineStartx = (pantas * x + tAy + tAx * sqrt(3) - y) / (pantas + sqrt(3));
						lineStarty = y + pantas * (lineStartx - x);
					}
					else //mediatoare
					{
						lineStartx = x + r / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineStarty = y + (r * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
					}
				}
			}
			break;
		default:
			lineStartx = x + r / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineStarty = y + (r * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
			break;
		}

		switch ((int)formas)
		{
		case 0:
			lineFinishx = xs - rs / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineFinishy = ys - (rs * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
			break;
		case 1: // patrat
			float semilaturaP;
			semilaturaP = rs / sqrt(2);

			if (pantas > -1 && pantas < 1 && x > xs) //cadran 1
			{
				lineFinishx = xs + semilaturaP;
				lineFinishy = ys + pantas * semilaturaP;
			}
			else
			{
				if ((pantas < -1 || pantas > 1) && y > ys) //cadran 2
				{
					lineFinishx = (xs * pantas + semilaturaP) / pantas;
					lineFinishy = ys + semilaturaP;
				}
				else
				{
					if (pantas > -1 && pantas < 1 && x < xs) //cadran 3
					{
						lineFinishx = xs - semilaturaP;
						lineFinishy = ys - pantas * semilaturaP;
					}
					else
					{
						if ((pantas < -1 || pantas > 1) && y < ys) //cadran 4
						{
							lineFinishx = (xs * pantas - semilaturaP) / pantas;
							lineFinishy = ys - semilaturaP;
						}
						else //mediatoare
						{
							lineFinishx = xs - rs / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineFinishy = ys - (rs * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
						}
					}
				}
			}
			break;
		case 2: //triunghi
			float tAx, tBx, tCx, tAy, tBy, tCy;
			tAx = xs, tAy = ys - rs;
			tBx = xs - rs * sqrt(3) / 2, tBy = ys + rs / 2;
			tCx = xs + rs * sqrt(3) / 2, tCy = ys + rs / 2;

			if (pantas > (-tan1) && pantas<tan2 && x > tAx) //cadran 1
			{
				lineFinishx = (pantas * xs + tAy - tAx * sqrt(3) - ys) / (pantas - sqrt(3));
				lineFinishy = ys + pantas * (lineFinishx - xs);
			}
			else
			{
				if (pantas < (-tan2) || pantas>tan2 && y > tAy + r * 3 / 2) //cadran 2
				{
					lineFinishx = (rs / 2 + pantas * xs) / pantas;
					lineFinishy = ys + rs / 2;
				}
				else
				{
					if (pantas<tan1 && pantas>-tan2 && x < tAx) //cadran 3
					{
						lineFinishx = (pantas * xs + tAy + tAx * sqrt(3) - ys) / (pantas + sqrt(3));
						lineFinishy = ys + pantas * (lineFinishx - xs);
					}
					else //mediatoare
					{
						lineFinishx = xs - rs / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineFinishy = ys - (rs * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
					}
				}
			}
			break;
		default:
			lineFinishx = xs - rs / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys), lineFinishy = ys - (rs * pantas) / sqrt(pantas * pantas + 1) * sgn(pantas, x, xs) * childAbove(y, ys);
			break;
		}



		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(lineStartx, lineStarty);
		lines[1].position = sf::Vector2f(lineFinishx, lineFinishy);
		window.draw(lines);

		float s = pantas, t = (s - tagBeta) / (1 + s * tagBeta);
		float xM = lineFinishx - 20 / sqrt(s * s + 1) * sgn(s, x, xs) * childAbove(y, ys), yM = lineFinishy - (20 * s) / sqrt(s * s + 1) * sgn(s, x, xs) * childAbove(y, ys);
		float xB = ((2 * xM - lineFinishx) * (1 + s * t) - (xM - lineFinishx) * (s * s + 1)) / (1 + s * t);
		float yB = ((xM - lineFinishx) * (s * s * t + 2 * s - t) + lineFinishy * (1 + s * t)) / (1 + s * t);
		float xC = (lineFinishx * (1 + s * t) + (xM - lineFinishx) * (s * s + 1)) / (1 + s * t);
		float yC = (t * (xM - lineFinishx) * (s * s + 1) + lineFinishy * (1 + s * t)) / (1 + s * t);

		sf::VertexArray lines1(sf::LinesStrip, 2);
		lines1[0].position = sf::Vector2f(lineFinishx, lineFinishy);
		lines1[1].position = sf::Vector2f(xB, yB);
		window.draw(lines1);

		sf::VertexArray lines2(sf::LinesStrip, 2);
		lines2[0].position = sf::Vector2f(lineFinishx, lineFinishy);
		lines2[1].position = sf::Vector2f(xC, yC);
		window.draw(lines2);
	}

	if (!EsteNULL(a->dreapta))
	{
		float xd, yd, rd, formad;
		xd = a->dreapta->x;
		yd = a->dreapta->y;
		rd = a->dreapta->r;
		formad = a->dreapta->forma;
		float lineStartx, lineStarty, lineFinishx, lineFinishy, pantad;
		pantad = (yd - y) / (xd - x);
		if (xd == x)pantad = 1000;

		switch ((int)forma)
		{
		case 0:
			lineStartx = x + r / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineStarty = y + (r * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
			break;
		case 1: // patrat
			float semilaturaP;
			semilaturaP = r / sqrt(2);

			if (pantad > -1 && pantad < 1 && x < xd) //cadran 1
			{
				lineStartx = x + semilaturaP;
				lineStarty = y + pantad * semilaturaP;
			}
			else
			{
				if ((pantad < -1 || pantad > 1) && y < yd) //cadran 2
				{
					lineStartx = (x * pantad + semilaturaP) / pantad;
					lineStarty = y + semilaturaP;
				}
				else
				{
					if (pantad > -1 && pantad < 1 && x > xd) //cadran 3
					{
						lineStartx = x - semilaturaP;
						lineStarty = y - pantad * semilaturaP;
					}
					else
					{
						if ((pantad < -1 || pantad > 1) && y > yd) //cadran 4
						{
							lineStartx = (x * pantad - semilaturaP) / pantad;
							lineStarty = y - semilaturaP;
						}
						else //mediatoare
						{
							lineStartx = x + r / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineStarty = y + (r * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
						}
					}
				}
			}
			break;
		case 2: //triunghi
			float tAx, tBx, tCx, tAy, tBy, tCy;
			tAx = x, tAy = y - r;
			tBx = x - r * sqrt(3) / 2, tBy = y + r / 2;
			tCx = x + r * sqrt(3) / 2, tCy = y + r / 2;

			if (pantad > (-tan1) && pantad<tan2 && xd > tAx) //cadran 1
			{
				lineStartx = (pantad * x + tAy - tAx * sqrt(3) - y) / (pantad - sqrt(3));
				lineStarty = y + pantad * (lineStartx - x);
			}
			else
			{
				if (pantad < (-tan2) || pantad>tan2 && yd > tAy + r * 3 / 2) //cadran 2
				{
					lineStartx = (r / 2 + pantad * x) / pantad;
					lineStarty = y + r / 2;
				}
				else
				{
					if (pantad<tan1 && pantad>-tan2 && xd < tAx) //cadran 3
					{
						lineStartx = (pantad * x + tAy + tAx * sqrt(3) - y) / (pantad + sqrt(3));
						lineStarty = y + pantad * (lineStartx - x);
					}
					else //mediatoare
					{
						lineStartx = x + r / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineStarty = y + (r * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
					}
				}
			}
			break;
		default:
			lineStartx = x + r / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineStarty = y + (r * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
			break;
		}



		switch ((int)formad)
		{
		case 0:
			lineFinishx = xd - rd / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineFinishy = yd - (rd * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
			break;
		case 1: // patrat
			float semilaturaP;
			semilaturaP = rd / sqrt(2);

			if (pantad > -1 && pantad < 1 && x > xd) //cadran 1
			{
				lineFinishx = xd + semilaturaP;
				lineFinishy = yd + pantad * semilaturaP;
			}
			else
			{
				if ((pantad < -1 || pantad > 1) && y > yd) //cadran 2
				{
					lineFinishx = (xd * pantad + semilaturaP) / pantad;
					lineFinishy = yd + semilaturaP;
				}
				else
				{
					if (pantad > -1 && pantad < 1 && x < xd) //cadran 3
					{
						lineFinishx = xd - semilaturaP;
						lineFinishy = yd - pantad * semilaturaP;
					}
					else
					{
						if ((pantad < -1 || pantad > 1) && y < yd) //cadran 4
						{
							lineFinishx = (xd * pantad - semilaturaP) / pantad;
							lineFinishy = yd - semilaturaP;
						}
						else //mediatoare
						{
							lineFinishx = xd - rd / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineFinishy = yd - (rd * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
						}
					}
				}
			}
			break;
		case 2: //triunghi
			float tAx, tBx, tCx, tAy, tBy, tCy;
			tAx = xd, tAy = yd - rd;
			tBx = xd - rd * sqrt(3) / 2, tBy = yd + rd / 2;
			tCx = xd + rd * sqrt(3) / 2, tCy = yd + rd / 2;

			if (pantad > (-tan1) && pantad<tan2 && x > tAx) //cadran 1
			{
				lineFinishx = (pantad * xd + tAy - tAx * sqrt(3) - yd) / (pantad - sqrt(3));
				lineFinishy = yd + pantad * (lineFinishx - xd);
			}
			else
			{
				if (pantad < (-tan2) || pantad>tan2 && y > tAy + r * 3 / 2) //cadran 2
				{
					lineFinishx = (rd / 2 + pantad * xd) / pantad;
					lineFinishy = yd + rd / 2;
				}
				else
				{
					if (pantad<tan1 && pantad>-tan2 && x < tAx) //cadran 3
					{
						lineFinishx = (pantad * xd + tAy + tAx * sqrt(3) - yd) / (pantad + sqrt(3));
						lineFinishy = yd + pantad * (lineFinishx - xd);
					}
					else //mediatoare
					{
						lineFinishx = xd - rd / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineFinishy = yd - (rd * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
					}
				}
			}
			break;
		default:
			lineFinishx = xd - rd / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd), lineFinishy = yd - (rd * pantad) / sqrt(pantad * pantad + 1) * sgn(pantad, x, xd) * childAbove(y, yd);
			break;
		}

		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(lineStartx, lineStarty);
		lines[1].position = sf::Vector2f(lineFinishx, lineFinishy);
		window.draw(lines);

		float s = pantad, t = (s - tagBeta) / (1 + s * tagBeta);
		float xM = lineFinishx - 20 / sqrt(s * s + 1) * sgn(s, x, xd) * childAbove(y, yd), yM = lineFinishy - (20 * s) / sqrt(s * s + 1) * sgn(s, x, xd) * childAbove(y, yd);
		float xB = ((2 * xM - lineFinishx) * (1 + s * t) - (xM - lineFinishx) * (s * s + 1)) / (1 + s * t);
		float yB = ((xM - lineFinishx) * (s * s * t + 2 * s - t) + lineFinishy * (1 + s * t)) / (1 + s * t);
		float xC = (lineFinishx * (1 + s * t) + (xM - lineFinishx) * (s * s + 1)) / (1 + s * t);
		float yC = (t * (xM - lineFinishx) * (s * s + 1) + lineFinishy * (1 + s * t)) / (1 + s * t);

		sf::VertexArray lines1(sf::LinesStrip, 2);
		lines1[0].position = sf::Vector2f(lineFinishx, lineFinishy);
		lines1[1].position = sf::Vector2f(xB, yB);
		window.draw(lines1);

		sf::VertexArray lines2(sf::LinesStrip, 2);
		lines2[0].position = sf::Vector2f(lineFinishx, lineFinishy);
		lines2[1].position = sf::Vector2f(xC, yC);
		window.draw(lines2);
	}
}

void DeseneazaArbore(arbore a)
{
	if (!EsteNULL(a))
	{
		DeseneazaNod(a);
		DeseneazaArbore(a->stanga);
		DeseneazaArbore(a->dreapta);
	}
}

bool redimensionare = false, mutareNoduri = false, schimbareForma = false, schimbareCuloare = false, resetareArbore = false;

arbore VerificareNodClicked(arbore a)
{
	if (!EsteNULL(a))
	{
		if (arboreCurent != a)
		{
			if (arboreCurent == null)
			{
				int x = a->x, y = a->y, raza = a->r;
				if (redimensionare)
				{
					if (sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) < raza + 4 &&
						sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) > raza - 4)
					{
						//cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << " -- " << x << " " << y << endl;
						return a;
					}
				}
				else
				{
					if (mutareNoduri || schimbareForma || schimbareCuloare)
					{
						if (sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) < raza)
						{
							//cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << " -- " << x << " " << y << endl;
							return a;
						}
					}
				}
			}
			else
			{
				int x = a->x, y = a->y, raza = a->r;
				if (redimensionare)
				{
					if (sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) < raza + 4 + arboreCurent->r &&
						sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) > raza - 4 - arboreCurent->r)
					{
						return a;
					}
				}
				else
				{
					if (mutareNoduri || schimbareForma || schimbareCuloare)
					{
						if (sqrt((sf::Mouse::getPosition(window).x - x) * (sf::Mouse::getPosition(window).x - x) + (sf::Mouse::getPosition(window).y - y) * (sf::Mouse::getPosition(window).y - y)) < raza + arboreCurent->r)
						{
							return a;
						}
					}
				}

			}
		}

		arbore st = VerificareNodClicked(a->stanga);
		arbore dr = VerificareNodClicked(a->dreapta);
		if (st != null)
		{
			return st;
		}
		if (dr != null)
		{
			return dr;
		}
	}
	return null;
}

void AjustareCoordonate(arbore a, int numarNiveluri, int numarColoane)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!clicked)
		{
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>210 && sf::Mouse::getPosition(window).y < 290)
			{
				mutareNoduri = !mutareNoduri;
				redimensionare = schimbareForma = schimbareCuloare = false;
			}
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>300 && sf::Mouse::getPosition(window).y < 380)
			{
				redimensionare = !redimensionare;
				mutareNoduri = schimbareForma = schimbareCuloare = false;
			}
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>390 && sf::Mouse::getPosition(window).y < 470)
			{
				schimbareForma = !schimbareForma;
				mutareNoduri = redimensionare = schimbareCuloare = false;
			}
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>480 && sf::Mouse::getPosition(window).y < 560)
			{
				schimbareCuloare = !schimbareCuloare;
				mutareNoduri = redimensionare = schimbareForma = false;
			}
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>570 && sf::Mouse::getPosition(window).y < 650)
			{
				resetareArbore = true;
				mutareNoduri = redimensionare = schimbareForma = schimbareCuloare = false;
				CalculeazaCoordonateleSiRazaNodurilorDinArbore(a, 1, numarNiveluri, numarColoane, 0);
			}
			if (sf::Mouse::getPosition(window).x > latime + 10 && sf::Mouse::getPosition(window).x < latime + 90 && sf::Mouse::getPosition(window).y>660 && sf::Mouse::getPosition(window).y < 740)
			{
				numarErori = 0;
				d = 0;
				expresie[0] = null;
				ExpresieCorecta = false;
				ExpresieGresita = false;
				fereastraActiva = 0;

			}
			arbore i = VerificareNodClicked(a);
			if (i != null)
			{
				arboreCurent = i;
				if (schimbareForma)
				{
					arboreCurent->forma++;
					if (arboreCurent->forma > 2) arboreCurent->forma = 0;
				}
				else
				{
					if (schimbareCuloare)
					{
						arboreCurent->culoare++;
						if (arboreCurent->culoare > 3) arboreCurent->culoare = 0;
					}
				}
			}
			clicked = true;
		}
		else
		{
			if (!EsteNULL(arboreCurent)) //if (VerificareNodClicked(a) == null && !EsteNULL(arboreCurent))
			{
				if (redimensionare)
				{
					int inainte = arboreCurent->r;
					arboreCurent->r = sqrt((sf::Mouse::getPosition(window).x - arboreCurent->x) * (sf::Mouse::getPosition(window).x - arboreCurent->x) + (sf::Mouse::getPosition(window).y - arboreCurent->y) * (sf::Mouse::getPosition(window).y - arboreCurent->y));
					float minim = min(inaltime / numarNiveluri / 2, latime / numarColoane / 2) / 1.2f;
					int dupa = arboreCurent->r;
					arboreCurent->dimensiuneText += dupa - inainte;
				}
				else
				{
					if (mutareNoduri)
					{
						if (abs(arboreCurent->x - sf::Mouse::getPosition(window).x) > precizie || abs(arboreCurent->y - sf::Mouse::getPosition(window).y) > precizie)
						{
							arboreCurent->x = sf::Mouse::getPosition(window).x, arboreCurent->y = sf::Mouse::getPosition(window).y;
							//cout << contorGlobal++ << endl;
						}
					}
				}
			}
		}
	}
	else
	{
		clicked = false;
		if (resetareArbore)
		{
			resetareArbore = false;
		}
		arboreCurent = null;
	}
}

void DeseneazaButoanele()
{
	sf::VertexArray lines(sf::LinesStrip, 2);
	lines[0].position = sf::Vector2f(latime, 200);
	lines[1].position = sf::Vector2f(latime, inaltime - 200);
	window.draw(lines);
	lines[0].position = sf::Vector2f(latime, 200);
	lines[1].position = sf::Vector2f(latime + 100, 200);
	window.draw(lines);
	lines[0].position = sf::Vector2f(latime, 750);
	lines[1].position = sf::Vector2f(latime + 100, 750);
	window.draw(lines);

	sf::RectangleShape patrat(sf::Vector2f(80, 80));
	patrat.setOutlineThickness(2);
	patrat.setOutlineColor(sf::Color::Cyan);
	patrat.setPosition(sf::Vector2f(latime + 10, 210));
	if (mutareNoduri) patrat.setFillColor(sf::Color::Green);
	else patrat.setFillColor(sf::Color::White);
	window.draw(patrat);

	patrat.setPosition(sf::Vector2f(latime + 10, 300));
	if (redimensionare) patrat.setFillColor(sf::Color::Green);
	else patrat.setFillColor(sf::Color::White);
	window.draw(patrat);

	patrat.setPosition(sf::Vector2f(latime + 10, 390));
	if (schimbareForma) patrat.setFillColor(sf::Color::Green);
	else patrat.setFillColor(sf::Color::White);
	window.draw(patrat);

	patrat.setPosition(sf::Vector2f(latime + 10, 480));
	if (schimbareCuloare) patrat.setFillColor(sf::Color::Green);
	else patrat.setFillColor(sf::Color::White);
	window.draw(patrat);

	patrat.setPosition(sf::Vector2f(latime + 10, 570));
	if (resetareArbore) patrat.setFillColor(sf::Color::Green);
	else patrat.setFillColor(sf::Color::White);
	window.draw(patrat);

	patrat.setPosition(sf::Vector2f(latime + 10, 660));
	patrat.setFillColor(sf::Color::White);
	window.draw(patrat);
}

struct Dreptunghi
{
	int x1, x2, y1, y2;
}dreptunghiInserareFunctie, dreptunghiAfiseazaArbore, dreptunghiSchimbareLimba, dreptunghiFunctiiSiOperatori;

bool inserareFunctie = false, inserareVariabila = false, deseneazaArbore = false;
char variabila[20];
int dimensiuneVariabilaCurenta = 0;

void DeseneazaMeniu()
{
	sf::Text text;
	text.setFont(font);

	text.setCharacterSize(60);
	if (limba == 0)
	{
		text.setString("Evaluator de Expresii");
	}
	else
	{
		text.setString("Expression Evaluator");
	}
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(sf::Vector2f(textRect.width / 2, textRect.height / 2));
	text.setPosition(sf::Vector2f(latime / 2 + 50, 100));
	text.setFillColor(sf::Color::White);
	window.draw(text);

	text.setCharacterSize(30);
	if (limba == 0)
	{
		text.setString("Introduceti o expresie:");
	}
	else
	{
		text.setString("Enter an expression:");
	}
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(100, 300));
	textRect = text.getLocalBounds();
	text.setFillColor(sf::Color::White);
	dreptunghiInserareFunctie.x1 = 100, dreptunghiInserareFunctie.x2 = textRect.width + 100, dreptunghiInserareFunctie.y1 = 300, dreptunghiInserareFunctie.y2 = 300 + textRect.height;
	window.draw(text);
	/*
	sf::RectangleShape patrat(sf::Vector2f(700, 50));
	sf::FloatRect patratRect = patrat.getLocalBounds();
	patrat.setOrigin(sf::Vector2f(0, patratRect.height / 2));
	patrat.setOutlineThickness(3);
	if (inserareFunctie)
	{
		patrat.setOutlineColor(sf::Color::Green);
	}
	else
	{
		patrat.setOutlineColor(sf::Color::White);
	}
	patrat.setFillColor(sf::Color::Black);
	patrat.setPosition(sf::Vector2f(latime / 2 - 50, 300));
	dreptunghiInserareFunctie.x1 = latime / 2 - 50, dreptunghiInserareFunctie.x2 = latime / 2 + 650, dreptunghiInserareFunctie.y1 = 275, dreptunghiInserareFunctie.y2 = 325;

	window.draw(patrat);
	*/
	text.setCharacterSize(30);
	text.setString(expresie);
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(textRect.width + 120, 300));
	text.setFillColor(sf::Color::White);
	window.draw(text);

	text.setCharacterSize(30);
	if (limba == 0)
	{
		text.setString("Schimba in engleza");
	}
	else
	{
		text.setString("Switch to romanian");
	}
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(1500, 830));
	textRect = text.getLocalBounds();
	text.setFillColor(sf::Color::White);
	dreptunghiSchimbareLimba.x1 = 1500, dreptunghiSchimbareLimba.x2 = textRect.width + 1500, dreptunghiSchimbareLimba.y1 = 830, dreptunghiSchimbareLimba.y2 = 830 + textRect.height;
	window.draw(text);

	text.setCharacterSize(30);
	if (limba == 0)
	{
		text.setString("Functii si Operatori");
	}
	else
	{
		text.setString("Funtions and Operators");
	}
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(100, 830));
	textRect = text.getLocalBounds();
	text.setFillColor(sf::Color::White);
	dreptunghiFunctiiSiOperatori.x1 = 100, dreptunghiFunctiiSiOperatori.x2 = textRect.width + 100, dreptunghiFunctiiSiOperatori.y1 = 830, dreptunghiFunctiiSiOperatori.y2 = 830 + textRect.height;
	window.draw(text);

	if (inserareVariabila)
	{
		text.setCharacterSize(30);
		char textVar[100] = "Introduceti o valoare pentru variabila ";
		strcat_s(textVar, numeVariabila);
		strcat_s(textVar, " :");
		text.setString(textVar);
		sf::FloatRect textRect2 = text.getLocalBounds();
		text.setOrigin(sf::Vector2f(0, 0));
		text.setPosition(sf::Vector2f(100, 350));
		textRect2 = text.getLocalBounds();
		text.setFillColor(sf::Color::White);
		window.draw(text);

		text.setCharacterSize(30);
		text.setString(variabila);
		textRect = text.getLocalBounds();
		text.setOrigin(sf::Vector2f(0, 0));
		text.setPosition(sf::Vector2f(textRect2.width + 120, 350));
		text.setFillColor(sf::Color::White);
		window.draw(text);
	}
	else
	{
		if (ExpresieCorecta)
		{
			text.setCharacterSize(30);

			if (limba == 0)
			{
				text.setString("Expresia este corecta!");
			}
			else
			{
				text.setString("The expression is correct!");
			}
			sf::FloatRect textRect2 = text.getLocalBounds();
			text.setOrigin(sf::Vector2f(0, 0));
			text.setPosition(sf::Vector2f(100, 350));
			textRect2 = text.getLocalBounds();
			text.setFillColor(sf::Color::Green);
			window.draw(text);

			if (NuSePoateCalcula == false)
			{
				text.setCharacterSize(30);
				char chr[200] = "";
				if (limba == 0)
				{
					strcpy_s(chr, "Rezultatul expresiei este: ");
				}
				else
				{
					strcpy_s(chr, "The expression result is: ");
				}
				char chrNumar[100] = "";
				int decimal = 0, sign = 0;
				//_fcvt_s(chrNumar, 10, valoareaExpresiei, &decimal, &sign);
				_snprintf_s(chrNumar, 10, "%f", valoareaExpresiei);
				strcat_s(chr, chrNumar);
				text.setString(chr);
				sf::FloatRect textRect2 = text.getLocalBounds();
				text.setOrigin(sf::Vector2f(0, 0));
				text.setPosition(sf::Vector2f(100, 400));
				textRect2 = text.getLocalBounds();
				text.setFillColor(sf::Color::Green);
				window.draw(text);
			}
			else
			{
				text.setCharacterSize(30);
				if (limba == 0)
				{
					text.setString("Rezultatul nu se poate calcula!");
				}
				else
				{
					text.setString("The result cannot be calculated!");
				}
				text.setOrigin(sf::Vector2f(0, 0));
				text.setPosition(sf::Vector2f(100, 400));
				text.setFillColor(sf::Color::Red);
				window.draw(text);
			}

			/*
			sf::RectangleShape patrat2(sf::Vector2f(250, 30));
			patrat2.setOutlineThickness(3);
			patrat2.setOutlineColor(sf::Color::Green);
			patrat2.setFillColor(sf::Color::Black);
			patrat2.setPosition(sf::Vector2f(textRect2.width + 120, 400));
			dreptunghiAfiseazaArbore.x1 = textRect2.width + 120, dreptunghiAfiseazaArbore.x2 = textRect2.width + 320, dreptunghiAfiseazaArbore.y1 = 400, dreptunghiAfiseazaArbore.y2 = 450;

			window.draw(patrat2);
			*/
			text.setCharacterSize(30);
			if (limba == 0)
			{
				text.setString("Deseneaza arborele");
			}
			else
			{
				text.setString("Draw the tree");
			}
			text.setOrigin(sf::Vector2f(0, 0));
			text.setPosition(sf::Vector2f(textRect2.width + 120, 350));
			textRect = text.getLocalBounds();
			text.setFillColor(sf::Color::White);
			dreptunghiAfiseazaArbore.x1 = textRect2.width + 120, dreptunghiAfiseazaArbore.x2 = textRect2.width + 120 + textRect.width, dreptunghiAfiseazaArbore.y1 = 350, dreptunghiAfiseazaArbore.y2 = 350 + textRect2.height;
			window.draw(text);
		}
		else
		{
			if (ExpresieGresita)
			{
				text.setCharacterSize(30);
				if (limba == 0)
				{
					text.setString("Expresia este gresita!");
				}
				else
				{
					text.setString("Wrong expression!");
				}
				sf::FloatRect textRect2 = text.getLocalBounds();
				textRect2 = text.getLocalBounds();
				text.setOrigin(sf::Vector2f(0, 0));
				text.setPosition(sf::Vector2f(100, 350));
				text.setFillColor(sf::Color::Red);
				window.draw(text);
				for (int i = 0; i < numarErori; i++)
				{
					text.setCharacterSize(30);
					text.setString(eroriDeAfisat[i]);
					text.setOrigin(sf::Vector2f(0, 0));
					text.setPosition(sf::Vector2f(100, 400 + i * 50));
					text.setFillColor(sf::Color::Red);
					window.draw(text);
				}
			}
		}
	}
}

void FunctionalitateMeniu()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clicked == false)
		{
			if (sf::Mouse::getPosition(window).x > dreptunghiInserareFunctie.x1 && sf::Mouse::getPosition(window).x < dreptunghiInserareFunctie.x2 &&
				sf::Mouse::getPosition(window).y > dreptunghiInserareFunctie.y1 && sf::Mouse::getPosition(window).y < dreptunghiInserareFunctie.y2)
			{
				inserareFunctie = !inserareFunctie;
				if (inserareFunctie)
				{
					numarErori = 0;
					d = 0;
					expresie[0] = null;
					ExpresieCorecta = false;
					ExpresieGresita = false;
				}
			}
			else
			{
				if (sf::Mouse::getPosition(window).x > dreptunghiAfiseazaArbore.x1 && sf::Mouse::getPosition(window).x < dreptunghiAfiseazaArbore.x2 &&
					sf::Mouse::getPosition(window).y > dreptunghiAfiseazaArbore.y1 && sf::Mouse::getPosition(window).y < dreptunghiAfiseazaArbore.y2)
				{
					deseneazaArbore = true;
				}
				else
				{
					if (sf::Mouse::getPosition(window).x > dreptunghiSchimbareLimba.x1 && sf::Mouse::getPosition(window).x < dreptunghiSchimbareLimba.x2 &&
						sf::Mouse::getPosition(window).y > dreptunghiSchimbareLimba.y1 && sf::Mouse::getPosition(window).y < dreptunghiSchimbareLimba.y2)
					{
						limba = abs(limba - 1);
						if (ExpresieGresita)
						{
							if (limba == 0)
							{
								afisareErori();
							}
							else
							{
								Errors();
							}
						}
					}
					else
					{
						if (sf::Mouse::getPosition(window).x > dreptunghiFunctiiSiOperatori.x1 && sf::Mouse::getPosition(window).x < dreptunghiFunctiiSiOperatori.x2 &&
							sf::Mouse::getPosition(window).y > dreptunghiFunctiiSiOperatori.y1 && sf::Mouse::getPosition(window).y < dreptunghiFunctiiSiOperatori.y2)
						{
							fereastraActiva = 2;
						}
					}
				}

			}
			clicked = true;
		}
	}
	else
	{
		if (clicked == true)
		{
			clicked = false;
		}
	}
}

void FunctionalitateFereastraFunctiiSiOperatori()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (clicked == false)
		{
			if (sf::Mouse::getPosition(window).x > dreptunghiSchimbareLimba.x1 && sf::Mouse::getPosition(window).x < dreptunghiSchimbareLimba.x2 &&
				sf::Mouse::getPosition(window).y > dreptunghiSchimbareLimba.y1 && sf::Mouse::getPosition(window).y < dreptunghiSchimbareLimba.y2)
			{
				limba = abs(limba - 1);
			}
			else
			{
				if (sf::Mouse::getPosition(window).x > dreptunghiFunctiiSiOperatori.x1 && sf::Mouse::getPosition(window).x < dreptunghiFunctiiSiOperatori.x2 &&
					sf::Mouse::getPosition(window).y > dreptunghiFunctiiSiOperatori.y1 && sf::Mouse::getPosition(window).y < dreptunghiFunctiiSiOperatori.y2)
				{
					fereastraActiva = 0;
				}
			}
			clicked = true;
		}
	}
	else
	{
		if (clicked == true)
		{
			clicked = false;
		}
	}
}

void CitesteVariabilaDeLaTastatura(char var[])
{
	inserareVariabila = true;
	strcpy_s(variabila, "");
	dimensiuneVariabilaCurenta = 0;
	sf::Event event;
	while (inserareVariabila)
	{
		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode == 8)
					{
						variabila[dimensiuneVariabilaCurenta - 1] = null;
						dimensiuneVariabilaCurenta--;
					}
					else
					{
						if (event.text.unicode == 13)
						{
							inserareVariabila = false;
							strcpy_s(var, 20, variabila);
							return;
						}
						else
						{
							variabila[dimensiuneVariabilaCurenta++] = static_cast<char>(event.text.unicode);
							variabila[dimensiuneVariabilaCurenta] = null;
						}
					}
				}
			}
			window.clear(sf::Color::Black);
			DeseneazaMeniu();
			FunctionalitateMeniu();

			//cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;

			window.display();
		}
	}
	return;
}

void DeseneazaFuntiileSiOperatorii()
{
	sf::Text text;
	text.setFont(font);
	char chr[100] = "";
	int lungime;

	text.setCharacterSize(40);
	if (limba == 0)
	{
		text.setString("Operatii binare:");
	}
	else
	{
		text.setString("Binary operations:");
	}
	text.setPosition(sf::Vector2f(100, 100));
	text.setFillColor(sf::Color::White);
	window.draw(text);
	text.setCharacterSize(30);
	for (int i = 1; i <= 12; i++)
	{
		strcpy_s(chr, functii[i]);
		text.setString(chr);
		text.setPosition(sf::Vector2f(100, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
		if (limba == 0)
		{
			strcpy_s(chr, functiiRomana[i]);
		}
		else
		{
			strcpy_s(chr, functiiEngleza[i]);
		}
		text.setString(chr);
		text.setPosition(sf::Vector2f(150, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
	}

	text.setCharacterSize(40);
	if (limba == 0)
	{
		text.setString("Operatii pe biti:");
	}
	else
	{
		text.setString("Bits operations:");
	}
	text.setPosition(sf::Vector2f(600, 100));
	text.setFillColor(sf::Color::White);
	window.draw(text);
	text.setCharacterSize(30);
	for (int i = 1; i <= 4; i++)
	{
		strcpy_s(chr, functii[i + 12]);
		text.setString(chr);
		text.setPosition(sf::Vector2f(600, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
		if (limba == 0)
		{
			strcpy_s(chr, functiiRomana[i + 12]);
		}
		else
		{
			strcpy_s(chr, functiiEngleza[i + 12]);
		}
		text.setString(chr);
		text.setPosition(sf::Vector2f(650, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
	}

	text.setCharacterSize(40);
	if (limba == 0)
	{
		text.setString("Constante:");
	}
	else
	{
		text.setString("Constants:");
	}
	text.setPosition(sf::Vector2f(600, 500));
	text.setFillColor(sf::Color::White);
	window.draw(text);
	text.setCharacterSize(30);
	for (int i = 1; i <= 2; i++)
	{
		strcpy_s(chr, functii[i + 16]);
		text.setString(chr);
		text.setPosition(sf::Vector2f(600, 550 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
		if (limba == 0)
		{
			strcpy_s(chr, functiiRomana[i + 16]);
		}
		else
		{
			strcpy_s(chr, functiiEngleza[i + 16]);
		}
		text.setString(chr);
		text.setPosition(sf::Vector2f(650, 550 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
	}

	text.setCharacterSize(40);
	if (limba == 0)
	{
		text.setString("Functii:");
	}
	else
	{
		text.setString("Functions:");
	}
	text.setPosition(sf::Vector2f(1100, 100));
	text.setFillColor(sf::Color::White);
	window.draw(text);
	text.setCharacterSize(30);
	for (int i = 1; i <= 13; i++)
	{
		strcpy_s(chr, functii[i + 18]);
		text.setString(chr);
		text.setPosition(sf::Vector2f(1100, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
		if (limba == 0)
		{
			strcpy_s(chr, functiiRomana[i + 18]);
		}
		else
		{
			strcpy_s(chr, functiiEngleza[i + 18]);
		}
		text.setString(chr);
		text.setPosition(sf::Vector2f(1220, 150 + i * 45));
		text.setFillColor(sf::Color::White);
		window.draw(text);
	}

	text.setCharacterSize(30);
	if (limba == 0)
	{
		text.setString("Schimba in engleza");
	}
	else
	{
		text.setString("Switch to romanian");
	}
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(1500, 830));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setFillColor(sf::Color::White);
	dreptunghiSchimbareLimba.x1 = 1500, dreptunghiSchimbareLimba.x2 = textRect.width + 1500, dreptunghiSchimbareLimba.y1 = 830, dreptunghiSchimbareLimba.y2 = 830 + textRect.height;
	window.draw(text);

	text.setCharacterSize(30);
	if (limba == 0)
	{
		text.setString("Inapoi la meniu");
	}
	else
	{
		text.setString("Back to menu");
	}
	text.setOrigin(sf::Vector2f(0, 0));
	text.setPosition(sf::Vector2f(100, 830));
	textRect = text.getLocalBounds();
	text.setFillColor(sf::Color::White);
	dreptunghiFunctiiSiOperatori.x1 = 100, dreptunghiFunctiiSiOperatori.x2 = textRect.width + 100, dreptunghiFunctiiSiOperatori.y1 = 830, dreptunghiFunctiiSiOperatori.y2 = 830 + textRect.height;
	window.draw(text);
}

int main()
{
	arbore a = null;
	int numarNiveluri = 0, numarColoane = 0;
	ifstream ffunctii("functii.txt");
	ifstream fromana("functii_romana.txt");
	ifstream fengleza("functii_engleza.txt");
	for (int i = 1; i <= 31; i++)
	{
		ffunctii.getline(functii[i], 100);
		fromana.getline(functiiRomana[i], 100);
		fengleza.getline(functiiEngleza[i], 100);
	}
	if (!font.loadFromFile("Fonts/MyFont.ttf"))
	{
		throw ("Error Font Loading");
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered)
			{
				if (inserareFunctie)
				{
					if (event.text.unicode == 8)
					{
						expresie[d - 1] = null;
						d--;
					}
					else
					{
						if (event.text.unicode == 13)
						{
							inserareFunctie = false;
							_strlwr_s(expresie);
							expresieValida(expresie);
							if (ExpresieCorecta)
							{
								F.lung = d;
								valoareaExpresiei = ValoareFunctie(F);
							}
							else
							{
								if (limba == 0)
								{
									afisareErori();
								}
								else
								{
									Errors();
								}
								ExpresieGresita = true;
							}
						}
						else
						{
							expresie[d++] = static_cast<char>(event.text.unicode);
							expresie[d] = null;
						}
					}
				}
			}
		}
		window.clear(sf::Color::Black);
		if (deseneazaArbore)
		{
			deseneazaArbore = false;
			InitArbore(a);
			CitesteArbore(a, F, 2, d - 2);
			numarNiveluri = nrNiveluri(a);
			numarColoane = nrColoane(a);
			CalculeazaCoordonateleSiRazaNodurilorDinArbore(a, 1, numarNiveluri, numarColoane, 0);
			fereastraActiva = 1;
		}
		switch (fereastraActiva)
		{
		case 0:
			DeseneazaMeniu();
			FunctionalitateMeniu();
			break;
		case 1:
			DeseneazaArbore(a);
			AjustareCoordonate(a, numarNiveluri, numarColoane);
			DeseneazaButoanele();
			break;
		case 2:
			DeseneazaFuntiileSiOperatorii();
			FunctionalitateFereastraFunctiiSiOperatori();
			break;
		}

		window.display();
	}
	return 0;
}
