
#include <iostream>
#include <clocale>
#include "Finanse.h"

/*
* TEMAT: Struktury, przeładowanie funkcji, referencja jako argument, zarządzanie pamięcią za pomocą operatorów new oraz delete.
* W zadaniu należy stworzyć program, który będzie zarządzał rodziną. Rodzina składa się z osób, które posiadają karty bankowe.

- Program wynikowy należy wgrać do Teams w formie pliku zip, w którym mają się znaleść tylko pliki z kodem źródłowym.

**** Ocena 5.0 ****
- Jeśli zostały zrealizowane punkty 1-12 na zajęciu, wtedy plik zip nazwij: Laboratorium_1.zip. 
- Po uzupełnieniu programu o punkty 13-15, nazwij plik zip: Laboratorium_1_Dom.zip i wgraj również do Teams
  przed kolejnym zajęciem laboratoryjnym.

**** Ocena 4.0 - 4.5 ****
- Jeśli nie udało się w czasie laboratoriów zrealizować punktów 1-12, wtedy plik zip nazwij: Laboratorium_1_v1.zip i wgraj do Teams
przed ukończeniem zajęcia laboratoryjnego. 
Dopracowany program z punktami 13-15 wgraj do Teams przed kolejnym zajęciem laboratoryjnym, plik zip nazwij: Laboratorium_1_v2.zip
Wysokość oceny zależy od stopnia realizacji punktów 1-12 w pliku Laboratorium_1_v1.zip.

**** Ocena 3.0 - 3.5 ****
- Jeśli wynikowy program zostanie wgrany do Teams w terminie 2 tygodni po zajęciu laboratoryjnym, lecz przed zajęciem nim,
wtedy plik zip nazwij: Laboratorium_1_v3.zip. Wysokość oceny zależy od stopnia realizacji punktów 1-12 w pliku Laboratorium_1_v1.zip.

**** Ocena 2.0 ****
- Jeśli został pzrekroczony termin wgrywania jak na ocenę 3.0 - 3.5, wtedy plik zip nazwij: Laboratorium_1_v4.zip.

**** Ocena 0.0 ****
- Jeśli wcale nie zostanie wgrany plik zip do Teams z programem, wtedy ocena 0.0.

Program powinien dokładnie realizować poniższe założenia:

// ------------------------------- to co pokrywa wykład ------------------------------
!!!1. Wylosuj liczbę osób w rodzinie (od 2 do 10 osób).
2. Dla każdej osoby wylosuj pleć, nazwisko i stwórz godnosć. Jeśli osoba jest mężczyzną, to godność to Pan, w przeciwnym wypadku Pani.
!!!3. Nazwiska losuj z listy: Kowalski, Nowak, Wiśniewski, Dąbrowski, Lewandowski, Wójcik, Kamiński, Kowalczyk, Zieliński, Szymański.
!!!4. Dla każdej osoby wylosuj datę urodzenia w formacie dd.mm.rrrr.
!!!5. Dla każdej osoby wylosuj numer PESEL.
!!!6. Dla każdej osoby wylosuj i stwórz od 2 do 4 kart bankowych. Dla każdej karty bankowej wylosuj numer, nazwę banku i saldo.
!!!7. Tworzenie danych zrealizuj za pomocą funkcji przeładowanych stworz(...) (wzoruj się przykładem z wykładu).
!!!8. Uwzględnij w programie mechanizm zarządzania pamięcią. Dodawaj/Usuwaj członków rodziny albo/i karty za pomocą przeładowanych
funkcji dodawania/usuwania.
!!!9. Wyświetl dane wszystkich członków rodziny za pomocą przeładowanych funkcji print(...) : print dla osoby oraz print() dla karty.
// ------------------------------- nowa funkcjonalność ------------------------------
10.Uwzględnij opcję zmiany właściciela karty. Wylosuj nowego właściciela i przesuń kartę do jego danych.
11.Uwzględnij opcję kopiowania karty, wówczas tą samą kartą może korzystać kilka osób. 
12.Uwzględnij opcję dokonania zakupu o losowej kwocie. Zakup dokonaj na losowej karcie losowego członka rodziny albo kartach,
jeśli saldo nie jest wystarczające.
// ------------------------------- praca domowa ------------------------------
13.Uwzględnij opcję wyświetlania danych wszystkich członków rodziny, którzy mają saldo na koncie większe niż ... (podaj wartość z klawiatury).
14.Uwzględnij opcję wyświetlania danych wszystkich członków rodziny, którzy mają kartę w banku ... (podaj nazwę banku z klawiatury).
15.Uwzględnij opcję realizacji przelewu z karty na kartę (wylosuj numery kart źródłowej i docelowej oraz kwotę przelewu).
*/

int losujLiczbe(int min, int max) {
    return min + rand() % (max - min + 1);
}

