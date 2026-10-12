/*
============================================================
✅ Solution 6: Grid Setelah Pemadatan
============================================================
Approach: Kompresi koordinat dua dimensi (sumbu terpisah)
Complexity: Time O(n log n) | Space O(n)
Key Insight: Seluruh cerita tentang menghapus baris kosong dan menggeser
             kartu hanyalah pembungkus. Hasil akhirnya adalah pernyataan
             yang jauh lebih sederhana: posisi akhir sebuah kartu adalah
             PERINGKAT koordinatnya di antara seluruh koordinat yang
             terpakai. Baris dan kolom sama sekali tidak saling memengaruhi,
             jadi keduanya dikompresi secara TERPISAH.

📖 PENJELASAN PENDEKATAN:
1. Kumpulkan seluruh A[i] ke kamus X, seluruh B[i] ke kamus Y.
2. Bangun keduanya (sort + unique + erase).
3. Jawabannya (idxX(A[i]) + 1, idxY(B[i]) + 1).

KENAPA INI BENAR: proses penghapusan berhenti tepat ketika tidak ada lagi
baris kosong di antara baris berisi. Keadaan itu setara dengan "baris ke-k
yang terpakai berada di posisi k". Dan "baris ke-k yang terpakai" persis
sama dengan peringkat ke-k dalam daftar baris unik terurut. Tidak ada
simulasi yang perlu dilakukan.

Pelajaran yang lebih umum: kalau sebuah soal menggambarkan proses berulang
yang "menghapus celah", jawabannya hampir selalu peringkat. Cari pernyataan
akhir yang stabil, bukan simulasi langkahnya.

⚠️ SUMBU TIDAK BOLEH DIGABUNG. Satu kesalahan yang mungkin terjadi adalah
   mengompres A dan B ke dalam satu kamus bersama. Itu salah -- keduanya
   ruang yang berbeda dan peringkatnya dihitung terpisah.

VERIFIKASI SAMPEL 1:
   A = [1, 2, 4, 4]  -> unik [1, 2, 4]     peringkat 0, 1, 2, 2
   B = [1, 1, 2, 4]  -> unik [1, 2, 4]     peringkat 0, 0, 1, 2
   hasil (1-based): (1,1) (2,1) (3,2) (3,3)  ✓

🔄 ALTERNATIVE APPROACHES:
- map<ll,int> untuk masing-masing sumbu: setara, sedikit lebih lambat.
- Simulasi penghapusan baris/kolom: O(n * banyak langkah) -- jauh lebih
  lambat dan sama sekali tidak perlu.
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
    vector<ll> A(n), B(n);
    for (int i = 0; i < n; i++) cin >> A[i] >> B[i];

    // Kamus terpisah untuk masing-masing sumbu
    vector<ll> vx = A, vy = B;
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    sort(vy.begin(), vy.end());
    vy.erase(unique(vy.begin(), vy.end()), vy.end());

    string out;
    for (int i = 0; i < n; i++) {
        int r = int(lower_bound(vx.begin(), vx.end(), A[i]) - vx.begin()) + 1;
        int c = int(lower_bound(vy.begin(), vy.end(), B[i]) - vy.begin()) + 1;
        out += to_string(r);
        out += ' ';
        out += to_string(c);
        out += '\n';
    }
    cout << out;

    return 0;
}
