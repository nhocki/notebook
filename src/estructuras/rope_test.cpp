// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <bitset>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

#define D(x) cout << #x " is " << (x) << endl

#include "rope.cpp"

// test begins here

const int MAXN = 100;
vector<int> a;
Node * root;

void test_sum() {
    puts("Testing complete sum...");
    long long sum = 0;
    for (int i = 0; i < a.size(); ++i) sum += a[i];
    assert(sum == root->sum);
}

void test_sums() {
    puts("Testing fragment sum...");
    for (int k = 0; k < 50; ++k) {
        int l = rand() % a.size();
        int r = rand() % a.size();
        if (r < l) swap(l, r);

        long long sum = 0;
        for (int i = l; i <= r; ++i) {
            sum += a[i];
        }
        
        Node * A, * B, * C;
        split(root, l - 1, A, B);
        split(B, r - l, B, C);
        
        assert(sum == B->sum);
        root = merge(A, merge(B, C));
    }
}

void test_find() {
    vector<int> p(a.size());
    for (int i = 0; i < a.size(); ++i) p[i] = i;
    random_shuffle(p.begin(), p.end());
    puts("Testing find...");
    for (int i = 0; i < a.size(); ++i) {
        int index = p[i];
        assert( a[index] == find(root, index)->payload );
    }
}

void test_split() {
    puts("testing split...");
    for (int i = 0; i < 10; ++i) {
        assert(a.size() == root->size);
        int k = rand() % a.size();

        Node * A, * B;
        split(root, k, A, B);
        
        assert((A ? A->size : 0) == k + 1);
        
        for (int i = 0; i <= k; ++i) assert(a[i] == find(A, i)->payload );

        assert((B ? B->size : 0) == a.size() - (k + 1));
        for (int i = k + 1; i < a.size(); ++i) assert(a[i] == find(B, i - (k + 1))->payload );
        root = merge(A, B);
    }

}

void test_insert() {
    puts("testing insert...");
    for (int k = 0; k < 10; ++k) {
        int at = rand() % (a.size() + 1);
        int new_val = rand();
        a.insert(a.begin() + at, new_val);
        root = insert(root, new Node(new_val), at);
        test_sum();
        test_sums();
        test_find();
        test_split();
    }
    
    int new_val = rand();
    root = insert(root, new Node(new_val), a.size());
    a.insert(a.end(), new_val);
    test_sum();
    test_sums();
    test_find();
    test_split();
    
    new_val = rand();
    root = insert(root, new Node(new_val), 0);
    a.insert(a.begin(), new_val);
    test_sum();
    test_sums();
    test_find();
    test_split();
}

void test_erase() {
    puts("testing erase...");
    for (int k = 0; k < 10; ++k) {
        int at = rand() % a.size();
        a.erase(a.begin() + at);
        root = erase(root, at);
        test_sum();
        test_sums();
        test_find();
        test_split();
    }

    root = erase(root, a.size() - 1);
    a.erase(a.begin() + a.size() - 1);
    test_sum();
    test_sums();
    test_find();
    test_split();
    
    root = erase(root, 0);
    a.erase(a.begin() + 0);
    test_sum();
    test_sums();
    test_find();
    test_split();
}

void test_reverse() {
    puts("testing reverse...");
    for (int k = 0; k < 10; ++k) {
        int l = rand() % a.size();
        int r = rand() % a.size();
        if (r < l) swap(l, r);

        Node * A, * B, * C;
        split(root, l - 1, A, B);
        split(B, r - l, B, C);
        
        assert(!B->pending_reversal);
        B->pending_reversal = true;
        root = merge(A, merge(B, C));
        
        reverse(a.begin() + l, a.begin() + r + 1);
        
        test_find();
        test_sum();
        test_sums();
        test_split();
    }
}

int main(){
    int seed = time(NULL);
    printf("Random seed = %d\n", seed);
    srand(seed);
    
    root = null;
    for (int i = 0; i < 3000; ++i) {
        a.push_back(rand());
        root = merge(root, new Node(a[i]));
    }
    test_sum();
    test_sums();
    test_find();
    test_insert();
    test_split();
    test_erase();
    test_reverse();
    printf("Everything OK (random seed = %d).\n", seed);
    return 0;
}
