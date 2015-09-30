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

#include "treap.cpp"

// test begins here

const int MAXN = 100;
vector<int> a;
Node * root;

vector<int> extract(Node * t) {
    if (t == null) return vector<int>();
    vector<int> ans = extract(t->l);
    ans.push_back(t->x);
    vector<int> right = extract(t->r);
    ans.insert(ans.end(), right.begin(), right.end());
    return ans;
}

void traverse(Node * p, int depth = 0) {
    if (p == null) return;
    for (int i = 0; i < depth; ++i) printf(" "); traverse(p->l, depth + 1);
    for (int i = 0; i < depth; ++i) printf(" "); printf("%d\n", p->x);
    for (int i = 0; i < depth; ++i) printf(" "); traverse(p->r, depth + 1);
}


void test_split() {
    puts("testing split...");
    for (int k = 0; k < 20; ++k) {

        int x;
        if (k % 2 == 0) {
            x = rand();
        } else {
            x = a[rand() % a.size()];
        }

        Node * A, * B;
        split(root, x, A, B);
        vector<int> left = extract(A);
        vector<int> right = extract(B);
        for (int i = 0; i < left.size(); ++i) {
            assert(left[i] <= x);
        }
        for (int i = 0; i < right.size(); ++i) {
            assert(right[i] > x);
        }
        root = merge(A, B);
    }
}

void test_insert() {
    puts("testing insert...");
    for (int k = 0; k < 10; ++k) {
        int x = rand();
        root = insert(root, new Node(x));
        a.push_back(x);
        sort(a.begin(), a.end());
        assert( extract(root) == a );
    }

    int repeated = a[rand() % a.size()];
    for (int i = 0; i < 10; ++i) {
        root = insert(root, new Node(repeated));
        a.push_back(repeated);
        sort(a.begin(), a.end());
        assert( extract(root) == a );
    }
}

void test_erase() {
    puts("testing erase...");
    for (int k = 0; k < 10; ++k) {
        int at = rand() % a.size();
        root = erase(root, a[at]);
        a.erase(a.begin() + at);
        sort(a.begin(), a.end());
        assert( extract(root) == a );
    }
}

void test_find() {
    puts("testing find...");
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); ++i) {
        Node * node = find(root, a[i]);
        assert(node != null);
        assert(node->x == a[i]);
    }
    for (int k = a.back() + 1; k < a.back() + 1 + 10; ++k) {
        assert( find(root, k) == null );
    }
}

void test_find_kth() {
    puts("testing find_kth...");
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); ++i) {
        Node * node = find_kth(root, i);
        assert(node != null);
        assert(node->x == a[i]);
    }
    for (int k = a.back() + 1; k < a.back() + 1 + 10; ++k) {
        assert( find_kth(root, k) == null );
    }
}

void test_sum() {
    puts("testing sum...");
    for (int i = 0; i < 10; ++i) {
        int x = a[rand() % a.size()];

        long long brute_sum = 0;
        for (int i = 0; i < a.size(); ++i) if (a[i] <= x) brute_sum += a[i];
        assert(sum(root, x) == brute_sum);
    }
}

int get_depth(Node * t) {
    if (t == null) return 0;
    return max(get_depth(t->l), get_depth(t->r)) + 1;
}

void free_memory(Node * node) {
    if (node == null) return;
    free_memory(node->l);
    free_memory(node->r);
    delete node;
}

void test_inserting_many_equal_elements() {
    puts("Testing inserting many equal elements...");
    Node * new_tree = null;
    int n = 100000;
    for (int i = 0; i < n; ++i) {
        new_tree = insert(root, new Node(1337));
    }
    int depth = get_depth(new_tree);
    int perfect_depth = ceil(log2(n));

    D(depth);
    D(perfect_depth);
    int difference = depth - perfect_depth;
    D(difference);
    assert(difference <= 25);
    free_memory(new_tree);
}

int main(){
    int seed = time(NULL);
    printf("Random seed = %d\n", seed);
    srand(seed);

    root = null;
    for (int i = 0; i < 3000; ++i) {
        a.push_back(rand());
        root = insert(root, new Node(a[i]));
    }
    test_split();
    test_insert();
    test_erase();
    test_find();
    test_find_kth();
    test_sum();
    test_inserting_many_equal_elements();
    printf("Everything OK (random seed = %d).\n", seed);
    return 0;
}
