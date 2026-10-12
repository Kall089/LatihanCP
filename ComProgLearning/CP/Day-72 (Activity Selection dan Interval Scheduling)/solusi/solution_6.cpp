/*
============================================================
✅ SOLUSI Exercise 6: Menyewakan Mesin
============================================================
Difficulty: Hard | Kompleksitas: O(K * V * E) dengan MCMF SPFA
                   V = O(n), E = O(n) → sangat cepat untuk n=2000, K=50

── MEMBACA BATASAN LEBIH DULU ──────────────────────────────
n <= 2000 dan K <= 50. Ini terlalu kecil untuk soal greedy
murni. Batasan sekecil ini justru mengundang solusi yang
"mahal" seperti aliran biaya minimum.

── MERUMUSKAN ULANG SOALNYA ────────────────────────────────
Kunci pengamatannya:

  Sehimpunan permintaan bisa dilayani oleh K mesin
  ⟺  pada SETIAP titik waktu, paling banyak K permintaan
     terpilih yang saling menindih.

Arah "hanya jika" jelas. Arah "jika" benar karena interval
membentuk graf interval, dan pada graf interval bilangan
kromatik sama dengan ukuran klik maksimum — yaitu tumpang
tindih maksimum. Jadi kalau tumpang tindihnya tidak pernah
melebihi K, K mesin selalu cukup. (Ini persis fakta yang kita
pakai di Exercise 3.)

── MODEL ALIRAN ────────────────────────────────────────────
Kompres seluruh waktu (l dan r) menjadi titik 0..M-1 pada
sumbu bilangan. Bangun graf:

  - untuk tiap i: busur titik[i] -> titik[i+1]
                  kapasitas K, biaya 0
                  (ini "waktu berjalan tanpa memakai mesin")
  - untuk tiap permintaan (l, r, p):
                  busur titik(l) -> titik(r)
                  kapasitas 1, biaya -p
  - alirkan tepat K unit dari titik 0 ke titik M-1

Setiap unit aliran adalah satu mesin yang berjalan sepanjang
sumbu waktu. Kalau unit itu melewati busur permintaan, mesin
tersebut melayani permintaan itu. Kapasitas 1 memastikan tiap
permintaan dilayani paling banyak sekali. Kapasitas K pada
busur waktu memastikan tidak pernah lebih dari K mesin
"berjalan" — persis batasan tumpang tindih di atas.

Total biaya minimum = negatif dari total bayaran maksimum.

── KENAPA MCMF, BUKAN MAX FLOW BIASA ───────────────────────
Kita tidak memaksimalkan jumlah permintaan, melainkan total
bayaran. Bayaran diwakili biaya negatif, dan kita mencari
biaya minimum untuk aliran sebesar K. Karena biayanya negatif,
Dijkstra biasa tidak bisa dipakai langsung — gunakan SPFA
(Bellman-Ford berbasis antrean) untuk mencari lintasan
terpendek pada setiap augmentasi.

Grafnya tidak punya siklus berbiaya negatif karena semua busur
mengarah maju sepanjang sumbu waktu; busur balik yang muncul
dari residual ditangani dengan benar oleh SPFA.

── ALTERNATIF KALAU K = 1 ──────────────────────────────────
Dengan K = 1 soal ini menjadi Exercise 5 (weighted interval
scheduling) dan bisa diselesaikan O(n log n) dengan DP.
Uji: sampel 1 memakai K = 1 dan jawabannya 8, yang bisa kamu
periksa dengan tangan: [3,6) p=6 lalu [6,8) p=2.

── JEBAKAN ─────────────────────────────────────────────────
1. Menyangka jawabannya bisa didapat dengan menjalankan
   weighted interval scheduling sebanyak K kali. Tidak bisa —
   sama seperti Exercise 4, pilihan putaran pertama merusak
   putaran berikutnya.
2. Lupa mengompres koordinat waktu (r sampai 10^9).
3. Memakai Dijkstra dengan biaya negatif.
4. Lupa long long pada akumulasi biaya.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct MCMF {
    struct E { int to; ll cap, cost; };
    vector<E> e;
    vector<vector<int>> g;
    int n;

    MCMF(int n) : g(n), n(n) {}

    void add(int u, int v, ll cap, ll cost) {
        g[u].push_back(e.size()); e.push_back({v, cap, cost});
        g[v].push_back(e.size()); e.push_back({u, 0, -cost});
    }

    // Alirkan paling banyak 'need' unit dari s ke t, biaya minimum.
    // Mengembalikan {aliran, biaya}.
    pair<ll, ll> jalankan(int s, int t, ll need) {
        ll flow = 0, cost = 0;
        const ll INF = LLONG_MAX / 4;
        while (flow < need) {
            vector<ll> d(n, INF);
            vector<int> pe(n, -1);
            vector<char> inq(n, 0);
            deque<int> q;
            d[s] = 0; q.push_back(s); inq[s] = 1;

            // SPFA: biaya boleh negatif
            while (!q.empty()) {
                int u = q.front(); q.pop_front(); inq[u] = 0;
                for (int id : g[u]) {
                    if (e[id].cap <= 0) continue;
                    int v = e[id].to;
                    if (d[u] + e[id].cost < d[v]) {
                        d[v] = d[u] + e[id].cost;
                        pe[v] = id;
                        if (!inq[v]) { inq[v] = 1; q.push_back(v); }
                    }
                }
            }
            if (d[t] >= INF) break;          // tidak ada lintasan lagi

            // berapa banyak yang bisa dialirkan lewat lintasan ini
            ll push = need - flow;
            for (int v = t; v != s; v = e[pe[v] ^ 1].to)
                push = min(push, e[pe[v]].cap);
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) {
                e[pe[v]].cap -= push;
                e[pe[v] ^ 1].cap += push;
            }
            flow += push;
            cost += push * d[t];
        }
        return {flow, cost};
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll K;
    if (!(cin >> n >> K)) return 0;
    vector<ll> L(n), R(n), P(n);
    vector<ll> ts;
    for (int i = 0; i < n; i++) {
        cin >> L[i] >> R[i] >> P[i];
        ts.push_back(L[i]);
        ts.push_back(R[i]);
    }

    // Kompresi koordinat waktu.
    sort(ts.begin(), ts.end());
    ts.erase(unique(ts.begin(), ts.end()), ts.end());
    int M = ts.size();
    auto id = [&](ll x) {
        return (int)(lower_bound(ts.begin(), ts.end(), x) - ts.begin());
    };

    MCMF f(M);
    // busur waktu berjalan: kapasitas K, biaya 0
    for (int i = 0; i + 1 < M; i++) f.add(i, i + 1, K, 0);
    // busur permintaan: kapasitas 1, biaya -p
    for (int i = 0; i < n; i++) f.add(id(L[i]), id(R[i]), 1, -P[i]);

    auto [flow, cost] = f.jalankan(0, M - 1, K);
    (void)flow;

    cout << -cost << '\n';
    return 0;
}
