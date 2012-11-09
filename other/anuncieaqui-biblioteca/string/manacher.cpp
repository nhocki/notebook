vector<int> manacher(const string& s) {
    string s2 = "#";
    for(unsigned int i = 0; i < s.size(); i++)
        s2 += s[i], s2 += '#';

    int c = 1, sz = (int)s2.size(), j;
    vector<int> ans(sz);
    while(c < sz) {
        while(c > ans[c] && c+ans[c]+1 < sz && s2[c-ans[c]-1] == s2[c+ans[c]+1])
            ans[c]++;

        j = 1;
        while(c+j < sz && j < ans[c]-ans[c-j])
            ans[c+j] = ans[c-j], j++;
        if(c+j < sz)
            ans[c+j] = ans[c]-j;
        c += j;
    }

    return ans;
}
