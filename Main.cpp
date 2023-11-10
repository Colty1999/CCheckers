#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <math.h>

int ik, jk, ik1, jk1;
char tab[8][8];

void gra(char*, int, int);
void utworz_plansze();
void wyswietl_plansze();
void zapis_stanu(char*);
void wczytanie_stanu(char*, int);
void koniec_gry();
int g_or_k();
void ruch_gracza();
void g1_wybor_pionka(int* i, int* j);
void drugi_gracz();
void g2_wybor_pionka(int* i, int* j);
void ruch_komputera();
int wartosc_gry(int);
int minimax(int, int);



void main()
{
	char plik[20];
	printf("Do jakiego pliku chcesz zapisywac stan gry?\n");
	gets_s(plik);

	system("cls");
	int gracz_czy_komputer = g_or_k();

	system("cls");
	char nap[20];
	printf("Czy wczytac stan gry? (tak/nie) \n");
	gets_s(nap);
	if (strcmp("tak", nap) == 0)
	{
		wczytanie_stanu(plik, gracz_czy_komputer);
		gra(plik, 1, gracz_czy_komputer);
	}
	else
		gra(plik, 0, gracz_czy_komputer);
}

void gra(char* plik, int nowa_czy_wczytac, int gracz_czy_komputer)
{
	if (nowa_czy_wczytac == 0)
	{
		system("cls");
		utworz_plansze();
		printf("\n Witaj w grze w warcaby! \n Pionki pierwszego gracza sa oznaczone jako X \n Y steruje gracz 2 lub komputer \n Milej zabawy!\n\n\n");
	}
	else
	{
		system("cls");
		wyswietl_plansze();
	}
	ruch_gracza();
	koniec_gry();
	if (gracz_czy_komputer == 0)
		drugi_gracz();
	else
	{
		printf("\n%d\n", minimax(2, 0));
		ruch_komputera();
		//printf("%d\n%d\n%d\n%d\n", ik, jk, ik1, jk1);
	}
	koniec_gry();
	zapis_stanu(plik);
	gra(plik, 1, gracz_czy_komputer);
}

void utworz_plansze() //tworzy plansze dla nowej gry
{
	char rzad = 'A';
	int wiersz = 1;
	printf("\t");
	for (int i = 0; i < 8; rzad++ && i++)
		printf("%c\t", rzad);
	printf("\n\n");
	for (int i = 0; i < 8; wiersz++ && i++)
	{
		printf("%d\t", wiersz);
		for (int j = 0; j < 8; j++)
		{
			if (i < 3)
			{
				if (j % 2 == 1 && i % 2 == 1)
				{
					printf("\033[1;32m");
					tab[i][j] = 'Y';
				}
				else if (j % 2 == 0 && i % 2 == 1)
				{
					printf("\033[1;33m");
					tab[i][j] = 'O';
				}
				else if (j % 2 == 1 && i % 2 == 0)
				{
					printf("\033[1;33m");
					tab[i][j] = 'O';
				}
				else if (j % 2 == 0 && i % 2 == 0)
				{
					printf("\033[1;32m");
					tab[i][j] = 'Y';
				}
				printf("%c\t", tab[i][j]);
			}
			else if (i < 5)
			{
				printf("\033[1;33m");
				tab[i][j] = 'O';
				printf("%c\t", tab[i][j]);
			}
			else
			{
				if (j % 2 == 1 && i % 2 == 1)
				{
					printf("\033[1;31m");
					tab[i][j] = 'X';
				}
				else if (j % 2 == 0 && i % 2 == 1)
				{
					printf("\033[1;33m");
					tab[i][j] = 'O';
				}
				else if (j % 2 == 1 && i % 2 == 0)
				{
					printf("\033[1;33m");
					tab[i][j] = 'O';
				}
				else if (j % 2 == 0 && i % 2 == 0)
				{
					printf("\033[1;31m");
					tab[i][j] = 'X';
				}

				printf("%c\t", tab[i][j]);
			}
		}
		printf("\n");
		printf("\033[0m");
	}

}

void wyswietl_plansze() //wyswietla plansze zaladowana z pliku
{
	char rzad = 'A';
	int wiersz = 1;
	printf("\t");
	for (int i = 0; i < 8; rzad++ && i++)
		printf("%c\t", rzad);
	printf("\n\n");
	for (int i = 0; i < 8; wiersz++ && i++)
	{
		printf("%d\t", wiersz);
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] == 'X')
				printf("\033[1;31m");
			else if (tab[i][j] == 'Y')
				printf("\033[1;32m");
			else
				printf("\033[1;33m");
			printf("%c\t", tab[i][j]);
			printf("\033[0m");
		}
		printf("\n");
	}
}

