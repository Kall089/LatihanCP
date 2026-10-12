# Day 127 — Teori Lengkap: Dijkstra dengan Priority Queue

---

## 1. Masalah

Diberikan graf berbobot `G = (V, E)` dan sebuah simpul sumber `s`. Cari jarak
terpendek dari `s` ke **setiap** simpul lain. ("Jarak" = total bobot edge
sepanjang jalur.)

BFS (Day 114) sudah menyelesaikan ini untuk graf **tak berbobot**, karena di
situ "terpendek" berarti "paling sedikit edge" dan BFS mengunjungi simpul
persis dalam urutan jarak. Begitu edge punya bobot berbeda, urutan itu rusak:
jalur dengan 1 edge berbobot 100 lebih panjang daripada jalur dengan 5 edge
berbobot 1.

Dijkstra memperbaikinya dengan mengganti antrean FIFO menjadi **antrean
prioritas**.

---

## 2. Ide Inti

Bagi simpul menjadi dua himpunan:

- **FINAL** — jarak terpendeknya sudah pasti.
- **SEMENTARA** — kita punya perkiraan `dist[v]`, tetapi mungkin masih bisa
  membaik.

Awalnya `dist[s] = 0`, semuanya lain `∞`, dan FINAL kosong.

```
ulangi V kali:
    pilih u dari SEMENTARA dengan dist[u] TERKECIL
    pindahkan u ke FINAL                          <- klaim: dist[u] sudah final
    untuk setiap tetangga v dari u:
        dist[v] = min(dist[v], dist[u] + w(u,v))  <- RELAKSASI
```

Seluruh algoritma bergantung pada klaim di baris ketiga. Bagian berikutnya
membuktikannya — dan bagian 5 menunjukkan apa yang terjadi kalau syaratnya
dilanggar.

---

## 3. Kenapa Simpul yang Dipilih Sudah Final

> **Klaim.** Jika semua bobot `≥ 0`, maka simpul `u` dengan `dist[u]` terkecil
> di antara simpul SEMENTARA sudah memiliki jarak terpendek yang benar.

**Bukti (kontradiksi).** Andaikan tidak: ada jalur `P` dari `s` ke `u` dengan
panjang `L < dist[u]`.

Jalur `P` berawal di `s` (FINAL) dan berakhir di `u` (SEMENTARA). Jadi di
suatu titik `P` harus **menyeberang** dari himpunan FINAL ke SEMENTARA. Sebut
edge penyeberangan pertamanya `(x → y)`, dengan `x` FINAL dan `y` SEMENTARA.

Karena `x` sudah FINAL, `dist[x]` benar, dan kita sudah merelaksasi `x`.
Karena itu `dist[y] ≤ dist[x] + w(x,y)` = panjang **prefiks** `P` sampai `y`.

Sekarang langkah kuncinya:

> panjang prefiks `P` sampai `y`  ≤  panjang seluruh `P`  =  `L`

Digabung: `dist[y] ≤ L < dist[u]`. Tapi `u` dipilih sebagai yang **terkecil**
di antara simpul SEMENTARA, dan `y` juga SEMENTARA. Kontradiksi. ∎

**Di mana persis asumsi "bobot ≥ 0" dipakai?** Pada satu baris:

```
panjang prefiks  <=  panjang seluruh jalur
```

Ini hanya benar kalau **sisa** jalur (dari `y` sampai `u`) punya total bobot
tidak negatif. Kalau sisa jalur bisa negatif, prefiksnya justru bisa **lebih
panjang** daripada keseluruhan, dan seluruh bukti runtuh.

Ingat kalimat ini. Itulah jawaban atas "kenapa Dijkstra gagal pada bobot
negatif" — bukan sekadar "karena tidak boleh".

---

## 4. Implementasi

### 4.1 Versi Standar

```cpp
typedef long long ll;
typedef pair<ll,int> pli;
const ll INF = LLONG_MAX / 4;

vector<ll> dijkstra(int n, vector<vector<pair<int,ll>>>& g, int s) {
    vector<ll> dist(n + 1, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;   // MIN-heap
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;                       // entri USANG
        for (auto& [v, w] : g[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}
```

Perhatikan: pasangan yang disimpan adalah `(jarak, simpul)` — jarak dulu,
supaya perbandingan default `pair` mengurutkan berdasarkan jarak.

### 4.2 Lazy Deletion — Kenapa `if (d > dist[u]) continue;`

