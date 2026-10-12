/*
============================================================
✅ Solusi 1: Dari struct ke class
============================================================
🎯 Yang dilatih: access specifier, member function, const

📖 KEPUTUSAN DESAIN:

1. Kenapa geser() TIDAK const, tapi jarakKeAsal() const?
   geser mengubah objek, jarakKeAsal tidak. Aturannya sesederhana itu -
   tapi konsekuensinya besar: tanpa const pada jarakKeAsal, kamu tidak
   bisa memanggilnya pada objek const.

2. Kenapa parameter cetak() hilang?
   Di versi prosedural, cetak(t) butuh tahu titik mana. Di versi class,
   informasi itu datang lewat this. Perhatikan bahwa jumlah parameter
   berkurang satu di SEMUA fungsi - itu bukan kebetulan, itu inti
   perubahan dari prosedural ke objek.

3. Jawaban pertanyaan "kenapa private padahal tidak ada invariant?"
   JAWABAN JUJUR: untuk Titik2D sederhana, private memang tidak banyak
   membantu. Titik 2D adalah kumpulan data murni tanpa aturan - dan
   untuk kasus seperti ini, struct dengan anggota public JUSTRU pilihan
   yang lebih baik dan lebih jujur.

   Ini bukan jebakan. Ini pelajaran nyata: jangan membuat sesuatu private
   hanya karena "katanya OOP begitu". Buat private kalau ada yang perlu
   dijaga. std::pair dan banyak tipe di pustaka standar anggotanya public,
   dan itu keputusan yang benar.

   Kapan private jadi berguna di sini? Kalau nanti kamu mau mengganti
   representasi internal ke koordinat polar (r, theta) tanpa membongkar
   pemakainya. Itu alasan yang sah - tapi baru berlaku kalau kebutuhan
   itu memang ada.

⚠️ Perhatikan: solusi ini memakai akhiran _ untuk data anggota. Konvensi
   lain yang juga umum: m_x. Pilih satu, lalu konsisten seumur proyek.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Titik2D {
public:
    Titik2D(double x, double y) : x_(x), y_(y) {}

    void geser(double dx, double dy) {     // mengubah -> TIDAK const
        x_ += dx;
        y_ += dy;
    }

    double jarakKeAsal() const {           // tidak mengubah -> const
        return sqrt(x_ * x_ + y_ * y_);
    }

    void cetak() const {
        cout << "(" << x_ << ", " << y_ << ")\n";
    }

    double x() const { return x_; }
    double y() const { return y_; }

private:
    double x_;
    double y_;
};

int main() {
    Titik2D t(3, 4);
    t.cetak();                        // (3, 4)
    cout << t.jarakKeAsal() << "\n";  // 5
    t.geser(2, 3);
    t.cetak();                        // (5, 7)
    return 0;
}
