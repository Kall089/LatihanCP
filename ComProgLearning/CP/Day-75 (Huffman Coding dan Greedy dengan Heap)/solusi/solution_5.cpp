/*
============================================================
✅ SOLUSI Exercise 5: Membagi Tugas ke Mesin
============================================================
Difficulty: Hard | Kompleksitas: O(n log m) waktu, O(m) memori

── SIMULASI, BUKAN PENEMUAN ────────────────────────────────
Perbedaan penting dari soal-soal sebelumnya: aturannya SUDAH
DIBERIKAN oleh soal. Kamu tidak perlu membuktikan greedy apa
pun — tugasmu hanya menyimulasikannya dengan efisien.

Membedakan dua jenis soal ini menghemat banyak waktu di kontes.
Kalau soal berkata "berikan kepada mesin yang paling cepat
menganggur", jangan menghabiskan lima menit membuktikan bahwa
aturan itu optimal. Ia mungkin memang tidak optimal — tetapi
itu bukan urusanmu.

── KENAPA SIMULASI NAIF TERLALU LAMBAT ─────────────────────
Memeriksa seluruh m mesin untuk setiap tugas menghasilkan
n * m = 4 * 10^10 operasi pada batasan terburuk.
Yang kita butuhkan hanyalah MINIMUM dari waktu bebas, dan
minimum itu berubah setiap langkah. Itu definisi min-heap.

── ISI HEAP ────────────────────────────────────────────────
Heap menyimpan WAKTU BEBAS tiap mesin, bukan nomor mesinnya.
Untuk soal ini nomor mesin tidak perlu dilacak karena yang
ditanya hanya waktu selesai terakhir.
(Kalau soal minta jadwal lengkap, simpan pasangan
(waktu bebas, nomor mesin) — heap akan otomatis memecah seri
menurut nomor terkecil.)

── MESIN LEBIH BANYAK DARI TUGAS ───────────────────────────
Kalau m > n, mesin selebihnya tidak akan pernah dipakai.
Mengalokasikan heap berukuran min(n, m) menghemat memori dan
tidak mengubah hasil: mesin yang tak terpakai punya waktu bebas
0, dan itu tidak memengaruhi maksimum.
Sampel 2 menguji kasus ini.

── MELACAK JAWABAN ─────────────────────────────────────────
Waktu selesai terakhir adalah maksimum dari seluruh waktu
selesai yang pernah terjadi. Karena setiap tugas hanya menambah
waktu bebas sebuah mesin, cukup ambil maksimum berjalan saat
mendorong kembali ke heap.
Alternatif: setelah semua tugas selesai, ambil nilai terbesar di
dalam heap. Keduanya benar; maksimum berjalan lebih sederhana.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai max-heap. Kamu butuh mesin yang paling CEPAT
   menganggur, jadi min-heap.
2. Mengalokasikan heap berukuran m ketika m sangat besar.
3. Lupa long long: n = 2*10^5 dan t = 10^9 -> sampai 2*10^14.
4. Menyangka soal ini meminta makespan OPTIMAL. Bukan — soal
   meminta hasil dari aturan yang sudah ditentukan. Makespan
   optimal dengan tugas boleh diurutkan ulang adalah masalah
   NP-hard.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<ll> t(n);
    for (ll& x : t) cin >> x;

    // mesin selebihnya tidak akan pernah dipakai
    int mesin = min(n, m);
    priority_queue<ll, vector<ll>, greater<ll>> pq;   // waktu bebas, MIN-heap
    for (int i = 0; i < mesin; i++) pq.push(0);

    ll jawab = 0;
    for (ll x : t) {
        ll bebas = pq.top(); pq.pop();
        bebas += x;                                   // mesin ini selesai di sini
        jawab = max(jawab, bebas);
        pq.push(bebas);
    }

    cout << jawab << '\n';
    return 0;
}
