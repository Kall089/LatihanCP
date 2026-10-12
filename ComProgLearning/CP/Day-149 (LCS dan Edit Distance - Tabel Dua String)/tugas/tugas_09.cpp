/*
============================================================
📋 TUGAS 09: LCS dengan Rolling Array
============================================================
Source: Latihan optimasi
Difficulty: Medium
Topics: memori O(min(n,m))

PROBLEM:
Cetak panjang LCS, tetapi memori yang dipakai harus O(min(|A|,|B|)).
Uji dengan string panjang untuk memastikan tidak MLE.

INPUT: dua baris
OUTPUT: satu bilangan
CONSTRAINTS: 1 <= |A|, |B| <= 10^4  (tabel penuh akan 400 MB - MLE)

SAMPLE INPUT 1:      SAMPLE OUTPUT 1:
abcde                3
ace

SAMPLE INPUT 2:      SAMPLE OUTPUT 2:
abcbdab              4
bdcaba

SAMPLE INPUT 3:      SAMPLE OUTPUT 3:
xyz                  0
abc
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false);cin.tie(NULL);
    // TODO: Kerjakan di sini
    // SIMPAN nilai diagonal SEBELUM ditimpa:
    //     int simpan = dp[j];  ... ; prevDiag = simpan;
    // Tukar A dan B agar yang digulung adalah dimensi yang LEBIH KECIL.
    // Catat: dengan cara ini rekonstruksi menjadi mustahil.
    return 0;}
