# Day 170 - Fenwick Tree (Binary Indexed Tree)

## Deskripsi
Fenwick tree adalah struktur data yang mendukung query rentang (prefix sum) dan update titik dalam waktu O(log N). Lebih mudah diimplementasikan dibanding Segment Tree.

## Konsep Penting (i & -i)
Bitwise AND antara i dan -i `(i & -i)` mengembalikan bit paling tidak signifikan yang bernilai 1. Ini menentukan jangkauan (lebar) rentang yang dikelola oleh indeks i dalam tree.
