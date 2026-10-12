/*
============================================================
🏋️ Exercise 3: Query Palindrom O(1)
============================================================
Day: 216 | Difficulty: Medium
Topic: Konversi indeks pusat
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S dan Q pertanyaan. Setiap pertanyaan berisi sepasang
bilangan l dan r (1-based, inklusif), dan kamu harus menjawab apakah
substring S[l..r] merupakan palindrom.
Karena Q bisa sangat besar, setiap pertanyaan harus dijawab dalam O(1)
setelah preprocessing O(N). Menjalankan pengecekan naif per pertanyaan
akan TLE.

📥 INPUT FORMAT:
- Baris pertama: string S
- Baris kedua: Q
- Q baris berikutnya: masing-masing dua bilangan l dan r

📤 OUTPUT FORMAT:
- Q baris berisi "YES" atau "NO"

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- 1 <= Q <= 10^6
- 1 <= l <= r <= |S|

📎 SAMPLE INPUT 1:
abacaba
4
1 7
1 3
2 4
3 5

📎 SAMPLE OUTPUT 1:
YES
YES
NO
YES

💡 HINT: Pertanyaannya hanyalah "apakah radius di pusat (l, r) cukup panjang?"
         Cari tahu indeks pusat pada string tertransformasi. Petunjuk:
         huruf S[k] berada di indeks 2k+1 pada T. Turunkan titik tengahnya.

🎯 Learning Goals:
- [ ] Menurunkan rumus pusat = l + r + 1 sendiri, bukan menghafalnya
- [ ] Hati-hati konversi 1-based ke 0-based
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // TODO: preprocessing Manacher sekali

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        // TODO: konversi ke 0-based, hitung pusat, bandingkan radius
    }

    return 0;
}
