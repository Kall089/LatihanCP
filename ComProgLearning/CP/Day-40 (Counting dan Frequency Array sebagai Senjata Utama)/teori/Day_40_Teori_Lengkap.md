# 📊 Day 40: Counting & Frequency Array sebagai Senjata Utama

> **Prasyarat:** Array (Day 7), Coordinate Compression (Day 38), Prefix Sum (Day 29)
> **Estimasi belajar:** 2–3 jam (teori + 6 latihan)
> **Kata kunci soal:** *"berapa kali muncul"*, *"anagram"*, *"pasangan dengan selisih K"*, *"paling sering"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 40, kamu akan mampu:

- [ ] Memilih **array** alih-alih `map` ketika domainnya kecil, dan tahu bedanya sebesar apa
- [ ] Memakai frekuensi untuk **anagram**, **mode**, dan **pasangan**
- [ ] Menghitung pasangan **berselisih K** dan **berjumlah K** dalam O(n)
- [ ] Menggabungkan frekuensi dengan **prefix sum** untuk query rentang nilai
- [ ] Memakai **frekuensi prefiks per huruf** untuk query substring
- [ ] Mengenali kapan `map` tetap lebih tepat daripada array
- [ ] Menghindari jebakan **membersihkan array** pada multi-test case

---

## 🔍 1. Konsep & Intuisi

### Ide dasar

```
cnt[v] = berapa kali nilai v muncul
```

Satu baris, tetapi ia mengubah banyak masalah O(n²) menjadi O(n).

### Analogi: kotak surat apartemen

Untuk mencari tahu siapa yang menerima surat terbanyak, kamu **tidak** perlu
membandingkan setiap penghuni dengan setiap penghuni lain. Kamu cukup memasang
kotak surat, memasukkan setiap surat ke kotak pemiliknya, lalu melihat kotak mana
yang paling penuh.

Array frekuensi adalah deretan kotak surat itu. Satu sapuan untuk memasukkan,
satu sapuan untuk membaca.

### Kenapa array, bukan map?

Keduanya menjawab pertanyaan yang sama. Bedanya konstanta, dan konstantanya besar.

```
array   : cnt[v]++      -> satu akses memori, ~1 ns
map     : cnt[v]++      -> pohon merah-hitam, ~100 ns  (log n perbandingan + alokasi)
unordered_map           -> ~30 ns, tetapi bisa di-hack di Codeforces
```

Untuk `n = 10^6`, selisihnya adalah 1 ms melawan 100 ms. Itu perbedaan antara AC
dan TLE pada soal yang batas waktunya ketat.

```
Domain nilai kecil (<= 10^6, atau alfabet 26)  -> ARRAY, selalu
Domain besar tapi n kecil                      -> kompresi (Day 38) lalu ARRAY
Domain besar dan nilai muncul online           -> map
```

### Dua pola sapuan yang harus dihafal

**Pola 1 — hitung dulu, baca kemudian:**

```cpp
for (int x : a) cnt[x]++;          // sapuan 1
for (int v = 0; v <= MAKS; v++)    // sapuan 2
    if (cnt[v] > 0) { /* ... */ }
```

**Pola 2 — hitung sambil jalan (untuk pasangan):**

```cpp
long long hasil = 0;
for (int x : a) {
    hasil += cnt[pasangan(x)];     // pasangkan dengan yang SUDAH lewat
    cnt[x]++;                      // baru daftarkan diri sendiri
}
```

Pola 2 sangat penting: menghitung **sebelum** mendaftarkan diri sendiri otomatis
menghindari elemen berpasangan dengan dirinya sendiri, dan otomatis menghitung setiap
pasangan tepat satu kali. Kalau urutannya dibalik, kedua jaminan itu hilang.

---

## 🧮 2. Analisis Kompleksitas

| Tugas | Waktu | Ruang |
| ----- | ----- | ----- |
| Bangun frekuensi | O(n) | O(V) |
| Mode (nilai paling sering) | O(n + V) | O(V) |
| Cek anagram | O(n + A) | O(A) |
| Pasangan berselisih K | O(n) atau O(n + V) | O(V) |
| Pasangan berjumlah K | O(n) | O(V) |
| Query "berapa nilai ≤ x" | O(V) preprocess, O(1) query | O(V) |
| Frekuensi prefiks per huruf | O(n·A) | O(n·A) |

