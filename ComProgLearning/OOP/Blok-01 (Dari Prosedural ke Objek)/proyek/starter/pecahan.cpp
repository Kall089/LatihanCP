/*
============================================================
🛠 PROYEK BLOK 1 — Class Pecahan
============================================================
Baca proyek/SPESIFIKASI.md sebelum mulai.

INVARIANT yang harus SELALU terjaga:
  1. penyebut_ != 0
  2. penyebut_ > 0            (tanda dibawa pembilang)
  3. FPB(|pembilang_|, penyebut_) == 1

Kompilasi:
  g++ -std=c++17 -Wall -Wextra -o pecahan pecahan.cpp && ./pecahan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Pecahan {
public:
    // ── Pembuatan ────────────────────────────────────────
    // TODO: Pecahan()                       -> 0/1
    // TODO: explicit Pecahan(int bulat)     -> bulat/1
    // TODO: Pecahan(int p, int q)           -> disederhanakan otomatis

    // ── Aritmetika ───────────────────────────────────────
    // Semua mengembalikan objek BARU dan TIDAK mengubah this.
    // TODO: Pecahan tambah(const Pecahan& lain) const;
    // TODO: Pecahan kurang(const Pecahan& lain) const;
    // TODO: Pecahan kali  (const Pecahan& lain) const;
    // TODO: Pecahan bagi  (const Pecahan& lain) const;

    // ── Perbandingan ─────────────────────────────────────
    // TODO: bool samaDengan (const Pecahan& lain) const;
    // TODO: bool lebihKecil (const Pecahan& lain) const;
    //   Hati-hati: a/b < c/d  <=>  a*d < c*b  HANYA aman kalau b dan d
    //   dijamin positif. Untunglah invariant 2 menjaminnya. Perhatikan
    //   bagaimana invariant menyederhanakan kode di tempat lain.

    // ── Query ────────────────────────────────────────────
    // TODO: int     pembilang() const;
    // TODO: int     penyebut()  const;
    // TODO: double  keDouble()  const;
    // TODO: bool    negatif()   const;
    // TODO: Pecahan kebalikan() const;

    // ── Keluaran ─────────────────────────────────────────
    // TODO: void cetak() const;   "3/4", tapi "5" kalau penyebutnya 1

private:
    // TODO: void sederhanakan();
    //   SATU-SATUNYA tempat yang menjaga invariant.
    //   Langkah: (a) tangani kasus pembilang == 0
    //            (b) pindahkan tanda ke pembilang
    //            (c) bagi keduanya dengan FPB
    //   Petunjuk: std::gcd ada di <numeric> (C++17), atau tulis sendiri.
    //             Pakai abs() saat menghitung FPB.

    int pembilang_ = 0;
    int penyebut_  = 1;
};

// ════════════════════════════════════════════════════════
//  PROGRAM UJI — jangan diubah
// ════════════════════════════════════════════════════════
int main() {
    cout << "=== Pembuatan ===\n";
    Pecahan a;              a.cetak();          // 0
    Pecahan b(5);           b.cetak();          // 5
    Pecahan c(3, 4);        c.cetak();          // 3/4
    Pecahan d(2, 4);        d.cetak();          // 1/2
    Pecahan e(1, -2);       e.cetak();          // -1/2
    Pecahan f(-1, -2);      f.cetak();          // 1/2
    Pecahan g(0, 5);        g.cetak();          // 0

    cout << "\n=== Aritmetika ===\n";
    Pecahan x(3, 4), y(1, 2);
    cout << "3/4 + 1/2 = "; x.tambah(y).cetak();     // 5/4
    cout << "3/4 - 1/2 = "; x.kurang(y).cetak();     // 1/4
    cout << "3/4 * 1/2 = "; x.kali(y).cetak();       // 3/8
    cout << "3/4 : 1/2 = "; x.bagi(y).cetak();       // 3/2

    cout << "\n=== Perbandingan ===\n";
    cout << "1/2 == 2/4 ? " << (Pecahan(1,2).samaDengan(Pecahan(2,4)) ? "ya" : "tidak") << "\n";
    cout << "1/2 < 2/3 ? "  << (Pecahan(1,2).lebihKecil(Pecahan(2,3)) ? "ya" : "tidak") << "\n";
    cout << "2/3 < 1/2 ? "  << (Pecahan(2,3).lebihKecil(Pecahan(1,2)) ? "ya" : "tidak") << "\n";

    cout << "\n=== Query ===\n";
    cout << "3/4 sebagai desimal = " << x.keDouble() << "\n";
    cout << "-1/2 negatif? " << (e.negatif() ? "ya" : "tidak") << "\n";
    cout << "kebalikan 3/4 = "; x.kebalikan().cetak();

    cout << "\n=== Penyederhanaan otomatis ===\n";
    cout << "6/8 = ";    Pecahan(6, 8).cetak();      // 3/4
    cout << "100/25 = "; Pecahan(100, 25).cetak();   // 4
    cout << "1/2 + 1/2 = "; Pecahan(1,2).tambah(Pecahan(1,2)).cetak();  // 1

    return 0;
}
