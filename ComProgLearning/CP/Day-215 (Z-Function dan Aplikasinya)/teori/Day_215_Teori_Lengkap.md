# 📊 Day 215: Z-Function & Aplikasinya

> **Prasyarat:** KMP & tabel pi (Day 213), Aplikasi pi (Day 214)
> **Estimasi belajar:** 3–4 jam (teori + 6 latihan)
> **Kata kunci soal:** *"cocok berapa huruf dari posisi i"*, *"awalan bersama"*, *"cari pola"*, *"periode"*

---

## 🎯 Tujuan Pembelajaran

Setelah menyelesaikan Day 215, kamu akan mampu:

- [ ] Mendefinisikan `z[i]` dengan tepat dan membedakannya dari `pi[i]`
- [ ] Membangun Z-array dalam **O(n)** dan menjelaskan peran **z-box `[l, r]`**
- [ ] Membuktikan kenapa `r` **tidak pernah mundur** sehingga totalnya linear
- [ ] Mencari pola dengan trik `pola + '#' + teks`
- [ ] Menurunkan **periode**, **border**, dan **cek rotasi** dari Z-array
- [ ] Menghitung **jumlah substring berbeda** dan **kompresi string** dengan Z
- [ ] Memilih antara **Z-function dan prefix function** secara sadar, bukan asal

---

## 🔍 1. Konsep & Intuisi

### Definisi

```
z[i] = panjang string TERPANJANG yang sekaligus
         - awalan dari S, dan
         - awalan dari S[i..n-1]

z[0] didefinisikan 0 (atau n; pilih satu, konsisten — di sini kita pakai 0)
```

Dengan kata lain: **"kalau aku menempelkan salinan S di posisi i, berapa huruf yang cocok?"**

```
S = a a b c a a b x a a b c a a b
i :  0 1 2 3 4 5 6 7 8 9 ...

z[4]:  S      = a a b c a a b ...
       S[4..] = a a b x a a b ...
                ✓ ✓ ✓ ✗          -> z[4] = 3

z[8]:  S      = a a b c a a b x ...
       S[8..] = a a b c a a b     -> z[8] = 7 (sampai habis)

z[1]:  S      = a a b ...
       S[1..] = a b c ...
                ✓ ✗              -> z[1] = 1
```

### pi vs z — dua pertanyaan berbeda

```
pi[i] : "sampai posisi i, berapa panjang awalan yang juga akhiran?"
        -> melihat ke BELAKANG, berakhir di i

z[i]  : "mulai dari posisi i, berapa huruf yang cocok dengan awal string?"
        -> melihat ke DEPAN, dimulai di i
```

```
S = a a b a a
pi: 0 1 0 1 2
z : _ 1 0 2 1
      ↑         z[1]=1: "a" cocok
          ↑     z[3]=2: "aa" cocok
```

Keduanya bisa saling dikonversi dalam O(n), jadi secara kekuatan mereka setara.
Yang membedakan hanyalah **kenyamanan** — dan itu nyata. Beberapa soal terasa
sepele dengan z tapi berbelit dengan pi, dan sebaliknya.

### Ide algoritma: z-box

Cara naif: untuk setiap `i`, bandingkan huruf demi huruf → O(n²) pada `"aaaa...a"`.

Idenya: **simpan satu kecocokan yang paling jauh menjangkau ke kanan.**

```
z-box [l, r] = interval PALING KANAN yang sudah terbukti sama dengan awal S
               yaitu  S[l..r] == S[0 .. r-l]
```

```
S = a a b c a a b x a a b c a a b
                    └──── z-box ────┘
                    l=8            r=14
    ┌──── salinan ───┐
    0                6
```

Saat sampai di `i` yang berada **di dalam** z-box, posisi `i` punya "kembaran"
di `i − l`. Kita sudah tahu jawaban di kembaran itu, jadi bisa **menyalin**
alih-alih membandingkan dari nol.

```
i di dalam z-box:                   kembaran k = i - l
                                    tebakan awal = min(z[k], r - i + 1)

  Kenapa dibatasi r - i + 1?
  Karena di luar z-box kita BELUM PUNYA BUKTI apa pun. Yang di luar
  harus dicek manual — dan pengecekan manual itulah yang mendorong r maju.
```

### Kenapa linear?

Setiap perbandingan manual yang **berhasil** menaikkan `r` setidaknya satu.
`r` hanya bisa naik, maksimal sampai `n`. Perbandingan yang **gagal** terjadi
paling banyak sekali per `i`. Total: `O(n) + O(n) = O(n)`.

