# Day 11 — Recursion Dasar

> **Topik**: Factorial, Fibonacci, Tower of Hanoi, Fast Power, GCD, Rekursi String
> **Estimasi Waktu**: 3–4 jam
> **Prasyarat**: Day 1-10 (C++ dasar, fungsi, array)

---

## Tujuan Pembelajaran

Setelah menyelesaikan Day 11, kamu akan mampu:

- [ ] Memahami konsep **base case** dan **recursive case**
- [ ] Mengimplementasikan **factorial** dan **fibonacci** secara rekursif
- [ ] Menjelaskan masalah **overlapping subproblems** pada fibonacci naif
- [ ] Menggunakan **memoization** untuk optimasi rekursi O(2^n) → O(n)
- [ ] Mensimulasikan **Tower of Hanoi** dan memahami kompleksitas O(2^n)
- [ ] Mengimplementasikan **fast power** O(log b) secara rekursif
- [ ] Menggunakan **algoritma Euclidean** (GCD rekursif)
- [ ] Menulis fungsi rekursi pada **string** (palindrome, reverse)
- [ ] Memahami **call stack** dan batas rekursi
- [ ] Mengubah rekursi menjadi iteratif dengan explicit stack

---

## Struktur Folder

```
Day-11 (Recursion)/
├── README.md               ← Kamu di sini
├── teori/
│   ├── Day_11_Teori_Lengkap.md      ← Materi teori (baca dulu!)
│   ├── generate_presentation.py     ← Script generate PPT
│   └── Day_11_Presentation.pptx     ← PPT (auto-generated)
├── latihan/
│   ├── exercise_1.cpp   (Factorial rekursif)
│   ├── exercise_2.cpp   (Fibonacci + memoization)
│   ├── exercise_3.cpp   (Tower of Hanoi)
│   ├── exercise_4.cpp   (Fast Power mod m)
│   ├── exercise_5.cpp   (GCD & LCM rekursif)
│   └── exercise_6.cpp   (Palindrome check rekursif)
├── solusi/
│   ├── solution_1.cpp   ← solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp     ← tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

### Langkah 1: Baca Teori (45 menit)
Buka `teori/Day_11_Teori_Lengkap.md` dan baca semua seksi.
Fokus pada: base case, call stack, memoization, Tower of Hanoi.

### Langkah 2: Lihat PPT (15 menit)
Generate PPT: `cd teori && python3 generate_presentation.py`
PPT memperlihatkan visualisasi call stack dan recursion tree secara visual.

### Langkah 3: Kerjakan Latihan (90 menit)
Kerjakan exercise 1–6 secara berurutan. Jangan langsung lihat solusi!

### Langkah 4: Cek Solusi
Bandingkan pendekatanmu dengan solusi di folder `solusi/`.

### Langkah 5: Kerjakan Tugas
15 soal tugas dengan tingkat kesulitan meningkat. Minimal selesaikan 10.

---

## Daftar Latihan

| File | Topik | Tingkat | Konsep Kunci |
|------|-------|---------|--------------|
| exercise_1.cpp | Factorial | Warm-up | Base case n=0, linear recursion |
| exercise_2.cpp | Fibonacci + Memo | Core | Overlapping subproblems, memo[] |
| exercise_3.cpp | Tower of Hanoi | Core | Divide & conquer recursion |
| exercise_4.cpp | Fast Power mod m | Challenge | Binary splitting, O(log b) |
| exercise_5.cpp | GCD & LCM | Core | Euclidean algorithm |
| exercise_6.cpp | Palindrome Rekursif | Core | Two-pointer via recursion |

---

## Ringkasan Tugas

| Tugas | Topik | Kesulitan |
|-------|-------|-----------|
| 01 | Sum array rekursif (no loop) | Easy |
| 02 | Maximum element rekursif | Easy |
| 03 | Count digits rekursif | Easy |
| 04 | Sum of digits rekursif | Easy |
| 05 | Reverse number rekursif | Easy |
| 06 | Binary to decimal rekursif | Medium |
| 07 | Nested braces depth | Medium |
| 08 | Ackermann function + memo | Medium |
| 09 | Catalan number + memo | Medium |
| 10 | 2^n tanpa fungsi pow() | Medium |
| 11 | Pascal triangle row n | Hard |
| 12 | Recursive flood fill | Hard |
| 13 | Josephus problem | Hard |
| 14 | Merge sort rekursif | Hard |
| 15 | Climb stairs with memo | Hard |

---

## Rekomendasi Online Judge

### CSES
- [Coin Combinations I](https://cses.fi/problemset/task/1635) — intro memoization
- [Fibonacci Numbers](https://cses.fi/problemset/task/1722) — fibonacci besar

### Codeforces
- [Codeforces 110A](https://codeforces.com/problemset/problem/110/A) — nearly lucky number
- [Codeforces 615B](https://codeforces.com/problemset/problem/615/B) — recursive tree

### LeetCode
- [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) — rekursi dasar
- [50. Pow(x, n)](https://leetcode.com/problems/powx-n/) — fast power
- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) — memoization
- [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) — rekursi list

---

## Common Mistakes

1. **Lupa base case** — rekursi tanpa base case = infinite loop = stack overflow
2. **Base case salah** — `factorial(1)` instead of `factorial(0)` akan hang di n=0
3. **Tidak reset memo** — memo array dari soal sebelumnya tidak di-`memset`
4. **Overflow** — `factorial(21)` > `long long` max, gunakan BigInteger
5. **Stack overflow** — rekursi depth > ~10^4 akan crash; pakai iteratif atau increase stack
6. **Fibonacci tanpa memo** — naif O(2^n) sangat lambat untuk n>40

---

## Quick Reference

```
Pola Rekursi Umum:
RetType func(params) {
    if (base_case) return base_value;  // WAJIB
    // Kecilkan masalah
    return combine(func(smaller_params));
}

Memoization:
ll memo[MAXN];
memset(memo, -1, sizeof(memo));
ll func(int n) {
    if (n <= base) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = func(n-1) + func(n-2);
}

Fast Power O(log b):
ll fastpow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1;
    ll half = fastpow(base, exp/2, mod);
    if (exp % 2 == 0) return half*half % mod;
    return base % mod * half % mod * half % mod;
}

GCD Euclidean:
ll gcd(ll a, ll b) { return b==0 ? a : gcd(b, a%b); }
ll lcm(ll a, ll b) { return a/gcd(a,b)*b; }
```
