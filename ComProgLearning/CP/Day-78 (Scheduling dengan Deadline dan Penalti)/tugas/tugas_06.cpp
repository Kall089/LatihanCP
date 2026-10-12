/*
============================================================
📋 TUGAS 06: Denda dengan Waktu Rilis
============================================================
Source: 1 | rj | sum wj Uj
Difficulty: Hard
Topics: Bitmask

PROBLEM:
Ada n pekerjaan. Pekerjaan ke-i baru tersedia mulai waktu r[i], butuh t[i] waktu,
bertenggat d[i], dan berdenda w[i] kalau terlambat. Mesin boleh menganggur menunggu.
Cari total denda minimum.

INPUT FORMAT:
Baris 1: n
n baris berikutnya: r[i], t[i], d[i], w[i]

OUTPUT FORMAT:
Satu bilangan: total denda minimum

CONSTRAINTS:
1 <= n <= 18, 0 <= r[i] <= 10^9, 1 <= t[i] <= 10^9, 1 <= d[i] <= 10^18

SAMPLE INPUT 1:
2
0 5 5 3
1 1 2 100

SAMPLE OUTPUT 1:
3
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Pisahkan kelayakan dari bobot. Hitung f[mask] = waktu selesai minimum untuk menjadwalkan mask semuanya tepat waktu, lalu maksimalkan bobot mask yang layak. Menyimpan (denda, waktu) sekaligus akan SALAH.

    return 0;
}
