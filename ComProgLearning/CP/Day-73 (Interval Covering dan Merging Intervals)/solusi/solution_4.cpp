/*
============================================================
✅ SOLUSI Exercise 4: Lompat Sejauh Mungkin
============================================================
Difficulty: Medium | Kompleksitas: O(n) waktu, O(1) memori tambahan

── PEMETAAN KE COVERING ────────────────────────────────────
Petak i menjadi interval [i, i + a[i]].
Alasannya: untuk memakai petak i sebagai batu loncatan kamu
harus sudah bisa mencapai posisi i, dan dari sana kamu bisa
mendarat di mana saja sampai i + a[i].
Target yang harus ditutupi adalah [0, n-1].

Dengan pemetaan itu, soal ini PERSIS Exercise 3. Bedanya kita
tidak perlu membangun array interval sama sekali, karena
interval ke-i selalu dimulai tepat di i — yang berarti saat
kita menyapu i dari kiri ke kanan, interval yang "boleh
dipertimbangkan" adalah persis yang sudah kita lewati.

── BENTUK YANG LAZIM DIPAKAI ───────────────────────────────
  jangkauan  = sejauh mana bisa dicapai dengan 'lompat' lompatan
  berikutnya = sejauh mana bisa dicapai dengan satu lompatan lagi

Sapu i dari 0 sampai n-2:
  berikutnya = max(berikutnya, i + a[i])
  kalau i sudah mencapai batas 'jangkauan', kita HARUS melompat:
      jangkauan = berikutnya, lompat++
      kalau jangkauan tidak bertambah -> mustahil

── KENAPA BERHENTI DI n-2 ──────────────────────────────────
Kalau kita sudah berdiri di petak n-1, tidak perlu melompat
lagi. Memasukkan i = n-1 ke dalam loop akan menambah satu
lompatan yang tidak perlu.
Ini juga yang membuat sampel 3 (n = 1) menghasilkan 0 secara
alami: loopnya tidak berjalan sama sekali.

── DETEKSI MUSTAHIL ────────────────────────────────────────
Kalau pada saat harus melompat 'berikutnya' tidak lebih besar
dari 'jangkauan', kita terjebak. Sampel 2 memakai a[3] = 0
sebagai penghalang yang tidak bisa dilewati.

── JEBAKAN ─────────────────────────────────────────────────
1. Menghitung lompatan saat i = n-1. Menghasilkan jawaban
   kelebihan satu.
2. Lupa kasus n = 1.
3. i + a[i] bisa melebihi n-1; itu tidak masalah untuk logika,
   tetapi jangan dipakai sebagai indeks array.
4. Solusi BFS juga benar dan O(n), tetapi greedy ini lebih
   ringkas dan tidak memakai memori tambahan.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    ll jangkauan = 0, berikutnya = 0;
    int lompat = 0;

    for (int i = 0; i <= n - 2; i++) {
        if (i > jangkauan) {               // tidak bisa mencapai petak ini
            cout << -1 << '\n';
            return 0;
        }
        berikutnya = max(berikutnya, (ll)i + a[i]);
        if (i == jangkauan) {              // batas lompatan sekarang habis
            if (berikutnya <= jangkauan) { // tidak ada kemajuan
                cout << -1 << '\n';
                return 0;
            }
            jangkauan = berikutnya;
            lompat++;
        }
    }

    cout << lompat << '\n';
    return 0;
}
