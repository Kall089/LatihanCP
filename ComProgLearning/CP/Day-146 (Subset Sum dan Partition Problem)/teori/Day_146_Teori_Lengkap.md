# 📊 Day 146: Subset Sum & Partition Problem

**Hari**: Day 146 dari 308 Hari Competitive Programming  
**Topik**: Subset Sum, Partition, Counting, dan Bitset DP  
**Prerequisites**: Day 141 (Prinsip DP), Day 145 (0/1 Knapsack)  
**Difficulty**: ⭐⭐  

**Learning Objectives**:

- Mendesain state boolean untuk subset sum
- Mengubah masalah partisi menjadi target subset sum
- Menghitung semua sum yang mungkin dibentuk
- Menghitung banyak subset dengan sum tertentu
- Memahami optimasi `bitset` untuk subset sum

---

## 🔍 1. Konsep & Intuisi

### 1.1 Masalah dasar

Diberi `N` bilangan `a[1..N]` dan target `S`. Setiap bilangan boleh dipakai paling banyak sekali.

Pertanyaan:

```
Apakah ada subset yang jumlah elemennya tepat S?
```

Contoh:

```
a = [3, 5, 7, 10]
S = 12

Subset [5, 7] menghasilkan 12 -> YES
```

Ini adalah versi boolean dari 0/1 knapsack:

- 0/1 karena setiap elemen dipilih atau tidak dipilih
- boolean karena kita hanya peduli **bisa atau tidak**
- target sum karena kapasitasnya adalah jumlah yang ingin dicapai

### 1.2 State yang benar

Definisikan:

```
bisa[s] = apakah ada subset dari elemen yang sudah diproses
          dengan jumlah tepat s
```

Basis:

```
bisa[0] = true
```

Mengapa? Sebelum memilih elemen apa pun, jumlah `0` bisa dibentuk oleh subset kosong. Basis ini bukan formalitas. Tanpa `bisa[0]`, elemen pertama tidak akan pernah bisa menyalakan state apa pun.

Transisi untuk setiap elemen `x`:

```
jika sum s-x sudah bisa, maka sum s juga bisa setelah mengambil x

bisa[s] |= bisa[s - x]
```

Loop harus **mundur**:

```cpp
for (int x : a)
    for (int s = S; s >= x; s--)
        bisa[s] |= bisa[s - x];
```

### 1.3 Kenapa loop mundur?

Ambil satu elemen saja:

```
a = [3]
S = 6
```

Kalau loop maju:

```
awal: bisa[0] = 1

s = 3 -> bisa[3] |= bisa[0] -> true
s = 6 -> bisa[6] |= bisa[3] -> true
```

Hasilnya `6` dianggap bisa, padahal hanya ada satu angka `3`. Itu berarti angka `3` dipakai dua kali.

Loop mundur mencegah ini:

```
s = 6 -> baca bisa[3] yang masih false
s = 3 -> baca bisa[0] yang true -> nyalakan bisa[3]
```

ASCII state:

```
S = 6, x = 3

MUNDUR:
before: 1 0 0 0 0 0 0
read :        ^           saat s=6 baca bisa[3] lama = 0
write:              -
then : 1 0 0 1 0 0 0     saat s=3 tulis bisa[3]

MAJU:
before: 1 0 0 0 0 0 0
s=3 : 1 0 0 1 0 0 0
s=6 : 1 0 0 1 0 0 1     salah untuk 0/1
```

### 1.4 Cara berpikir "set jumlah yang reachable"

Subset sum juga bisa dipahami sebagai kumpulan jumlah yang mungkin:

```
awal                  : {0}
ambil / tidak ambil 3 : {0, 3}
ambil / tidak ambil 5 : {0, 3, 5, 8}
ambil / tidak ambil 7 : {0, 3, 5, 7, 8, 10, 12, 15}
```

DP array hanya menyimpan set ini dalam bentuk boolean.

---

## 🧮 2. Analisis Kompleksitas

Misalkan:

```
N = banyak elemen
S = target atau total sum yang diproses
T = total seluruh elemen
```

| Problem | State | Time | Space |
| ------- | ----- | ---- | ----- |
| Ada subset sum S? | `bisa[0..S]` | O(N·S) | O(S) |
| Semua sum | `bisa[0..T]` | O(N·T) | O(T) |
| Equal partition | `bisa[0..T/2]` | O(N·T) | O(T) |
| Minimum difference | `bisa[0..T]` atau `0..T/2` | O(N·T) | O(T) |
| Count subsets | `cara[0..S]` | O(N·S) | O(S) |
| Bitset subset sum | `bitset[0..T]` | O(N·T / word_size) | O(T / word_size) |

Aturan contest:

```
N * S <= 1e8       -> vector DP mungkin aman
N * T <= 1e8       -> semua sum mungkin aman
T <= 2e5 atau 1e6  -> bitset sangat menarik
T besar sekali     -> cari struktur lain; mungkin meet in the middle, gcd, atau greedy khusus
```

Subset sum umum adalah NP-complete jika angka target bisa sangat besar. Di CP, solusi DP bekerja karena `S` atau `T` biasanya dibatasi kecil.

