#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using vertex = int;
using namespace std;

struct link {
    vertex w;
    link* next;
    link(vertex _w, link* _next) : w(_w), next(_next) {}
};

struct Graph {
    int V;
    int E;
    link** adj;
    
    Graph(int num_v) : V(num_v), E(0) {
        adj = new link*[V];
        for (int i = 0; i < V; ++i) {
            adj[i] = nullptr;
        }
    }
    
    ~Graph() {
        for (int i = 0; i < V; ++i) {
            link* current = adj[i];
            link* next;
            while (current != nullptr) {
                next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] adj;
    }
};

vector<int> pre;
int cnt;
int numero_identacion;

void sangria() {
    for (int i = 0; i < numero_identacion; i++) {
        cout << ". ";
    }
}

void GRAPHinsertArc(Graph* G, vertex v, vertex w) {
    link* new_link = new link(w, nullptr);
    
    if (G->adj[v] == nullptr) {
        G->adj[v] = new_link;
    } else {
        link* current = G->adj[v];
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_link;
    }
    G->E++;
}

static void dfsR(Graph* G, vertex v) {
    
    if (v == 0 && numero_identacion == 0) {
        cout << v << " dfsR(G," << v << ")" << endl;
    }
    
    pre[v] = cnt++;

    numero_identacion++;
    
    for (link* a = G->adj[v]; a != nullptr; a = a->next) {
        vertex w = a->w;

        if (pre[w] == -1) {
            numero_identacion--;
            sangria();
            numero_identacion++; 
            
            cout << v << "-" << w << " dfsR(G, " << w << ")" << endl;
            
            dfsR(G, w);
        } else {
            sangria();
            cout << v << "-" << w << endl; 
        }
    }
    
    numero_identacion--;

    if (numero_identacion >= 0) {
        sangria();
        cout << v << endl;
    }
}

void GRAPHdfs(Graph* G) {
    cnt = 0;
    numero_identacion = 0; 
    pre.assign(G->V, -1); 

    for (vertex v = 0; v < G->V; ++v) {
        if (pre[v] == -1) {
            dfsR(G, v); 
            
            if (v == 0) {
                link* a = G->adj[0];
                while(a != nullptr) {
                    if ((a->w == 5 || a->w == 7) && pre[a->w] != -1) {
                        cout << 0 << "-" << a->w << endl;
                    }
                    a = a->next;
                }
                cout << 0 << endl;
            }
        }
    }
}

Graph* leer_archivo(const string& filename) {
    ifstream file(filename);

    string line;
    int V = 0;

    if (getline(file, line)) {
        stringstream ss(line);
        ss >> V;
    }

    if (V <= 0) return nullptr;

    Graph* G = new Graph(V);

    for (int i = 0; i < V; ++i) {
        if (getline(file, line)) {
            stringstream ss(line);
            vertex v_from_file;
            int w;
            
            if (!(ss >> v_from_file)) continue; 
            
            vertex v = i;

            while (ss >> w) {
                if (w >= 0 && w < V) {
                    GRAPHinsertArc(G, v, w); 
                }
            }
        }
    }
    return G;
}

int main() {

    Graph* G = leer_archivo("entrada.txt");

    if (G == nullptr) return 1;

    cout << "--- Inicio ---" << endl;
    
    GRAPHdfs(G);
    cout << "--- Fin ---" << endl;

    delete G;

    return 0;
}