void wczytanie_stanu(char* plik, int gracz_czy_komputer) // wczytuje stan gry do tabeli
{
	char wczyt[20];
	printf("Z jakiego pliku chcesz wczytac stan? (wpisz 'nowa' aby rozpoczac nowa gre)\n");
	gets_s(wczyt);
	if (strcmp("nowa", wczyt) == 0)
	{
		gra(plik, 0, gracz_czy_komputer);
	}
	else
	{
		FILE* wczytywanie = fopen(wczyt, "r");
		if (wczytywanie == NULL)
		{
			puts("Otwieranie pliku nie powiodlo sie\n");
			exit(0);
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					//fscanf(wczytywanie, "%c", tab[i][j]);
					tab[i][j] = fgetc(wczytywanie);
				}
			}
		}
		fclose(wczytywanie);
	}
}

void zapis_stanu(char* plik) // zapisuje stan gry do pliku
{
	FILE* odczyt_zapis = fopen(plik, "w");
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			fprintf(odczyt_zapis, "%c", tab[i][j]);
		//fprintf(odczyt_zapis, "\n");
		//fputc(tab[i][j], odczyt_zapis);
	}
	fclose(odczyt_zapis);
}

void koniec_gry()
{
	int X = 0;
	int Y = 0;
	for (int i = 0; i < 8; i++) // sprawdza tabele na obecnosc X i Y oraz liczy ich ilosc
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] == 'X')
				X += 1;
			else if (tab[i][j] == 'Y')
				Y += 1;
		}
	}
	if (X == 0) //jesli program nie wykryje X-ow na planszy zakonczy dzialanie
	{
		printf("Przegrales!");
		exit(0);
	}
	else if (Y == 0) //jesli program nie wykryje Y-kow na planszy zakonczy dzialanie
	{

		printf("Gratulacje, wygrales!");
		exit(0);
	}
}

int g_or_k()
{
	char g_czy_k[20];
	printf("Chcesz grac z 2 graczem czy z komputerem? \ngracz - wpisz 'gracz' \nkomputer - wpisz 'komputer' \n");
	gets_s(g_czy_k);
	while (strcmp("gracz", g_czy_k) != 0 && strcmp("komputer", g_czy_k) != 0)
	{
		system("cls");
		printf("Niepoprawna zmienna \nChcesz grac z 2 graczem czy z komputerem? \ngracz - wpisz 'gracz' \nkomputer - wpisz 'komputer' \n");
		gets_s(g_czy_k);
	}
	if (strcmp("gracz", g_czy_k) == 0)
		return 0;
	else if (strcmp("komputer", g_czy_k) == 0)
		return 1;
}

void ruch_gracza()
{
	int i;
	int j;
	int i1;
	int j1;
	char poziom1;
	int pion1;
	g1_wybor_pionka(&i, &j);
	printf("\n Gdzie chcesz sie ruszyc? (wybor innego pionka - wpisz 'Z0') \n");
	scanf(" %c%d", &poziom1, &pion1);
	if (poziom1 == 'Z' && pion1 == 0)
		g1_wybor_pionka(&i, &j);
	j1 = poziom1 - '0';
	j1 -= 17;
	i1 = pion1 - 1;
	//while (((j1 != j + 1 && j1 != j - 1) || (i1 != i + 1 && i1 != i - 1) || tab[i1][j1] != 'O') && ((j1 != j + 2 && j1 != j - 2) || (i1 != i + 2 && i1 != i - 2) || tab[i1][j1] != 'O' || (tab[i + 1][j + 1] != 'Y' && tab[i + 1][j - 1] != 'Y' && tab[i - 1][j + 1] != 'Y' && tab[i - 1][j - 1] != 'Y')))
	while ((i1 > 7 || j1 > 7) || (i1 < 0 || j1 < 0) || (((i1 != i + 1 || j1 != j + 1) && (i1 != i + 1 || j1 != j - 1) && (i1 != i - 1 && j1 != j + 1) && (i1 != i - 1 || j1 != j - 1)) || tab[i1][j1] != 'O') && (((i1 != i + 2 || j1 != j + 2 || tab[i + 1][j + 1] != 'Y') && (i1 != i + 2 || j1 != j - 2 || tab[i + 1][j - 1] != 'Y') && (i1 != i - 2 || j1 != j + 2 || tab[i - 1][j + 1] != 'Y') && (i1 != i - 2 || j1 != j - 2 || tab[i - 1][j - 1] != 'Y')) || tab[i1][j1] != 'O'))
		// sprawdza czy wybrano poprawne miejsce ruchu
	{
		system("cls");
		wyswietl_plansze();
		printf("Wprowadz poprawne miejsce ruchu (wybor innego pionka - wpisz 'Z0')\n");
		scanf(" %c%d", &poziom1, &pion1);
		if (poziom1 == 'Z' && pion1 == 0)
			g1_wybor_pionka(&i, &j);
		j1 = poziom1 - '0';
		j1 -= 17;
		i1 = pion1 - 1;
	}
	if ((j1 == j + 1 || j1 == j - 1) && (i1 == i + 1 || i1 == i - 1)) //wykonanie ruchu
	{
		tab[i][j] = 'O';
		tab[i1][j1] = 'X';
	}
	else // wykonanie zbicia
	{
		tab[i][j] = 'O';
		tab[i1][j1] = 'X';
		if (i1 > i&& j1 > j)
			tab[i + 1][j + 1] = 'O';
		else if (i1 > i&& j1 < j)
			tab[i + 1][j - 1] = 'O';
		else if (i1 < i && j1 > j)
			tab[i - 1][j + 1] = 'O';
		else if (i1 < i && j1 < j)
			tab[i - 1][j - 1] = 'O';
	}
	system("cls");
	wyswietl_plansze();
}

