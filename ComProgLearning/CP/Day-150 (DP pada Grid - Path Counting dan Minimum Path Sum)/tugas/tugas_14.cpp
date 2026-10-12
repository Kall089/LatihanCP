/*
============================================================
📋 TUGAS 14: Grid 2 — Halangan Sedikit, Grid Raksasa
============================================================
Source: AtCoder DP-Y
Difficulty: Hard
Topics: kombinatorika + inclusion-exclusion terurut

PROBLEM:
Grid H x W dengan H, W sampai 10^5 (tabel mustahil), tetapi hanya ada N <= 3000
sel terhalang. Hitung banyak jalur kiri-atas ke kanan-bawah (kanan/bawah)
modulo 10^9+7.

INPUT: Baris 1 H W N; N baris "r c" (1-indexed) posisi halangan
OUTPUT: satu bilangan
CONSTRAINTS: 2 <= H, W <= 10^5, 1 <= N <= 3000

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
3 4 2                3
2 2
1 4

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
2 2 1                1
1 2

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
5 5 1                34
3 3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // Urutkan halangan menaik (r, lalu c). Definisikan
    //   f[i] = banyak jalur dari (1,1) ke halangan ke-i TANPA melewati
    //          halangan mana pun sebelumnya
    //        = C(jalur bebas) - sum_{j sebelum i} f[j] * C(dari j ke i)
    // Jawaban = C(ke tujuan) - sum f[i] * C(dari i ke tujuan). O(N^2).
    // Ini pola "kurangi jalur buruk yang pertama kali menyentuh halangan" --
    // layak dihafal, karena muncul di banyak soal kombinatorik berhalangan.
    return 0;}
