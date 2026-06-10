#include <iostream>
#include <string>

using namespace std;

const int MAX=20;

class Elementi{
    public:
        Elementi():titolo(""),autore(""){}
        Elementi(string t,string a):titolo(t),autore(a){}

        virtual ~Elementi(){}

        string getTitolo(){
            return titolo;
        }

        string getAutore(){
            return autore;
        }


        virtual void stampa()=0;
    protected:
        string titolo;
        string autore;
};

class Libri:public Elementi{
    public:
        Libri():Elementi("",""){
            numeroPag=0;
        }
        Libri(string t,string a,int n):Elementi(t,a),numeroPag(n){}

        

        void stampa(){
            cout<<"Libro\tTitolo: "<<titolo<<" Autore: "<<autore<<" Numero pagine: "<<numeroPag<<endl;
        }

    private:
        int numeroPag;
};

class DVD:public Elementi{
    public:
        DVD():Elementi("",""){
            durata=0;
        }
        DVD(string t,string a,int d):Elementi(t,a),durata(d){}

        void stampa(){
            cout<<"DVD\tTitolo: "<<titolo<<" Autore: "<<autore<<" Durata brani ore: "<<durata<<endl;
        }


    private:
        int durata;
};

class Libreria{
    public:
        Libreria():nElementi(0){}

        void insertElemento(){
            int scelta;
            while(true){
                cout<<"Creazione elemento"<<endl;
                cout<<"1.Libro"<<endl;
                cout<<"2.DVD"<<endl;
                cout<<"scelta: ";
            
                cin>>scelta;
                cin.get();

                
                if(scelta<1||scelta>2){
                    cout<<"Opzione non disponibile,riprova"<<endl;
                    return;
                }else{
                    break;
                }

            }

            string t;
            string a;
            int v;

            switch(scelta){
                case 1:
                    cout<<"Creazione libro"<<endl;
                    cout<<"Inserisci titolo: ";
                    getline(cin,t);
                    cout<<endl;
                    cout<<"Inserisci autore: ";
                    getline(cin,a);
                    cout<<endl;
                    cout<<"Inserisci numero pagine: ";
                    cin>>v;
                    cin.get();
                    cout<<endl<<"Creazione Elemento..."<<endl;

                    collezione[nElementi]= new Libri(t,a,v);
                    nElementi++;

                    break;

                case 2:

                    cout<<"Creazione DVD"<<endl;
                    cout<<"Inserisci titolo: ";
                    getline(cin,t);
                    
                    cout<<endl;
                    cout<<"Inserisci autore: ";
                    getline(cin,a);
                    
                    cout<<endl;
                    cout<<"Inserisci durata(ore): ";
                    cin>>v;
                    cin.get();
                    
                    cout<<endl<<"Creazione Elemento..."<<endl;

                    collezione[nElementi]= new DVD(t,a,v);
                    nElementi++;

                    break;
                default:
                    break;
            }
             
        }

        void stampaLibreria(){
            cout<<"Libreria:"<<endl;
            for(int i=0;i<nElementi;i++){
                collezione[i]->stampa();
            }
        }

        bool ricercaElemento(string tR){
            for(int i=0;i<nElementi;i++){
                if(collezione[i]->getTitolo()==tR){
                    cout<<"Elemento trovato:"<<endl;
                    collezione[i]->stampa();
                    return true;
                }
            }
            cout<<"Elemento non trovato"<<endl;
            return false;
        }

    private:
        Elementi** collezione= new Elementi*[MAX];
        int nElementi;
};


int main(){
    Libreria libreria;


    for(int i=0;i<5;i++){
         libreria.insertElemento();
    }

    libreria.stampaLibreria();

    string ricerca;

    cout<<"Inserisci un elemento da cercare:";
    getline(cin,ricerca);

    libreria.ricercaElemento(ricerca);


    return 0;
}