void g1_wybor_pionka(int* i, int* j)
{
	char poziom;  //pion i poziom to razem lokalizacja wybranego pionka
	int pion;
	printf("\nTwoj ruch! \n Ruszasz X-ami \n Wybierz pionek!  \n");
	scanf(" %c%d", &poziom, &pion);
	*j = poziom - '0';
	*j -= 17;
	*i = pion - 1;
	while (tab[*i][*j] != 'X')
	{ //sprawdza czy wybrano poprawny pionek
		system("cls");
		wyswietl_plansze();
		printf("Blednie wybrane pole \n wybierz poprawny pionek \n");
		scanf(" %c%d", &poziom, &pion);
		*j = poziom - '0';
		*j -= 17;
		*i = pion - 1;
	}
}

void drugi_gracz()
{
	int i;
	int j;
	int i1;
	int j1;
	char poziom1;
	int pion1;
	g2_wybor_pionka(&i, &j);
	printf("\n Gdzie chcesz sie ruszyc? (wybor innego pionka - wpisz 'Z0') \n");
	scanf(" %c%d", &poziom1, &pion1);
	if (poziom1 == 'Z' && pion1 == 0)
		g2_wybor_pionka(&i, &j);
	j1 = poziom1 - '0';
	j1 -= 17;
	i1 = pion1 - 1;
	//while (((j1 != j + 1 && j1 != j - 1) || (i1 != i + 1 && i1 != i - 1) || tab[i1][j1] != 'O') && ((j1 != j + 2 && j1 != j - 2) || (i1 != i + 2 && i1 != i - 2) || tab[i1][j1] != 'O' || (tab[i + 1][j + 1] != 'X' && tab[i + 1][j - 1] != 'X' && tab[i - 1][j + 1] != 'X' && tab[i - 1][j - 1] != 'X')))
	while ((i1 > 7 || j1 > 7) || (i1 < 0 || j1 < 0) || (((i1 != i + 1 || j1 != j + 1) && (i1 != i + 1 || j1 != j - 1) && (i1 != i - 1 && j1 != j + 1) && (i1 != i - 1 || j1 != j - 1)) || tab[i1][j1] != 'O') && (((i1 != i + 2 || j1 != j + 2 || tab[i + 1][j + 1] != 'X') && (i1 != i + 2 || j1 != j - 2 || tab[i + 1][j - 1] != 'X') && (i1 != i - 2 || j1 != j + 2 || tab[i - 1][j + 1] != 'X') && (i1 != i - 2 || j1 != j - 2 || tab[i - 1][j - 1] != 'X')) || tab[i1][j1] != 'O'))
		// sprawdza czy wybrano poprawne miejsce ruchu
	{
		system("cls");
		wyswietl_plansze();
		printf("Wprowadz poprawne miejsce ruchu (wybor innego pionka - wpisz 'Z0')\n");
		scanf(" %c%d", &poziom1, &pion1);
		if (poziom1 == 'Z' && pion1 == 0)
			g2_wybor_pionka(&i, &j);
		j1 = poziom1 - '0';
		j1 -= 17;
		i1 = pion1 - 1;
	}
	if ((j1 == j + 1 || j1 == j - 1) && (i1 == i + 1 || i1 == i - 1)) //wykonanie ruchu
	{
		tab[i][j] = 'O';
		tab[i1][j1] = 'Y';
	}
	else // wykonanie zbicia
	{
		tab[i][j] = 'O';
		tab[i1][j1] = 'Y';
		if (i1 > i&& j1 > j)
			tab[i + 1][j + 1] = 'O';
		else if (i1 > i&& j1 < j)
			tab[i + 1][j - 1] = 'O';
		else if (i1 < i && j1 > j)
			tab[i - 1][j + 1] = 'O';
		else if (i1 < i && j1 < j)
			tab[i - 1][j - 1] = 'O';
	}
	system("cls");
	wyswietl_plansze();
}

