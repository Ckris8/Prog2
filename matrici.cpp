#include <iostream>

using namespace std;

class Matrice{
    public:
        Matrice(int r,int c):righe(r),colonne(c){
            M= new int*[righe];
            for(int i=0;i< righe;i++){
                M[i]= new int[colonne];
            }
        }
        //costruttore di copia
        Matrice(const Matrice& mtx) : righe(mtx.righe), colonne(mtx.colonne) {
            M = new int*[righe];
            for(int i = 0; i < righe; i++){
                M[i] = new int[colonne];
                for(int j = 0; j < colonne; j++){
                    M[i][j] = mtx.M[i][j];
                }
            }
        }

        ~Matrice(){
            for(int i=0;i<righe;i++){   
                    delete [] M[i];
            }
            delete [] M;
        }

        void acquisisci(){
            int num;
            cout<<"Inserisci i ("<<righe*colonne<<") elementi della matriche "<<righe<<"X"<<colonne<<" in sequenza:";
            for(int i=0;i<righe;i++){
                for(int j=0;j<colonne;j++){
                    cin>>num;
                    cin.get();
                    M[i][j]=num;
                }
            }
        }

        friend ostream& operator<<(ostream& out, const Matrice &mtx){
            for(int i=0;i<mtx.righe;i++){
                for(int j=0;j<mtx.colonne;j++){
                    out<<mtx.M[i][j]<<"\t";
                }
            out<<endl;
            }
            return out;
        }

        Matrice operator+(const Matrice& mtx){
            if(colonne==mtx.colonne&&righe==mtx.righe){
                Matrice C(righe,colonne);
                for(int i=0;i<righe;i++){
                    for(int j=0;j<colonne;j++){
                        C.M[i][j]= M[i][j]+mtx.M[i][j];
                    }
                }
                return C;
            }else{
                throw runtime_error("operazione non riuscita\nle colonne e righe devono essere ugual numero");
            }  
        }


        Matrice operator*(const Matrice& mtx){
            if(colonne==mtx.colonne&&righe==mtx.righe){
                Matrice C(righe,colonne);
                for(int i=0;i<righe;i++){
                    for(int j=0;j<colonne;j++){
                        C.M[i][j]= M[i][j]*mtx.M[i][j];
                    }
                }
                return C;
            }else{
                throw runtime_error("operazione non riuscita\nle colonne e righe devono essere ugual numero");
            }
        }


        Matrice& operator=(const Matrice& mtx){
            if(colonne==mtx.colonne&&righe==mtx.righe){
                for(int i=0;i<righe;i++){
                    for(int j=0;j<colonne;j++){
                        M[i][j]=mtx.M[i][j];
                    }
                }
                return *this;
            }else{
                throw runtime_error("operazione non riuscita\nle colonne e righe devono essere ugual numero");
            }
        }

    private:
        int righe;
        int colonne;
        int **M;
};

int main(){
    Matrice A(2,3);
    Matrice B(2,3);

    A.acquisisci();

    cout<<"Matrice A:"<<endl;
    cout<<A;

    B.acquisisci();

    cout<<"Matrice B:"<<endl;
    cout<<B;

    Matrice C(2,3);

    cout<<"C = A + B"<<endl;
    C=A+B;
    cout<<C;
    
    Matrice D(2,3);

    cout<<"D = (A * C)"<<endl;
    D=(A*C);
    cout<<D;


    return 0;
}