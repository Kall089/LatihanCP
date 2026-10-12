/*
============================================================
✅ Solution 6: Sliding Window Distinct Count
============================================================
Approach: Sliding window + frequency map
Complexity: Time O(N log N) | Space O(N)
Key Insight: Maintain frequency map untuk window saat ini.
             Saat geser: tambah elemen baru, hapus elemen lama.
             map.size() = jumlah distinct di window.

📖 PENJELASAN PENDEKATAN:
1. Baca array
2. Inisialisasi window pertama [0..K-1]: masukkan ke freq map
3. Output freq.size() untuk window pertama
4. Untuk setiap posisi baru i dari K sampai N-1:
   a. Tambah arr[i]: freq[arr[i]]++
   b. Hapus arr[i-K]: freq[arr[i-K]]--, jika 0 → erase key
   c. Output freq.size()

🔄 ALTERNATIVE APPROACHES:
- Unordered_map: O(N) average (lebih cepat, tapi constant factor)
- Segment tree: overkill untuk problem ini
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    map<int, int> freq;

    // Inisialisasi window pertama [0..K-1]
    for (int i = 0; i < k; i++) {
        freq[a[i]]++;
    }
    cout << freq.size();

    // Slide window
    for (int i = k; i < n; i++) {
        // Tambah elemen baru (masuk window)
        freq[a[i]]++;

        // Hapus elemen lama (keluar window)
        freq[a[i - k]]--;
        if (freq[a[i - k]] == 0) {
            freq.erase(a[i - k]);
        }

        cout << ' ' << freq.size();
    }
    cout << '\n';

    return 0;
}