---

## 💻 3. Implementasi C++

### 3.1 Ada subset dengan sum S?

```cpp
#include <bits/stdc++.h>
using namespace std;

bool subsetSumExists(const vector<int>& a, int S) {
    vector<char> bisa(S + 1, 0);
    bisa[0] = 1;

    for (int x : a) {
        for (int s = S; s >= x; s--) {
            if (bisa[s - x]) bisa[s] = 1;
        }
    }

    return bisa[S];
}
```

Kompleksitas:

- Time: `O(N·S)`
- Space: `O(S)`

### 3.2 Semua jumlah yang bisa dibentuk

```cpp
vector<int> allReachableSums(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;

    for (int x : a)
        for (int s = total; s >= x; s--)
            bisa[s] |= bisa[s - x];

    vector<int> hasil;
    for (int s = 1; s <= total; s++)
        if (bisa[s]) hasil.push_back(s);

    return hasil;
}
```

Perhatikan `s` dimulai dari `1` ketika mengumpulkan jawaban karena subset kosong biasanya tidak diminta.

### 3.3 Equal partition

Masalah:

```
Bisakah array dibagi menjadi dua subset dengan jumlah sama?
```

Jika total `T` ganjil, jawabannya langsung `NO`. Jika genap, cukup cek apakah ada subset dengan sum `T / 2`.

```cpp
bool canEqualPartition(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    if (total % 2 == 1) return false;
    return subsetSumExists(a, total / 2);
}
```

### 3.4 Minimum partition difference

Masalah:

```
Bagi array menjadi dua subset A dan B.
Minimalkan |sum(A) - sum(B)|.
```

Jika satu subset punya sum `s`, subset lain punya sum `total - s`, maka selisihnya:

```
|total - 2s|
```

Untuk meminimalkan selisih, cari `s` reachable yang sedekat mungkin dengan `total / 2`.

```cpp
int minimumPartitionDifference(const vector<int>& a) {
    int total = accumulate(a.begin(), a.end(), 0);
    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;

    for (int x : a)
        for (int s = total; s >= x; s--)
            bisa[s] |= bisa[s - x];

    for (int s = total / 2; s >= 0; s--)
        if (bisa[s]) return total - 2 * s;

    return total;
}
```

### 3.5 Menghitung banyak subset dengan sum K

Ganti boolean menjadi jumlah cara:

```cpp
const long long MOD = 1000000007LL;

long long countSubsetsWithSum(const vector<int>& a, int K) {
    vector<long long> cara(K + 1, 0);
    cara[0] = 1;

    for (int x : a) {
        for (int s = K; s >= x; s--) {
            cara[s] = (cara[s] + cara[s - x]) % MOD;
        }
    }

    return cara[K];
}
```

Kasus penting: jika `x = 0`, loop tetap benar. Setiap subset lama punya dua versi: tidak mengambil nol dan mengambil nol. Karena itu semua `cara[s]` mengganda.

### 3.6 Target sum dengan tanda + dan -

Masalah:

```
Untuk setiap angka, pilih tanda + atau -.
Berapa banyak ekspresi yang hasilnya target?
```

Misal subset positif berjumlah `P`, total semua angka `T`.

```
P - (T - P) = target
2P = T + target
P = (T + target) / 2
```

Maka masalahnya berubah menjadi counting subset sum `P`.

Syarat valid:

```
T + target >= 0
T + target genap
P <= T
```

```cpp
long long countTargetExpressions(const vector<int>& a, int target) {
    int total = accumulate(a.begin(), a.end(), 0);
    int raw = total + target;
    if (raw < 0 || raw % 2 != 0) return 0;
    return countSubsetsWithSum(a, raw / 2);
}
```

### 3.7 Bitset subset sum

Jika `total` punya batas compile-time yang jelas, `bitset` membuat subset sum sangat cepat.

```cpp
const int MAX_SUM = 200000;

bitset<MAX_SUM + 1> reachableByBitset(const vector<int>& a) {
    bitset<MAX_SUM + 1> bs;
    bs[0] = 1;

    for (int x : a) {
        bs |= (bs << x);
    }

    return bs;
}
```

Intuisi:

```
bs       : sum lama yang bisa
bs << x  : sum lama ditambah x
OR       : tidak ambil x atau ambil x
```

Contoh:

```
bs untuk {0, 3, 5}: bit 0,3,5,8 menyala
x = 7
bs << 7 menyalakan 7,10,12,15
OR menghasilkan 0,3,5,7,8,10,12,15
```

Kompleksitas praktisnya sekitar `O(N·T/64)`, karena bit diproses per word CPU.

---

## 🔄 4. Trace / Simulasi

Contoh:

```
a = [3, 5, 7]
S = 10
```

Representasikan state sebagai set jumlah yang bisa:

```
awal      : {0}
proses 3  : {0, 3}
proses 5  : {0, 3, 5, 8}
proses 7  : {0, 3, 5, 7, 8, 10, 12, 15}
```

Jika hanya peduli sampai target `S = 10`, state di atas target bisa diabaikan:

