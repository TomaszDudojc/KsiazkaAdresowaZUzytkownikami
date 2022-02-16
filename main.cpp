#include <iostream>
#include <windows.h>
#include<algorithm>
#include <fstream>
#include <vector>
#include <conio.h>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika=0;
    string nazwa, haslo;
};

vector <string> podzielLinijkeNaPojedynczeDane(string linijkaWszystkichDanych)
{
    vector <string> pojedynczeDane;
    string dana = "";

    for (int pozycjaWyrazu = 0; pozycjaWyrazu <= linijkaWszystkichDanych.size(); pozycjaWyrazu++)
    {
        if (linijkaWszystkichDanych[pozycjaWyrazu] != '|' )
        {
            dana += linijkaWszystkichDanych[pozycjaWyrazu];
        }
        else
        {
            pojedynczeDane.push_back(dana);
            dana = "";
        }
    }
    return pojedynczeDane;
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik>&uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwa, haslo;
    int idUzytkownika=0;
    vector <string> pojedynczeDaneUzytkownika;
    string linia;
    string linijkaWszystkichDanychUzytkownika;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,linia))
        {
            linijkaWszystkichDanychUzytkownika=linia;
            pojedynczeDaneUzytkownika=podzielLinijkeNaPojedynczeDane(linijkaWszystkichDanychUzytkownika);

            uzytkownik.idUzytkownika = atoi(pojedynczeDaneUzytkownika[0].c_str());
            uzytkownik.nazwa = pojedynczeDaneUzytkownika[1];
            uzytkownik.haslo = pojedynczeDaneUzytkownika[2];

            uzytkownicy.push_back(uzytkownik);
        }
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }
}

string zamienPierwszaLitereNaDuzaPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void rejestracja(vector<Uzytkownik>&uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwa, haslo;
    int idUzytkownika=0;

    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;
    nazwa=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwa);

    int i=0;
    while (i<uzytkownicy.size())
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>nazwa;
            nazwa=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwa);
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj haslo: ";
    cin>> haslo;

    if(uzytkownicy.size()==0)
    {
        idUzytkownika=1;
    }
    else
    {
        idUzytkownika=uzytkownicy[uzytkownicy.size()-1].idUzytkownika+1;
    }

    uzytkownik.nazwa = nazwa;
    uzytkownik.haslo = haslo;
    uzytkownik.idUzytkownika = idUzytkownika;
    uzytkownicy.push_back(uzytkownik);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik<<idUzytkownika<<"|"<<nazwa<<"|"<<haslo<<"|"<<endl;
        plik.close();

        cout<<"Konto zalozone"<<endl;
        Sleep(1000);
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"Uytkownicy.txt\""<<endl;
    }
}

