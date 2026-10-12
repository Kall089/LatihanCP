/*
============================================================
🏋️ Exercise 2: Pekerjaan Bertenggat
============================================================
Day: 77 | Difficulty: Easy
Topic: Regret dengan arah heap berlawanan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan. Setiap pekerjaan memerlukan TEPAT SATU satuan waktu.
Pekerjaan ke-i memberi keuntungan p[i] dan harus dikerjakan pada salah satu
slot waktu 1 sampai d[i].
Setiap slot waktu hanya bisa diisi satu pekerjaan.
Cari TOTAL KEUNTUNGAN MAKSIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: d[i] dan p[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total keuntungan maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= d[i] <= N
- 1 <= p[i] <= 10^9

📎 SAMPLE INPUT 1:
4
4 20
1 10
1 40
1 30

📎 SAMPLE OUTPUT 1:
60

📎 SAMPLE INPUT 2:
3
1 5
1 5
1 5

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Kerangkanya sama persis dengan Exercise 1: urutkan, ambil semua,
         batalkan saat melanggar.
         Tapi ada satu perbedaan yang harus kamu temukan sendiri. Pada
         Exercise 1, batasannya adalah TOTAL WAKTU. Di sini setiap
         pekerjaan memakan slot yang sama besarnya, sehingga batasannya
         adalah JUMLAH pekerjaan.
         Pertanyaan kuncinya: kalau semua pekerjaan memakan sumber daya
         yang sama, apa arti "pilihan terburuk"?
         Jawabanmu akan menentukan arah heap yang kamu pakai, dan arah itu
         BERLAWANAN dengan Exercise 1. Salah arah tidak menghasilkan error
         apa pun — hanya jawaban yang salah.
         Sampel 2 adalah pemeriksaan paling sederhana: tiga pekerjaan yang
         semuanya harus di slot 1. Hanya satu yang bisa dikerjakan.
         Renungkan juga: kenapa memeriksa "jumlah terpilih tidak melebihi
         tenggat sekarang" sudah cukup untuk menjamin seluruh jadwal layak?

🎯 Learning Goals:
- [ ] Menyesuaikan arti "terburuk" dengan bentuk batasannya
- [ ] Memilih arah heap secara sadar
- [ ] Memahami kenapa pemeriksaan prefiks sudah menjamin kelayakan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan menurut tenggat

    // TODO: tentukan apa arti "terburuk" di sini, lalu pilih arah heap

    return 0;
}
