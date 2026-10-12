/*
============================================================
🏋️ Exercise 6: Penjaga Museum Berjarak (House Robber O(1) Space)
============================================================
Day: 153 | Difficulty: Easy-Medium | Topic: O(1) Memory State Compression
Source: LeetCode 198 / Classic DP 1D
Time Limit: 2.0 detik | Memory Limit: 16 MB

📋 PROBLEM STATEMENT:
Seorang pencuri berencana mengambil artefak berharga dari deretan N ruangan pameran di museum.
Ruangan pameran berbaris lurus dan dinomori dari 1 hingga N.
Ruangan ke-i menyimpan artefak dengan nilai a[i].

Museum ini memiliki sistem keamanan otomatis: jika dua ruangan yang berdampingan langsung
(misalnya ruangan i dan i + 1) sama-sama dibobol pada malam yang sama, alarm utama akan berbunyi
dan polisi akan langsung datang.
Oleh karena itu, pencuri TIDAK BOLEH mengambil artefak dari dua ruangan yang bertetangga!

Tentukan TOTAL NILAI MAKSIMUM artefak yang bisa didapatkan tanpa pernah memicu alarm.

Batasan: N dapat mencapai 1.000.000.
Batas memori program sangat ketat, yaitu 16 MB.
Kamu DILARANG membuat array DP ukuran N!
Selesaikan masalah ini dengan menggunakan ruang memori konstan O(1) (hanya beberapa variabel)!

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat non-negatif a[0], a[1], ..., a[N-1].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total nilai maksimum yang dapat diperoleh.

📏 CONSTRAINTS:
- 1 <= N <= 1.000.000
- 0 <= a[i] <= 1.000.000.000
- Batas memori tambahan O(1) (tidak boleh menyimpan array DP)

📎 SAMPLE INPUT 1:
4
1 2 3 1

📎 SAMPLE OUTPUT 1:
4

[Penjelasan Sample 1:
Pilih ruangan 1 (nilai 1) dan ruangan 3 (nilai 3).
Total nilai = 1 + 3 = 4.
(Jika memilih ruangan 2 dan 4, nilai = 2 + 1 = 3).]

📎 SAMPLE INPUT 2:
5
2 7 9 3 1

📎 SAMPLE OUTPUT 2:
12

[Penjelasan Sample 2:
Pilih ruangan 1 (2), ruangan 3 (9), dan ruangan 5 (1).
Total nilai = 2 + 9 + 1 = 12.]

📎 SAMPLE INPUT 3:
1
100

📎 SAMPLE OUTPUT 3:
100

💡 HINT:
- Perhatikan relasi rekurens standar:
  `dp[i] = max(dp[i - 1], dp[i - 2] + a[i])`.
- Untuk menghitung nilai saat ini, kita HANYA butuh dua nilai sebelumnya:
  - `prev2`: merepresentasikan `dp[i - 2]`.
  - `prev1`: merepresentasikan `dp[i - 1]`.
- Di setiap langkah ruangan `x`:
  - `cur = max(prev1, prev2 + x);`
  - Geser jendela: `prev2 = prev1; prev1 = cur;`
- Pemakaian memori: O(1) konstan!

🎯 Learning Goals:
- [ ] Menekan memori DP 1D menjadi O(1) variabel lepas (*sliding window of states*).
- [ ] Mencegah alokasi array besar pada N = 10^6 dengan pemrosesan streaming O(1) memori.
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

    // TODO: Selesaikan House Robber dengan O(1) memori
    // Gunakan prev2, prev1, dan baca elemen langsung per perulangan

    return 0;
}
