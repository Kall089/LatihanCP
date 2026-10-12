/*
============================================================
✅ Solusi 2: Constructor yang Menjaga Invariant
============================================================
🎯 Yang dilatih: constructor, invariant, satu tempat penjagaan

📖 KEPUTUSAN DESAIN:

1. KENAPA NORMALISASI DILAKUKAN LEWAT TOTAL DETIK
   Cara naif: perbaiki detik dulu, lalu menit, lalu jam - dengan tiga
   blok if yang saling bergantung. Itu bisa benar, tapi rapuh: setiap
   kali kamu menambah operasi baru (kurangDetik, tambahJam), kamu harus
   menulis ulang logika normalisasi yang sama.

   Cara yang dipakai di sini: ubah ke satu bilangan (total detik),
   normalkan sekali, pecah lagi. Semua operasi lain tinggal memanggilnya.
   Ada SATU tempat yang menjaga invariant, dan itu tujuan enkapsulasi.

2. KENAPA setDari(totalDetik) DIBUAT private
   Fungsi itu alat internal, bukan bagian dari antarmuka yang berguna
   bagi pemakai. Kalau dibuat public, pemakai bisa memberikan nilai
   yang mengandalkan detail implementasi kita - dan kita jadi tidak
   bebas mengubahnya nanti.

3. KENAPA MEMBUNGKUS (modulo), BUKAN MEMOTONG (clamp)
   Waktu itu siklis: 25:00 memang wajar berarti 01:00 hari berikutnya.
   Kalau ini kelas Persentase, memotong ke 100 justru yang benar.
   Pilihan ini bergantung DOMAIN, bukan aturan umum - dan keputusan
   seperti ini layak ditulis di komentar kelas.

⚠️ ((x % N) + N) % N dipakai supaya nilai negatif tetap menghasilkan
   sisa non-negatif. Di C++, (-1) % 24 menghasilkan -1, bukan 23.
   Kamu sudah bertemu jebakan yang sama di folder CP.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Waktu {
public:
    Waktu() : jam_(0), menit_(0), detik_(0) {}

    Waktu(int j, int m, int d) {
        setDari(j * 3600LL + m * 60LL + d);
    }

    void tambahDetik(long long n) {
        setDari(totalDetik() + n);
    }

    void cetak() const {
        cout << setw(2) << setfill('0') << jam_   << ":"
             << setw(2) << setfill('0') << menit_ << ":"
             << setw(2) << setfill('0') << detik_ << "\n";
    }

    int jam()   const { return jam_; }
    int menit() const { return menit_; }
    int detik() const { return detik_; }

    long long totalDetik() const {
        return jam_ * 3600LL + menit_ * 60LL + detik_;
    }

private:
    // SATU-SATUNYA tempat yang menjaga invariant.
    void setDari(long long total) {
        const long long SEHARI = 24LL * 3600LL;
        total = ((total % SEHARI) + SEHARI) % SEHARI;   // aman untuk negatif
        jam_   = static_cast<int>(total / 3600);
        menit_ = static_cast<int>((total % 3600) / 60);
        detik_ = static_cast<int>(total % 60);
    }

    int jam_;
    int menit_;
    int detik_;
};

int main() {
    Waktu a;              a.cetak();      // 00:00:00
    Waktu b(13, 45, 30);  b.cetak();      // 13:45:30
    Waktu c(1, 70, 0);    c.cetak();      // 02:10:00
    Waktu d(25, 0, 0);    d.cetak();      // 01:00:00

    Waktu e(0, 0, 59);    e.cetak();      // 00:00:59
    e.tambahDetik(1);     e.cetak();      // 00:01:00
    return 0;
}
