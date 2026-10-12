/*
============================================================
✅ Solusi 6: explicit dan Named Constructor
============================================================
🎯 Yang dilatih: overloading constructor, explicit, static member function

📖 HASIL EKSPERIMEN

   TANPA explicit, baris `cetakSuhu(25);` KOMPILASI DENGAN SUKSES.
   Kompilator diam-diam mengubah 25 menjadi Suhu(25), lalu mencetak
   "25C = 77F".

   Kelihatannya nyaman. Masalahnya: 25 itu apa? Pembaca kode tidak
   punya cara mengetahuinya tanpa membuka definisi Suhu. Kalau nanti
   kamu mengganti constructor utamanya jadi Fahrenheit, SEMUA
   pemanggilan seperti ini diam-diam berubah artinya - tanpa satu pun
   error kompilasi.

   DENGAN explicit, baris itu ditolak:
       error: could not convert '25' from 'int' to 'const Suhu&'

   Pemanggil dipaksa menulis cetakSuhu(Suhu(25)), yang menyatakan
   niatnya secara jelas.

📖 KENAPA dariFahrenheit() STATIC, BUKAN CONSTRUCTOR

   Dua alasan.

   1. TIDAK BISA. Suhu(double) sudah dipakai untuk Celsius. Constructor
      kedua dengan tanda tangan Suhu(double) adalah duplikat, dan
      kompilator menolaknya. Tanda tangan constructor tidak bisa
      dibedakan hanya oleh "maksudnya".

   2. LEBIH JELAS meski andaikan bisa. Bandingkan:
          Suhu s(212);                      // 212 apa?
          Suhu s = Suhu::dariFahrenheit(212);   // jelas
      Namanya sendiri sudah jadi dokumentasi. Pola ini disebut
      "named constructor idiom", dan berguna setiap kali sebuah tipe
      punya beberapa cara pembuatan yang tipenya sama.

📖 KENAPA static

   dariFahrenheit tidak butuh objek - ia MEMBUAT objek. Fungsi non-static
   butuh objek yang sudah ada untuk dipanggil, dan di sini belum ada.
   Itu sebabnya ia harus static.

   Pemanggilannya lewat nama kelas: Suhu::dariFahrenheit(212).

📖 KENAPA MENYIMPAN CELSIUS SAJA, BUKAN KEDUANYA

   Menyimpan celsius_ dan fahrenheit_ sekaligus berarti ada dua sumber
   kebenaran yang harus selalu konsisten - dan invariant seperti itu
   mudah bocor. Simpan satu, hitung yang lain saat diminta.

   Aturan umum yang layak dibawa: JANGAN SIMPAN APA YANG BISA DIHITUNG,
   kecuali perhitungannya mahal dan terbukti jadi hambatan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Suhu {
public:
    Suhu() : celsius_(0) {}
    explicit Suhu(double celsius) : celsius_(celsius) {}

    // named constructor - lebih jelas daripada constructor kedua
    static Suhu dariFahrenheit(double f) {
        return Suhu((f - 32.0) * 5.0 / 9.0);
    }

    double celsius() const { return celsius_; }

    // dihitung, bukan disimpan - hanya satu sumber kebenaran
    double fahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }

private:
    double celsius_;
};

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

    // cetakSuhu(25);   <- ditolak karena explicit. Itu tujuannya.
    return 0;
}
