/*
============================================================
✅ Solution 4: Rata-rata Segmen Terbaik
============================================================
Approach: Transformasi a[i] - x + prefix sum + minimum berjalan
Complexity: Time O(100 * N) | Space O(N)
Key Insight: Gabungan tiga teknik yang masing-masing sudah kamu kuasai.
             Transformasi a[i] - x (hari ini) mengubah "rata-rata" menjadi
             "jumlah". Prefix sum (Day 29) mengubah "jumlah segmen" menjadi
             "selisih dua prefix". Minimum berjalan mengubah "cari segmen
             terbaik" menjadi satu sapuan O(N).

📖 PENJELASAN PENDEKATAN:
1. Setelah transformasi, predikatnya: "adakah segmen berurutan sepanjang
   setidaknya L yang jumlah (a[i] - x)-nya >= 0?"
2. Dengan pre[i] = jumlah (a[0..i-1] - x), jumlah segmen [j, i-1] adalah
   pre[i] - pre[j].
3. Untuk setiap ujung kanan i (dengan i >= L), ujung kiri yang sah adalah
   j = 0 .. i-L. Kita ingin pre[j] SEKECIL mungkin agar selisihnya terbesar.
4. Karena himpunan j yang sah BERTAMBAH SATU setiap kali i maju, kita bisa
   menjaga minimumnya secara berjalan: sebelum memproses i, masukkan
   pre[i - L] ke dalam minimum.

⚠️ URUTAN OPERASI DI LANGKAH 4 SANGAT PENTING.
   minPre harus diperbarui dengan pre[i - L] SEBELUM membandingkan dengan
   pre[i]. Kalau dibalik, kamu akan mengizinkan segmen yang panjangnya
   KURANG dari L (yaitu j = i - L + 1 ke atas), dan jawabannya menjadi
   terlalu besar. Ini bug yang tidak terlihat pada sampel dengan L kecil.

⚠️ KENAPA MINIMUM BERJALAN CUKUP, TIDAK PERLU STRUKTUR DATA:
   Kita hanya butuh minimum atas PREFIKS dari himpunan yang bertambah, dan
   himpunan itu tidak pernah kehilangan anggota. Minimum atas himpunan yang
   hanya bertambah bisa dijaga dengan satu variabel. Kalau himpunannya juga
   bisa kehilangan anggota dari kiri (jendela geser), barulah kamu butuh
   monotonic deque (Day 37).

⚠️ ARAH BINARY SEARCH: predikatnya true untuk x kecil, jadi cari x TERBESAR
   yang masih layak.

VERIFIKASI SAMPEL 1 (a = [6,4,2,10,3,8,5,9,4,1], L = 6):
   Segmen terbaik adalah indeks 3..8 (nilai 10,3,8,5,9,4), jumlah 39,
   panjang 6, rata-rata 6.5.
   Uji x = 6.5: (a[i] - 6.5) untuk segmen itu berjumlah tepat 0 -> layak.
   Uji x sedikit lebih besar: seluruh segmen berjumlah negatif -> tidak layak.
   Jadi jawabannya 6.500   ✓

CATATAN PRESISI: nilai a[i] adalah bilangan bulat sampai 2000 dan N sampai
10^5, sehingga pre[] bisa mencapai 2*10^8 -- masih aman di double (yang
eksak untuk bilangan bulat sampai 2^53). Kalau nilainya jauh lebih besar,
pertimbangkan untuk mengalikan semuanya dan bekerja dalam long long.

🔄 ALTERNATIVE APPROACHES:
- Divide and conquer + convex hull trick: O(N log N) tanpa binary search,
  tetapi jauh lebih rumit.
- Kalau L = 1, soalnya runtuh menjadi "cari elemen maksimum".
- Soal ini adalah POJ 2018 "Best Cow Fences", contoh klasik dari pola ini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, L;
    if (!(cin >> n >> L)) return 0;
    vector<double> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    double lo = *min_element(a.begin(), a.end());
    double hi = *max_element(a.begin(), a.end());

    vector<double> pre(n + 1);
    auto bisa = [&](double x) {
        pre[0] = 0;
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (a[i] - x);

        double minPre = 0;
        for (int i = L; i <= n; i++) {
            minPre = min(minPre, pre[i - L]);      // masukkan DULU, baru cek
            if (pre[i] - minPre >= 0) return true;
        }
        return false;
    };

    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (bisa(mid)) lo = mid;
        else           hi = mid;
    }

    printf("%.3f\n", lo);
    return 0;
}