> Ini pola yang sama dengan KMP dan Manacher (Day 216): satu pointer yang
> **monoton maju** membayar seluruh biaya. Kalau kamu menangkap pola ini,
> Manacher besok akan terasa seperti déjà vu.

---

## 🧮 2. Analisis Kompleksitas

| Tugas | Waktu | Ruang | Catatan |
| ----- | ----- | ----- | ------- |
| Bangun Z-array | O(n) | O(n) | amortisasi lewat `r` monoton |
| Cari pola (`P + '#' + T`) | O(n + m) | O(n + m) | butuh memori gabungan |
| Semua border | O(n) | O(n) | `z[i] == n − i` |
| Periode terkecil | O(n) | O(n) | `i` terkecil dengan `z[i] == n − i` |
| Cek rotasi | O(n) | O(n) | pada `A + '#' + B + B` |
| Kompresi string | O(n) | O(n) | `i` pembagi `n` dengan `z[i] == n − i` |
| Jumlah substring berbeda | O(n²) | O(n) | inkremental, n ≤ ~5000 |

**Perbandingan memori dengan KMP:** trik `P + '#' + T` memerlukan array sepanjang
`n + m + 1`. Untuk `n = 10^6`, itu 4 MB — aman. Tapi KMP biasa hanya butuh `O(m)`.
Kalau memori sangat ketat, KMP menang.

---

## 💻 3. Implementasi C++

### 3.1 Z-array

```cpp
vector<int> bangunZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;                  // z-box saat ini: s[l..r]

    for (int i = 1; i < n; i++) {
        if (i < r)                     // di dalam z-box -> salin dari kembaran
            z[i] = min(r - i, z[i - l]);

        // perluas manual; setiap keberhasilan mendorong r ke kanan
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;

        if (i + z[i] > r) {            // z-box baru yang lebih jauh
            l = i;
            r = i + z[i];
        }
    }
    return z;                          // z[0] dibiarkan 0
}
```

Sembilan baris. Perhatikan konvensi di sini: `r` bersifat **eksklusif**
(`s[l..r-1]` yang cocok), sehingga batasnya `min(r - i, ...)` bukan `min(r - i + 1, ...)`.
Kedua konvensi beredar luas di internet — pilih satu dan konsisten, jangan campur.

### 3.2 Pencarian pola

```cpp
// Semua posisi awal (0-based) kemunculan pola di teks, tumpang tindih ikut.
vector<int> cariZ(const string& teks, const string& pola) {
    string g = pola + '\1' + teks;     // '\1' pasti tidak ada di input normal
    vector<int> z = bangunZ(g);
    int m = pola.size();

    vector<int> hasil;
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) hasil.push_back(i - m - 1);
    return hasil;
}
```

**Kenapa separator wajib?** Tanpa `'\1'`, kecocokan bisa "menyeberang" dari daerah
pola ke daerah teks dan menghasilkan `z[i] > m`, yang artinya palsu. Separator memotong
setiap kecocokan tepat di batas, sehingga `z[i] ≤ m` selalu.

### 3.3 Border, periode, kompresi

```cpp
// Semua panjang border, urut MENAIK.
vector<int> semuaBorderZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s), res;
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) res.push_back(n - i);   // sufiks di i = awalan S
    reverse(res.begin(), res.end());               // i naik -> panjang turun
    return res;
}

// Periode terkecil.
int periodeTerkecilZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (z[i] == n - i) return i;               // i terkecil = periode terkecil
    return n;
}

// Blok kompresi: harus periodik DAN membagi n habis.
int blokKompresiZ(const string& s) {
    int n = s.size();
    vector<int> z = bangunZ(s);
    for (int i = 1; i < n; i++)
        if (n % i == 0 && z[i] == n - i) return i;
    return n;
}
```

`z[i] == n − i` berarti "sufiks yang mulai di `i` **habis** cocok dengan awalan S",
yaitu sufiks itu adalah border. Satu baris, langsung dari definisi.

### 3.4 Cek rotasi

```cpp
bool rotasiDari(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    string g = a + '\1' + b + b;
    vector<int> z = bangunZ(g);
    int m = a.size();
    for (int i = m + 1; i < (int)g.size(); i++)
        if (z[i] >= m) return true;
    return false;
}
```

### 3.5 Jumlah substring berbeda (inkremental)

