#include <iostream>
#include <string>

const int MAX=20;

using namespace std;

class Data{
    public:
        Data(int giorno,int mese,int anno):giorno_(giorno),mese_(mese),anno_(anno){}

        int getAnno(){
            return anno_;
        }

        int getMese(){
            return mese_;
        }

        int getGiorno(){
            return giorno_;
        }
    private:
        int anno_;
        int mese_;
        int giorno_;
};

class Prodotto{
    public:
        Prodotto():id_(0),prezzo_(0.0){}
        Prodotto(int id,double prezzo):id_(id),prezzo_(prezzo){}

        int getId(){
            return id_;
        }

        double getPrezzo(){
            return prezzo_;
        }

        void setId(int id){
            id_=id;
        }

        void setPrezzo(double prezzo){
            prezzo_=prezzo;
        }

        virtual bool verifica(Data* oggi){return true;}

        friend ostream& operator<<(ostream& out,Prodotto& p){
            out<<"Prodotto\t ID: "<<p.id_<<" Prezzo: "<<p.prezzo_<<endl;
            return out;
        }


        void leggi(){
            int id;
            double prezzo;

            cout<<"Creazione prodotto\n Inserisci ID: ";
            cin >> id;
            cin.get();
            cout<<"Inserisci Prezzo: ";
            cin>> prezzo;
            cin.get();

            Prodotto(id,prezzo);
        }

    private:
        int id_;
        double prezzo_;
};



class ProdottoAlimentare:public Prodotto{
    public:
        ProdottoAlimentare(int id,double prezzo, int giorno,int mese,int anno):Prodotto(id,prezzo){
            scadenza= new Data(giorno,mese,anno);
        }

        bool verifica(Data* oggi){
            if (oggi->getAnno() > scadenza->getAnno()) return false;
        
            if (oggi->getMese() > scadenza->getMese()) return false;

            if(oggi->getGiorno()<scadenza->getGiorno() ){
                cout<<"Prodotto valido,non scaduto"<<endl;
                return true;
            }else{
                cout<<"Prodotto Scaduto"<<endl;
                return false;
            }
        }
    private:
        Data* scadenza;
};


class ProdottoPerBambini:public Prodotto{
    public:
        ProdottoPerBambini(int id,double prezzo, int fascia):Prodotto(id,prezzo){
            fasciaEta=fascie[fascia];
        }

    private:
        string fascie[4]={"0-3","3-6","6-9","9-12"};
        string fasciaEta;
};


class Venditore{
    public:
        Venditore():IdVend(0),nProdotti(0){
            prodotti=new Prodotto*[MAX];
        }
        Venditore(int id):IdVend(id),nProdotti(0){
            prodotti=new Prodotto*[MAX];
        }

        friend ostream& operator<<(ostream& out,Venditore &v ){
            out<<"Venditore\tID:"<<v.IdVend<<endl;
            out<<"Prodotti Venduti:"<<endl;
            if(v.nProdotti==0){
                out<<"Nessun prodotto";
            }else{
                for(int i=0;i<v.nProdotti;i++){
                out<<*(v.prodotti[i]);
                }
            }
            
            return out;
        }

        double calcolaPrezzoTotale(){
            double somma=0.0;
            for(int i=0;i<nProdotti;i++){
                somma+=prodotti[i]->getPrezzo();
            }
            return somma;
        }

        double calcolaValoreMagazzino(Data*oggi){
            double somma=0.0;
            for(int i=0;i<nProdotti;i++){
                if(prodotti[i]->verifica(oggi)){
                    somma+=prodotti[i]->getPrezzo();
                }
            }
            return somma;
        }

        void aggiungiProdotto(Prodotto* p){
            if(nProdotti<MAX){
                prodotti[nProdotti]= p;
                nProdotti++;
            }else{
                cout<<"Catalogo pieno"<<endl;
                delete p;
                return;
            }
            
        }

        void leggi(){
            int id;

            cout<<"Creazione venditore\n Inserisci ID: ";
            cin >> id;
            cin.get();
            

           // Venditore(id);
        }

    private:
        int IdVend;
        Prodotto** prodotti;
        int nProdotti;
};

void swap(Venditore*& a,Venditore*& b){
    Venditore* temp=a;
    a=b;
    b=temp;
}

void stampaTotali(Venditore* V[],int size, int scelta){
    for(int pass=0;pass<size-1;pass++){
        for(int i=0;i<size-1-pass;i++){
            if(scelta==1){
                if(V[i]->calcolaPrezzoTotale() > V[i+1]->calcolaPrezzoTotale()){
                    swap(V[i],V[i+1]);
                }
            }else{
                if(V[i]->calcolaPrezzoTotale() < V[i+1]->calcolaPrezzoTotale()){
                    swap(V[i],V[i+1]);
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        cout << *V[i];
        cout << "Prezzo Totale Catalogo: " << V[i]->calcolaPrezzoTotale() << " Euro\n\n";
    }
}

int main(){

    // Creiamo una data odierna fittizia per il controllo scadenze (es. 9 Giugno 2026)
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

    // Interfaccia Menu richiesta dalla traccia
    int scelta = 0;
    cout << "=== MENU SELEZIONE ===\n";
    cout << "Come vuoi ordinare i venditori in base al prezzo totale?\n";
    cout << "1) Ordine Crescente\n";
    cout << "2) Ordine Decrescente\n";
    cout << "Scelta: ";
    cin >> scelta;
    cout << "\n";

    stampaTotali(venditori, numVenditori, scelta);

    return 0;
}