# 📊 Day 20: Sliding Window

**Hari**: Day 20 dari 150 Hari Competitive Programming
**Topik**: Sliding Window — Fixed Size, Variable Size, Maximum/Minimum
**Prerequisites**: Two Pointers (Day 19), Deque (Day 5), Map (Day 4)
**Difficulty**: ⭐⭐⭐ (Intermediate)
**Learning Objectives**:
- Memahami konsep sliding window dan dua varian utama (fixed & variable)
- Mengimplementasikan fixed-size window dengan teknik slide-add-remove
- Mengimplementasikan variable-size window untuk longest/shortest subarray
- Menggunakan frequency map di dalam window untuk constraint karakter
- Menggunakan monotonic deque untuk window maximum/minimum O(n)
- Memahami amortized complexity O(n) — tiap elemen masuk & keluar 1 kali

---

## 🔍 1. Konsep & Intuisi

### Apa itu Sliding Window?

**Sliding Window** adalah teknik untuk memproses **subarray/substring kontinu** secara efisien dengan menggeser sebuah "jendela" di sepanjang array. Daripada menghitung ulang setiap window dari nol O(n·k), kita memanfaatkan **tumpang-tindih** antar window:

```
Array: [2, 1, 5, 1, 3, 2]
              ↑ K = 3

Window 1: [2, 1, 5]            sum = 8
Window 2:    [1, 5, 1]         sum = 8 - 2 + 1 = 7   ← reuse!
Window 3:       [5, 1, 3]      sum = 7 - 1 + 3 = 9
Window 4:          [1, 3, 2]   sum = 9 - 5 + 2 = 6
```

Setiap geser, hanya **1 elemen masuk** (kanan) dan **1 elemen keluar** (kiri). Ini O(1) per slide → total O(n)!

### Analogi Kehidupan Nyata

- **Window kaca mobil** yang bergerak melihat pemandangan: yang lewat di belakang hilang, yang baru muncul terlihat
- **Antrean fast-food** dengan kapasitas K: orang baru masuk dari belakang, yang tertua keluar dari depan
- **Speedometer** yang menunjukkan rata-rata kecepatan 5 menit terakhir: tiap detik, satu data lama dibuang, satu data baru dimasukkan

### Kapan Pakai Sliding Window?

✅ **YES → Sliding Window**:
- "Berapa max/min/sum/avg subarray ukuran tepat K?"
- "Cari subarray TERPANJANG yang memenuhi constraint X"
- "Cari subarray TERPENDEK yang memenuhi constraint X"
- "Hitung berapa subarray yang sum-nya ≤ K (non-negative array)"
- "Maximum tiap window K ukuran"
- "Substring dengan paling banyak K karakter berbeda"

❌ **NO → Pakai teknik lain**:
- Subarray non-kontinu → tidak cocok
- Array dengan nilai NEGATIF + sum constraint → pakai prefix sum + map
- Butuh hasil semua subarray (tidak bisa di-prune) → tetap O(n²)

### Dua Varian Utama

```
┌──────────────────────────────────────────────────────────┐
│ FIXED-SIZE: Ukuran K tetap, slide 1 langkah              │
│                                                          │
│   [_ _ _]_ _ _    →    _[_ _ _]_ _    →    _ _[_ _ _]_   │
│    L   R              L+1  R+1            L+2   R+2     │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│ VARIABLE-SIZE: Window membesar/mengecil sesuai kondisi   │
│                                                          │
│   [_]_ _ _ _ _   →   [_ _ _]_ _ _   →   _ _[_]_ _ _      │
│    L=R              L  expand R           shrink L       │
└──────────────────────────────────────────────────────────┘
```

---

## 🧮 2. Analisis Kompleksitas

### Mengapa O(n)?

**Kunci**: Pointer L dan R hanya bergerak **maju** (tidak pernah mundur).