void g2_wybor_pionka(int* i, int* j)
{
	char poziom;  //pion i poziom to razem lokalizacja wybranego pionka
	int pion;
	printf("Twoj ruch! \n Ruszasz Y-kami \n Wybierz pionek!  \n");
	scanf(" %c%d", &poziom, &pion);
	*j = poziom - '0';
	*j -= 17;
	*i = pion - 1;
	while (tab[*i][*j] != 'Y')
	{ //sprawdza czy wybrano poprawny pionek
		system("cls");
		wyswietl_plansze();
		printf("Blednie wybrane pole \n wybierz poprawny pionek \n");
		scanf(" %c%d", &poziom, &pion);
		*j = poziom - '0';
		*j -= 17;
		*i = pion - 1;
	}
}

void ruch_komputera()
{
	if ((jk1 == jk + 1 || jk1 == jk - 1) && (ik1 == ik + 1 || ik1 == ik - 1)) //wykonanie ruchu
	{
		tab[ik][jk] = 'O';
		tab[ik1][jk1] = 'Y';
	}
	else // wykonanie zbicia
	{
		tab[ik][jk] = 'O';
		tab[ik1][jk1] = 'Y';
		if (ik1 > ik&& jk1 > jk)
			tab[ik + 1][jk + 1] = 'O';
		else if (ik1 > ik&& jk1 < jk)
			tab[ik + 1][jk - 1] = 'O';
		else if (ik1 < ik && jk1 > jk)
			tab[ik - 1][jk + 1] = 'O';
		else if (ik1 < ik && jk1 < jk)
			tab[ik - 1][jk - 1] = 'O';
	}
	system("cls");
	wyswietl_plansze();
}

int wartosc_gry(int warstwa)
{

	int X = 0;
	int Y = 0;
	for (int i = 0; i < 8; i++) // sprawdza tabele na obecnosc X i Y oraz liczy ich ilosc
	{
		for (int j = 0; j < 8; j++)
		{
			if (tab[i][j] == 'X')
				X += 1;
			else if (tab[i][j] == 'Y')
				Y += 1;
		}
	}
	if (X == 0) //jesli AI nie wykryje X-ow na planszy notuje zwyciestwo
	{
		return 10 - warstwa;
	}
	else if (Y == 0) //jesli AI nie wykryje Y-kow na planszy notuje przegrana
	{
		return -10 + warstwa;
	}
	return 0; //gra zakonczona remisem
}

int minimax(int warstwa, int gracz_czy_komputer)
{
	int best;
	char znak;
	char przeciwny_znak;
	int punkty = wartosc_gry(warstwa);
	if (warstwa == 0 || punkty != 0) // sprawdzenie czy gra jest rozstrzygnieta
		return punkty;
	else
	{
		// sprawdzenie czyj jest nastepny ruch

		if (gracz_czy_komputer == 0) // ruch komputera
		{
			best = -1000;
			znak = 'Y';
			przeciwny_znak = 'X';
		}
		else  // ruch gracza
		{
			best = 1000;
			znak = 'X';
			przeciwny_znak = 'Y';
		}

		// obliczenie minmax + zapisanie najlepszego ruchu

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				for (int i1 = -2; i1 < 3; i1++)
				{
					for (int j1 = -2; j1 < 3; j1++)
					{
						if (tab[i][j] == znak && ((i1 == 1 && j1 == 1) || (i1 == 1 && j1 == -1) || (i1 == -1 && j1 == 1) || (i1 == -1 && j1 == -1)) && (i1 + i > 0 && j1 + j > 0 && i1 + i < 8 && j1 + j < 8) && tab[i + i1][j + j1] == 'O')
						{

							i1 = i + i1;
							j1 = j + j1;

							tab[i][j] = 'O';
							tab[i1][j1] = znak;

							if (gracz_czy_komputer == 0)
							{
								int wartosc = minimax(warstwa - 1, 1);
								if (wartosc > best)
								{
									best = wartosc;
									ik = i;
									jk = j;
									ik1 = i1;
									jk1 = j1;
								}
							}
							else if (gracz_czy_komputer == 1)
							{
								int wartosc = minimax(warstwa - 1, 0);
								if (wartosc < best)
									best = wartosc;
							}

							tab[i][j] = znak;
							tab[i1][j1] = 'O';
						}
					}
				}
			}
		}

		return best;

	}
}
