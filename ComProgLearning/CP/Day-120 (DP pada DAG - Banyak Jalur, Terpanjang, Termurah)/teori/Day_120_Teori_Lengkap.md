# Day 120 — Teori Lengkap: DP pada DAG

---

## 1. Kenapa Materi Ini Datang Tepat Setelah Topological Sort

Kemarin (Day 119) kamu menutup dengan satu baris yang tampak sepele:

```cpp
lvl[v] = max(lvl[v], lvl[u] + 1);
```

Itu sudah DP. Hari ini kita menyadari bahwa baris tersebut adalah satu kasus
khusus dari kerangka yang jauh lebih luas — dan bahwa dengan mengganti dua atau
tiga simbol saja, kerangka yang sama menjawab pertanyaan yang kelihatannya
sangat berbeda.

---

## 2. Kenapa DAG Boleh Di-DP (dan Graf Bersiklus Tidak)

Dynamic programming butuh dua hal:

1. **Optimal substructure** — jawaban untuk `v` dibangun dari jawaban untuk
   pendahulu-pendahulu `v`.
2. **Urutan evaluasi bebas-siklus** — saat kita menghitung `dp[v]`, semua nilai
   yang ia butuhkan harus **sudah final**.

Syarat kedua itulah yang dipatahkan oleh siklus. Kalau `a -> b -> c -> a`, maka
`dp[a]` butuh `dp[c]`, yang butuh `dp[b]`, yang butuh `dp[a]`. Tidak ada titik
mulai. Lebih dari itu, pertanyaannya sendiri jadi tidak bermakna: kalau siklus
punya total bobot positif, "jalur terpanjang" adalah tak hingga (putari terus);
kalau kita menghitung jalur, jumlahnya juga tak hingga.

Pada DAG, urutan topologis memberi tepat apa yang dibutuhkan:

> **Klaim.** Jika `u` muncul sebelum `v` dalam urutan topologis untuk setiap
> edge `u -> v`, maka memproses simpul dalam urutan itu menjamin `dp[u]` sudah
> final ketika `u` diproses.

**Alasannya:** semua yang bisa memengaruhi `dp[u]` datang lewat edge yang MASUK
ke `u`, yaitu dari simpul-simpul yang menurut definisi berada **sebelum** `u` di
dalam urutan. Mereka semua sudah selesai diproses.

Efeknya: **DAG berperilaku seperti array satu dimensi.** Semua intuisi DP linear
yang kamu punya berlaku, hanya "indeks berikutnya" diganti "tetangga".

---

## 3. Dua Gaya: Pull dan Push

Ada dua cara menulis loop yang sama.

### PULL (backward) — "tarik dari pendahulu"

```cpp
for (int v : topo)
    for (int u : rev[v])           // butuh graf TERBALIK
        dp[v] = gabung(dp[v], f(dp[u], w(u,v)));
```

Terasa paling dekat dengan rumus rekursif di buku. Kelemahannya: kamu harus
membangun daftar adjacency terbalik.

### PUSH (forward) — "lempar ke penerus"

```cpp
for (int u : topo)
    for (auto [v, w] : g[u])       // graf ASLI
        dp[v] = gabung(dp[v], f(dp[u], w));
```

Saat `u` diambil dari urutan topologis, `dp[u]` **sudah final**, jadi aman
dipakai memperbarui siapa pun. Tidak butuh graf terbalik. **Ini gaya default
yang direkomendasikan.**

Keduanya `O(V + E)`. Sisa dokumen ini memakai PUSH.

---

## 4. Tiga Pertanyaan di Atas Satu Kerangka

Ini inti hari ini. Perhatikan bahwa **struktur loopnya identik**.

| | Banyak Jalur | Terpanjang | Termurah |
|---|---|---|---|
| arti `dp[v]` | berapa jalur `s → v` | jalur `s → v` terpanjang | jalur `s → v` termurah |
| `dp[s]` | `1` | `0` | `0` |
| simpul lain | `0` | `-INF` | `+INF` |
| gabung | `dp[v] += ...` (mod) | `dp[v] = max(...)` | `dp[v] = min(...)` |
| `f(dp[u], w)` | `dp[u]` (bobot diabaikan) | `dp[u] + w` | `dp[u] + w` |
| elemen netral | 0 untuk `+` | `-INF` untuk `max` | `+INF` untuk `min` |

Kenapa nilai awal simpul lain berbeda-beda? Karena masing-masing adalah
**elemen identitas** dari operator penggabungnya: `0 + x = x`,
`max(-INF, x) = x`, `min(+INF, x) = x`. Kalau kamu salah memilihnya, jawaban
akan tercemar sejak langkah pertama.

### 4.1 Banyak Jalur

```cpp
const long long MOD = 1e9 + 7;
vector<long long> dp(n + 1, 0);
dp[s] = 1;
for (int u : topo)
    for (int v : g[u])
        dp[v] = (dp[v] + dp[u]) % MOD;
// jawaban: dp[t]
```

