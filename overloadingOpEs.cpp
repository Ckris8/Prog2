#include <iostream>
#include <iomanip>
#include <stdexcept>

class OraDelGiorno {
    int ore, minuti, secondi;

public:
    OraDelGiorno(int h = 0, int m = 0, int s = 0);

    // ─────────────────────────────────────────
    // ARITMETICI
    // ─────────────────────────────────────────
    OraDelGiorno  operator+ (const OraDelGiorno& altro) const; 
    OraDelGiorno  operator- (const OraDelGiorno& altro) const; 

    // ─────────────────────────────────────────
    // ARITMETICI COMPOSTI (assignment)
    // ─────────────────────────────────────────
    OraDelGiorno& operator+=(const OraDelGiorno& altro);
    OraDelGiorno& operator-=(const OraDelGiorno& altro);

    // ─────────────────────────────────────────
    // INCREMENTO / DECREMENTO
    // ─────────────────────────────────────────
    OraDelGiorno& operator++();    // prefisso ++ora
    OraDelGiorno  operator++(int); // postfisso ora++
    OraDelGiorno& operator--();    // prefisso --ora
    OraDelGiorno  operator--(int); // postfisso ora--

    // ─────────────────────────────────────────
    // CONFRONTO
    // ─────────────────────────────────────────
    bool operator==(const OraDelGiorno& altro) const;
    bool operator!=(const OraDelGiorno& altro) const;
    bool operator< (const OraDelGiorno& altro) const;
    bool operator> (const OraDelGiorno& altro) const;
    bool operator<=(const OraDelGiorno& altro) const;
    bool operator>=(const OraDelGiorno& altro) const;

    // ─────────────────────────────────────────
    // ASSEGNAMENTO
    // ─────────────────────────────────────────
    OraDelGiorno& operator= (const OraDelGiorno& altro);      

    // ─────────────────────────────────────────
    // ACCESSO / INDICIZZAZIONE
    // ─────────────────────────────────────────
    int  operator[](int indice) const; 
    int& operator[](int indice);       

    // ─────────────────────────────────────────
    // STREAM (funzioni friend, non membri)
    // ─────────────────────────────────────────
    friend std::ostream& operator<<(std::ostream& os, const OraDelGiorno& ora);
    friend std::istream& operator>>(std::istream& is,       OraDelGiorno& ora);
};

// =====================================================================
// IMPLEMENTAZIONE DEI METODI
// =====================================================================

// Costruttore con normalizzazione
OraDelGiorno::OraDelGiorno(int h, int m, int s) {
    // Trasforma tutto in secondi per semplificare il calcolo dei riporti
    int total_sec = h * 3600 + m * 60 + s;
    
    // Gestione dei tempi negativi (es. se sottraggo 2 ore da 1 ora)
    if (total_sec < 0) {
        total_sec = (total_sec % 86400) + 86400; 
    }
    
    // Limita al ciclo delle 24 ore (86400 secondi in un giorno)
    total_sec %= 86400;

    ore = total_sec / 3600;
    minuti = (total_sec % 3600) / 60;
    secondi = total_sec % 60;
}

// ─────────────────────────────────────────
// ARITMETICI
// ─────────────────────────────────────────
OraDelGiorno OraDelGiorno::operator+(const OraDelGiorno& altro) const {
    // Passo i valori sommati al costruttore, che li normalizzerà in automatico
    return OraDelGiorno(ore + altro.ore, minuti + altro.minuti, secondi + altro.secondi);
}

OraDelGiorno OraDelGiorno::operator-(const OraDelGiorno& altro) const {
    return OraDelGiorno(ore - altro.ore, minuti - altro.minuti, secondi - altro.secondi);
}

// ─────────────────────────────────────────
// ARITMETICI COMPOSTI
// ─────────────────────────────────────────
OraDelGiorno& OraDelGiorno::operator+=(const OraDelGiorno& altro) {
    *this = *this + altro; // Riuso l'operatore + già implementato
    return *this;
}