```cpp
long long substringBerbedaZ(const string& s) {
    long long total = 0;
    string cur;
    for (char ch : s) {
        cur += ch;
        string r(cur.rbegin(), cur.rend());
        vector<int> z = bangunZ(r);
        int mx = 0;
        for (int v : z) mx = max(mx, v);
        total += (long long)cur.size() - mx;
    }
    return total;
}
```

Logika identik dengan versi pi di Day 214, tapi lebih langsung: `z[i]` **sudah**
berarti "panjang prefiks `r` yang muncul lagi di posisi `i`". Tidak perlu memikirkan
rantai apa pun — cukup ambil maksimumnya.

### 3.6 Konversi pi ↔ z

Berguna saat kamu punya satu tapi butuh yang lain (jarang, tapi bagus untuk pemahaman).

Arah **z → pi** punya rumus pendek dan andal:

```cpp
// Kecocokan sepanjang z[i] yang DIMULAI di i akan BERAKHIR di i + z[i] - 1.
// Itu tepat kondisi yang dicatat pi. Sisanya tinggal "menurunkan" nilai
// ke posisi sebelumnya, karena border sepanjang L di posisi i+1 menjamin
// border sepanjang minimal L-1 di posisi i.
vector<int> piDariZ(const vector<int>& z) {
    int n = z.size();
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
        if (z[i] > 0) pi[i + z[i] - 1] = max(pi[i + z[i] - 1], z[i]);
    for (int i = n - 2; i >= 0; i--)
        pi[i] = max(pi[i], pi[i + 1] - 1);
    return pi;
}
```

Arah **pi → z** juga mungkin, tetapi rumus pendeknya yang beredar di internet
punya banyak varian yang salah pada kasus seperti `"caccacca"`. Saran praktis:
kalau kamu butuh `z` dan hanya punya `pi`, **bangun ulang `z` dari string-nya** —
sama-sama O(n) dan tidak ada yang bisa salah.

---

## 🔄 4. Trace & Simulasi

### 4.1 Membangun Z untuk `S = "aabcaabxaabc"` (n = 12)

```
i  :  0  1  2  3  4  5  6  7  8  9 10 11
S  :  a  a  b  c  a  a  b  x  a  a  b  c
```

| i | i < r? | tebakan awal | perbandingan manual | z[i] | z-box baru [l,r) |
|---|--------|--------------|---------------------|------|------------------|
| 1 | 0 < 0 tidak | 0 | `S[0]='a'` vs `S[1]='a'` ✓, `S[1]='a'` vs `S[2]='b'` ✗ | **1** | [1, 2) |
| 2 | 2 < 2 tidak | 0 | `S[0]='a'` vs `S[2]='b'` ✗ | **0** | tetap |
| 3 | 3 < 2 tidak | 0 | `S[0]='a'` vs `S[3]='c'` ✗ | **0** | tetap |
| 4 | 4 < 2 tidak | 0 | `aab` cocok, lalu `S[3]='c'` vs `S[7]='x'` ✗ | **3** | [4, 7) |
| 5 | 5 < 7 YA | `min(7−5, z[1]=1) = 1` | `S[1]='a'` vs `S[6]='b'` ✗ | **1** | tetap |
| 6 | 6 < 7 YA | `min(7−6, z[2]=0) = 0` | `S[0]='a'` vs `S[6]='b'` ✗ | **0** | tetap |
| 7 | 7 < 7 tidak | 0 | `S[0]='a'` vs `S[7]='x'` ✗ | **0** | tetap |
| 8 | 8 < 7 tidak | 0 | `aabc` cocok, lalu habis | **4** | [8, 12) |
| 9 | 9 < 12 YA | `min(12−9, z[1]=1) = 1` | `S[1]='a'` vs `S[10]='b'` ✗ | **1** | tetap |
| 10 | 10 < 12 YA | `min(2, z[2]=0) = 0` | ✗ | **0** | tetap |
| 11 | 11 < 12 YA | `min(1, z[3]=0) = 0` | ✗ | **0** | tetap |

```
Hasil:
i :  0  1  2  3  4  5  6  7  8  9 10 11
z :  0  1  0  0  3  1  0  0  4  1  0  0
```

Perhatikan `i = 5` dan `i = 9`: keduanya menyalin dari kembaran `z[1] = 1` dan
**tidak perlu memulai dari nol**. Di string seperti `"aaaa...a"`, penghematan ini
adalah selisih antara O(n) dan O(n²).

### 4.2 Pencarian pola `P = "aba"` di `T = "ababa"`

