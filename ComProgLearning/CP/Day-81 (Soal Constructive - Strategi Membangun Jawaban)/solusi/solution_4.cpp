/*
============================================================
✅ SOLUSI Exercise 4: Membagi Menjadi Dua Bagian Sama
============================================================
Difficulty: Medium | Kompleksitas: O(n)

── LANGKAH 1: PARITAS (paling murah) ───────────────────────
Total seluruh bilangan 1..n adalah S = n(n+1)/2.
Agar bisa dibagi menjadi dua kelompok berjumlah sama, S harus
GENAP. Kalau ganjil -> "NO", selesai tanpa kerja lagi.

Memeriksa kemustahilan lebih dulu adalah kebiasaan yang sangat
menghemat: ia murah, dan menyelesaikan sekitar separuh kasus
uji.

Kapan S genap? n(n+1)/2 genap terjadi ketika n mod 4 adalah 0
atau 3. Kamu tidak perlu menghafal itu — cukup hitung
langsung.

── LANGKAH 2: KONSTRUKSI SERAKAH ───────────────────────────
Target: pilih sebagian dari 1..n yang jumlahnya tepat S/2.
Ambil bilangan dari yang TERBESAR selama masih muat.

    sisa = S / 2
    untuk x dari n turun ke 1:
        kalau x <= sisa: ambil x, sisa -= x
        kalau sisa == 0: berhenti

── KENAPA GREEDY INI PASTI BERHASIL ────────────────────────
Ini bagian yang harus kamu tuliskan, bukan sekadar diasumsikan.

Invarian: setiap kali kita memproses bilangan x, sisa target
selalu memenuhi 0 <= sisa <= 1 + 2 + ... + x, yaitu jumlah
seluruh bilangan yang masih tersedia.

Buktinya induktif. Di awal, sisa = S/2 <= S = 1+...+n. ✓
Pada langkah x:
  - kalau x <= sisa, kita ambil x, dan sisa baru = sisa - x.
    Karena sisa <= 1+...+x, maka sisa - x <= 1+...+(x-1). ✓
  - kalau x > sisa, kita lewati, dan sisa tetap. Kita perlu
    sisa <= 1+...+(x-1). Karena sisa < x dan sisa bilangan
    bulat, sisa <= x-1 <= 1+...+(x-1) untuk x >= 2. ✓

Ketika kita sampai di x = 1, invarian memberi sisa <= 1,
sehingga sisa pasti 0 atau 1 — dan kalau 1, kita ambil angka 1.
Jadi sisa selalu berhasil dinolkan. ∎

Argumen ini adalah "konstruksi" dalam pasangan batas-bawah dan
konstruksi: ia membuktikan bahwa jawabannya benar-benar ada,
bukan hanya bahwa paritasnya memungkinkan.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa memeriksa paritas lebih dulu.
2. Lupa long long: n sampai 10^6 -> S sekitar 5*10^11.
3. Mengambil dari yang TERKECIL. Itu juga berhasil tetapi
   buktinya lebih rumit; dari yang terbesar lebih bersih.
4. Format keluaran: soal meminta ukuran kelompok pada baris
   terpisah sebelum isinya.
5. Menyangka jawabannya unik. Untuk n = 4, {1,4} dan {2,3}
   sama-sama benar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n;
    if (!(cin >> n)) return 0;

    ll S = n * (n + 1) / 2;
    if (S % 2 != 0) { cout << "NO\n"; return 0; }   // paritas

    ll sisa = S / 2;
    vector<ll> pilih;
    for (ll x = n; x >= 1 && sisa > 0; x--)
        if (x <= sisa) { pilih.push_back(x); sisa -= x; }

    cout << "YES\n" << pilih.size() << '\n';
    for (size_t i = 0; i < pilih.size(); i++)
        cout << pilih[i] << " \n"[i + 1 == pilih.size()];
    return 0;
}
