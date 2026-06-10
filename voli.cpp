#include <iostream>
#include <string>

using namespace std;
const int MAX=10;
const int N_POSTI_MAX=200;

class Passeggero;//forward decarations per usare i refirimenti a passeggero anche se dichiarata dopo

class Volo{
    public:

        Volo(string id,string d):idVolo_(id),destinazione_(d),numPosti_(0){}

        string getIdVolo(){
            return idVolo_;
        }

        string getDestinazione(){
            return destinazione_;
        }

        int getNumPosti(){
            return numPosti_;
        }

        void aggiuntaPasseggero(Passeggero* p){
            if(numPosti_<N_POSTI_MAX){
                passeggeri[numPosti_]=p;
                numPosti_++;
            }else{
                cout<<"nessun posto disponibile"<<endl;
                return;
            }
        }

        void EsigenzePart();
        

        
    private:
        string idVolo_;
        string destinazione_;
        int numPosti_;
        Passeggero* passeggeri[N_POSTI_MAX];
};

class Prenotazione{
    public:
        Prenotazione(string id,Volo*v,Passeggero*p):idPre_(id),v_(v),p_(p){}


        string getIdPre(){
            return idPre_;
        }

        void stampa();
        
    private:
        string idPre_;
        Volo* v_;
        Passeggero* p_;
};


class Passeggero{
    public:
        Passeggero(string n,string c,string id,bool e):nome_(n),cognome_(c),id_(id),esigenze_(e),nPrenotazioni(0){}

        string getNome(){
            return nome_;
        }
        
        string getId(){
            return id_;
        }

        bool getEsigenze(){
            return esigenze_;
        }

        void stampa(){
            cout<<"Passeggero\tNome:"<<nome_<<" Cognome: "<<cognome_<<" ID:"<<id_<<"\tEsigenze particolari: "<<((esigenze_)?"SI":"NO")<<endl;
        }


        void aggiungiPrenotazione(Prenotazione* p){
            if(nPrenotazioni>=MAX-1){
                cout<<"Prenotazioni massime raggiunte"<<endl;
                return;
            }

            prenotazioni[nPrenotazioni]=p;
            p->stampa();
            nPrenotazioni++;
        }

        bool annullaPrenotazione(string Ep){
            if(nPrenotazioni<=0){
                cout<<"Nessuna Prenotazione Presente"<<endl;
                return false;
            }

            for(int i=0; i<nPrenotazioni;i++){
                if(Ep==prenotazioni[i]->getIdPre()){
                    delete prenotazioni[i]; // Elimina l'oggetto
                    for(int j = i; j < nPrenotazioni - 1; j++){
                        prenotazioni[j] = prenotazioni[j+1]; // Sposta gli elementi indietro
                    }
                    prenotazioni[nPrenotazioni - 1] = nullptr; // Pulisci l'ultimo
                    nPrenotazioni--;
                    return true;
                }
            }

            cout<<"Prenotazione non trovata"<<endl;
            return false;
        }

        void visualizzaPrenotazioni(){
            cout<<"Prenotazioni di " << nome_ <<endl;
            for(int i=0;i<nPrenotazioni;i++){
                prenotazioni[i]->stampa();
            }
        }

    private:
        string nome_;
        string cognome_;
        string id_;
        bool esigenze_;
        Prenotazione* prenotazioni[MAX];
        int nPrenotazioni;
};





class SistemaPrenotazione{
    public:

        SistemaPrenotazione(string nc):nomeCompagnia_(nc),nVoli(0){}

        void AggiungiVolo(Volo* Iv){
            if(nVoli>=MAX-1){
                cout<<"Numero voli massimi raggiunti"<<endl;
                return;
            }

            cout<<"Aggiunta Volo riuscito"<<endl;
            voli_[nVoli]=Iv;
            nVoli++;
        }

