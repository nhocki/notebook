typedef complex<long double> pt;
pt tmp[1<<20];

void fft(pt *in, int sz, bool inv = false) {
    if(sz == 1) return;
    for(int i = 0; i < sz; i++)
        tmp[i] = in[i];

    sz /= 2;
    pt *even = in, *odd = in + sz;
    for(int i = 0; i < 2*sz; i++)
        if(i&1) odd[i/2] = tmp[i];
        else even[i/2] = tmp[i];

    fft(even, sz, inv);
    fft(odd, sz, inv);

    long double p = (inv ? 1 : -1) * acosl(-1)/sz;
    for(int i = 0; i < sz; i++) {
        pt conv = pt(cosl(i*p), sinl(i*p)) * odd[i];
        tmp[i] = even[i] + conv;
        tmp[i+sz] = even[i] - conv;
    }

    for(int i = 0; i < 2*sz; i++)
        in[i] = tmp[i];
}
