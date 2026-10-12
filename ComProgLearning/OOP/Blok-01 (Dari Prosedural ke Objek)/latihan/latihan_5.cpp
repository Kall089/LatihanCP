/*
============================================================
🏋️ Latihan 5: const Correctness
============================================================
Blok: 1 | Tingkat: Sedang | Estimasi: 20 menit
Topik: const member function

📋 TUGAS:
Class Rekening di bawah TIDAK const-correct. Akibatnya fungsi
cetakLaporan() di bagian bawah tidak bisa dikompilasi.

  1. Perbaiki class-nya - beri const pada setiap member function
     yang memang tidak mengubah objek
  2. JANGAN mengubah tanda tangan cetakLaporan(). Justru fungsi itu
     yang menunjukkan cara normal melewatkan objek: const&
  3. Ada SATU member function yang TIDAK boleh diberi const.
     Yang mana, dan kenapa?

❓ PERTANYAAN:
   Kenapa cetakLaporan menerima const Rekening& dan bukan Rekening?
   Sebutkan DUA alasan.

📤 KELUARAN YANG DIHARAPKAN:
=== Laporan ===
Pemilik : Kall
Saldo   : 500000
Status  : aktif
Setelah setor 250000:
Saldo   : 750000
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Rekening {
public:
    Rekening(const string& pemilik, long long saldoAwal)
        : pemilik_(pemilik), saldo_(saldoAwal) {}

    // TODO: mana saja yang harus const?
    string pemilik()  { return pemilik_; }
    long long saldo() { return saldo_; }
    bool aktif()      { return saldo_ >= 0; }

    void setor(long long jumlah) { saldo_ += jumlah; }

private:
    string pemilik_;
    long long saldo_;
};

// JANGAN UBAH fungsi ini - justru ini yang benar
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

/*
YANG TIDAK BOLEH const, DAN KENAPA:

DUA ALASAN MEMAKAI const& SEBAGAI PARAMETER:
  1.
  2.
*/
