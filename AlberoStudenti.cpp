#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Studente{
    public:
        Studente(){
            matricola=0;
            nome="";
            cognome="";;
            media=0.0;
        }

        Studente(int m,string n,string c,double mn):matricola(m),nome(n),cognome(c),media(mn){}

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

        void stampa(){
            cout<< nome<<" "<<cognome <<" - Matricola: "<<matricola <<" Media generale: "<<media<<endl;
        }

    private:
        int matricola;
        string nome;
        string cognome;
        double media;
};

class nodo{
    public:
        Studente* s;
        nodo* dx;
        nodo* sx;

        nodo(Studente*Is){
            s=Is;
            dx=nullptr;
            sx=nullptr;
        }
};

class albero{
    public:

        albero(){
            radice=nullptr;
        }

        void insert(Studente*s){
            I(radice,s);
        }

        bool search(int n){
            return sh(radice,n);
        }

        void InOrder(){
            In(radice);
        }

    private:
        nodo* radice;

        void I(nodo*&r,Studente* s){
            if(!r){
                r= new nodo(s);
                
            }else if(s->getMatricola()  > r->s->getMatricola() ){
                I(r->dx,s);
            }else{
                I(r->sx,s);
            }
        }

        bool sh(nodo*r,int m){
            if(r){
                if(r->s->getMatricola()==m){
                    return true;
                }else if(m > r->s->getMatricola()){
                    return sh(r->dx, m);
                }else{
                    return sh(r->sx, m);
                }
            }else{
                return false;
            }
        }

        void In(nodo*& r){
            if(r){
                In(r->sx);
                cout<< r->s->getMatricola() << " ";
                In(r->dx);
            }
        }


};


int main(){
    albero studenti;

    ifstream file("input.txt");

    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file." << endl;
        return 1;
    }

    int m;
    string n,c;
    double mn;

    while(file >> m >> n >> c >> mn){
        studenti.insert(new Studente(m,n,c,mn));
    }

    if (studenti.search(1004)) {
        cout << "Studente 1004 trovato!" << endl;
    } else {
        cout << "Studente 1004 NON trovato." << endl;
    }

    

    studenti.InOrder();


    return 0;
}
