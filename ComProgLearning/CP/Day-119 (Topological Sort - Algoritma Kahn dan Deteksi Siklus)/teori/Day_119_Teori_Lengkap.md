# Day 119 — Teori Lengkap: Topological Sort, Kahn & Deteksi Siklus

---

## 1. Masalah yang Sebenarnya Sedang Kita Pecahkan

Ada 6 mata kuliah. Beberapa punya prasyarat:

```
Kalkulus      -> Kalkulus Lanjut
Kalkulus      -> Fisika
Pemrograman   -> Struktur Data
Struktur Data -> Algoritma
Kalkulus Lanjut -> Algoritma
```

Pertanyaannya: **dalam urutan apa saya boleh mengambilnya, satu per semester,
supaya tidak pernah mengambil mata kuliah sebelum prasyaratnya selesai?**

Itulah topological sort. Bukan "mengurutkan" dalam arti kecil-ke-besar —
tidak ada nilai yang dibandingkan. Yang diurutkan adalah **ketergantungan**.

**Definisi formal.** Diberikan graf berarah `G = (V, E)`, urutan topologis
adalah permutasi seluruh simpul `v1, v2, ..., vn` sehingga untuk setiap edge
`(u -> v)`, posisi `u` lebih kecil daripada posisi `v`.

Cara membayangkannya: susun semua simpul pada satu garis horizontal. Urutan itu
topologis kalau **setiap panah menunjuk ke kanan**, tidak ada satu pun yang
menunjuk balik ke kiri.

---

## 2. Kapan Urutan Topologis Ada?

> **Teorema.** Urutan topologis ada **jika dan hanya jika** graf berarah
> tersebut tidak memiliki siklus (yaitu, ia sebuah **DAG** — Directed Acyclic
> Graph).

**Arah "kalau ada siklus maka tidak ada urutan".** Misalkan ada siklus
`a -> b -> c -> a`. Andaikan ada urutan topologis. Maka posisi(a) < posisi(b),
posisi(b) < posisi(c), dan posisi(c) < posisi(a). Digabung: posisi(a) <
posisi(a). Kontradiksi. Jadi tidak mungkin ada urutan.

**Arah sebaliknya (kalau DAG maka ada urutan).** Buktinya konstruktif — dan
konstruksinya persis algoritma Kahn di bagian 3. Kuncinya: **setiap DAG tak
kosong pasti punya minimal satu simpul dengan in-degree 0.** Kenapa? Kalau
setiap simpul punya minimal satu edge masuk, kita bisa berjalan mundur terus:
dari simpul mana pun, lompat ke pendahulunya, lalu ke pendahulunya lagi, dan
seterusnya. Karena simpul terbatas, cepat atau lambat kita mengunjungi simpul
yang sama dua kali — dan itu berarti siklus. Bertentangan dengan asumsi DAG.

Fakta kecil ini adalah **mesin** seluruh algoritma hari ini.

**Urutan topologis TIDAK unik.** Pada contoh mata kuliah di atas, `Kalkulus`
dan `Pemrograman` dua-duanya bebas prasyarat; siapa pun boleh duluan. Ini
penting saat mengerjakan soal: kalau jawabannya "urutan apa pun yang valid",
jangan bandingkan output-mu dengan satu string tetap.

---

## 3. Algoritma Kahn — Ide

Kahn adalah bukti di atas yang dijalankan berulang:

```
selama masih ada simpul:
    ambil simpul dengan in-degree 0     (pasti ada, kalau DAG)
    tulis ke hasil
    hapus simpul itu beserta semua edge keluarnya
```

Menghapus simpul `u` berarti mengurangi in-degree setiap tetangga `v`. Kalau
in-degree `v` jatuh ke 0, `v` kini bebas dan boleh diambil berikutnya.

Supaya tidak perlu menyapu seluruh simpul setiap iterasi untuk mencari yang
in-degree-nya 0, kita simpan mereka di sebuah **antrean**.

### Implementasi

```cpp
vector<int> kahn(int n, vector<vector<int>>& g) {
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; u++)
        for (int v : g[u]) indeg[v]++;

    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0) q.push(u);

    vector<int> ord;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ord.push_back(u);
        for (int v : g[u])
            if (--indeg[v] == 0) q.push(v);
    }
    return ord;
}
```

**Kompleksitas.** Menghitung in-degree menyapu semua edge sekali: `O(V + E)`.
Loop utama memasukkan setiap simpul ke antrean **tepat sekali** (karena
in-degree hanya menyentuh 0 sekali) dan menelusuri daftar tetangga setiap
simpul tepat sekali. Total `O(V + E)` waktu, `O(V)` memori.

---

## 4. Trace Manual

Graf (1-indexed), simpul = mata kuliah:

```
1 Pemrograman     1 -> 3
2 Kalkulus        2 -> 4,  2 -> 6
3 Struktur Data   3 -> 5
4 Kalkulus Lanjut 4 -> 5
5 Algoritma       (tidak ada keluar)
6 Fisika          (tidak ada keluar)
```

