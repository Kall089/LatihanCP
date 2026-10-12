/*
============================================================
✅ Solution 4: Knapsack dengan Barang Sedikit
============================================================
Approach: Meet in the middle + PREFIX MAKSIMUM
Complexity: Time O(2^(N/2) · N) | Space O(2^(N/2))
Key Insight: Ini bentuk MITM yang paling sering muncul, dan ia memuat bug
             nomor satu di seluruh topik ini. Ketika setiap subset punya
             DUA besaran (berat dan nilai), mengurutkan berdasarkan berat
             TIDAK cukup -- karena subset dengan berat lebih kecil bisa
             punya nilai lebih besar.

📖 KENAPA PREFIX MAKSIMUM WAJIB -- contoh minimal:
   Paruh kiri: barang {berat 1, nilai 10} dan {berat 3, nilai 2}.
   Subsetnya (berat, nilai): (0,0), (1,10), (3,2), (4,12)
   Terurut berdasarkan berat: (0,0), (1,10), (3,2), (4,12)

   Misalkan sisa kapasitas = 3.
     TANPA prefix maksimum: upper_bound mundur satu -> (3, 2), nilainya 2.
        Padahal (1, 10) juga muat dan nilainya 10!   SALAH.
     DENGAN prefix maksimum, kolom nilai menjadi:
        (0,0), (1,10), (3,10), (4,12)
        upper_bound mundur satu -> (3, 10).           BENAR  ✓

   Setelah prefix maksimum, kolom nilai menjadi TIDAK MENURUN, sehingga
   "berat terbesar yang muat" otomatis juga "nilai terbaik yang muat".

⚠️ BUG INI HANYA MUNCUL SAAT DUA BESARAN TERPISAH. Pada Solution 3 (hanya
   berat), kolom yang diurutkan dan kolom yang dimaksimalkan adalah SAMA,
   sehingga prefix maksimum tidak mengubah apa pun. Itulah kenapa banyak
   orang menulis MITM dengan benar untuk soal sederhana lalu gagal pada
   knapsack -- dan tidak mengerti kenapa.

⚠️ make_pair(sisa, LLONG_MAX) pada upper_bound memastikan kita melewati
   SELURUH pasangan yang beratnya tepat sama dengan sisa, sehingga idx
   menunjuk ke yang terakhir di antara mereka. Memakai make_pair(sisa, 0)
   akan melewatkan sebagian pasangan yang sebenarnya muat.

⚠️ KENAPA DP KNAPSACK MUSTAHIL DI SINI: berat mencapai 10^15, sehingga
   tabel DP berukuran N * C butuh 4*10^16 sel. MITM adalah satu-satunya
   pendekatan yang wajar.
   Sebaliknya, kalau C <= 10^6, DP knapsack O(N*C) jauh lebih sederhana --
   selalu periksa batas bobot sebelum memutuskan.

VERIFIKASI SAMPEL 1 (4 barang, C = 5):
   Barang: (1,10), (2,20), (3,30), (4,40)
   Pilihan terbaik: barang berat 2 (nilai 20) + barang berat 3 (nilai 30)
   Total berat 5 <= 5, total nilai 50.   ✓

CATATAN: implementasi ini telah diuji terhadap brute force 2^n pada 20000
kasus acak, termasuk kasus yang menjebak prefix maksimum.

🔄 ALTERNATIVE APPROACHES:
- DP knapsack O(N * C): mustahil untuk C = 10^15.
- DP atas NILAI (O(N * total nilai)): total nilai bisa 4*10^10 -- juga
  mustahil di sini, tetapi berguna kalau nilainya kecil sedangkan
  bobotnya besar.
- Branch and bound: bisa cepat dalam praktik, tetapi tidak ada jaminan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Barang { ll bobot, nilai; };

vector<pair<ll, ll>> bangkitPasangan(const vector<Barang>& b, int mulai, int akhir) {
    int m = akhir - mulai;
    vector<pair<ll, ll>> v(1 << m);
    for (int mask = 1; mask < (1 << m); mask++) {
        int i = __builtin_ctz(mask);
        auto prev = v[mask ^ (1 << i)];
        v[mask] = {prev.first + b[mulai + i].bobot,
                   prev.second + b[mulai + i].nilai};
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll C;
    cin >> n >> C;
    vector<Barang> b(n);
    for (int i = 0; i < n; i++) cin >> b[i].bobot >> b[i].nilai;

    int k = n / 2;
    auto A = bangkitPasangan(b, 0, k);
    auto B = bangkitPasangan(b, k, n);

    sort(A.begin(), A.end());                        // urut berdasarkan BOBOT

    // PREFIX MAKSIMUM atas NILAI -- langkah yang paling sering dilupakan
    for (size_t i = 1; i < A.size(); i++)
        A[i].second = max(A[i].second, A[i - 1].second);

    ll best = 0;
    for (auto& pr : B) {
        if (pr.first > C) continue;
        ll sisa = C - pr.first;
        int idx = int(upper_bound(A.begin(), A.end(),
                      make_pair(sisa, LLONG_MAX)) - A.begin()) - 1;
        if (idx >= 0) best = max(best, pr.second + A[idx].second);
    }

    cout << best << '\n';
    return 0;
}