`V` = ukuran domain nilai, `A` = ukuran alfabet.

⚠️ **Perhatikan `O(V)` pada ruang dan waktu.** Kalau `V = 10^6` dan ada `T = 10^5`
test case, membersihkan seluruh array setiap test case menjadi `10^11` operasi — TLE.
Solusinya dibahas di bagian 6.

---

## 💻 3. Implementasi C++

### 3.1 Frekuensi dasar

```cpp
const int MAKS = 1e6 + 5;
int cnt[MAKS];                      // global -> otomatis nol

for (int x : a) cnt[x]++;
```

Array global berukuran `10^6` int adalah 4 MB — aman. Deklarasi global juga
menghindarkanmu dari inisialisasi manual, karena variabel global otomatis nol.

### 3.2 Mode: nilai yang paling sering muncul

```cpp
int mode = -1, terbanyak = 0;
for (int v = 0; v < MAKS; v++)
    if (cnt[v] > terbanyak) { terbanyak = cnt[v]; mode = v; }
```

Kalau ada beberapa mode dan soal minta yang **terkecil**, pakai `>` (bukan `>=`)
seperti di atas. Kalau minta yang terbesar, pakai `>=`.

### 3.3 Anagram

```cpp
bool anagram(const string& s, const string& t) {
    if (s.size() != t.size()) return false;      // cek murah dulu
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'a']++;
    for (char c : t) if (--cnt[c - 'a'] < 0) return false;
    return true;
}
```

Trik `--cnt[...] < 0` menggabungkan dua sapuan menjadi satu: kalau `t` memakai huruf
lebih banyak dari yang tersedia, kita langsung tahu. Karena panjangnya sudah sama,
tidak perlu memeriksa sisa apa pun di akhir.

### 3.4 Pasangan dengan selisih tepat K

```cpp
// Menghitung pasangan indeks (i, j), i < j, dengan |a[i] - a[j]| == K
long long pasanganSelisih(const vector<int>& a, int K) {
    unordered_map<int, long long> cnt;
    long long hasil = 0;
    for (int x : a) {
        if (K == 0) hasil += cnt[x];             // pasangan nilai identik
        else {
            auto it1 = cnt.find(x - K);
            auto it2 = cnt.find(x + K);
            if (it1 != cnt.end()) hasil += it1->second;
            if (it2 != cnt.end()) hasil += it2->second;
        }
        cnt[x]++;                                // daftarkan SETELAH menghitung
    }
    return hasil;
}
```

⚠️ **`K == 0` harus dipisah.** Tanpa pemisahan, `x - 0` dan `x + 0` adalah nilai yang
sama, sehingga setiap pasangan terhitung dua kali.

### 3.5 Pasangan berjumlah K

```cpp
long long pasanganJumlah(const vector<int>& a, int K) {
    unordered_map<int, long long> cnt;
    long long hasil = 0;
    for (int x : a) {
        auto it = cnt.find(K - x);
        if (it != cnt.end()) hasil += it->second;
        cnt[x]++;
    }
    return hasil;
}
```

Perhatikan bahwa pola ini identik dengan "subarray jumlah = K" pada Day 29 —
hitung dulu, daftarkan kemudian. Pola yang sama muncul berulang kali; kenali bentuknya.

### 3.6 Frekuensi + prefix sum: query rentang nilai

*Berapa elemen yang nilainya antara L dan R?*

```cpp
for (int x : a) cnt[x]++;
for (int v = 1; v < MAKS; v++) cnt[v] += cnt[v - 1];   // jadi prefix

// jawaban untuk [L, R]:
int jawab = cnt[R] - (L > 0 ? cnt[L - 1] : 0);
```

Setelah diubah menjadi prefix, `cnt[v]` berarti *"berapa elemen yang nilainya ≤ v"*.
Ini transformasi kecil yang membuka banyak soal.

### 3.7 Frekuensi prefiks per huruf (untuk query substring)

*Berapa huruf 'a' di dalam `s[l..r]`?*

