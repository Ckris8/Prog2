#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Studente{
    public:
        Studente(){
            matricola="";
            nome="";
            cognome="";
            media=0.0;
        }
        Studente(string m,string n,string c, double mn):matricola(m),nome(n),cognome(c),media(mn){}

        string getMatricola(){
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

        
        void stampa(){
            cout<< nome<<" "<<cognome <<" - Matricola: "<<matricola <<endl;
        }
    protected:
        string matricola;
        string nome;
        string cognome;
        double media;
};

class BorsaDiStudio{
    public:

        BorsaDiStudio(int imp, int dur) 
        : importo(imp), durata(dur) {}

        void setImporto(int i){
            importo=i;
        }
        void setDurata(int d){
            durata=d;
        }

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

        StudenteBorsista(string m,string n,string c, double mn,int b,int d):Studente(m,n,c,mn){
            borsa= new BorsaDiStudio(b,d);
        }

        ~StudenteBorsista() {if (borsa) delete borsa;}
        
        double get_importo_borsa(){
            return borsa->getImporto();
        }

        double get_durata_borsa(){
            return borsa->getDurata();
        }

        void set_durata_borsa(int n){
            borsa->setDurata(n);
        }

        void stampaB(){
            if(borsa->getDurata()!=0){
                cout<< matricola<<" : "<<nome<<" "<<cognome <<" - "<<media<<" ["<<borsa->getImporto()<<"]"<<endl;
            }else{
                stampa();
            }
        }
    private:
        BorsaDiStudio* borsa;
};


struct nodo{
    StudenteBorsista* s;
    nodo*next;
};

class pila{
    public:

        pila(){
            testa=nullptr;
        }

        void push(StudenteBorsista* Is){
            nodo* nuovo= new nodo;
            nuovo->s=Is;
            nuovo->next=testa;
            testa=nuovo;
        }
        
        void pop(StudenteBorsista* Es){
            if(testa==nullptr){ 
                cout<<"Pila vuota"<<endl;
                return;
            }else{
                
                nodo* current=testa;
                nodo* prev=nullptr;
                while((current!=nullptr)&&current->s->getMatricola()!=Es->getMatricola()){
                    prev=current;
                    current=current->next;
                }

                if(current==nullptr){
                    return;
                }

                if(prev==nullptr){
                    testa=testa->next;
                }else{
                    prev->next=current->next;
                }
                delete current->s;
                delete current;
            }
        }


        void verifica(){
            nodo*current=testa;
            while(current!=nullptr){
                if(current->s->getMedia()<25.0){
                    current->s->set_durata_borsa(0);
                    nodo*Es= current;
                    current=current->next;
                    cout<<"Studente insufficiente rimosso:";
                    current->s->stampaB();
                    pop(Es->s);//rimuove
                }else{
                    current=current->next;
                }
            }

        }

        void stampaTotale(){
            int somma=0;
            nodo*current=testa;
            cout<<"La pila contiene i seguenti studenti:"<<endl;
            while(current!=nullptr){
                current->s->stampaB();
                if(current->s->get_durata_borsa()>0){
                    somma += current->s->get_importo_borsa();
                }
                
                current=current->next;
            }
            cout<<"Totale importi borse di studio: "<<somma<<" euro"<<endl;
        }

    private:
        nodo*testa;
};


int main(){

    pila studenti;

    ifstream file("input.txt");
    
    if(!file.is_open()){
        cout<<"Errore, apertura file"<<endl;
    }

    string m;
    string n;
    string c;
    double mn;
    int b;
    int d;

    while(file >> m>>n>>c>>mn>>b>>d){
        
        StudenteBorsista* studente= new StudenteBorsista(m,n,c,mn,b,d);
        
        studenti.push(studente);
    }

    file.close();
    
    studenti.verifica();

    studenti.stampaTotale();

    return 0;
}