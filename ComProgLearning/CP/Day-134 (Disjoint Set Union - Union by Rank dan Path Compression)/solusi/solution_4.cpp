/*
============================================================
✅ Solution 4: Membangun Jalan
============================================================
Approach: DSU + statistik global yang dijaga inkremental
Complexity: Time O((N + M) α(N)) | Space O(N)
Key Insight: Kedua statistik yang diminta bisa dijaga TANPA menyapu ulang.
             Banyaknya komponen berkurang tepat satu per penggabungan yang
             berhasil. Ukuran terbesar hanya bisa BERTAMBAH, sehingga cukup
             dibandingkan dengan ukuran gabungan yang baru terbentuk.

📖 KENAPA UKURAN TERBESAR CUKUP DIBANDINGKAN SEKALI:
   Penggabungan hanya MEMBESARKAN sebuah komponen; tidak ada komponen yang
   mengecil. Jadi maksimum global tidak pernah turun.
   Satu-satunya komponen yang ukurannya berubah adalah yang baru terbentuk,
   sehingga membandingkan `terbesar` dengan ukuran gabungan itu saja sudah
   menjamin kebenarannya.

   Ini pola yang berulang di CP: kalau sebuah besaran MONOTON, kamu sering
   bisa menjaganya dengan satu variabel alih-alih menghitung ulang.

⚠️ KAPAN MEMBACA UKURAN GABUNGAN: setelah sz[a] += sz[b], bukan sebelumnya.
   Membacanya sebelum penggabungan memberi ukuran salah satu komponen saja.

⚠️ PENGGABUNGAN YANG GAGAL tidak boleh mengubah apa pun -- tidak
   `komponen`, tidak `terbesar`. Jalan yang menghubungkan dua kota yang
   sudah terhubung memang tidak mengubah struktur.

⚠️ KELUARAN M BARIS: dengan M = 2*10^5, mencetak dengan cout per baris
   masih aman, tetapi membangun satu string lalu mencetak sekali adalah
   kebiasaan yang lebih baik dan gratis.

VERIFIKASI SAMPEL (5 kota, jalan: 1-2, 1-3, 4-5, 1-5):
   hari 1: gabung {1,2}      komponen 5->4, terbesar 2   -> "4 2"   ✓
   hari 2: gabung {1,2,3}    komponen 4->3, terbesar 3   -> "3 3"   ✓
   hari 3: gabung {4,5}      komponen 3->2, terbesar max(3,2)=3 -> "2 3"  ✓
   hari 4: gabung semuanya   komponen 2->1, terbesar 5   -> "1 5"   ✓

🔄 ALTERNATIVE APPROACHES:
- Menyapu seluruh kota setiap hari untuk menghitung ulang: O(N) per hari,
  total O(N*M) = 4*10^10 -- TLE telak.
- BFS/DFS ulang setiap hari: sama buruknya.
- DSU inkremental adalah satu-satunya pendekatan yang wajar, dan inilah
  contoh terbaik kenapa DSU unggul atas BFS/DFS untuk graf yang TUMBUH.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> par(n + 1), sz(n + 1, 1);
    iota(par.begin(), par.end(), 0);
    int komponen = n, terbesar = 1;

    function<int(int)> find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    };

    string out;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a = find(a); b = find(b);

        if (a != b) {                              // gagal = tidak mengubah apa pun
            if (sz[a] < sz[b]) swap(a, b);
            par[b] = a;
            sz[a] += sz[b];                        // baca SETELAH digabung
            komponen--;
            terbesar = max(terbesar, sz[a]);       // maksimum bersifat MONOTON
        }

        out += to_string(komponen);
        out += ' ';
        out += to_string(terbesar);
        out += '\n';
    }
    cout << out;

    return 0;
}
