// Finds the lexicographically smallest rotation of string s.
// Returns the index that should be moved to the first position
// to achieve the smallest rotation.
// If there are two or more smallest rotations, returns the
// smallest index.
int minimum_rotation(string s) {
    int n = s.size();
    s = s + s;
    int mini = 0, p = 1, k = 0;
    while (p < n && mini + k + 1 < n) {
        if (s[mini + k] == s[p + k]) {
            k++;
        } else if (s[mini + k] < s[p + k]) {
            p = p + k + 1;
            k = 0;
        } else if (s[mini + k] > s[p + k]){
            mini = max(mini + k + 1, p);
            p = mini + 1;
            k = 0;
        }
    }
    // the actual minimum rotated string is  s.substr(mini, n)
    return mini;
}