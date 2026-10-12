# Monotonic Stack dan Deque

[← README](README.md) · [Indeks CP](../README.md)

> **Ide satu kalimat:** buang orang yang sudah pasti kalah — yang lebih pendek di belakang tidak akan jadi juara lagi.

Day ComprogLearning: **036** monotonic stack, **037** monotonic deque. Semua 0-based. Fungsi modular. `ll` untuk luas dan jumlah.

## Daftar isi

- [Next Greater Element](#next-greater-element)
- [Previous Smaller Element](#previous-smaller-element)
- [Next Smaller Element](#next-smaller-element)
- [Previous Greater Element](#previous-greater-element)
- [Histogram persegi panjang](#histogram-persegi-panjang)
- [Trapping rain water](#trapping-rain-water)
- [Sliding window maximum](#sliding-window-maximum)
- [Sliding window minimum](#sliding-window-minimum)
- [Max minus min pada window](#max-minus-min-pada-window)

---

## Next Greater Element

> **Ide satu kalimat:** tumpukan orang menghadap kanan; yang lebih pendek menengadah ke orang baru, lalu turun.

### Next Greater Element

**Teori:** Analoginya antrean melihat ke kanan siapa yang pertama lebih tinggi. Stack **menurun** (nilai dari dasar ke puncak turun). Orang baru i: selama puncak lebih kecil, NGE puncak = a[i], pop. Alasan O(n): tiap indeks push sekali, pop sekali. Yang tersisa tidak punya NGE (−1).

**Kapan:** Pakai NGE, daily temperature, stock span. Jangan brute O(n²) pada n=1e5.

**Proses:** `a = [2, 1, 2, 4, 3]`.

| i | a[i] | pop | nge yang terisi | stack indeks |
| ---: | ---: | --- | --- | --- |
| 0 | 2 | - | - | 0 |
| 1 | 1 | - | - | 0,1 |
| 2 | 2 | 1 | nge[1]=2 | 0,2 |
| 3 | 4 | 2,0 | nge[2]=4, nge[0]=4 | 3 |
| 4 | 3 | - | - | 3,4 |

1. Hasil nilai: `[4,2,4,-1,-1]`.
2. `<=` versus `<` mengubah kembar.
3. Simpan indeks, bukan hanya nilai, jika butuh posisi.
4. Sisa stack = −1.
5. Satu sapu cukup.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<ll> nextGreater(const vector<ll>& a) {
    int n = (int)a.size();
    vector<ll> nge(n, -1);
    vector<int> st;
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
    FASTIO;
    auto nge = nextGreater({2, 1, 2, 4, 3});
    for (int i = 0; i < 5; i++) cout << nge[i] << " \n"[i == 4];
    // 4 2 4 -1 -1
    return 0;
}
```

**Jebakan:**
1. `<=` versus `<` (NGE ketat atau tidak).
2. Push nilai, bukan indeks, lalu butuh posisi.
3. `st.back()` tanpa empty.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Previous Smaller Element

> **Ide satu kalimat:** NGE yang diputar: jalan dari kiri, cari yang lebih kecil di belakang.

### Previous Smaller Element

**Teori:** Analoginya melihat ke kiri, tiang pertama yang lebih pendek. Stack **meningkat** ke puncak. CSES Nearest Smaller Values. Alasan sama: tiap elemen sekali masuk-keluar. Histogram memakai PSE + NSE untuk lebar.

**Kapan:** Pakai nearest smaller, histogram. Jangan tertukar arah loop.

**Proses:** `a = [2, 1, 2, 4, 3]`, PSE ketat, indeks, −1 jika tidak ada.

| i | a[i] | pop | pse[i] | stack |
| ---: | ---: | --- | ---: | --- |
| 0 | 2 | - | -1 | 0 |
| 1 | 1 | 0 | -1 | 1 |
| 2 | 2 | - | 1 | 1,2 |
| 3 | 4 | - | 2 | 1,2,3 |
| 4 | 3 | 3 | 2 | 1,2,4 |

1. Indeks: `-1,-1,1,2,2`.
2. Nilai PSE: tidak ada, tidak ada, 1, 2, 2.
3. `>=` membuang yang sama tinggi.
4. Soal 1-based menambah 1 saat cetak.
5. Loop dari kiri.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    auto pse = prevSmallerIdx({2, 1, 2, 4, 3});
    for (int i = 0; i < 5; i++) cout << pse[i] << " \n"[i == 4];
    // -1 -1 1 2 2
    return 0;
}
```

**Jebakan:**
1. `>` versus `>=` mengubah “equal nearest”.
2. Mengembalikan nilai padahal soal minta indeks 1-based.
3. Loop dari kanan tanpa mengubah makna.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Next Smaller Element

> **Ide satu kalimat:** pagar kanan histogram; tiang pertama lebih rendah di depan.

### Next Smaller Element

**Teori:** Analoginya berjalan ke kanan sampai ketemu tiang yang lebih pendek. Bisa dihitung dengan stack menurun dari kiri (pop saat ketemu yang lebih kecil) atau loop dari kanan. Alasan benar: lebar batang i di histogram = `NSE[i] - PSE[i] - 1`.

**Kapan:** Pakai histogram, range sampai batas lebih kecil. Jangan tertukar dengan NGE.

**Proses:** `a = [2, 1, 5, 6, 2, 3]`.

| i | a[i] | nse indeks |
| ---: | ---: | ---: |
| 0 | 2 | 1 |
| 1 | 1 | 6 (sentinel) |
| 2 | 5 | 4 |
| 3 | 6 | 4 |
| 4 | 2 | 6 |
| 5 | 3 | 6 |

1. Batang 5 berhenti di indeks 4.
2. Batang 6 juga berhenti di 4.
3. Sentinel n di ujung memudahkan lebar.
4. Tanpa sentinel, sisa = −1.
5. Ketat: 2 tidak mem-pop 2 jika memakai `<`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> nextSmallerIdx(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> nse(n, n);
    vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] > a[i]) {
            nse[st.back()] = i;
            st.pop_back();
        }
        st.push_back(i);
    }
    return nse;
}

int main() {
    FASTIO;
    auto nse = nextSmallerIdx({2, 1, 5, 6, 2, 3});
    for (int i = 0; i < 6; i++) cout << nse[i] << " \n"[i == 5];
    // 1 6 4 4 6 6
    return 0;
}
```

**Jebakan:**
1. Default −1 lalu lebar `nse-pse-1` pecah.
2. `>=` versus `>` pada batang sama tinggi.
3. Mengira NSE adalah nilai, bukan indeks.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Previous Greater Element

> **Ide satu kalimat:** cermin NGE ke kiri; berguna untuk stock span dan “berapa hari lebih kecil beruntun”.

### Previous Greater Element

**Teori:** Analoginya melihat ke kiri siapa yang pertama lebih tinggi. Stack menurun dari kiri, pop yang lebih kecil atau sama sesuai soal. Stock span = `i - PGE[i]`. Alasan O(n) sama: tiap indeks sekali.

**Kapan:** Pakai stock span, next warmer ke kiri. Jangan NGE jika soal melihat ke belakang.

**Proses:** `a = [100, 80, 60, 70, 60, 75, 85]`.

| i | harga | PGE indeks | span |
| ---: | ---: | ---: | ---: |
| 0 | 100 | -1 | 1 |
| 1 | 80 | 0 | 1 |
| 2 | 60 | 1 | 1 |
| 3 | 70 | 1 | 2 |
| 4 | 60 | 3 | 1 |
| 5 | 75 | 1 | 4 |
| 6 | 85 | 0 | 6 |

1. 70 melihat 80 di indeks 1, span 2.
2. 75 mem-pop 60 dan 70, melihat 80, span 4.
3. 85 melihat 100, span 6.
4. Span minimal 1 (diri sendiri).
5. PGE default −1.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> stockSpan(const vector<ll>& a) {
    int n = (int)a.size();
    vector<int> span(n), st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] <= a[i]) st.pop_back();
        int pge = st.empty() ? -1 : st.back();
        span[i] = i - pge;
        st.push_back(i);
    }
    return span;
}

int main() {
    FASTIO;
    auto s = stockSpan({100, 80, 60, 70, 60, 75, 85});
    for (int i = 0; i < 7; i++) cout << s[i] << " \n"[i == 6];
    // 1 1 1 2 1 4 6
    return 0;
}
```

**Jebakan:**
1. Span dihitung `i-pge-1` — kehilangan diri sendiri.
2. Comparator `<=` tertukar dengan `<`.
3. Stack menyimpan nilai lalu tidak bisa hitung jarak.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Histogram persegi panjang

> **Ide satu kalimat:** tiap batang jadi tinggi plafon; lebarnya sampai tetangga yang lebih pendek.

### Histogram persegi panjang

**Teori:** Analoginya gedung-gedung: persegi terlebar dengan atap h[i] dibatasi gedung pertama lebih rendah di kiri dan kanan. Lebar = `R - L - 1`. Alasan O(n): L dari PSE, R dari NSE. Versi satu pass: stack meningkat, saat pop, kanan = i, kiri = stack baru.

**Kapan:** Pakai LC 84, maximal rectangle setelah dipadatkan jadi histogram per baris. Jangan O(n²) n=1e5.

**Proses:** `h = [2, 1, 5, 6, 2, 3]`.

1. Batang 5 (indeks 2): kiri lebih kecil =1, kanan lebih kecil =4. Lebar 4-1-1=2. Luas 10.
2. Batang 6: kiri 2, kanan 4, lebar 1, luas 6.
3. Jawaban klasik 10.
4. Sentinel 0 di ujung memaksa pop sisa.
5. `W = i - L - 1`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

ll largestRectangle(vector<ll> h) {
    h.push_back(0);
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
    FASTIO;
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

**Teori:** Analoginya lorong: air tidak lebih tinggi dari pagar terendah di kedua sisi. `leftMax[i]` / `rightMax[i]` dua sapuan. Versi dua pointer O(1) memori: sisi yang pagarnya lebih rendah menentukan air. Alasan benar: air di i hanya bergantung ekstrem kiri-kanan, bukan jumlah. Ini bukan luas histogram.

**Kapan:** Pakai LC 42. Jangan histogram luas. Stack juga bisa: pop lembah.

**Proses:** Mini `h = [2,0,2]` dan `h = [3,0,1]`.

| i pada [2,0,2] | Lmax | Rmax | air |
| ---: | ---: | ---: | ---: |
| 0 | 2 | 2 | 0 |
| 1 | 2 | 2 | 2 |
| 2 | 2 | 2 | 0 |

1. Tengah menampung 2.
2. `[3,0,1]`: min(3,1)-0=1.
3. Ujung tidak menampung.
4. Jawaban klasik array panjang = 6.
5. Two pointers: gerakkan sisi dengan max lebih kecil.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
    cout << trapAir({2, 0, 2}) << '\n'; // 2
    cout << trapAir({3, 0, 1}) << '\n'; // 1
    return 0;
}
```

**Jebakan:**
1. Menghitung volume 2D sebagai histogram rectangle.
2. Overflow.
3. `leftMax` tidak memuat diri — tetap aman karena air jadi 0 di puncak.

**Kompleksitas:** O(n) waktu, O(n) memori (bisa O(1) two pointers).

---

## Sliding window maximum

> **Ide satu kalimat:** deque menyimpan kandidat menurun; yang lebih tua dan lebih pendek tidak pernah juara lagi.

### Sliding window maximum

**Teori:** Analoginya antrean juara jendela: orang di belakang yang lebih pendek dari pendatang baru tidak akan jadi max selama pendatang masih ada, jadi diusir dari belakang. Orang di depan yang sudah keluar jendela diusir dari depan. Alasan O(n): tiap indeks push/pop ≤ sekali. Inilah Day 037.

**Kapan:** Pakai window max/min, DP dengan transisi “max di `[i-k, i-1]`”. Jangan Kadane untuk panjang tetap.

**Proses:** `a = [1,3,-1,-3,5,3,6,7]`, k=3.

| i | a[i] | deque indeks | max jika penuh |
| ---: | ---: | --- | ---: |
| 0 | 1 | 0 | - |
| 1 | 3 | 1 | - |
| 2 | -1 | 1,2 | 3 |
| 3 | -3 | 1,2,3 | 3 |
| 4 | 5 | 4 | 5 |
| 5 | 3 | 4,5 | 5 |
| 6 | 6 | 6 | 6 |
| 7 | 7 | 7 | 7 |

1. Jawaban `3,3,5,5,6,7`.
2. Simpan indeks agar tahu kapan keluar.
3. Pop depan jika `front <= i-k`.
4. Jangan cetak sebelum `i >= k-1`.
5. `multiset` juga benar, lebih lambat.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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

**Teori:** Cermin window max. Pop belakang yang ≥ a[i]. Dipakai “min di jendela”, dan sebagai setengah dari syarat max-min ≤ X.

**Kapan:** Pakai min jendela. Jangan dua `multiset` jika deque cukup.

**Proses:** `a = [1,3,-1,-3,5]`, k=3.

1. i=0: [0].
2. i=1: 3>1, dq=[0,1].
3. i=2: -1 pop 1 dan 0, dq=[2], min=-1.
4. i=3: -3 pop 2, dq=[3], min=-3.
5. i=4: 5, dq=[3,4], depan 3 masih masuk. min=-3. Hasil `-1,-3,-3`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
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
    FASTIO;
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
3. k=1 lupa — jawaban harus array itu sendiri.

**Kompleksitas:** O(n) waktu, O(k) memori.

---

## Max minus min pada window

> **Ide satu kalimat:** dua deque, satu juara tinggi, satu juara pendek; selisihnya adalah rentang.

### Max minus min pada window

**Teori:** Analoginya termometer ruangan: kamu ingin jendela hari di mana panas minus dingin ≤ X. Pertahankan dua deque. Jika `max-min > X`, majukan L dan buang indeks usang dari kedua deque. Alasan O(n): tiap indeks masuk-keluar tiap deque sekali.

**Kapan:** Pakai “longest window max-min ≤ X”, CSES/CF klasik. Jangan satu deque.

**Proses:** `a = [2, 5, 3]`, X=2.

| R | window | max-min | aksi |
| ---: | --- | ---: | --- |
| 0 | [2] | 0 | ok, panjang 1 |
| 1 | [2,5] | 3 | shrink, buang 2 |
| 1 | [5] | 0 | ok |
| 2 | [5,3] | 2 | ok, panjang 2 |

1. Terpanjang 2.
2. `[2,5]` terlalu lebar rentangnya.
3. Setelah buang 2, `[5,3]` sah.
4. Kedua deque harus dibersihkan saat L maju.
5. X=0 hanya window nilai sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int terpanjangMaxMin(const vector<ll>& a, ll X) {
    deque<int> mx, mn;
    int L = 0, best = 0;
    for (int R = 0; R < (int)a.size(); R++) {
        while (!mx.empty() && a[mx.back()] <= a[R]) mx.pop_back();
        while (!mn.empty() && a[mn.back()] >= a[R]) mn.pop_back();
        mx.push_back(R);
        mn.push_back(R);
        while (L <= R && a[mx.front()] - a[mn.front()] > X) {
            if (mx.front() == L) mx.pop_front();
            if (mn.front() == L) mn.pop_front();
            L++;
        }
        best = max(best, R - L + 1);
    }
    return best;
}

int main() {
    FASTIO;
    cout << terpanjangMaxMin({2, 5, 3}, 2) << '\n'; // 2
    cout << terpanjangMaxMin({1, 1, 1}, 0) << '\n'; // 3
    return 0;
}
```

**Jebakan:**
1. Hanya membersihkan satu deque saat L maju.
2. `>` versus `>=` pada syarat X.
3. Overflow kurang `max-min` jika memakai `int` pada nilai 2e9.

**Kompleksitas:** O(n) waktu, O(n) memori.

---

## Ringkasan

- Stack monoton = NGE/NSE/PGE/PSE O(n).
- Histogram: lebar `i-L-1`, sentinel 0.
- Air: min(pagar kiri, pagar kanan) minus tinggi.
- Deque menurun = window max O(n).
- Deque menaik = window min.
- Max-min: dua deque, geser L bersama.

Lanjut: [kompresi koordinat](kompresi.md).
