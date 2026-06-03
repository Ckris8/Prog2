#include <iostream>

using namespace std;

// ==========================================
// 1. STRUTTURE DATI DI BASE (NODI)
// ==========================================

template <typename T>
struct Nodo {
    T dato;
    Nodo* next;
    Nodo(T val) : dato(val), next(nullptr) {}
};

template <typename T>
struct NodoDoppio {
    T dato;
    NodoDoppio* next;
    NodoDoppio* prev;
    NodoDoppio(T val) : dato(val), next(nullptr), prev(nullptr) {}
    NodoDoppio() : next(nullptr), prev(nullptr) {} // Costruttore di default per la sentinella
};


// ==========================================
// 2. LISTA CONCATENATA SEMPLICE (Interi / Generica)
// ==========================================
template <typename T>
class ListaSemplice {
protected: // Protected così le classi derivate (es. ordinata) possono accedere alla testa
    Nodo<T>* testa;

public:
    ListaSemplice() : testa(nullptr) {}
    virtual ~ListaSemplice() {
        Nodo<T>* temp;
        while (testa != nullptr) {
            temp = testa;
            testa = testa->next;
            delete temp;
        }
    }

    // Inserimento in testa
    virtual void inserisci(T val) {
        Nodo<T>* nuovo = new Nodo<T>(val);
        nuovo->next = testa;
        testa = nuovo;
    }

    virtual void rimuovi(T val) {
        Nodo<T>* corr = testa;
        Nodo<T>* prec = nullptr;
        while (corr != nullptr && corr->dato != val) {
            prec = corr;
            corr = corr->next;
        }
        if (corr == nullptr) return; // Non trovato
        if (prec == nullptr) testa = corr->next; // Era in testa
        else prec->next = corr->next; // Era in mezzo o fine
        delete corr;
    }

    bool ricerca(T val) const {
        Nodo<T>* corr = testa;
        while (corr != nullptr) {
            if (corr->dato == val) return true;
            corr = corr->next;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const ListaSemplice& lista) {
        Nodo<T>* temp = lista.testa;
        while (temp != nullptr) {
            os << temp->dato << " -> ";
            temp = temp->next;
        }
        os << "NULL";
        return os;
    }
};


// ==========================================
// 3. LISTA CONCATENATA ORDINATA
// Eredita dalla Lista Semplice, ma cambia l'inserimento
// ==========================================
template <typename T>
class ListaOrdinata : public ListaSemplice<T> {
public:
    void inserisci(T val) override {
        Nodo<T>* nuovo = new Nodo<T>(val);
        
        // Caso 1: Lista vuota o inserimento in testa
        if (this->testa == nullptr || this->testa->dato >= val) {
            nuovo->next = this->testa;
            this->testa = nuovo;
            return;
        }

        // Caso 2: Inserimento in mezzo o in fondo
        Nodo<T>* corr = this->testa;
        while (corr->next != nullptr && corr->next->dato < val) {
            corr = corr->next;
        }
        nuovo->next = corr->next;
        corr->next = nuovo;
    }
};


// ==========================================
// 4. LISTA DOPPIAMENTE LINKATA
// ==========================================
template <typename T>
class ListaDoppia {
protected:
    NodoDoppio<T>* testa;

public:
    ListaDoppia() : testa(nullptr) {}
    virtual ~ListaDoppia() {
        NodoDoppio<T>* temp;
        while (testa != nullptr) {
            temp = testa;
            testa = testa->next;
            delete temp;
        }
    }

    virtual void inserisci(T val) {
        NodoDoppio<T>* nuovo = new NodoDoppio<T>(val);
        if (testa != nullptr) {
            testa->prev = nuovo;
            nuovo->next = testa;
        }
        testa = nuovo;
    }

    virtual void rimuovi(T val) {
        NodoDoppio<T>* corr = testa;
        while (corr != nullptr && corr->dato != val) {
            corr = corr->next;
        }
        if (corr == nullptr) return; // Non trovato
        
        if (corr->prev != nullptr) corr->prev->next = corr->next;
        else testa = corr->next; // Era la testa
        
        if (corr->next != nullptr) corr->next->prev = corr->prev;
        
        delete corr;
    }

