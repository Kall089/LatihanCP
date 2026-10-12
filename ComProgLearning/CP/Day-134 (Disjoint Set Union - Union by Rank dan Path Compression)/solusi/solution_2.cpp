/*
============================================================
✅ Solution 2: Deteksi Sisi yang Membentuk Siklus
============================================================
Approach: unite yang mengembalikan bool
Complexity: Time O((N + M) α(N)) | Space O(N)
Key Insight: Sebuah sisi membentuk siklus PERSIS ketika kedua ujungnya
             sudah berada di komponen yang sama. Kita tidak perlu mencari
             siklusnya -- cukup memeriksa apakah penggabungan berhasil.

📖 KENAPA NILAI KEMBALIAN BOOL PENTING:
   Tanpa itu, kamu harus menulis:
       if (find(u) == find(v)) { redundan }
       else unite(u, v);
   Itu memanggil find EMPAT kali (dua di pemeriksaan, dua di dalam unite).
   Dengan nilai kembalian, cukup:
       if (!unite(u, v)) { redundan }
   Dua kali find, dan kodenya lebih pendek. Kebiasaan ini akan terbayar
   lagi di Exercise 5 (Kruskal), di mana pola yang sama dipakai untuk
   memutuskan sisi mana yang masuk MST.

⚠️ SELF-LOOP (u sama dengan v): find(u) == find(v) secara otomatis,
   sehingga unite mengembalikan false dan sisi itu benar dilaporkan
   redundan. Tidak perlu penanganan khusus -- tetapi bagus untuk diyakini,
   karena beberapa soal melarang self-loop dan beberapa tidak.

⚠️ KELUARAN KOSONG: kalau tidak ada sisi redundan, soal meminta baris
   kosong. Pastikan program tetap mencetak newline, bukan tidak mencetak
   apa pun -- beberapa juri membedakan keduanya.

VERIFIKASI SAMPEL 1 (4 simpul, sisi: 1-2, 2-3, 1-3, 3-4, 1-4):
   sisi 1 (1-2) : gabung        -> tidak redundan
   sisi 2 (2-3) : gabung        -> tidak redundan
   sisi 3 (1-3) : 1 dan 3 sudah sekelompok  -> REDUNDAN
   sisi 4 (3-4) : gabung        -> tidak redundan
   sisi 5 (1-4) : sudah sekelompok          -> REDUNDAN
   jawab: 3 5   ✓

🔄 ALTERNATIVE APPROACHES:
- DFS mencari back edge: O(N + M), tetapi butuh seluruh graf lebih dulu
  dan tidak memberi tahu sisi MANA yang pertama membentuk siklus dalam
  urutan penambahan.
- DSU adalah pilihan alami karena sisi datang berurutan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct DSU {
    vector<int> par, sz;
    DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;                  // sudah sekelompok
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    DSU d(n + 1);

    string out;
    bool pertama = true;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (!d.unite(u, v)) {                      // gagal menggabung = redundan
            if (!pertama) out += ' ';
            out += to_string(i);
            pertama = false;
        }
    }
    out += '\n';                                   // tetap cetak newline
    cout << out;

    return 0;
}
