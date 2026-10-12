/*
============================================================
✅ Solution 6: Keranjang Buah
============================================================
🔑 TEKNIK: SLIDING WINDOW VARIABEL + FREQUENCY MAP  (Day 34 + 40)
Complexity: Time O(N log N) dengan map | Space O(N)

📖 FRASA PENENTUNYA: tiga sinyal sekaligus -
   "berurutan tanpa melompat"  -> subarray, bukan subset
   "terpanjang yang memenuhi"  -> mencari rentang optimal
   syarat rusak saat melebar, pulih saat menyempit -> MONOTON

   Monotonisitas itulah izin memakai window variabel. Tanpa itu, teknik ini
   tidak sah (bandingkan dengan soal yang punya elemen negatif).

📖 STRUKTUR PEMBANTU: kamu perlu tahu "ada berapa jenis berbeda di window
   sekarang". Frequency map menjawabnya: ukuran map = jumlah jenis.

⚠️ HAPUS KUNCI SAAT HITUNGANNYA NOL. Kalau kamu hanya melakukan cnt[x]--
   tanpa menghapus entri yang bernilai 0, map.size() akan terus membesar
   dan kondisimu salah. Ini bug nomor satu di soal jenis ini.

⚠️ Nilai buah sampai 10^9, jadi tidak bisa pakai array frekuensi biasa.
   Pilihannya: map, unordered_map (rawan anti-hash), atau kompresi
   koordinat lebih dulu lalu array (paling cepat).

⚠️ Sample 4 ([3,1,2,2,2,1,4], K=2 -> 5): jawabannya [1,2,2,2,1] pada posisi
   2..6. Bukan yang dimulai dari kiri. Menguji apakah window kamu
   benar-benar bergeser, bukan cuma melebar dari awal.

🩺 DIAGNOSIS DIRI:
   Tidak mengenali             -> ulangi Day 34
   Salah karena map membengkak -> tidak menghapus kunci bernilai 0
   Menulis O(N^2)              -> pointer kiri kamu mundur; ia tidak boleh
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    map<ll,int> cnt;
    int l = 0, best = 0;

    for (int r = 0; r < n; r++) {
        cnt[a[r]]++;
        while ((int)cnt.size() > k) {
            cnt[a[l]]--;
            if (cnt[a[l]] == 0) cnt.erase(a[l]);   // WAJIB dihapus
            l++;
        }
        best = max(best, r - l + 1);
    }

    cout << best << "\n";
    return 0;
}
