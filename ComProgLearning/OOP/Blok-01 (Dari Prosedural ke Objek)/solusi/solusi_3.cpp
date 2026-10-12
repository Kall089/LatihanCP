/*
============================================================
✅ Solusi 3: Tebak Keluaran (Siklus Hidup)
============================================================
🎯 Yang dilatih: urutan constructor & destructor

📤 KELUARAN YANG BENAR:

lahir  : global
=== main mulai ===
lahir  : a
lahir  : b
lahir  : dalam if
  ...isi if...
mati   : dalam if
lahir  : dalam fungsi
  ...isi fungsi...
mati   : dalam fungsi
lahir  : d
=== main selesai ===
mati   : d
mati   : b
mati   : a
mati   : global

📖 JAWABAN PERTANYAAN:

1. KENAPA URUTAN MATINYA TERBALIK?
   Objek lokal hidup di stack. Stack bersifat LIFO - yang terakhir masuk
   yang pertama keluar.

   Tapi alasan sebenarnya lebih dalam daripada sekadar "karena stack":
   objek yang lahir belakangan MUNGKIN memakai objek yang lahir duluan.

       Berkas f("data.txt");
       Penulis p(f);            // p memakai f

   Kalau f mati duluan, destructor p akan menyentuh objek yang sudah
   mati. Urutan terbalik adalah SATU-SATUNYA urutan yang aman secara
   umum. Ini bukan detail implementasi - ini jaminan bahasa.

2. KENAPA "dalam if" MATI SEBELUM "selesai"?
   Objek lokal mati di akhir blok { } tempat ia dideklarasikan, bukan
   di akhir fungsi. Blok if punya kurung kurawalnya sendiri.

   Ini bukan sekadar aturan - ini yang membuat RAII berguna. Kamu bisa
   membatasi umur sebuah kunci, koneksi, atau file hanya pada blok yang
   membutuhkannya:

       {
           KunciMutex k(m);     // terkunci
           // ... bagian kritis ...
       }                        // terbuka otomatis di sini

3. KALAU `Jejak d("d")` DIPINDAH KE DALAM BLOK if?
   Ia lahir setelah "dalam if", dan mati sebelum "dalam if" mati
   (terbalik), keduanya sebelum fungsi() dipanggil. Keluarannya:

       lahir  : dalam if
         ...isi if...
       lahir  : d
       mati   : d
       mati   : dalam if
       lahir  : dalam fungsi
       ...

📖 CATATAN OBJEK GLOBAL:
   Objek global lahir SEBELUM main() dan mati SETELAH main() selesai.
   Ini terlihat rapi di sini, tapi jadi sumber masalah nyata: urutan
   inisialisasi antar-global di file .cpp yang BERBEDA tidak dijamin
   oleh standar. Namanya "static initialization order fiasco", dan itu
   salah satu alasan objek global sebaiknya dihindari. Kamu akan
   bertemu lagi dengannya saat membahas Singleton di Blok 10.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Jejak {
public:
    Jejak(const string& nama) : nama_(nama) {
        cout << "lahir  : " << nama_ << "\n";
    }
    ~Jejak() {
        cout << "mati   : " << nama_ << "\n";
    }
private:
    string nama_;
};

Jejak global("global");

void fungsi() {
    Jejak f("dalam fungsi");
    cout << "  ...isi fungsi...\n";
}

int main() {
    cout << "=== main mulai ===\n";
    Jejak a("a");
    Jejak b("b");
    if (true) {
        Jejak c("dalam if");
        cout << "  ...isi if...\n";
    }
    fungsi();
    Jejak d("d");
    cout << "=== main selesai ===\n";
    return 0;
}