In-degree awal:

```
simpul :  1  2  3  4  5  6
indeg  :  0  0  1  1  2  1
```

| Langkah | Antrean | Ambil | Aksi | Hasil |
|---|---|---|---|---|
| 0 | [1, 2] | — | inisialisasi | [] |
| 1 | [2] | 1 | indeg[3] 1→0, push 3 | [1] |
| 2 | [3] | 2 | indeg[4] 1→0 push; indeg[6] 1→0 push | [1,2] |
| 3 | [4, 6] | 3 | indeg[5] 2→1 | [1,2,3] |
| 4 | [6] | 4 | indeg[5] 1→0, push 5 | [1,2,3,4] |
| 5 | [5] | 6 | tidak ada tetangga | [1,2,3,4,6] |
| 6 | [] | 5 | tidak ada tetangga | [1,2,3,4,6,5] |

`ord.size() == 6 == n` → valid.

Perhatikan langkah 3: `5` **tidak** masuk antrean, karena in-degree-nya baru
turun dari 2 ke 1 — ia masih punya satu prasyarat yang belum diambil. Inilah
inti Kahn: sebuah simpul masuk antrean tepat pada saat prasyarat **terakhir**-nya
selesai.

---

## 5. Deteksi Siklus — Bagian Terpenting Hari Ini

Tambahkan satu edge sehingga terbentuk siklus: `5 -> 3`.

In-degree awal sekarang: `1:0, 2:0, 3:2, 4:1, 5:2, 6:1`.

Jalankan Kahn:

- ambil 1 → indeg[3] 2→1 (belum 0)
- ambil 2 → indeg[4] →0 push, indeg[6] →0 push
- ambil 4 → indeg[5] 2→1
- ambil 6 → —
- antrean **kosong**, tapi hasil baru berisi 4 simpul dari 6.

```
ord.size() = 4  !=  n = 6   =>  ADA SIKLUS
```

**Kenapa ini selalu benar?** Ambil simpul mana pun `c` yang berada di dalam
sebuah siklus. `c` punya pendahulu `p` yang juga di dalam siklus itu. Agar
in-degree `c` mencapai 0, `p` harus sudah dikeluarkan lebih dulu. Tapi argumen
yang sama berlaku untuk `p`: ia butuh pendahulunya keluar duluan. Mengelilingi
siklus, setiap anggota menunggu anggota lain — tidak ada yang bisa mulai.
Mereka semua (dan semua keturunannya yang bergantung pada mereka) tidak pernah
masuk hasil.

Sebaliknya, kalau tidak ada siklus, bukti di bagian 2 menjamin bahwa selama
masih ada simpul tersisa, selalu ada yang in-degree-nya 0 — jadi prosesnya
tidak pernah berhenti lebih awal, dan `ord.size() == n`.

> **Satu baris `if (ord.size() != n)` adalah detektor siklus lengkap untuk graf
> berarah.** Kamu tidak perlu DFS 3 warna kalau sudah menulis Kahn.

**Bonus: simpul mana yang ada di siklus?** Setiap simpul yang **tidak** muncul
di `ord` berada di dalam siklus atau bisa dicapai dari siklus.

---

## 6. Versi DFS (Post-order + Reverse)

Alternatif klasik:

```cpp
vector<int> ord;
vector<int> warna;   // 0 = belum, 1 = sedang di stack, 2 = selesai
bool adaSiklus = false;

void dfs(int u, vector<vector<int>>& g) {
    warna[u] = 1;
    for (int v : g[u]) {
        if (warna[v] == 1) { adaSiklus = true; return; }  // BACK EDGE
        if (warna[v] == 0) dfs(v, g);
    }
    warna[u] = 2;
    ord.push_back(u);          // PUSH SETELAH semua anak selesai
}
// panggil dfs untuk setiap simpul yang warnanya 0, lalu:
reverse(ord.begin(), ord.end());
```

**Kenapa post-order lalu dibalik?** `u` di-push hanya setelah seluruh simpul
yang bisa dicapai dari `u` sudah di-push. Jadi dalam daftar post-order, `u`
muncul **setelah** semua keturunannya. Membalik daftar membuat `u` muncul
**sebelum** semua keturunannya — persis definisi urutan topologis.

**Kenapa butuh 3 warna, bukan sekadar `visited`?** Warna 2 (sudah selesai)
bukan siklus — itu cuma edge lintas ke subtree yang sudah diproses. Hanya
warna 1 (masih di dalam stack rekursi saat ini) yang berarti kita menemukan
jalan balik ke leluhur — **back edge** — yaitu siklus. Memakai satu bit
`visited` akan menuduh graf punya siklus padahal tidak.

**Kahn atau DFS?**

| | Kahn | DFS |
|---|---|---|
| Bentuk | iteratif, aman untuk n besar | rekursif, risiko stack overflow di n ≈ 10^5+ |
| Deteksi siklus | `size != n`, gratis | butuh 3 warna |
| Leksikografis | tinggal ganti ke priority_queue | sulit |
| Level / longest path | alami | perlu usaha lebih |

