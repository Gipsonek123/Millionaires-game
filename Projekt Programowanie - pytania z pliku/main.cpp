#include <iostream>
#include <iomanip> // biblioteka s�u��ca do wy�wietlenie tekstu 
#include <Windows.h> // biblioteka s�u��ca do zmiany koloru wy�wietlanego tekstu
#include <string>  // biblioteka, z kt�rej wykorzytuj� funkcje get.line i stoi
#include <fstream> // biblioteka s�u��ca do zapisu/odczytu do/z pliku

using namespace std;

int tab[12]{}; // stworzenie tablicy na wylosowane liczby pyta�
int g = 1; // zmienna g s�u��cy do stwiedzenia czy kto� wygral czy nie 1 - wygrana 0 - przegrana

void Obecna_wygrana(int i, int wygrana) // funcja wypisuje na ekran obecn� wygran�
{
	HANDLE hOut; // uchwyt odpowiedzialny za kolory

	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // uchwyt do wyj�cia konsoli zapami�tujemy w zmiennej hOut

	if (i >= 0)
	{
		if (i == 1)
		{
			cout << "----------" << endl;
		}

		else if (i == 2)
		{
			cout << setw(57) << "--------------------------------------" << endl;
			cout << setw(50) << "| Twoja obecna wygrana wynosi: " << wygrana << "z� |" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED); // ustawienie koloru
			cout << "----------";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << setw(47) << "--------------------------------------" << endl;
		}
		else if (i > 2 && i < 6)
		{
			cout << setw(58) << "---------------------------------------" << endl;
			cout << setw(50) << "| Twoja obecna wygrana wynosi: " << wygrana << "z� |" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << "----------";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << setw(48) << "---------------------------------------" << endl;
		}
		else if (i > 5 && i < 10)
		{
			cout << setw(59) << "----------------------------------------" << endl;
			cout << setw(50) << "| Twoja obecna wygrana wynosi: " << wygrana << "z� |" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << "----------";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << setw(49) << "----------------------------------------" << endl;
		}
		else
		{
			cout << setw(60) << "-----------------------------------------" << endl;
			cout << setw(50) << "| Twoja obecna wygrana wynosi: " << wygrana << "z� |" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << "-----------";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
			cout << setw(49) << "-----------------------------------------" << endl;
		}

	}
}

void Wpisanie_wyniku_do_pliku(string nazwaPliku, string nazwa, int wygrana) // funkcja zapisuje do pliku wynik wraz z nazw� gracza
{
	fstream plik;
	string linia;
	int c = 0;

	plik.open(nazwaPliku, ios::in);
	if (plik.good())
	{
		getline(plik, linia);

		c = linia.length();
	}
	plik.close();


	plik.open(nazwaPliku, ios::app);

	if (plik.good())
	{
		if (c == 0)
		{
			plik << nazwa << " : " << wygrana << "z�";
		}
		else
		{
			plik << endl << nazwa << " : " << wygrana << "z�";
		}

	}
	else
	{
		cout << "B��d otwarcia pliku!";
	}
	plik.close();
}

int Losowanie_pytania(int liczba, int tab[]) // Funkcja losuje liczb� z zakresu 1 - 30 bez powt�rze�
{
	int j = 0;

	srand(time(NULL)); // pobranie czasu 
	liczba = rand() % 30 + 1;

	while (*(tab + j) != 0)
	{
		if (*(tab + j) == liczba)
		{
			srand(time(NULL));
			liczba = rand() % 12 + 1;
			j = 0;
		}
		else
		{
			j++;
		}
	}

	tab[j] = liczba;

	return liczba;

}

