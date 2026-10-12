# Day 272 — Slope Trick

> **Ide satu kalimat:** Memelihara fungsi konveks linier sepotong-sepotong (*piecewise linear convex function*) $f(x)$ secara dinamis menggunakan dua Priority Queue (Max-Heap dan Min-Heap) untuk titik-titik belok (*breakpoints*), mereduksi transisi DP bernilai mutlak atau batas monoton dari $\mathcal{O}(N^2)$ menjadi $\mathcal{O}(N \log N)$.

---

## 1. Motivasi dan Batasan DP Klasik

Perhatikan masalah klasik optimasi berikut:
> Diberikan array $A = [a_1, a_2, \dots, a_N]$. Kita ingin mengubah elemen-elemennya menjadi array baru $B = [b_1, b_2, \dots, b_N]$ sedemikian sehingga:
> 1. $B$ terurut tidak menurun: $b_1 \le b_2 \le \dots \le b_N$
> 2. Total biaya perubahan termaksimalkan/terminimalkan: $\min \sum_{i=1}^N |a_i - b_i|$.

### Formulasi DP Standar:
Misalkan $dp[i](x)$ adalah biaya minimum untuk memproses prefiks hingga elemen $i$ dengan nilai $b_i = x$.
Rekurensi transisi:
$$dp[i](x) = |x - a_i| + \min_{y \le x} \{ dp[i-1](y) \}$$

Jika rentang nilai $x \in [0, M]$, kompleksitas DP adalah $\mathcal{O}(N \cdot M)$.
Dengan koordinat diskret dari nilai elemen $A$, kompleksitasnya dapat diturunkan menjadi $\mathcal{O}(N^2)$.
Namun jika $N = 100.000$, waktu $\mathcal{O}(N^2)$ pasti menghasilkan **TLE**.
**Slope Trick** memungkinkan kita memproses seluruh rekurensi ini dalam waktu $\mathcal{O}(N \log N)$!

---

## 2. Struktur Matematis Fungsi Konveks Sepotong-sepotong

Sebuah fungsi $f(x) : \mathbb{R} \to \mathbb{R}$ dikatakan **konveks sepotong-sepotong (*piecewise linear convex*)** jika:
1. Grafiknya terdiri dari segmen-segmen garis lurus yang tersambung secara kontinu.
2. Kemiringannya (*slope*) tidak pernah menurun:
   $$\dots \le s_{-2} \le s_{-1} \le 0 \le s_1 \le s_2 \le \dots$$
3. Terdapat segmen dasar (atau titik) di mana slope bernilai $0$, yang merupakan titik minimum global dari fungsi tersebut.

Titik-titik di mana kemiringan fungsi berubah disebut **breakpoints** (titik belok).

```text
f(x)
 ^
 |    \  slope = -2
 |     \
 |      \  slope = -1
 |       \________/  slope = 0 (nilai minimum global: min_val)
 |                \
 |                 \  slope = +1
 |                  \
 +----------------------------> x
           L        R
```

---

## 3. Representasi Slope Trick: Dua Priority Queue

Untuk memelihara fungsi $f(x)$ dengan kemiringan integer, kita hanya perlu mencatat:
1. `min_val`: Nilai minimum global fungsi pada daerah datar (slope $= 0$).
2. `L` (**Max-Heap**): Kumpulan breakpoint di sisi kiri, di mana kemiringan bertambah $+1$ menuju $0$.
   Puncak heap `L.top()` adalah batas kanan dari lereng menurun (titik awal daerah minimum).
3. `R` (**Min-Heap**): Kumpulan breakpoint di sisi kanan, di mana kemiringan bertambah $+1$ dari $0$ menuju positif.
   Puncak heap `R.top()` adalah batas kiri dari lereng menaik (titik akhir daerah minimum).

Dengan representasi ini, daerah di mana $f(x)$ mencapai nilai minimum `min_val` adalah interval $[\max(L), \min(R)]$.

---

