vector<int> lis(vector<int>& seq) {
    int smallest_end[seq.size()+1], prev[seq.size()];
    smallest_end[1] = 0;

    int sz = 1;
    for(int i = 1; i < seq.size(); ++i) {
        int lo = 0, hi = sz;
        while(lo < hi) {
            int mid = (lo + hi + 1)/2;
            if(seq[smallest_end[mid]] <= seq[i])
                lo = mid;
            else
                hi = mid - 1;
        }

        prev[i] = smallest_end[lo];
        if(lo == sz)
            smallest_end[++sz] = i;
        else if(seq[i] < seq[smallest_end[lo+1]])
            smallest_end[lo+1] = i;
    }

    vector<int> ret;
    for(int cur = smallest_end[sz]; sz > 0; cur = prev[cur], --sz)
        ret.push_back(seq[cur]);
    reverse(ret.begin(), ret.end());

    return ret;
}