```cpp
int n = s.size();
vector<array<int, 26>> pre(n + 1);
pre[0].fill(0);
for (int i = 0; i < n; i++) {
    pre[i + 1] = pre[i];
    pre[i + 1][s[i] - 'a']++;
}

// query:
int jumlahHuruf = pre[r + 1][c] - pre[l][c];
```

Memori `O(26n)`. Untuk `n = 10^5` itu 2.6 juta int = ~10 MB — aman.
Untuk `n = 10^6` itu 104 MB — kemungkinan MLE, pertimbangkan cara lain.

### 3.8 Counting sort (pratinjau Day 46)

```cpp
void countingSort(vector<int>& a, int MAKS) {
    vector<int> cnt(MAKS + 1, 0);
    for (int x : a) cnt[x]++;
    int idx = 0;
    for (int v = 0; v <= MAKS; v++)
        while (cnt[v]--) a[idx++] = v;
}
```

O(n + V), mengalahkan `sort` ketika `V` kecil. Dibahas lengkap di Day 46.

---

## 🔄 4. Trace & Simulasi

### 4.1 Pasangan berselisih K = 2 pada `a = [1, 5, 3, 4, 2]`

```
cnt kosong, hasil = 0
```

| x | cari `x−2` | cari `x+2` | tambahan | hasil | cnt setelahnya |
| - | ---------- | ---------- | -------- | ----- | -------------- |
| 1 | −1 (tidak) | 3 (tidak) | 0 | 0 | {1:1} |
| 5 | 3 (tidak) | 7 (tidak) | 0 | 0 | {1:1, 5:1} |
| 3 | 1 (**ada, 1×**) | 5 (**ada, 1×**) | 2 | **2** | {1:1,5:1,3:1} |
| 4 | 2 (tidak) | 6 (tidak) | 0 | 2 | {...,4:1} |
| 2 | 0 (tidak) | 4 (**ada, 1×**) | 1 | **3** | {...,2:1} |

```
hasil = 3
Verifikasi manual: (1,3), (5,3), (4,2)  -> 3 pasangan  ✓
```

Perhatikan bahwa setiap pasangan terhitung **tepat sekali** — saat elemen yang lebih
belakang diproses. Itu efek langsung dari "hitung dulu, daftarkan kemudian".

### 4.2 Kalau urutannya dibalik (bug)

```
x = 3: cnt[3]++ DULU -> {1:1, 5:1, 3:1}
       lalu cari 1 dan 5 -> tetap 2

Untuk K = 0 baru terlihat rusaknya:
a = [7, 7]
BENAR  : x=7 -> hasil += cnt[7]=0 -> 0, cnt={7:1}
                x=7 -> hasil += cnt[7]=1 -> 1, cnt={7:2}     hasil 1  ✓
SALAH  : x=7 -> cnt={7:1}, hasil += cnt[7]=1 -> 1
                x=7 -> cnt={7:2}, hasil += cnt[7]=2 -> 3     hasil 3  ✗
```

Elemen berpasangan dengan dirinya sendiri. Urutan dua baris itu bukan gaya, melainkan
kebenaran.

### 4.3 Frekuensi menjadi prefix

```
a = [3, 1, 4, 1, 5]

cnt mentah  : indeks 0 1 2 3 4 5
              nilai  0 2 0 1 1 1

cnt prefix  : indeks 0 1 2 3 4 5
              nilai  0 2 2 3 4 5
                       ↑
              "ada 2 elemen bernilai <= 1"

Query "berapa elemen bernilai antara 2 dan 4?"
   cnt[4] - cnt[1] = 4 - 2 = 2      -> yaitu 3 dan 4   ✓
```

### 4.4 Anagram dengan satu sapuan

