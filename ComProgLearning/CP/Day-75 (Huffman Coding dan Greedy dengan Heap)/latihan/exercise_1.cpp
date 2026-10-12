/*
============================================================
🏋️ Exercise 1: Menggabungkan Tumpukan Batu
============================================================
Day: 75 | Difficulty: Easy
Topic: Huffman dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tumpukan batu; tumpukan ke-i berisi a[i] batu.
Kamu berulang kali memilih DUA tumpukan, menggabungkannya menjadi satu, dan
membayar biaya sebesar jumlah batu kedua tumpukan itu. Tumpukan hasil
gabungan bisa dipilih lagi pada langkah berikutnya.
Proses berhenti ketika hanya tersisa satu tumpukan.
Cari TOTAL BIAYA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total biaya minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 2 3 4

📎 SAMPLE OUTPUT 1:
19

📎 SAMPLE INPUT 2:
1
5

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
6
1 1 1 1 1 1

📎 SAMPLE OUTPUT 3:
16

💡 HINT: Naluri pertama: urutkan sekali, lalu gabungkan dari kiri secara
         berurutan. Uji ide itu pada sampel 3 sebelum mempercayainya —
         kamu akan mendapat 20, bukan 16.
         Kenapa gagal? Karena tumpukan hasil gabungan HARUS bisa dipilih
         lagi bersaing dengan tumpukan asli. Array yang sudah diurutkan
         tidak bisa menerima anggota baru dengan murah.
         Struktur data apa yang selalu memberimu elemen terkecil, dan tetap
         murah ketika elemen baru dimasukkan?
         Perhatikan arah heapnya. Bawaan C++ memberi yang TERBESAR di atas;
         kamu membutuhkan kebalikannya, dan salah arah tidak akan
         menghasilkan error apa pun — hanya jawaban yang salah.
         Sampel 2 menguji kasus tanpa penggabungan sama sekali.
         Terakhir: 2*10^5 tumpukan berisi 10^9 batu. Perkirakan besar
         jawabannya sebelum memilih tipe data.

🎯 Learning Goals:
- [ ] Mengenali kapan sort sekali tidak cukup
- [ ] Memakai min-heap dengan arah yang benar
- [ ] Menangani kasus n = 1 dan memilih tipe data
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: pilih struktur data yang bisa menerima kandidat baru

    // TODO: gabungkan dua terkecil berulang kali

    return 0;
}