        bool RimuoviVolo(Volo* Ev){
            if(nVoli<=0){
                cout<<"Nessun volo Presente"<<endl;
                return false;
            }

            for(int i=0; i<nVoli;i++){
                if(Ev->getIdVolo()==voli_[i]->getIdVolo()){
                    delete voli_[i]; // Elimina l'oggetto
                    for(int j = i; j < nVoli - 1; j++){
                        voli_[j] = voli_[j+1]; // Sposta gli elementi indietro
                    }
                    voli_[nVoli - 1] = nullptr; // Pulisci l'ultimo
                    nVoli--;
                    return true;
                }
            }

            cout<<"Volo non trovato"<<endl;
            return false;
        }

        bool creaPrenotazione(Passeggero*p,string idP){
            string d;

            cout<<"Creazione Prenotazione per "<<p->getNome()<<endl;
            
            cout<<"Inserisci destinazione:";
            cin>>d;
            cin.get();


            for(int i=0;i<nVoli;i++){
                if(voli_[i]->getDestinazione()==d){
                    cout<<"Volo disponibile\n Creazione Prenotazione..."<<endl;

                    p->aggiungiPrenotazione(new Prenotazione(idP,voli_[i],p));
                    voli_[i]->aggiuntaPasseggero(p);

                    return true;
                }
            }

            cout<<"nessun volo disponibile per la destinazione"<<endl;
            return false;
        }

        bool CancellaPrenotazione(Passeggero *p){
            string Ep;
            cout<<"Inserisci ID da prenotazione da eliminare:"<<endl;
            cin>>Ep;
            return p->annullaPrenotazione(Ep);
        }


        bool RicercaVoli(string d){
            for(int i=0;i<nVoli;i++){
                if(voli_[i]->getDestinazione()==d){
                    if(voli_[i]->getNumPosti()==N_POSTI_MAX){
                        cout<<"Volo Pieno"<<endl;
                        return false;
                    }

                    cout<<"Volo disponibile per "<<d<<"."<<endl;

                    return true;
                }
            }
            return false;
        }

        // void VisualizzaEsigenze(Volo *& v){
        //     for(int i=0;i<nVoli;i++){
        //         if(voli_[i]->getIdVolo()==v->getIdVolo()){
        //             voli_
        //         }
        //     }
        // }

    private: 
        string nomeCompagnia_;
        Volo* voli_[MAX];
        int nVoli;
};


void Volo::EsigenzePart() {
    for(int i=0; i<numPosti_; i++){
        if(passeggeri[i]->getEsigenze()){
            passeggeri[i]->stampa(); // Ora il compilatore conosce Passeggero!
        }
    }
}

void Prenotazione::stampa(){
        cout<<"Prenotazione\tID: "<<idPre_<<" Volo ID:"<<v_->getIdVolo() << "Passeggero ID:"<<p_->getId()<<endl;
}

int main(){

    SistemaPrenotazione* sistema= new SistemaPrenotazione("Ryanair");

    Volo* v1= new Volo("39530","Catania");
    Volo* v2= new Volo("39535","Roma");

    Passeggero* p1= new Passeggero("Chrristian","Fillo","99949", false);
    Passeggero* p2= new Passeggero("Marco","renna","40393", true);
    Passeggero* p3= new Passeggero("Matteo","lisso","88888", true);
    Passeggero* p4= new Passeggero("Sergio","negro","99999", false);

    sistema->AggiungiVolo(v1);
    sistema->AggiungiVolo(v2);

    sistema->RicercaVoli("39530");
    sistema->RicercaVoli("99999");

    sistema->creaPrenotazione(p1,"40639");
    sistema->creaPrenotazione(p1,"52052");
    sistema->creaPrenotazione(p2,"32012");
    sistema->creaPrenotazione(p3,"20521");
    sistema->creaPrenotazione(p4,"20012");

    v1->EsigenzePart();


    sistema->CancellaPrenotazione(p3);

    sistema->RimuoviVolo(v2);


    return 0;
}