```
g = "aba" + '\1' + "ababa"      (m = 3)

indeks : 0  1  2  3  4  5  6  7  8
g      : a  b  a  \1 a  b  a  b  a
z      : 0  0  1  0  3  0  3  0  1
                     ↑     ↑
                    z=3   z=3   -> z[i] >= m
                    i=4         -> posisi teks 4-3-1 = 0
                          i=6   -> posisi teks 6-3-1 = 2

Pola muncul di indeks 0 dan 2 (0-based). Tumpang tindih ikut terhitung.  ✓
```

Perhatikan `z[4] = 3` **berhenti tepat di 3**, tidak lebih — karena `g[3] = '\1'`
tidak akan pernah cocok dengan apa pun. Itulah gunanya separator.

### 4.3 Periode dari Z — `S = "abcabcab"` (n = 8)

```
i :  0  1  2  3  4  5  6  7
S :  a  b  c  a  b  c  a  b
z :  0  0  0  5  0  0  2  0

Cari i terkecil dengan z[i] == n - i:
  i=1: z=0, n-i=7  ✗
  i=2: z=0, n-i=6  ✗
  i=3: z=5, n-i=5  ✓  <- KETEMU

periode terkecil = 3
8 % 3 != 0  -> BUKAN pengulangan utuh (tetap periodik, tapi terpotong)
```

---

## 📝 5. Variasi & Pattern

| Kalimat di soal | Yang dipakai |
| --------------- | ------------ |
| "cari semua kemunculan pola" | `z` pada `P + sep + T`, cek `z[i] >= m` |
| "untuk tiap i, berapa huruf yang cocok dengan awal string" | `z` langsung — ini definisinya |
| "berapa panjang awalan bersama S dan sufiks ke-i" | `z[i]` |
| "semua border / periode" | `z[i] == n − i` |
| "apakah A rotasi B" | `z` pada `A + sep + B + B` |
| "jumlah substring berbeda", n ≤ 5000 | `z` inkremental pada string terbalik |
| "berapa posisi dengan awalan bersama minimal k" | hitung `z[i] >= k` |
| "gabungkan dua string dengan tumpang tindih maksimal" | `z` pada `B + sep + A`, cari `z[i] == n − i` |

### Pattern penting: "awalan bersama terpanjang dengan setiap sufiks"

Ini adalah **hal yang pi tidak berikan secara langsung** — dan alasan utama Z-function
tetap layak dihafal meski pi sudah dikuasai.

```cpp
// Berapa banyak sufiks S yang diawali dengan prefiks S sepanjang tepat k?
vector<int> z = bangunZ(s);
int hitung = 0;
for (int i = 1; i < n; i++) if (z[i] >= k) hitung++;
```

### Pattern: string terkecil yang memuat A sebagai awalan dan B sebagai akhiran