Buku teks memakai operasi **decrease-key**: ketika `dist[v]` membaik, ubah
prioritas entri `v` yang sudah ada di dalam heap. `std::priority_queue` tidak
punya operasi itu.

Solusinya: **jangan mengubah, cukup push entri baru**. Akibatnya heap bisa
memuat beberapa entri untuk simpul yang sama, dengan nilai berbeda. Entri
dengan nilai terkecil akan keluar duluan (dan itu yang benar); sisanya adalah
sampah yang harus diabaikan:

```cpp
if (d > dist[u]) continue;
```

Konsekuensinya heap memuat sampai `O(E)` entri, bukan `O(V)`. Kompleksitasnya
menjadi `O(E log E)` = `O(E log V)` (karena `E ≤ V²`, `log E ≤ 2 log V`).
Sama saja secara asimtotik.

Menghilangkan baris itu **tidak membuat jawaban salah** — relaksasi ulang tidak
merusak apa pun — tetapi bisa membuat program jauh lebih lambat karena simpul
diproses berkali-kali.

Alternatif lain: `set<pair<ll,int>>` dengan `erase` manual untuk mensimulasikan
decrease-key. Lebih rapi secara teori, konstanta lebih besar dalam praktik.

### 4.3 Versi `O(V²)` Tanpa Heap

```cpp
for (int it = 0; it < n; it++) {
    int u = -1;
    for (int v = 1; v <= n; v++)
        if (!done[v] && (u == -1 || dist[v] < dist[u])) u = v;
    if (dist[u] == INF) break;
    done[u] = true;
    for (int v = 1; v <= n; v++)
        dist[v] = min(dist[v], dist[u] + w[u][v]);
}
```

Lebih baik dari versi heap kalau graf **sangat padat** (`E ≈ V²`), karena
`V² < E log V` di situ. Untuk kontes biasa, versi heap yang dipakai.

---

## 5. Kenapa Dijkstra Gagal Total pada Bobot Negatif

Ini bagian yang diminta hari ini. Kita tidak akan puas dengan "karena
syaratnya begitu" — kita akan melihatnya rusak.

### 5.1 Contoh Tandingan Minimal

Empat simpul:

```
1 -> 2  bobot  1
1 -> 3  bobot  10
2 -> 4  bobot  10
3 -> 4  bobot -20
```

Jarak terpendek `1 → 4` yang benar: lewat 3, yaitu `10 + (-20) = -10`.
Lewat 2: `1 + 10 = 11`. Jawaban benar: **−10**.

Jalankan Dijkstra:

| pop | d | aksi |
|---|---|---|
| (0, 1) | 0 | relaksasi: dist[2]=1, dist[3]=10 |
| (1, 2) | 1 | relaksasi: dist[4]= 1+10 = **11** |
| (10, 3) | 10 | relaksasi: 10 + (−20) = −10 < 11 → dist[4] = −10, push (−10,4) |
| (11, 4) | 11 | 11 > dist[4]=−10 → SKIP (usang) |
| (−10, 4) | −10 | — |

Menariknya, versi lazy-deletion di atas **kebetulan** memberi jawaban benar di
contoh ini, karena entri `(−10, 4)` masih sempat masuk heap. Itulah yang
membuat bug ini berbahaya: **kadang benar, kadang salah**, dan kamu tidak bisa
mengandalkannya.

### 5.2 Contoh yang Benar-Benar Salah

Sekarang tambahkan satu simpul supaya simpul yang "dikunci" ikut menyebarkan
nilai yang salah:

```
1 -> 2  bobot  1
1 -> 3  bobot  4
2 -> 4  bobot  0
3 -> 2  bobot -3
```

Jarak benar ke `4`: `1 → 3 → 2 → 4` = `4 − 3 + 0 = 1`.
Tapi `1 → 2` langsung juga 1, jadi dist[2] benar. Ubah sedikit:

```
1 -> 2  bobot  2
1 -> 3  bobot  1
3 -> 2  bobot -5
2 -> 4  bobot  1
```

Benar: `1 → 3 → 2 → 4` = `1 − 5 + 1 = −3`.

Dijkstra versi **klasik dengan `visited` yang mengunci** (implementasi buku
teks, atau implementasi yang menandai simpul saat dipop dan menolak
memprosesnya lagi):

| pop | aksi |
|---|---|
| 1 (0) | dist[2]=2, dist[3]=1 |
| 3 (1) | dist[2] = min(2, 1−5) = −4, push |
| 2 (−4) | dist[4] = −4+1 = −3 |

