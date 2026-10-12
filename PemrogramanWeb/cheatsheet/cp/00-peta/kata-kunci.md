# Kata kunci soal → file

[← 00-peta](README.md) · [Cara kenali soal](cara-kenali-soal.md) · [Indeks CP](../README.md)

Kalimat soal adalah peta, bukan teka-teki sastra. Satu frasa seperti “jumlah pada rentang yang tidak berubah” hampir selalu membuka prefix, bukan segment tree. File ini memetakan **kalimat → folder/file**. Batasan `n` tetap wajib dibaca di [cara-kenali-soal.md](cara-kenali-soal.md); kata kunci tanpa `n` bisa menyesatkan.

Semua contoh pernyataan di bawah **diciptakan untuk belajar**. Jangan menyalin soal berhak cipta dari Codeforces / AtCoder / buku. Semua kode: `#include <bits/stdc++.h>`, `typedef long long ll`, `FASTIO`, **0-indexed**.

## Daftar isi

- [Cara membaca kalimat](#cara-membaca-kalimat)
- [Array dan rentang](#array-dan-rentang)
- [Greedy dan konstruktif](#greedy-dan-konstruktif)
- [Graf dan pohon](#graf-dan-pohon)
- [Dynamic programming](#dynamic-programming)
- [String](#string)
- [Geometri](#geometri)
- [Teori permainan](#teori-permainan)
- [Kata yang menipu](#kata-yang-menipu)
- [Contoh kerja 1: jumlah kotak](#contoh-kerja-1-jumlah-kotak)
- [Contoh kerja 2: tas dan pecahan](#contoh-kerja-2-tas-dan-pecahan)
- [Contoh kerja 3: kota dan jalan](#contoh-kerja-3-kota-dan-jalan)
- [Contoh kerja 4: pola teks](#contoh-kerja-4-pola-teks)
- [Contoh kerja 5: dua tumpukan batu](#contoh-kerja-5-dua-tumpukan-batu)
- [Contoh kerja 6: pagar dan titik](#contoh-kerja-6-pagar-dan-titik)
- [Peta keputusan singkat](#peta-keputusan-singkat)
- [Ringkasan](#ringkasan)

---

## Cara membaca kalimat

**Teori:** Analoginya membaca resep: “panggang 20 menit” lebih penting daripada “sajikan hangat”. Di soal CP, tiga lapisan dibaca berurutan: (1) objek yang diminta (angka, objek, ya/tidak), (2) operasi yang diizinkan (ubah, potong, kunjungi), (3) batasan. Kata kunci adalah lapisan 2. Alasan benar: banyak soal memakai cerita berbeda dengan operasi yang sama. “Kota dan jalan” = graf. “Hari dan rapat” = interval. “Huruf dan pola” = string. Cerita berubah; senjata tidak.

**Kapan:** selalu, sebelum mengetik loop. Jangan hanya karena judul “Graph” jika inputnya array tanpa sisi. Jangan percaya satu kata “optimal” — itu hampir semua soal.

**Proses:** pernyataan mini (diciptakan): “Diberi `n` bilangan. Ada `q` pertanyaan. Tiap pertanyaan memberi `l r` (0-based). Array tidak berubah. Cetak jumlah `a[l]+…+a[r]`.”

1. Objek: angka jumlah.
2. Operasi: query rentang, data diam.
3. Kata “tidak berubah” menolak Fenwick.
4. Buka [03-array/prefix-difference.md](../03-array/prefix-difference.md).
5. Jika nanti ada “ubah posisi `i` jadi `x`”, pindah ke [10 Fenwick](../10-struktur-data/fenwick.md).

**Kode:** pemetaan kata → folder, hanya sebagai pengingat, bukan classifier ajaib.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string folderDariKalimat(const string& s) {
    string t = s;
    for (char& c : t) c = (char)tolower(c);
    if (t.find("jumlah") != string::npos && t.find("tidak berubah") != string::npos)
        return "03-array/prefix-difference.md";
    if (t.find("ubah posisi") != string::npos && t.find("jumlah") != string::npos)
        return "10-struktur-data/fenwick.md";
    if (t.find("kota") != string::npos && t.find("jalan") != string::npos)
        return "08-graf/dfs-bfs.md";
    return "00-peta/cara-kenali-soal.md";
}

int main() {
    FASTIO;
    string a = "jumlah rentang, array tidak berubah";
    string b = "ubah posisi i, lalu jumlah l r";
    cout << folderDariKalimat(a) << '\n';
    cout << folderDariKalimat(b) << '\n';
    return 0;
}
```

**Jebakan:**
1. Memetakan “minimum” selalu ke greedy.
2. Mengabaikan `t` tes dan `sum n`.
3. Menyalin soal orang ke cheatsheet.

**Kompleksitas:** berpikir O(1) per kalimat kunci. Salah folder = TLE atau WA, bukan O-notation.

---

## Array dan rentang

**Teori:** Array adalah barisan indeks. Kalimat yang menyebut `l r`, subarray, prefix, atau “tiap elemen sebagai minimum” hampir selalu folder [03-array](../03-array/README.md) atau [10-struktur-data](../10-struktur-data/README.md).

**Kapan:** ada indeks linier. Jangan jika hubungan adalah sisi graf.

**Proses:** baca kolom kiri, buka kolom kanan. Jangan hafal 80 file; hafal keluarga.

| Kalimat (diciptakan) | File |
|---|---|
| jumlah `[l,r]`, array diam | [prefix-difference.md](../03-array/prefix-difference.md) |
| banyak query jumlah pada matriks diam | [prefix-2d.md](../03-array/prefix-2d.md) |
| tambah `+v` pada persegi, lalu baca akhir | [prefix-2d.md](../03-array/prefix-2d.md) |
| tambah `+v` pada `[l,r]`, satu kali cetak array | [prefix-difference.md](../03-array/prefix-difference.md) |
| subarray jumlah maksimum | [kadane.md](../03-array/kadane.md) |
| dua ujung bergerak, syarat jumlah / beda | [two-pointers-window.md](../03-array/two-pointers-window.md) |
| window tetap `k`, maksimum | [mono-stack-deque.md](../03-array/mono-stack-deque.md) |
| next greater / suhu berikutnya lebih panas | [mono-stack-deque.md](../03-array/mono-stack-deque.md) |
| persegi terluas di histogram batang | [histogram-kontribusi.md](../03-array/histogram-kontribusi.md) |
| jumlah semua subarray-minimum | [histogram-kontribusi.md](../03-array/histogram-kontribusi.md) |
| berapa subarray yang `a[i]` jadi min | [histogram-kontribusi.md](../03-array/histogram-kontribusi.md) |
| nilai sampai `1e9`, indeks kecil | [kompresi.md](../03-array/kompresi.md) |
| update titik + jumlah prefix | [fenwick.md](../10-struktur-data/fenwick.md) |
| update titik + min rentang | [segment-tree.md](../10-struktur-data/segment-tree.md) |
| update rentang + query rentang | [lazy.md](../10-struktur-data/lazy.md) |
| min/max/gcd rentang, array diam | [sparse-table.md](../10-struktur-data/sparse-table.md) |
| banyak query offline, beda unik | [persistent-sqrt-mo.md](../10-struktur-data/persistent-sqrt-mo.md) |
| inversi pasangan `i<j`, `a[i]>a[j]` | [merge-inversi.md](../04-sorting-searching/merge-inversi.md) |
| cari `x` terurut, atau “minimum yang cukup” | [binary-search.md](../04-sorting-searching/binary-search.md) |
| fungsi naik lalu turun | [ternary.md](../04-sorting-searching/ternary.md) |
| `n ≤ 40`, subset jumlah | [meet-in-the-middle.md](../04-sorting-searching/meet-in-the-middle.md) |

**Kode:** deteksi “data diam + jumlah”.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string senjataRentang(bool adaUpdate, bool hanyaJumlah, bool data2D) {
    if (!adaUpdate && data2D) return "prefix-2d";
    if (!adaUpdate && hanyaJumlah) return "prefix-1d";
    if (!adaUpdate) return "sparse-table";
    if (hanyaJumlah) return "fenwick";
    return "segtree";
}

int main() {
    FASTIO;
    cout << senjataRentang(false, true, false) << '\n'; // prefix-1d
    cout << senjataRentang(false, true, true) << '\n';  // prefix-2d
    cout << senjataRentang(true, true, false) << '\n';  // fenwick
    return 0;
}
```

**Jebakan:**
1. Prefix untuk min — tidak ada invers.
2. Fenwick untuk data diam — berlebihan, bukan salah.
3. Histogram dikira Kadane.

**Kompleksitas:** prefix query O(1) setelah O(n). Struktur data `O(log n)` per operasi.

---

## Greedy dan konstruktif

**Teori:** Kata “ambil yang berakhir paling cepat”, “gabung dua tumpukan terkecil”, “isi tas boleh dipotong” adalah greedy mapan. Kata “cetak sembarang permutasi yang sah” adalah konstruktif. Kata “optimal” sendirian **bukan** bukti greedy.

**Kapan:** ada kriteria sort yang bisa ditukar. Jangan jika kapasitas plus nilai utuh.

| Kalimat | File |
|---|---|
| rapat, pilih sebanyak mungkin yang tidak tabrakan | [interval-exchange.md](../06-greedy/interval-exchange.md) |
| gabungkan interval yang bersentuhan | [interval-exchange.md](../06-greedy/interval-exchange.md) |
| tutupi `[S,T]` dengan potongan minimum | [interval-exchange.md](../06-greedy/interval-exchange.md) |
| semua janji harus masuk, berapa ruang | [interval-exchange.md](../06-greedy/interval-exchange.md) |
| minimalkan jumlah waktu selesai `Σ C_i` | [interval-exchange.md](../06-greedy/interval-exchange.md) |
| pekerjaan `(durasi, deadline)`, sebanyak mungkin | [huffman-jadwal.md](../06-greedy/huffman-jadwal.md) |
| gabung file / batu, **pasangan mana saja** | [huffman-jadwal.md](../06-greedy/huffman-jadwal.md) |
| kode prefix, frekuensi huruf | [huffman-jadwal.md](../06-greedy/huffman-jadwal.md) |
| tas boleh pecah (minyak, serbuk) | [huffman-jadwal.md](../06-greedy/huffman-jadwal.md) |
| tas **tidak** boleh pecah | [05-01-knapsack.md](../09-dp/05-01-knapsack.md) |
| “ambil maksimum kelihatan benar” | [kapan-dp.md](../06-greedy/kapan-dp.md) |
| cetak objek sah, banyak jawaban | [konstruktif.md](../06-greedy/konstruktif.md) |
| permutasi / matriks / pewarnaan | [konstruktif.md](../06-greedy/konstruktif.md) |

**Proses:** “Diberi `n` pekerjaan. Tiap pekerjaan durasi `t_i` dan tenggat `d_i`. Satu mesin. Berapa banyak yang bisa selesai `≤ d_i`?”

1. Bukan knapsack: tidak ada nilai berbeda aneh.
2. Urut tenggat, heap buang terpanjang.
3. File: [huffman-jadwal.md](../06-greedy/huffman-jadwal.md).
4. Jika tiap pekerjaan punya **nilai** tidak monoton terhadap durasi → [09-dp](../09-dp/README.md).
5. Jika boleh potong pekerjaan → pecahan, tetap greedy.

**Kode:** pecahan vs utuh diputus di fungsi `tasApa` pada contoh kerja 2 di bawah.

**Jebakan:**
1. Huffman untuk **batu bersebelahan saja** — itu range DP.
2. Greedy rasio pada 0-1 knapsack.
3. Activity selection berbobot — DP.

**Kompleksitas:** hampir semua greedy klasik `O(n log n)`.

---

## Graf dan pohon

**Teori:** Entitas + hubungan = graf. Jika `m = n-1` dan terhubung, itu pohon. Kata “kapasitas pipa” = flow. Kata “A atau B harus benar” = 2-SAT.

**Kapan:** input menyebut sisi, tetangga, kota-jalan, persahabatan. Jangan memaksa graf pada array murni.

| Kalimat | File |
|---|---|
| daftar sisi, kunjungi semua tercapai | [dfs-bfs.md](../08-graf/dfs-bfs.md) |
| grid `.` `#`, daerah terhubung | [flood-komponen.md](../08-graf/flood-komponen.md) |
| apakah bisa 2 warna / tidak ada siklus ganjil | [siklus-bipartit.md](../08-graf/siklus-bipartit.md) |
| deteksi siklus terarah / tak terarah | [siklus-bipartit.md](../08-graf/siklus-bipartit.md) |
| prasyarat kuliah, urutan pengerjaan | [topo-dp-dag.md](../08-graf/topo-dp-dag.md) |
| jalur terpanjang di DAG | [topo-dp-dag.md](../08-graf/topo-dp-dag.md) |
| lintasan melewati tiap sisi sekali | [euler.md](../08-graf/euler.md) |
| state (posisi, sisa kunci), langkah unweighted | [bfs-state.md](../08-graf/bfs-state.md) |
| jarak, bobot sisi `≥ 0` | [dijkstra.md](../08-graf/dijkstra.md) |
| ada bobot negatif, deteksi siklus negatif | [bellman-floyd.md](../08-graf/bellman-floyd.md) |
| jarak semua pasangan, `n ≤ 400` | [bellman-floyd.md](../08-graf/bellman-floyd.md) |
| minimal biaya agar semua terhubung | [dsu-mst.md](../08-graf/dsu-mst.md) |
| “apakah A dan B satu komponen setelah tambah sisi” | [dsu-mst.md](../08-graf/dsu-mst.md) |
| komponen kuat terarah | [scc-bridge.md](../08-graf/scc-bridge.md) |
| jembatan / titik artikulasi | [scc-bridge.md](../08-graf/scc-bridge.md) |
| syarat “A atau B”, implikasi | [sat2-flow.md](../08-graf/sat2-flow.md) |
| kapasitas, aliran maksimum | [sat2-flow.md](../08-graf/sat2-flow.md) |
| matching bipartit | [sat2-flow.md](../08-graf/sat2-flow.md) |
| `n` simpul, `n-1` sisi, terhubung | [11-pohon/README.md](../11-pohon/README.md) |
| nenek moyang bersama, jarak di pohon | [lca.md](../11-pohon/lca.md) |
| diameter pohon | [diameter-euler.md](../11-pohon/diameter-euler.md) |
| query jalur + update di pohon | [hld-centroid.md](../11-pohon/hld-centroid.md) |
| gabung himpunan anak, `n log n` | [small-to-large.md](../11-pohon/small-to-large.md) |

**Proses:** “`n` kota, `m` jalan berarah berbobot, beberapa bobot negatif. Ada jalur dari 1 ke `n` yang bisa makin murah tanpa batas?”

1. Bukan Dijkstra.
2. Bellman-Ford + tandai tercapai dari siklus.
3. [bellman-floyd.md](../08-graf/bellman-floyd.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string senjataGraf(bool adaNegatif, bool allPairs, bool mst, bool pohon) {
    if (pohon) return "11-pohon";
    if (mst) return "dsu-mst";
    if (allPairs) return "floyd";
    if (adaNegatif) return "bellman";
    return "dijkstra-atau-bfs";
}

int main() {
    FASTIO;
    cout << senjataGraf(true, false, false, false) << '\n';
    cout << senjataGraf(false, false, true, false) << '\n';
    cout << senjataGraf(false, false, false, true) << '\n';
    return 0;
}
```

**Jebakan:**
1. Dijkstra pada negatif.
2. Floyd pada `n = 2000`.
3. Mengira pohon butuh MST — sudah pohon.

**Kompleksitas:** BFS `O(n+m)`, Dijkstra `O(m log n)`, Bellman `O(nm)`, Floyd `O(n³)`.

---

## Dynamic programming

**Teori:** Kata “ambil atau tidak”, “sisa kapasitas”, “dua string”, “digit dari kiri”, “himpunan yang sudah dipakai” adalah DP. Tulis STATE dalam satu kalimat sebelum tabel.

**Kapan:** overlapping + keputusan. Jangan DP jika greedy terbukti.

| Kalimat | File |
|---|---|
| overlapping, fondasi | [01-prinsip.md](../09-dp/01-prinsip.md) |
| memo versus tabel | [02-topdown-bottomup.md](../09-dp/02-topdown-bottomup.md) |
| tangga, frog, rumah | [03-linear-1d.md](../09-dp/03-linear-1d.md) |
| koin boleh diulang | [04-coin-unbounded.md](../09-dp/04-coin-unbounded.md) |
| barang paling banyak sekali | [05-01-knapsack.md](../09-dp/05-01-knapsack.md) |
| apakah subset jumlah `S` | [06-subset-sum.md](../09-dp/06-subset-sum.md) |
| stok terbatas per barang | [07-bounded-knapsack.md](../09-dp/07-bounded-knapsack.md) |
| subsequence menaik terpanjang | [08-lis.md](../09-dp/08-lis.md) |
| dua string, LCS / edit | [09-lcs-edit.md](../09-dp/09-lcs-edit.md) |
| jalur di grid, rintangan | [10-grid.md](../09-dp/10-grid.md) |
| gabung selang / matrix chain | [11-range.md](../09-dp/11-range.md) |
| cetak pilihan, bukan hanya angka | [12-rekonstruksi.md](../09-dp/12-rekonstruksi.md) |
| memori ketat, rolling | [13-memori.md](../09-dp/13-memori.md) |
| state aneh, desain dulu | [14-state-lanjut.md](../09-dp/14-state-lanjut.md) |
| `n ≤ 20`, keliling kota | [15-bitmask-tsp.md](../09-dp/15-bitmask-tsp.md) |
| penugasan himpunan | [16-bitmask-assignment.md](../09-dp/16-bitmask-assignment.md) |
| jumlah atas subset | [17-sos.md](../09-dp/17-sos.md) |
| hitung `x` di `[A,B]` syarat digit | [18-digit.md](../09-dp/18-digit.md) |
| DP dari anak ke ayah | [19-tree.md](../09-dp/19-tree.md) |
| knapsack di pohon | [20-knapsack-pohon.md](../09-dp/20-knapsack-pohon.md) |
| setiap simpul jadi akar | [21-reroot.md](../09-dp/21-reroot.md) |
| ekspektasi / probabilitas | [22-probabilitas.md](../09-dp/22-probabilitas.md) |
| OR/AND banyak subset, bitset | [23-bitset.md](../09-dp/23-bitset.md) |
| menang/kalah pada DAG | [24-game.md](../09-dp/24-game.md) |
| tiling baris, profil rusak | [25-broken-profile.md](../09-dp/25-broken-profile.md) |
| min `y = m x + c` banyak garis | [26-cht.md](../09-dp/26-cht.md) |
| titik potong optimal monoton | [27-dnc-knuth.md](../09-dp/27-dnc-knuth.md) |
| gabung batu **hanya tetangga** | [11-range.md](../09-dp/11-range.md) |
| `n ≤ 20` assignment | [16-bitmask-assignment.md](../09-dp/16-bitmask-assignment.md) |

**Proses:** “`n ≤ 18` kota, jarak lengkap, mulai 0, kunjungi semua, kembali.”

1. `n!` TLE.
2. State himpunan + kota terakhir.
3. [15-bitmask-tsp.md](../09-dp/15-bitmask-tsp.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string pilihDp(int n, bool duaString, bool knapsackUtuh, bool digit) {
    if (n <= 20) return "bitmask";
    if (duaString) return "lcs-edit";
    if (knapsackUtuh) return "01-knapsack";
    if (digit) return "digit-dp";
    return "tulis STATE dulu";
}

int main() {
    FASTIO;
    cout << pilihDp(18, false, false, false) << '\n';
    cout << pilihDp(1000, true, false, false) << '\n';
    cout << pilihDp(100, false, true, false) << '\n';
    return 0;
}
```

**Jebakan:**
1. DP tanpa STATE tertulis.
2. Bitmask pada `n = 40`.
3. Range DP pada gabung **bebas pasangan** (itu Huffman).

**Kompleksitas:** baca `n` dulu. `n·W`, `n²`, `2^n·n²` harus dihitung.

---

## String

**Teori:** Teks, pola, palindrom, awalan, banyak pola sekaligus. Hash cepat tapi perlu dua modulus. KMP/Z deterministik.

**Kapan:** input string, bukan array angka murni. Jangan hash jika butuh bukti 100% tanpa collision plan.

| Kalimat | File |
|---|---|
| banding potongan `s[l..r]` sering | [hashing.md](../12-string/hashing.md) |
| cari pola `p` di teks `s` | [kmp.md](../12-string/kmp.md) |
| prefix function, periode | [kmp.md](../12-string/kmp.md) |
| Z-array, berapa awalan cocok | [z-manacher.md](../12-string/z-manacher.md) |
| palindrom terpanjang / semua radius | [z-manacher.md](../12-string/z-manacher.md) |
| kamus awalan, XOR bit | [trie.md](../12-string/trie.md) |
| banyak pola sekaligus | [sa-aho-sam.md](../12-string/sa-aho-sam.md) |
| LCP, suffix, substring distinct | [sa-aho-sam.md](../12-string/sa-aho-sam.md) |
| LCS dua string (bukan suffix) | [09-lcs-edit.md](../09-dp/09-lcs-edit.md) |
| anti-hash / birthday | [random-antihash.md](../16-teknik-kontes/random-antihash.md) |

**Proses:** “Diberi teks dan satu pola. Cetak semua posisi kemunculan.”

1. `n, m ≤ 1e6` → KMP atau Z, bukan `O(nm)`.
2. [kmp.md](../12-string/kmp.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string senjataString(bool banyakPola, bool palindrom, bool potonganSering) {
    if (banyakPola) return "aho-atau-sa";
    if (palindrom) return "manacher";
    if (potonganSering) return "hashing";
    return "kmp-atau-z";
}

int main() {
    FASTIO;
    cout << senjataString(false, false, false) << '\n';
    cout << senjataString(true, false, false) << '\n';
    cout << senjataString(false, true, false) << '\n';
    return 0;
}
```

**Jebakan:**
1. Satu modulus hash.
2. KMP pada banyak pola tanpa Aho.
3. LCS `n = 1e5` dua string — `O(n²)` mati.

**Kompleksitas:** KMP/Z `O(n+m)`, hash bangun `O(n)`, query `O(1)`.

---

## Geometri

**Teori:** Titik, cross product, hull, garis sapu. Integer dulu; `double` hanya jika terpaksa.

**Kapan:** koordinat, poligon, “titik di kiri garis”. Jangan geo jika “jarak” ternyata graf.

| Kalimat | File |
|---|---|
| kiri/kanan/lurus, luas, orientasi | [cross-hull.md](../13-geometri/cross-hull.md) |
| convex hull | [cross-hull.md](../13-geometri/cross-hull.md) |
| titik terdekat, garis bergerak | [sweep.md](../13-geometri/sweep.md) |
| irisan segmen, event `x` | [sweep.md](../13-geometri/sweep.md) |
| koordinat jadi indeks array | [kompresi.md](../03-array/kompresi.md) |

**Proses:** “`n` tiang di bidang. Keliling karet yang memeluk semua tiang.”

1. Convex hull.
2. [cross-hull.md](../13-geometri/cross-hull.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string senjataGeo(bool hull, bool terdekat) {
    if (hull) return "cross-hull";
    if (terdekat) return "sweep";
    return "cross dulu, jangan double";
}

int main() {
    FASTIO;
    cout << senjataGeo(true, false) << '\n';
    cout << senjataGeo(false, true) << '\n';
    return 0;
}
```

**Jebakan:**
1. `double` untuk cross.
2. Overflow `x1*y2` tanpa `ll`.
3. Sweep tanpa urutan event saat `x` sama.

**Kompleksitas:** hull `O(n log n)`, closest pair `O(n log n)`.

---

## Teori permainan

**Teori:** Giliran, impartial, tumpukan. XOR Nim. Grundy untuk gabungan permainan. Menang/kalah DAG jika aturan bergantung posisi berbobot aneh — itu [24-game.md](../09-dp/24-game.md).

**Kapan:** dua pemain bergiliran, informasi sempurna. Jangan Grundy pada permainan partizan (ada petak putih/hitam berbeda).

| Kalimat | File |
|---|---|
| tumpukan batu, ambil `1..k` | [nim-grundy.md](../14-game-theory/nim-grundy.md) |
| beberapa tumpukan independen | [nim-grundy.md](../14-game-theory/nim-grundy.md) |
| mex, Grundy, XOR | [nim-grundy.md](../14-game-theory/nim-grundy.md) |
| posisi pada DAG, menang/kalah | [24-game.md](../09-dp/24-game.md) |
| game + knapsack / state | [24-game.md](../09-dp/24-game.md) |

**Proses:** “Tiga tumpukan 3, 4, 5. Ambil sembarang dari satu tumpukan. Siapa menang?”

1. Nim klasik, XOR `3^4^5 = 2 ≠ 0` → first win.
2. [nim-grundy.md](../14-game-theory/nim-grundy.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool firstNimMenang(const vector<ll>& a) {
    ll x = 0;
    for (ll v : a) x ^= v;
    return x != 0;
}

int main() {
    FASTIO;
    cout << firstNimMenang({3, 4, 5}) << '\n'; // 1
    cout << firstNimMenang({1, 1}) << '\n';    // 0
    return 0;
}
```

**Jebakan:**
1. XOR ukuran tumpukan padahal aturan ambil terbatas aneh — hitung Grundy.
2. Game DP pada `n = 1e5` tanpa pola.
3. Mengira second selalu menang jika tumpukan sama tanpa cek aturan.

**Kompleksitas:** Nim `O(n)`. Grundy per posisi tergantung cabang.

---

## Kata yang menipu

**Teori:** Beberapa kata terdengar seperti algoritma tertentu, tetapi batasan atau syarat memindahkan folder. Analoginya “kopi” bisa minuman atau berkas.

**Kapan:** selalu cek ulang setelah menemukan kata pertama.

| Kata | Bisa berarti | Bukan otomatis |
|---|---|---|
| jarak | BFS / Dijkstra / geo | selalu Dijkstra |
| minimum | greedy / DP / binsearch on answer | selalu greedy |
| optimal | hampir semua | bukti |
| pohon | 11-pohon atau MST | Floyd |
| palindrom | Manacher / DP | selalu DP `n²` |
| subset | bitmask / knapsack / MITM | selalu `2^n` |
| query | prefix / BIT / Mo | selalu SegTree |
| interaktif | flush, binsearch | FASTIO buta |
| modulus | addmod / nCr | `double` |
| grid | flood / DP grid / geo | selalu graf `n²` simpul |

**Proses:** “Jarak antara dua titik di papan catur dengan kuda.”

1. Bukan Euclidean.
2. BFS state pada papan.
3. [bfs-state.md](../08-graf/bfs-state.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string jarakApa(bool adaSisiGraf, bool bobotPositif, bool papanLangkah) {
    if (papanLangkah) return "bfs-state";
    if (adaSisiGraf && bobotPositif) return "dijkstra";
    if (adaSisiGraf) return "bellman";
    return "geo-atau-baca-ulang";
}

int main() {
    FASTIO;
    cout << jarakApa(false, false, true) << '\n';
    cout << jarakApa(true, true, false) << '\n';
    return 0;
}
```

**Jebakan:** satu kata pertama mengunci folder yang salah.

**Kompleksitas:** dua menit baca ulang lebih murah dari dua jam WA.

---

## Contoh kerja 1: jumlah kotak

**Teori:** Latihan membaca pernyataan utuh, bukan satu kata.

**Kapan:** pola “grid + jumlah persegi + diam”.

**Proses:** pernyataan diciptakan:

```text
Kebun berbentuk n baris m kolom. Tiap petak punya apel a[i][j].
Ada q pertanyaan. Pertanyaan ke-k: baris r1..r2, kolom c1..c2
(0-based, inklusif). Kebun tidak berubah. n,m ≤ 800, q ≤ 1e5.
Cetak jumlah apel tiap pertanyaan.
```

Langkah:

1. Objek: jumlah submatriks.
2. Data diam → prefix 2D, bukan Fenwick 2D.
3. `n·m = 6.4e5` bangun aman, `q` query O(1).
4. Buka [prefix-2d.md](../03-array/prefix-2d.md).
5. `ll` karena `800·800·1e9`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<ll>> bangunP(const vector<vector<ll>>& a) {
    int n = (int)a.size(), m = (int)a[0].size();
    vector<vector<ll>> p(n + 1, vector<ll>(m + 1, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            p[i + 1][j + 1] = p[i][j + 1] + p[i + 1][j] - p[i][j] + a[i][j];
    return p;
}

ll kotak(const vector<vector<ll>>& p, int r1, int c1, int r2, int c2) {
    return p[r2 + 1][c2 + 1] - p[r1][c2 + 1] - p[r2 + 1][c1] + p[r1][c1];
}

int main() {
    FASTIO;
    vector<vector<ll>> a = {{1, 2}, {3, 4}};
    auto p = bangunP(a);
    cout << kotak(p, 0, 0, 1, 1) << '\n'; // 10
    return 0;
}
```

**Jebakan:** lupa `+ p[r1][c1]`. Indeks 1-based di soal, 0-based di kode.

**Kompleksitas:** bangun `O(nm)`, query `O(1)`.

---

## Contoh kerja 2: tas dan pecahan

**Teori:** Satu kata “tas” belum menentukan greedy atau DP.

**Kapan:** selalu tanya “boleh potong?”.

**Proses:** dua pernyataan diciptakan.

Pernyataan A:

```text
n jenis minyak. Jenis i volume w_i, nilai v_i. Tas kapasitas W.
Boleh mengambil pecahan. n ≤ 1e5.
```

Pernyataan B:

```text
n patung. Patung i berat w_i, nilai v_i. Tas W. Patung utuh.
n ≤ 100, W ≤ 1e5.
```

1. A: pecahan → rasio, [huffman-jadwal.md](../06-greedy/huffman-jadwal.md).
2. B: utuh → 0-1, [05-01-knapsack.md](../09-dp/05-01-knapsack.md).
3. Jika B punya `n ≤ 40`, `W` besar → MITM.
4. Jika B `n ≤ 20` tanpa W kecil → bitmask.
5. Jangan pakai A untuk B.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string tasApa(bool pecahan, int n, ll W) {
    if (pecahan) return "fractional greedy";
    if (n <= 40 && W > 2000000) return "mitm";
    return "01-knapsack";
}

int main() {
    FASTIO;
    cout << tasApa(true, 100000, 1e12) << '\n';
    cout << tasApa(false, 100, 100000) << '\n';
    cout << tasApa(false, 35, (ll)1e12) << '\n';
    return 0;
}
```

**Jebakan:** rasio `double` pada pecahan; loop mundur lupa pada 0-1.

**Kompleksitas:** pecahan `O(n log n)`, 0-1 `O(n W)`.

---

## Contoh kerja 3: kota dan jalan

**Teori:** Cerita kota hampir selalu graf, tetapi senjata mengikuti bobot dan pertanyaan.

**Kapan:** ada `m` pasangan.

**Proses:** pernyataan diciptakan:

```text
n kota, m jalan dua arah. Tiap jalan punya lama tempuh w ≥ 0.
Hitung lama minimum dari kota s ke semua kota.
n,m ≤ 1e5.
```

1. Unweighted? Tidak, ada `w`.
2. Negatif? Tidak.
3. Dijkstra, [dijkstra.md](../08-graf/dijkstra.md).
4. Jika “minimal jumlah w agar semua terhubung” → MST.
5. Jika “apakah tetap terhubung jika satu jalan rusak” → bridge.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string kotaJalan(bool wNonNeg, bool tanyaTerhubungMin, bool satuSisiKritis) {
    if (satuSisiKritis) return "scc-bridge";
    if (tanyaTerhubungMin) return "dsu-mst";
    if (wNonNeg) return "dijkstra";
    return "bellman";
}

int main() {
    FASTIO;
    cout << kotaJalan(true, false, false) << '\n';
    cout << kotaJalan(true, true, false) << '\n';
    cout << kotaJalan(true, false, true) << '\n';
    return 0;
}
```

**Jebakan:** BFS pada bobot tidak seragam. MST untuk jarak pasangan.

**Kompleksitas:** `O((n+m) log n)` Dijkstra heap.

---

## Contoh kerja 4: pola teks

**Teori:** “cari kemunculan” ≠ LCS.

**Kapan:** satu atau banyak pola.

**Proses:**

```text
Teks s panjang n, pola p panjang m. n,m ≤ 1e6.
Cetak berapa kali p muncul sebagai substring.
```

1. Bukan DP `n·m`.
2. KMP atau Z atau hash.
3. Hash perlu dua basis jika takut tabrakan.
4. Banyak pola berbeda → Aho.
5. [kmp.md](../12-string/kmp.md).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> prefFunc(const string& s) {
    int n = (int)s.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int hitungMuncul(const string& s, const string& p) {
    string t = p + "#" + s;
    auto pi = prefFunc(t);
    int m = (int)p.size(), ans = 0;
    for (int x : pi) if (x == m) ans++;
    return ans;
}

int main() {
    FASTIO;
    cout << hitungMuncul("abababa", "aba") << '\n'; // 3
    return 0;
}
```

**Jebakan:** overlap terlewat jika geser `+m`. Hash satu modulus.

**Kompleksitas:** `O(n+m)`.

---

## Contoh kerja 5: dua tumpukan batu

**Teori:** Cerita batu bisa Nim, bisa Huffman, bisa range DP.

**Kapan:** baca aturan gabung / ambil.

**Proses:** tiga pernyataan diciptakan.

```text
A. Dua pemain, satu tumpukan n, ambil 1..3. Siapa menang?
B. n tumpukan, gabung dua tumpukan mana saja, biaya = jumlah.
C. n batu berjajar, gabung hanya tetangga.
```

1. A → Nim/game, [nim-grundy.md](../14-game-theory/nim-grundy.md) atau [24-game.md](../09-dp/24-game.md).
2. B → Huffman, [huffman-jadwal.md](../06-greedy/huffman-jadwal.md).
3. C → range DP, [11-range.md](../09-dp/11-range.md).
4. Kata “batu” tidak menentukan.
5. Kata “tetangga” menentukan.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string batuApa(bool giliran, bool hanyaTetangga) {
    if (giliran) return "game";
    if (hanyaTetangga) return "range-dp";
    return "huffman";
}

int main() {
    FASTIO;
    cout << batuApa(true, false) << '\n';
    cout << batuApa(false, true) << '\n';
    cout << batuApa(false, false) << '\n';
    return 0;
}
```

**Jebakan:** memakai heap Huffman pada batu berjajar.

**Kompleksitas:** Huffman `O(n log n)`, range DP `O(n³)` atau Knuth `O(n²)`.

---

## Contoh kerja 6: pagar dan titik

**Teori:** “Titik di bidang” bisa hull atau compact + sweep, atau bahkan interval jika diproyeksi.

**Kapan:** ada koordinat `(x,y)`.

**Proses:**

```text
n tiang (x,y). Ada q pertanyaan: berapa tiang di dalam
persegi [x1,x2] × [y1,y2]? n,q ≤ 1e5. Tiang tidak bergerak.
```

1. Bukan prefix 2D mentah: koordinat `1e9`.
2. Kompresi + Fenwick 2D / sweep + Fenwick.
3. [kompresi.md](../03-array/kompresi.md) lalu [fenwick.md](../10-struktur-data/fenwick.md) / [sweep.md](../13-geometri/sweep.md).
4. Jika `n ≤ 2000` dan grid sudah kecil → [prefix-2d.md](../03-array/prefix-2d.md).
5. Jika minta keliling karet → hull, bukan query persegi.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string pagarTitik(bool queryPersegi, bool koordinatBesar, bool hull) {
    if (hull) return "cross-hull";
    if (queryPersegi && !koordinatBesar) return "prefix-2d";
    if (queryPersegi) return "kompresi+sweep/fenwick";
    return "baca soal lagi";
}

int main() {
    FASTIO;
    cout << pagarTitik(true, true, false) << '\n';
    cout << pagarTitik(true, false, false) << '\n';
    cout << pagarTitik(false, true, true) << '\n';
    return 0;
}
```

**Jebakan:** prefix 2D pada `x ≤ 1e9`. Sweep tanpa kompresi `y`.

**Kompleksitas:** kompresi `O(n log n)`, query log.

---

## Peta keputusan singkat

**Teori:** Setelah tabel, satu pohon keputusan mencegah lompat folder.

**Kapan:** 30 detik pertama.

**Proses:**

```text
Ada sisi / tetangga / kota-jalan?     → 08 atau 11
Ada string / pola / palindrom?        → 12 (atau LCS di 09)
Ada giliran dua pemain?               → 14 atau 09/24
Ada titik (x,y) dan cross/hull/sweep? → 13
Ada kapasitas + ambil utuh?           → 09 knapsack
Ada interval / deadline / pecahan?    → 06
Ada [l,r] pada array?                 → 03 atau 10
n ≤ 20 himpunan?                      → 09 bitmask
Tidak yakin?                          → cara-kenali-soal.md (baca n)
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string petaCepat(bool graf, bool str, bool game, bool geo, bool knapsack) {
    if (graf) return "08-atau-11";
    if (str) return "12";
    if (game) return "14-atau-24";
    if (geo) return "13";
    if (knapsack) return "09";
    return "03-06-atau-baca-n";
}

int main() {
    FASTIO;
    cout << petaCepat(true, false, false, false, false) << '\n';
    cout << petaCepat(false, true, false, false, false) << '\n';
    return 0;
}
```

**Jebakan:** menempuh dua folder sekaligus tanpa membuang satu.

**Kompleksitas:** pohon ini O(1) cabang.

---

## Ringkasan

**Teori:** Kata kunci memilih **keluarga** file. Batasan memilih **anggota** yang muat waktu. Keduanya wajib.

**Kapan:** setiap soal baru. File ini bukan pengganti bukti.

**Proses:** lima langkah tetap.

1. Tulis objek jawaban (angka / objek / ya-tidak).
2. Lingkari 2–4 kata operasi.
3. Cocokkan tabel di atas.
4. Cek `n`, `sum n`, update atau diam.
5. Buka file, tulis STATE atau kriteria greedy.

**Kode:** pengingat urutan, bukan AI.

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void urutanBaca() {
    cout << "1 objek\n2 kata operasi\n3 tabel\n4 batasan\n5 file\n";
}

int main() {
    FASTIO;
    urutanBaca();
    return 0;
}
```

**Jebakan:** menyalin pernyataan kontes berhak cipta ke catatan. Menebak dari judul. Mengabaikan overflow di [overflow-io.md](overflow-io.md).

**Kompleksitas:** 2–5 menit baca soal menghemat 50 menit coding salah senjata.

Lanjut: [overflow-io.md](overflow-io.md) sebelum mengetik `int` untuk jumlah, atau [cara-kenali-soal.md](cara-kenali-soal.md) untuk tabel `n`.