| Pola | Pergerakan L | Pergerakan R | Total |
|------|--------------|--------------|-------|
| Fixed-Size | maju n-k kali | maju n-k kali | O(n) |
| Variable Longest | maju ≤ n kali | maju n kali | O(n) |
| Variable Shortest | maju ≤ n kali | maju n kali | O(n) |
| Monotonic Deque | maju ≤ n kali (pop) | maju n kali (push) | O(n) |

**Setiap elemen** masuk window **maksimum 1 kali** dan keluar **maksimum 1 kali** → total operasi 2n = O(n).

### Perbandingan dengan Brute Force

| Algoritma | Brute Force | Sliding Window | Speedup |
|-----------|-------------|----------------|---------|
| Max Sum Subarray K | O(n·k) | O(n) | k× |
| Longest Subarray Sum ≤ K | O(n²) | O(n) | n× |
| Min Subarray Sum ≥ S | O(n²) | O(n) | n× |
| Sliding Window Max | O(n·k) | O(n) | k× |
| Longest Substring K Distinct | O(n²·26) | O(n) | n× |

### Space Complexity

- Tanpa map/deque: **O(1)**
- Dengan frequency map (k karakter unik): **O(k)**
- Dengan deque (window K): **O(K)**

---

## 💻 3. Implementasi C++

### 3.1 Fixed-Size Window — Maximum Sum Subarray K

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n, k;
    cin >> n >> k;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    // Step 1: Hitung sum window pertama [0..k-1]
    ll sum = 0;
    for (int i = 0; i < k; i++) sum += A[i];
    ll ans = sum;

    // Step 2: Slide window dari index k sampai n-1
    for (int i = k; i < n; i++) {
        sum += A[i] - A[i - k];   // masuk A[i], keluar A[i-k]
        ans = max(ans, sum);
    }

    cout << ans << "\n";
    return 0;
}
```

**Penjelasan baris demi baris**:
- `sum += A[i] - A[i - k]`: tambah elemen baru (kanan), kurangi elemen lama (kiri)
- Window pada iterasi ke-i adalah `[i-k+1, i]`

### 3.2 Variable-Size Window — Longest Subarray Sum ≤ K

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    ll K;
    cin >> n >> K;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    int L = 0;
    int ans = 0;
    ll sum = 0;

    for (int R = 0; R < n; R++) {
        sum += A[R];                       // expand kanan

        while (sum > K && L <= R) {        // shrink kiri sampai valid
            sum -= A[L];
            L++;
        }

        ans = max(ans, R - L + 1);         // window [L,R] valid
    }

    cout << ans << "\n";
    return 0;
}
```

**⚠️ Pre-condition**: Semua A[i] ≥ 0. Kalau ada nilai negatif, sum bisa naik-turun → window gak monotonic → bukan sliding window!

### 3.3 Variable-Size Window — Smallest Subarray Sum ≥ S

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    ll S;
    cin >> n >> S;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    int L = 0;
    int ans = INT_MAX;
    ll sum = 0;

    for (int R = 0; R < n; R++) {
        sum += A[R];                       // expand kanan

        while (sum >= S) {                 // selama valid, coba shrink
            ans = min(ans, R - L + 1);
            sum -= A[L];
            L++;
        }
    }

    cout << (ans == INT_MAX ? 0 : ans) << "\n";
    return 0;
}
```

**Beda dengan POLA Longest**:
- Shrink **WHILE valid** (bukan WHILE invalid)
- Update ans **DI DALAM loop shrink** (saat masih valid)

### 3.4 Variable-Size Window + Frequency Map — Longest Substring K Distinct

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int K;
    cin >> s >> K;
    int n = s.size();

    unordered_map<char, int> freq;
    int L = 0, ans = 0;

    for (int R = 0; R < n; R++) {
        freq[s[R]]++;                          // tambah char baru

        while ((int)freq.size() > K) {         // > K distinct → shrink
            freq[s[L]]--;
            if (freq[s[L]] == 0)
                freq.erase(s[L]);              // ⚠️ wajib erase!
            L++;
        }

        ans = max(ans, R - L + 1);
    }

    cout << ans << "\n";
    return 0;
}
```

