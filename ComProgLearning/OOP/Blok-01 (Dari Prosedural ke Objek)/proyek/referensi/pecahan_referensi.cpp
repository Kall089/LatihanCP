/*
============================================================
✅ REFERENSI — Proyek Blok 1: Class Pecahan
============================================================
Jangan buka ini sebelum versimu sendiri jalan.

📖 KEPUTUSAN DESAIN YANG PATUT DIPERHATIKAN

1. sederhanakan() ADALAH SATU-SATUNYA PENJAGA INVARIANT
   Semua constructor memanggilnya, dan semua operasi aritmetika
   menghasilkan objek lewat constructor. Konsekuensinya: TIDAK ADA
   jalan membuat Pecahan yang tidak tersederhanakan. Bukan karena
   pemakainya disiplin, tapi karena tidak ada celahnya.

   Bandingkan dengan versi struct di teori bagian 1.4, di mana setiap
   pemanggil harus ingat memanggil sederhanakan(). Perbedaannya bukan
   soal jumlah baris kode - perbedaannya adalah kelas ini tidak bisa
   dipakai secara salah.

2. KENAPA ARITMETIKA MENGEMBALIKAN OBJEK BARU
   a.tambah(b) tidak mengubah a, sama seperti 3 + 4 tidak mengubah 3.
   Ini namanya value semantics. Kalau tambah() mengubah this, kode
   seperti ini jadi mengejutkan:

       Pecahan total = hargaA.tambah(hargaB);   // hargaA ikut berubah?!

   Aturan praktis: tipe yang berperilaku seperti BILANGAN sebaiknya
   punya value semantics. Tipe yang berperilaku seperti ENTITAS
   (Rekening, Pengguna) biasanya tidak.

3. KENAPA lebihKecil() BOLEH MENGALIKAN SILANG
   a/b < c/d  <=>  a*d < c*b  hanya benar kalau b dan d POSITIF.
   Kalau salah satu negatif, tanda pertidaksamaan harus dibalik.

   Invariant 2 (penyebut selalu positif) menjamin syarat itu, sehingga
   perbandingannya jadi satu baris tanpa percabangan.

   Ini contoh penting: invariant yang dijaga ketat di satu tempat
   MENYEDERHANAKAN kode di banyak tempat lain. Itulah keuntungan
   sesungguhnya dari enkapsulasi - bukan "menyembunyikan data", tapi
   mengurangi jumlah hal yang perlu dipikirkan di setiap fungsi.

4. long long DIPAKAI UNTUK PERHITUNGAN ANTARA
   Pada tambah(), pembilang_ * lain.penyebut_ bisa meluap int meski
   hasil akhirnya kecil. Hitung dengan long long, sederhanakan, baru
   simpan kembali ke int.

   Ini pola umum: rentang nilai ANTARA sering lebih besar daripada
   rentang nilai HASIL.

5. PEMBAGIAN DENGAN NOL: DIPILIH JADI 0/1, DAN DIDOKUMENTASIKAN
   Bukan pilihan yang bagus - hanya pilihan yang KONSISTEN, karena
   exception baru dibahas di Blok 7. Perbaikan diam-diam menyembunyikan
   bug pemanggil, dan itu memang kelemahan versi ini.
   Saat sampai Blok 7, kembalilah ke sini dan ganti dengan
   throw invalid_argument. Itu latihan yang bagus.

6. cetak() ADALAH KELEMAHAN DESAIN YANG DISENGAJA
   Mencetak langsung ke cout mengikat kelas ini ke konsol. Kelas
   Pecahan seharusnya tidak tahu apa-apa soal konsol.
   Perbaikannya operator<< (Blok 2), dan pertanyaan yang lebih dalam
   soal siapa yang bertanggung jawab memformat keluaran dibahas di
   Blok 9 (Single Responsibility).

📊 KOMPLEKSITAS: semua operasi O(log n) karena gcd. Praktis O(1).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Pecahan {
public:
    // ── Pembuatan ────────────────────────────────────────
    Pecahan() : pembilang_(0), penyebut_(1) {}

    explicit Pecahan(int bulat) : pembilang_(bulat), penyebut_(1) {}

    Pecahan(int p, int q) : pembilang_(p), penyebut_(q) {
        // Pembagian dengan nol: dipilih menjadi 0/1 agar konsisten.
        // Lihat catatan desain nomor 5 - ini akan diganti di Blok 7.
        if (penyebut_ == 0) { pembilang_ = 0; penyebut_ = 1; }
        sederhanakan();
    }

    // ── Aritmetika ───────────────────────────────────────
    Pecahan tambah(const Pecahan& lain) const {
        long long p = 1LL * pembilang_ * lain.penyebut_
                    + 1LL * lain.pembilang_ * penyebut_;
        long long q = 1LL * penyebut_ * lain.penyebut_;
        return dariLongLong(p, q);
    }

    Pecahan kurang(const Pecahan& lain) const {
        long long p = 1LL * pembilang_ * lain.penyebut_
                    - 1LL * lain.pembilang_ * penyebut_;
        long long q = 1LL * penyebut_ * lain.penyebut_;
        return dariLongLong(p, q);
    }

    Pecahan kali(const Pecahan& lain) const {
        return dariLongLong(1LL * pembilang_ * lain.pembilang_,
                            1LL * penyebut_  * lain.penyebut_);
    }

    Pecahan bagi(const Pecahan& lain) const {
        if (lain.pembilang_ == 0) return Pecahan();     // konsisten dengan di atas
        return dariLongLong(1LL * pembilang_ * lain.penyebut_,
                            1LL * penyebut_  * lain.pembilang_);
    }

    // ── Perbandingan ─────────────────────────────────────
    bool samaDengan(const Pecahan& lain) const {
        // Aman membandingkan langsung KARENA invariant 3 menjamin
        // bentuknya selalu paling sederhana, dan invariant 2 menjamin
        // tandanya selalu di pembilang. Tanpa keduanya, 2/4 dan 1/2
        // akan dianggap berbeda.
        return pembilang_ == lain.pembilang_ && penyebut_ == lain.penyebut_;
    }

    bool lebihKecil(const Pecahan& lain) const {
        // Sah tanpa percabangan karena kedua penyebut dijamin positif.
        return 1LL * pembilang_ * lain.penyebut_
             < 1LL * lain.pembilang_ * penyebut_;
    }

    // ── Query ────────────────────────────────────────────
    int    pembilang() const { return pembilang_; }
    int    penyebut()  const { return penyebut_;  }
    double keDouble()  const { return static_cast<double>(pembilang_) / penyebut_; }
    bool   negatif()   const { return pembilang_ < 0; }

    Pecahan kebalikan() const {
        if (pembilang_ == 0) return Pecahan();
        return Pecahan(penyebut_, pembilang_);
    }

    // ── Keluaran ─────────────────────────────────────────
    void cetak() const {
        if (penyebut_ == 1) cout << pembilang_ << "\n";
        else                cout << pembilang_ << "/" << penyebut_ << "\n";
    }

private:
    // Satu-satunya penjaga invariant.
    void sederhanakan() {
        if (pembilang_ == 0) { penyebut_ = 1; return; }   // kasus khusus nol
        if (penyebut_ < 0) {                              // tanda ke pembilang
            pembilang_ = -pembilang_;
            penyebut_  = -penyebut_;
        }
        int g = gcd(abs(pembilang_), penyebut_);
        pembilang_ /= g;
        penyebut_  /= g;
    }

    // Pembantu: menyederhanakan dalam long long dulu, baru kembali ke int.
    // Perhitungan antara bisa meluap int meski hasil akhirnya kecil.
    static Pecahan dariLongLong(long long p, long long q) {
        if (q == 0) return Pecahan();
        if (q < 0) { p = -p; q = -q; }
        long long g = (p == 0) ? q : gcd(llabs(p), q);
        return Pecahan(static_cast<int>(p / g), static_cast<int>(q / g));
    }

    int pembilang_;
    int penyebut_;
};

// ════════════════════════════════════════════════════════
int main() {
    cout << "=== Pembuatan ===\n";
    Pecahan a;              a.cetak();
    Pecahan b(5);           b.cetak();
    Pecahan c(3, 4);        c.cetak();
    Pecahan d(2, 4);        d.cetak();
    Pecahan e(1, -2);       e.cetak();
    Pecahan f(-1, -2);      f.cetak();
    Pecahan g(0, 5);        g.cetak();

    cout << "\n=== Aritmetika ===\n";
    Pecahan x(3, 4), y(1, 2);
    cout << "3/4 + 1/2 = "; x.tambah(y).cetak();
    cout << "3/4 - 1/2 = "; x.kurang(y).cetak();
    cout << "3/4 * 1/2 = "; x.kali(y).cetak();
    cout << "3/4 : 1/2 = "; x.bagi(y).cetak();

    cout << "\n=== Perbandingan ===\n";
    cout << "1/2 == 2/4 ? " << (Pecahan(1,2).samaDengan(Pecahan(2,4)) ? "ya" : "tidak") << "\n";
    cout << "1/2 < 2/3 ? "  << (Pecahan(1,2).lebihKecil(Pecahan(2,3)) ? "ya" : "tidak") << "\n";
    cout << "2/3 < 1/2 ? "  << (Pecahan(2,3).lebihKecil(Pecahan(1,2)) ? "ya" : "tidak") << "\n";

    cout << "\n=== Query ===\n";
    cout << "3/4 sebagai desimal = " << x.keDouble() << "\n";
    cout << "-1/2 negatif? " << (e.negatif() ? "ya" : "tidak") << "\n";
    cout << "kebalikan 3/4 = "; x.kebalikan().cetak();

    cout << "\n=== Penyederhanaan otomatis ===\n";
    cout << "6/8 = ";    Pecahan(6, 8).cetak();
    cout << "100/25 = "; Pecahan(100, 25).cetak();
    cout << "1/2 + 1/2 = "; Pecahan(1,2).tambah(Pecahan(1,2)).cetak();

    return 0;
}