```
s = "listen", t = "silent"

setelah menghitung s:  e:1 i:1 l:1 n:1 s:1 t:1

memproses t:
   's' -> --cnt[s] = 0   ok
   'i' -> --cnt[i] = 0   ok
   'l' -> --cnt[l] = 0   ok
   'e' -> --cnt[e] = 0   ok
   'n' -> --cnt[n] = 0   ok
   't' -> --cnt[t] = 0   ok
   tidak pernah negatif -> anagram  ✓

s = "listen", t = "listee"
   't' -> --cnt[t] = 0   ok
   ...
   'e' kedua -> --cnt[e] = -1  -> BUKAN anagram, langsung berhenti  ✓
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "berapa kali x muncul" | frekuensi dasar |
| "nilai yang paling sering" | frekuensi + sapuan maksimum |
| "apakah dua string anagram" | frekuensi 26 huruf |
| "pasangan dengan selisih K" | hitung dulu, daftarkan kemudian |
| "pasangan dengan jumlah K" | pola yang sama |
| "berapa elemen bernilai ≤ x" | frekuensi + prefix sum |
| "berapa huruf 'c' di s[l..r]" | frekuensi prefiks per huruf |
| "elemen yang muncul lebih dari n/2 kali" | frekuensi, atau Boyer–Moore O(1) ruang |
| "urutkan nilai kecil" | counting sort (Day 46) |
| nilai sampai 10^9 | kompresi dulu (Day 38), baru frekuensi |

### Pattern: frekuensi dari frekuensi

Beberapa soal menanyakan *"berapa nilai yang muncul tepat k kali"*. Jawabannya
adalah menghitung frekuensi **dari** array frekuensi:

```cpp
for (int x : a) cnt[x]++;
for (int v = 0; v < MAKS; v++)
    if (cnt[v]) cntCnt[cnt[v]]++;      // berapa nilai yang muncul cnt[v] kali
