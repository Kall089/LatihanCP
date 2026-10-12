/*
============================================================
🏋️ Latihan 3: Tebak Keluaran (Siklus Hidup)
============================================================
Blok: 1 | Tingkat: Mudah | Estimasi: 15 menit
Topik: constructor, destructor, urutan

📋 TUGAS:
JANGAN dijalankan dulu. Tulis dulu tebakanmu tentang keluaran program
ini di komentar bagian bawah, baru compile dan bandingkan.

Latihan ini melatih kemampuan yang tidak bisa dilatih dengan menulis kode:
memprediksi kapan objek lahir dan mati.

❓ Setelah membandingkan, jawab:
   1. Kenapa urutan matinya terbalik dari urutan lahirnya?
   2. Kenapa "objek dalam if" mati sebelum "selesai" tercetak?
   3. Apa yang terjadi kalau baris `Jejak d("d");` dipindah ke dalam
      blok if? Coba pikirkan dulu, baru coba.

📤 KELUARAN: tulis tebakanmu di bagian bawah file, lalu jalankan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Jejak {
public:
    Jejak(const string& nama) : nama_(nama) {
        cout << "lahir  : " << nama_ << "\n";
    }
    ~Jejak() {
        cout << "mati   : " << nama_ << "\n";
    }
private:
    string nama_;
};

Jejak global("global");

void fungsi() {
    Jejak f("dalam fungsi");
    cout << "  ...isi fungsi...\n";
}

int main() {
    cout << "=== main mulai ===\n";

    Jejak a("a");
    Jejak b("b");

    if (true) {
        Jejak c("dalam if");
        cout << "  ...isi if...\n";
    }

    fungsi();

    Jejak d("d");
    cout << "=== main selesai ===\n";
    return 0;
}

/*
TEBAKANKU (isi SEBELUM menjalankan):




KELUARAN SEBENARNYA (isi SETELAH menjalankan):




YANG SALAH TEBAK DAN KENAPA:


*/
