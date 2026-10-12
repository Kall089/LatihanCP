/*
============================================================
✅ Solusi 4: Perbaiki Initializer List
============================================================
🎯 Yang dilatih: urutan inisialisasi, const & referensi anggota

📖 MASALAH A - URUTAN DEKLARASI vs URUTAN PENULISAN

   Deklarasinya:  luas_, lebar_, tinggi_
   Ditulisnya  :  lebar_(w), tinggi_(h), luas_(lebar_ * tinggi_)

   C++ menginisialisasi anggota menurut URUTAN DEKLARASI, jadi luas_
   dihitung PERTAMA - saat lebar_ dan tinggi_ masih berisi sampah.
   Hasilnya angka acak, dan kompilator tidak menghentikanmu.

   Kenapa aturannya begitu? Karena destructor harus menghancurkan
   anggota dengan urutan terbalik, dan urutan itu harus SAMA untuk
   semua constructor. Kalau urutannya mengikuti initializer list,
   dua constructor berbeda bisa menghasilkan urutan penghancuran yang
   berbeda - dan itu mustahil dikelola.

   PERBAIKAN: ubah urutan DEKLARASI jadi lebar_, tinggi_, luas_.
   g++ -Wall memberi peringatan -Wreorder. Jangan pernah abaikan itu.

📖 MASALAH B - ANGGOTA const TIDAK BISA DITUGASKAN

   PI_ = 3.14159; di dalam badan constructor adalah PENUGASAN, bukan
   inisialisasi. Anggota const sudah selesai diinisialisasi (dengan
   nilai tak tentu) sebelum badan constructor dimulai, dan setelah itu
   ia tidak boleh diubah selamanya.

   PERBAIKAN: pakai initializer list.
   Berlaku sama untuk anggota REFERENSI - referensi harus diikat ke
   objek saat lahir dan tidak bisa dipindah.

   CATATAN: untuk konstanta seperti PI, `static constexpr double PI =
   3.14159;` lebih baik lagi - satu salinan untuk semua objek, bukan
   satu per objek. Versi di bawah tetap memakai anggota const supaya
   pelajaran initializer list-nya terlihat.

📖 MASALAH C - ANGGOTA TANPA CONSTRUCTOR DEFAULT

   Mesin tidak punya Mesin(). Saat BagianC() dijalankan, C++ berusaha
   menginisialisasi mesin_ sebelum badan constructor - dan satu-satunya
   cara yang ia tahu adalah Mesin(), yang tidak ada.

   PERBAIKAN: sebutkan di initializer list: BagianC() : mesin_(150) {}

   Ini contoh nyata bahwa initializer list bukan sekadar optimasi.
   Untuk tiga kasus - const, referensi, dan anggota tanpa constructor
   default - ia satu-satunya cara yang mungkin.

⚠️ POLA UMUM KETIGANYA: badan constructor terlalu terlambat. Saat
   kurung kurawal pembuka dijalankan, semua anggota SUDAH terlanjur
   diinisialisasi.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══ BAGIAN A - urutan deklarasi diperbaiki ═══
class BagianA {
    int lebar_;                  // <- deklarasi diurutkan sesuai kebutuhan
    int tinggi_;
    int luas_;
public:
    BagianA(int w, int h) : lebar_(w), tinggi_(h), luas_(lebar_ * tinggi_) {}

    void cetak() const {
        cout << "A: lebar=" << lebar_ << " tinggi=" << tinggi_
             << " luas=" << luas_ << "\n";
    }
};

// ═══ BAGIAN B - pakai initializer list untuk anggota const ═══
class BagianB {
    const double PI_;
    double radius_;
public:
    BagianB(double r) : PI_(3.14159), radius_(r) {}

    void cetak() const {
        cout << "B: PI=" << PI_ << " radius=" << radius_
             << " keliling=" << 2 * PI_ * radius_ << "\n";
    }
};

// ═══ BAGIAN C - anggota tanpa constructor default ═══
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
    BagianC() : mesin_(150) {}       // WAJIB lewat initializer list

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