```

Dua lapis penghitungan. Pola ini sering muncul di soal Div3 dan hampir selalu
terlewat oleh pemula.

### Pattern: majority element (Boyer–Moore)

Kalau soal menjamin ada elemen yang muncul **lebih dari** n/2 kali, ada solusi O(1) ruang:

```cpp
int kandidat = a[0], hitung = 0;
for (int x : a) {
    if (hitung == 0) kandidat = x;
    hitung += (x == kandidat) ? 1 : -1;
}
// kandidat pasti benar KALAU majority dijamin ada; kalau tidak, verifikasi ulang
```

Layak diketahui karena ia menunjukkan bahwa frekuensi tidak selalu perlu disimpan
seluruhnya.

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Membersihkan seluruh array pada multi-test case.** Ini penyebab TLE yang halus.

   ```cpp
   // SALAH: O(V) per test case
   while (T--) { memset(cnt, 0, sizeof cnt); ... }     // 10^5 * 10^6 = TLE

   // BENAR: bersihkan hanya yang dipakai
   while (T--) {
       for (int x : a) cnt[x]++;
       ... proses ...
       for (int x : a) cnt[x] = 0;                     // O(n), bukan O(V)
   }
   ```

   Alternatif elegan: array "cap waktu" (`stamp[v] == testCase` menandakan valid).

2. **Mendaftarkan diri sendiri sebelum menghitung.** Menghasilkan elemen berpasangan
   dengan dirinya sendiri.

3. **`K == 0` tidak dipisah** pada pasangan berselisih. Setiap pasangan terhitung dua kali.

4. **Overflow.** `n = 10^5` dengan semua elemen sama menghasilkan `n(n−1)/2 ≈ 5·10^9`
   pasangan. `long long` wajib untuk hitungan pasangan.

5. **Nilai negatif sebagai indeks.** Kalau `a[i]` bisa negatif, geser dengan offset
   (`cnt[x + OFFSET]`) atau kompres dulu.

6. **Array lokal berukuran besar.** `int cnt[1000000]` di dalam fungsi bisa menyebabkan
   stack overflow. Deklarasikan **global** atau pakai `vector`.

7. **Memakai `map` padahal domainnya kecil.** Kehilangan faktor 100 secara cuma-cuma.

8. **Lupa memeriksa panjang pada anagram.** `"abc"` dan `"abcd"` tidak akan tertangkap
   oleh pemeriksaan `--cnt < 0` saja.

### Edge cases wajib diuji

```
semua elemen sama          -> hitungan pasangan mencapai n(n-1)/2, cek overflow
K = 0                      -> pasangan berselisih nol, jangan hitung dua kali
n = 1                      -> tidak ada pasangan sama sekali
nilai negatif              -> butuh offset atau kompresi
string kosong pada anagram -> dua string kosong adalah anagram
multi test case            -> pastikan pembersihan array benar dan murah
```

---

## 🏆 7. Tips Contest

**Red flag → aksi:**

- Melihat *"berapa kali"*, *"paling sering"*, *"anagram"*, *"pasangan"* → array frekuensi.
  Ini adalah alat pertama yang harus dicoba, bukan yang terakhir.
- Melihat batas nilai `≤ 10^6` → array, bukan `map`. Tulis `const int MAKS = 1e6 + 5;`
  di atas dan lanjutkan.
- Melihat batas nilai `≤ 10^9` dengan `n ≤ 10^5` → kompresi (Day 38) lalu array.
- Melihat huruf kecil saja → `int cnt[26]`, dan hampir selalu itu cukup.

**Kebiasaan yang menyelamatkan:** deklarasikan array frekuensi sebagai **global**.
Ia otomatis nol, tidak membebani stack, dan tidak perlu diinisialisasi ulang di
soal satu-test-case.

**Untuk multi-test case,** langsung tulis pembersihan berbasis elemen (`for (int x : a)
cnt[x] = 0;`) sebagai refleks. Menulis `memset` di dalam loop test case adalah cara
paling umum mendapat TLE pada soal yang sebenarnya mudah.

**Manajemen waktu:** array frekuensi seharusnya jadi dalam < 1 menit. Kalau sebuah soal
Div3 A/B terasa sulit, tanyakan *"apakah ini bisa diselesaikan dengan menghitung
sesuatu?"* — jawabannya sangat sering ya.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  COUNTING & FREQUENCY ARRAY
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  const int MAKS = 1e6 + 5;
  int cnt[MAKS];                 <- GLOBAL: otomatis nol, tidak bebani stack

  POLA 1: hitung dulu, baca kemudian
    for (x : a) cnt[x]++;
    for (v : domain) if (cnt[v]) ...

  POLA 2: pasangan -- hitung SEBELUM mendaftarkan diri
    for (x : a) { hasil += cnt[pasangan(x)]; cnt[x]++; }
    urutan ini otomatis: tidak berpasangan dengan diri sendiri,
                         setiap pasangan terhitung sekali

  selisih K : hasil += cnt[x-K] + cnt[x+K]     (K == 0 HARUS dipisah!)
  jumlah K  : hasil += cnt[K-x]
  anagram   : cnt[26], lalu --cnt < 0 -> bukan (cek panjang dulu)
  <= x      : ubah cnt jadi prefix sum
  substring : pre[i+1] = pre[i]; pre[i+1][c]++   O(26n) memori

  PILIH ALAT
    domain <= 1e6        -> array
    domain besar, n kecil -> kompresi (Day 38) lalu array
    online / domain tak terbatas -> map

  MULTI TEST CASE: bersihkan per ELEMEN, bukan memset seluruh array
  OVERFLOW       : hitungan pasangan bisa 5e9 -> long long
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CSES 1621 — Distinct Numbers](https://cses.fi/problemset/task/1621) | CSES | nilai berbeda |
| [CSES 1640 — Sum of Two Values](https://cses.fi/problemset/task/1640) | CSES | pasangan berjumlah K |
| [LeetCode 242 — Valid Anagram](https://leetcode.com/problems/valid-anagram/) | LeetCode | anagram |
| [LeetCode 169 — Majority Element](https://leetcode.com/problems/majority-element/) | LeetCode | mode / Boyer–Moore |
| [LeetCode 1200 — Minimum Absolute Difference](https://leetcode.com/problems/minimum-absolute-difference/) | LeetCode | frekuensi + sort |
| [CF 1520A/B — soal Div3](https://codeforces.com/problemset) | Codeforces | latihan counting |
| [ABC 205 B / ABC 155 C](https://atcoder.jp/) | AtCoder | frekuensi dasar |
| [SPOJ AGGRCOW / TDPRIMES](https://www.spoj.com/) | SPOJ | sieve = frekuensi juga |

---

**Selanjutnya:** Day 41–42 adalah hari latihan terpadu dan review untuk seluruh
teknik array (Day 29–40). Setelah itu Day 43 memulai blok **sorting**, di mana
counting sort hari ini akan muncul kembali sebagai algoritma pengurutan penuh.
