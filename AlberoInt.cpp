#include <iostream>

using namespace std;

struct nodo{
    int numero;
    nodo*sx;
    nodo*dx;
};

class nodo{
    public:
        int numero;
        nodo*sx;
        nodo*dx;

        Nodo(int num){
            numero= num;
            sx=nullptr;
            dx=nullptr;
        }
}

class albero{
    public:
        albero(){
            radice=NULL;
        }

        void inserisci(int num){
            I(radice,num);
        }

        ~albero(){distruggi(radice);}

        void stampaCresc(){
            cout<<"Elementi in ordine crescente:"<<endl;
            In(radice);
            cout<<endl;
        }

        void minimo(){
            cout<<"Valore minimo albero(-1 errore):"<<min(radice)<<endl;
        }

        void massimo(){
            cout<<"Valore massimo albero(-1 errore):"<<max(radice)<<endl;
        }

        void cerca(int num){
            if(search(radice,num)){
                cout<<"Il valore "<<num<<" e' presente nell'albero"<<endl;
            }else{
                cout<<"Il valore "<< num <<" NON e' presente nel albero"<<endl;
            }
        }


    private:
        nodo*radice;

        void distruggi(nodo* &rad) {
            if(rad) {//se il nodo rad esiste
                distruggi(rad->sx);
                distruggi(rad->dx);
                delete rad;
                rad=NULL;
            }
        }

        void I(int num, node* &rad) {
            if (rad == nullptr) { 
                // Se il puntatore è nullo, abbiamo trovato il posto giusto per il nuovo nodo
                rad = new node(num);
            } 
            else if (chiave < rad->numero) {
                I(num, rad->sx); // Scende a sinistra
            } 
            else{
                I(num, rad->dx); // Scende a destra
            }
        }

        void In(nodo* rad) {//sinistra->radice->destra
	    if (rad) {
		In(rad -> sx);
		cout << rad->numero << ' ';
		In(rad -> dx);
		}
}

        bool search(nodo* rad,int num){
            if(rad){
                if(rad->numero==num){
                    return true;
                }
                if(num>rad->numero  ){
                    return search(rad->dx,num);
                }else {
                    return search(rad->sx,num);
                }  
            }else{
                return false;
            }
        }

        int max(nodo*rad){
            if(rad){
                while(rad->dx !=NULL){
                    rad=rad->dx;
                }
                return rad->numero;
            }else{
                return -1;
            }
        }

        int min(nodo*rad){
            if(rad){
                while(rad->sx !=NULL){
                    rad=rad->sx;
                }
                return rad->numero;
            }else{
                return -1;
            }
        };
};


int main(){
    albero alberoInt;
    int input=0;
    do{
        cout<<"Inserisci un numero intero positivo nell'albero (-1 per terminare):"<<endl;
        while(!(cin>>input)){
            cout<<"Errore, inserisci un intero, riprova:";
            cin.clear();
            cin.ignore(10000,'\n');
        }
        if(input>=0){
            alberoInt.inserisci(input);
        }else if(input != -1){
            cout<<"Numero inserito errato(-1 per terminare)"<<endl;
        }
    }while(input!=-1);

    alberoInt.stampaCresc();

    alberoInt.minimo();
    alberoInt.massimo();

    cout<<"Inserisci un valore da cercare nell'albero:";
    cin>>input;
    alberoInt.cerca(input);

    return 0;
}