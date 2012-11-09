struct No {
    int fail;
    vector< pair<int,int> > out; // num e tamanho do padrao
    //bool marc;  // p/ decisao
    map<char, int> lista;
    int next; // aponta para o proximo sufixo que tenha out.size > 0
};
No arvore[1000003]; // quantida maxima de nos
//bool encontrado[1005]; // quantidade maxima de padroes, p/ decisao
int qtdNos, qtdPadroes;

// Funcao para inicializar
void inic() {
    arvore[0].fail = -1;
    arvore[0].lista.clear();
    arvore[0].out.clear();
    arvore[0].next = -1;
    qtdNos = 1;
    qtdPadroes = 0;
    //arvore[0].marc = false; // p/ decisao
    //memset(encontrado, false, sizeof(encontrado)); // p/ decisao
}

// Funcao para adicionar um padrao
void adicionar(char *padrao) {
    int no = 0, len = 0;
    for (int i = 0 ; padrao[i] ; i++, len++) {
        if (arvore[no].lista.find(padrao[i]) == arvore[no].lista.end()) {
            arvore[qtdNos].lista.clear(); arvore[qtdNos].out.clear();
            //arvore[qtdNos].marc = false; // p/ decisao
            arvore[no].lista[padrao[i]] = qtdNos;
            no = qtdNos++;
        } else no = arvore[no].lista[padrao[i]];
    }
    arvore[no].out.push_back(pair<int,int>(qtdPadroes++,len));
}

// Ativar Aho-corasick, ajustando funcoes de falha
void ativar() {
    int no,v,f,w;
    queue<int> fila;
    for (map<char,int>::iterator it = arvore[0].lista.begin();
         it != arvore[0].lista.end() ; it++) {
        arvore[no = it->second].fail = 0;
        arvore[no].next = arvore[0].out.size() ? 0 : -1;
        fila.push(no);
    }
    while (!fila.empty()) {
        no = fila.front(); fila.pop();
        for (map<char,int>::iterator it=arvore[no].lista.begin();
             it!=arvore[no].lista.end(); it++) {
            char c = it->first;
            v = it->second;
            fila.push(v);
            f = arvore[no].fail;
            while (arvore[f].lista.find(c) == arvore[f].lista.end()) {
                if (f == 0) { arvore[0].lista[c] = 0; break; }
                f = arvore[f].fail;
            }
            w = arvore[f].lista[c];
            arvore[v].fail = w;
            arvore[v].next = arvore[w].out.size() ? w : arvore[w].next;
        }
    }
}

// Buscar padroes no aho-corasik
void buscar(char *input) {
    int v, no = 0;
    for (int i = 0 ; input[i] ; i++) {
        while (arvore[no].lista.find(input[i]) == arvore[no].lista.end()) {
            if (no == 0) { arvore[0].lista[input[i]] = 0; break; }
            no = arvore[no].fail;
        }
        v = no = arvore[no].lista[input[i]];
        // marcar os encontrados
        while (v != -1 /* && !arvore[v].marc */ ) { // p/ decisao
            //arvore[v].marc = true; // p/ decisao: nao continua a lista
            for (int k = 0 ; k < arvore[v].out.size() ; k++) {
                //encontrado[arvore[v].out[k].first] = true; // p/ decisao
                printf("Padrao %d na posicao %d\n", arvore[v].out[k].first,
                       i-arvore[v].out[k].second+1);
            }
            v = arvore[v].next;
        }
    }
    // for (int i = 0 ; i < qtdPadroes ; i++)
    //printf("%s\n", encontrado[i]?"y":"n"); // p/ decisao
}