OraDelGiorno& OraDelGiorno::operator-=(const OraDelGiorno& altro) {
    *this = *this - altro; // Riuso l'operatore - già implementato
    return *this;
}

// ─────────────────────────────────────────
// INCREMENTO / DECREMENTO
// ─────────────────────────────────────────
OraDelGiorno& OraDelGiorno::operator++() { // Prefisso
    *this = *this + OraDelGiorno(0, 0, 1);
    return *this;
}

OraDelGiorno OraDelGiorno::operator++(int) { // Postfisso
    OraDelGiorno temp = *this; // Salvo lo stato attuale
    ++(*this);                 // Incremento usando il prefisso
    return temp;               // Restituisco la copia salvata prima dell'incremento
}

OraDelGiorno& OraDelGiorno::operator--() { // Prefisso
    *this = *this - OraDelGiorno(0, 0, 1);
    return *this;
}

OraDelGiorno OraDelGiorno::operator--(int) { // Postfisso
    OraDelGiorno temp = *this;
    --(*this);
    return temp;
}

// ─────────────────────────────────────────
// CONFRONTO
// ─────────────────────────────────────────
bool OraDelGiorno::operator==(const OraDelGiorno& altro) const {
    return ore == altro.ore && minuti == altro.minuti && secondi == altro.secondi;
}

bool OraDelGiorno::operator!=(const OraDelGiorno& altro) const {
    return !(*this == altro); // Riuso l'operatore == negandolo
}

bool OraDelGiorno::operator<(const OraDelGiorno& altro) const {
    int thisSec = ore * 3600 + minuti * 60 + secondi;
    int altroSec = altro.ore * 3600 + altro.minuti * 60 + altro.secondi;
    return thisSec < altroSec;
}

bool OraDelGiorno::operator>(const OraDelGiorno& altro) const {
    return altro < *this; // Riuso l'operatore < a ruoli invertiti
}

bool OraDelGiorno::operator<=(const OraDelGiorno& altro) const {
    return !(*this > altro);
}

bool OraDelGiorno::operator>=(const OraDelGiorno& altro) const {
    return !(*this < altro);
}

// ─────────────────────────────────────────
// ASSEGNAMENTO
// ─────────────────────────────────────────
OraDelGiorno& OraDelGiorno::operator=(const OraDelGiorno& altro) {
    if (this != &altro) { // Evito l'auto-assegnamento (es. a = a)
        ore = altro.ore;
        minuti = altro.minuti;
        secondi = altro.secondi;
    }
    return *this;
}

// ─────────────────────────────────────────
// ACCESSO / INDICIZZAZIONE
// ─────────────────────────────────────────
int OraDelGiorno::operator[](int indice) const { // Lettura
    if (indice == 0) return ore;
    if (indice == 1) return minuti;
    if (indice == 2) return secondi;
    throw std::out_of_range("Indice non valido. Usare 0, 1 o 2.");
}

int& OraDelGiorno::operator[](int indice) { // Scrittura
    if (indice == 0) return ore;
    if (indice == 1) return minuti;
    if (indice == 2) return secondi;
    throw std::out_of_range("Indice non valido. Usare 0, 1 o 2.");
}

// ─────────────────────────────────────────
// STREAM
// ─────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, const OraDelGiorno& ora) {
    // Formatta la stampa come HH:MM:SS (es. 09:05:01)
    os << std::setfill('0') << std::setw(2) << ora.ore << ":"
       << std::setfill('0') << std::setw(2) << ora.minuti << ":"
       << std::setfill('0') << std::setw(2) << ora.secondi;
    return os;
}

std::istream& operator>>(std::istream& is, OraDelGiorno& ora) {
    int h, m, s;
    char c1, c2;
    // Si aspetta un input formattato come HH:MM:SS
    if (is >> h >> c1 >> m >> c2 >> s) {
        if (c1 == ':' && c2 == ':') {
            ora = OraDelGiorno(h, m, s); // Sfrutto il costruttore per normalizzare
        } else {
            is.setstate(std::ios::failbit); // Segnala un errore nel formato
        }
    }
    return is;
}