**Kunci**: `freq.erase(s[L])` saat count jadi 0 — kalau lupa, `freq.size()` akan over-count.

### 3.5 Monotonic Deque — Sliding Window Maximum

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    deque<int> dq;   // simpan INDEX, A[idx] decreasing dari front

    for (int i = 0; i < n; i++) {
        // 1. Buang index dari front yang sudah keluar window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // 2. Buang index dari back yang nilainya ≤ A[i]
        //    (mereka tidak akan pernah jadi max selama A[i] ada)
        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();

        // 3. Tambah index sekarang
        dq.push_back(i);

        // 4. Output max ketika window sudah penuh
        if (i >= k - 1)
            cout << A[dq.front()] << " \n"[i == n - 1];
    }

    return 0;
}
```

**Invariant deque**:
- Index di deque selalu di dalam window `[i-k+1, i]`
- A[front] ≥ A[next] ≥ ... ≥ A[back] (decreasing)
- A[front] = MAX di window sekarang

---

## 🔄 4. Trace / Simulasi

### Trace 1: Maximum Sum Subarray K = 3

**Input**: `A = [2, 1, 5, 1, 3, 2]`, `K = 3`

```
Step | Window    | Operation        | Sum | Ans
-----|-----------|------------------|-----|----
init | [2,1,5]   | initial          |  8  |  8
i=3  | [1,5,1]   | +A[3] -A[0]      |  7  |  8
     |           | +1 -2 = -1       |     |
i=4  | [5,1,3]   | +A[4] -A[1]      |  9  |  9
     |           | +3 -1 = +2       |     |
i=5  | [1,3,2]   | +A[5] -A[2]      |  6  |  9
     |           | +2 -5 = -3       |     |
```

**Output**: 9 (window [5,1,3])

### Trace 2: Smallest Subarray Sum ≥ 7

**Input**: `A = [2, 1, 5, 2, 3, 2]`, `S = 7`

```
R | A[R] | sum | L | window      | shrink? | ans
--|------|-----|---|-------------|---------|----
0 |  2   |  2  | 0 | [2]         | no      | INF
1 |  1   |  3  | 0 | [2,1]       | no      | INF
2 |  5   |  8  | 0 | [2,1,5]     | YES     | 3
  |      |  6  | 1 | [1,5]       | no      | 3
3 |  2   |  8  | 1 | [1,5,2]     | YES     | min(3,3)=3
  |      |  7  | 2 | [5,2]       | YES     | min(3,2)=2
  |      |  2  | 3 | [2]         | no      | 2
4 |  3   |  5  | 3 | [2,3]       | no      | 2
5 |  2   |  7  | 3 | [2,3,2]     | YES     | min(2,3)=2
  |      |  5  | 4 | [3,2]       | no      | 2
```

**Output**: 2 (window [5,2])

### Trace 3: Longest Substring K=2 Distinct

**Input**: `s = "araaci"`, `K = 2`

```
R | s[R] | freq          | size | L | shrink steps  | window  | ans
--|------|---------------|------|---|---------------|---------|----
0 |  a   | {a:1}         |  1   | 0 |  -            | "a"     | 1
1 |  r   | {a:1,r:1}     |  2   | 0 |  -            | "ar"    | 2
2 |  a   | {a:2,r:1}     |  2   | 0 |  -            | "ara"   | 3
3 |  a   | {a:3,r:1}     |  2   | 0 |  -            | "araa"  | 4
4 |  c   | {a:3,r:1,c:1} |  3>2 | 0 | rm a:freq=2   |         |
  |      | {a:2,r:1,c:1} |  3>2 | 1 | rm r:erase    |         |
  |      | {a:2,c:1}     |  2   | 2 |  -            | "aac"   | 4
