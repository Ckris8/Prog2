//inline inserisce i parametri del chiamante(da cercare)
//funzioni inline e no
//funzioni inline dal compilatore e non dal linker
//storage classes
    //static : viene conservato per tutte l'esecuzioni della funzione, viene allocato a inizio programma e deallocato alla fine
    //register
    //extern

//compilazione modulare

//funzioni template


//leggi 3 double in input e produci un piccolo report
//massimo minim0
//media double e media arrotontada int 

#include <iostream>

//#include "utility.h"

using namespace std;

double max(double a,double b,double c);
//double max(double a,double b,double c=0);//se il c non viene menzionato nella chiamata assegna ad esso il parametro di default
//il parametro di default devono essere inseriti come ultimi parametri della funzione
double max(double a,double b);
double min(double a,double b,double c); 
double min(double a,double b);
int media(double *valori, int n);
double media(const double *valori, int n);
enum ordine{tutti_uguali,crescente,decrescente,misto};
ordine classificazione(double a,double b, double c);




int main(){

    double A,B,C=0;

    cout<<"inserisci n1 valore double: ";
    cin >> A;
    cout << "il numero inserito e' " << A << endl;
    cout<<"inserisci n2 valore double: ";
    cin >> B;
    cout << "il numero inserito e' " << B << endl;
    cout<<"inserisci n3 valore double: ";
    cin >> C;
    cout << "il numero inserito e' " << C << endl;

    cout<<"report:"<<endl;
    cout<< "A: "<<A<< " B: "<<B<< " C: "<<C<<endl;

    cout << "il max dei 3 valori e': "<< max(A,B,C)<<endl;
    cout << "il min dei 3 valori e': "<< min(A,B,C)<<endl;

    double valori[]= {A,B,C};
    int n=sizeof(valori)/sizeof(valori[0]);
    cout << "la dimenzione dell'array e': "<< n << endl;
    double mediaA=media(valori,n);
    cout << "la media degli elementi dell'array e': "<< mediaA <<endl;

    double valI[]={static_cast<int>(A),static_cast<int>(B),static_cast<int>(C)};
    int mediaI= media(valI,n);

    ordine Ord =classificazione(A,B,C);
    cout<<"l'ordine dei numeri e': ";
    switch (Ord){
        case tutti_uguali:
            cout<< "Tutti uguali";
            break;
        case crescente:
            cout<< "Crescente";
            break;
        case decrescente:
            cout<< "decrescente";
            break;
        default:
            cout <<"Misto";
    }
    cout<<endl;
    


    bool almeno_uno_negativo = (A < 0.0) || (B <0.0) || (C <0.0);
    bool almeno_uno_negativo = (A < 0.0) || (B <0.0) || (C <0.0);
    cout << "almeno uno negativo: "<< endl;
    //completare


    cout << "il min dei 3 valori e': "<< minimo<double>(A,B)<<endl;//template
    //se non specifico il tipo osserva il tipo degli argomenti passati
    // se sono diversi va in errore
}


double max(double a,double b,double c){
    return max(a,max(b,c));
}

double max(double a,double b){
    if(a > b){
        return a;
    }else{
        return b;
    }
    
}
double min(double a,double b,double c){

    return min(a,min(b,c));
}

double min(double a,double b){
    if(a < b){
        return a;
    }else{
        return b;
    }
    
}

int arrotonda(double v){
    if(v>=0.0){
        return static_cast<int>(v+0.5);
    }else{
        return static_cast<int>(v-0.5);
    }
}

int media(double *valori, int n){
    double somma=0.0;

    for(int i =0; i<n;i++){
        somma += valori[i];
        //somma += *(valori+i);
    }

    //cast esplicito
    //static cast(tipo in cui convertire)
    return arrotonda(static_cast<double>(somma/n));
}

double media(const double *valori, int n){
    double somma=0.0;

    for(int i =0; i<n;i++){
        //cast esplicito
        //const cast
        const_cast<double*>(valori)[i] =0;
        somma += valori[i];
        //somma += *(valori+i);
    }

    
    return(somma/n);
}

ordine classificazione(double a,double b, double c){
    if(a==0.0&&b==0.0&&c==0.0){
        return tutti_uguali;
    }
    if(a<= b && b <= c){
        return crescente;
    }
    if(a >= b && b >= c){
        return misto;
    }
}

template <typename T>//funzione che accetta ogni tipi di dati
T minimo(T a,T b){
    return(a < b)? a : b;
}

