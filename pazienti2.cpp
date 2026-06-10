#include <iostream>
#include <string>

using namespace std;


class Patient{
    public:
        Patient():id(0),nome(""),condizione(0){}
        Patient(int i,string n, int c):id(i),nome(n),condizione(c){}

        int getId(){
            return id;
        }

        string getNome(){
            return nome;
        }

        int getCondizioneN(){
            return condizione;
        }

        string getCondizioneS(){
            return stati[condizione];
        }

        virtual bool getRaccomandato(){return false;}

        virtual void stampa(){
            cout<<"Paziente\t ID:"<<id<<" Nome:"<<nome<<" Condizione: "<<stati[condizione]<<endl;
        }

    protected:
        int id;
        string nome;
        int condizione;
        string stati[4]={"ND","Verde","Arancione","Rosso"};
};

class PatientR:public Patient{
    public:
        PatientR():Patient(0,"",0){
            raccomandazione=true;
        }
        PatientR(int i,string n, int c):Patient(i,n,c){
            raccomandazione=true;
        }

        bool getRaccomandato(){
            return raccomandazione;
        }

    private:
        bool raccomandazione;
};

template<typename T>
struct Nodo{
    T *p;
    Nodo<T>*next;
};

template<typename T>
class Queue{
    public:

        Queue(){
            testa=nullptr;
            coda=nullptr;
            size=0;
        }

        void enqueue(T *val){
            Nodo<T>*nuovo= new Nodo<T>;
            nuovo->p=val;
            nuovo->next=nullptr;

            Nodo<T>* current=testa;
            Nodo<T>* previus=nullptr;

            while(current!=nullptr&&current->p->getCondizioneN() < val->getCondizioneN()){
                previus=current;
                current=current->next;
            }

            if (previus == nullptr) { 
                // Inserimento in testa (lista vuota o elemento a priorità massima)
                nuovo->next = testa;
                testa = nuovo;
                if (coda == nullptr) {
                    coda = nuovo;
                }
            } else { 
                // Inserimento in mezzo o in coda
                previus->next = nuovo;
                nuovo->next = current;
                if (current == nullptr) { 
                    // Se siamo arrivati in fondo, il nuovo nodo diventa la coda
                    coda = nuovo;
                }
            }
            size++;


        }

        T* dequeue(){
            if(!isEmpty()){
                Nodo<T>* elim= testa;
                T *val= testa->p;
                testa=testa->next;
                if(isEmpty()){
                    coda=nullptr;
                }
                elim->p->stampa();
                delete elim;
                size--;
                return val;
            }else{
                throw runtime_error("Coda vuota");
            }
        }

        bool isEmpty(){
            return testa==nullptr;
        }

        void enqueuePriority(T* val){
            if(isEmpty()){
                enqueue(val);
                return;
            }
            Queue<T> tempQueue;

            //es=elementi da spostare
            int Es= size>3? size-3 :0;// se ci sono più di 3 elementi togliamo quelli davanti
                                    // se no eliminiamo tutto il raccomandato andra in testa
            for(int i=0;i<Es;i++){
                tempQueue.enqueue(this->dequeue());//aggiunge alla coda temp gli elementi levati da qwuella principale
            }

            this->enqueue(val);

            while(!tempQueue.isEmpty()){
                this->enqueue(tempQueue.dequeue());//riinserisce gli elementi eliminati
            }

        }
    private:
        Nodo<T>* testa;
        Nodo<T>* coda;
        int size;
};

int main(){
    Queue<Patient> coda;

    coda.enqueue(new Patient(383, "Ciccio", 3)); // Rosso
    coda.enqueue( new Patient(384, "Sara", 2));   // Arancione
    coda.enqueuePriority(new PatientR(295, "Viola", 1));  // Verde
    coda.enqueuePriority(new PatientR(296, "Romolo", 2)); // Arancione
    coda.enqueue(new Patient(396, "Elio", 3));   // Rosso

    cout << "--- Estrazione pazienti in ordine di coda---" << endl;
    while (!coda.isEmpty()) {
        coda.dequeue();
    }

}