/*
============================================================
🏋️ Exercise 2: Nilai Tertinggi Setelah Semua Perintah
============================================================
Day: 29 | Difficulty: Easy-Medium
Topic: Difference Array 1D + pelacakan maksimum
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah gedung apartemen punya N lantai yang awalnya kosong (0 penghuni).
Ada Q pengumuman, masing-masing berbentuk "l r v" yang berarti
sebanyak v penghuni baru menempati SETIAP lantai dari l sampai r.
Setelah semua pengumuman selesai, manajemen ingin tahu lantai mana
yang paling padat dan berapa penghuninya.
Jika ada beberapa lantai dengan kepadatan sama, pilih nomor lantai TERKECIL.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan Q
- Q baris berikutnya: tiga integer l, r, v

📤 OUTPUT FORMAT:
- Satu baris berisi dua integer: nilai maksimum dan nomor lantai terkecil
  yang mencapai nilai tersebut, dipisah satu spasi.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2 × 10^5
- 1 ≤ Q ≤ 2 × 10^5
- 1 ≤ l ≤ r ≤ N
- 1 ≤ v ≤ 10^9

📎 SAMPLE INPUT 1:
6 3
1 4 10
2 6 5
5 5 100

📎 SAMPLE OUTPUT 1:
105 5

📎 SAMPLE INPUT 2:
3 2
1 3 4
1 1 4

📎 SAMPLE OUTPUT 2:
8 1

💡 HINT:
- Kamu tidak perlu menyimpan seluruh array hasil.
- Cukup jalankan prefix sum sambil melacak nilai terbesar yang pernah dilihat.
- Karena kita berjalan dari kiri ke kanan, lantai terkecil otomatis
  terpilih kalau kamu memakai perbandingan ">" (bukan ">=").

🎯 Learning Goals:
- [ ] Menggabungkan rekonstruksi dengan perhitungan lain dalam satu loop
- [ ] Menangani tie-breaking (ambil indeks terkecil) dengan benar
- [ ] Menyadari bahwa array hasil tidak selalu perlu disimpan
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

  int curr_val = 0;
  int floor = -1;
  int max_val = -1;

  for (int i = 1; i <= n; i++)
  {
    curr_val += diff[i];

    if (curr_val > max_val)
    {
      max_val = curr_val;
      floor = i;
    }
  }

  cout << max_val << " " << floor << endl;
}