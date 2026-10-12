/*
============================================================
✅ Solution 3: Subarray dengan Jumlah Tepat K
============================================================
Approach: Prefix sum + map frekuensi
Complexity: Time O(n log n) | Space O(n)
Key Insight: Kondisi tentang SUBARRAY diubah menjadi kondisi tentang PASANGAN
             PREFIX. jumlah a[l..r] = K  <=>  pre[l] = pre[r+1] - K.
             Setelah diubah, kita tidak lagi mencari subarray satu per satu;
             kita cukup menghitung berapa prefix bernilai tertentu yang sudah
             pernah lewat.

📖 PENJELASAN PENDEKATAN:
1. freq[0] = 1 -- ini mewakili PREFIX KOSONG. Tanpa ini, subarray yang dimulai
   dari indeks 0 tidak akan pernah terhitung.
2. Sapu dari kiri sambil menjaga cur = prefix sampai posisi sekarang.
3. hasil += freq[cur - K], lalu freq[cur]++.
   URUTAN INI PENTING: tambahkan ke hasil DULU, baru daftarkan cur.
   Kalau dibalik, saat K = 0 kamu akan menghitung subarray kosong.

VERIFIKASI SAMPEL 2 (a = [0,0,0,0], K = 0):
   Setiap pasangan indeks prefix (i < j) dari 5 prefix bernilai 0
   memberi satu subarray -> C(5,2) = 10.  ✓
   Ini sekaligus menjelaskan kenapa jawabannya 10 dan bukan 4.

⚠️ SLIDING WINDOW TIDAK BISA DIPAKAI di sini karena ada bilangan negatif.
   Sliding window bergantung pada sifat "menambah elemen membuat jumlah naik",
   yang rusak begitu ada angka negatif. Ini pembeda utama Day 29 vs Day 33-34.

⚠️ unordered_map vs map: di Codeforces, unordered_map dengan kunci long long
   bisa dijadikan O(n^2) lewat tes anti-hash. map memberi O(n log n) yang
   dijamin. Kalau butuh kecepatan unordered_map, tambahkan custom hash acak.

🔄 ALTERNATIVE APPROACHES:
- Naif O(n^2): cukup untuk n <= 5000.
- Kalau dijamin semua elemen POSITIF, sliding window O(n) tanpa map.
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

    map<ll, ll> freq;
    freq[0] = 1;                       // prefix kosong

    ll cur = 0, hasil = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        cur += x;

        auto it = freq.find(cur - K);  // hitung DULU
        if (it != freq.end()) hasil += it->second;

        freq[cur]++;                   // daftarkan SETELAHNYA
    }

    cout << hasil << '\n';
    return 0;
}
