/*
============================================================
✅ Solution 3: Substring Seimbang Terpanjang
============================================================
Approach: transformasi +1/-1, lalu prefix sum + map kemunculan pertama
Complexity: Time O(N log N) dengan map, O(N) dengan array offset | Space O(N)
Key Insight: setelah 'a' -> +1 dan 'b' -> -1, "seimbang" berarti jumlahnya 0.
             Dan substring (j..i-1) berjumlah 0 tepat ketika P[i] == P[j].
             Jadi soalnya berubah menjadi: cari dua indeks prefix dengan nilai
             sama yang jaraknya paling jauh.

📖 PENJELASAN PENDEKATAN:
1. P[0] = 0, P[i] = P[i-1] + (S[i-1] == 'a' ? 1 : -1).
2. Untuk tiap nilai prefix, simpan indeks PERTAMA kali ia muncul.
3. Saat bertemu nilai yang sudah pernah ada di posisi j, panjang kandidatnya
   adalah i - j.

⚠️ KENAPA KEMUNCULAN PERTAMA, BUKAN TERAKHIR:
   kita mencari jarak TERJAUH antara dua prefix bernilai sama. Untuk i yang
   tetap, jarak terjauh dicapai oleh j sekecil mungkin. Jadi begitu sebuah
   nilai sudah tercatat, JANGAN pernah ditimpa.

⚠️ PREFIX KOSONG: (nilai 0, indeks 0) harus dimasukkan lebih dulu. Tanpa itu,
   substring seimbang yang dimulai dari karakter pertama tidak akan terdeteksi.
   Sample 4 ("baab") gagal total kalau ini terlewat.

⚠️ RENTANG NILAI PREFIX: antara -N dan +N. Karena rapat dan terbatas, kamu
   bisa mengganti map dengan array berukuran 2N+1 memakai offset N. Itu
   menurunkan kompleksitas jadi O(N) murni dan menghindari risiko anti-hash
   pada unordered_map. Solusi ini memakai cara array tersebut.

🔄 ALTERNATIVE APPROACHES:
- map<int,int>: lebih pendek ditulis, O(N log N), aman.
- unordered_map: O(N) rata-rata TAPI rawan anti-hash di Codeforces.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string s;
    cin >> n >> s;

    // nilai prefix berkisar -n..n, geser dengan offset n
    const int OFF = n;
    vector<int> first(2 * n + 1, -2);   // -2 = belum pernah muncul
    first[0 + OFF] = 0;                 // prefix kosong di indeks 0

    int pre = 0, best = 0;
    for (int i = 1; i <= n; i++) {
        pre += (s[i - 1] == 'a') ? 1 : -1;
        int key = pre + OFF;
        if (first[key] == -2) first[key] = i;
        else best = max(best, i - first[key]);
    }

    cout << best << "\n";
    return 0;
}
