/*
============================================================
🏋️ Exercise 1: Rute Foto Pematang (Frog Jump Path Reconstruction)
============================================================
Day: 152 | Difficulty: Easy-Medium | Topic: Suffix DP + Lexicographical Path Reconstruction
Source: Educational / AtCoder Frog Jump Variation
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang fotografer lanskap sedang menyusuri deretan pematang sawah yang terdiri dari N pos,
dinomori dari 1 hingga N dari barat ke timur.
Pos ke-i memiliki ketinggian H[i] meter di atas permukaan laut.

Fotografer memulai perjalanannya tepat di Pos 1 dan harus berakhir di Pos N.
Dari pos i saat ini, fotografer hanya diperbolehkan melangkah maju ke salah satu dari dua pos berikutnya:
- Pos i + 1, dengan biaya energi |H[i] - H[i+1]|
- Pos i + 2 (jika i + 2 <= N), dengan biaya energi |H[i] - H[i+2]|

Tentukan:
1. Total energi minimum yang diperlukan untuk berpindah dari Pos 1 ke Pos N.
2. Jumlah pos yang dikunjungi dalam rute tersebut (L).
3. Daftar nomor pos yang dikunjungi (1-indexed), dimulai dari 1 dan berakhir di N.

Aturan Pemecah Seri (Tie-Breaker):
Jika terdapat lebih dari satu jalur yang menghasilkan total energi minimum yang sama,
pilih jalur yang terkecil secara LEKSIKOGRAFIS berdasarkan daftar indeks posnya.
(Artinya, bandingkan dua rute pada posisi pertama di mana indeks pos yang dikunjungi berbeda;
rute dengan indeks pos lebih kecil yang dipilih).

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- Baris kedua berisi N bilangan bulat H[0], H[1], ..., H[N-1] (0-indexed dalam pembacaan, nomor pos 1..N).

📤 OUTPUT FORMAT:
- Baris pertama: satu bilangan bulat, energi minimum.
- Baris kedua: satu bilangan bulat L, jumlah pos yang dikunjungi.
- Baris ketiga: L bilangan bulat dipisahkan spasi, nomor pos yang dikunjungi.

📏 CONSTRAINTS:
- 1 <= N <= 300
- 0 <= H[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
10 30 20 40

📎 SAMPLE OUTPUT 1:
30
3
1 2 4

[Penjelasan Sample 1:
Pilihan jalur:
- 1 -> 2 -> 4: biaya |10-30| + |30-40| = 20 + 10 = 30.
- 1 -> 3 -> 4: biaya |10-20| + |20-40| = 10 + 20 = 30.
Kedua jalur sama-sama membutuhkan energi 30.
Bandingkan urutan pos:
Jalur pertama: [1, 2, 4]
Jalur kedua:   [1, 3, 4]
Pada elemen kedua, 2 < 3. Maka rute [1, 2, 4] lebih kecil secara leksikografis.]

📎 SAMPLE INPUT 2:
1
8

📎 SAMPLE OUTPUT 2:
0
1
1

[Penjelasan Sample 2:
Hanya ada 1 pos. Fotografer sudah berada di pos tujuan sejak awal.
Biaya 0, panjang 1, pos [1].]

📎 SAMPLE INPUT 3:
3
5 5 5

📎 SAMPLE OUTPUT 3:
0
3
1 2 3

[Penjelasan Sample 3:
Semua ketinggian sama (biaya lompat selalu 0).
Jalur [1, 2, 3] memiliki biaya 0.
Jalur [1, 3] memiliki biaya 0.
Pada elemen kedua, 2 < 3. Maka jalur [1, 2, 3] menang secara leksikografis meskipun lebih panjang!]

💡 HINT:
- Gunakan Suffix DP:
  Definisikan dp[i] = energi minimum untuk mencapai Pos N dari Pos i.
  Isi tabel dari i = N-2 mundur ke 0.
- Rekonstruksi:
  Mulai dari Pos 0 (pos 1): coba j = i + 1 lalu j = i + 2 secara berurutan.
  Pilihan pertama yang memenuhi: `dp[i] == abs(H[i] - H[j]) + dp[j]`
  dijamin optimal sekaligus leksikografis paling awal!

🎯 Learning Goals:
- [ ] Memahami teknik Suffix DP untuk menjamin urutan rekonstruksi leksikografis optimal.
- [ ] Membedakan antara minimasi panjang jalur vs. leksikografis indeks.
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

    vector<ll> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // TODO: Selesaikan Rute Foto Pematang dengan Suffix DP
    // 1. Tabulasi suffix dp[i] dari N-2 ke 0
    // 2. Rekonstruksi jalur leksikografis dari pos 0
    // 3. Cetak energi, jumlah pos L, dan rute pos

    return 0;
}
