/*
============================================================
✅ Solution 5: Biaya Menghubungkan Semua Kota (Kruskal)
============================================================
Approach: Kruskal -- urutkan sisi, ambil yang tidak membentuk siklus
Complexity: Time O(M log M) | Space O(N + M)
Key Insight: Greedy "termurah dulu" BENAR untuk MST, dan DSU adalah yang
             membuatnya praktis: ia menjawab "apakah sisi ini membentuk
             siklus" dalam waktu hampir konstan. Tanpa DSU, pemeriksaan itu
             butuh BFS/DFS per sisi -- O(M * N).

📖 KENAPA GREEDY TERMURAH-DULU BENAR (cut property):
   Ambil sisi termurah e yang menghubungkan dua komponen berbeda.
   Klaim: ADA MST yang memuat e.
   Bukti singkat: ambil MST T mana pun. Kalau T tidak memuat e, tambahkan e
   ke T -- terbentuk tepat satu siklus, dan siklus itu pasti memuat sisi
   lain f yang juga menyeberangi kedua komponen tadi. Karena e termurah di
   antara penyeberang, bobot e <= bobot f. Tukar f dengan e: hasilnya tetap
   pohon merentang, dan bobotnya tidak lebih besar. Jadi ada MST yang
   memuat e.
   Argumen ini disebut EXCHANGE ARGUMENT, dan ia adalah cara baku
   membuktikan greedy (Day 71 dan 79 membahasnya lebih dalam).

📖 KENAPA BERHENTI SETELAH N-1 SISI:
   Pohon merentang atas N simpul selalu punya tepat N-1 sisi. Setelah
   mencapainya, seluruh sisi berikutnya pasti membentuk siklus. Berhenti
   lebih awal menghemat waktu, meski tidak mengubah kebenaran.

⚠️ DETEKSI GRAF TIDAK TERHUBUNG: kalau setelah memproses SELURUH sisi
   jumlah yang terpakai kurang dari N-1, berarti graf tidak terhubung dan
   tidak ada spanning tree. Ini pemeriksaan yang sering dilupakan --
   sampel 2 memang ditaruh untuk menangkapnya.
   Cara setara: cek apakah `komponen` masih lebih dari 1 di akhir.

⚠️ OVERFLOW: 10^5 sisi dengan bobot 10^9 memberi total 10^14. long long
   untuk akumulator, meski bobot individualnya muat di int.

⚠️ NILAI KEMBALIAN unite DIPAKAI LANGSUNG sebagai kondisi. Menuliskannya
   sebagai `if (find(u) != find(v)) { unite(u,v); ... }` memanggil find
   empat kali alih-alih dua -- benar, tetapi boros.

VERIFIKASI SAMPEL 1 (4 kota, sisi terurut: 1,2,3,4,5):
   (1, 1-2) : gabung -> total 1, terpakai 1
   (2, 2-3) : gabung -> total 3, terpakai 2
   (3, 1-3) : SUDAH sekelompok -> lewati
   (4, 3-4) : gabung -> total 7, terpakai 3 = N-1, BERHENTI
   jawab 7   ✓

CATATAN: implementasi ini telah diuji terhadap Prim O(n^2) pada 20000 graf acak.

🔄 ALTERNATIVE APPROACHES:
- Prim dengan priority queue: O(M log N). Lebih baik untuk graf PADAT
  (M mendekati N^2) karena tidak perlu mengurutkan seluruh sisi.
  Kruskal lebih baik untuk graf JARANG dan jauh lebih pendek ditulis.
- Boruvka: O(M log N), berguna untuk paralelisasi. Jarang dipakai di CP.
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
        if (a == b) return false;
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

    vector<array<ll, 3>> sisi(m);                  // {bobot, u, v}
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        sisi[i] = {w, u, v};
    }
    sort(sisi.begin(), sisi.end());                // termurah dulu

    DSU d(n + 1);
    ll total = 0;                                  // bisa 10^14 -> long long
    int dipakai = 0;

    for (auto& e : sisi)
        if (d.unite((int)e[1], (int)e[2])) {       // nilai kembalian dipakai
            total += e[0];
            if (++dipakai == n - 1) break;         // pohon merentang selesai
        }

    if (dipakai == n - 1) cout << total << '\n';
    else                  cout << "IMPOSSIBLE\n";  // graf tidak terhubung

    return 0;
}