    bool ricerca(T val) const {
        NodoDoppio<T>* corr = testa;
        while (corr != nullptr) {
            if (corr->dato == val) return true;
            corr = corr->next;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const ListaDoppia& lista) {
        NodoDoppio<T>* temp = lista.testa;
        os << "NULL <-> ";
        while (temp != nullptr) {
            os << temp->dato << " <-> ";
            temp = temp->next;
        }
        os << "NULL";
        return os;
    }
};


// ==========================================
// 5. LISTA DOPPIAMENTE LINKATA ORDINATA
// ==========================================
template <typename T>
class ListaDoppiaOrdinata : public ListaDoppia<T> {
public:
    void inserisci(T val) override {
        NodoDoppio<T>* nuovo = new NodoDoppio<T>(val);
        
        if (this->testa == nullptr) {
            this->testa = nuovo;
            return;
        }

        if (this->testa->dato >= val) {
            nuovo->next = this->testa;
            this->testa->prev = nuovo;
            this->testa = nuovo;
            return;
        }

        NodoDoppio<T>* corr = this->testa;
        while (corr->next != nullptr && corr->next->dato < val) {
            corr = corr->next;
        }

        nuovo->next = corr->next;
        nuovo->prev = corr;
        if (corr->next != nullptr) {
            corr->next->prev = nuovo;
        }
        corr->next = nuovo;
    }
};


// ==========================================
// 6. LISTA DOPPIA CIRCOLARE (CON SENTINELLA)
// La sentinella è un nodo "finto" che semplifica le operazioni
// ed evita i controlli sui nullptr.
// ==========================================
template <typename T>
class ListaCircolareSentinella {
private:
    NodoDoppio<T>* sentinella;

public:
    ListaCircolareSentinella() {
        sentinella = new NodoDoppio<T>(); // Nodo fittizio
        sentinella->next = sentinella;
        sentinella->prev = sentinella;
    }

    ~ListaCircolareSentinella() {
        NodoDoppio<T>* corr = sentinella->next;
        while (corr != sentinella) {
            NodoDoppio<T>* temp = corr;
            corr = corr->next;
            delete temp;
        }
        delete sentinella;
    }

    // Inserimento alla fine (prima della sentinella)
    void inserisci(T val) {
        NodoDoppio<T>* nuovo = new NodoDoppio<T>(val);
        NodoDoppio<T>* ultimo = sentinella->prev;

        nuovo->next = sentinella;
        nuovo->prev = ultimo;
        
        ultimo->next = nuovo;
        sentinella->prev = nuovo;
    }

    void rimuovi(T val) {
        NodoDoppio<T>* corr = sentinella->next;
        while (corr != sentinella) {
            if (corr->dato == val) {
                corr->prev->next = corr->next;
                corr->next->prev = corr->prev;
                delete corr;
                return;
            }
            corr = corr->next;
        }
    }

    bool ricerca(T val) const {
        NodoDoppio<T>* corr = sentinella->next;
        while (corr != sentinella) {
            if (corr->dato == val) return true;
            corr = corr->next;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const ListaCircolareSentinella& lista) {
        NodoDoppio<T>* temp = lista.sentinella->next;
        os << "[Sentinella] <-> ";
        while (temp != lista.sentinella) {
            os << temp->dato << " <-> ";
            temp = temp->next;
        }
        os << "[Sentinella]";
        return os;
    }
};


// ==========================================
// MAIN - TEST DI TUTTE LE STRUTTURE
// ==========================================
int main() {
    cout << "--- 1 & 2. Lista Semplice Generica (Uso float come test) ---" << endl;
    ListaSemplice<float> listaSemplice;
    listaSemplice.inserisci(10.5);
    listaSemplice.inserisci(20.3);
    listaSemplice.inserisci(5.1);
    cout << "Lista inserita in testa: " << listaSemplice << endl;
    listaSemplice.rimuovi(20.3);
    cout << "Dopo rimozione 20.3: " << listaSemplice << endl;
    cout << "Ricerca 10.5: " << (listaSemplice.ricerca(10.5) ? "Trovato" : "Non Trovato") << "\n\n";

    cout << "--- 3. Lista Singola Ordinata (Interi) ---" << endl;
    ListaOrdinata<int> listaOrd;
    listaOrd.inserisci(30);
    listaOrd.inserisci(10);
    listaOrd.inserisci(20);
    cout << "Lista ordinata: " << listaOrd << endl;
    listaOrd.rimuovi(10);
    cout << "Dopo rimozione 10: " << listaOrd << "\n\n";

    cout << "--- 4. Lista Doppiamente Linkata ---" << endl;
    ListaDoppia<int> listaDoppia;
    listaDoppia.inserisci(1);
    listaDoppia.inserisci(2);
    listaDoppia.inserisci(3);
    cout << "Lista doppia (inserita in testa): " << listaDoppia << endl;
    listaDoppia.rimuovi(2);
    cout << "Dopo rimozione 2: " << listaDoppia << "\n\n";

    cout << "--- 5. Lista Doppia Ordinata ---" << endl;
    ListaDoppiaOrdinata<int> listaDppOrd;
    listaDppOrd.inserisci(50);
    listaDppOrd.inserisci(10);
    listaDppOrd.inserisci(30);
    cout << "Lista doppia ordinata: " << listaDppOrd << endl;
    listaDppOrd.rimuovi(30);
    cout << "Dopo rimozione 30: " << listaDppOrd << "\n\n";

    cout << "--- 6. Lista (Doppia) Circolare con Sentinella ---" << endl;
    ListaCircolareSentinella<int> listaCirc;
    listaCirc.inserisci(100);
    listaCirc.inserisci(200);
    listaCirc.inserisci(300);
    cout << "Lista circolare (inserita in coda): " << listaCirc << endl;
    listaCirc.rimuovi(200);
    cout << "Dopo rimozione 200: " << listaCirc << endl;

    return 0;
}