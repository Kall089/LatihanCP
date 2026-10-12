/*
============================================================
📋 TUGAS 05: Deteksi Kapan PBS Tidak Perlu
============================================================
Source: Original
Difficulty: Easy
Topics: analisis

PROBLEM:
Diberikan Q deskripsi soal dalam bentuk terstruktur, tentukan untuk setiap
soal apakah ia (a) bisa diselesaikan dengan SATU sapuan, (b) butuh parallel
binary search, atau (c) tidak bisa offline sama sekali.
Setiap deskripsi berisi tiga bilangan: apakah query online (0/1), apakah
seluruh query memeriksa besaran yang sama (0/1), dan apakah predikatnya
monoton (0/1). Cetak SATU_SAPUAN, PBS, atau TIDAK_BISA.

INPUT FORMAT:
- Baris pertama: Q
- Q baris berisi tiga bilangan 0/1

OUTPUT FORMAT:
- Q baris

CONSTRAINTS:
- 1 <= Q <= 1000

SAMPLE INPUT 1:
3
0 1 1
0 0 1
1 0 1

SAMPLE OUTPUT 1:
SATU_SAPUAN
PBS
TIDAK_BISA
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Soal ini melatih POHON KEPUTUSAN sebelum menulis kode: online -> tidak bisa; besaran sama -> satu sapuan; selain itu -> PBS.

    return 0;
}
