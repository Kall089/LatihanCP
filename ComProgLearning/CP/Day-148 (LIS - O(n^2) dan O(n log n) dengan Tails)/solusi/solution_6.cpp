/*
============================================================
✅ Solution 6: Menumpuk Kotak (LIS yang Menyamar)
============================================================
Approach: sort dua kriteria dengan tie-break TERBALIK, lalu LIS pada dimensi kedua
Complexity: Time O(N log N) | Space O(N)
Key Insight: Mengurutkan berdasarkan w membereskan dimensi pertama -- setelah
             diurutkan, syarat w_A < w_B otomatis terpenuhi untuk pasangan yang
             berurutan, KECUALI kalau w-nya sama. Tie-break menurun pada h
             menangani pengecualian itu tanpa satu pun if tambahan.

📖 KENAPA TIE-BREAK h HARUS MENURUN:
   Dua kotak dengan w SAMA tidak boleh dua-duanya masuk rantai (syaratnya
   ketat). Dengan mengurutkan h MENURUN untuk w yang sama, barisan h mereka
   menjadi menurun -- dan LIS KETAT tidak akan pernah mengambil dua elemen
   dari barisan menurun. Jadi pembatasannya terjadi otomatis.

   Uji dengan [(1,1), (1,2), (2,3)]:
     tie-break MENURUN  -> urut: (1,2), (1,1), (2,3) -> h = [2,1,3] -> LIS 2 ✓
     tie-break MENAIK   -> urut: (1,1), (1,2), (2,3) -> h = [1,2,3] -> LIS 3 ✗
   Yang kedua salah karena dua kotak pertama sama-sama berlebar 1.

⚠️ SAMPEL 2 ADALAH UJI TIE-BREAK. Tiga kotak berlebar 1: jawabannya 1.
   Tanpa tie-break terbalik kamu akan menjawab 3.

⚠️ LIS-nya harus KETAT (lower_bound), sesuai syarat h_A < h_B.
   Kalau soal memakai "muat kalau <=", ubah ke upper_bound DAN ubah tie-break
   h menjadi menaik. Dua perubahan itu selalu berpasangan.

⚠️ JANGAN mengurutkan berdasarkan LUAS (w*h). Itu godaan umum dan salah:
   luas lebih besar tidak menjamin kedua dimensinya lebih besar.

VERIFIKASI SAMPEL 1 ([(5,4),(6,4),(6,7),(2,3)]):
   urut w naik, h menurun saat seri: (2,3), (5,4), (6,7), (6,4)
   h = [3, 4, 7, 4]
   LIS ketat pada h: 3, 4, 7  -> 3  ✓
   Rantainya: (2,3) -> (5,4) -> (6,7)

🔄 ALTERNATIVE APPROACHES:
- Untuk 3 dimensi (box stacking sungguhan), satu kali sort tidak cukup --
  butuh DP O(n^2) atau struktur data 2D (BIT 2D / CDQ divide and conquer).
  Pola "urutkan satu dimensi, DP di dimensi lain" tetap sama.
- Soal ini identik dengan LC 354 Russian Doll Envelopes.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<pair<int,int>> b(n);
    for (auto& p : b) cin >> p.first >> p.second;

    sort(b.begin(), b.end(), [](const pair<int,int>& A, const pair<int,int>& B) {
        if (A.first != B.first) return A.first < B.first;
        return A.second > B.second;              // MENURUN saat w sama
    });

    vector<int> tails;
    for (auto& p : b) {
        int x = p.second;
        auto it = lower_bound(tails.begin(), tails.end(), x);   // KETAT
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << tails.size() << '\n';
    return 0;
}
