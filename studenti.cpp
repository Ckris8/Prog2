#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Studente{
    public:
        Studente():matricola(0),nome(""),cognome(""),media(0.0){}
        Studente(int m,string n,string c,double mn):matricola(m),nome(n),cognome(c),media(mn){}

        ~Studente(){}

        int getMatricola(){
            return matricola;
        }

        string getNome(){
            return nome;
        }

        string getCognome(){
            return cognome;
        }

        double getMedia(){
            return media;
        }

        virtual void stampa(){
            cout<< matricola<<": "<<nome<<" "<<cognome<<" - media "<<media<<endl;
        }
    protected:
        int matricola;
        string nome;
        string cognome;
        double media;
};

class BorsaDiStudio{
    public:
        BorsaDiStudio():importo(0),durata(0){}
        BorsaDiStudio(int i,int d):importo(i),durata(d){}

        ~BorsaDiStudio(){}

        int getImporto(){
            return importo;
        }

        int getDurata(){
            return durata;
        }

        
    private:
        int importo;
        int durata;
};

class StudenteBorsista:public Studente{
    public:
        StudenteBorsista():Studente(0,"","",0.0){
            borsa=nullptr;
        }
        StudenteBorsista(int m,string n,string c,double mn,int imp,int dur):Studente(m,n,c,mn){
            if (dur > 0 && imp > 0) {
                borsa = new BorsaDiStudio(imp, dur);
            } else {
                borsa = nullptr;
        }
        }

        ~StudenteBorsista(){
            delete borsa;
        }

        int get_importo_borsa(){
            return borsa != nullptr ? borsa->getImporto() : 0;
        }

        int get_durata_borsa(){
            return borsa != nullptr ? borsa->getDurata() : 0;
        }

        void stampa(){
            if(borsa != nullptr && borsa->getDurata() > 0){
                cout<< matricola<<": "<<nome<<" "<<cognome<<" - media "<<media<<" ["<<borsa->getImporto()<<"]"<<endl;
            }else{
                Studente::stampa();
            }
        }

    private:
        BorsaDiStudio* borsa;
};

template<typename T>
struct Nodo{
    T* s;
    Nodo* next;
};

template<typename T>
class Pila{
    public:
        Pila():testa(nullptr){}

        ~Pila(){   
            while (!isEmpty()) {
            T* rimosso = pop();
            delete rimosso; 
            }
        }

        bool isEmpty(){
            return testa==nullptr;
        }


        void push(T* val){
            Nodo<T>* nuovo= new Nodo<T>;
            nuovo->s=val;
            nuovo->next=testa;
            testa=nuovo;
        }

        T* pop(){

            if (isEmpty()) return nullptr;

            Nodo<T>* temp = testa;
            T* record = testa->s;
            testa = testa->next;
            
            delete temp; // Elimina il "contenitore" Nodo
            return record;
            
        }

        void verifica(){
            Pila<T> pilaTemp;

            while(!isEmpty()){
                T*sT=pop();
                if(sT->getMedia() < 25.0){//controlla tutta la pila svuotandola per verificare la media
                    cout<<"Studente insufficiente rimosso:";
                    sT->stampa();
                    delete sT;
                }else{
                    pilaTemp.push(sT);
                }
            }
                //ritorniamo gli studenti validi nella pila
                while(!pilaTemp.isEmpty()){
                    push(pilaTemp.pop());
                }
           
        }

        void stampaPila(){
            double somma=0.0;
            Nodo<T>* current=testa;
            while(current!=nullptr){
                if(current->s->get_durata_borsa() <= 0){
                    current->s->stampa();
                }else{
                    current->s->stampa();
                    somma += current->s->get_importo_borsa();
                }

                current=current->next;
            }

            cout<<"Totali importi borse di studio: "<<somma<<" euro."<<endl;
        }

    private:
        Nodo<T>*testa;
};

int main(){

    Pila<StudenteBorsista> pila;

    ifstream file("input.txt");
    if(!file.is_open()){
        cout<<"Errore apertura file"<<endl;
    }

    int m;
    string n;
    string c;
    double mn;
    int imp;
    int d;


    while(file>>m>>n>>c>>mn>>imp>>d){
        
        pila.push(new StudenteBorsista(m,n,c,mn,imp,d));
        
    }
    file.close();

    pila.verifica();

    pila.stampaPila();
    return 0;
}
