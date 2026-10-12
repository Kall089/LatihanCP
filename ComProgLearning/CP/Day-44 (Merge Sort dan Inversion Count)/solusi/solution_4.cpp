/*
============================================================
✅ Solution 4: Pertukaran Berdampingan Minimum
============================================================
Approach: Jawabannya = banyaknya inversi
Complexity: Time O(n log n) per kasus | Space O(n)
Key Insight: Soal ini terlihat sama sekali berbeda dari "hitung inversi",
             tetapi keduanya adalah besaran yang sama. Kemampuan mengenali
             hal ini jauh lebih berharga daripada mengingat kodenya.

📖 BUKTI SINGKAT bahwa jawabannya tepat sama dengan banyaknya inversi:

   BATAS BAWAH: satu pertukaran elemen BERDAMPINGAN mengubah urutan relatif
   dari TEPAT SATU pasangan -- yaitu dua elemen yang ditukar itu sendiri.
   Semua pasangan lain tidak terpengaruh, karena posisi relatif mereka
   terhadap satu sama lain tidak berubah.
   Array terurut punya nol inversi. Jadi kalau array awal punya X inversi,
   kita butuh SETIDAKNYA X pertukaran.

   BATAS ATAS: X pertukaran selalu CUKUP. Selama array belum terurut, pasti
   ada pasangan berdampingan yang terbalik (kalau tidak ada, array sudah
   terurut). Tukar pasangan itu -- inversi berkurang tepat satu. Ulangi.
   Setelah X langkah, inversinya nol.

   Batas bawah = batas atas = X. Jadi jawabannya persis banyaknya inversi.

Perhatikan bahwa argumen ini juga menjelaskan Day 43: bubble sort hanya
menukar elemen berdampingan dan hanya kalau terbalik, sehingga jumlah
swap-nya sama dengan inversi -- bubble sort ternyata OPTIMAL dalam hal
jumlah pertukaran berdampingan.

⚠️ JANGAN TERTUKAR dengan "jumlah pertukaran minimum kalau boleh menukar
   dua elemen SEMBARANG". Itu masalah yang berbeda, jawabannya
   n - (banyaknya siklus permutasi), dan biasanya jauh lebih kecil.
   Contoh: [3,1,2] punya 2 inversi, tetapi bisa diurutkan dengan
   1 pertukaran bebas.

⚠️ MULTI TEST CASE: alokasikan ulang vektor per kasus (ukurannya berbeda),
   dan pastikan inversinya di-reset. Di sini kita membuat vektor baru
   setiap kasus, jadi otomatis aman.

⚠️ NILAI TIDAK DIJAMIN PERMUTASI dan bisa mencapai 10^9. Merge sort tidak
   peduli -- ia bekerja pada nilai apa pun. (Kalau kamu memakai pendekatan
   BIT, di sinilah kamu butuh kompresi koordinat lebih dulu.)

🔄 ALTERNATIVE APPROACHES:
- BIT + kompresi: O(n log n) juga.
- Simulasi bubble sort: O(n^2) -- TLE untuk n = 10^5.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll invCount(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    ll inv = invCount(a, tmp, l, mid) + invCount(a, tmp, mid, r);
    int i = l, j = mid, k = l;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else { tmp[k++] = a[j++]; inv += mid - i; }
    }
    while (i < mid) tmp[k++] = a[i++];
    while (j < r)   tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
    return inv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    string out;

    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n), tmp(n);
        for (int& x : a) cin >> x;

        out += to_string(invCount(a, tmp, 0, n));
        out += '\n';
    }

    cout << out;
    return 0;
}
