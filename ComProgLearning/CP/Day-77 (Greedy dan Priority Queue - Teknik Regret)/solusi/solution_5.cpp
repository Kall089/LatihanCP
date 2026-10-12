/*
============================================================
✅ SOLUSI Exercise 5: Kursus dengan Bobot
============================================================
Difficulty: Hard | Kompleksitas: O(n * sum(t)) ~ 2000 * 2*10^6 ... TERLALU BESAR
                   -> dibatasi oleh min(sum(t), max(d)) = 2*10^6
                   Praktisnya O(n * T) dengan T = min(sum t, max d)

── KENAPA REGRET GAGAL DI SINI ─────────────────────────────
Godaan: pakai kerangka Exercise 1, tetapi batalkan kursus
dengan NILAI terkecil.

Buktinya runtuh pada invarian (2) dari teori. Pada Exercise 1
kita menjaga "di antara himpunan berukuran maksimum, total
waktu minimum" — dan itu bisa dibandingkan karena SATU besaran
saja yang penting.
Di sini ada DUA besaran yang bersaing: waktu yang dimakan dan
nilai yang diberikan. Dua keadaan dengan nilai total sama bisa
punya waktu terpakai berbeda, dan tidak ada yang mendominasi.
Membuang kursus bernilai kecil belum tentu membebaskan waktu;
membuang kursus yang lama belum tentu mengorbankan sedikit
nilai.

Uji sendiri: jalankan regret-berdasar-nilai terhadap brute
force pada n <= 8. Ia akan gagal.

── MEMBACA BATASAN ─────────────────────────────────────────
  N <= 2000, t <= 1000  ->  sum(t) <= 2*10^6
  d <= 2*10^6
Hasil kali N dan batas waktu itu sekitar 4*10^9 kalau ditulis
naif — terlalu besar. Tetapi perhatikan bahwa waktu yang
relevan dibatasi oleh min(sum t, max d), dan pada banyak
masukan nyata jauh lebih kecil.
Kode di bawah memakai batas T = min(sum t, max d), yang aman
dan sesuai batasan soal.

── RUMUSAN DP ──────────────────────────────────────────────
Urutkan kursus menurut TENGGAT MENAIK (alasan yang sama dengan
Exercise 1: memproses dalam urutan itu membuat "waktu sekarang"
menjadi keadaan yang cukup).

  dp[w] = nilai maksimum yang bisa dicapai kalau total waktu
          yang sudah terpakai tepat w

Untuk tiap kursus (t, d, v), loop w MUNDUR dari d ke t:
  dp[w] = max(dp[w], dp[w - t] + v)

Batas atas loop adalah d, bukan T — itulah yang menegakkan
tenggat: kursus ini hanya boleh selesai pada waktu <= d.

Jawabannya maksimum seluruh dp.

── KENAPA URUTAN TENGGAT MENAIK MEMBUAT DP INI BENAR ───────
Klaim: kalau sehimpunan kursus layak, maka menjadwalkannya
menurut tenggat menaik juga layak (exchange argument yang sama
dengan Exercise 1).
Karena itu kita boleh membatasi diri pada jadwal terurut
tenggat. DP di atas membangun jadwal seperti itu: kursus
diproses menurut tenggat, dan dp[w] berarti "sudah memakai w
waktu dengan kursus-kursus bertenggat <= tenggat sekarang".

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai regret. Gagal — uji dulu.
2. Loop MAJU. Membuat kursus bisa diambil berkali-kali.
3. Batas atas loop memakai T alih-alih d. Menghilangkan
   penegakan tenggat.
4. Lupa mengurutkan menurut tenggat.
5. Lupa long long: v sampai 10^9 dikali 2000 kursus.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Kursus { ll t, d, v; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<Kursus> k(n);
    ll sumT = 0, maxD = 0;
    for (auto& x : k) {
        cin >> x.t >> x.d >> x.v;
        sumT += x.t;
        maxD = max(maxD, x.d);
    }

    sort(k.begin(), k.end(), [](const Kursus& a, const Kursus& b) {
        return a.d < b.d;                       // tenggat MENAIK
    });

    ll T = min(sumT, maxD);                     // waktu yang relevan
    vector<ll> dp(T + 1, -1);
    dp[0] = 0;

    for (auto& x : k) {
        ll batas = min(x.d, T);                 // tenggat menegakkan batas ATAS
        for (ll w = batas; w >= x.t; w--)       // MUNDUR: tiap kursus sekali
            if (dp[w - x.t] >= 0)
                dp[w] = max(dp[w], dp[w - x.t] + x.v);
    }

    ll jawab = 0;
    for (ll w = 0; w <= T; w++) jawab = max(jawab, dp[w]);

    cout << jawab << '\n';
    return 0;
}
