# Day 11 — Recursion Dasar: Teori Lengkap

---

## 1. Apa itu Rekursi?

**Rekursi** adalah teknik pemrograman di mana sebuah fungsi memanggil **dirinya sendiri** untuk menyelesaikan masalah yang lebih kecil, hingga mencapai kasus dasar (base case).

### Komponen Wajib Rekursi

Setiap fungsi rekursif **harus** memiliki dua hal:

1. **Base Case** — kondisi yang menghentikan rekursi
2. **Recursive Case** — pemanggilan diri sendiri dengan input yang **lebih kecil**

Tanpa base case → **infinite recursion** → **stack overflow**!

### Contoh Paling Sederhana

```cpp
void countdown(int n) {
    if (n == 0) {        // BASE CASE
        cout << "Selesai!\n";
        return;
    }
    cout << n << "\n";
    countdown(n - 1);    // RECURSIVE CASE (n berkurang)
}
```

### Visualisasi Call Stack: countdown(3)

```
countdown(3)
  └─ countdown(2)
       └─ countdown(1)
            └─ countdown(0)  ← BASE CASE: "Selesai!"
            ← return
         ← return
      ← return
   ← return
```

---

## 2. Factorial

### Definisi Matematis

```
n! = n × (n-1) × (n-2) × ... × 1
0! = 1  (base case)
1! = 1
5! = 5 × 4 × 3 × 2 × 1 = 120
```

Secara rekursif:
```
fact(n) = n × fact(n-1)    untuk n > 0
fact(0) = 1                 base case
```

### Implementasi C++

```cpp
ll factorial(int n) {
    if (n == 0) return 1LL;       // BASE CASE
    return (ll)n * factorial(n - 1); // RECURSIVE CASE
}
```

### Trace Eksekusi: factorial(4)

```
factorial(4)
  = 4 * factorial(3)
  = 4 * 3 * factorial(2)
  = 4 * 3 * 2 * factorial(1)
  = 4 * 3 * 2 * 1 * factorial(0)
  = 4 * 3 * 2 * 1 * 1
  = 24
```

### Visualisasi Stack Frame

```
┌──────────────────┐ ← TOP
│  factorial(0)=1  │
├──────────────────┤
│  factorial(1)=1  │
├──────────────────┤
│  factorial(2)=2  │
├──────────────────┤
│  factorial(3)=6  │
├──────────────────┤
│  factorial(4)=24 │
└──────────────────┘ ← BOTTOM (main)
```

### Batasan

| n  | n! |
|----|-----|
| 0  | 1 |
| 5  | 120 |
| 10 | 3,628,800 |
| 20 | 2,432,902,008,176,640,000 (~2.4×10^18) |
| 21 | **OVERFLOW** (> long long max ~9.2×10^18) |

> Untuk n > 20, gunakan `__int128` atau BigInteger.

---

## 3. Fibonacci — Naif O(2^n)

### Definisi

```
F(0) = 0
F(1) = 1
F(n) = F(n-1) + F(n-2)  untuk n ≥ 2
```

### Implementasi Naif

```cpp
ll fib(int n) {
    if (n <= 1) return n;  // BASE CASE: F(0)=0, F(1)=1
    return fib(n-1) + fib(n-2);
}
```

### Pohon Rekursi untuk fib(5)

```
                fib(5)
              /        \
          fib(4)       fib(3)
         /      \      /    \
      fib(3) fib(2) fib(2) fib(1)
      /   \   /  \   /  \
  fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
  /   \
fib(1) fib(0)
```

### Masalah: Overlapping Subproblems

`fib(3)` dihitung **2 kali**, `fib(2)` dihitung **3 kali**!
Secara umum: **~2^n total pemanggilan** untuk fib(n).

| n  | Pemanggilan total (approx) |
|----|---------------------------|
| 10 | ~177 |
| 20 | ~21,891 |
| 30 | ~2.7 juta |
| 40 | ~331 juta |
| 50 | **TLE (timeout)** |

