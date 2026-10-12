/*
============================================================
🏋️ Latihan 6: explicit dan Overloading Constructor
============================================================
Blok: 1 | Tingkat: Sedang | Estimasi: 20 menit
Topik: overloading constructor, explicit

📋 TUGAS:
Buat class Suhu yang menyimpan suhu dalam Celsius.

  1. Suhu()               -> 0 derajat Celsius
  2. Suhu(double celsius) -> dari Celsius
  3. Suhu::dariFahrenheit(double f) -> static, membuat Suhu dari Fahrenheit
     (rumus: C = (F - 32) * 5 / 9)
  4. celsius() dan fahrenheit() untuk membaca nilainya
  5. Constructor satu-parameter HARUS explicit

❓ EKSPERIMEN WAJIB:
   Setelah selesai, HAPUS kata explicit lalu hidupkan baris ini:

       cetakSuhu(25);

   Kompilasi. Apa yang terjadi? Lalu kembalikan explicit dan
   kompilasi lagi. Tulis pengamatanmu di bawah.

   Renungkan: 25 apa? Celsius? Fahrenheit? Kelvin? Kompilator diam saja
   dan memilihkan satu untukmu. Di situlah bahayanya.

💡 KENAPA dariFahrenheit dibuat static function, bukan constructor?
   Karena Suhu(double) sudah dipakai untuk Celsius, dan kamu tidak bisa
   punya dua constructor dengan tanda tangan yang sama. Nama fungsi yang
   jelas juga membuat pemanggilnya tidak perlu menebak satuannya.
   Pola ini namanya "named constructor".

📤 KELUARAN YANG DIHARAPKAN:
0C = 32F
25C = 77F
100C = 212F
212F = 100C
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// TODO: tulis class Suhu di sini

void cetakSuhu(const Suhu& s) {
    cout << s.celsius() << "C = " << s.fahrenheit() << "F\n";
}

int main() {
    Suhu a;
    cetakSuhu(a);                      // 0C = 32F

    Suhu b(25);
    cetakSuhu(b);                      // 25C = 77F

    Suhu c(100);
    cetakSuhu(c);                      // 100C = 212F

    Suhu d = Suhu::dariFahrenheit(212);
    cout << "212F = " << d.celsius() << "C\n";   // 212F = 100C

    // cetakSuhu(25);   <- EKSPERIMEN: hidupkan ini, coba dengan dan
    //                     tanpa explicit

    return 0;
}

/*
PENGAMATAN EKSPERIMEN:
  tanpa explicit :
  dengan explicit:
  kenapa explicit lebih baik di sini:
*/
