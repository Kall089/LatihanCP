/*
============================================================
✅ Solution 4: Perampok Rumah Melingkar
============================================================
Approach: jalankan versi linear DUA KALI pada dua irisan
Complexity: Time O(N) | Space O(1)
Key Insight: Rumah pertama dan terakhir kini bertetangga, jadi MUSTAHIL
             keduanya dirampok bersamaan. Artinya setiap solusi yang sah pasti
             melewatkan minimal satu di antaranya. Cukup paksa masing-masing
             kasus dan ambil yang lebih baik.

📖 DUA KASUS YANG MENCAKUP SEMUANYA:
   (a) rumah TERAKHIR tidak dirampok  -> jalankan linear pada a[0 .. n-2]
   (b) rumah PERTAMA tidak dirampok   -> jalankan linear pada a[1 .. n-1]
   jawaban = max(a, b)

   KELENGKAPAN: setiap solusi sah melewatkan minimal satu ujung, jadi tercakup.
   KESAHIHAN  : setiap solusi dari (a) atau (b) tidak pernah memakai kedua
                ujung sekaligus, jadi valid pada lingkaran.
   Boleh saja sebuah solusi tercakup di keduanya -- karena kita mengambil MAX
   (bukan menjumlahkan), penghitungan ganda tidak jadi masalah.

⚠️ n == 1 WAJIB DITANGANI TERPISAH.
   a[0 .. n-2] menjadi rentang KOSONG, dan jawabannya akan salah (0 alih-alih
   a[0]). Sampel 3 menguji ini secara khusus.

⚠️ JANGAN MENAMBAL REKURENS DENGAN if.
   Godaan terbesar adalah menulis satu sapuan dengan "kalau i == n-1 dan rumah
   0 dirampok maka ...". Itu memerlukan state tambahan (apakah rumah 0
   dirampok) dan hampir selalu salah di kasus batas. Dua kali jalan linear
   lebih pendek DAN lebih mudah dibuktikan.

VERIFIKASI SAMPEL 1 ([2,1,1,2], melingkar):
   (a) linear pada [2,1,1] -> max(2+1, 1) = 3
   (b) linear pada [1,1,2] -> max(1+2, 1) = 3
   jawaban 3  ✓
   Bandingkan dengan Latihan 3 (versi lurus) yang memberi 4. Perbedaan inilah
   inti soalnya: rumah 0 dan 3 kini bertetangga.

VERIFIKASI SAMPEL 2 ([1,2,3]):
   (a) [1,2] -> 2 ; (b) [2,3] -> 3 ; jawaban 3  ✓

🔄 ALTERNATIVE APPROACHES:
- DP dengan state "apakah rumah 0 dirampok": dp[i][0/1]. Benar juga, tapi
  lebih panjang dan lebih rawan salah di indeks terakhir.
- Pola "jalankan linear dua kali" ini muncul lagi di banyak soal melingkar:
  Kadane melingkar, interval melingkar, dan DP pada array melingkar umumnya.
  Alternatif umum lainnya: duplikasi array (a + a) lalu jendela sepanjang n.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll robberLinear(const vector<ll>& a, int l, int r) {   // inklusif [l, r]
    ll p2 = 0, p1 = 0;
    for (int i = l; i <= r; i++) {
        ll c = max(p1, p2 + a[i]);
        p2 = p1;
        p1 = c;
    }
    return p1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    if (n == 1) { cout << a[0] << '\n'; return 0; }    // KASUS KHUSUS WAJIB

    cout << max(robberLinear(a, 0, n - 2),             // buang yang terakhir
                robberLinear(a, 1, n - 1)) << '\n';    // buang yang pertama
    return 0;
}