**Kenapa benar:** setiap jalur `s → t` melewati tepat satu edge terakhir
`u → t`. Jadi jumlah jalur ke `t` adalah jumlah dari jumlah jalur ke setiap
pendahulunya. Tidak ada jalur yang terhitung dua kali karena edge terakhirnya
berbeda.

**Modulo wajib.** Pada DAG dengan 30 simpul saja jumlah jalur bisa melampaui
`2^30`. Soal hampir selalu meminta hasil modulo `10^9+7`.

### 4.2 Jalur Terpanjang

```cpp
const long long NEG = LLONG_MIN / 4;
vector<long long> dp(n + 1, NEG);
dp[s] = 0;
for (int u : topo) {
    if (dp[u] == NEG) continue;          // <-- WAJIB
    for (auto [v, w] : g[u])
        dp[v] = max(dp[v], dp[u] + w);
}
```

Baris `if (dp[u] == NEG) continue;` bukan optimasi — ia **benar-benar
diperlukan**. Tanpanya, simpul yang tidak bisa dicapai dari `s` akan
"merelaksasi" tetangganya dengan `NEG + w`, dan nilai palsu itu menular ke
seluruh graf. Gejalanya: jawaban berupa angka negatif raksasa yang aneh.

> **Jalur terpanjang pada graf UMUM adalah NP-hard** (ia memuat Hamiltonian
> path sebagai kasus khusus). Pada DAG ia selesai dalam waktu linear. Perbedaan
> ini menjelaskan kenapa banyak soal susah payah membuktikan dulu bahwa
> grafnya DAG.

### 4.3 Jalur Termurah

Sama persis dengan 4.2, hanya `max → min`, `NEG → POS`.

```cpp
const long long POS = LLONG_MAX / 4;
vector<long long> dp(n + 1, POS);
dp[s] = 0;
for (int u : topo) {
    if (dp[u] == POS) continue;
    for (auto [v, w] : g[u])
        dp[v] = min(dp[v], dp[u] + w);
}
```

**Kapan ini lebih baik daripada Dijkstra (Day 127)?**

- Kalau grafnya DAG dan ada **bobot negatif**: Dijkstra memberi jawaban salah,
  DP ini benar, dan lebih cepat (`O(V+E)` vs `O(E log V)`).
- Kalau butuh jalur **terpanjang**: Dijkstra tidak bisa sama sekali.
- Kalau butuh **menghitung** jalur: DP alami, Dijkstra perlu tambahan.

Dijkstra unggul kalau grafnya **bersiklus** (dan bobotnya non-negatif) — di
situ tidak ada urutan topologis untuk dipakai.

---

## 5. Trace Manual

DAG berbobot, `s = 1`, `t = 5`:

```
1 -> 2 (w 3)
1 -> 3 (w 2)
2 -> 4 (w 4)
3 -> 4 (w 1)
3 -> 5 (w 7)
4 -> 5 (w 2)
```

Urutan topologis: `1 2 3 4 5`.

**Banyak jalur (dp awal: 1,0,0,0,0)**

| proses | aksi | dp setelah |
|---|---|---|
| 1 | dp[2]+=1, dp[3]+=1 | 1,1,1,0,0 |
| 2 | dp[4]+=1 | 1,1,1,1,0 |
| 3 | dp[4]+=1, dp[5]+=1 | 1,1,1,2,1 |
| 4 | dp[5]+=2 | 1,1,1,2,3 |

`dp[5] = 3`. Cek manual: `1-2-4-5`, `1-3-4-5`, `1-3-5`. ✓

**Terpanjang (dp awal: 0,−INF,−INF,−INF,−INF)**

| proses | aksi | dp setelah |
|---|---|---|
| 1 | dp[2]=3, dp[3]=2 | 0,3,2,−,− |
| 2 | dp[4]=max(−,3+4)=7 | 0,3,2,7,− |
| 3 | dp[4]=max(7,2+1)=7, dp[5]=2+7=9 | 0,3,2,7,9 |
| 4 | dp[5]=max(9,7+2)=9 | 0,3,2,7,9 |

`dp[5] = 9`, lewat `1-3-5`. Cek: `1-2-4-5 = 3+4+2 = 9`; seri, keduanya 9. ✓

**Termurah (dp awal: 0,+INF,...)**

| proses | aksi | dp setelah |
|---|---|---|
| 1 | dp[2]=3, dp[3]=2 | 0,3,2,∞,∞ |
| 2 | dp[4]=7 | 0,3,2,7,∞ |
| 3 | dp[4]=min(7,3)=3, dp[5]=9 | 0,3,2,3,9 |
| 4 | dp[5]=min(9,3+2)=5 | 0,3,2,3,5 |

`dp[5] = 5`, lewat `1-3-4-5 = 2+1+2 = 5`. ✓

Tiga jawaban berbeda (3, 9, 5) dari loop yang identik.

---

## 6. Rekonstruksi Jalur