void Pytanie_i_opdowiedz(int (*Losowanie_pytania) (int, int*)) // funkcja kt�ra pobiera z pliku pytanie na podstawie wylosowanej liczby, wy�wietla je na ekranie z opdowiedziami
{																// i sprawdza czy odpowied� jest dobra
	HANDLE hOut;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	string odp;
	int i = 0;

	int liczba = Losowanie_pytania(0, tab);

	fstream plik;

	string liczb;
	string liczb1;
	string linia0;
	string linia;
	string linia1;
	string linia2;
	int numer = 0;
	int r = 0;
	plik.open("Pytania.txt", ios::in);

	if (plik.good()) // pobieranie pytania z pliku
	{
		while (true)
		{


			if (liczba < 10)
			{
				getline(plik, linia0);
				liczb = linia0[0];
				numer = stoi(liczb);
				getline(plik, linia2);
				if (numer == liczba)
				{
					linia1 = linia0.erase(0, 2);
					break;
				}
			}
			else
			{
				if (r == 0)
				{
					for (int i = 0; i < 18; i++)
					{
						getline(plik, linia);
					}
				}
				getline(plik, linia0);
				liczb = linia0[0];
				liczb += linia0[1];
				numer = stoi(liczb);
				getline(plik, linia2);
				if (numer == liczba)
				{
					linia1 = linia0.erase(0, 3);
					break;
				}
			}
			r++;
		}
	}
	else
	{
		cout << "B��d otwarcia pliku!";
	}

	plik.close();

	switch (liczba) // switch kt�ry na podstawie wylosowanej liczby wypisuje na ekran pytanie i odpowiedzi, odpowidnio formatuje grafik� w zale�no�ci od pytania, sprawdza czy odpowied� jest dobra
	{
	case 1:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY); // ustawnie koloru
		cout << "-----------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);// ustawnie koloru
		cout << linia2 << endl;
		cout << "-----------------------------------" << endl;

		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------" << endl;
			g = 0;
		}

		Sleep(3000); // program czeka 3 sekundu
		system("cls"); // czyszczenie ekranu
		break;


	case 2:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 3:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 4:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 5:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 6:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 7:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 8:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "--------------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "--------------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 9:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 10:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 11:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "--------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "--------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "--------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;


	case 12:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 13:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 14:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 15:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "----------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "----------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "----------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "----------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "----------------------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 16:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "--------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "--------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "--------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "--------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "--------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "--------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 17:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 18:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "----------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "----------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "----------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "----------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "----------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "----------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "----------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 19:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "--------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "--------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "--------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "--------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "--------------------------------------------------------------------" << endl;
			g = 0;
		}
		Sleep(3000);
		system("cls");
		break;

	case 20:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 21:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 22:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-------------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 23:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 24:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 25:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "B" || odp == "b")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 26:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "---------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "---------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "---------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "---------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "---------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "---------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "---------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 27:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "------------------------------------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 28:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "A" || odp == "a")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 29:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-----------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-----------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-----------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "D" || odp == "d")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-----------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-----------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-----------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-----------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;

	case 30:
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "-------------------------------------------------------------------------------------" << endl;
		cout << linia1 << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << linia2 << endl;
		cout << "-------------------------------------------------------------------------------------" << endl;
		while (odp != "a" && odp != "A" && odp != "b" && odp != "B" && odp != "c" && odp != "C" && odp != "d" && odp != "D")
		{
			if (i >= 1)
			{
				cout << "Podaj liter� a, b, c lub d" << endl;
			}
			cout << "Podaj odpowied�: ";
			cin >> odp;
			i++;
		}

		i = 0;

		if (odp == "C" || odp == "c")
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << "-------------------------------------------------------------------------------------" << endl;
			cout << "Prawdi�owa odpowied�!" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "-------------------------------------------------------------------------------------" << endl;
			cout << "Niestety b��dna odpowied�." << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;
			g = 0;
		}

		Sleep(3000);
		system("cls");
		break;
	}
}

