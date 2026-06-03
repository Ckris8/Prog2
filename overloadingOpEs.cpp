//

#include <iostream>

class OraDelGiorno {
    int ore, minuti, secondi;

public:
    OraDelGiorno(int h = 0, int m = 0, int s = 0);

    // ─────────────────────────────────────────
    // ARITMETICI
    // ─────────────────────────────────────────
    OraDelGiorno  operator+ (const OraDelGiorno& altro) const; // ora + ora 
    OraDelGiorno  operator- (const OraDelGiorno& altro) const; // ora - ora

    //passa un secondo parametro come const & per evitare copie in memoria 
    //  const finale consente di non modificare l'oggetto originale di partenza , 
    // ma restituisce un nuovo oggetto per valore

    // ─────────────────────────────────────────
    // ARITMETICI COMPOSTI (assignment)
    // ─────────────────────────────────────────
    OraDelGiorno& operator+=(const OraDelGiorno& altro);
    OraDelGiorno& operator-=(const OraDelGiorno& altro);

    //permette di assegnare e sommare e classi in una
    //non è presente const finale perche il valore di una classe viene modificato


    // ─────────────────────────────────────────
    // INCREMENTO / DECREMENTO
    // ─────────────────────────────────────────
    OraDelGiorno& operator++();    // prefisso ++ora
    OraDelGiorno  operator++(int); // postfisso ora++
    OraDelGiorno& operator--();    // prefisso --ora
    OraDelGiorno  operator--(int); // postfisso ora--

    //per distinguerlo dal prefisso il post fisso ha un parametro int che non viene usato

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
    OraDelGiorno& operator= (const OraDelGiorno& altro);      // copia

    // ─────────────────────────────────────────
    // ACCESSO / INDICIZZAZIONE
    // ─────────────────────────────────────────
    
    //trasforma la classe in array , potendo accedere ai membri singolarmente 

    int  operator[](int indice) const; // 0=ore, 1=min, 2=sec (lettura orario)
    int& operator[](int indice);       // idem in scrittura


    // ─────────────────────────────────────────
    // STREAM (funzioni friend, non membri)
    // ─────────────────────────────────────────
    //permettono stampa a video con cout o scrittura da tastiera
    //friend: funzione non del tipo della classe, ma con friend possiamo permettere al metodo di usare i membri privati della classe

    friend std::ostream& operator<<(std::ostream& os, const OraDelGiorno& ora);
    friend std::istream& operator>>(std::istream& is,       OraDelGiorno& ora);
};