/*
============================================================
✅ Solusi 5: const Correctness
============================================================
🎯 Yang dilatih: const member function

📖 YANG TIDAK BOLEH const: setor()
   Ia mengubah saldo_. Memberi const padanya tidak akan dikompilasi -
   dan itu bagus. Kompilator menegakkan janjimu, bukan mengandalkan
   ingatanmu.

📖 DUA ALASAN MEMAKAI const& SEBAGAI PARAMETER:

   1. MENGHINDARI PENYALINAN. Tanpa &, setiap pemanggilan menyalin
      seluruh objek termasuk string pemilik_. Untuk objek besar ini
      mahal, dan biayanya tersembunyi - tidak ada yang tampak salah
      di kode.

   2. MENYATAKAN NIAT DAN MENEGAKKANNYA. const memberitahu pembaca
      "fungsi ini tidak akan mengubah argumenmu", dan kompilator
      memastikannya. Tanpa const, pembaca harus membaca seluruh badan
      fungsi untuk tahu apakah objeknya aman.

   Ada alasan ketiga yang lebih halus: tanpa const, fungsi ini tidak
   bisa menerima objek temporer maupun objek const. Ini membatasi
   pemakaian dengan cara yang baru terasa jauh di kemudian hari.

📖 KENAPA pemilik() MENGEMBALIKAN const string& DAN BUKAN string

   Versi soal mengembalikan string per nilai - itu menyalin seluruh
   nama setiap kali dipanggil. Untuk getter yang sering dipanggil,
   kembalikan const& saja.

   TAPI HATI-HATI: mengembalikan referensi ke anggota berarti pemakai
   memegang rujukan ke isi objekmu. Kalau objeknya mati sementara
   rujukan itu masih dipakai, kamu punya dangling reference. Untuk
   getter sederhana ini aman; untuk kasus rumit, kembalikan per nilai.

   Trade-off seperti ini akan berulang sepanjang C++. Tidak ada aturan
   yang benar untuk semua kasus - yang ada hanya kesadaran akan biayanya.

📖 CATATAN DESAIN YANG LEBIH BESAR
   Class ini punya getter untuk hampir semua anggotanya. Apakah itu
   baik? Belum tentu - untuk kelas ini masih wajar karena laporan
   memang butuh membaca nilainya. Tapi pertanyaan "kapan getter justru
   merusak enkapsulasi" adalah materi Blok 2, dan jawabannya mungkin
   akan mengubah cara pandangmu terhadap kelas ini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Rekening {
public:
    Rekening(const string& pemilik, long long saldoAwal)
        : pemilik_(pemilik), saldo_(saldoAwal) {}

    const string& pemilik() const { return pemilik_; }   // const& hemat salinan
    long long saldo()       const { return saldo_; }
    bool aktif()            const { return saldo_ >= 0; }

    void setor(long long jumlah) { saldo_ += jumlah; }   // TIDAK const - mengubah

private:
    string pemilik_;
    long long saldo_;
};

void cetakLaporan(const Rekening& r) {
    cout << "=== Laporan ===\n";
    cout << "Pemilik : " << r.pemilik() << "\n";
    cout << "Saldo   : " << r.saldo()   << "\n";
    cout << "Status  : " << (r.aktif() ? "aktif" : "diblokir") << "\n";
}

int main() {
    Rekening r("Kall", 500000);
    cetakLaporan(r);

    r.setor(250000);
    cout << "Setelah setor 250000:\n";
    cout << "Saldo   : " << r.saldo() << "\n";
    return 0;
}