int main()
{
	string koniec;

	setlocale(LC_CTYPE, "Polish"); // ustawienie polskich znak�w

	while (koniec != "k") // p�tla, kt�ra pozwala po zako�czeniu gry zagra� jeszcze raz albo zako�czy� gr�
	{
		string nazwa;

		string start;

		int wygrana = 0;

		HANDLE hOut;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << setw(23) << "--------------" << endl;
		cout << setw(23) << "| Milionerzy |" << endl;
		cout << setw(23) << "--------------" << endl;

		while (start != "s")
		{
			cout << "--------------------------------" << endl;
			cout << setw(29) << "Aby rozpocz�c gr� klinij s" << endl;
			cout << "--------------------------------" << endl;
			cin >> start;
		}

		int d = 0;
		int dl = 0;
		int l = 0;

		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);
		while (d == 0) // podanie nazwy dop�ki wyst�puje jaki� znak graficzny
		{
			if (l == 0)
			{
				cout << "-------------------" << endl;
				cout << "Podaj swoj� nazw�: " << endl;
				cout << "-------------------" << endl;
			}
			else
			{
				cout << "----------------------------------------------------------------------" << endl;
				cout << "Podaj swoj� nazw� (nazwa musi zawiera� minimum jeden znak graficzny) : " << endl;
				cout << "----------------------------------------------------------------------" << endl;
			}
			cin.ignore();
			getline(cin, nazwa);
			dl = nazwa.length();
			for (int i = 0; i < dl; i++)
			{
				if (nazwa[i] > 32 && nazwa[i] < 127)
				{
					d = 1;
					break;
				}
			}
			l++;
		}

		Sleep(1000);
		system("cls");

		for (int i = 1; i < 13; i++) // p�tla wykonuj�ca si� 12 razy bo w Milionerach jest 12 pyta�
		{

			Obecna_wygrana(i, wygrana);

			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED);

			cout << "Pytanie " << i << ". " << endl;

			Pytanie_i_opdowiedz(Losowanie_pytania);



			if (g == 0) // wypisanie na ekran odpowiedniego komunikatu gdy przegramy
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				if (i == 1)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "-------------------" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "Tw�j wynik to: " << wygrana << "z�" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "-------------------" << endl;
					break;
				}
				else if (i == 2)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "---------------------" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "Tw�j wynik to: " << wygrana << "z�" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "---------------------" << endl;
					break;
				}
				else if (i > 2 && i < 6)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "----------------------" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "Tw�j wynik to: " << wygrana << "z�" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "----------------------" << endl;
					break;
				}
				else if (i > 5 && i < 10)
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "-----------------------" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
					cout << "Tw�j wynik to: " << wygrana << "z�" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "-----------------------" << endl;
					break;
				}
				else
				{
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "------------------------" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);;
					cout << "Tw�j wynik to: " << wygrana << "z�" << endl;
					SetConsoleTextAttribute(hOut, FOREGROUND_RED);
					cout << "------------------------" << endl;
					break;
				}

			}

			if (i >= 1) // obliczanie wygranej
			{
				if (i == 1)
				{
					wygrana = 500;
				}
				else if (i == 4)
				{
					wygrana = 5000;
				}
				else if (i == 8)
				{
					wygrana = 75000;
				}
				else if (i == 9)
				{
					wygrana = 125000;
				}
				else
				{
					wygrana *= 2;
				}

			}

		}


		if (g == 1) // wypisanie odpowiedniego komunikatu gdy komu� uda si� wygra�
		{
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "Uda�o si�. Wygra�e� 1000000z�!!!" << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "--------------------------------" << endl;
		}

		Wpisanie_wyniku_do_pliku("Wyniki.txt", nazwa, wygrana);


		SetConsoleTextAttribute(hOut, FOREGROUND_RED); // ekran ko�cowy, gdy kto� przegra lub wygra, mo�e zagra� jeszcze raz lub zako�czy� gr�
		cout << "-----------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Je�li chcesz zako�czy� gr� naci�nij k" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
		cout << "-----------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Jesli chcesz zagra� jeszcze raz naci�nij dowolny inny znak/znaki" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
		cout << "-----------------------------------------------------------------" << endl;
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cin >> koniec;
		Sleep(2000);
		system("cls");

		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

		g = 1; // ustawienie zmiennej g na 1
		for (int i = 0; i < 12; i++) // wype�nienie tablicy zapisuj�cej numery wylosowanych pyta�
		{
			tab[i] = 0;
		}

	}


}