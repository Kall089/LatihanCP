/*
============================================================
🏋️ Latihan 2: Constructor yang Menjaga Invariant
============================================================
Blok: 1 | Tingkat: Mudah | Estimasi: 20 menit
Topik: constructor, invariant

📋 TUGAS:
Buat class Waktu yang menyimpan jam, menit, dan detik.

INVARIANT yang HARUS selalu benar:
  0 <= jam   <= 23
  0 <= menit <= 59
  0 <= detik <= 59

Aturan:
  1. Constructor Waktu(j, m, d) - kalau nilainya di luar rentang,
     PERBAIKI dengan normalisasi (bukan sekadar dipotong).
     Contoh: Waktu(1, 70, 0) harus menjadi 02:10:00
             Waktu(25, 0, 0) harus menjadi 01:00:00 (membungkus 24 jam)
  2. Constructor Waktu() - menghasilkan 00:00:00
  3. cetak() dengan format HH:MM:SS (dua digit, pakai nol di depan)
  4. tambahDetik(n) - menambah n detik, invariant tetap terjaga

💡 PETUNJUK: ubah semuanya jadi total detik dulu, normalkan, baru pecah lagi.
   Cara ini membuat satu tempat saja yang menjaga invariant.

⚠️ Untuk format dua digit: #include <iomanip> lalu setw(2) << setfill('0')

📤 KELUARAN YANG DIHARAPKAN:
00:00:00
13:45:30
02:10:00
01:00:00
00:00:59
00:01:00
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// TODO: tulis class Waktu di sini

int main() {
    // TODO: hidupkan kode di bawah setelah class Waktu selesai
    /*
    Waktu a;              a.cetak();      // 00:00:00
    Waktu b(13, 45, 30);  b.cetak();      // 13:45:30
    Waktu c(1, 70, 0);    c.cetak();      // 02:10:00
    Waktu d(25, 0, 0);    d.cetak();      // 01:00:00

    Waktu e(0, 0, 59);    e.cetak();      // 00:00:59
    e.tambahDetik(1);     e.cetak();      // 00:01:00
    */

    return 0;
}
