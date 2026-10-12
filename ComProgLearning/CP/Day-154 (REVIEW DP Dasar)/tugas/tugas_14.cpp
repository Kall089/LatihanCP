/*
============================================================
📋 TUGAS 14: Penataan Balok Menara 3D Tertinggi
============================================================
Source: Classic DP / Box Stacking Problem
Difficulty: Medium-Hard
Topics: LIS on DAG, 3D Geometry

PROBLEM:
Diberikan N buah tipe balok dengan dimensi (panjang l[i], lebar w[i], tinggi h[i]).
Setiap tipe balok boleh digunakan berkali-kali dan boleh diputar dalam 3 orientasi berbeda
sebagai alas (panjang dan lebar) dan tinggi.
Kamu ingin membangun menara balok setinggi mungkin dengan menumpuk balok-balok tersebut.
Sebuah balok hanya boleh ditaruh di atas balok lain jika PANJANG dan LEBAR alasnya
KEDUANYA LEBIH KECIL SECARA KETAT daripada panjang dan lebar balok di bawahnya.
Tentukan TINGGI MAKSIMUM menara yang dapat dibangun!

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya masing-masing berisi tiga bilangan bulat l[i], w[i], dan h[i].

OUTPUT FORMAT:
Satu baris berisi satu bilangan bulat: tinggi maksimum menara.

CONSTRAINTS:
1 <= N <= 100
1 <= l[i], w[i], h[i] <= 1.000

SAMPLE INPUT 1:
4
4 6 7
1 2 3
4 5 6
10 12 32

SAMPLE OUTPUT 1:
60
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Hasilkan 3 orientasi tiap balok, urutkan alas secara menurun, lalu LIS DP

    return 0;
}
