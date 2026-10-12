/*
============================================================
✅ Solution 4: Apakah Urutan Topologisnya Unik?
============================================================
Approach: Kahn + periksa ukuran antrean setiap iterasi
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Antrean berisi TEPAT himpunan simpul yang boleh diambil sekarang.
             Kalau ukurannya >= 2, ada minimal dua urutan sah berbeda: tukar
             dua simpul itu dan sisanya bisa diselesaikan sama saja. Kalau
             ukurannya selalu 1, tidak pernah ada pilihan -> urutan tunggal.

📖 CARA PANDANG LAIN (setara):
   Urutan topologis unik  <=>  ada Hamiltonian path pada DAG-nya
   <=>  setiap pasangan berurutan ord[i], ord[i+1] terhubung edge langsung.
   Cara antrean di atas lebih murah dan lebih mudah ditulis.

⚠️ URUTAN PENGECEKAN. Periksa q.size() > 1 SEBELUM melakukan pop, di awal
   setiap iterasi. Memeriksa setelah pop akan melewatkan kasus terakhir.

⚠️ SIKLUS DIPERIKSA DULU. Kalau ord.size() != n, jawabannya SIKLUS -- nilai
   flag "unik" tidak relevan lagi dan bisa menyesatkan.

⚠️ SIMPUL TERISOLASI MEMBUAT JAWABAN "BANYAK". Sampel 2 (n=3, hanya edge 1->2)
   menguji ini: simpul 3 tidak terikat apa pun, jadi ia boleh diletakkan di
   mana saja -> BANYAK. Antrean awal berisi {1,3}, ukurannya 2, terdeteksi.

VERIFIKASI SAMPEL 1 (1->2, 2->3):
   antre [1] size1 -> pop 1, push 2
   antre [2] size1 -> pop 2, push 3
   antre [3] size1 -> pop 3
   tidak pernah >1, dan size==n  ->  UNIK  ✓

VERIFIKASI SAMPEL 2 (edge 1->2 saja, n=3):
   indeg = [_,0,1,0]; antre awal [1,3] ukuran 2 -> BANYAK  ✓

🔄 ALTERNATIVE APPROACHES:
- Cek Hamiltonian path: jalankan Kahn biasa, lalu untuk tiap i periksa apakah
  edge (ord[i] -> ord[i+1]) ada. Butuh set/hash edge, lebih repot.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for (int u = 1; u <= n; u++) if (indeg[u] == 0) q.push(u);

    bool unik = true;
    int keluar = 0;
    while (!q.empty()) {
        if (q.size() > 1) unik = false;      // cek SEBELUM pop
        int u = q.front(); q.pop();
        keluar++;
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }

    if (keluar != n)      cout << "SIKLUS\n";
    else if (unik)        cout << "UNIK\n";
    else                  cout << "BANYAK\n";
    return 0;
}
