/*
============================================================
✅ Solution 2: Word Frequency (Map)
============================================================
Approach: map<string, int> frequency counter
Complexity: Time O(N log N) | Space O(N)
Key Insight: map otomatis sorted by key, jadi iterasi langsung
             menghasilkan output yang terurut lexicographic.

📖 PENJELASAN PENDEKATAN:
1. Baca kata satu per satu
2. freq[word]++ untuk setiap kata
3. Iterasi map (otomatis sorted) dan output

🔄 ALTERNATIVE APPROACHES:
- unordered_map + sort keys: O(N) counting + O(K log K) sort (K = unique words)
- vector<pair<string,int>> + sort: lebih manual
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    map<string, int> freq;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        freq[word]++;
    }

    for (auto& [word, count] : freq) {
        cout << word << ' ' << count << '\n';
    }

    return 0;
}
