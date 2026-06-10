#include <iostream>

// Struttura di un nodo
struct NodoPila {
    int valore;
    NodoPila* prossimo;
};

class PilaDinamica {
private:
    NodoPila* top;

public:
    PilaDinamica() {
        top = nullptr;
    }

    // Inserisce in cima
    void push(int valore) {
        NodoPila* nuovo = new NodoPila;
        nuovo->valore = valore;
        nuovo->prossimo = top;
        top = nuovo;
    }

    // Toglie dalla cima
    int pop() {
        if(top != nullptr) {
            int valore = top->valore;
            NodoPila* temp = top;
            top = top->prossimo;
            delete temp;
            return valore;
        } else {
            std::cout << "Errore: pila vuota\n";
            return -1;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    PilaDinamica pila;

    pila.push(5);
    pila.push(10);
    pila.push(15);

    while(!pila.isEmpty()) {
        std::cout << "Pop: " << pila.pop() << std::endl;
    }

    return 0;
}