int logowanie(vector <Uzytkownik>&uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj nazwe: ";
    cin>>nazwa;
    nazwa=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwa);
    int i=0;

    while (i<uzytkownicy.size())
    {
        if(uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby=0; proby<3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                cin>>haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie "<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;
}

struct Adresat
{
    int idAdresata=0, idZalogowanegoUzytkownika=0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};

int wczytajAdresatowZPliku(vector<Adresat>&adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idAdresata=0;
    vector <string> pojedynczeDaneAdresata;
    string linia;
    string linijkaWszystkichDanychAdresata;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (plik.good())
    {
        while(getline(plik,linia))
        {
            linijkaWszystkichDanychAdresata=linia;
            pojedynczeDaneAdresata=podzielLinijkeNaPojedynczeDane(linijkaWszystkichDanychAdresata);

            adresat.idAdresata = atoi(pojedynczeDaneAdresata[0].c_str());
            adresat.idZalogowanegoUzytkownika = atoi(pojedynczeDaneAdresata[1].c_str());
            adresat.imie = pojedynczeDaneAdresata[2];
            adresat.nazwisko = pojedynczeDaneAdresata[3];
            adresat.numerTelefonu = pojedynczeDaneAdresata[4];
            adresat.email = pojedynczeDaneAdresata[5];
            adresat.adres = pojedynczeDaneAdresata[6];
            if (adresat.idZalogowanegoUzytkownika == idZalogowanegoUzytkownika)
                adresaci.push_back(adresat);
        }
        plik.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
}

int sprawdzIloscWszystkichAdresatow()
{
    int iloscLinii=0;
    int iloscWszystkichAdresatow=0;
    string linia;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good())
    {
        while(getline(plik, linia))
        {
            iloscLinii++;
        }
        iloscWszystkichAdresatow=iloscLinii;
        plik.close();
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\""<<endl;
    }
    return iloscWszystkichAdresatow;
}

int sprawdzIdOstatniegoAdresata()
{
    int idOstatniegoAdresata;
    int iloscWszystkichAdresatow=sprawdzIloscWszystkichAdresatow();

    if(iloscWszystkichAdresatow==0)
    {
        idOstatniegoAdresata=0;
    }
    else
    {
        string linia;
        fstream plik;
        plik.open("KsiazkaAdresowa.txt", ios::in);
        if (plik.good())
        {
            for (int nrLinii=1; nrLinii<=iloscWszystkichAdresatow; nrLinii++)
            {
                if (nrLinii==iloscWszystkichAdresatow)
                {
                    getline(plik,linia,'|');
                    idOstatniegoAdresata=atoi(linia.c_str());
                }
                else
                {
                    getline(plik,linia);
                }
            }
            plik.close();
        }
        else
        {
            cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\""<<endl;
        }
    }
    return idOstatniegoAdresata;
}
void dodajAdresata(vector<Adresat>&adresaci, int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idAdresata=0;
    int iloscWszystkichAdresatow=sprawdzIloscWszystkichAdresatow();

    if(iloscWszystkichAdresatow==0)
    {
        idAdresata=1;
    }
    else
    {
        idAdresata=sprawdzIdOstatniegoAdresata()+1;
    }

    cout<<"Podaj imie i nazwisko adresta: ";
    cin>>imie>>nazwisko;
    imie=zamienPierwszaLitereNaDuzaPozostaleNaMale(imie);
    nazwisko=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwisko);

    int i=0;
    while (i<adresaci.size())
    {
        if(adresaci[i].imie == imie && adresaci[i].nazwisko == nazwisko)
        {
            cout<<"Taka osoba jest juz zapisana. Wpisz inne imie i nazwisko: ";
            cin>>imie>>nazwisko;
            i=0;
        }
        else
        {
            i++;
        }
    }

    cout<<"Podaj nr telefonu: ";
    cin.sync(); // oprozniam bufor
    getline(cin, numerTelefonu);
    cout<<"Podaj email: ";
    cin>>email;
    cout<<"Podaj adres: ";
    cin.sync(); // oprozniam bufor
    getline(cin, adres);

    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;
    adresat.idAdresata = idAdresata;
    adresat.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;

    adresaci.push_back(adresat);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good())
    {
        plik<<idAdresata<<"|"<<idZalogowanegoUzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<numerTelefonu<<"|"<<email<<"|"<<adres<<"|"<<endl;
        plik.close();

        cout<<"Adresat zapisany do ksiazki adresowej"<<endl;
        Sleep(1000);
    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\""<<endl;
    }
}

void wypiszAdresatow(vector<Adresat>&adresaci, int i)
{
    cout<<"id: "<<adresaci[i].idAdresata<<"|imie: "<<adresaci[i].imie<<"|nazwisko: "<<adresaci[i].nazwisko<<"|tel.: "<<adresaci[i].numerTelefonu<<"|email: "<<adresaci[i].email<<"|adres: "<<adresaci[i].adres<<"|"<<endl;
}

bool sprawdzCzyImieWystepujeWKsiazce (vector<Adresat>&adresaci, string imie)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].imie == imie)
            istnieje=true;
    }
    return istnieje;
}

void wyszukajPoImieniu(vector<Adresat>&adresaci)
{
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        string imie;
        cout<<"Podaj szukane imie: ";
        cin>>imie;
        imie=zamienPierwszaLitereNaDuzaPozostaleNaMale(imie);

        if(sprawdzCzyImieWystepujeWKsiazce (adresaci, imie)==true)
        {
            for (int i=0; i<adresaci.size(); i++)
            {
                if(adresaci[i].imie == imie)
                {
                    wypiszAdresatow(adresaci, i);
                }
            }
        }
        else cout<<"Brak osob o imieniu \""<<imie<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

bool sprawdzCzyNazwiskoWystepujeWKsiazce (vector<Adresat>&adresaci, string nazwisko)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].nazwisko == nazwisko)
            istnieje=true;
    }
    return istnieje;
}

