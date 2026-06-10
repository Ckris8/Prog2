#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const string stati[4] = {"ND", "Verde", "Arancione", "Rosso"};

class Patient {
    public:
        Patient() {
            id_ = 0;
            nome_ = "";
            condizione_ = 0;
        }
        Patient(int id, string nome, int condizione) : id_(id), nome_(nome) {
            if (condizione < 0 || condizione > 3) {
                throw runtime_error("Stato errato");
            } else {
                condizione_ = condizione;
            }
        }

        int getId() { return id_; }
        string getNome() { return nome_; }
        int getCondizione() { return condizione_; }

        void setPatient(int id, string nome, int condizione) {
            id_ = id;
            nome_ = nome;
            if (condizione < 0 || condizione > 3) {
                throw runtime_error("Stato errato");
            } else {
                condizione_ = condizione;
            }
        }

        void stampa() {
            cout << "Paziente ID: " << id_ << " , Nome: " << nome_ << " Codice: " << stati[condizione_] << endl;
        }
    private:
        int id_;
        string nome_;
        int condizione_;
};

// CORRETTO: Definizione corretta della struttura Nodo con tipo generico T
template<typename T>
struct Nodo {
    T p;
    Nodo* next;
};

template<typename T>
class Queue {
    public:
        Queue() {
            testa = nullptr;
            coda = nullptr;
        }

        // Distruttore per evitare memory leak
        ~Queue() {
            while (!isEmpty()) {
                Nodo<T>* elim = testa;
                testa = testa->next;
                delete elim;
            }
        }

        // CORRETTO: Corretto il typo nel nome
        bool isEmpty() {
            return testa == nullptr;
        }

        // CORRETTO: Passaggio per riferimento costante a T
        void enqueue(const T& Ip) {
            Nodo<T>* nuovo = new Nodo<T>;
            nuovo->p = Ip;
            nuovo->next = nullptr;

            Nodo<T>* curr = testa;
            Nodo<T>* prev = nullptr;

            // Ordiniamo in base alla priorità (Rosso = 3 va davanti a tutti)
            while (curr != nullptr && curr->p.getCondizione() >= Ip.getCondizione()) {
                prev = curr;
                curr = curr->next;
            }

            // CORRETTO: Ridisegnata la logica di inserimento dei puntatori
            if (prev == nullptr) { 
                // Inserimento in testa (lista vuota o elemento a priorità massima)
                nuovo->next = testa;
                testa = nuovo;
                if (coda == nullptr) {
                    coda = nuovo;
                }
            } else { 
                // Inserimento in mezzo o in coda
                prev->next = nuovo;
                nuovo->next = curr;
                if (curr == nullptr) { 
                    // Se siamo arrivati in fondo, il nuovo nodo diventa la coda
                    coda = nuovo;
                }
            }
        }

        T dequeue() {
            if (testa != nullptr) {
                Nodo<T>* elim = testa;
                T val = elim->p;
                testa = testa->next;
                
                if (isEmpty()) {
                    coda = nullptr;
                }
                
                // CORRETTO: Usato il punto (.) invece di ->
                elim->p.stampa(); 
                delete elim;
                return val;
            } else {
                throw runtime_error("Coda vuota");
            }
        }

    private:
        Nodo<T>* testa;
        Nodo<T>* coda;
};

int main() {
    // CORRETTO: Specificato il tipo del template <Patient>
    Queue<Patient> coda;

    // Adesso l'inserimento di oggetti temporanei funziona correttamente
    coda.enqueue(Patient(383, "Ciccio", 3)); // Rosso
    coda.enqueue(Patient(384, "Sara", 2));   // Arancione
    coda.enqueue(Patient(295, "Viola", 1));  // Verde
    coda.enqueue(Patient(296, "Romolo", 2)); // Arancione
    coda.enqueue(Patient(396, "Elio", 3));   // Rosso

    cout << "--- Estrazione pazienti in ordine di Triage ---" << endl;
    while (!coda.isEmpty()) {
        coda.dequeue();
    }

    return 0;
}