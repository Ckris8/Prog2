#include <iostream>
#include <string>

using namespace std;

template <typename T>

T min(T a,T b){
    if(a<=b){
        return a;
    }else{return b;}
}


class OraDelGiorno{
    public:
        OraDelGiorno(int h,int m, int s) : h_(h),m_(m),s_(s){}

        bool operator==(const OraDelGiorno& other) const;
        friend ostream& operator <<(ostream& s,const OraDelGiorno& o);
    private: 
        int h_;
        int m_;
        int s_;
}
//overloading per cout 
ostream& operator<<(ostream& s, const OraDelGiorno& o)
{
    s << o.h_ << ":" << o.m_ << ":" << o.s_;
    return s;
}


template <typename T>
class arrayDinamico{
    public:
        arrayDinamico(int n);

        T getN(int i) const;

        void set(int i,T v);

        void resize(int n);

        ~arrayDinamico();

    private:
        int n_;
        T* array_;
}

int main(){
    string a="A";
    string b="B";

    int n=2;

    arrayDinamico<string> array(n);
    array.set(0,"pippo");
    array.set(1,"pappo");

    for(int i=0; i<n;i++){
        cout<<array.get(i)<<endl;
    }

    cout << min<string>(a,b) <<endl;

    OraDelGiorno o1(2,34,0);
    OraDelGiorno o2(3,35,0);

    cout << (o1 == o2) << endl;

    ((cout << o1) << " ") << endl;

    return 0;
}


arrayDinamico<T>::~arrayDinamico(){
    delete [] array_;
}


template <typename T>//nel caso si usa il tipo template si deve ricordare
void arrayDinamico<T>::arrayDinamico(int n){

    array_= new T[n];
    n_=n;
}

template <typename T>
void arrayDinamico<T>::resize(int n){
    T* newarray = new T[n];
    //copia elementi da newarray ad array_
    delete [] array_;
    array_= newarray;
    n_=n;
}

template <typename T>
void arrayDinamico<T>::get(int n){
    return array_[n];
}

template <typename T>
void arrayDinamico<T>::set(int i,T v){
    array_[i]= v;
}


//dichiarazione overloading
bool OraDelGiorno::operator==(const OraDelGiorno& other) const
{
    return ((h_ == other.h_) && (m_ == other.m_) && (s_ == other.s_));
}