void wyszukajPoNazwisku(vector<Adresat>&adresaci)
{
    if (adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        string nazwisko;
        cout<<"Podaj szukane nazwisko: ";
        cin>>nazwisko;
        nazwisko=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwisko);

        if(sprawdzCzyNazwiskoWystepujeWKsiazce (adresaci, nazwisko)==true)
        {

            for (int i=0; i<adresaci.size(); i++)
            {
                if(adresaci[i].nazwisko == nazwisko)
                {
                    wypiszAdresatow(adresaci, i);
                }
            }
        }
        else cout<<"Brak osob o nazwisku \""<<nazwisko<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

void wypiszWszystkichAdresatow(vector<Adresat>&adresaci)
{
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        cout<<"Wszyscy adresaci ("<<adresaci.size()<<") z ksiazki adresowej: "<<endl<<endl;
        for (int i=0; i<adresaci.size(); i++)

        {
            wypiszAdresatow(adresaci,i);
        }
        system("pause");
    }
}

bool sprawdzCzyIdWystepujeWKsiazce (vector<Adresat>&adresaci, int idAdresata)
{
    bool istnieje=false;

    for (int i=0; i<adresaci.size(); i++)
    {
        if(adresaci[i].idAdresata == idAdresata)
            istnieje=true;
    }
    return istnieje;
}

void zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoUsunieciu (vector<Adresat>&adresaci, int idAdresata)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idZalogowanegoUzytkownika;
    vector <string> pojedynczeDaneAdresata;
    string linia;
    string linijkaWszystkichDanychAdresata;

    fstream plikOryginalny, plikTymczasowy;
    plikOryginalny.open("KsiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("KsiazkaAdresowa_tymczasowy.txt", ios::out);
    if (plikOryginalny.good())
    {
        while(getline(plikOryginalny,linia))
        {
            linijkaWszystkichDanychAdresata=linia;
            pojedynczeDaneAdresata=podzielLinijkeNaPojedynczeDane(linijkaWszystkichDanychAdresata);

            adresat.idAdresata = atoi(pojedynczeDaneAdresata[0].c_str());
            adresat.idZalogowanegoUzytkownika = atoi(pojedynczeDaneAdresata[1].c_str());
            adresat.imie = pojedynczeDaneAdresata[2];
            adresat.nazwisko = pojedynczeDaneAdresata[3];
            adresat.numerTelefonu = pojedynczeDaneAdresata[4];
            adresat.email = pojedynczeDaneAdresata[5];
            adresat.adres = pojedynczeDaneAdresata[6];

            if (plikTymczasowy.good())
            {
                if (adresat.idAdresata != idAdresata)
                {
                    plikTymczasowy<<adresat.idAdresata<<"|"<<adresat.idZalogowanegoUzytkownika<<"|"<<adresat.imie<<"|"<<adresat.nazwisko<<"|"<<adresat.numerTelefonu<<"|"<<adresat.email<<"|"<<adresat.adres<<"|"<<endl;
                }
            }
            else
            {
                cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa_tymczasowy.txt\""<<endl;
            }
        }
        plikOryginalny.close();
        plikTymczasowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\"" << endl;
    }
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowa_tymczasowy.txt", "KsiazkaAdresowa.txt");
}

void zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji (vector<Adresat>&adresaci, int i, int idAdresata)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idZalogowanegoUzytkownika;
    vector <string> pojedynczeDaneAdresata;
    string linia;
    string linijkaWszystkichDanychAdresata;

    fstream plikOryginalny, plikTymczasowy;
    plikOryginalny.open("KsiazkaAdresowa.txt", ios::in);
    plikTymczasowy.open("KsiazkaAdresowa_tymczasowy.txt", ios::out);
    if (plikOryginalny.good())
    {
        while(getline(plikOryginalny,linia))
        {
            linijkaWszystkichDanychAdresata=linia;
            pojedynczeDaneAdresata=podzielLinijkeNaPojedynczeDane(linijkaWszystkichDanychAdresata);

            adresat.idAdresata = atoi(pojedynczeDaneAdresata[0].c_str());
            adresat.idZalogowanegoUzytkownika = atoi(pojedynczeDaneAdresata[1].c_str());
            adresat.imie = pojedynczeDaneAdresata[2];
            adresat.nazwisko = pojedynczeDaneAdresata[3];
            adresat.numerTelefonu = pojedynczeDaneAdresata[4];
            adresat.email = pojedynczeDaneAdresata[5];
            adresat.adres = pojedynczeDaneAdresata[6];

            if (plikTymczasowy.good())
            {
                if (adresat.idAdresata != idAdresata)
                {
                    plikTymczasowy<<adresat.idAdresata<<"|"<<adresat.idZalogowanegoUzytkownika<<"|"<<adresat.imie<<"|"<<adresat.nazwisko<<"|"<<adresat.numerTelefonu<<"|"<<adresat.email<<"|"<<adresat.adres<<"|"<<endl;
                }
                else
                {
                    plikTymczasowy<<adresaci[i].idAdresata<<"|"<<adresaci[i].idZalogowanegoUzytkownika<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu<<"|"<<adresaci[i].email<<"|"<<adresaci[i].adres<<"|"<<endl;
                }
            }
            else
            {
                cout<<"Nie mozna otworzyc pliku: \"KsiazkaAdresowa_tymczasowy.txt\""<<endl;
            }
        }
        plikOryginalny.close();
        plikTymczasowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: \"KsiazkaAdresowa.txt\"" << endl;
    }
    remove ("KsiazkaAdresowa.txt");
    rename ("KsiazkaAdresowa_tymczasowy.txt", "KsiazkaAdresowa.txt");
}