Nilai saja jarang cukup; soal biasanya minta jalurnya.

```cpp
vector<int> par(n + 1, 0);
for (int u : topo) {
    if (dp[u] == NEG) continue;
    for (auto [v, w] : g[u])
        if (dp[u] + w > dp[v]) {      // HANYA saat benar-benar membaik
            dp[v] = dp[u] + w;
            par[v] = u;               // catat DI SINI
        }
}
// telusuri balik
vector<int> path;
for (int v = t; v != 0; v = par[v]) path.push_back(v);
reverse(path.begin(), path.end());
```

Dua kesalahan klasik:

- **Menulis `par[v] = u` di luar `if`** — parent-nya jadi edge terakhir yang
  dilihat, bukan edge terbaik.
- **Memakai `>=` alih-alih `>`** — pada kasus seri, parent bisa menunjuk balik
  dan menciptakan lingkaran saat ditelusuri.

Kalau `dp[t]` masih sentinel, tidak ada jalur sama sekali → cetak IMPOSSIBLE
sebelum menelusuri.

---

## 7. Varian yang Sering Muncul

### 7.1 Termurah + Menghitung Ada Berapa yang Termurah

Simpan dua array. Saat merelaksasi:

```cpp
if (dp[u] + w < dp[v]) { dp[v] = dp[u] + w; cnt[v] = cnt[u]; }
else if (dp[u] + w == dp[v]) cnt[v] = (cnt[v] + cnt[u]) % MOD;
```

Ini pola yang sama nanti muncul di CSES "Investigation" untuk Dijkstra.

### 7.2 Banyak Sumber / Banyak Tujuan

- "Jalur terpanjang di seluruh graf, boleh mulai dan berakhir di mana saja":
  inisialisasi `dp[u] = 0` untuk **semua** `u`, lalu jawabannya `max(dp)`.
- "Mulai dari salah satu dari k simpul": tambahkan **super-source** `0` dengan
  edge berbobot 0 ke masing-masing.

### 7.3 DAG yang Tersembunyi

Banyak soal DP yang tidak menyebut graf sebenarnya adalah DP di DAG:

- **Grid** (Day 150): setiap sel adalah simpul, edge ke kanan dan ke bawah.
  DAG-nya jelas karena gerakannya selalu maju.
- **LIS** (Day 148): edge `i -> j` kalau `i < j` dan `a[i] < a[j]`. LIS =
  jalur terpanjang. (Versi eksplisit ini `O(n^2)`; Day 148 mempercepatnya.)
- **Coin change**: simpul = sisa uang, edge = memakai satu koin.
- **Kondensasi SCC** (Day 132): graf bersiklus apa pun bisa diciutkan menjadi
  DAG komponen, lalu di-DP.

### 7.4 DP dengan State Tambahan

Kalau state-nya bukan cuma simpul (misalnya "sudah pakai berapa tiket diskon"),
buat `dp[v][k]`. Urutan topologis tetap mengendalikan dimensi simpul; dimensi
tambahan diproses di dalamnya. Kompleksitas `O((V + E) * K)`.

---

## 8. Kesalahan yang Paling Sering Terjadi

1. **Tidak melewati simpul bersentinel** → nilai `-INF + w` menular. Paling
   sering. Gejalanya angka negatif raksasa.
2. **Lupa modulo** pada penghitungan jalur.
3. **Memproses simpul dengan urutan lain** (nomor simpul, urutan input). Hanya
   urutan topologis yang menjamin `dp[u]` final.
4. **DP di graf bersiklus** tanpa mengecek. Selalu verifikasi `ord.size() == n`.
5. **`int` untuk total bobot** — `2*10^5 * 10^9` jauh melampaui `int`.
6. **Rekonstruksi dengan `par` di luar `if`**.
7. **Membalik tanda bobot agar Dijkstra mencari terpanjang** — Dijkstra tidak
   boleh bobot negatif; hasilnya salah.
8. **"Banyak jalur" vs "banyak jalur terpendek"** — dua soal berbeda. Yang
   kedua butuh min dan count bersamaan (7.1).
9. **Mengasumsikan `s` selalu simpul 1.** Baca soal.

---

## 9. Ringkasan

- Urutan topologis = urutan evaluasi DP yang benar untuk DAG.
- Kerangka PUSH: `for u in topo: for (v,w) in g[u]: dp[v] = gabung(dp[v], f(dp[u], w))`.
- Ganti `init`, `gabung`, dan `f` untuk berpindah dari "banyak jalur" ke
  "terpanjang" ke "termurah". Loopnya tidak berubah.
- Sentinel harus **dilewati**, bukan sekadar diinisialisasi.
- Rekonstruksi: `par[v]` dicatat hanya saat `dp[v]` benar-benar membaik.
- DP-DAG **boleh** bobot negatif — sesuatu yang tidak dimiliki Dijkstra.
- Banyak DP yang tampak lain (grid, LIS, coin change) sebenarnya DP di DAG.
