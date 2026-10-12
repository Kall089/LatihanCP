/*
============================================================
✅ Solution 1: Kapan Tabungan Mencapai Target
============================================================
Approach: SATU sapuan + two pointers atas query terurut
Complexity: Time O(n + q log q) | Space O(q)
Key Insight: Soal ini sengaja ditaruh pertama untuk menunjukkan bahwa
             parallel binary search SERING TIDAK DIPERLUKAN. Karena seluruh
             pertanyaan memeriksa BESARAN GLOBAL yang sama (total tabungan),
             mengurutkan pertanyaan berdasarkan ambangnya sudah cukup --
             tanpa binary search sama sekali.

📖 PENJELASAN PENDEKATAN:
1. Baca query beserta ID ASLINYA, lalu urutkan berdasarkan target.
2. Sapu hari t = 1..n sambil mengakumulasi total.
3. Selama query terdepan (target terkecil yang belum terjawab) sudah
   tercapai, catat jawabannya dan majukan penunjuk.
4. Cetak sesuai urutan ID asli.

KENAPA SATU SAPUAN CUKUP: total tabungan MONOTON NAIK (seluruh a[t] positif),
dan query sudah terurut berdasarkan ambang. Jadi begitu ambang ke-j
tercapai, seluruh ambang yang lebih kecil pasti sudah tercapai lebih dulu.
Penunjuk query hanya perlu MAJU, tidak pernah mundur -- persis argumen
two pointers dari Day 32.

⚠️ SELALU PERIKSA VARIAN INI SEBELUM MENULIS PARALLEL BINARY SEARCH.
   O(n + q log q) jauh lebih sederhana dan lebih cepat daripada
   O(log n * (n + q)). Parallel binary search baru diperlukan kalau setiap
   query memeriksa BESARAN YANG BERBEDA (lihat Exercise 2), sehingga tidak
   ada satu urutan global yang bisa dimanfaatkan.

⚠️ JANGAN LUPA ID ASLI. Setelah diurutkan, urutan query berubah. Kalau kamu
   mencetak langsung dalam urutan terurut, keluarannya salah meski
   perhitungannya benar. Simpan pasangan {target, id}.

⚠️ OVERFLOW: n = 5*10^5 dan a[t] sampai 10^9 memberi total 5*10^14,
   dan target sampai 10^18. long long wajib untuk keduanya.

VERIFIKASI SAMPEL (a = [1,2,3,4,5]):
   total kumulatif: 1, 3, 6, 10, 15
   target 3   -> tercapai hari 2   ✓
   target 10  -> tercapai hari 4   ✓
   target 100 -> tidak pernah      ✓

🔄 ALTERNATIVE APPROACHES:
- Prefix sum + binary search per query: O(n + q log n). Juga benar dan
  sangat sederhana. Untuk soal ini, keduanya sama baiknya.
- Parallel binary search: berlebihan di sini, tetapi tetap benar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int t = 1; t <= n; t++) cin >> a[t];

    // simpan {target, id} supaya urutan keluaran bisa dipulihkan
    vector<pair<ll, int>> qs(q);
    for (int i = 0; i < q; i++) { cin >> qs[i].first; qs[i].second = i; }
    sort(qs.begin(), qs.end());

    vector<int> jawab(q, -1);
    ll total = 0;
    int ptr = 0;

    for (int t = 1; t <= n && ptr < q; t++) {
        total += a[t];
        while (ptr < q && qs[ptr].first <= total) {     // penunjuk hanya MAJU
            jawab[qs[ptr].second] = t;
            ptr++;
        }
    }

    string out;
    for (int i = 0; i < q; i++) { out += to_string(jawab[i]); out += '\n'; }
    cout << out;

    return 0;
}