void usunAdresata(vector<Adresat>&adresaci)
{
    int idAdresata;
    char znak;
    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        system("cls");
        cout<<"Wybierz z ponizszej listy id adresata, ktorego chcesz usunac z ksiazki adresowej: "<<endl<<endl;
        wypiszWszystkichAdresatow(adresaci);
        cin>>idAdresata;

        if(sprawdzCzyIdWystepujeWKsiazce (adresaci, idAdresata)==true)
        {
            for (auto it= adresaci.begin(); it != adresaci.end(); it++)
            {
                if(it->idAdresata==idAdresata)
                {
                    cout<<"Jesli jestes pewny, ze chcesz usunac adresata o id \""<<idAdresata<<"\", wcisnij \"t\""<<endl;

                    znak = getch();

                    if (znak == 't')
                    {
                        cout<<"Adresat o id \""<<idAdresata<<"\" zostal usuniety z ksiazki adresowej"<<endl;
                        Sleep(2000);
                        adresaci.erase(it);
                        zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoUsunieciu(adresaci, idAdresata);
                        break;
                    }
                }
            }
        }
        else cout<<"Brak osob o id \""<<idAdresata<<"\" w ksiazce adresowej!"<<endl;
        system("pause");
    }
}

void edytujAdresata(vector<Adresat>&adresaci,int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    int idAdresata=0;
    char wybor;

    if(adresaci.size()==0)
    {
        cout<<"Ksiazka adresowa jest pusta!"<<endl;
        system("pause");
    }
    else
    {
        while(true)
        {
            system("cls");
            int idAdresata;

            cout<<"Wybierz z ponizszej listy id adresata, ktorego dane chcesz edytowac: "<<endl<<endl;
            wypiszWszystkichAdresatow(adresaci);
            cin>>idAdresata;
            system("cls");

            if(sprawdzCzyIdWystepujeWKsiazce (adresaci, idAdresata)==true)
            {
                for (int i=0; i<adresaci.size(); i++)
                {
                    if(adresaci[i].idAdresata == idAdresata)
                    {
                        cout<<"Jakie dane adresata:"<<endl;
                        wypiszAdresatow(adresaci, i);
                        cout<<"chcesz edytowac?"<<endl<<endl;
                        cout<<"1 - imie"<<endl;
                        cout<<"2 - nazwisko"<<endl;
                        cout<<"3 - numer telefonu"<<endl;
                        cout<<"4 - email"<<endl;
                        cout<<"5 - adres"<<endl;
                        cout<<"6 - powrot do menu"<<endl;
                        cout<<endl<<"Twoj wybor: ";
                        cin>>wybor;
                        cout<<endl;

                        if (wybor=='1')
                        {
                            string imie;
                            cout<<"Wpisz nowe imie: ";
                            cin>>imie;
                            imie=zamienPierwszaLitereNaDuzaPozostaleNaMale(imie);
                            adresaci[i].imie = imie;
                            zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji(adresaci, i, idAdresata);
                            cout<<"Imie zostalo zmienione na: \""<<imie<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='2')
                        {
                            string nazwisko;
                            cout<<"Wpisz nowe nazwisko: ";
                            cin>>nazwisko;
                            nazwisko=zamienPierwszaLitereNaDuzaPozostaleNaMale(nazwisko);
                            adresaci[i].nazwisko = nazwisko;
                            zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji(adresaci,i, idAdresata);
                            cout<<"nazwisko zostalo zmienione na: \""<<nazwisko<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='3')
                        {
                            string numerTelefonu;
                            cout<<"Wpisz nowy numer telefonu: ";
                            cin.sync(); // oprozniam bufor
                            getline(cin, numerTelefonu);
                            adresaci[i].numerTelefonu = numerTelefonu;
                            zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji(adresaci,i, idAdresata);
                            cout<<"Numer telefonu zostal zmieniony na: \""<<numerTelefonu<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='4')
                        {
                            string email;
                            cout<<"Wpisz nowy adres email: ";
                            cin>>email;
                            adresaci[i].email = email;
                            zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji(adresaci,i, idAdresata);
                            cout<<"Adres email zostal zmieniony na: \""<<email<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='5')
                        {
                            string adres;
                            cout<<"Wpisz nowy adres: ";
                            cin.sync(); // oprozniam bufor
                            getline(cin, adres);
                            adresaci[i].adres = adres;
                            zapiszZmienioneDaneDoPlikuKsiazkaAdresowaPoEdycji(adresaci,i, idAdresata);
                            cout<<"Adres zostal zmieniony na: \""<<adres<<"\""<<endl;
                            Sleep(1500);
                            return;
                        }
                        else if (wybor=='6')
                        {
                            return;
                        }
                    }
                }
            }
            else cout<<"Brak osob o id \""<<idAdresata<<"\" w ksiazce adresowej!"<<endl;
            system("pause");
        }
    }
}

