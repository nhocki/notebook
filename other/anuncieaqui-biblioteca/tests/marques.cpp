#include <queue>
#include <map>
#include <iostream>
#include <cstring>

using namespace std;

#define MAXV 500
#define MAXE 500*500

#include "../graph/edmonds_karp.cpp"

int main()
{
    int n; cin >> n; string str;
    for(int z = 0; z < n; z++)
    {
        ek_init();

        int onibus, pessoas; cin >> pessoas >> onibus;
        map<string, vector<int> > bus2ind; int ind = 0;
        for(int i = 0; i < onibus; i++)
        {
            cin >> str;
            bus2ind[str].push_back(ind++);
        }

        for(int i = 0; i < pessoas; i++)
        {
            int k; cin >> k;
            ek_edge(0, i + 1, 1);
            for(int j = 0; j < k; j++)
            {
                cin >> str;
                for(int l = 0; l < (int)bus2ind[str].size(); l++)
                    ek_edge(i + 1, pessoas + 1 + bus2ind[str][l], 1);
            }
        }

        for(int i = 0; i < onibus; i++)
            ek_edge(pessoas + 1 + i, pessoas + onibus + 1, 1);

        int cur_flow = 0;
        for(int i = 1; i <= 100; i++)
        {
            for(int j = 0; j < onibus; j++)
                cap[last_edge[pessoas + 1 + j]] = i;

            cur_flow += edmonds_karp(0, pessoas + onibus + 1, pessoas + onibus + 2);
            if(cur_flow == pessoas)
            {
                cout << i << endl;
                break;
            }
        }
    }
}

