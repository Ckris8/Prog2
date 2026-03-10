// ========================
//  Direttive del preprocessore
// ========================
#include <iostream>     // libreria standard per input/output
#include <cmath>        // esempio di un'altra libreria

// ========================
//  Macro del preprocessore
// ========================
#define PI 3.14159       // costante macro
#define SQUARE(x) ((x)*(x))  // macro per funzione

// ========================
//  Spazio dei nomi standard
// ========================
using namespace std;

// ========================
//  Variabili e costanti globali
// ========================
const double globalFactor = 2.5;   // costante globale
int globalCounter = 0;             // variabile globale

// ========================
//  Dichiarazioni di funzioni (prototipi)
// ========================
double areaCerchio(double r);      // calcola area del cerchio
void stampaMessaggio();            // stampa un messaggio
int somma(int a, int b);           // funzione somma

// ========================
//  Funzione principale
// ========================
int main() {
    stampaMessaggio();

    double r = 5.0;
    cout << "Area del cerchio di r = " << r << " e': " << areaCerchio(r) << endl;

    cout << "Somma: " << somma(3, 4) << endl;

    cout << "Global factor: " << globalFactor << endl;
    cout << "Global counter: " << globalCounter << endl;

    return 0;
}

// ========================
//  Definizioni delle funzioni
// ========================

// usa PI e SQUARE definite nel preprocessore
double areaCerchio(double r) {
    return PI * SQUARE(r);
}

void stampaMessaggio() {
    cout << "Esempio di struttura di un programma C++" << endl;
    globalCounter++;  // modifica variabile globale
}

int somma(int a, int b) {
    return a + b;
}