---

## 4. Fibonacci — Memoization O(n)

**Memoization** = cache hasil sub-pemanggilan agar tidak dihitung ulang.

```
Sebelum: fib(n) dipanggil ulang berkali-kali
Sesudah: fib(n) dihitung sekali, lalu disimpan di memo[n]
```

### Implementasi

```cpp
const int MAXN = 105;
ll memo[MAXN];

ll fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];    // CACHE HIT
    return memo[n] = fib(n-1) + fib(n-2); // CACHE MISS: hitung + simpan
}

int main() {
    memset(memo, -1, sizeof(memo));  // WAJIB: inisialisasi -1 (belum dihitung)
    int n; cin >> n;
    cout << fib(n) << "\n";
}
```

### Visualisasi dengan Memo

```
fib(5) → belum ada di memo, hitung:
  fib(4) → belum ada, hitung:
    fib(3) → belum ada, hitung:
      fib(2) → belum ada, hitung:
        fib(1) = 1  ← base
        fib(0) = 0  ← base
      memo[2] = 1
    memo[3] = fib(2)+fib(1) = 1+1 = 2
  memo[4] = fib(3)+fib(2) = 2+1 = 3
  fib(3) → memo[3]=2  ← CACHE HIT!
memo[5] = fib(4)+fib(3) = 3+2 = 5
```

Hanya **n pemanggilan unik** — O(n)!

### Perbandingan Kompleksitas

| Versi | Time | Space |
|-------|------|-------|
| Naif rekursif | O(2^n) | O(n) stack |
| Memoization | O(n) | O(n) memo + O(n) stack |
| Bottom-up DP | O(n) | O(n) atau O(1) |

---

## 5. Tower of Hanoi

### Aturan

Ada 3 tiang (A, B, C) dan n disk berbeda ukuran. Awalnya semua disk di tiang A.

- Pindahkan semua disk dari A ke C
- Hanya boleh memindahkan 1 disk per langkah
- Disk besar tidak boleh di atas disk kecil

### Strategi Rekursif

```
Untuk pindahkan n disk dari src → dst melalui via:
1. Pindahkan (n-1) disk dari src → via (melalui dst)
2. Pindahkan disk ke-n dari src → dst
3. Pindahkan (n-1) disk dari via → dst (melalui src)
```

### Implementasi

```cpp
void hanoi(int n, char src, char dst, char via) {
    if (n == 0) return;                    // BASE CASE
    hanoi(n-1, src, via, dst);             // Pindah n-1 disk ke via
    cout << "Move disk " << n << " from " << src << " to " << dst << "\n";
    hanoi(n-1, via, dst, src);             // Pindah n-1 disk dari via ke dst
}
// Panggil: hanoi(n, 'A', 'C', 'B');
```

### Trace untuk n=2

```
hanoi(2, A, C, B):
  hanoi(1, A, B, C):
    hanoi(0, ...) → return
    "Move disk 1 from A to B"
    hanoi(0, ...) → return
  "Move disk 2 from A to C"
  hanoi(1, B, C, A):
    hanoi(0, ...) → return
    "Move disk 1 from B to C"
    hanoi(0, ...) → return

Output:
Move disk 1 from A to B
Move disk 2 from A to C
Move disk 1 from B to C
```

### Jumlah Langkah

```
T(n) = 2*T(n-1) + 1
T(1) = 1
T(n) = 2^n - 1
```

| n | Langkah |
|---|---------|
| 1 | 1 |
| 2 | 3 |
| 3 | 7 |
| 4 | 15 |
| 10 | 1023 |
| 20 | ~1 juta |
| 64 | ~1.8×10^19 (jika 1 langkah/detik: lebih lama dari usia alam semesta!) |

---

## 6. Fast Power — a^b mod m

### Masalah

Hitung `a^b mod m` di mana b bisa sangat besar (misal 10^9).

