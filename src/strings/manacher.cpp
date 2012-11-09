// Complejidad: O(n)
void manacher(const string &s) {
    int n = s.size();
    
    vector<int> d1(n);
    int l=0, r=-1;
    for (int i=0; i<n; ++i) {
        int k = (i>r ? 0 : min (d1[l+r-i], r-i)) + 1;
        while (i+k < n && i-k >= 0 && s[i+k] == s[i-k]) ++k;
        d1[i] = --k;
        if (i+k > r) l = i-k, r = i+k;
    }
    vector<int> d2(n);
    l=0, r=-1;
    for (int i=0; i<n; ++i) {
        int k = (i>r ? 0 : min (d2[l+r-i+1], r-i+1)) + 1;
        while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k]) ++k;
        d2[i] = --k;
        if (i+k-1 > r) l = i-k, r = i+k-1;
    }
    
    // d1[i] = piso de la mitad de la longitud del palíndromo
    //         impar más largo cuyo centro es i.
    // d2[i] = mitad de la longitud del palíndromo par más
    //         largo cuyo centro de la derecha es i.
    
    for (int i = 0; i < n; ++i) {
        assert(is_palindrome( s.substr(i - d1[i], 2*d1[i] + 1) ));
        assert(is_palindrome( s.substr(i - d2[i], 2*d2[i])     ));
        
    }    
}