Untuk kontes, **Kahn adalah pilihan default.**

---

## 7. Varian yang Sering Muncul

### 7.1 Urutan Leksikografis Terkecil

Ganti `queue` dengan min-heap. Kapan pun ada beberapa pilihan yang sah, ambil
nomor simpul terkecil.

```cpp
priority_queue<int, vector<int>, greater<int>> q;
```

Kompleksitas naik jadi `O((V + E) log V)`.

**Jebakan:** menjalankan Kahn biasa lalu `sort(ord)` di akhir adalah **salah**.
Hasil sort belum tentu urutan topologis sama sekali.

### 7.2 Apakah Urutannya Unik?

Urutan topologis unik **jika dan hanya jika** pada setiap iterasi antrean berisi
**tepat satu** simpul. Kalau pernah berisi ≥ 2, ada dua urutan sah berbeda.

```cpp
bool unik = true;
while (!q.empty()) {
    if (q.size() > 1) unik = false;
    ...
}
```

(Cara ekuivalen: urutan unik ⟺ ada **Hamiltonian path** di DAG-nya, yaitu
setiap simpul berurutan terhubung langsung.)

### 7.3 Level / Rantai Prasyarat Terpanjang

Berapa semester minimum kalau boleh mengambil banyak mata kuliah sekaligus?
Jawabannya = panjang rantai prasyarat terpanjang + 1.

```cpp
vector<int> lvl(n + 1, 0);
// di dalam loop Kahn, saat memproses edge u -> v:
lvl[v] = max(lvl[v], lvl[u] + 1);
// jawaban = max(lvl) + 1
```

Relaksasi ini **valid** karena saat `u` dikeluarkan, semua pendahulu `u` sudah
diproses, jadi `lvl[u]` sudah final. Ini pintu masuk ke Day 120.

### 7.4 Memodelkan Soal Menjadi Graf

Banyak soal topological sort tidak menyebut kata "graf" sama sekali:

- **Alien Dictionary** — diberi daftar kata yang sudah terurut menurut alfabet
  asing. Bandingkan tiap kata bersebelahan, cari huruf pertama yang berbeda:
  itu memberi satu edge `a -> b`. Lalu topo sort huruf-hurufnya.
- **Rekonstruksi ranking** dari hasil pertandingan "A mengalahkan B".
- **Urutan build / kompilasi** modul dengan dependensi.
- **Deteksi deadlock**: proses A menunggu resource yang dipegang B, dst.
  Siklus = deadlock.

Aturan arah yang selalu sama: **prasyarat menunjuk ke yang bergantung padanya.**
"A harus sebelum B" → edge `A -> B`.

Satu kasus khusus pada Alien Dictionary: kalau kata panjang muncul **sebelum**
prefiksnya (`"abcd"` lalu `"ab"`), datanya tidak konsisten — jawab invalid tanpa
membangun graf.

---

## 8. Kesalahan yang Paling Sering Terjadi

1. **Tidak mengecek `ord.size() == n`.** Program mencetak urutan yang cacat
   diam-diam. Selalu cek.
2. **Simpul terisolasi terlupakan.** In-degree 0, tidak punya edge — ia tetap
   bagian dari jawaban dan harus ikut diantrekan di awal.
3. **Arah edge terbalik.** Gejalanya: jawaban keluar persis kebalikan dari yang
   diharapkan. Tulis ulang kalimat soal jadi "X harus sebelum Y" sebelum
   membuat edge.
4. **`indeg` tidak direset** antar test case pada soal multi-kasus.
5. **`sort` di akhir** untuk leksikografis — sudah dibahas, salah.
6. **DFS satu bit `visited`** untuk deteksi siklus pada graf berarah — false
   positive.
7. **Rekursi DFS pada rantai 10^5 simpul** — stack overflow. Pakai Kahn.
8. **Self-loop `u -> u`** membuat in-degree u tidak pernah 0. Ini benar — memang
   tidak ada urutan. Tapi kalau soal menganggap self-loop diabaikan, saring dulu
   saat membaca input.
9. **Menganggap graf tak berarah** bisa di-topo-sort. Tidak bisa; konsepnya
   tidak terdefinisi.

---

## 9. Ringkasan

- Urutan topologis ada ⟺ graf adalah DAG.
- Kahn: hitung in-degree, antre yang nol, keluarkan, kurangi tetangga. `O(V+E)`.
- `ord.size() != n` ⟺ ada siklus. Detektor siklus paling murah untuk graf berarah.
- DFS post-order + reverse memberi hasil yang sama; butuh 3 warna untuk siklus.
- Leksikografis terkecil: `priority_queue`. Keunikan: antrean selalu berukuran 1.
- Level via relaksasi `lvl[v] = max(lvl[v], lvl[u]+1)` adalah jembatan ke DP di DAG (Day 120).
