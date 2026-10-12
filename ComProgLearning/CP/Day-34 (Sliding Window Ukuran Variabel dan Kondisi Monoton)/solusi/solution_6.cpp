/*
============================================================
✅ Solution 6: Blok Seragam Terpanjang Setelah Penggantian
============================================================
Approach: Sliding window + frekuensi karakter mayoritas
Complexity: Time O(26n) = O(n) | Space O(1)
Key Insight: Untuk sebuah window, biaya membuatnya seragam adalah
             (lebar window) - (frekuensi karakter terbanyak di dalamnya).
             Window layak kalau biaya itu <= K. Kita tidak perlu tahu
             karakter mana yang dipilih -- cukup tahu frekuensi terbesarnya.

📖 PENJELASAN PENDEKATAN:
1. cnt[26] menghitung karakter di dalam window.
2. maxFreq = frekuensi terbesar yang PERNAH tercapai.
3. Selama (r - l + 1) - maxFreq > K, susutkan.
4. Catat panjang.

⚠️ BAGIAN YANG MEMBINGUNGKAN: maxFreq TIDAK PERNAH DITURUNKAN saat window
   menyusut, padahal frekuensi sesungguhnya bisa berkurang. Kenapa hasilnya
   tetap benar?

   Karena maxFreq yang "kedaluwarsa" hanya membuat window terlihat LEBIH
   layak dari seharusnya, sehingga window tidak menyusut sebanyak yang
   seharusnya. Tapi itu tidak pernah menghasilkan jawaban yang LEBIH BESAR
   dari yang benar: agar best bertambah, window harus melebar melewati
   rekor sebelumnya, dan itu hanya terjadi kalau maxFreq benar-benar naik --
   yang berarti nilainya valid pada saat itu.

   Singkatnya: window boleh "salah" untuk sementara, tapi rekornya tidak.
   Ini pola yang halus dan layak diingat; beberapa soal window memakainya.

   (Kalau kamu ingin implementasi yang secara harfiah benar setiap saat,
   hitung ulang maxFreq dari 26 slot setiap iterasi. Itu O(26n), sama
   cepatnya, dan lebih mudah dipertanggungjawabkan. Versi di bawah memakai
   pendekatan pertama karena inilah yang lazim ditemui.)

VERIFIKASI SAMPEL 2 (S = "AABABBA", K = 1):
   window terbaik "ABAB"? -> 4 karakter, maxFreq 2, biaya 2 > 1, tidak layak
   window "AABA" -> maxFreq 3 (A), biaya 1 <= 1, layak, panjang 4  ✓
   jawab 4  ✓

🔄 ALTERNATIVE APPROACHES:
- Ulangi window untuk masing-masing 26 huruf sebagai target: O(26n),
  lebih mudah dijelaskan, sama cepatnya. Pilihan yang bagus kalau kamu
  tidak yakin dengan argumen maxFreq di atas.
- Binary search on answer + pengecekan window tetap: O(26 n log n).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    string s;
    cin >> n >> K >> s;
    n = s.size();

    vector<int> cnt(26, 0);
    int l = 0, best = 0, maxFreq = 0;

    for (int r = 0; r < n; r++) {
        maxFreq = max(maxFreq, ++cnt[s[r] - 'A']);
        while ((r - l + 1) - maxFreq > K) {
            cnt[s[l] - 'A']--;
            l++;
        }
        best = max(best, r - l + 1);
    }

    cout << best << '\n';
    return 0;
}
