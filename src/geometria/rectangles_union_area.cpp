// Complexity: O(n log n), where n is the number
// of rectangles.

// Usage:
// - Set the MAXN variable below to be big enough.
// - Run RectangleUnion::get_area(vector<Box> r) with
//   the rectangles. This will return the area of their
//   union.

struct Box {
   long long x1, x2, y1, y2, z1, z2;

   Box(){}
   Box(long long _x1, long long _x2, long long _y1,
   long long _y2, long long _z1 = 0, long long _z2 = 0) {
      x1 = min(_x1, _x2);
      x2 = max(_x1, _x2);
      y1 = min(_y1, _y2);
      y2 = max(_y1, _y2);
      z1 = min(_z1, _z2);
      z2 = max(_z1, _z2);
   }
};


namespace RectangleUnion {
   struct Event {
      enum { OUT, IN };
      int at, y1, y2, type;
      Event(int at, int y1, int y2, int type) : at(at), 
         y1(y1), y2(y2), type(type) {}

      bool operator < (const Event &t) const {
         if (at != t.at) return at < t.at;
         return type < t.type;
      }
   };

   vector<int> y;

   namespace SegmentTree {
        // For every rectangle we need two places in the
        // segment tree. If the segment tree has N places,
        // its size must be at least twice the first power
        // of two greater than or equal to N.
        // A safe value is 8 times the maximum number of
        // rectangles, because this always satisfies the
        // constraints above.
      const int MAXN = 8 * 55;
      long long sum[MAXN];
      int add[MAXN];

      void clear() {
         memset(sum, 0, sizeof sum);
         memset(add, 0, sizeof add);
      }

      void refresh(int u, int l, int r) {
         sum[u] = 0;
         if (add[u] > 0) sum[u] = y[r + 1] - y[l];
         else if (l < r) sum[u] = sum[2*u+1] + sum[2*u+2];
      }

      void update(int u, int l, int r, int p, int q, int what) {
         if (q < l or r < p) return; // outside
         p = max(p, l);
         q = min(q, r);
         if (l == p and q == r) {
            add[u] += what;
         } else {
            int m = (l + r) / 2;
            update(2*u+1, l, m,  p, q, what);
            update(2*u+2, m+1, r, p, q, what);
         }
         refresh(u, l, r);
      }
   };

    // Returns the area covered by the given rectangles.
    // All z values are ignored; we only consider the
    // rectangles formed by the x and y values in each
    // box (hence, we are finding the area covered by
    // all the projections of each box onto the z = 0
    // plane).
   long long get_area(const vector<Box> &r) {
      y.clear();
      for (int i = 0; i < r.size(); ++i) {
         y.push_back(r[i].y1);
         y.push_back(r[i].y2);
      }
      sort(y.begin(), y.end());
      y.resize(unique(y.begin(), y.end()) - y.begin());

      vector<Event> events;
      for (int i = 0; i < r.size(); ++i) {
            // discard empty rectangle
         if (r[i].x1 >= r[i].x2 or r[i].y1 >= r[i].y2) continue;
         events.push_back(Event(r[i].x1, r[i].y1, r[i].y2,
                                Event::IN));
         events.push_back(Event(r[i].x2, r[i].y1, r[i].y2,
                                Event::OUT));
      }
      sort(events.begin(), events.end());

      SegmentTree::clear();

      long long previous_length = 0, ans = 0;
      for (int i = 0; i < events.size(); ++i) {
         if (i > 0) {
            int advanced = events[i].at - events[i - 1].at;
            ans += previous_length * advanced;
         }

         int p = lower_bound(y.begin(), y.end(), events[i].y1)
                 - y.begin();
         int q = lower_bound(y.begin(), y.end(), events[i].y2)
                 - y.begin();
         assert(p < q);

         if (events[i].type == Event::IN) {
            SegmentTree::update(0, 0, y.size()-2, p, q-1, +1);
         } else {
            SegmentTree::update(0, 0, y.size()-2, p, q-1, -1);
         }
         // update to current value for next iteration
         previous_length = SegmentTree::sum[0];
      }
      return ans;
   }
}
