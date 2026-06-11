#include <iostream>

using namespace std;

class Grafo;

class Edge 
{
private:
    // costruttore privato: solo Grafo puo' creare archi
    Edge(int val, Edge* next) : next(next), target(val) {}
public: 
    int getVal() const {return target;}
    Edge* getNext() {return next;}
private:
    Edge* next;
    int target;

    friend class Grafo;
};

class Grafo
{
private:
    enum Color {white, gray, black};
public:
    Grafo(int nNodes)
        : color_(nullptr), d_(nullptr), f_(nullptr),
          pred_(nullptr), time_(0), nNodes_(nNodes)
    {
        adj_ = new Edge*[nNodes];
        for (int i=0; i<nNodes; i++)
            adj_[i] = nullptr;
    }
    ~Grafo() {
        // elimina le liste di adiacenza
        for (int i=0; i<nNodes_; i++) {
            Edge* e = adj_[i];
            while (e != nullptr) {
                Edge* tmp = e;
                e = e->getNext();
                delete tmp;
            }
        }
        delete [] adj_;
        // disalloca le strutture dati della DFS
        delete [] color_;
        delete [] d_;
        delete [] f_;
        delete [] pred_;
    }

    Grafo& addEdge(int source, int target) {
        if (source >= nNodes_ || target >= nNodes_)
            return *this;
        Edge* edge = new Edge(target, adj_[source]);
        adj_[source] = edge;
        return *this;
    }
    //Grafo& removeEdge(int source, int target);

    void DFS()
    {
        // alloca le strutture solo la prima volta
        if (color_ == nullptr) {
            color_ = new Color[nNodes_];
            d_ = new int[nNodes_];
            f_ = new int[nNodes_];
            pred_ = new int[nNodes_];
        }
        // inizializza tutti i nodi
        for (int i=0; i<nNodes_; i++) {
            color_[i] = white;
            d_[i] = 0;
            f_[i] = 0;
            pred_[i] = -1;   // -1 = nessun predecessore
        }
        time_ = 1;
        // visita ogni nodo non ancora scoperto
        for (int i=0; i<nNodes_; i++)
            if (color_[i] == white)
                DFS_Visit(i);
    }

private:
    void DFS_Visit(int u)
    {
        d_[u] = time_++;
        color_[u] = gray;
        cout << "Visito nodo " << u << endl;
        for (Edge* e = adj_[u]; e != nullptr; e = e->getNext()) {
            int v = e->getVal();
            if (color_[v] == white) {
                pred_[v] = u;
                DFS_Visit(v);
            }
        }
        color_[u] = black;    // nodo completato
        f_[u] = time_++;        // tempo di fine
    }

    Color* color_;
    int* d_;      // tempi di scoperta
    int* f_;      // tempi di fine
    int* pred_;   // predecessori
    int time_;
    int nNodes_;
    Edge** adj_;
};

int main() 
{
    Grafo g(5);
    g.addEdge(0,1).addEdge(0,2).addEdge(1,3).addEdge(2,3).addEdge(3,4);
    g.DFS();
    return 0;
}
