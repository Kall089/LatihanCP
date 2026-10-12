/*
============================================================
✅ Solution 3: Playlist Tanpa Pengulangan
============================================================
Approach: Sliding window + peta posisi kemunculan terakhir
Complexity: Time O(n log n) | Space O(n)
Key Insight: Alih-alih menyusutkan window satu per satu, kita bisa
             MELOMPATKAN ujung kiri langsung ke posisi setelah kemunculan
             sebelumnya. Tetapi lompatan itu hanya sah kalau kemunculan
             tersebut masih berada DI DALAM window -- kalau tidak, l akan
             MUNDUR dan seluruh jaminan algoritma runtuh.

📖 PENJELASAN PENDEKATAN:
1. lastSeen[nilai] = indeks terakhir nilai itu terlihat.
2. Untuk setiap r:
   kalau lastSeen[a[r]] ada DAN >= l, maka l = lastSeen[a[r]] + 1.
3. Perbarui lastSeen[a[r]] = r, lalu catat panjang r - l + 1.

⚠️ SYARAT ">= l" ADALAH INTI SOAL INI.
   Contoh yang membongkarnya: a = [1, 2, 1, 3, 2, ...]
   Di r = 4 (nilai 2), lastSeen[2] = 1. Kalau kita langsung set l = 2,
   padahal l sudah maju ke 3 karena kejadian sebelumnya, maka l MUNDUR
   dari 3 ke 2 -- window kembali memuat duplikat dan jawabannya salah.

VERIFIKASI SAMPEL 1 (a = [1,2,1,3,2,7,4,2]):
   r=0 1 : l=0, best=1
   r=1 2 : l=0, best=2
   r=2 1 : lastSeen[1]=0 >= 0 -> l=1, best=2
   r=3 3 : l=1, best=3
   r=4 2 : lastSeen[2]=1 >= 1 -> l=2, best=3
   r=5 7 : l=2, best=4
   r=6 4 : l=2, best=5      <- [1,3,2,7,4]
   r=7 2 : lastSeen[2]=4 >= 2 -> l=5, best=5
   jawab 5  ✓

CATATAN KECEPATAN: unordered_map memberi O(n) rata-rata tetapi bisa di-hack
di Codeforces. map memberi O(n log n) yang dijamin. Kalau nilainya bisa
dikompresi (Day 38), array jauh lebih cepat dari keduanya.

🔄 ALTERNATIVE APPROACHES:
- Menyusutkan satu per satu sambil menghapus dari set: O(n log n) juga,
  lebih mudah dibaca tapi sedikit lebih lambat.
- Kompresi koordinat + array: O(n log n) untuk kompresi, O(n) untuk window.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& v : a) cin >> v;

    map<int, int> lastSeen;
    int l = 0, best = 0;

    for (int r = 0; r < n; r++) {
        auto it = lastSeen.find(a[r]);
        if (it != lastSeen.end() && it->second >= l)   // syarat >= l WAJIB
            l = it->second + 1;

        lastSeen[a[r]] = r;
        best = max(best, r - l + 1);
    }

    cout << best << '\n';
    return 0;
}
