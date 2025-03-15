#pragma once
#define BUFFER 100
struct CKartaBankowa {
    long numer;
    char nazwaBanku[BUFFER];
    unsigned long saldo;
};

struct COsoba {
	char plec; //M - mê¿czyzna, K - kobieta
    size_t pesel;
	char data_urodzenia[BUFFER]; //dd.mm.rrrr
	char godnosc[BUFFER]; //np. Pan/Pani + nazwisko
    CKartaBankowa* visa;
    CKartaBankowa* mastercard;
};