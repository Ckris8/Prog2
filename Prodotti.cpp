#include<iostream>
#include <string>

using namespace std;
const int MAX=20;

class Prodotto{
    public:
        Prodotto():id(0),prezzo(0.0){}
        Prodotto(int i,double p):id(i),prezzo(p){}

        ~Prodotto(){}

        int getId(){
            return id;
        }

        double getPrezzo(){
            return prezzo;
        }

        void setId(int i){
            id=i;
        }

        void setPrezzo(double p){
            prezzo=p;
        }

        friend ostream& operator<<(ostream& out,Prodotto*& p){
            out<<"ID: "<<p->id<<" Prezzo: "<< p->prezzo<<endl;
            return out;
        }

        virtual bool verifica(){return true;}

    protected:
        int id;
        double prezzo;
};

class Data{
    public:
        Data(int g,int m,int a):giorno(g),mese(m),anno(a){}

        ~Data(){}

        int getGiorno(){
            return giorno;
        }

        int getMese(){
            return mese;
        }

        int getAnno(){
            return anno;
        }

        bool operator<= (Data& other){
            if(anno <= other.anno){
                if(mese <= other.mese){
                    if(giorno <= other.giorno){
                        return true;
                    }else{
                        return false;
                    }
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }


    private:

        int giorno;
        int mese;
        int anno;
};

class ProdottoAlimentare:public Prodotto{
    public:
        ProdottoAlimentare(int i,double p,int g,int m,int a):Prodotto(i,p){
            scadenza= new Data(g,m,a);
        }

        ~ProdottoAlimentare(){
            delete scadenza;
        }

        bool verifica(Data*oggi){
            return oggi<=scadenza;
        }
    private:
        Data* scadenza;
};

class ProdottoPerBambini:public Prodotto{
    public:
         ProdottoPerBambini(int i,double p,int f):Prodotto(i,p){
            fascia= fascie[f];
        }

        ~ProdottoPerBambini(){}


    private:
        string fascia;
        string fascie[4]={"0-3","3-6","6-9","9-12"};
};

class Venditore{
    public:
        Venditore():idV(0),nProdotti(0){}
        Venditore(int i):idV(i),nProdotti(0){}

        ~Venditore(){}

        friend ostream& operator<<(ostream&out, Venditore*& v){
            out<<" Venditore ID:"<<v->idV<<endl;
            if(v->nProdotti>0){
                for(int i=0;i < v->nProdotti;i++){
                    out<< v->catalogo[i];
                }
            }else{
                out<<"Nessun prodotto venduto";
            }
            return out;
        }

        double calcolaPrezzoTotale(){
            double somma=0.0;
            for(int i=0;i<nProdotti;i++){
                somma += catalogo[i]->getPrezzo();
            }
            return somma;
        }

        double calcolaValoreMagazino(){
            double somma=0.0;
            for(int i=0;i<nProdotti;i++){
                if(catalogo[i]->verifica()){
                    somma += catalogo[i]->getPrezzo();
                }
            }
            return somma;
        }

        void aggiungiProdotto(Prodotto* p){
            catalogo[nProdotti]=p;
            nProdotti++;
        }

    private:
        int idV;
        Prodotto** catalogo= new Prodotto*[MAX];
        int nProdotti;
};


void bubbleSort(Venditore*V[],int size){
    int scelta;

    cout<<"Selezione l'ordine di visualizzazione:\n1.Crescente\n2.Decrescente\nscelta:";
    cin>>scelta;

    switch(scelta){
        case 1:
            for(int pass=0;pass<size-1;pass++){
                for(int i=0;i<size-1;i++){
                    if(V[i]->calcolaPrezzoTotale() > V[i+1]->calcolaPrezzoTotale()){
                        Venditore* temp=V[i];
                        V[i]=V[i+1];
                        V[i+1]=temp;
                    }
                }
            }
            break;
        case 2:
            for(int pass=0;pass<size-1;pass++){
                for(int i=0;i<size-1;i++){
                    if(V[i]->calcolaPrezzoTotale() < V[i+1]->calcolaPrezzoTotale()){
                        Venditore* temp=V[i];
                        V[i]=V[i+1];
                        V[i+1]=temp;
                    }
                }
            }
            break;
        default:
            cout<<"Opzione non disponibile"<<endl;
            break;
    }

}

int main(){
    Data oggi(9, 6, 2026);

    int numVenditori = 3;
    Venditore* venditori[3] = { new Venditore(101), new Venditore(102), new Venditore(103) };

    // Riempiamo i venditori con almeno 5 prodotti ciascuno (Misto di prodotti)
    // Venditore 1
    venditori[0]->aggiungiProdotto(new Prodotto(1, 19.99));
    venditori[0]->aggiungiProdotto(new ProdottoAlimentare(2, 4.50, 15, 8, 2026)); // Buono
    venditori[0]->aggiungiProdotto(new ProdottoAlimentare(3, 2.30, 1, 5, 2026));  // Scaduto
    venditori[0]->aggiungiProdotto(new ProdottoPerBambini(4, 29.90, 1));          // Fascia 3-6
    venditori[0]->aggiungiProdotto(new Prodotto(5, 9.99));

    // Venditore 2
    venditori[1]->aggiungiProdotto(new Prodotto(6, 12.00));
    venditori[1]->aggiungiProdotto(new Prodotto(7, 8.50));
    venditori[1]->aggiungiProdotto(new ProdottoPerBambini(8, 45.00, 0));
    venditori[1]->aggiungiProdotto(new ProdottoAlimentare(9, 1.20, 20, 12, 2026));
    venditori[1]->aggiungiProdotto(new Prodotto(10, 15.00));

    // Venditore 3
    venditori[2]->aggiungiProdotto(new Prodotto(11, 100.00));
    venditori[2]->aggiungiProdotto(new ProdottoAlimentare(12, 3.50, 10, 5, 2026)); // Scaduto
    venditori[2]->aggiungiProdotto(new ProdottoPerBambini(13, 11.90, 3));
    venditori[2]->aggiungiProdotto(new ProdottoPerBambini(14, 22.00, 2));
    venditori[2]->aggiungiProdotto(new Prodotto(15, 5.00));

    bubbleSort(venditori,numVenditori);

    cout<<"stampa..."<<endl;

    for(int i=0;i<numVenditori;i++){
        cout<<venditori[i];
        cout<<" Costo Merce Totale: "<< venditori[i]->calcolaPrezzoTotale()<<endl;;
    }

    return 0;
}
