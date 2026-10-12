/*
============================================================
🏋️ Latihan 1: Dari struct ke class
============================================================
Blok: 1 | Tingkat: Mudah | Estimasi: 15 menit
Topik: access specifier, member function

📋 TUGAS:
Di bawah ada kode PROSEDURAL yang bekerja dengan titik 2 dimensi.
Ubah menjadi class dengan aturan:

  1. data x dan y harus PRIVATE (pakai akhiran _ : x_, y_)
  2. sediakan member function:
       - geser(dx, dy)   menggeser titik
       - jarakKeAsal()   mengembalikan jarak ke titik (0,0)
       - cetak()         mencetak dengan format (x, y)
  3. sediakan cara membaca x dan y dari luar

❓ PERTANYAAN SEBELUM KODING (jawab di komentar):
   Kenapa membuat x_ dan y_ private itu berguna di sini, padahal
   titik 2D sebenarnya TIDAK punya invariant yang perlu dijaga?
   (Petunjuk: baca teori bagian 1.5 dan 1.7. Jawaban yang jujur
    mungkin "tidak terlalu berguna" - dan itu jawaban yang benar.)

📤 KELUARAN YANG DIHARAPKAN:
(3, 4)
5
(5, 7)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ─── KODE PROSEDURAL YANG HARUS DIUBAH ───────────────────
struct Titik
{
    double x;
    double y;
};

void geser(Titik &t, double dx, double dy)
{
    t.x += dx;
    t.y += dy;
}

double jarakKeAsal(const Titik &t)
{
    return sqrt(t.x * t.x + t.y * t.y);
}

void cetak(const Titik &t)
{
    cout << "(" << t.x << ", " << t.y << ")\n";
}

// TODO: tulis class Titik2D di sini

int main()
{
    // TODO: ganti kode di bawah supaya memakai class Titik2D

    Titik t{3, 4};
    cetak(t);                       // (3, 4)
    cout << jarakKeAsal(t) << "\n"; // 5
    geser(t, 2, 3);
    cetak(t); // (5, 7)

    return 0;
}