5 |  i   | {a:2,c:1,i:1} |  3>2 | 2 | rm a:freq=1   |         |
  |      | {a:1,c:1,i:1} |  3>2 | 3 | rm a:erase    |         |
  |      | {c:1,i:1}     |  2   | 4 |  -            | "ci"    | 4
```

**Output**: 4 (substring "araa")

### Trace 4: Sliding Window Maximum K=3

**Input**: `A = [1, 3, -1, -3, 5, 3, 6, 7]`, `K = 3`

```
i | A[i] | Pop front (out)| Pop back (≤ A[i]) | Push | dq (idx) | A[front] | Out
--|------|----------------|-------------------|------|----------|----------|----
0 |  1   | -              | -                 | 0    | [0]      | 1        | -
1 |  3   | -              | A[0]=1 → pop      | 1    | [1]      | 3        | -
2 | -1   | -              | -                 | 2    | [1,2]    | 3        | 3
3 | -3   | -              | -                 | 3    | [1,2,3]  | 3        | 3
4 |  5   | -              | A[3]=-3,A[2]=-1   | 4    | [1,4]    |          |
  |      |                | A[1]=3 → pop      |      | [4]      | 5        | 5
5 |  3   | -              | -                 | 5    | [4,5]    | 5        | 5
6 |  6   | -              | A[5]=3,A[4]=5→pop | 6    | [6]      | 6        | 6
7 |  7   | -              | A[6]=6 → pop      | 7    | [7]      | 7        | 7
```

**Output**: `3 3 5 5 6 7`

---

## 📝 5. Variasi & Pattern

### Pattern 1: Fixed-Size — Sum/Avg/Count

```cpp
ll sum = 0;
for (int i = 0; i < k; i++) sum += A[i];
ll ans = sum;
for (int i = k; i < n; i++) {
    sum += A[i] - A[i - k];
    ans = (max/min)(ans, sum);
}
```

### Pattern 2: Variable Longest dengan Constraint

```cpp
int L = 0, ans = 0;
for (int R = 0; R < n; R++) {
    add(A[R]);
    while (window_invalid()) {
        remove(A[L]);
        L++;
    }
    ans = max(ans, R - L + 1);
}
```

### Pattern 3: Variable Shortest dengan Constraint

```cpp
int L = 0, ans = INT_MAX;
for (int R = 0; R < n; R++) {
    add(A[R]);
    while (window_valid()) {
        ans = min(ans, R - L + 1);
        remove(A[L]);
        L++;
    }
}
```

### Pattern 4: Count Subarray dengan Constraint

```cpp
// Hitung jumlah subarray dengan sum ≤ K (semua A[i] ≥ 0)
int L = 0;
ll cnt = 0, sum = 0;
for (int R = 0; R < n; R++) {
    sum += A[R];
    while (sum > K) sum -= A[L++];
    cnt += (R - L + 1);  // semua subarray berakhiran R yang valid
}
```

### Pattern 5: "Exactly K" = "AtMost(K) - AtMost(K-1)"

```cpp
// Subarray dengan EXACTLY K distinct elements
auto atMost = [&](int K) -> ll {
    unordered_map<int,int> freq;
    int L = 0;
    ll cnt = 0;
    for (int R = 0; R < n; R++) {
        freq[A[R]]++;
        while ((int)freq.size() > K) {
            freq[A[L]]--;
            if (freq[A[L]] == 0) freq.erase(A[L]);
            L++;
        }
        cnt += R - L + 1;
    }
    return cnt;
};
ll ans = atMost(K) - atMost(K - 1);
```

### Pattern 6: Anagram/Permutation Check (Fixed Window + Freq)

```cpp
// Cari semua window di s yang merupakan anagram dari t
int n = s.size(), m = t.size();
vector<int> need(26, 0), have(26, 0);
for (char c : t) need[c - 'a']++;

