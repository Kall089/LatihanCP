/*
============================================================
✅ SOLUSI Exercise 1: Menggabungkan Tumpukan Batu
============================================================
Difficulty: Easy | Kompleksitas: O(n log n) waktu, O(n) memori

── IDE UTAMA ────────────────────────────────────────────────
Ini algoritma Huffman. Gabungkan terus DUA tumpukan TERKECIL,
jumlahkan setiap biaya penggabungan.

── KENAPA HEAP, BUKAN SORT SEKALI ──────────────────────────
Tumpukan hasil gabungan harus bisa dipilih lagi dan bersaing
dengan tumpukan asli. Array terurut tidak bisa menerima anggota
baru dengan murah; heap bisa dalam O(log n).

Tanda pengenal umum: KEPUTUSANMU MENGHASILKAN KANDIDAT BARU.
Setiap kali kamu melihat itu, sort sekali tidak akan cukup.

── KENAPA "URUT SEKALI LALU GABUNG BERURUTAN" SALAH ────────
Strategi itu selalu menggabungkan hasil sebelumnya dengan
elemen berikutnya, tanpa membiarkan hasil bersaing kembali.

  {1,1,1,1,1,1} : sekuensial 20, Huffman 16
  {1,1,1,1,100} : sekuensial 113, Huffman 112
  {5,9,12,13,16,45} : sekuensial 234, Huffman 224

Contoh pertama paling jelas: sekuensial membangun rantai miring
berkedalaman 5, Huffman membangun pohon seimbang berkedalaman 3.

── BUKTI SINGKAT ───────────────────────────────────────────
Lemma 1: ada pohon optimal yang menempatkan dua nilai terkecil
sebagai saudara di kedalaman maksimum.
  Ambil pohon optimal T. Daun terdalam pasti punya saudara
  (kalau tidak, subpohonnya bisa dinaikkan dan biayanya turun).
  Sebut dua saudara terdalam a dan b. Tukar nilai terkecil x
  dengan a:
      delta = (f_a - f_x) * (d_x - d_a)
  Karena f_a >= f_x dan d_x <= d_a, delta <= 0. Biaya tidak
  naik. Ulangi untuk y dan b.

Lemma 2: setelah x dan y dijadikan saudara, gantilah keduanya
dengan satu simpul bernilai x+y. Hubungan biayanya
      biaya(T) = biaya(T') + x + y
dan suku x+y KONSTAN. Jadi meminimalkan T sama dengan
meminimalkan T'. Itu optimal substructure.

Kedua lemma memberi greedy choice property dan optimal
substructure — dua bahan Day 71.

Diverifikasi: 400 kasus acak (n <= 7) dibandingkan dengan brute
force atas SELURUH urutan penggabungan. Semuanya cocok.

── JEBAKAN ─────────────────────────────────────────────────
1. priority_queue default di C++ adalah MAX-heap. Untuk soal
   ini kamu butuh MIN-heap:
       priority_queue<ll, vector<ll>, greater<ll>>
   Salah arah tidak menghasilkan error apa pun, hanya jawaban
   salah. Ini salah satu bug tersulit dilacak.
2. n = 1: tidak ada penggabungan, jawabannya 0.
3. Tipe data. Kedalaman pohon sampai O(log n), jadi total
   sekitar sum(a) * log n = 2*10^14 * 18. WAJIB long long.
   (Bahkan pada kasus miring terburuk masih muat.)
4. Membangun pohon eksplisit. Tidak perlu untuk soal ini —
   cukup jumlahkan tiap hasil gabungan.
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

    // MIN-heap: perhatikan greater<ll>
    priority_queue<ll, vector<ll>, greater<ll>> pq(a.begin(), a.end());

    ll total = 0;
    while (pq.size() > 1) {
        ll x = pq.top(); pq.pop();
        ll y = pq.top(); pq.pop();
        total += x + y;               // biaya penggabungan ini
        pq.push(x + y);               // hasilnya jadi kandidat baru
    }

    cout << total << '\n';            // n == 1 menghasilkan 0 secara alami
    return 0;
}
