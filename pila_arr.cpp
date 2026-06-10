#include <iostream>
#define MAX 100 // Dimensione massima della pila

class PilaArray {
private:
    int elementi[MAX]; // Array per salvare gli elementi
    int top;           // Indice dell'elemento in cima

public:
    PilaArray() {
        top = -1; // La pila è vuota
    }

    // Inserisce un elemento in cima (push)
    void push(int valore) {
        if(top < MAX - 1) {
            elementi[++top] = valore;
        } else {
            std::cout << "Errore: pila piena\n";
        }
    }

    // Rimuove l'elemento in cima (pop)
    int pop() {
        if(top >= 0) {
            return elementi[top--];
        } else {
            std::cout << "Errore: pila vuota\n";
            return -1;
        }
    }

    // Ritorna l'elemento in cima senza toglierlo
    int peek() {
        if(top >= 0)
            return elementi[top];
        else {
            std::cout << "Pila vuota\n";
            return -1;
        }
    }

    // Controlla se la pila è vuota
    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    PilaArray pila;

    pila.push(10);
    pila.push(20);
    pila.push(30);

    std::cout << "Elemento in cima: " << pila.peek() << std::endl; // 30

    while(!pila.isEmpty()) {
        std::cout << "Pop: " << pila.pop() << std::endl;
    }

    return 0;
}
