/*
============================================================
✅ SOLUSI Exercise 5: Tenggat dengan Prasyarat
============================================================
Difficulty: Hard | Kompleksitas: O(n + m + n log n)

── IDE UTAMA: MODIFIKASI TENGGAT, LALU EDF ─────────────────
Kalau pekerjaan a harus selesai sebelum b dimulai, maka a
sebenarnya punya tenggat yang lebih ketat daripada yang
tertulis.

Seberapa ketat? Kalau b harus selesai pada waktu d[b] dan
memerlukan t[b] waktu, maka b harus MULAI paling lambat pada
d[b] - t[b]. Karena a harus selesai sebelum b mulai:

      d_efektif[a] = min( d[a],  d_efektif[b] - t[b] )

Perhatikan bahwa rumusnya memakai d_efektif[b], bukan d[b] —
sehingga efeknya merambat melalui seluruh rantai prasyarat.

── ARAH PEMROSESAN ─────────────────────────────────────────
Kita membutuhkan d_efektif[b] sebelum menghitung d_efektif[a],
padahal a mendahului b. Jadi kita harus memproses dari
pekerjaan AKHIR ke pekerjaan AWAL — yaitu urutan topologis
TERBALIK.

Kode di bawah menghitung urutan topologis biasa dengan Kahn,
lalu menyapunya dari belakang.

── KENAPA SETELAH ITU PRASYARAT BISA DIABAIKAN ─────────────
Ini bagian yang paling elegan dan paling mengejutkan.

Klaim: setelah tenggat dimodifikasi, jadwal EDF (urut
d_efektif menaik) OTOMATIS memenuhi seluruh prasyarat.

Alasannya: kalau a mendahului b, maka menurut rumus di atas
d_efektif[a] <= d_efektif[b] - t[b] < d_efektif[b] (karena
t[b] >= 1). Jadi a punya tenggat efektif yang benar-benar
lebih kecil, sehingga EDF pasti menempatkan a sebelum b.

Kita tidak perlu pemeriksaan tambahan sama sekali.

Klaim kedua: jadwal EDF atas tenggat efektif juga optimal untuk
tenggat ASLI. Ini karena setiap jadwal yang memenuhi prasyarat
otomatis memenuhi tenggat efektif dengan keterlambatan yang
sama atau lebih baik — modifikasi tenggat hanya membuat eksplisit
batasan yang sudah tersirat.

── POLA UMUM ───────────────────────────────────────────────
"Modifikasi masukan agar batasan tersirat menjadi eksplisit,
lalu jalankan algoritma sederhana yang sudah kamu punya."
Pola ini muncul di banyak soal. Kenali bentuknya.

── JEBAKAN ─────────────────────────────────────────────────
1. Memproses graf ke arah yang salah (dari awal ke akhir).
2. Memakai d[b] alih-alih d_efektif[b] dalam rumus. Efeknya
   tidak merambat melalui rantai panjang.
3. Masih memaksa pengurutan topologis saat menjadwalkan.
   Tidak perlu — EDF sudah menanganinya.
4. Overflow: d_efektif bisa menjadi sangat negatif setelah
   dikurangi berkali-kali. Pakai long long, dan sadari bahwa
   nilai negatif itu SAH (artinya pekerjaan itu sudah pasti
   terlambat).
5. Lupa bahwa keluarannya boleh negatif.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<ll> t(n), d(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> d[i];

    vector<vector<int>> adj(n);                  // a -> b (a sebelum b)
    vector<int> deg(n, 0);
    for (int e = 0; e < m; e++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        deg[b]++;
    }

    // urutan topologis (Kahn)
    vector<int> topo;
    topo.reserve(n);
    queue<int> q;
    for (int i = 0; i < n; i++) if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) if (--deg[v] == 0) q.push(v);
    }

    // sapu TERBALIK: butuh d_efektif penerus sebelum menghitung pendahulu
    for (int k = n - 1; k >= 0; k--) {
        int u = topo[k];
        for (int v : adj[u])
            d[u] = min(d[u], d[v] - t[v]);       // rumus tenggat efektif
    }

    // setelah modifikasi, EDF biasa sudah memenuhi seluruh prasyarat
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return d[a] < d[b]; });

    ll cur = 0, worst = LLONG_MIN;
    for (int i : ord) {
        cur += t[i];
        worst = max(worst, cur - d[i]);
    }

    cout << worst << '\n';
    return 0;
}
