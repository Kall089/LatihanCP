# 04 — Kadane, monotonic stack/deque, kompresi

[← Prefix dan window](03-prefix-diff-twopointer-window.md) · [README dasar](README-dasar.md) · [Lanjut sorting dan search →](05-sorting-binsearch-ternary-mitm.md)

> **Ide satu kalimat:** buang informasi yang sudah pasti kalah — prefix negatif, orang lebih pendek di belakang, kursi 10⁹ yang tidak pernah diduduki.

Day ComprogLearning: **035** Kadane, **036** monotonic stack, **037** monotonic deque, **038** kompresi koordinat.

Semua 0-based. Fungsi modular. `ll` untuk jumlah.

## Daftar isi

- [Kadane](#kadane)
- [Kadane beserta indeks](#kadane-beserta-indeks)
- [Kadane melingkar](#kadane-melingkar)
- [Subarray jumlah minimum](#subarray-jumlah-minimum)
- [Maximum product subarray](#maximum-product-subarray)
- [Next Greater Element](#next-greater-element)
- [Previous Smaller Element](#previous-smaller-element)
- [Histogram persegi panjang](#histogram-persegi-panjang)
- [Trapping rain water](#trapping-rain-water)
- [Sliding window maximum](#sliding-window-maximum)
- [Sliding window minimum](#sliding-window-minimum)
- [Kompresi koordinat](#kompresi-koordinat)
- [Kompresi interval dan r+1](#kompresi-interval-dan-r1)

---

## Kadane

> **Ide satu kalimat:** kalau beban dari belakang sudah negatif, buang saja.

### Kadane

**Teori:** Analoginya membawa tas di trek pendakian: jika isi tas sudah merugikan, lebih baik tas baru di titik ini. Sliding window gagal karena elemen negatif mematahkan monoton. Dua sudut setara: (1) DP, (2) prefix minus prefix minimum di kiri. Alasan DP benar: subarray terbaik yang **berakhir di i** hanya dua pilihan — mulai baru di i, atau sambung dari i-1.

**State:** `cur[i]` = jumlah subarray terbaik yang berakhir di i. `best` = maksimum semua `cur`.
**Transisi:** `cur = max(a[i], cur + a[i])`, `best = max(best, cur)`.

Inisialisasi: `best = LLONG_MIN` jika subarray **tidak boleh kosong**. `best = 0` jika boleh kosong.

**Kapan dipakai / kapan tidak.** Pakai maximum subarray bebas panjang. Jangan jika panjang dibatasi (window / deque prefix). Jangan `best=0` saat wajib ada elemen.

**Proses:** `a = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`.

1. i=0: cur=-2, best=-2.
2. i=1: max(1, -2+1)=1, best=1.
3. i=2: max(-3, 1-3)=-2, best=1.
4. i=3: max(4, -2+4)=4, best=4.
5. i=4: 3, best=4. i=5: 5. i=6: 6, best=6 (`4,-1,2,1`). i=7: 1. i=8: 5. Jawaban 6.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll kadane(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MIN; // tidak boleh kosong
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

int main() {
    vector<ll> a = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << kadane(a) << '\n'; // 6
    vector<ll> b = {-5, -2, -3};
    cout << kadane(b) << '\n'; // -2
    return 0;
}
```

**Jebakan:**
1. `best = 0` pada array semua negatif.
2. Overflow `int`.
3. Mengira Kadane bisa “panjang ≤ k”.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane beserta indeks

> **Ide satu kalimat:** catat kapan kamu memutuskan “tas baru”, itu kiri; kanan selalu i saat `best` pecah.

### Kadane beserta indeks

**Teori:** Analoginya besides berat tas, kamu butuh foto start dan finish. `curL` berubah **hanya** saat `x > cur+x` (mulai baru). Saat `cur > best`, simpan `[curL, i]`. Alasan tie-break: kalau soal minta paling kiri, update `best` hanya saat `cur > best`, bukan `>=`.

**Kapan dipakai / kapan tidak.** Pakai rekonstruksi. Jangan update `curL` setiap iterasi.

**Proses:** `a = [1, -2, 3, 1]`.

1. i=0: cur=1, mulai 0, best=1, `[0,0]`.
2. i=1: 1-2=-1, vs -2 → cur=-1, masih sambung? max(-2, -1)=-1, tidak mulai baru. best tetap 1.
3. i=2: max(3, -1+3)=3, 3> -1+3? 3==3, `max(x,cur+x)` jika kita tulis `x > cur+x` maka mulai baru saat cur<0. cur sebelum = -1 <0, jadi mulai di 2. best=3, `[2,2]`.
4. i=3: 3+1=4 > 1, sambung, best=4, `[2,3]`.
5. Jawaban nilai 4, indeks 2..3.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Segmen {
    ll nilai;
    int l, r; // 0-based inklusif
};

Segmen kadanePosisi(const vector<ll>& a) {
    ll cur = a[0], best = a[0];
    int curL = 0, bestL = 0, bestR = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (cur < 0) { // mulai baru
            cur = a[i];
            curL = i;
        } else cur += a[i];
        if (cur > best) {
            best = cur;
            bestL = curL;
            bestR = i;
        }
    }
    return {best, bestL, bestR};
}

int main() {
    vector<ll> a = {1, -2, 3, 1};
    auto s = kadanePosisi(a);
    cout << s.nilai << ' ' << s.l << ' ' << s.r << '\n'; // 4 2 3
    return 0;
}
```

**Jebakan:**
1. `curL = i` setiap langkah.
2. Tie `>=` vs `>` tidak sesuai soal.
3. `n=1` terlewat jika loop dari 0 tanpa inisialisasi.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Kadane melingkar

> **Ide satu kalimat:** subarray melingkar = total minus lubang (subarray minimum) di tengah.

### Kadane melingkar

**Teori:** Analoginya kalung manik: potongan terbaik yang nyambung ujung-ujung sama dengan “buang sepotong terburuk di tengah”. `max(kadaneBiasa, total - kadaneMin)`. Lubang: jika semua negatif, `total - minSum` = 0 = array kosong — **dilarang**. Kembalikan Kadane biasa (elemen terbesar).

**Kapan dipakai / kapan tidak.** Pakai LC 918. Jangan tanpa penjaga semua-negatif.

**Proses:** `a = [5, -3, 5]`.

1. Kadane biasa: 5, 5-3=2, 2+5=7. best=7 (seluruh).
2. total=7. Min-subarray: -3. `total-(-3)=10` yaitu `[5] + [5]` nyambung.
3. Jawaban 10.
4. `a = [-2,-1,-3]`: Kadane=-1. `total-minSum=0` kosong → jawab −1.
5. Penjaga wajib.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll kadaneMax(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MIN;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

ll kadaneMin(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MAX;
    for (ll x : a) {
        cur = min(x, cur + x);
        best = min(best, cur);
    }
    return best;
}

ll kadaneMelingkar(const vector<ll>& a) {
    ll biasa = kadaneMax(a);
    ll total = 0;
    for (ll x : a) total += x;
    ll cand = total - kadaneMin(a);
    // semua negatif: circular jadi kosong (0), dilarang
    if (biasa < 0) return biasa;
    return max(biasa, cand);
}

int main() {
    cout << kadaneMelingkar({5, -3, 5}) << '\n';    // 10
    cout << kadaneMelingkar({-2, -1, -3}) << '\n'; // -1
    return 0;
}
```

**Jebakan:**
1. Lupa semua-negatif.
2. `total` overflow.
3. Min Kadane dengan `best=0`.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Subarray jumlah minimum

> **Ide satu kalimat:** Kadane pada `−a`, atau transisi `min` bukan `max`.

### Subarray jumlah minimum

**Teori:** Analoginya tas yang ingin **paling ringan** (bisa negatif: utang besar). Transisi cermin. Alasan benar: struktur subarray sama. Dipakai di rumus melingkar dan “buang potongan terburuk”.

**Kapan dipakai / kapan tidak.** Pakai lubang kalung, “kerugian terbesar”. Jangan campur inisialisasi `best=0` jika wajib nonempty.

**Proses:** `a = [3, -2, 4, -5, 1]`.

1. cur=3, best=3.
2. min(-2, 3-2)=-2, best=-2.
3. min(4, -2+4)=2, best=-2.
4. min(-5, 2-5)=-5, best=-5.
5. min(1, -5+1)=-4, best=-5. Jawaban −5 (satu elemen).

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll kadaneMinimum(const vector<ll>& a) {
    ll cur = 0, best = LLONG_MAX;
    for (ll x : a) {
        cur = min(x, cur + x);
        best = min(best, cur);
    }
    return best;
}

int main() {
    vector<ll> a = {3, -2, 4, -5, 1};
    cout << kadaneMinimum(a) << '\n'; // -5
    return 0;
}
```

**Jebakan:**
1. `best=0`.
2. Negasi overflow `INT_MIN`.
3. Lupa nonempty.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Maximum product subarray

> **Ide satu kalimat:** dua negatif jadi positif; jadi kamu harus membawa **minimum** juga.

### Maximum product subarray

**Teori:** Analoginya hutang kali hutang = kekayaan. Satu variabel `curMax` kalah saat `-2 * (-5)`. Saat `x<0`, max dan min bertukar peran. Alasan benar: hasil kali terbaik/buruk yang berakhir di i hanya dari `{x, curMax*x, curMin*x}`.

**State:** `mx, mn` produk max/min berakhir di sini.
**Transisi:** jika `x<0` tukar `mx`/`mn` dulu, lalu `mx=max(x, mx*x)`, `mn=min(x, mn*x)`.

**Kapan dipakai / kapan tidak.** Pakai LC 152. Jangan Kadane jumlah. Hati-hati overflow — di kontes sering modulo atau nilai kecil.

**Proses:** `a = [2, 3, -2, 4]`.

1. mx=2, mn=2, best=2.
2. x=3: mx=max(3,2·3)=6, mn=min(3,2·3)=3, best=6.
3. x=-2 < 0: tukar mx↔mn menjadi (3,6). mx=max(-2,3·-2)=-2, mn=min(-2,6·-2)=-12. best tetap 6.
4. x=4: mx=max(4,-2·4)=4, mn=min(4,-12·4)=-48. best=max(6,4)=6 yaitu `[2,3]`.
5. Kasus `[2,-5,-2]`: dua negatif menghidupkan rantai, jawaban 20.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll maxProduk(const vector<ll>& a) {
    ll mx = a[0], mn = a[0], best = a[0];
    for (int i = 1; i < (int)a.size(); i++) {
        ll x = a[i];
        if (x < 0) swap(mx, mn);
        mx = max(x, mx * x);
        mn = min(x, mn * x);
        best = max(best, mx);
    }
    return best;
}

int main() {
    cout << maxProduk({2, 3, -2, 4}) << '\n'; // 6
    cout << maxProduk({2, -5, -2}) << '\n';   // 20
    return 0;
}
```

**Jebakan:**
1. Satu variabel.
2. Nol mematahkan rantai — rumus `max(x, mx*x)` sudah mulai baru.
3. Overflow.

**Kompleksitas:** O(n) waktu, O(1) memori.

---

## Next Greater Element

> **Ide satu kalimat:** tumpukan orang menghadap kanan; yang lebih pendek menengadah ke orang baru, lalu turun.

### Next Greater Element

**Teori:** Analoginya antrean melihat ke kanan siapa yang pertama lebih tinggi. Stack **menurun** (nilai dari dasar ke puncak turun, atau kita simpan indeks dengan `a[st.top()]` menurun ke puncak). Orang baru i: selama puncak lebih kecil, NGE puncak = a[i], pop. Alasan O(n): tiap indeks push sekali, pop sekali. Yang tersisa tidak punya NGE (−1).

**State:** stack indeks dengan `a` monoton menurun ke puncak.
**Transisi:** pop semua yang kalah, lalu push i.

**Kapan dipakai / kapan tidak.** Pakai NGE, daily temperature, stock span. Jangan brute O(n²) pada n=1e5.

**Proses:** `a = [2, 1, 2, 4, 3]`.

1. i=0: stack `[0]`.
2. i=1: 1<2, tidak pop. stack `[0,1]`.
3. i=2: 2>1, nge[1]=2, pop. 2==2 tidak pop. stack `[0,2]`.
4. i=3: 4>2, nge[2]=4, pop. 4>2, nge[0]=4, pop. stack `[3]`.
5. i=4: 3<4. stack `[3,4]`. Sisa nge = −1. Hasil: `[4,2,4,-1,-1]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> nextGreater(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> nge(n, -1);
    vector<int> st; // indeks, a menurun ke puncak
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) {
            nge[st.back()] = a[i];
            st.pop_back();
        }
        st.push_back(i);
    }
    return nge;
}

int main() {
    auto nge = nextGreater({2, 1, 2, 4, 3});
    for (int i = 0; i < 5; i++) cout << nge[i] << " \n"[i == 4];
    // 4 2 4 -1 -1
    return 0;
}
```

**Jebakan:**
1. `<=` vs `<` (NGE ketat atau tidak).
2. Push nilai, bukan indeks, lalu butuh posisi.
3. `st.top()` tanpa empty.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Previous Smaller Element

> **Ide satu kalimat:** NGE yang diputar: jalan dari kiri, cari yang lebih kecil di belakang.

### Previous Smaller Element

**Teori:** Analoginya melihat ke kiri, tiang pertama yang lebih pendek. Stack **meningkat** ke puncak. CSES Nearest Smaller Values. Alasan sama: tiap elemen sekali masuk-keluar. Histogram memakai PSE + NSE untuk lebar.

**Kapan dipakai / kapan tidak.** Pakai nearest smaller, histogram. Jangan tertukar arah loop.

**Proses:** `a = [2, 1, 2, 4, 3]`, PSE ketat, indeks (bukan nilai), −1 jika tidak ada.

1. i=0: kosong, pse=−1. stack `[0]`.
2. i=1: 1<2 pop 0, kosong, pse=−1. stack `[1]`.
3. i=2: 2>1, pse=1. stack `[1,2]`.
4. i=3: 4>2, pse=2. stack `[1,2,3]`.
5. i=4: 3<4 pop 3, 3>2, pse=2. stack `[1,2,4]`. Indeks: `-1,-1,1,2,2`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> prevSmallerIdx(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> pse(n, -1);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) pse[i] = st.back();
        st.push_back(i);
    }
    return pse;
}

int main() {
    auto pse = prevSmallerIdx({2, 1, 2, 4, 3});
    for (int i = 0; i < 5; i++) cout << pse[i] << " \n"[i == 4];
    // -1 -1 1 2 2
    return 0;
}
```

**Jebakan:**
1. `>` vs `>=` mengubah “equal nearest”.
2. Mengembalikan nilai padahal soal minta indeks 1-based.
3. Loop dari kanan tanpa mengubah makna.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Histogram persegi panjang

> **Ide satu kalimat:** tiap batang jadi tinggi plafon; lebarnya sampai tetangga yang lebih pendek.

### Histogram persegi panjang

**Teori:** Analoginya gedung-gedung: persegi terlebar dengan atap h[i] dibatasi gedung pertama lebih rendah di kiri dan kanan. Lebar = `R - L - 1`. Alasan O(n): L dari PSE, R dari NSE. Versi satu pass: stack meningkat, saat pop, kanan = i, kiri = stack baru.

**Kapan dipakai / kapan tidak.** Pakai LC 84, maximal rectangle (LC 85) setelah dipadatkan jadi histogram per baris. Jangan O(n²) n=1e5.

**Proses:** `h = [2, 1, 5, 6, 2, 3]`.

1. Batang 5 (indeks 2): kiri lebih kecil =1 (nilai 1), kanan lebih kecil =4 (nilai 2). Lebar 4-1-1=2. Luas 10.
2. Batang 6: kiri 2, kanan 4, lebar 1, luas 6.
3. Batang 2 di indeks 4: bisa melebar ke 2..5? PSE/NSE hitung. Jawaban klasik 10.
4. Sentinel 0 di ujung memaksa pop sisa.
5. `W = st.empty() ? i : i - st.top() - 1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll largestRectangle(vector<ll> h) {
    h.push_back(0); // sentinel: paksa pop
    vector<int> st;
    ll best = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.back()] > h[i]) {
            ll H = h[st.back()];
            st.pop_back();
            ll L = st.empty() ? -1 : st.back();
            ll W = i - L - 1;
            best = max(best, H * W);
        }
        st.push_back(i);
    }
    return best;
}

int main() {
    cout << largestRectangle({2, 1, 5, 6, 2, 3}) << '\n'; // 10
    return 0;
}
```

**Jebakan:**
1. Lebar `i - st.top()` tanpa −1.
2. Sentinel lupa → batang terakhir tidak dihitung.
3. `int` untuk `H*W`.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Trapping rain water

> **Ide satu kalimat:** air di i = max(0, min(pagar kiri, pagar kanan) − tinggi i).

### Trapping rain water

**Teori:** Analoginya lorong: air tidak lebih tinggi dari pagar terendah di kedua sisi. `leftMax[i]` / `rightMax[i]` dua sapuan. Versi dua pointer O(1) memori: sisi yang pagarnya lebih rendah menentukan air. Alasan benar: air di i hanya bergantung ekstrem kiri-kanan, bukan jumlah.

**Kapan dipakai / kapan tidak.** Pakai LC 42. Jangan histogram luas (itu beda soal). Stack juga bisa: pop lembah.

**Proses:** `h = [0,1,0,2,1,0,1,3,2,1,2,1]`. Jawaban klasik 6.

Mini: `h = [2,0,2]`.

1. i=1: leftMax=2, rightMax=2, air=2.
2. Ujung tidak menampung.
3. Total 2.
4. `h = [3,0,1]`: min(3,1)-0=1 di tengah? rightMax di indeks 1 adalah 1. Air 1. Indeks 2 ujung 0.
5. Total 1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll trapAir(const vector<ll>& h) {
    int n = (int)h.size();
    if (n == 0) return 0;
    vector<ll> L(n), R(n);
    L[0] = h[0];
    for (int i = 1; i < n; i++) L[i] = max(L[i - 1], h[i]);
    R[n - 1] = h[n - 1];
    for (int i = n - 2; i >= 0; i--) R[i] = max(R[i + 1], h[i]);
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += max(0LL, min(L[i], R[i]) - h[i]);
    return ans;
}

int main() {
    cout << trapAir({2, 0, 2}) << '\n'; // 2
    cout << trapAir({3, 0, 1}) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. `leftMax` tidak memuat diri sendiri — tetap aman karena `min-h` jadi 0.
2. Overflow.
3. Menghitung volume 2D sebagai histogram rectangle.

**Kompleksitas:** O(n) waktu, O(n) memori (bisa O(1) two pointers).

---

## Sliding window maximum

> **Ide satu kalimat:** deque menyimpan kandidat menurun; yang lebih tua dan lebih pendek tidak pernah juara lagi.

### Sliding window maximum

**Teori:** Analoginya antrean juara jendela: orang di belakang yang lebih pendek dari pendatang baru tidak akan jadi max selama pendatang masih ada, jadi diusir dari belakang. Orang di depan yang sudah keluar jendela diusir dari depan. Alasan O(n): tiap indeks push/pop ≤ sekali. Inilah Day 037.

**State:** deque indeks, `a[dq]` **menurun**. Depan = max jendela.
**Transisi:** pop belakang yang ≤ a[i]; pop depan yang `< i-k+1`; push i.

**Kapan dipakai / kapan tidak.** Pakai window max/min, DP dengan transisi “max di `[i-k, i-1]`”. Jangan `multiset` jika O(n log n) terasa sayang — deque O(n). Jangan Kadane untuk panjang tetap.

**Proses:** `a = [1,3,-1,-3,5,3,6,7]`, k=3.

1. i=0: dq=[0].
2. i=1: 3>1 pop 0, dq=[1].
3. i=2: -1<3, dq=[1,2]. Jendela penuh, max=3.
4. i=3: -3, dq=[1,2,3]. Depan 1 masih di jendela. max=3.
5. i=4: 5 pop semua, dq=[4]. max=5. Lanjut: 5,6,7. Jawaban `3,3,5,5,6,7`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> windowMax(const vector<ll>& a, int k) {
    deque<int> dq;
    vector<ll> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}

int main() {
    auto ans = windowMax({1, 3, -1, -3, 5, 3, 6, 7}, 3);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    // 3 3 5 5 6 7
    return 0;
}
```

**Jebakan:**
1. Simpan nilai, bukan indeks — tidak tahu kapan keluar.
2. Pop depan dengan `== i-k` salah (pakai `<= i-k`).
3. Cetak sebelum jendela penuh.

**Kompleksitas:** O(n) waktu, O(k) memori.

---

## Sliding window minimum

> **Ide satu kalimat:** deque menaik; depan selalu yang paling pendek di jendela.

### Sliding window minimum

**Teori:** Cermin window max. Pop belakang yang ≥ a[i]. Dipakai “min di jendela”, shortest subarray sum ≥ K dengan prefix (beda file), max-min ≤ X.

**Kapan dipakai / kapan tidak.** Pakai min jendela. Jangan dua `multiset` jika deque cukup.

**Proses:** `a = [1,3,-1,-3,5]`, k=3.

1. i=0: [0].
2. i=1: 3>1, dq=[0,1].
3. i=2: -1 pop 1 dan 0, dq=[2], min=-1.
4. i=3: -3 pop 2, dq=[3], min=-3.
5. i=4: 5, dq=[3,4], depan 3 masih masuk? i-k=1, 3>1 ya. min=-3. Hasil `-1,-3,-3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> windowMin(const vector<ll>& a, int k) {
    deque<int> dq;
    vector<ll> ans;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
        if (i >= k - 1) ans.push_back(a[dq.front()]);
    }
    return ans;
}

int main() {
    auto ans = windowMin({1, 3, -1, -3, 5}, 3);
    for (int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << " \n"[i + 1 == (int)ans.size()];
    // -1 -3 -3
    return 0;
}
```

**Jebakan:**
1. Tertukar `<=` max dengan min.
2. Window max-min: butuh **dua** deque.
3. k=1 lupa.

**Kompleksitas:** O(n) waktu, O(k) memori.

---

## Kompresi koordinat

> **Ide satu kalimat:** nilai boleh 10⁹, tapi kalau n cuma 10⁵, beri mereka nomor kursi 0..n-1.

### Kompresi koordinat

**Teori:** Analoginya bioskop: tiket bertuliskan “kursi 1.000.000.007” tidak berguna jika hanya 5 orang datang — beri kursi 0..4 menurut urutan tiket. Idiom: `sort`, `unique+erase`, `lower_bound`. Alasan benar: urutan terjaga (`a<b` ⇒ `id[a]<id[b]`), **jarak hancur** (`b-a` bukan `id[b]-id[a]`). `unique` tanpa `erase` meninggalkan ekor.

**Kapan dipakai / kapan tidak.** Pakai Fenwick/segtree/array freq pada nilai 1e9. Jangan jika rumus butuh jarak asli (panjang interval di sumbu). Jangan tanpa `erase`.

**Proses:** `a = [100, 1, 100, 50]`.

1. Salin, sort: `1,50,100,100`.
2. unique+erase: `1,50,100`.
3. 100 → indeks 2, 1 → 0, 50 → 1.
4. Array terkompres: `2,0,2,1`.
5. `freq[3]` cukup, bukan `freq[101]`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Kompres {
    vector<ll> v;
    void bangun(vector<ll> a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        v = a;
    }
    int id(ll x) const { // 0-based
        return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
    }
    int size() const { return (int)v.size(); }
};

int main() {
    vector<ll> a = {100, 1, 100, 50};
    Kompres kp;
    kp.bangun(a);
    cout << kp.size() << '\n'; // 3
    cout << kp.id(100) << ' ' << kp.id(1) << ' ' << kp.id(50) << '\n'; // 2 0 1
    return 0;
}
```

**Jebakan:**
1. `unique` tanpa `erase`.
2. `id` pada nilai yang tidak pernah di-`bangun`.
3. Mengira selisih id = selisih nilai.

**Kompleksitas:** bangun O(n log n), query O(log n), memori O(n).

---

## Kompresi interval dan r+1

> **Ide satu kalimat:** titik tutup interval harus punya kursi sendiri, atau sapuan `−1` menumpuk di hari yang masih aktif.

### Kompresi interval dan r+1

**Teori:** Analoginya hotel: tamu check-out pagi hari R+1, bukan malam R — kamar R masih terisi. Saat menandai `+1` di L dan `−1` di R+1 pada sumbu terkompres, **R+1 harus ada di daftar kursi**. Alasan WA: hanya memasukkan L dan R, lalu `id(R+1)` jatuh ke nilai berikutnya yang salah atau `end()`.

Jenis A: buang duplikat (nilai unik). Jenis B: peringkat penuh (dua 100 dapat id berbeda jika diminta rank).

**Kapan dipakai / kapan tidak.** Pakai sweep interval, count overlapping. Jangan kompres jika kamu menjumlah **panjang asli** — pakai nilai asli pada sumbu.

**Proses:** interval `[1,3]`, `[3,4]` inklusif, hitung berapa interval di tiap titik integer.

1. Titik penting: 1,3,4 dan 3+1=4, 4+1=5. Unik: 1,3,4,5.
2. `+1` di 1, `−1` di 4 untuk interval pertama (habis setelah 3).
3. `+1` di 3, `−1` di 5.
4. Sweep: pos1:1, pos3:2, pos4:1, pos5:0.
5. Tanpa kursi 5, `−1` kedua hilang.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> titikPenting(const vector<pair<ll, ll>>& seg) {
    vector<ll> v;
    for (auto [L, R] : seg) {
        v.push_back(L);
        v.push_back(R);
        v.push_back(R + 1); // wajib
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}

int idOf(const vector<ll>& v, ll x) {
    return (int)(lower_bound(v.begin(), v.end(), x) - v.begin());
}

vector<int> sapuan(const vector<pair<ll, ll>>& seg) {
    auto v = titikPenting(seg);
    vector<int> d(v.size() + 1, 0);
    for (auto [L, R] : seg) {
        d[idOf(v, L)]++;
        d[idOf(v, R + 1)]--;
    }
    for (int i = 1; i < (int)d.size(); i++) d[i] += d[i - 1];
    return d;
}

int main() {
    vector<pair<ll, ll>> seg = {{1, 3}, {3, 4}};
    auto d = sapuan(seg);
    auto v = titikPenting(seg); // 1 3 4 5
    cout << d[idOf(v, 1)] << ' ' << d[idOf(v, 3)] << ' ' << d[idOf(v, 4)] << '\n';
    // 1 2 1
    return 0;
}
```

**Jebakan:**
1. Lupa `R+1` di daftar.
2. Interval setengah terbuka vs inklusif tertukar.
3. Menjumlah overlap × 1 alih-alih × panjang asli.

**Kompleksitas:** O(n log n) bangun, O(n) sapuan, memori O(n).

---

## Ringkasan file 04

- Kadane: `cur = max(x, cur+x)`, tanya “boleh kosong?”.
- Melingkar: `total - min`, jaga semua-negatif.
- Produk: bawa min dan max.
- Stack monoton = NGE/NSE O(n).
- Histogram: lebar `i-L-1`.
- Deque menurun = window max O(n).
- Kompresi: urutan hidup, jarak mati; `unique`+`erase`; interval butuh `R+1`.

Lanjut: [05 — merge, binary search, ternary, interaktif, MITM](05-sorting-binsearch-ternary-mitm.md).
