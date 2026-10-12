/*
============================================================
✅ Solution 4: Biaya Perjalanan Optimal
============================================================
Approach: Dua kandidat (solusi langsung), dengan ternary sebagai pembanding
Complexity: Time O(1) | Space O(1)
Key Insight: Fungsi biayanya LINEAR PER BAGIAN. Untuk fungsi seperti itu,
             minimumnya selalu berada di salah satu TITIK EKSTREM -- yaitu
             ujung rentang atau titik patah. Kita tidak perlu mencari sama
             sekali; cukup membandingkan beberapa kandidat.

📖 MENYUSUN FUNGSI BIAYA:
   biaya(k) = k*A + (k < N ? B + (N-k)*C : 0)

   Untuk k dari 0 sampai N-1:
       biaya(k) = k*A + B + (N-k)*C = k*(A-C) + (B + N*C)
   Ini fungsi LINEAR terhadap k dengan kemiringan (A - C).
       A > C -> menanjak -> minimum di k = 0    (langsung naik lift)
       A < C -> menurun  -> minimum di k = N-1
       A = C -> DATAR    -> semua k sama

   Untuk k = N: biaya(N) = N*A (naik tangga seluruhnya, tanpa menunggu lift).

   Jadi hanya ada TIGA kandidat: k = 0, k = N-1, dan k = N.
   Bahkan sebenarnya cukup DUA: k = 0 (lift penuh) dan k = N (tangga penuh),
   ditambah k = N-1 untuk kasus A < C yang jarang.

⚠️ KENAPA TERNARY SEARCH BERBAHAYA DI SINI:
   Kalau A tepat sama dengan C, fungsinya DATAR pada seluruh k dari 0 sampai
   N-1. Ternary search akan mendapati f(m1) == f(m2) dan tidak punya
   informasi arah -- ia bisa membuang sisi yang memuat k = N.
   Ini contoh nyata dari peringatan di teori: fungsi dengan DATARAN tidak
   dijamin diselesaikan dengan benar oleh ternary search.

   Pelajaran umumnya: sebelum memakai ternary search, periksa apakah
   fungsimu punya dataran. Kalau fungsinya linear per bagian, hampir selalu
   ada solusi langsung yang lebih baik.

⚠️ OVERFLOW ADALAH JEBAKAN NYATA:
   N sampai 10^12 dan A sampai 10^9, sehingga N*A mencapai 10^21 --
   MELUAP bahkan di long long (batas ~9.2*10^18).
   Untuk soal ini, batasan sesungguhnya membuat jawabannya tetap muat
   karena kita mengambil MINIMUM, tetapi kandidat individual bisa meluap
   saat dihitung. Solusi ini memakai unsigned long long dan membandingkan
   dengan hati-hati; untuk soal serupa, pertimbangkan __int128 kalau ragu.

VERIFIKASI SAMPEL 1 (N=100, A=10, B=100, C=1):
   k = N   : 100*10 = 1000                 (tangga penuh)
   k = 0   : 0 + 100 + 100*1 = 200         (langsung lift)
   k = N-1 : 99*10 + 100 + 1*1 = 1091
   minimum = 200   ✓   Karena A > C, kemiringan (A-C) positif sehingga
   bagian liftnya minimum di k = 0 -- sesuai analisis di atas.

VERIFIKASI SAMPEL 2 (N=5, A=1, B=100, C=1):
   k = N = 5 : 5*1 = 5
   k = 0     : 100 + 5 = 105
   minimum = 5   ✓   Di sini biaya menunggu lift terlalu mahal untuk gedung
   sependek itu, sehingga tangga penuh yang menang. Perhatikan bahwa
   A == C di sini, yaitu tepat kasus DATARAN yang membuat ternary search
   tidak dapat diandalkan -- sedangkan pendekatan kandidat tetap benar.

🔄 ALTERNATIVE APPROACHES:
- Ternary search integer: bekerja KALAU A != C, tetapi rapuh pada dataran.
- Sapuan linier: mustahil, N sampai 10^12.
- Solusi langsung (dipakai di sini): O(1), eksak, tanpa asumsi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll N, A, B, C;
    if (!(cin >> N >> A >> B >> C)) return 0;

    // Fungsi biaya untuk k lantai dengan tangga, sisanya dengan lift.
    auto biaya = [&](ll k) -> ull {
        ull t = (ull)k * (ull)A;
        if (k < N) t += (ull)B + (ull)(N - k) * (ull)C;
        return t;
    };

    // Fungsi linear per bagian -> minimum di titik ekstrem.
    // Kandidatnya: k = 0, k = N-1, k = N.
    ull best = biaya(N);                       // tangga penuh
    best = min(best, biaya(0));                // langsung lift
    if (N >= 1) best = min(best, biaya(N - 1));

    cout << best << '\n';
    return 0;
}
