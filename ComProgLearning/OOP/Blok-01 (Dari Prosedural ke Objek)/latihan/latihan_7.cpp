/*
============================================================
🏋️ Latihan 7: Gabungan - Class dengan Invariant Nyata
============================================================
Blok: 1 | Tingkat: Sulit | Estimasi: 35 menit
Topik: seluruh Blok 1

📋 TUGAS:
Buat class Persediaan yang mencatat stok barang di gudang.

INVARIANT (harus SELALU benar, tanpa kecuali):
  - stok >= 0                    tidak boleh minus
  - stok <= kapasitas            tidak boleh melebihi kapasitas
  - kapasitas > 0                kapasitas tidak berubah seumur hidup objek
  - nama tidak boleh string kosong

ANTARMUKA:
  Persediaan(nama, kapasitas)              stok awal 0
  Persediaan(nama, kapasitas, stokAwal)

  bool tambah(int n)      menambah n barang. Kalau melebihi kapasitas,
                          TIDAK menambah sama sekali dan mengembalikan false
  bool ambil(int n)       mengambil n barang. Kalau stok tidak cukup,
                          TIDAK mengambil sama sekali dan mengembalikan false
  int  stok() const
  int  kapasitas() const
  int  sisaRuang() const
  bool penuh() const
  bool kosong() const
  void cetak() const      format: "beras: 30/100"

ATURAN TAMBAHAN:
  - kapasitas_ harus const (tidak berubah seumur hidup objek)
  - constructor yang menerima nilai tidak valid: perbaiki dengan cara
    yang MASUK AKAL, dan tulis alasannya di komentar
  - semua fungsi yang tidak mengubah objek WAJIB const

❓ PERTANYAAN DESAIN (jawab di komentar, ini bagian terpenting):
   1. Kenapa tambah() mengembalikan bool, bukan void?
   2. Kenapa "tidak menambah sama sekali" lebih baik daripada
      "menambah sebanyak yang muat"? Dalam situasi apa justru
      sebaliknya yang lebih baik?
   3. Class ini TIDAK punya setStok(int). Kenapa itu keputusan yang benar?

📤 KELUARAN YANG DIHARAPKAN:
beras: 0/100
beras: 30/100
gagal: melebihi kapasitas
beras: 30/100
beras: 10/100
gagal: stok tidak cukup
beras: 10/100
sisa ruang: 90
penuh? tidak
gula: 50/50
penuh? ya
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// TODO: tulis class Persediaan di sini

int main() {
    // TODO: hidupkan setelah class selesai
    /*
    Persediaan beras("beras", 100);
    beras.cetak();                          // beras: 0/100

    beras.tambah(30);
    beras.cetak();                          // beras: 30/100

    if (!beras.tambah(90)) cout << "gagal: melebihi kapasitas\n";
    beras.cetak();                          // beras: 30/100  <- tidak berubah

    beras.ambil(20);
    beras.cetak();                          // beras: 10/100

    if (!beras.ambil(50)) cout << "gagal: stok tidak cukup\n";
    beras.cetak();                          // beras: 10/100  <- tidak berubah

    cout << "sisa ruang: " << beras.sisaRuang() << "\n";
    cout << "penuh? " << (beras.penuh() ? "ya" : "tidak") << "\n";

    Persediaan gula("gula", 50, 50);
    gula.cetak();                           // gula: 50/50
    cout << "penuh? " << (gula.penuh() ? "ya" : "tidak") << "\n";
    */

    return 0;
}

/*
JAWABAN PERTANYAAN DESAIN:
  1.
  2.
  3.
*/
