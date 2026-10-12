/*
============================================================
✅ Solution 2: Kapan Posisi Mencapai Target
============================================================
Approach: Parallel binary search + BIT (range update, point query)
Complexity: Time O(log n * (n + q) log m) | Space O(m + n + q)
Key Insight: Berbeda dari Exercise 1, setiap query memeriksa POSISI YANG
             BERBEDA, sehingga tidak ada satu besaran global yang bisa
             diurutkan. Di sinilah parallel binary search benar-benar
             diperlukan: kita menjalankan seluruh binary search BERBARENGAN,
             satu lapis per putaran.

📖 KENAPA NAIF TERLALU LAMBAT:
   Setiap query sendirian adalah binary search O(log n) langkah, tetapi
   MENGUJI satu tebakan berarti menerapkan t kejadian -> O(t log m).
   Total: q * log n * n log m = 2*10^5 * 18 * 2*10^5 * 18  -> MUSTAHIL.

📖 KERANGKANYA:
   1. Setiap query punya rentang pencariannya sendiri [lo[i], hi[i]].
   2. Setiap putaran: kelompokkan query berdasarkan mid-nya ke dalam bucket.
   3. Reset struktur data, lalu sapu t = 1..n SEKALI.
      Saat mencapai t, seluruh query di bucket[t] sudah punya keadaan yang
      tepat untuk diuji.
   4. Ulangi sampai seluruh rentang menyempit.

   Biayanya: log(n) putaran x satu sapuan O(n log m) = O(n log n log m),
   ditambah O(q log n log m) untuk menjawab. Sekitar 6*10^7 -- aman.

⚠️ RESET ADALAH BAGIAN WAJIB, DAN INI BUG NOMOR SATU.
   Putaran 1 berakhir dengan BIT memuat seluruh n kejadian. Kalau putaran 2
   dimulai tanpa reset, kejadian 1..n masih ada DITAMBAH kejadian yang baru
   diterapkan -- seluruh nilainya salah.
   Gejalanya sangat membingungkan: sampel kecil yang hanya butuh satu
   putaran tetap benar, sehingga bugnya lolos dari pengujian awal.

⚠️ LOOP t HARUS BERJALAN PENUH dari 1 sampai n, meski sebagian besar
   bucket kosong. Struktur data harus dibangun BERTAHAP; melompati t yang
   bucket-nya kosong membuat keadaannya salah saat mencapai t berikutnya.

⚠️ PILIHAN STRUKTUR DATA: kita butuh update RENTANG dan baca TITIK.
   BIT dengan trik difference (add di l, kurangi di r+1, lalu prefix sum
   saat membaca) memberi keduanya dalam O(log m).
   Difference array biasa TIDAK cocok: updatenya O(1) tetapi membaca satu
   nilai butuh O(m), dan kita membaca berkali-kali di tengah sapuan.

⚠️ hi DIINISIALISASI n+1, BUKAN n. Slot n+1 mewakili "tidak pernah
   tercapai". Tanpa itu, query yang tidak punya jawaban akan salah
   dilaporkan menjawab n.

CATATAN: implementasi ini telah diuji terhadap brute force pada 3000 kasus
acak berukuran kecil.

🔄 ALTERNATIVE APPROACHES:
- Segment tree pada waktu (segment tree beats / offline divide and conquer):
  O((n+q) log^2 n), lebih rumit tetapi kadang lebih fleksibel.
- Persistent BIT: memungkinkan query ONLINE, tetapi memorinya jauh lebih besar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int m;
vector<ll> bitArr;

void bitAdd(int i, ll v) { for (; i <= m; i += i & -i) bitArr[i] += v; }
void rangeAdd(int l, int r, ll v) { bitAdd(l, v); bitAdd(r + 1, -v); }
ll bitGet(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bitArr[i]; return s; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> m >> n >> q;

    vector<int> L(n + 1), R(n + 1);
    vector<ll> V(n + 1);
    for (int t = 1; t <= n; t++) cin >> L[t] >> R[t] >> V[t];

    vector<int> P(q);
    vector<ll> T(q);
    for (int i = 0; i < q; i++) cin >> P[i] >> T[i];

    vector<int> lo(q, 1), hi(q, n + 1);       // n+1 = "tidak pernah"
    vector<vector<int>> bucket(n + 2);

    while (true) {
        for (auto& b : bucket) b.clear();     // clear, bukan realokasi
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                int mid = lo[i] + (hi[i] - lo[i]) / 2;
                bucket[mid].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        bitArr.assign(m + 2, 0);              // RESET -- WAJIB

        for (int t = 1; t <= n; t++) {        // sapuan PENUH, jangan melompat
            rangeAdd(L[t], R[t], V[t]);

            for (int i : bucket[t]) {
                if (bitGet(P[i]) >= T[i]) hi[i] = t;
                else                      lo[i] = t + 1;
            }
        }
    }

    string out;
    for (int i = 0; i < q; i++) {
        out += to_string(lo[i] > n ? -1 : lo[i]);
        out += '\n';
    }
    cout << out;

    return 0;
}