for (int i = 0; i < n; i++) {
    have[s[i] - 'a']++;
    if (i >= m) have[s[i - m] - 'a']--;
    if (i >= m - 1 && have == need)
        cout << i - m + 1 << " ";   // anagram ditemukan
}
```

### Pattern 7: Monotonic Deque untuk Min

```cpp
// Sliding window MIN — sama persis dengan MAX, tapi:
while (!dq.empty() && A[dq.back()] >= A[i])  // ≥ (bukan ≤)
    dq.pop_back();
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### Mistake 1: Pakai `if` Bukan `while` Saat Shrink

```cpp
// ❌ SALAH — kondisi violated bisa berlangsung beberapa langkah
if (sum > K) {
    sum -= A[L];
    L++;
}

// ✅ BENAR
while (sum > K && L <= R) {
    sum -= A[L];
    L++;
}
```

### Mistake 2: Update Ans Sebelum Shrink (Variable Longest)

```cpp
// ❌ SALAH — ans bisa di-update saat window invalid
for (int R = 0; R < n; R++) {
    sum += A[R];
    ans = max(ans, R - L + 1);   // SALAH: window mungkin invalid!
    while (sum > K) sum -= A[L++];
}

// ✅ BENAR — update ans SETELAH window pasti valid
for (int R = 0; R < n; R++) {
    sum += A[R];
    while (sum > K) sum -= A[L++];
    ans = max(ans, R - L + 1);   // sekarang aman
}
```

### Mistake 3: Lupa Erase di Frequency Map

```cpp
// ❌ SALAH
freq[s[L]]--;
L++;

// ✅ BENAR
freq[s[L]]--;
if (freq[s[L]] == 0) freq.erase(s[L]);  // wajib agar freq.size() benar!
L++;
```

### Mistake 4: Sliding Window pada Nilai Negatif

```cpp
// ❌ SALAH — sliding window tidak bekerja!
// Karena sum bisa naik-turun, monotonicity hilang
A = [1, -2, 3, -4, 5];
// Untuk "longest subarray sum ≤ K" dengan negatif → pakai prefix sum + map
```

### Mistake 5: Off-by-one Window Size

```cpp
// Window [L, R] inclusive, panjang = R - L + 1
// ❌ R - L = panjang minus 1!

ans = max(ans, R - L + 1);   // ✅
ans = max(ans, R - L);       // ❌
```

### Mistake 6: Inisialisasi Window Pertama Lupa

```cpp
// Fixed-size window MAX SUM K
// ❌ langsung loop dari 0
ll sum = 0, ans = 0;
for (int i = 0; i < n; i++) {
    sum += A[i];
    if (i >= k) sum -= A[i - k];
    ans = max(ans, sum);   // i < k-1: window belum penuh, tidak valid!
}

// ✅ inisialisasi dulu, lalu slide
ll sum = 0;
for (int i = 0; i < k; i++) sum += A[i];
ll ans = sum;
for (int i = k; i < n; i++) {
    sum += A[i] - A[i - k];
    ans = max(ans, sum);
}
```

### Edge Cases

| Kasus | Behavior | Handle |
|-------|----------|--------|
| `n < k` (window > array) | window tidak ada | return 0 / -1 / "IMPOSSIBLE" |
| `n == k` | satu window saja | loop initial cukup |
| `array kosong` | tidak ada output | early return |
| `semua negatif` (sum-based) | sliding window invalid | pakai prefix sum |
| `s kosong` (string) | freq.size() = 0 | tidak masuk loop |

---

## 🏆 7. Tips Contest

### Decision Tree Cepat

