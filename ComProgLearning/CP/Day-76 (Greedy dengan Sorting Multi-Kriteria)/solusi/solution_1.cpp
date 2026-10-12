/*
============================================================
✅ SOLUSI Exercise 1: Peringkat Siswa
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── BENTUK KOMPARATOR YANG BENAR ────────────────────────────
Setiap lapis memeriksa KETIDAKSAMAAN lebih dulu:

    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.idx < y.idx;

Bentuk yang SALAH dan sering ditulis:

    if (x.a < y.a) return true;
    if (x.b < y.b) return true;    // dijalankan meski x.a > y.a !
    return false;

Versi salah bisa mengembalikan true untuk cmp(x,y) DAN cmp(y,x)
sekaligus — melanggar asimetri, dan std::sort boleh berperilaku
tak terduga (termasuk membaca di luar batas).

── KENAPA BATASAN NILAI KECIL ITU PETUNJUK ─────────────────
Nilai paling besar 100 dan usia paling besar 100, sementara n
sampai 2*10^5. Artinya nilai yang SAMA pasti sering muncul,
dan lapis kedua serta ketiga benar-benar diuji.
Batasan sempit pada nilai hampir selalu berarti "soal ini
tentang tie-break".

── LAPIS KETIGA MEMBUATNYA URUTAN TOTAL ────────────────────
Karena nomor pendaftaran unik, komparator ini tidak pernah
menganggap dua elemen "sama". Akibatnya:
  - hasilnya deterministik, tidak bergantung implementasi
  - std::sort dan std::stable_sort memberi hasil identik
  - seluruh kelas bug seri lenyap sekaligus

Ini lebih baik daripada mengandalkan stable_sort, karena
niatnya tertulis eksplisit di dalam kode.

── MENGUJI KOMPARATOR SENDIRI ──────────────────────────────
Pemeriksa tercepat: panggil cmp(x, x). Kalau hasilnya true,
komparatormu melanggar irrefleksivitas.
Untuk pemeriksaan menyeluruh, kompilasi dengan
    g++ -D_GLIBCXX_DEBUG
Pustaka standar akan memeriksa strict weak ordering saat
runtime dan memberi tahu kalau dilanggar.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai <= di dalam komparator.
2. Lupa memeriksa ketidaksamaan di tiap lapis.
3. Menyimpan indeks 0-based lalu lupa menambah 1 saat mencetak.
4. Lupa fast I/O pada n = 2*10^5.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Siswa { int nilai, usia, idx; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<Siswa> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i].nilai >> s[i].usia;
        s[i].idx = i + 1;                       // nomor pendaftaran 1-based
    }

    sort(s.begin(), s.end(), [](const Siswa& x, const Siswa& y) {
        if (x.nilai != y.nilai) return x.nilai > y.nilai;   // nilai MENURUN
        if (x.usia  != y.usia)  return x.usia  < y.usia;    // usia MENAIK
        return x.idx < y.idx;                               // urutan asli
    });

    for (int i = 0; i < n; i++) cout << s[i].idx << " \n"[i == n - 1];
    return 0;
}
