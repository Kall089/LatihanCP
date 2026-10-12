/*
============================================================
🏋️ Exercise 4: Rata-rata Segmen Terbaik
============================================================
Day: 51 | Difficulty: Medium
Topic: Trik a[i] - x + prefix sum
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Seorang peternak punya N petak pagar berjajar, petak ke-i bernilai a[i].
Ia ingin memilih SEGMEN BERURUTAN dengan panjang SETIDAKNYA L, sedemikian
sehingga rata-rata nilai petak di dalam segmen itu semaksimal mungkin.
Cetak rata-rata maksimum itu dengan 3 desimal.
Berbeda dari Exercise 3, di sini elemen yang dipilih harus BERURUTAN,
sehingga tidak ada solusi langsung dengan mengurutkan.

📥 INPUT FORMAT:
- Baris pertama: N dan L
- N baris berikutnya: masing-masing satu bilangan bulat a[i]

📤 OUTPUT FORMAT:
- Satu bilangan real dengan 3 desimal

📏 CONSTRAINTS:
- 1 <= L <= N <= 10^5
- 0 <= a[i] <= 2000

📎 SAMPLE INPUT 1:
10 6
6
4
2
10
3
8
5
9
4
1

📎 SAMPLE OUTPUT 1:
6.500

Penjelasan: segmen terbaik adalah petak ke-4 sampai ke-9 (nilai
10, 3, 8, 5, 9, 4) dengan jumlah 39 dan panjang 6, sehingga rata-ratanya
6.5.

📎 SAMPLE INPUT 2:
3 1
1
2
3

📎 SAMPLE OUTPUT 2:
3.000

💡 HINT: Terapkan transformasi yang sama dengan Exercise 3. Setelah setiap
         a[i] diganti dengan (a[i] - x), pertanyaannya menjadi: "adakah
         segmen berurutan sepanjang setidaknya L yang JUMLAHNYA tidak
         negatif?"
         Untuk menjawab itu dalam O(N), pakai prefix sum lalu — untuk setiap
         ujung kanan i — bandingkan dengan prefix TERKECIL di antara semua
         ujung kiri yang sah. Perhatikan bahwa himpunan ujung kiri yang sah
         bertambah satu setiap kali i maju.

🎯 Learning Goals:
- [ ] Menggabungkan transformasi a[i]-x dengan prefix sum
- [ ] Menjaga minimum berjalan atas himpunan yang bertambah
- [ ] Menyadari batasan panjang minimal L memengaruhi indeks mana yang boleh
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: predikat bisa(x) dengan prefix sum atas (a[i] - x)

    // TODO: jaga minimum prefix yang sudah "cukup jauh" di kiri

    return 0;
}