void zapiszZmienioneDaneDoPlikuUzytkownicy (vector<Uzytkownik>&uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwa, haslo;
    int idUzytkownika=0;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);

    if (plik.good())
    {
        for (int i=0; i<uzytkownicy.size(); i++)
        {
            plik<<uzytkownicy[i].idUzytkownika<<"|"<<uzytkownicy[i].nazwa<<"|"<<uzytkownicy[i].haslo<<"|"<<endl;
        }
        plik.close();

    }
    else
    {
        cout<<"Nie mozna otworzyc pliku: \"Uytkownicy.txt\""<<endl;
    }
}

void zmienHaslo(vector <Uzytkownik>&uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
            uzytkownicy[i].haslo= haslo;
        zapiszZmienioneDaneDoPlikuUzytkownicy (uzytkownicy);
    }
    cout<<"Haslo zostalo zmienione"<<endl;
    Sleep(1500);
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika;
    char wybor;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while(true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cout<<endl<<"Twoj wybor: ";
            cin>>wybor;
            cout<<endl;

            if (wybor=='1')
            {
                rejestracja(uzytkownicy);
            }
            else if (wybor=='2')
            {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy);
            }
            else if (wybor=='9')
            {
                exit(0);
            }
        }
        else
        {
            vector <Adresat> adresaci;
            wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);

            while(true)
            {
                system("cls");
                cout<<"1. Dodaj adresata"<<endl;
                cout<<"2. Wyszukaj po imieniu"<<endl;
                cout<<"3. Wyszukaj po nazwisku"<<endl;
                cout<<"4. Wyswietl wszystkich adresatow"<<endl;
                cout<<"5. Usun adresata"<<endl;
                cout<<"6. Edyduj adresata"<<endl;
                cout<<"7. Zmien haslo"<<endl;
                cout<<"8. Wyloguj sie"<<endl;
                cout<<endl<<"Twoj wybor: ";
                cin>>wybor;
                cout<<endl;

                if (wybor=='1')
                {
                    dodajAdresata(adresaci, idZalogowanegoUzytkownika);
                }
                else if (wybor=='2')
                {
                    wyszukajPoImieniu(adresaci);
                }
                else if (wybor=='3')
                {
                    wyszukajPoNazwisku(adresaci);            ;
                }
                else if (wybor=='4')
                {
                    wypiszWszystkichAdresatow(adresaci);
                }
                else if (wybor=='5')
                {
                    usunAdresata(adresaci);
                }
                else if (wybor=='6')
                {
                    edytujAdresata(adresaci,idZalogowanegoUzytkownika);
                }
                else if (wybor=='7')
                {
                    zmienHaslo(uzytkownicy,idZalogowanegoUzytkownika);
                }
                else if (wybor=='8')
                {
                    idZalogowanegoUzytkownika = 0;
                    break;
                }
            }
        }
    }
    return 0;
}

