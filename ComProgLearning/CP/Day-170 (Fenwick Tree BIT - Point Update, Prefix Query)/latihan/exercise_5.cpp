/*
============================================================
🏋️ Exercise 5: Gaji Karyawan
============================================================
Day: 170 | Difficulty: Hard
Topic: BIT + kompresi dengan nilai dari query
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah perusahaan punya N karyawan, karyawan ke-i bergaji p[i].
Ada Q operasi:
- "! k x" : ubah gaji karyawan ke-k menjadi x.
- "? a b" : cetak berapa karyawan yang gajinya berada di antara a dan b
  (inklusif).
Gaji bisa mencapai 10^9.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan gaji awal
- Q baris berikutnya: operasi

📤 OUTPUT FORMAT:
- Satu baris untuk setiap operasi "?"

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- 1 <= gaji, x, a, b <= 10^9

📎 SAMPLE INPUT 1:
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3

📎 SAMPLE OUTPUT 1:
3
2

💡 HINT: Struktur hari ini diindeks oleh nilai, sehingga kompresi koordinat
         diperlukan. Tetapi ada jebakan yang tidak muncul di Exercise 2:
         nilai yang perlu diindeks TIDAK HANYA berasal dari array awal.
         Pikirkan nilai apa saja yang akan pernah kamu jadikan indeks
         selama seluruh program berjalan — termasuk yang muncul di
         operasi-operasi berikutnya.
         Kalau kamu membangun kamus kompresi hanya dari gaji awal, apa yang
         terjadi saat operasi "!" mengubah gaji menjadi nilai yang belum
         pernah ada?
         Ini berarti kamu harus membaca SELURUH operasi sebelum mulai
         memproses apa pun. Teknik itu punya nama, dan kamu sudah
         memakainya di Day 53.
         Untuk operasi "?", batas a dan b juga perlu dipetakan — tetapi
         hati-hati, keduanya belum tentu ada di dalam kamus. Pikirkan bound
         mana yang tepat untuk masing-masing.

🎯 Learning Goals:
- [ ] Mengumpulkan SELURUH nilai sebelum membangun kamus kompresi
- [ ] Memproses query secara offline
- [ ] Memetakan batas query yang tidak ada di kamus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca SELURUH operasi dulu, kumpulkan semua nilai

    // TODO: bangun kamus kompresi, lalu proses ulang operasinya

    // TODO: untuk batas query, pilih bound yang tepat

    return 0;
}
