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