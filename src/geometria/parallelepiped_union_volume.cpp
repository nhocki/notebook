// Complexity: O(n^2 log n), where n is the number
// of boxes.
namespace BoxUnion {
    long long get_volume(const vector<Box> &r) {
        vector<int> z;
        for (int i = 0; i < r.size(); ++i) {
            z.push_back(r[i].z1);
            z.push_back(r[i].z2);
        }
        sort(z.begin(), z.end());
        z.resize(unique(z.begin(), z.end()) - z.begin());

        long long ans = 0;
        for (int i = 1; i < z.size(); ++i) {
            vector<Box> boxes; 
            for (int j = 0; j < r.size(); ++j) {
                if (r[j].z1 < z[i] and z[i] <= r[j].z2) {
                    boxes.push_back(r[j]);
                }
            }
            ans += RectangleUnion::get_area(boxes)*(z[i]-z[i-1]);
        }
        return ans;
    }
}
