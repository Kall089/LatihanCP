/*
============================================================
✅ Solution 5: Hitung Subarray dengan Tepat K Jenis
============================================================
Approach: atMost(K) - atMost(K-1)
Complexity: Time O(n log n) | Space O(n)
Key Insight: Predikat "tepat K" TIDAK monoton -- memperlebar window bisa
             membuatnya layak, lalu tidak layak, lalu layak lagi. Sliding
             window tidak bisa dipakai langsung.
             Tetapi "paling banyak K" MONOTON. Dan
             {tepat K} = {paling banyak K} \ {paling banyak K-1}.
             Jadi satu masalah yang tidak bisa diselesaikan diubah menjadi
             selisih dua masalah yang bisa.

📖 PENJELASAN PENDEKATAN:
1. atMost(K) menghitung BANYAKNYA subarray dengan <= K jenis berbeda.
2. Di dalamnya, untuk setiap ujung kanan r, semua subarray yang berakhir
   di r dan dimulai di l..r pasti layak (karena kalau [l..r] punya <= K
   jenis, maka setiap sub-window di dalamnya juga punya <= K jenis).
   Banyaknya: r - l + 1.
   Inilah bedanya "menghitung banyak" dan "mencari terpanjang":
     terpanjang -> best = max(best, r - l + 1)
     banyaknya  -> hasil += r - l + 1
3. Jawabannya atMost(K) - atMost(K-1).

VERIFIKASI SAMPEL 1 (a = [1,2,1,2,3], K = 2):
   atMost(2) = 1 + 2 + 3 + 4 + 2 = 12
   atMost(1) = 1 + 1 + 1 + 1 + 1 = 5
   tepat 2   = 12 - 5 = 7  ✓
   Manual: [1,2] [2,1] [1,2] [1,2,1] [2,1,2] [1,2,1,2] [2,3] = 7  ✓

⚠️ OVERFLOW: untuk n = 2*10^5, atMost bisa mencapai n(n+1)/2 = 2*10^10.
   long long wajib. Ini kesalahan yang sering lolos karena sampel kecil.

⚠️ K - 1 bisa bernilai 0. atMost(0) harus mengembalikan 0 (tidak ada
   subarray tidak kosong dengan nol jenis), dan fungsinya harus menangani
   itu tanpa infinite loop.

🔄 ALTERNATIVE APPROACHES:
- Dua pointer kiri (l1 untuk <= K, l2 untuk <= K-1) dalam satu sapuan:
  O(n), satu kali jalan, tetapi jauh lebih rawan salah. Untuk kontes,
  versi pengurangan lebih aman.
- Trik pengurangan ini berlaku untuk SEMUA predikat "tepat" yang versi
  "paling banyak"-nya monoton -- termasuk "jumlah tepat S" pada array
  non-negatif. Simpan polanya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Banyaknya subarray dengan PALING BANYAK K nilai berbeda.
ll atMost(const vector<int>& a, int K) {
    if (K <= 0) return 0;
    map<int, int> cnt;
    ll hasil = 0;
    int l = 0, jenis = 0;

    for (int r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) jenis++;
        while (jenis > K) {
            if (--cnt[a[l]] == 0) jenis--;
            l++;
        }
        hasil += r - l + 1;                // semua subarray berakhir di r
    }
    return hasil;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;
    vector<int> a(n);
    for (int& v : a) cin >> v;

    cout << atMost(a, K) - atMost(a, K - 1) << '\n';
    return 0;
}
