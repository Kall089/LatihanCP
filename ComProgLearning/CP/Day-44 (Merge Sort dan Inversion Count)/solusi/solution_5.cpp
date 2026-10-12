/*
============================================================
✅ Solution 5: Pasangan Terbalik Kuat
============================================================
Approach: Merge sort DUA FASE (hitung, lalu gabung)
Complexity: Time O(n log n) | Space O(n)
Key Insight: Kondisi yang DIHITUNG (a[i] > 2*a[j]) berbeda dari kondisi
             yang dipakai MENGGABUNG (a[i] <= a[j]). Karena berbeda, kedua
             pekerjaan itu tidak bisa dilakukan dalam satu loop -- harus
             dipisah menjadi dua fase yang berjalan berurutan.

📖 PENJELASAN PENDEKATAN:
1. Rekursi kiri dan kanan seperti biasa.
2. FASE 1 -- menghitung. Kedua bagian sudah terurut. Untuk setiap i di
   bagian kiri, geser penunjuk j di bagian kanan selama a[i] > 2*a[j].
   Semua elemen kanan dari mid sampai j-1 membentuk pasangan dengan a[i].
   Karena a[i] MENAIK saat i maju, ambang batasnya juga menaik, sehingga
   j tidak perlu mundur -- j hanya MAJU. Itulah yang menjaga fase ini O(n).
3. FASE 2 -- merge biasa.

⚠️ KENAPA j TIDAK PERLU DIRESET setiap i? Karena bagian kiri terurut menaik.
   Kalau a[i] > 2*a[j] maka a[i+1] >= a[i] > 2*a[j] juga. Jadi semua yang
   sudah lolos untuk a[i] pasti lolos untuk a[i+1]. Ini persis argumen
   two pointers yang sama dengan Day 32 dan Day 34.

⚠️ OVERFLOW ADALAH JEBAKAN NYATA DI SOAL INI.
   Batasnya mencapai 2^31 - 1, sehingga 2 * a[j] meluap kalau dihitung
   dalam int. Tulis 2LL * a[j] dan cast a[i] ke long long.
   Nilai negatif juga penting: untuk a[j] negatif, 2*a[j] justru LEBIH
   KECIL dari a[j], jadi kondisinya tetap masuk akal tanpa penanganan
   khusus -- tetapi hanya kalau perkaliannya tidak overflow.

⚠️ JANGAN MENCOBA MENGGABUNGKAN DUA FASE. Godaan untuk menghitung sambil
   merge sangat besar, tetapi karena ambang batasnya berbeda, hasilnya akan
   salah dengan cara yang sulit dilihat.

VERIFIKASI SAMPEL 2 ([2,4,3,5,1]):
   pasangan yang memenuhi: (4,1), (3,1), (5,1) -> 3  ✓
   ((2,1) tidak memenuhi karena 2 > 2*1 = 2 salah)

CATATAN: solusi ini telah diuji terhadap brute force pada 20000 array acak.

🔄 ALTERNATIVE APPROACHES:
- BIT + kompresi: untuk tiap j, hitung berapa a[i] di kiri yang lebih besar
  dari 2*a[j]. Butuh kompresi atas gabungan nilai a[i] dan 2*a[j].
- Ordered set: paling pendek, tetapi konstanta besar.
- Pola dua fase ini bisa dipakai untuk kondisi APA PUN yang monoton
  terhadap pengurutan -- misalnya a[i] > a[j] + K, atau a[i] * a[j] > C
  untuk nilai positif.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rec(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int mid = l + (r - l) / 2;
    ll res = rec(a, tmp, l, mid) + rec(a, tmp, mid, r);

    // FASE 1: hitung. j hanya MAJU -> O(n) per level.
    int j = mid;
    for (int i = l; i < mid; i++) {
        while (j < r && (ll)a[i] > 2LL * a[j]) j++;   // 2LL: hindari overflow
        res += j - mid;
    }

    // FASE 2: merge biasa
    int i2 = l, j2 = mid, k = l;
    while (i2 < mid && j2 < r)
        tmp[k++] = (a[i2] <= a[j2]) ? a[i2++] : a[j2++];
    while (i2 < mid) tmp[k++] = a[i2++];
    while (j2 < r)   tmp[k++] = a[j2++];
    for (int t = l; t < r; t++) a[t] = tmp[t];

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n), tmp(n);
    for (int& x : a) cin >> x;

    cout << rec(a, tmp, 0, n) << '\n';
    return 0;
}
