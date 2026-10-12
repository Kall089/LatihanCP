/*
============================================================
🏋️ Exercise 3: Border dan Periode dari Z
============================================================
Day: 215 | Difficulty: Medium
Topic: z[i] == n - i
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang N, kerjakan tiga hal sekaligus:
1. Cetak semua panjang border S, terurut MENAIK (border = string non-kosong
   yang merupakan awalan sekaligus akhiran S, tetapi bukan S sendiri).
2. Cetak periode terkecil S (panjang p terkecil sehingga S[i] == S[i+p]
   untuk semua i yang valid).
3. Cetak "YES" jika S merupakan pengulangan utuh dari blok yang lebih pendek
   dari S, dan "NO" jika bukan.
Semuanya harus diturunkan dari Z-array, tanpa memakai prefix function.

📥 INPUT FORMAT:
- Satu baris berisi string S (huruf kecil)

📤 OUTPUT FORMAT:
- Baris 1: panjang-panjang border urut menaik (kosong jika tidak ada)
- Baris 2: periode terkecil
- Baris 3: YES atau NO

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6

📎 SAMPLE INPUT 1:
abcabcab

📎 SAMPLE OUTPUT 1:
2 5
3
NO

📎 SAMPLE INPUT 2:
abab

📎 SAMPLE OUTPUT 2:
2
2
YES

💡 HINT: Sufiks yang mulai di i adalah border kalau ia cocok dengan awalan S
         sampai HABIS, yaitu z[i] == n - i. Indeks i yang menaik menghasilkan
         panjang border yang menurun. Untuk bagian 3, jangan lupa satu syarat
         tambahan selain periodisitas.

🎯 Learning Goals:
- [ ] Menerjemahkan definisi border langsung ke syarat z
- [ ] Ingat lagi: periodik != pengulangan utuh
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

    // TODO: bangun z

    // TODO: kumpulkan i dengan z[i] == n - i

    // TODO: border = n - i (perlu dibalik agar menaik)

    // TODO: periode terkecil = i terkecil yang memenuhi (atau n)

    // TODO: pengulangan utuh butuh i < n DAN n % i == 0

    return 0;
}
