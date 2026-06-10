#include <iostream>

// Struttura di un nodo
struct NodoCoda {
    int valore;
    NodoCoda* prossimo;
};

class CodaDinamica {
private:
    NodoCoda* testa; // Primo elemento
    NodoCoda* coda;  // Ultimo elemento

public:
    CodaDinamica() {
        testa = coda = nullptr;
    }

    // Inserisce in coda (enqueue)
    void enqueue(int valore) {
        NodoCoda* nuovo = new NodoCoda;
        nuovo->valore = valore;
        nuovo->prossimo = nullptr;
        if(coda == nullptr) { // Coda vuota
            testa = coda = nuovo;
        } else {
            coda->prossimo = nuovo;
            coda = nuovo;
        }
    }

    // Estrae dalla testa (dequeue)
    int dequeue() {
        if(testa != nullptr) {
            int valore = testa->valore;
            NodoCoda* temp = testa;
            testa = testa->prossimo;
            if(testa == nullptr) // Coda vuota dopo l'estrazione
                coda = nullptr;
            delete temp;
            return valore;
        } else {
            std::cout << "Errore: coda vuota\n";
            return -1;
        }
    }

    bool isEmpty() {
        return testa == nullptr;
    }
};

int main() {
    CodaDinamica coda;

    coda.enqueue(100);
    coda.enqueue(200);
    coda.enqueue(300);

    while(!coda.isEmpty()) {
        std::cout << "Dequeue: " << coda.dequeue() << std::endl;
    }

    return 0;
}