const char* wylosujNazwisko() {
    static const char* nazwiska[] = { "Kowalski", "Nowak", "Wiśniewski", "Dąbrowski", "Lewandowski",
                        "Wójcik", "Kamiński", "Kowalczyk", "Zieliński", "Szymański" };
    int wylosowanaLiczba = losujLiczbe(0, sizeof(nazwiska) / sizeof(nazwiska[0]) - 1);

    return nazwiska[wylosowanaLiczba];
}

void wylosujGodnosc(char* data, size_t rozmiar) {
    bool isPani = losujLiczbe(0, 1);
    const char* nazwisko = wylosujNazwisko();
    snprintf(data, rozmiar, "%s %s", isPani ? "Pani" : "Pan", nazwisko);
}

void wylosujNazweBanku(char* data, size_t rozmiar) {
    static const char* nazwy[] = { "PKO", "mBank", "CityBank" };
    int wylosowanaLiczba = losujLiczbe(0, sizeof(nazwy) / sizeof(nazwy[0]) - 1);

    snprintf(data, rozmiar, "%s", nazwy[wylosowanaLiczba]);
}

void wylosujDateUrodzenia(char* data, size_t rozmiar) {
    int dzien = losujLiczbe(1, 29);
    int miesiac = losujLiczbe(1, 12);
    int rok = losujLiczbe(1950, 2005);

    snprintf(data, rozmiar, "%02d.%02d.%04d", dzien, miesiac, rok);
}

void zmienWlasciela(COsoba& osoba, COsoba& nowyWlasciciel) {
    osoba.godnosc = nowyWlasciciel.godnosc;
    osoba.data_urodzenia = nowyWlasciciel.data_urodzenia;
    osoba.pesel = nowyWlasciciel.pesel;
}

void stworz(COsoba**& osoby, const size_t rozmiar) {
    osoby = new COsoba * [rozmiar];
    for (size_t ind = 0; ind < rozmiar; ind++) {
        osoby[ind] = new COsoba;
    }
}

void stworz(COsoba& osoba) {
    wylosujDateUrodzenia(osoba.data_urodzenia, BUFFER);
    osoba.pesel = losujLiczbe(10000000, 99999999);
    osoba.plec = losujLiczbe(0, 1);
    wylosujGodnosc(osoba.godnosc, BUFFER);
    // todo: wylosowac karte
}

void stworz(CKartaBankowa& karta) {
    karta.numer = losujLiczbe(10000000, 99999999);
    wylosujNazweBanku(karta.nazwaBanku, BUFFER);
    karta.saldo = losujLiczbe(10, 50000);
}

void usun(COsoba*& osoba) {
    delete osoba;
    osoba = nullptr;
}

void usun(COsoba**& rodzina) {
    delete[] rodzina; // to jest array pointerow, wiec musze usunac kazdy pointer oddzielnie w loopie
    rodzina = nullptr;
}

void usun(CKartaBankowa*& karta) {
    delete karta;
    karta = nullptr;
}

void print(const COsoba& osoba) {
    std::cout << std::endl << "Godność osoby : " << osoba.godnosc;
    std::cout << std::endl << "PESEL         : " << osoba.pesel;
    std::cout << std::endl << "Data Urodzenia: " << osoba.data_urodzenia;
    std::cout << std::endl;
}

void print(COsoba** rodzina, const size_t rozmiar) {
    std::cout << "===OSOBY===" << std::endl;
    for (size_t ind = 0; ind < rozmiar; ind++) {
        print(*rodzina[ind]);
    }
}

void init(COsoba**& rodzina) {
    int rozmiarRodziny = losujLiczbe(2, 6);
    stworz(rodzina, rozmiarRodziny);
    // dodac losowe osoby do rodziny
}

int main() {
    setlocale(LC_CTYPE, "Polish");
    size_t choice{};
    COsoba** rodzina{ nullptr };

    do {
        std::cout << "Menu\n\n";
        std::cout << "1. Stwórz rodzinę" << std::endl;
        std::cout << "2. Pokaż rodzinę" << std::endl;
        // ... .... ... ... ... ... ... .. .. . ..  . .
        std::cout << "0. Exit" << std::endl;
        std::cout << "Wybież opcję : ";
        std::cin >> choice;
        switch (choice) {
        case 1:
			if (rodzina == nullptr) {
                init(rodzina);
                //stworz();
			}
            else {
                std::cout << "Już określiłeś się z rodziną" << std::endl;
            }
            system("pause");
            system("cls");
            break;
        case 2:
            print(rodzina, BUFFER); // todo: do naprawy, dodac rozmiar rodziny (jak?)
            system("pause");
            system("cls");
            break;

    	// ... ... ... ... ... ... ... ... ...  ...
        case 0:
            if (rodzina != nullptr)
                usun(rodzina);
            if (rodzina == nullptr)
                std::cout << "Baza jest pusta !" << std::endl;
            break;
        default:
            std::cout << "Błędny wybór. Powtórz\n";
        }
    } while (choice != 0);
}
