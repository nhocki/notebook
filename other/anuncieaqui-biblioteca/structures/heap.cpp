struct heap {
    int heap[MAXV][2], v2n[MAXV];
    int size;

    void init(int sz) __attribute__((always_inline)) {
        memset(v2n, -1, sizeof(int) * sz);
        size = 0;
    }

    void swap(int& a, int& b) __attribute__((always_inline)) {
        int temp = a;
        a = b;
        b = temp;
    }

    void s(int a, int b) __attribute__((always_inline)) {
        swap(v2n[heap[a][1]], v2n[heap[b][1]]);
        swap(heap[a][0], heap[b][0]);
        swap(heap[a][1], heap[b][1]);
    }

    int extract_min() {
        int ret = heap[0][1];
        s(0, --size);

        int cur = 0, next = 2;
        while(next < size) {
            if(heap[next][0] > heap[next - 1][0])
                next--;
            if(heap[next][0] >= heap[cur][0])
                break;

            s(next, cur);
            cur = next;
            next = 2*cur + 2;
        }
        if(next == size && heap[next - 1][0] < heap[cur][0])
            s(next - 1, cur);

        return ret;
    }

    void decrease_key(int vertex, int new_value) __attribute__((always_inline))
    {
        if(v2n[vertex] == -1) {
            v2n[vertex] = size;
            heap[size++][1] = vertex;
        }

        heap[v2n[vertex]][0] = new_value;

        int cur = v2n[vertex];
        while(cur >= 1) {
            int parent = (cur - 1)/2;
            if(new_value >= heap[parent][0])
                break;

            s(cur, parent);
            cur = parent;
        }
    }
};

