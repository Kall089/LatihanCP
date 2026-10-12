/*
============================================================
✅ Solution 3: Pasangan dengan Selisih Tepat K
============================================================
Approach: Sapuan tunggal, hitung SEBELUM mendaftarkan diri sendiri
Complexity: Time O(n log n) | Space O(n)
Key Insight: Urutan dua operasi menentukan kebenaran. Dengan menghitung
             pasangan SEBELUM memasukkan elemen sekarang ke dalam peta,
             kita mendapat dua jaminan sekaligus secara gratis:
             (1) sebuah elemen tidak pernah berpasangan dengan dirinya
                 sendiri,
             (2) setiap pasangan terhitung TEPAT SEKALI, yaitu saat
                 anggotanya yang lebih belakang diproses.

📖 PENJELASAN PENDEKATAN:
1. Sapu dari kiri, jaga peta hitungan nilai yang SUDAH lewat.
2. Untuk elemen x, pasangan yang mungkin adalah x-K dan x+K.
3. Tambahkan hitungannya ke hasil, LALU daftarkan x.

⚠️ K == 0 HARUS DIPISAH.
   Kalau K = 0, maka x-K dan x+K adalah nilai yang sama, sehingga menambahkan
   keduanya membuat setiap pasangan terhitung dua kali.
   Untuk K = 0, cukup hasil += cnt[x] sekali.
   Sampel 2 ([7,7,7,1], K=0) menguji tepat ini: jawabannya 3 (yaitu C(3,2)),
   bukan 6.

⚠️ URUTAN OPERASI, DEMONSTRASI DENGAN a = [7,7], K = 0:
   BENAR  : hasil += cnt[7]=0 -> 0, cnt[7]=1
            hasil += cnt[7]=1 -> 1, cnt[7]=2      hasil 1  ✓
   TERBALIK: cnt[7]=1, hasil += cnt[7]=1 -> 1
            cnt[7]=2, hasil += cnt[7]=2 -> 3      hasil 3  ✗

⚠️ OVERFLOW: kalau semua n = 2*10^5 elemen sama dan K = 0, jawabannya
   n(n-1)/2 = 2*10^10. int jebol. long long wajib.

CATATAN PILIHAN STRUKTUR: nilai mencapai 10^9 sehingga array frekuensi
langsung mustahil. Di sini kita memakai map (O(n log n), dijamin).
Alternatif yang lebih cepat: kompres dulu (Day 38) lalu pakai array --
O(n log n) untuk kompresi tetapi O(1) per akses setelahnya.
unordered_map sebaiknya dihindari di Codeforces karena bisa di-hack.

🔄 ALTERNATIVE APPROACHES:
- Sort lalu two pointers: O(n log n), ruang O(1), dan menghindari map
  sepenuhnya. Pendekatan yang sangat bagus untuk soal ini.
- Kompresi + array: tercepat kalau n besar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    ll K;
    cin >> n >> K;

    map<ll, ll> cnt;
    ll hasil = 0;

    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;

        if (K == 0) {
            auto it = cnt.find(x);                    // pasangan nilai identik
            if (it != cnt.end()) hasil += it->second;
        } else {
            auto i1 = cnt.find(x - K);
            if (i1 != cnt.end()) hasil += i1->second;
            auto i2 = cnt.find(x + K);
            if (i2 != cnt.end()) hasil += i2->second;
        }

        cnt[x]++;                                     // daftarkan SETELAHNYA
    }

    cout << hasil << '\n';
    return 0;
}
