/*
============================================================
🏋️ Exercise 1: Peringkat Siswa
============================================================
Day: 76 | Difficulty: Easy
Topic: Tie-break berlapis
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N siswa. Siswa ke-i punya nilai n[i], usia u[i], dan nomor urut
pendaftaran (yaitu urutan kemunculannya pada masukan, dimulai dari 1).
Urutkan siswa dengan aturan berikut, diterapkan secara berlapis:
  1. Nilai LEBIH BESAR lebih dulu.
  2. Kalau nilainya sama, usia LEBIH MUDA lebih dulu.
  3. Kalau usianya juga sama, nomor pendaftaran LEBIH KECIL lebih dulu.
Cetak nomor pendaftaran siswa sesuai urutan hasil.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: n[i] dan u[i]

📤 OUTPUT FORMAT:
- Satu baris berisi N nomor pendaftaran

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= n[i] <= 100
- 1 <= u[i] <= 100

📎 SAMPLE INPUT 1:
5
90 20
85 19
90 19
85 19
90 20

📎 SAMPLE OUTPUT 1:
3 1 5 2 4

📎 SAMPLE INPUT 2:
1
50 30

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Soal ini terlihat sepele, dan justru karena itu ia berharga.
         Perhatikan batasan nilainya: paling besar 100. Itu berarti nilai
         yang SAMA akan sering muncul, dan lapis kedua serta ketiga
         benar-benar akan diuji.
         Tulis komparatormu dengan bentuk yang memeriksa KETIDAKSAMAAN
         lebih dulu di setiap lapis. Bentuk yang menulis serangkaian
         "kalau ini lebih kecil kembalikan benar" tanpa memeriksa
         kesamaan akan menghasilkan komparator yang tidak konsisten.
         Uji sendiri: jalankan komparatormu dengan dua argumen yang SAMA
         PERSIS. Kalau hasilnya benar, kodemu salah.
         Lapis ketiga membuat komparatormu menjadi urutan total. Pikirkan
         kenapa itu menghilangkan seluruh kelas kesalahan sekaligus, dan
         kenapa itu lebih baik daripada mengandalkan sorting yang stabil.

🎯 Learning Goals:
- [ ] Menulis komparator berlapis dengan bentuk yang benar
- [ ] Menguji irrefleksivitas komparator sendiri
- [ ] Memahami nilai indeks sebagai tie-break terakhir
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct Mhs
{
  int nilai;
  int usia;
  int idx;
};

int main()
{
  int n;
  cin >> n;

  vector<Mhs> s(n);

  for (int i = 0; i < n; i++)
  {
    cin >> s[i].nilai >> s[i].usia;
    s[i].idx = i + 1;
  }

  auto comp = [&](Mhs &a, Mhs &b)
  {
    if (a.nilai != b.nilai)
    {
      return a.nilai > b.nilai;
    }
    if (a.usia != b.usia)
    {
      return a.usia < b.usia;
    }

    return a.idx < b.idx;
  };

  sort(s.begin(), s.end(), comp);

  for (int i = 0; i < n; i++)
  {
    cout << s[i].idx << " ";
  }
}