```cpp
string g = b + '\1' + a;
int ov = bangunZ(g).back();   // hati-hati: ini bukan cara paling langsung
// Lebih aman: cari z[i] == |g| - i untuk i di daerah a
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

1. **Konvensi `r` campur aduk.** Ada yang memakai `r` inklusif (`min(r - i + 1, ...)`),
   ada yang eksklusif (`min(r - i, ...)`). Menyalin kode dari dua sumber berbeda =
   off-by-one yang sangat sulit dilacak. **Pilih satu, tulis di template, jangan ganti.**

2. **Separator ada di input.** Kalau soal mengizinkan karakter apa pun (termasuk `'#'`),
   pakai `'\1'` atau bekerja dengan `vector<int>` dan separator `-1`.

3. **`z[0]` diasumsikan `n`.** Beberapa implementasi mendefinisikan `z[0] = n`. Kalau kamu
   lalu melakukan `max(z)` untuk mencari substring berbeda, jawabannya akan langsung salah.
   Di materi ini `z[0] = 0` — konsisten.

4. **Memori pada `P + sep + T`.** `n + m + 1` int. Untuk `n = m = 10^6` itu 8 MB.
   Biasanya aman, tetapi kalau limit 32 MB dan kamu juga menyimpan string, hitung ulang.

5. **Lupa `n % i == 0` pada kompresi.** Sama persis dengan jebakan Day 214. `z[i] == n − i`
   hanya berarti periodik, bukan pengulangan utuh.

6. **Loop `while` tanpa batas `i + z[i] < n`.** Ini membaca di luar string. Selalu cek
   batas **sebelum** membandingkan karakter.

7. **Mencari `z[i] == m` alih-alih `z[i] >= m`.** Dengan separator, `z[i] > m` mustahil,
   jadi keduanya setara — tapi `>= m` lebih aman kalau separatormu ternyata bocor.

### Edge cases wajib diuji

```
S = "a"            -> z = [0]                  n=1, tidak ada i>=1
S = "aaaa"         -> z = [0,3,2,1]            kasus z-box bekerja keras
S = "abcd"         -> z = [0,0,0,0]            tidak ada kecocokan sama sekali
pola lebih panjang dari teks  -> hasil kosong, jangan crash
pola == teks       -> tepat satu kemunculan di posisi 0
string kosong      -> return awal, jangan akses z.back()
```

---

## 🏆 7. Tips Contest

**Kapan pilih Z, kapan pilih pi?**

| Situasi | Pilih |
| ------- | ----- |
| "cocok berapa huruf dari posisi i dengan awal string" | **Z** — definisinya langsung |
| Butuh **automaton** untuk DP | **pi** — Z tidak punya automaton |
| Butuh rantai border / hitung kemunculan tiap prefiks | **pi** — rantai pi adalah struktur pohon |
| Matching sederhana, sekali pakai | **Z** — 9 baris, lebih sedikit yang bisa salah |
| Memori sangat ketat (`O(m)` saja) | **pi** — tidak perlu string gabungan |
| Kamu grogi dan hanya hafal satu | **yang kamu hafal** — jangan eksperimen saat kontes |

**Kejujuran praktis:** kebanyakan CM+ hanya menyimpan **satu** dari keduanya di template
dan memaksakannya ke semua soal. Itu strategi yang sah. Tapi ketahuilah bahwa
soal DP-counting-string (Day 214 exercise 6) **memaksa** pi, karena butuh automaton.

**Red flag → aksi:**

- Soal menyebut *"untuk setiap i"* dan *"awalan"* dalam satu kalimat → Z-function.
- Soal minta *"kemunculan pola"* saja → pakai mana pun; Z lebih cepat ditulis.
- Soal minta *"berapa banyak string yang ..."* → pi + automaton, bukan Z.

**Trik implementasi:** simpan `bangunZ` **persis 9 baris** di template. Jangan tulis ulang
saat kontes — off-by-one pada z-box adalah bug yang bisa menghabiskan 40 menit.

---

## 📌 8. Ringkasan & Cheatsheet

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  Z-FUNCTION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  z[i] = panjang awalan bersama antara S dan S[i..]
  z[0] = 0   (konvensi materi ini)

  INTI (r eksklusif):
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) { l = i; r = i + z[i]; }

  r MONOTON NAIK -> total O(n)

  TURUNAN
    cari pola      : z pada P + sep + T, cek z[i] >= m
    border         : z[i] == n - i
    periode kecil  : i terkecil dengan z[i] == n - i
    kompresi       : + syarat n % i == 0
    rotasi         : z pada A + sep + B + B
    substr berbeda : Σ (|cur| - max z(rev(cur)))

  SEPARATOR: pakai '\1', BUKAN '#'  (bisa bocor)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### Soal latihan online

| Soal | Platform | Topik |
| ---- | -------- | ----- |
| [CF 126B — Password](https://codeforces.com/problemset/problem/126/B) | Codeforces | z + border |
| [CF 432D — Prefixes and Suffixes](https://codeforces.com/problemset/problem/432/D) | Codeforces | z lebih mudah dari pi di sini |
| [CF 535D — Tavas and Malekas](https://codeforces.com/problemset/problem/535/D) | Codeforces | z + interval |
| [CF 1968G1 — Division + LCP](https://codeforces.com/problemset/problem/1968/G1) | Codeforces | z + binary search |
| [CSES 1732 — Finding Borders](https://cses.fi/problemset/task/1732) | CSES | border via z |
| [CSES 1753 — String Matching](https://cses.fi/problemset/task/1753) | CSES | matching |
| [AtCoder ABC 141 E](https://atcoder.jp/contests/abc141/tasks/abc141_e) | AtCoder | z untuk substring berulang |
| [AtCoder ABC 150 F](https://atcoder.jp/contests/abc150/tasks/abc150_f) | AtCoder | z pada array XOR |
| [SPOJ PERIOD](https://www.spoj.com/problems/PERIOD/) | SPOJ | periode tiap prefiks |

---

**Selanjutnya:** Day 216 — Manacher. Kamu akan melihat **pola pointer monoton yang sama
persis** dengan z-box, tapi dipakai untuk palindrom. Kalau hari ini kamu benar-benar paham
kenapa `r` tidak pernah mundur, besok kamu akan langsung mengenali strukturnya.