Versi lazy tetap benar di sini juga. Sekarang tukar bobotnya:

```
1 -> 2  bobot  1
1 -> 3  bobot  2
2 -> 4  bobot  5
3 -> 2  bobot -4
```

Benar: `1 → 3 → 2 → 4` = `2 − 4 + 5 = 3`. Lewat `1 → 2 → 4` = `6`.

Dijkstra dengan `visited` mengunci:

| pop | aksi |
|---|---|
| 1 (0) | dist[2]=1, dist[3]=2 |
| **2 (1)** | **KUNCI simpul 2**; dist[4] = 6 |
| 3 (2) | dist[2] = min(1, 2−4) = −2, tapi 2 sudah TERKUNCI → tidak diproses ulang |
| 4 (6) | selesai |

Jawaban Dijkstra: **6**. Jawaban benar: **3**. **Salah.**

### 5.3 Pelajaran Sebenarnya

Dua hal:

1. **Sumber kesalahannya bukan tanda minus itu sendiri, melainkan asumsi
   "sekali final, selamanya final".** Bobot negatif berarti sebuah jalur bisa
   memendek setelah simpulnya terlanjur dikunci.
2. **Versi lazy-deletion "sering" menyelamatkanmu — dan itu justru berbahaya.**
   Ia bisa memproses ulang simpul, jadi pada graf kecil hasilnya sering benar
   sehingga bug lolos dari pengujianmu. Tapi ia kehilangan jaminan
   kompleksitas: pada graf yang dirancang jahat, jumlah relaksasinya bisa
   **eksponensial**. Jadi bahkan versi yang "kebetulan benar" pun bisa TLE
   parah.

Kesimpulannya sederhana: **ada satu saja bobot negatif → jangan pakai
Dijkstra.**

### 5.4 Kalau Ada Bobot Negatif, Pakai Apa?

| Situasi | Alat | Kompleksitas |
|---|---|---|
| bobot negatif, graf umum | **Bellman-Ford** (Day 129) | `O(V·E)` |
| bobot negatif, graf **DAG** | **DP topologis** (Day 120) | `O(V + E)` |
| bobot negatif, semua pasangan | **Floyd-Warshall** (Day 131) | `O(V³)` |
| bobot negatif, tapi butuh cepat & banyak query | **Johnson** (reweighting) | `O(V·E + V·E log V)` |
| ada **siklus negatif** | jarak terpendek **tidak terdefinisi**; Bellman-Ford mendeteksinya | |

**Trik yang TIDAK berhasil:** menambahkan konstanta `C` ke semua bobot agar
non-negatif. Ini mengubah masalahnya, karena jalur dengan lebih banyak edge
mendapat tambahan lebih besar — jalur terpendek yang baru belum tentu sama.

---

## 6. Rekonstruksi Jalur

```cpp
vector<int> par(n + 1, 0);
// di dalam relaksasi:
if (dist[u] + w < dist[v]) { dist[v] = dist[u] + w; par[v] = u; pq.push(...); }

// telusuri balik:
vector<int> path;
for (int v = t; v; v = par[v]) { path.push_back(v); if (v == s) break; }
reverse(path.begin(), path.end());
```

Kalau `dist[t] == INF`, tidak ada jalur — cetak `-1` sebelum menelusuri.

Kumpulan seluruh edge `(par[v] → v)` membentuk **shortest path tree**.

---

## 7. Varian Penting

### 7.1 Menghitung Banyak Jalur Terpendek

```cpp
if (nd < dist[v])       { dist[v] = nd; cnt[v] = cnt[u]; pq.push({nd, v}); }
else if (nd == dist[v])   cnt[v] = (cnt[v] + cnt[u]) % MOD;
```

Pola yang sama dipakai untuk melacak jumlah edge minimum/maksimum di antara
jalur terpendek (CSES Investigation).

### 7.2 Minimax — Meminimalkan Edge TERMAHAL

"Cari jalur yang edge terbesarnya sekecil mungkin" (misalnya kapasitas
jembatan, LC 1631 Path With Minimum Effort). Cukup ganti operator:

```cpp
ll nd = max(dist[u], w);          // bukan dist[u] + w
if (nd < dist[v]) { dist[v] = nd; ... }
```

Kebenaran Dijkstra tetap terjaga karena `max(a, w) ≥ a` — sifat "tidak pernah
memperpendek" yang sama seperti bobot non-negatif.

