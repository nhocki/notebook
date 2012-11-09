#define MAXE 100052
#define MAXV 105000

#include <queue>
#include <iostream>
#include <string>
#include <map>
#include <cstring>
 
using namespace std;

#include "../structures/heap.cpp"
#include "../graph/dijkstra_sparse_fast.cpp"

map<string, int> idiomas; int numIdiomas;
int cod(string s)
{
    if(idiomas.find(s) == idiomas.end()) idiomas[s] = numIdiomas++;
    return idiomas[s];
}

struct triple
{
    int orig, dest; char c;
    triple() { }
    triple(int orig, int dest, char c) : orig(orig), dest(dest), c(c) { }
    bool operator<(triple t) const
    {
        if(orig < t.orig) return true;
        if(orig == t.orig && dest < t.dest) return true;
        if(orig == t.orig && dest == t.dest && c < t.c) return true;
        return false;
    }
};

int main()
{
    int M;
    while(cin >> M && M != 0)
    {
        idiomas.clear(); numIdiomas = 0;
        d_init();

        string origem, destino, palavra;
        cin >> origem >> destino;
        int corigem = cod(origem), cdestino = cod(destino);

        map<triple, int> entradas;
        for(int i = 0; i < M; i++)
        {
            cin >> origem >> destino >> palavra;
            int dorigem = cod(origem), ddestino = cod(destino);
            if(dorigem > ddestino) swap(dorigem, ddestino);

            if(entradas[triple(dorigem, ddestino, palavra[0])] == 0)
                entradas[triple(dorigem, ddestino, palavra[0])] = palavra.size();
            else
                entradas[triple(dorigem, ddestino, palavra[0])] = min(entradas[triple(dorigem, ddestino, palavra[0])], (int)palavra.size());
        }

        for(map<triple, int>::iterator it = entradas.begin(); it != entradas.end(); it++)
        {
            triple atual = (*it).first;
            for(int c = 0; c < 26; c++)
                if(c != atual.c - 'a')
                {
                    d_edge(atual.orig*26 + c, atual.dest*26 + (atual.c - 'a'), (*it).second);
                    d_edge(atual.dest*26 + c, atual.orig*26 + (atual.c - 'a'), (*it).second);
                }
        }

        int source = numIdiomas * 26, sink = numIdiomas * 26 + 1;
        for(int i = 0; i < 26; i++)
        {
            d_edge(source, corigem * 26 + i, 0);
            d_edge(cdestino * 26 + i, sink, 0);
        }

        dijkstra(source, numIdiomas * 26 + 2);
        if(dist[sink] >= 0x3f3f3f3f) cout << "impossivel" << endl;
        else cout << dist[sink] << endl;
    }
}