Perkalian naif `a*a*...*a` (b kali) adalah O(b) — TLE untuk b=10^9.

### Ide Fast Power (Exponentiation by Squaring)

```
a^b = (a^(b/2))^2          jika b genap
a^b = a * (a^(b/2))^2      jika b ganjil
a^0 = 1                    base case
```

### Implementasi

```cpp
ll fastpow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1LL;
    ll half = fastpow(base, exp / 2, mod);
    ll half2 = (half * half) % mod;
    if (exp % 2 == 0) return half2;
    return (base % mod * half2) % mod;
}
```

### Trace: fastpow(2, 10, 1000)

```
fastpow(2, 10, 1000):
  half = fastpow(2, 5, 1000)
    half = fastpow(2, 2, 1000)
      half = fastpow(2, 1, 1000)
        half = fastpow(2, 0, 1000) = 1
        exp=1 ganjil → 2 * 1*1 % 1000 = 2
      exp=2 genap → 2*2 % 1000 = 4
    exp=5 ganjil → 2 * 4*4 % 1000 = 32
  exp=10 genap → 32*32 % 1000 = 24 → 1024 % 1000 = 24
```

Hanya **log₂(10) ≈ 3-4 level** rekursi, bukan 10!

### Kompleksitas

- Time: O(log b)
- Space: O(log b) stack frames

---

## 7. GCD Rekursif (Algoritma Euclidean)

### Teorema

```
gcd(a, b) = gcd(b, a mod b)    untuk b ≠ 0
gcd(a, 0) = a                   base case
```

### Implementasi

```cpp
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;  // bagi dulu untuk hindari overflow
}
```

### Trace: gcd(48, 18)

```
gcd(48, 18)
  = gcd(18, 48 % 18) = gcd(18, 12)
  = gcd(12, 18 % 12) = gcd(12, 6)
  = gcd(6,  12 % 6)  = gcd(6, 0)
  = 6
```

### Mengapa Cepat?

Setiap 2 langkah, nilai `a` minimal berkurang setengah.
Time complexity: **O(log(min(a,b)))**

---

## 8. Rekursi pada String

### Palindrome Check Rekursif

```cpp
bool isPalin(const string& s, int l, int r) {
    if (l >= r) return true;       // BASE CASE: panjang 0 atau 1
    if (s[l] != s[r]) return false; // Karakter berbeda → bukan palindrome
    return isPalin(s, l + 1, r - 1); // Cek bagian dalam
}
// Panggil: isPalin(s, 0, s.size()-1)
```

### String Reverse Rekursif

```cpp
string rev(const string& s, int i) {
    if (i == (int)s.size()) return "";
    return rev(s, i + 1) + s[i];
}
```

### Trace: isPalin("racecar", 0, 6)

```
isPalin("racecar", 0, 6): s[0]='r' == s[6]='r' → OK
  isPalin("racecar", 1, 5): s[1]='a' == s[5]='a' → OK
    isPalin("racecar", 2, 4): s[2]='c' == s[4]='c' → OK
      isPalin("racecar", 3, 3): l >= r → return TRUE
```

---

## 9. Call Stack & Stack Overflow

### Apa itu Call Stack?

Setiap pemanggilan fungsi menyimpan **stack frame** berisi:
- Parameter fungsi
- Variabel lokal
- Return address

Stack memiliki kapasitas terbatas (~1-8 MB default di Linux/Mac).

### Stack Overflow

Rekursi terlalu dalam → stack frame memenuhi memori → **crash dengan SIGSEGV**.

```cpp
// BERBAHAYA: n=100000 akan stack overflow
ll naiveFib(int n) {
    if (n <= 1) return n;
    return naiveFib(n-1) + naiveFib(n-2); // depth O(n) = 100000 frames!
}
```

### Batas Aman

| Platform | Depth aman |
|----------|-----------|
| Codeforces/CSES | ~10^4 – 10^5 |
| Local Mac/Linux | ~10^4 – 5×10^4 |
| Windows | ~10^3 – 10^4 (stack lebih kecil) |

