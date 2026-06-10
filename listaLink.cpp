#include <iostream>

using namespace std;

// Definizione del nodo della lista linkata
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}//costruttore
};

// Funzione per stampare la lista linkata
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Funzione per rilevare e rimuovere un ciclo nella lista linkata
bool detectAndRemoveLoop(Node* head) {
    if (head == nullptr || head->next == nullptr)//controlla se presente una lista che abbia più di 2 elementi
        return false;

    
    Node *slow = head, *fast = head;//dichiaro 2 puntatori ai nodi che puntano allo stesso punto

    // Fase 1: RIVELAMENTO CICLO
    while (fast != nullptr && fast->next != nullptr) {//finche uno dei due non arriva a null(se dovesse accadere è sicuro che il ciclo non cè)
        slow = slow->next;//faccio avanzare un puntatore di 1 passo alla volta
        fast = fast->next->next;//l'altro di 2 nodi alla volta

        if (slow == fast)//se i due nodi si incontrano vuol dire che è presente un ciclo
            break;//esci dal while
    }

    // Se non c'è ciclo
    if (slow != fast)
        return false;//restituisce che non è presente

    // Fase 2: RIMOZIONE CICLO
    //proprietà:La distanza dall'inizio della lista al punto in cui 
    // inizia il ciclo è ESATTAMENTE UGUALE alla distanza dal punto 
    // di scontro all'inizio del ciclo.

    slow = head;//faccio ripartire il puntatore di 1 passo dal inizio
                //l'altro puntatore rimarrà fisso e diminuirà ad un
                // passo alla volta per rispettare la distanza
    if (slow == fast) {
        // Caso particolare: il ciclo parte dal primo nodo
        while (fast->next != slow){//in caso fa fare un giro completo al 2 puntatore finche il suo prossimo è il primo nodo
            fast = fast->next;
        }
    } else {
        while (slow->next != fast->next) {//avanzano di 1 passo finche i suou punti next non si incontrano
            slow = slow->next;
            fast = fast->next;
        }
    }
    fast->next = nullptr;  // Rimuove il ciclo

    return true;
}

// Funzione main per creare la lista con ciclo e testare detectAndRemoveLoop()
int main() {
    // Creazione nodi
    Node* head = new Node(50);
    head->next = new Node(20);
    head->next->next = new Node(15);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(10);

    // Creazione del ciclo: l'ultimo nodo punta al nodo con valore 15
    head->next->next->next->next->next = head->next->next;

    if (detectAndRemoveLoop(head)) {
        cout << "Lista linkata dopo la rimozione del ciclo" << endl;
        printList(head);
    } else {
        cout << "Nessun ciclo rilevato" << endl;
        printList(head);
    }

    return 0;
}
