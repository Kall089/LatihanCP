/*
============================================================
✅ Solusi 7: Class dengan Invariant Nyata
============================================================
🎯 Yang dilatih: seluruh Blok 1

📖 JAWABAN PERTANYAAN DESAIN

1. KENAPA tambah() MENGEMBALIKAN bool, BUKAN void?

   Karena operasinya BISA GAGAL, dan pemanggil perlu tahu.

   Kalau void, pemanggil tidak punya cara membedakan "berhasil menambah
   90" dari "tidak menambah apa-apa". Ia harus mengecek stok sebelum
   dan sesudah - dan kalau lupa, bugnya diam.

   Ada tiga pilihan umum untuk operasi yang bisa gagal:
     bool          sederhana, tapi mudah diabaikan pemanggil
     exception     tidak bisa diabaikan, tapi berat untuk kegagalan
                   yang wajar terjadi (Blok 7)
     std::optional / std::expected   modern, informatif (Blok 7)

   Untuk kegagalan yang WAJAR dan SERING (gudang penuh itu normal,
   bukan luar biasa), bool sudah tepat. Exception sebaiknya untuk hal
   yang benar-benar tidak diharapkan.

2. KENAPA "TIDAK MENAMBAH SAMA SEKALI" LEBIH BAIK?

   Ini namanya operasi ATOMIK: berhasil seluruhnya, atau tidak terjadi
   sama sekali. Keunggulannya, saat operasi gagal, objek tetap berada
   di keadaan yang pemanggil pahami - keadaan sebelum pemanggilan.

   Kalau tambah(90) menambah 70 saja (sebanyak yang muat), pemanggil
   yang tidak mengecek nilai kembalian akan mengira 90 masuk semua.
   Kesalahan seperti ini menyebar diam-diam.

   KAPAN JUSTRU SEBALIKNYA YANG LEBIH BAIK?
   Kalau domainnya memang parsial. Contoh: mengisi tangki bensin -
   "isi penuh" wajar berarti "isi sebanyak yang muat". Atau menulis
   ke buffer jaringan yang memang mengembalikan berapa byte terkirim.

   Kuncinya: kalau kamu memilih parsial, WAJIB kembalikan BERAPA
   BANYAK yang berhasil, bukan sekadar bool. int tambahSebisanya(int n)
   yang mengembalikan jumlah yang benar-benar masuk.

3. KENAPA TIDAK ADA setStok(int)?

   Karena setStok akan MEMBUKA JALAN MELANGGAR INVARIANT, atau kalau
   divalidasi, ia sekadar menduplikasi tambah/ambil dengan bentuk yang
   lebih rawan.

   Lebih dalam lagi: setStok memaksa pemanggil berpikir dalam
   "keadaan akhir" padahal domainnya berpikir dalam "kejadian".
   Di gudang nyata, yang terjadi adalah barang MASUK dan KELUAR -
   bukan "stok tiba-tiba menjadi 47". Antarmuka yang mengikuti bahasa
   domainnya lebih sulit disalahgunakan.

   Ini contoh konkret bahwa enkapsulasi bukan soal private + getter +
   setter. Kalau kamu menambahkan setter untuk setiap anggota, kamu
   sudah membuat struct dengan langkah tambahan.

📖 KENAPA kapasitas_ const
   Kapasitas gudang tidak berubah seumur hidup objek. Menyatakannya
   const membuat kompilator menegakkannya, dan memaksa inisialisasinya
   lewat initializer list. Efek sampingnya: kelas ini tidak bisa
   di-assign (operator= otomatis hilang) - dan itu wajar untuk kelas ini.

📖 PENANGANAN NILAI TIDAK VALID DI CONSTRUCTOR
   Solusi ini MEMPERBAIKI diam-diam (kapasitas <= 0 jadi 1, nama kosong
   jadi "tanpa-nama", stok awal dipotong ke rentang sah).

   Itu keputusan yang bisa diperdebatkan. Alternatif yang sering lebih
   baik: LEMPAR EXCEPTION. Membuat Persediaan dengan kapasitas -5
   hampir pasti bug di pemanggil, dan memperbaikinya diam-diam
   menyembunyikan bug itu.

   Kita pakai perbaikan diam-diam di sini hanya karena exception baru
   dibahas di Blok 7. Saat sampai ke sana, kembalilah ke kelas ini dan
   ubah - itu latihan yang bagus.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Persediaan {
public:
    Persediaan(const string& nama, int kapasitas)
        : nama_(nama.empty() ? "tanpa-nama" : nama),
          kapasitas_(kapasitas > 0 ? kapasitas : 1),
          stok_(0) {}

    Persediaan(const string& nama, int kapasitas, int stokAwal)
        : nama_(nama.empty() ? "tanpa-nama" : nama),
          kapasitas_(kapasitas > 0 ? kapasitas : 1),
          stok_(0) {
        // dipotong ke rentang sah; kapasitas_ sudah pasti valid di sini
        if (stokAwal > 0) stok_ = min(stokAwal, kapasitas_);
    }

    bool tambah(int n) {
        if (n < 0) return false;
        if (stok_ + n > kapasitas_) return false;   // atomik: gagal = tidak berubah
        stok_ += n;
        return true;
    }

    bool ambil(int n) {
        if (n < 0) return false;
        if (n > stok_) return false;                // atomik
        stok_ -= n;
        return true;
    }

    int  stok()       const { return stok_; }
    int  kapasitas()  const { return kapasitas_; }
    int  sisaRuang()  const { return kapasitas_ - stok_; }
    bool penuh()      const { return stok_ == kapasitas_; }
    bool kosong()     const { return stok_ == 0; }

    void cetak() const {
        cout << nama_ << ": " << stok_ << "/" << kapasitas_ << "\n";
    }

private:
    string    nama_;
    const int kapasitas_;      // tidak berubah seumur hidup objek
    int       stok_;
};

int main() {
    Persediaan beras("beras", 100);
    beras.cetak();

    beras.tambah(30);
    beras.cetak();

    if (!beras.tambah(90)) cout << "gagal: melebihi kapasitas\n";
    beras.cetak();

    beras.ambil(20);
    beras.cetak();

    if (!beras.ambil(50)) cout << "gagal: stok tidak cukup\n";
    beras.cetak();

    cout << "sisa ruang: " << beras.sisaRuang() << "\n";
    cout << "penuh? " << (beras.penuh() ? "ya" : "tidak") << "\n";

    Persediaan gula("gula", 50, 50);
    gula.cetak();
    cout << "penuh? " << (gula.penuh() ? "ya" : "tidak") << "\n";
    return 0;
}
