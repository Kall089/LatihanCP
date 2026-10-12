# Two Pointers dan Sliding Window

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** dua jari yang hanya maju mengganti O(n²), asal syaratnya monoton.

Day ComprogLearning: **032** two pointers dan sliding window. Semua 0-based. Fungsi modular. `ll` untuk jumlah. Nilai negatif sering mematahkan window jumlah.

## Daftar isi

- [Two pointers berlawanan](#two-pointers-berlawanan)
- [Container with most water](#container-with-most-water)
- [Three sum](#three-sum)
- [Two pointers searah](#two-pointers-searah)
- [Sliding window ukuran tetap](#sliding-window-ukuran-tetap)
- [Sliding window terpanjang](#sliding-window-terpanjang)
- [Sliding window terpendek](#sliding-window-terpendek)
- [Paling banyak K jenis](#paling-banyak-k-jenis)
- [Kapan window gagal](#kapan-window-gagal)

---

## Two pointers berlawanan

> **Ide satu kalimat:** kiri kecil, kanan besar, array sudah urut; tiap langkah buang satu ujung.

### Two pointers berlawanan

**Teori:** Analoginya dua orang di ujung rak buku, mencari dua tebal yang jumlahnya tepat. Jika jumlah terlalu besar, orang kanan mundur (buang yang besar). Terlalu kecil, orang kiri maju. Alasan benar: array naik ⇒ keputusan monoton, setiap indeks paling sekali disentuh. Tanpa urut, langkah “buang kanan” tidak sah.

**Kapan:** Pakai two sum terurut, pair sum ≤ X. Jangan array acak tanpa sort. Sort merusak indeks — simpan pair nilai-indeks dulu.

**Proses:** `a = [1,2,4,7]`, target 6.

| L | R | a[L]+a[R] | aksi |
| ---: | ---: | ---: | --- |
| 0 | 3 | 8 | terlalu besar, R-- |
| 0 | 2 | 5 | terlalu kecil, L++ |
| 1 | 2 | 6 | ketemu |

1. L=0, R=3: 1+7=8 > 6 → R=2.
2. 1+4=5 < 6 → L=1.
3. 2+4=6. Indeks 1 dan 2.
4. Berhenti atau lanjut cari pasangan lain.
5. Tidak ada loop n².

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

pair<int, int> twoSumUrut(const vector<ll>& a, ll target) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        ll s = a[l] + a[r];
        if (s == target) return {l, r};
        if (s < target) l++;
        else r--;
    }
    return {-1, -1};
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 4, 7};
    auto [i, j] = twoSumUrut(a, 6);
    cout << i << ' ' << j << '\n'; // 1 2
    return 0;
}
```

**Jebakan:**
1. Array belum urut.
2. `l <= r` lalu pasangan elemen yang sama dua kali.
3. Overflow `a[l]+a[r]` tanpa `ll`.

**Kompleksitas:** O(n) setelah sort O(n log n), memori O(1).

---

## Container with most water

> **Ide satu kalimat:** lebar berkurang satu; buang tiang yang lebih pendek, karena dialah plafon sekarang.

### Container with most water

**Teori:** Analoginya dua dinding kolam: luas = lebar × min(tinggi kiri, tinggi kanan). Jika kamu buang dinding lebih tinggi, min tidak naik dan lebar turun — luas pasti tidak membaik. Jadi buang yang lebih pendek. Alasan benar: kandidat optimal tidak terlewat karena dinding tinggi tetap dipertahankan.

**Kapan:** Pakai LC 11, “dua garis menampung air”. Jangan sort — posisi adalah lebar. Jangan histogram rectangle (itu mono stack).

**Proses:** `h = [1,8,6,2,5,4,8,3,7]`.

1. L=0,R=8: min(1,7)×8=8. Buang 1.
2. L=1,R=8: min(8,7)×7=49. Buang 7.
3. Sekarang R=7, min(8,3)×6=18 < 49.
4. Terus sampai L>=R. Jawaban klasik 49.
5. Mini: `[1,1]` luas 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll airMaksimal(const vector<ll>& h) {
    int l = 0, r = (int)h.size() - 1;
    ll best = 0;
    while (l < r) {
        ll lebar = r - l;
        ll tinggi = min(h[l], h[r]);
        best = max(best, lebar * tinggi);
        if (h[l] < h[r]) l++;
        else r--;
    }
    return best;
}

int main() {
    FASTIO;
    cout << airMaksimal({1, 8, 6, 2, 5, 4, 8, 3, 7}) << '\n'; // 49
    cout << airMaksimal({1, 1}) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. Menggeser kedua pointer sekaligus — melewatkan kandidat.
2. `int` untuk `lebar * tinggi`.
3. Mengurut tinggi dan kehilangan posisi.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Three sum

> **Ide satu kalimat:** kunci satu angka, sisanya two sum pada ekor yang sudah urut.

### Three sum

**Teori:** Analoginya rapat tiga orang: kamu mengunci ketua, lalu dua anggota mencari pasangan di sisa kursi. Setelah sort, untuk tiap i, two pointers di `i+1..n-1`. Alasan O(n²): n kunci, tiap kunci sapu O(n). Duplikat dilewati supaya triplet unik.

**Kapan:** Pakai n≤4000 untuk O(n²), target tetap. Jangan n=1e5. Jangan tiga loop n³ pada n=1000 jika waktu 1 detik ketat — O(n²) lebih aman.

**Proses:** `a = [-1,0,1,2,-1,-4]`, target 0.

| i | a[i] | pasangan di kanan | triplet |
| ---: | ---: | --- | --- |
| 0 | -4 | tidak ada | - |
| 1 | -1 | 0+1, -1+2 | {-1,0,1}, {-1,-1,2} |
| 2 | -1 | (duplikat, lewati) | - |

1. Sort: `[-4,-1,-1,0,1,2]`.
2. Kunci -1 pertama: L,R menemukan dua triplet.
3. Kunci -1 kedua dilewati.
4. Jawaban dua triplet.
5. `i` berhenti di `n-3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<array<ll, 3>> threeSum(vector<ll> a, ll target) {
    sort(a.begin(), a.end());
    int n = (int)a.size();
    vector<array<ll, 3>> ans;
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] == a[i - 1]) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
            ll s = a[i] + a[l] + a[r];
            if (s == target) {
                ans.push_back({a[i], a[l], a[r]});
                l++;
                r--;
                while (l < r && a[l] == a[l - 1]) l++;
                while (l < r && a[r] == a[r + 1]) r--;
            } else if (s < target) l++;
            else r--;
        }
    }
    return ans;
}

int main() {
    FASTIO;
    auto ans = threeSum({-1, 0, 1, 2, -1, -4}, 0);
    cout << ans.size() << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Tidak skip duplikat — output berulang.
2. `l = i` memakai elemen yang sama dua kali tanpa izin.
3. Overflow tiga `int`.

**Kompleksitas:** O(n²) waktu, O(1) tambahan di luar jawaban.

---

## Two pointers searah

> **Ide satu kalimat:** kanan maju menambah barang, kiri maju membuang; keduanya tidak mundur.

### Two pointers searah

**Teori:** Analoginya pita konveyor: kamu hanya boleh geser jendela ke kanan. Jika syarat “jumlah ≤ K” dan elemen **non-negatif**, membuang kiri selalu memperkecil jumlah. Alasan O(n): tiap pointer naik paling n kali. Ada negatif? Jumlah bisa naik saat buang kiri — monoton rusak, kembali ke prefix+map.

**Kapan:** Pakai subarray positif + batas jumlah, unique count, longest dengan syarat monoton. Jangan nilai negatif untuk syarat jumlah.

**Proses:** `a = [1,2,3,1]`, jumlah ≤ 5, cari terpanjang.

| R | masuk | sum | L setelah shrink | panjang |
| ---: | ---: | ---: | ---: | ---: |
| 0 | 1 | 1 | 0 | 1 |
| 1 | 2 | 3 | 0 | 2 |
| 2 | 3 | 6→5 | 1 | 2 |
| 3 | 1 | 6→4 | 2 | 2 |

1. `[1,2,3]=6` terlalu besar.
2. Terpanjang 2.
3. Kandidat `[1,2]`, `[2,3]`, `[3,1]`.
4. Pointer tidak mundur.
5. Negatif akan merusak langkah shrink.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int terpanjangJumlahPaling(const vector<ll>& a, ll K) {
    int n = (int)a.size(), L = 0, best = 0;
    ll sum = 0;
    for (int R = 0; R < n; R++) {
        sum += a[R];
        while (L <= R && sum > K) {
            sum -= a[L];
            L++;
        }
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 3, 1};
    cout << terpanjangJumlahPaling(a, 5) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Negatif di array.
2. `while` tidak `L<=R` lalu L lewat R+1.
3. Update `best` sebelum menstabilkan jendela.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Sliding window ukuran tetap

> **Ide satu kalimat:** jendelanya lebar k; masuk satu, keluar satu.

### Sliding window ukuran tetap

**Teori:** Analoginya antrian kasir yang hanya menampung k orang: orang baru masuk, orang terdepan pergi. Jumlah jendela baru = jumlah lama + masuk − keluar. Alasan O(n): bukan O(nk). Kadane **bukan** ini; Kadane panjangnya bebas.

**Kapan:** Pakai “tepat k”, rata-rata k hari, max sum panjang k. Jangan k berubah-ubah. Jangan k>n tanpa penjaga.

**Proses:** `a = [2,1,5,1,3]`, k=3.

| Jendela | sum | best |
| --- | ---: | ---: |
| 2 1 5 | 8 | 8 |
| 1 5 1 | 7 | 8 |
| 5 1 3 | 9 | 9 |

1. Jendela pertama dihitung utuh.
2. Keluar 2, masuk 1.
3. Keluar 1, masuk 3.
4. Jawaban 9.
5. `best=0` salah jika semua negatif.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll maxJumlahPanjangK(const vector<ll>& a, int k) {
    int n = (int)a.size();
    if (k > n) return LLONG_MIN;
    ll sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    ll best = sum;
    for (int i = k; i < n; i++) {
        sum += a[i] - a[i - k];
        best = max(best, sum);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {2, 1, 5, 1, 3};
    cout << maxJumlahPanjangK(a, 3) << '\n'; // 9
    return 0;
}
```

**Jebakan:**
1. Keluar `a[i-k-1]` salah indeks.
2. `best` diinisialisasi 0 padahal semua negatif.
3. Pakai Kadane untuk “tepat k”.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Sliding window terpanjang

> **Ide satu kalimat:** pertahankan invariant “jendela sah”; raih panjang maksimum.

### Sliding window terpanjang

**Teori:** Analoginya tas belanja: masukkan barang selama masih muat, jika penuh keluarkan dari yang paling lama. Pola sama dengan two pointers searah. Alasan benar: untuk syarat yang **monoton** (jendela lebih lebar lebih “berat”), jendela terpanjang yang berakhir di R didapat dengan L seminimal mungkin yang masih sah.

**Kapan:** Pakai syarat monoton terhadap pelebaran. Jangan “jumlah = K” dengan negatif.

**Proses:** angka `[1,1,2,1,2,3]`, paling banyak 2 nilai berbeda.

1. `1,1,2,1,2` — jenis 2, panjang 5.
2. Masuk `3`: jenis 3, shrink dari kiri sampai sisa `2,3`.
3. Panjang setelah shrink = 2, tidak memecahkan 5.
4. Jawaban 5.
5. `best` diupdate setelah jendela sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int terpanjangPalingKUnik(const vector<ll>& a, int k) {
    int n = (int)a.size(), L = 0, best = 0, jenis = 0;
    map<ll, int> freq;
    for (int R = 0; R < n; R++) {
        if (++freq[a[R]] == 1) jenis++;
        while (jenis > k) {
            if (--freq[a[L]] == 0) jenis--;
            L++;
        }
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 1, 2, 1, 2, 3};
    cout << terpanjangPalingKUnik(a, 2) << '\n'; // 5
    return 0;
}
```

**Jebakan:**
1. Lupa kurangi `jenis` saat freq jadi 0.
2. `map` versus array 26 huruf — konstanta.
3. `best` dihitung saat masih invalid.

**Kompleksitas:** O(n log n) dengan map, O(n) dengan array alfabet; memori O(n).

---

## Sliding window terpendek

> **Ide satu kalimat:** yang terpendek = setelah jendela **baru saja** sah, catat, lalu coba gemukkan kiri.

### Sliding window terpendek

**Teori:** Analoginya minum air sampai haus hilang, lalu tanya “bisakah gelas lebih kecil?”. Kanan maju sampai syarat terpenuhi (jumlah ≥ S). Lalu kiri maju selama masih sah, tiap kali catat panjang. Alasan berbeda dari terpanjang: `best` diupdate **di dalam** setelah shrink, bukan setiap R.

**Kapan:** Pakai shortest subarray sum ≥ S (positif), minimum window substring. Jangan sum ≥ S dengan negatif — itu deque.

**Proses:** `a = [2,3,1,2,4,3]`, S=7.

| R | jendela setelah shrink sah | panjang | best |
| ---: | --- | ---: | ---: |
| 3 | 3,1,2 | 3 | 3 |
| 4 | 1,2,4 | 3 | 3 |
| 5 | 4,3 | 2 | 2 |

1. Pertama kali sah di `[2,3,1,2]`.
2. Shrink membuang 2 depan.
3. Akhirnya `[4,3]` panjang 2.
4. Return 0 jika tidak pernah sah.
5. Update `best` hanya di dalam `while` sah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int terpendekJumlahPaling(const vector<ll>& a, ll S) {
    int n = (int)a.size(), L = 0, best = n + 1;
    ll sum = 0;
    for (int R = 0; R < n; R++) {
        sum += a[R];
        while (L <= R && sum >= S) {
            best = min(best, R - L + 1);
            sum -= a[L];
            L++;
        }
    }
    return (best == n + 1) ? 0 : best;
}

int main() {
    FASTIO;
    vector<ll> a = {2, 3, 1, 2, 4, 3};
    cout << terpendekJumlahPaling(a, 7) << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Update `best` di luar `while` (jendela bisa belum sah).
2. Return `n+1` tanpa sentinel.
3. Negatif: window boleh perlu memanjang setelah shrink — salah alat.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Paling banyak K jenis

> **Ide satu kalimat:** jenis adalah beban; freq jadi 0 berarti satu jenis benar-benar pergi.

### Paling banyak K jenis

**Teori:** Analoginya tas buah: kamu boleh K rasa. Masuk apel baru jika belum ada = jenis+1. Keluar apel terakhir = jenis-1. Alasan orang WA: mereka `--freq` tetapi lupa `jenis--` saat freq 0, atau menghapus kunci map tanpa menyesuaikan counter.

**Kapan:** Pakai “at most K distinct”, longest substring K unique. Jangan “tepat K” tanpa menyesuaikan update `best` (hanya catat saat `jenis==K`).

**Proses:** `a = [1,2,1,2,3]`, k=2, tepat 2 jenis.

1. Jendela tumbuh sampai jenis 2: `[1,2]`, `[1,2,1]`, `[1,2,1,2]`.
2. Masuk 3: jenis 3, shrink buang 1,1,2 sampai `[2,3]`.
3. Terpanjang tepat 2 = 4.
4. Untuk “paling banyak 2”, jawaban sama 4.
5. Untuk “paling banyak 1”, jawaban 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int terpanjangTepatKJenis(const vector<ll>& a, int k) {
    int L = 0, best = 0, jenis = 0;
    map<ll, int> freq;
    for (int R = 0; R < (int)a.size(); R++) {
        if (++freq[a[R]] == 1) jenis++;
        while (jenis > k) {
            if (--freq[a[L]] == 0) jenis--;
            L++;
        }
        if (jenis == k) best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    FASTIO;
    vector<ll> a = {1, 2, 1, 2, 3};
    cout << terpanjangTepatKJenis(a, 2) << '\n'; // 4
    cout << terpanjangTepatKJenis(a, 1) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `best` diupdate meski `jenis < k` saat soal minta tepat K.
2. `freq.erase` tanpa `jenis--`.
3. k=0 tidak dijaga.

**Kompleksitas:** O(n log n) dengan map, memori O(n).

---

## Kapan window gagal

> **Ide satu kalimat:** jika membuang kiri bisa membuat syarat **lebih berat**, jari monoton sudah mati.

### Kapan window gagal

**Teori:** Analoginya tas yang isinya kadang batu, kadang balon helium: mengeluarkan barang tidak selalu membuat tas lebih ringan. Jumlah dengan negatif, produk, dan “subarray XOR = K” tidak monoton terhadap lebar. Alasan benar: two pointers butuh “jendela lebih lebar ⇒ lebih sulit / lebih mudah” secara konsisten. Jika tidak, pakai prefix+map, deque, atau Kadane.

**Kapan:** Pakai tes ini sebelum coding window. Jangan memaksa window pada array campur tanda hanya karena n=2e5.

**Proses:** `a = [2, -3, 4]`, cari jumlah ≤ 3.

1. `[2]` sah.
2. `[2,-3]` jumlah -1 sah, lebih lebar lebih kecil — aneh untuk “≤”.
3. `[2,-3,4]` jumlah 3 sah.
4. Jika kamu shrink karena suatu saat sum besar, membuang `-3` justru menaikkan sum.
5. Window “sum ≤ K” rusak. Prefix+map atau naif kecil yang benar.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool windowAmanUntukJumlah(const vector<ll>& a) {
    for (ll x : a) if (x < 0) return false;
    return true;
}

int main() {
    FASTIO;
    cout << windowAmanUntukJumlah({1, 2, 3}) << '\n';    // 1
    cout << windowAmanUntukJumlah({2, -3, 4}) << '\n'; // 0
    return 0;
}
```

**Jebakan:**
1. Melihat n=2e5 lalu otomatis window.
2. “Jumlah = K” dengan negatif memakai shrink.
3. Mengira XOR window selalu monoton.

**Kompleksitas:** tes O(n); algoritma pengganti biasanya O(n log n).

---

## Ringkasan

- Berlawanan: array urut, buang satu ujung.
- Searah: kedua pointer hanya maju.
- Tetap k: masuk satu keluar satu.
- Terpanjang: update `best` setiap R setelah sah.
- Terpendek: update `best` di dalam shrink.
- Negatif membunuh window jumlah; pakai prefix+map.

Lanjut: [Kadane](kadane.md).
