#include <iostream>
#define MAX 100

class CodaArray {
private:
    int elementi[MAX];
    int inizio, fine;

public:
    CodaArray() {
        inizio = 0;   // Indice del primo elemento
        fine = -1;    // Indice dell'ultimo elemento
    }

    // Inserisce un elemento in coda (enqueue)
    void enqueue(int valore) {
        if(fine < MAX - 1) {
            elementi[++fine] = valore;
        } else {
            std::cout << "Errore: coda piena\n";
        }
    }

    // Estrae un elemento dalla testa (dequeue)
    int dequeue() {
        if(inizio <= fine) {
            return elementi[inizio++];
        } else {
            std::cout << "Errore: coda vuota\n";
            return -1;
        }
    }

    // Controlla se la coda è vuota
    bool isEmpty() {
        return inizio > fine;
    }
};

int main() {
    CodaArray coda;

    coda.enqueue(1);
    coda.enqueue(2);
    coda.enqueue(3);

    while(!coda.isEmpty()) {
        std::cout << "Dequeue: " << coda.dequeue() << std::endl;
    }

    return 0;
}