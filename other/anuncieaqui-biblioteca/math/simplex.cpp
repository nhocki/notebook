const double EPS = 1e-9;
typedef long double T;
typedef vector<T> VT;
vector<VT> A;
VT b,c,res;
VI kt,N;
int m;
inline void pivot(int k,int l,int e){
    int x=kt[l]; T p=A[l][e];
    REP(i,k) A[l][i]/=p; b[l]/=p; N[e]=0;
    REP(i,m) if (i!=l) b[i]-=A[i][e]*b[l],A[i][x]=A[i][e]*-A[l][x];
    REP(j,k) if (N[j]){
        c[j]-=c[e]*A[l][j];
        REP(i,m) if (i!=l) A[i][j]-=A[i][e]*A[l][j];
    }
    kt[l]=e; N[x]=1; c[x]=c[e]*-A[l][x];
}

VT doit(int k){
    VT res; T best;
    while (1){
        int e=-1,l=-1; REP(i,k) if (N[i] && c[i]>EPS) {e=i; break;}
        if (e==-1) break;
        REP(i,m) if (A[i][e]>EPS && (l==-1 || best>b[i]/A[i][e]))
            best=b[ l=i ]/A[i][e];
        if (l==-1) /*ilimitado*/ return VT();
        pivot(k,l,e);
    }
    res.resize(k,0); REP(i,m) res[kt[i]]=b[i];
    return res;
}

VT simplex(vector<VT> &AA,VT &bb,VT &cc){
    int n=AA[0].size(),k;
    m=AA.size(); k=n+m+1; kt.resize(m); b=bb; c=cc; c.resize(n+m);
    A=AA; REP(i,m){ A[i].resize(k); A[i][n+i]=1; A[i][k-1]=-1; kt[i]=n+i;}
    N=VI(k,1); REP(i,m) N[kt[i]]=0;
    int pos=min_element(ALL(b))-b.begin();
    if (b[pos]<-EPS){
        c=VT(k,0); c[k-1]=-1; pivot(k,pos,k-1); res=doit(k);
        if (res[k-1]>EPS) /*impossivel*/ return VT();
        REP(i,m) if (kt[i]==k-1)
            REP(j,k-1) if (N[j] && (A[i][j]<-EPS || EPS<A[i][j])){
                pivot(k,i,j); break;
            }
        c=cc; c.resize(k,0); REP(i,m) REP(j,k) if (N[j]) c[j]-=c[kt[i]]*A[i][j];
    }
    res=doit(k-1); if (!res.empty()) res.resize(n);
    return res;
}