```
Lihat soal:
│
├── "Subarray ukuran TEPAT K..."         → POLA 1 (Fixed)
│
├── "Subarray TERPANJANG yang..."        → POLA 2 (Var Longest)
│
├── "Subarray TERPENDEK yang..."         → POLA 3 (Var Shortest)
│
├── "Substring dengan paling banyak K..." → POLA 4 (Var + Freq Map)
│
├── "Maximum/Minimum tiap window K..."    → POLA 5/6 (Monotonic Deque)
│
└── "Berapa banyak subarray yang..."      → POLA 4 / Trick AtMost(K)-AtMost(K-1)
```

### Red Flags = Sliding Window

- 🚩 Kata kunci: "subarray kontinu", "substring kontinu"
- 🚩 Constraint pada subarray (sum ≤ X, distinct ≤ K, etc.)
- 🚩 Soal minta longest/shortest/count subarray
- 🚩 N besar (10⁵+) tapi minta complexity O(n)
- 🚩 Jika brute force = O(n²) atau O(n·k), sliding window biasa O(n)

### Time Management

1. **Identifikasi pola** (30 detik): fixed atau variable?
2. **Tentukan pre-condition** (30 detik): apakah array non-negatif? sorted?
3. **Tulis pseudocode** (1 menit): expand R, shrink L kapan?
4. **Implementasi** (5 menit): pakai template
5. **Test edge case** (2 menit): n=0, n=1, n<k

### Quick Tips

- **Pakai long long** untuk sum (overflow!)
- **`R - L + 1`** untuk panjang window, BUKAN `R - L`
- **Inisialisasi `ans`**: 0 untuk longest, INT_MAX untuk shortest
- **Bedakan `<=` vs `<`** di kondisi window
- **Test dengan k=1** dan k=n** untuk verifikasi

---

## 📌 8. Ringkasan & Cheatsheet

### Key Points

1. **Sliding window** = kasus khusus two pointers untuk subarray kontinu
2. Dua varian: **fixed-size** (slide) dan **variable-size** (expand-shrink)
3. **Amortized O(n)**: tiap elemen masuk & keluar window 1× saja
4. **Pre-condition penting**: untuk sum-based, semua nilai ≥ 0
5. **Monotonic deque** = sliding window + max/min query O(1)
6. **`while`, bukan `if`** untuk shrink loop
7. **Update ans setelah window valid**, bukan sebelum

### Cheatsheet Singkat

```cpp
// FIXED-SIZE
ll sum = 0;
for (int i = 0; i < k; i++) sum += A[i];
ll ans = sum;
for (int i = k; i < n; i++) {
    sum += A[i] - A[i-k];
    ans = max(ans, sum);
}

// VARIABLE LONGEST
int L = 0, ans = 0;
for (int R = 0; R < n; R++) {
    add(A[R]);
    while (invalid()) remove(A[L++]);
    ans = max(ans, R - L + 1);
}

// VARIABLE SHORTEST
int L = 0, ans = INT_MAX;
for (int R = 0; R < n; R++) {
    add(A[R]);
    while (valid()) {
        ans = min(ans, R - L + 1);
        remove(A[L++]);
    }
}

// MONOTONIC DEQUE (MAX)
deque<int> dq;
for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    while (!dq.empty() && A[dq.back()] <= A[i]) dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) cout << A[dq.front()] << " ";
}
```

### Link Soal Latihan

**LeetCode**:
- 643 Maximum Average Subarray I (Easy)
- 209 Minimum Size Subarray Sum (Medium)
- 3 Longest Substring Without Repeating (Medium)
- 438 Find All Anagrams (Medium)
- 239 Sliding Window Maximum (Hard)
- 76 Minimum Window Substring (Hard)
- 992 Subarrays with K Different Integers (Hard)

**CSES**:
- 1141 Playlist
- 1077 Sliding Median
- 1076 Sliding Window Cost
- 1085 Array Description (variant)

**Codeforces**:
- 1208B Uniqueness
- 814C An Impassioned Circulation
- 488B Candy Boxes

---

*Day 20 — Sliding Window | Competitive Programming Learning*