### Tips Anti Stack Overflow

1. Gunakan **memoization + iteratif (bottom-up)** untuk DP
2. Konversi ke **explicit stack** untuk rekursi dalam
3. Cek depth: jika n > 10^4, pertimbangkan iteratif

---

## 10. Pola-Pola Rekursi

### Linear Recursion
Satu pemanggilan rekursif per langkah.
```cpp
int sum(int* A, int n) {
    if (n == 0) return 0;
    return A[0] + sum(A+1, n-1);
}
// Depth: O(n), total calls: O(n)
```

### Binary Recursion
Dua pemanggilan rekursif per langkah.
```cpp
ll fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
// Depth: O(n), total calls: O(2^n) — TANPA MEMO
```

### Tree/Divide-and-Conquer
Split menjadi dua setengah.
```cpp
void mergeSort(int* A, int l, int r) {
    if (l >= r) return;
    int mid = (l+r)/2;
    mergeSort(A, l, mid);
    mergeSort(A, mid+1, r);
    merge(A, l, mid, r);
}
// Depth: O(log n), total calls: O(n)
```

### Mutual Recursion
Dua fungsi saling memanggil.
```cpp
bool isEven(int n) {
    if (n == 0) return true;
    return isOdd(n - 1);
}
bool isOdd(int n) {
    if (n == 0) return false;
    return isEven(n - 1);
}
```

---

## 11. Kapan Pakai Rekursi

### Cocok Dipakai Rekursi

| Masalah | Alasan |
|---------|--------|
| Pohon (tree traversal) | Struktur rekursif alami |
| Divide & conquer | Masalah = dua submasalah |
| Backtracking | Undo state dengan return |
| Parsing (ekspresi, tanda kurung) | Struktur nested |
| Tower of Hanoi, GCD | Definisi rekursif matematis |
| DFS pada graf | Kunjungi tetangga rekursif |

### Sebaiknya Iteratif

| Masalah | Alasan |
|---------|--------|
| n besar (>10^5) | Stack overflow |
| Fibonacci besar | Memoization → bottom-up DP lebih aman |
| Loop sederhana | Rekursi overhead tidak perlu |

---

## 12. Konversi Rekursi → Iteratif

Setiap rekursi bisa diubah iteratif dengan **explicit stack** (STL `stack<>`).

### Contoh: Factorial Iteratif

```cpp
ll factIter(int n) {
    ll result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
```

### Contoh: Fibonacci Iteratif (Bottom-up DP)

```cpp
ll fibDP(int n) {
    if (n <= 1) return n;
    ll a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        ll c = a + b;
        a = b; b = c;
    }
    return b;
}
```

### Contoh: DFS Iteratif dengan Stack

```cpp
void dfs(vector<vector<int>>& adj, int start) {
    stack<int> st;
    vector<bool> visited(adj.size(), false);
    st.push(start);
    while (!st.empty()) {
        int v = st.top(); st.pop();
        if (visited[v]) continue;
        visited[v] = true;
        cout << v << "\n";
        for (int u : adj[v]) st.push(u);
    }
}
```

---

## Ringkasan Kompleksitas

| Fungsi | Time | Space | Catatan |
|--------|------|-------|---------|
| factorial(n) | O(n) | O(n) stack | Iteratif O(1) space |
| fib(n) naif | O(2^n) | O(n) stack | JANGAN pakai tanpa memo |
| fib(n) memo | O(n) | O(n) | Aman untuk n≤100 |
| hanoi(n) | O(2^n) | O(n) stack | Minimum langkah = 2^n-1 |
| fastpow(a,b) | O(log b) | O(log b) | Gunakan untuk b>10^6 |
| gcd(a,b) | O(log min) | O(log) | Sangat cepat |
| isPalin(s,l,r) | O(n) | O(n) | Iteratif O(1) space |