```
awal      : {0}
proses 3  : {0, 3}
proses 5  : {0, 3, 5, 8}
proses 7  : {0, 3, 5, 7, 8, 10}
```

Karena `10` menyala, jawabannya `YES`.

Trace array boolean sampai `S = 10`:

```
index s : 0 1 2 3 4 5 6 7 8 9 10
awal   : 1 0 0 0 0 0 0 0 0 0 0
x = 3  : 1 0 0 1 0 0 0 0 0 0 0
x = 5  : 1 0 0 1 0 1 0 0 1 0 0
x = 7  : 1 0 0 1 0 1 0 1 1 0 1
```

Contoh equal partition:

```
a = [1, 5, 11, 5]
total = 22
target = 11

Subset [11] atau [1,5,5] mencapai 11 -> YES
```

Contoh minimum difference:

```
a = [1, 6, 11, 5]
total = 23
target tengah = 11

reachable terbesar <= 11 adalah 11
selisih = 23 - 2*11 = 1
partition: [11] dan [1,6,5]
```

---

## 📝 5. Variasi & Pattern

### 5.1 "Bisa atau tidak?"

Kata kunci:

- "can we form sum"
- "is there a subset"
- "exactly K"
- "possible sums"

Gunakan boolean DP.

### 5.2 "Semua jumlah yang mungkin"

Kata kunci:

- "print all distinct sums"
- "how many different sums"
- "reachable values"

Gunakan `bisa[0..total]`, lalu scan semua index yang true.

### 5.3 "Bagi menjadi dua kelompok"

Kata kunci:

- "two groups"
- "equal sum"
- "minimum difference"
- "balanced partition"

Turunkan ke `total / 2`.

### 5.4 "Berapa banyak cara?"

Kata kunci:

- "number of subsets"
- "count ways"
- "modulo"
- "assign signs"

Gunakan numeric DP:

```
cara[s] += cara[s - x]
```

### 5.5 "Banyak query target"

Jika semua query memakai array yang sama:

1. Precompute `bisa` sekali sampai `total`
2. Jawab setiap query dalam `O(1)`

Dengan `bitset`, precompute bisa jauh lebih cepat.

---

## ⚠️ 6. Common Mistakes & Edge Cases

### 6.1 Lupa basis

```cpp
vector<char> bisa(S + 1, 0);
// lupa bisa[0] = 1
```

Akibatnya semua state tetap false.

### 6.2 Loop maju

```cpp
for (int s = x; s <= S; s++) // salah untuk 0/1
```

Ini menyelesaikan unbounded subset sum, bukan subset 0/1.

### 6.3 Target lebih besar dari total

Kalau `S > total`, jawabannya pasti `NO`. DP tetap bisa berjalan, tetapi lebih hemat jika langsung tahu batasnya.

### 6.4 Total ganjil pada equal partition

```
total = 21
mustahil dibagi menjadi dua integer sum yang sama
```

Langsung `NO`.

### 6.5 Elemen nol pada counting

```
a = [0, 0, 1], K = 1
```

Jawaban adalah `4`: pilih `1`, lalu tiap nol bisa dipilih atau tidak. Jangan buang nol tanpa menghitung efeknya.

### 6.6 Overflow jumlah cara

Jumlah subset bisa sampai `2^N`. Untuk `N = 100`, ini jauh melewati `long long`. Jika soal memberi modulo, mod setiap transisi.

### 6.7 Memory terlalu besar

`vector<char> bisa(1e9)` tidak realistis. Kalau total sum besar, subset sum DP bukan pendekatan yang tepat.

---

## 🏆 7. Tips Contest

- Sebelum coding, hitung `N * target` atau `N * total`.
- Jika soal hanya butuh `YES/NO`, jangan simpan nilai maksimum.
- Jika target adalah setengah total, curigai partition.
- Jika diminta minimum selisih dua kelompok, scan reachable sum dari `total / 2` ke bawah.
- Jika ada banyak query terhadap array yang sama, precompute semua reachable sum sekali.
- Jika `total <= 200000` dan banyak operasi, pakai `bitset`.
- Jika elemen boleh negatif, teknik hari ini tidak langsung berlaku. Perlu offset atau pendekatan lain.

---

## 📌 8. Ringkasan

```
State:
  bisa[s] = sum s bisa dibentuk?

Basis:
  bisa[0] = true

Transisi:
  for x in a:
      for s from S down to x:
          bisa[s] |= bisa[s-x]

Equal partition:
  total genap dan bisa[total/2]

Minimum difference:
  cari s <= total/2 yang reachable
  answer = total - 2*s

Counting:
  cara[0] = 1
  cara[s] += cara[s-x]

Bitset:
  bs[0] = 1
  for x in a:
      bs |= bs << x
```

Subset sum adalah salah satu fondasi DP paling penting karena ia muncul sebagai penyamaran di knapsack, partisi, balancing, tanda `+/-`, dan query reachability. Kalau template ini sudah refleks, banyak soal DP dasar akan terasa seperti variasi kecil, bukan masalah baru.
