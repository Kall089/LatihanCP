/*
============================================================
✅ Solution 1: Urutkan Umur
============================================================
Approach: Counting sort sederhana
Complexity: Time O(n + V) | Space O(V)
Key Insight: Batas bawah Omega(n log n) hanya berlaku untuk pengurutan yang
             bekerja dengan MEMBANDINGKAN. Di sini kita tidak membandingkan
             satu elemen pun -- kita memakai nilai sebagai ALAMAT MEMORI.
             Itu bukan pelanggaran batas bawah, melainkan keluar dari
             modelnya.

📖 PENJELASAN PENDEKATAN:
1. cnt[umur]++ untuk seluruh elemen.
2. Sapu umur dari 1 sampai 100, cetak masing-masing sebanyak cnt kali.

ANALISIS: n = 2*10^6, V = 100.
   counting sort : 2*10^6 + 100 ~ 2*10^6 operasi
   std::sort     : 2*10^6 * log2(2*10^6) * 1.5 ~ 6*10^7 operasi
   Counting sort sekitar 30 kali lebih cepat.

Bandingkan kalau angkanya dibalik (n = 100, V = 2*10^6): counting sort akan
membuang 2 juta iterasi untuk slot kosong, sedangkan std::sort selesai dalam
sekitar 1000 operasi. Selalu HITUNG, jangan memakai counting sort secara
refleks.

⚠️ KELUARAN BESAR ADALAH BAGIAN NYATA DARI SOAL INI.
   Mencetak 2 juta bilangan dengan `cout << x << ' '` satu per satu bisa
   memakan waktu lebih lama daripada pengurutannya sendiri. Membangun satu
   string lalu mencetaknya sekali menghindari jutaan operasi stream.
   Kebiasaan ini layak dibentuk sekarang.

⚠️ UKURAN ARRAY harus maks+1, bukan maks. Umur 100 membutuhkan indeks 100,
   sehingga arraynya berukuran 101. Kesalahan off-by-one di sini menghasilkan
   akses di luar batas yang sering tidak crash.

🔄 ALTERNATIVE APPROACHES:
- std::sort: benar, tetapi sekitar 30x lebih lambat di sini.
- Radix sort: berlebihan; rentang nilainya sudah sangat kecil.
- Kalau soal hanya menanyakan STATISTIK (median, modus, kuartil), kamu
  bahkan tidak perlu mencetak array terurut -- cukup array frekuensinya
  saja (Day 40).
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

    vector<int> cnt(101, 0);                 // maks+1
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    string out;
    out.reserve(n * 4);                      // hindari realokasi berulang
    bool pertama = true;
    for (int v = 1; v <= 100; v++)
        while (cnt[v]--) {
            if (!pertama) out += ' ';
            out += to_string(v);
            pertama = false;
        }
    out += '\n';
    cout << out;

    return 0;
}
