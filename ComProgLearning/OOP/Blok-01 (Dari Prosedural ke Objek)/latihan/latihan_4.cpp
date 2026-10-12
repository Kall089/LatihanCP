/*
============================================================
🏋️ Latihan 4: Perbaiki Initializer List
============================================================
Blok: 1 | Tingkat: Sedang | Estimasi: 25 menit
Topik: member initializer list, urutan inisialisasi

📋 TUGAS:
Ada TIGA class di bawah, semuanya punya masalah. Perbaiki ketiganya.

  BagianA - kompilasi berhasil tapi HASILNYA SALAH
            (compile dengan -Wall untuk melihat petunjuknya)
  BagianB - kompilasi GAGAL. Kenapa? Perbaiki.
  BagianC - kompilasi GAGAL. Kenapa? Perbaiki.

⚠️ Compile dengan: g++ -std=c++17 -Wall latihan_4.cpp
   Peringatan -Wreorder itu penting, jangan diabaikan.

❓ Untuk masing-masing, tulis di komentar:
   - apa masalahnya
   - kenapa aturan C++ membuatnya begitu

📤 KELUARAN YANG DIHARAPKAN SETELAH DIPERBAIKI:
A: lebar=10 tinggi=20 luas=200
B: PI=3.14159 radius=2 keliling=12.5664
C: mesin daya 150 terpasang
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══ BAGIAN A - kompilasi berhasil, hasilnya salah ═══
class BagianA {
    int luas_;             // perhatikan urutan deklarasi ketiganya
    int lebar_;
    int tinggi_;
public:
    BagianA(int w, int h) : lebar_(w), tinggi_(h), luas_(lebar_ * tinggi_) {}

    void cetak() const {
        cout << "A: lebar=" << lebar_ << " tinggi=" << tinggi_
             << " luas=" << luas_ << "\n";
    }
};

// ═══ BAGIAN B - kompilasi gagal ═══
class BagianB {
    const double PI_;
    double radius_;
public:
    BagianB(double r) {
        PI_ = 3.14159;
        radius_ = r;
    }
    void cetak() const {
        cout << "B: PI=" << PI_ << " radius=" << radius_
             << " keliling=" << 2 * PI_ * radius_ << "\n";
    }
};

// ═══ BAGIAN C - kompilasi gagal ═══
class Mesin {
public:
    Mesin(int daya) : daya_(daya) {}
    int daya() const { return daya_; }
private:
    int daya_;
};

class BagianC {
    Mesin mesin_;
public:
    BagianC() {
    }
    void cetak() const {
        cout << "C: mesin daya " << mesin_.daya() << " terpasang\n";
    }
};

int main() {
    BagianA a(10, 20);  a.cetak();
    BagianB b(2);       b.cetak();
    BagianC c;          c.cetak();
    return 0;
}

/*
MASALAH A:

MASALAH B:

MASALAH C:

*/
