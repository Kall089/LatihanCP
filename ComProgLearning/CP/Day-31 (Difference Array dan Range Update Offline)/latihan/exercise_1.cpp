/*
============================================================
🏋️ Exercise 1: Range Update Sederhana
============================================================
Day: 29 | Difficulty: Easy
Topic: Difference Array 1D
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah deretan N kotak berjajar, masing-masing berisi angka 0.
Kamu menerima Q perintah. Setiap perintah berbentuk "l r v" yang artinya:
tambahkan nilai v ke SEMUA kotak dari posisi l sampai posisi r (inklusif).
Setelah semua perintah dijalankan, cetak isi akhir seluruh kotak.
Perhatikan N dan Q bisa sangat besar, jadi mengubah kotak satu per satu
untuk setiap perintah akan terlalu lambat.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan Q
- Q baris berikutnya: tiga integer l, r, v

📤 OUTPUT FORMAT:
- Satu baris berisi N integer: isi akhir kotak 1 sampai N, dipisah spasi.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2 × 10^5
- 1 ≤ Q ≤ 2 × 10^5
- 1 ≤ l ≤ r ≤ N
- -10^9 ≤ v ≤ 10^9  (hasil akhir bisa mencapai ±2 × 10^14, gunakan long long!)

📎 SAMPLE INPUT 1:
5 3
1 3 2
2 5 3
4 4 -1

📎 SAMPLE OUTPUT 1:
2 5 5 2 3

📎 SAMPLE INPUT 2:
4 1
1 4 7

📎 SAMPLE OUTPUT 2:
7 7 7 7

💡 HINT:
- Jangan ubah seluruh rentang. Cukup tandai DUA titik saja per perintah.
- diff[l] += v menandai "mulai bertambah di sini".
- diff[r + 1] -= v menandai "berhenti bertambah setelah r".
- Di akhir, jalan sekali dari kiri sambil menjumlahkan (prefix sum).

🎯 Learning Goals:
- [ ] Memahami rumus dasar difference array
- [ ] Menyadari kenapa pengurang ditaruh di r+1, bukan r
- [ ] Terbiasa memakai ukuran array n+2 dan tipe long long
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> diff(n + 2, 0);

    for (int i = 0; i < q; i++)
    {
        int l, r, val;

        cin >> l >> r >> val;

        diff[l] += val;
        diff[r + 1] -= val;
    }

    for (int i = 1; i <= n; i++)
    {
        diff[i] += diff[i - 1];
    }

    for (int i = 1; i <= n; i++)
    {
        cout << diff[i] << " ";
    }
}