## 4. Operasi Primitif Slope Trick

### Operasi 1: Menambahkan Fungsi Nilai Mutlak $g(x) = f(x) + |x - a|$
Fungsi $|x - a|$ memiliki slope $-1$ untuk $x < a$ dan slope $+1$ untuk $x > a$.
Breakpoint baru berada di titik $a$.
- **Kasus 1 ($a < \max(L)$)**:
  Titik $a$ berada di lereng kiri.
  Nilai minimum global bertambah sebesar $\max(L) - a$.
  Puncak $L$ berpindah ke $R$, dan $a$ didorong dua kali ke $L$:
  ```cpp
  min_val += L.top() - a;
  R.push(L.top());
  L.pop();
  L.push(a);
  L.push(a);
  ```
- **Kasus 2 ($a > \min(R)$)**:
  Titik $a$ berada di lereng kanan.
  Nilai minimum global bertambah sebesar $a - \min(R)$.
  Puncak $R$ berpindah ke $L$, dan $a$ didorong dua kali ke $R$:
  ```cpp
  min_val += a - R.top();
  L.push(R.top());
  R.pop();
  R.push(a);
  R.push(a);
  ```
- **Kasus 3 ($\max(L) \le a \le \min(R)$)**:
  Titik $a$ berada tepat di daerah datar (slope 0).
  Nilai minimum global tidak berubah.
  Cukup dorong $a$ ke $L$ dan $a$ ke $R$:
  ```cpp
  L.push(a);
  R.push(a);
  ```

### Operasi 2: Prefiks Minimum $g(x) = \min_{y \le x} f(y)$
Operasi ini mempertahankan bagian fungsi di mana slope $\le 0$, dan mengubah semua lereng menaik (slope $> 0$) menjadi datar (slope $= 0$).
Dalam struktur data kita, ini sangat mudah:
> **Cukup kosongkan Min-Heap `R`!**
```cpp
while (!R.empty()) R.pop();
```

### Operasi 3: Sufiks Minimum $g(x) = \min_{y \ge x} f(y)$
Operasi ini mengubah semua lereng menurun (slope $< 0$) menjadi datar (slope $= 0$).
> **Cukup kosongkan Max-Heap `L`!**
```cpp
while (!L.empty()) L.pop();
```

### Operasi 4: Pergeseran Translasi / Konvolusi Minkowski
Jika fungsi digeser menjadi $f(x - c)$, semua breakpoint di $L$ dan $R$ bertambah sebesar $c$.
Dapat dipelihara dengan variabel offset malas (*lazy tag*): `tag_L` dan `tag_R`.

---

## 5. Studi Kasus Klasik: Problem Sonya and Wi-Fi (CF 713C)

Ubah array $A$ menjadi strictly increasing ($b_1 < b_2 < \dots < b_N$) dengan meminimalkan $\sum |a_i - b_i|$.

### Reduksi Trik Indeks:
Syarat $b_1 < b_2 < \dots < b_N$ ekivalen dengan:
$$b_1 \le b_2 - 1 \le b_3 - 2 \le \dots \le b_N - (N - 1)$$
Definisikan $a'_i = a_i - i$ dan $b'_i = b_i - i$.
Syarat berubah menjadi $b'_1 \le b'_2 \le \dots \le b'_N$ (non-decreasing).
Pada setiap langkah $i$:
1. $dp[i](x) = |x - a'_i| + \min_{y \le x} dp[i-1](y)$.
2. Karena kita hanya membutuhkan prefiks minimum, kita bahkan tidak perlu memelihara `R`! Kita hanya perlu Max-Heap `L`.
3. Jika $a'_i < L.top()$:
   - `ans += L.top() - a'_i`
   - `L.pop()`
   - `L.push(a'_i)`
   - `L.push(a'_i)`
4. Jika $a'_i \ge L.top()$:
   - `L.push(a'_i)`
Kompleksitas total: $\mathcal{O}(N \log N)$ dengan hanya ~15 baris kode!