### 7.3 Maximin — Bottleneck Terlebar

"Maksimalkan kapasitas minimum sepanjang jalur": pakai **max-heap** dan
`dist[v] = max(dist[v], min(dist[u], w))`.

### 7.4 Jalur Paling Andal (Probabilitas)

Bobot = probabilitas edge selamat, ingin memaksimalkan hasil kali. Pakai
max-heap dan `dist[v] = max(dist[v], dist[u] * p)`. Valid karena `0 ≤ p ≤ 1`
sehingga perkalian tidak pernah membesarkan — analog "bobot non-negatif".

### 7.5 State Tambahan: `dist[v][k]`

"Boleh menggratiskan sampai `k` edge" (CSES Flight Discount, LC 787):

```cpp
// heap menyimpan (jarak, simpul, kupon terpakai)
// relaksasi bayar : dist[v][k]   <- dist[u][k] + w
// relaksasi kupon : dist[v][k+1] <- dist[u][k]
```

Kompleksitas `O(K·E log(K·V))`. Cara pandangnya: kita menjalankan Dijkstra di
graf berlapis, bukan menambal Dijkstra.

### 7.6 Banyak Sumber

Push **semua** sumber ke heap di awal dengan `dist = 0`. Hasilnya jarak ke
sumber **terdekat**. Tidak butuh super-source.

---

## 8. Memilih Alat yang Tepat

| Kondisi | Alat terbaik | Kompleksitas |
|---|---|---|
| tak berbobot | BFS (Day 114) | `O(V+E)` |
| bobot hanya 0 dan 1 | BFS 0-1 dengan deque (Day 115) | `O(V+E)` |
| bobot ≥ 0, satu sumber | **Dijkstra** | `O(E log V)` |
| bobot ≥ 0, graf sangat padat | Dijkstra `O(V²)` | `O(V²)` |
| ada bobot negatif, DAG | DP topologis (Day 120) | `O(V+E)` |
| ada bobot negatif, umum | Bellman-Ford (Day 129) | `O(V·E)` |
| semua pasangan, V kecil | Floyd-Warshall (Day 131) | `O(V³)` |
| jalur TERPANJANG, DAG | DP topologis (Day 120) | `O(V+E)` |
| jalur TERPANJANG, umum | NP-hard | — |

---

## 9. Kesalahan yang Paling Sering Terjadi

1. **Dijkstra pada bobot negatif.** Sudah dibahas panjang lebar di bagian 5.
2. **`int` untuk `dist`** — `2·10^5 · 10^9` = `2·10^14`.
3. **`INF = LLONG_MAX`** — lalu `dist[u] + w` overflow. Pakai `LLONG_MAX/4`.
4. **Lupa `greater<>`** → max-heap → jawaban acak.
5. **`memset(dist, 0x3f, ...)` untuk `long long`** — menghasilkan
   `0x3f3f3f3f3f3f3f3f`, yang muat tapi jangan lupa ini bukan angka yang kamu
   kira; lebih aman `fill`/konstruktor `vector`.
6. **Menandai `visited` saat push, bukan saat pop** — simpul terkunci sebelum
   nilainya final.
7. **Graf tak berarah tapi hanya `g[u].push_back(v)`.**
8. **Lupa relaksasi memakai `dist[u]` yang sudah diperbarui** — pakai `d` dari
   heap atau `dist[u]`, keduanya sama setelah cek entri usang.
9. **Membalik tanda bobot untuk mencari jalur terpanjang.** Ini adalah
   kesalahan nomor 1 dalam pakaian berbeda.

---

## 10. Ringkasan

- Dijkstra: berulang kali keluarkan simpul SEMENTARA terdekat; jaraknya final.
- `O(E log V)` dengan min-heap dan lazy deletion (`if (d > dist[u]) continue;`).
- Kebenarannya bersandar pada satu baris bukti: **prefiks jalur tidak pernah
  lebih panjang daripada seluruh jalur** — yang hanya benar bila bobot ≥ 0.
- Bobot negatif melanggar itu; simpul yang sudah dikunci bisa ternyata belum
  final. Contoh tandingan 4 simpul ada di bagian 5.2.
- Bobot negatif → Bellman-Ford (umum) atau DP topologis (DAG).
- Ganti operator gabung untuk minimax, maximin, dan jalur terandal; tambah
  dimensi state untuk kupon/batas hop.
