# Day 19 — Two Pointers: Teori Lengkap

---

## 1. Apa itu Two Pointers?

**Two Pointers** adalah teknik algoritmik yang menggunakan dua indeks (variabel pointer) untuk menelusuri array atau string secara efisien. Teknik ini menghindari nested loop O(n²) dengan cara menggerakkan kedua pointer secara cerdas berdasarkan kondisi tertentu.

### Intuisi Dasar

Bayangkan kamu mencari dua angka dalam daftar yang jumlahnya = 10:

```
Array: [1, 3, 4, 6, 8, 9]
        0  1  2  3  4  5
```

**Pendekatan naif (O(n²)):**
```
Cek (1,3)=4, (1,4)=5, (1,6)=7, (1,8)=9, (1,9)=10 ← ketemu
Total: banyak perbandingan
```

**Pendekatan two pointers (O(n)):**
```
L=0, R=5: 1+9=10 → ketemu!
Total: 1 perbandingan
```

### Konsep Pointer L dan R

```
Array:  [ 1 ][ 3 ][ 4 ][ 6 ][ 8 ][ 9 ]
Index:    0    1    2    3    4    5
          ↑                        ↑
          L                        R
```

- **L (Left pointer)**: mulai dari indeks 0 (ujung kiri)
- **R (Right pointer)**: mulai dari indeks n-1 (ujung kanan)
- Keduanya bergerak menuju tengah sampai bertemu atau kondisi terpenuhi

### Kapan Menggunakan Two Pointers?

| Situasi | Pola Yang Digunakan |
|---------|---------------------|
| Sorted array + cari pair/sum | Opposite Direction |
| Cek palindrome | Opposite Direction |
| Container with most water | Opposite Direction |
| Remove duplicates in-place | Same Direction (slow-fast) |
| Sliding window / subarray | Same Direction |
| Merge dua sorted array | Two Independent Pointers |
| 3-way partition | Three Pointers (Dutch Flag) |

### Pre-Condition Penting

- **Opposite Direction** → Array **harus sorted** (atau ada properti monoton)
- **Same Direction** → Array tidak harus sorted
- **Merge** → Kedua array harus sorted

---

## 2. Opposite Direction Pointers

Dalam pola ini:
- `L` dimulai dari indeks **0** (kiri)
- `R` dimulai dari indeks **n-1** (kanan)
- Keduanya bergerak ke **tengah**

```
Iterasi 1:
[ 1 ][ 3 ][ 4 ][ 6 ][ 8 ][ 9 ]
  L                        R
  ↑ bergerak ke kanan     ↑ bergerak ke kiri

Iterasi 2:
[ 1 ][ 3 ][ 4 ][ 6 ][ 8 ][ 9 ]
       L                  R

Iterasi 3:
[ 1 ][ 3 ][ 4 ][ 6 ][ 8 ][ 9 ]
            L         R

Stop ketika L >= R
```

**Template dasar:**
```cpp
int L = 0, R = n - 1;
while (L < R) {
    if (kondisi_terpenuhi) {
        // proses hasil
        break;  // atau L++, R--
    } else if (perlu_nilai_lebih_besar) {
        L++;  // geser kiri ke kanan (nilai naik karena sorted)
    } else {
        R--;  // geser kanan ke kiri (nilai turun karena sorted)
    }
}
```

---

## 3. Two Sum on Sorted Array

### Problem Statement
Diberikan sorted array `A` dan target `T`. Temukan dua indeks `i < j` sehingga `A[i] + A[j] = T`.

### Proof of Correctness

Mengapa two pointers benar untuk masalah ini?

**Klaim**: Jika `A[L] + A[R] > T`, maka A[R] tidak bisa berpasangan dengan elemen manapun di sisi kanan L yang menghasilkan sum = T.
- Karena array sorted, semua `A[i]` dengan `i >= L+1` lebih besar dari `A[L]`
- Jadi `A[i] + A[R] > A[L] + A[R] > T` untuk semua `i > L`
- Kesimpulan: R bisa di-decrement dengan aman

**Klaim**: Jika `A[L] + A[R] < T`, maka A[L] tidak bisa berpasangan dengan elemen manapun di sisi kiri R.
- Karena sorted, semua `A[j]` dengan `j <= R-1` lebih kecil dari `A[R]`
- Jadi `A[L] + A[j] < A[L] + A[R] < T` untuk semua `j < R`
- Kesimpulan: L bisa di-increment dengan aman

### Implementasi Lengkap

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;
    ll T; cin >> T;

    int L = 0, R = n - 1;
    bool found = false;
    while (L < R) {
        ll s = A[L] + A[R];
        if (s == T) {
            cout << L + 1 << " " << R + 1 << "\n";  // 1-indexed
            found = true;
            break;
        } else if (s < T) {
            L++;  // sum terlalu kecil, naikkan L
        } else {
            R--;  // sum terlalu besar, turunkan R
        }
    }
    if (!found) cout << "IMPOSSIBLE\n";

    return 0;
}
```

### Trace Table

Array: `[1, 3, 4, 6, 8, 9]`, Target `T = 10`

| Step | L | R | A[L] | A[R] | Sum | Aksi |
|------|---|---|------|------|-----|------|
| 1 | 0 | 5 | 1 | 9 | 10 | FOUND! |

Array: `[1, 3, 4, 6, 8, 9]`, Target `T = 7`

| Step | L | R | A[L] | A[R] | Sum | Aksi |
|------|---|---|------|------|-----|------|
| 1 | 0 | 5 | 1 | 9 | 10 | sum>T → R-- |
| 2 | 0 | 4 | 1 | 8 | 9 | sum>T → R-- |
| 3 | 0 | 3 | 1 | 6 | 7 | FOUND! |

Array: `[1, 3, 4, 6, 8, 9]`, Target `T = 2`

| Step | L | R | A[L] | A[R] | Sum | Aksi |
|------|---|---|------|------|-----|------|
| 1 | 0 | 5 | 1 | 9 | 10 | sum>T → R-- |
| 2 | 0 | 4 | 1 | 8 | 9 | sum>T → R-- |
| 3 | 0 | 3 | 1 | 6 | 7 | sum>T → R-- |
| 4 | 0 | 2 | 1 | 4 | 5 | sum>T → R-- |
| 5 | 0 | 1 | 1 | 3 | 4 | sum>T → R-- |
| 6 | L >= R | STOP | | | | IMPOSSIBLE |

**Kompleksitas**: O(n) time, O(1) space

---

## 4. Three Sum Problem

### Problem Statement
Temukan semua triplet unik `(i, j, k)` dengan `i < j < k` sehingga `A[i] + A[j] + A[k] = 0`.

### Strategi
1. **Sort** array terlebih dahulu
2. **Fix** satu elemen dengan outer loop (`A[i]`)
3. Gunakan **two pointers** untuk sisa dua elemen (`L = i+1`, `R = n-1`)
4. **Skip duplikat** untuk menghindari triplet yang sama

```
Array sorted: [-4, -1, -1, 0, 1, 2]
Fix A[0]=-4:
    L=1, R=5: -4+(-1)+2=-3 < 0 → L++
    L=2, R=5: -4+(-1)+2=-3 < 0 → L++
    L=3, R=5: -4+0+2=-2 < 0 → L++
    L=4, R=5: -4+1+2=-1 < 0 → L++
    L>=R, stop

Fix A[1]=-1:
    L=2, R=5: -1+(-1)+2=0 → FOUND [-1,-1,2], L++, R--
    L=3, R=4: -1+0+1=0 → FOUND [-1,0,1], L++, R--
    L>=R, stop

Fix A[2]=-1:  skip (duplikat A[1])
...
```

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    sort(A.begin(), A.end());
    vector<tuple<int,int,int>> ans;

    for (int i = 0; i < n - 2; i++) {
        // Skip duplikat untuk elemen i
        if (i > 0 && A[i] == A[i-1]) continue;

        int L = i + 1, R = n - 1;
        while (L < R) {
            int s = A[i] + A[L] + A[R];
            if (s == 0) {
                ans.push_back({A[i], A[L], A[R]});
                // Skip duplikat
                while (L < R && A[L] == A[L+1]) L++;
                while (L < R && A[R] == A[R-1]) R--;
                L++; R--;
            } else if (s < 0) {
                L++;
            } else {
                R--;
            }
        }
    }

    for (auto [a, b, c] : ans)
        cout << a << " " << b << " " << c << "\n";

    return 0;
}
```

**Kompleksitas**: O(n² ) time (outer O(n) × inner O(n)), O(1) space ekstra

---

## 5. Container With Most Water

### Problem Statement
Diberikan array `h` dimana `h[i]` adalah tinggi garis vertikal di posisi `i`. Temukan dua garis yang, bersama sumbu x, membentuk wadah yang bisa menampung air paling banyak.

```
Volume air = min(h[L], h[R]) × (R - L)
```

### Visualisasi

```
h = [1, 8, 6, 2, 5, 4]
     0  1  2  3  4  5

     8  |
     7  |   |
     6  |   |   |
     5  |   |       |
     4  |   |       |   |
     3  |   |       |   |
     2  |   |   |   |   |
     1  |   |   |   |   |   |
        0   1   2   3   4   5
```

Wadah terbaik: `h[1]=8` dan `h[5]=4`:
- Volume = min(8, 4) × (5-1) = 4 × 4 = 16

### Greedy Insight (Proof)

**Mengapa gerakkan pointer yang lebih kecil?**

Misalkan `h[L] < h[R]`. Volume saat ini = `h[L] × (R-L)`.

Jika kita gerakkan R ke R-1:
- Width berkurang menjadi (R-1-L)
- Height = min(h[L], h[R-1]) ≤ h[L] (karena min bounded by h[L])
- Volume baru ≤ h[L] × (R-1-L) < h[L] × (R-L)
- Pasti lebih kecil atau sama!

Jadi menggerakkan R tidak akan menghasilkan volume lebih besar ketika `h[L] < h[R]`. **Kita harus menggerakkan L** untuk mungkin mendapat tinggi lebih besar.

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> h(n);
    for (auto& x : h) cin >> x;

    int L = 0, R = n - 1;
    int ans = 0;
    while (L < R) {
        int vol = min(h[L], h[R]) * (R - L);
        ans = max(ans, vol);
        // Gerakkan pointer yang lebih kecil
        if (h[L] < h[R]) L++;
        else R--;
    }
    cout << ans << "\n";

    return 0;
}
```

### Trace Table

`h = [1, 8, 6, 2, 5, 4]`, answer = 16

| Step | L | R | h[L] | h[R] | Volume | Aksi |
|------|---|---|------|------|--------|------|
| 1 | 0 | 5 | 1 | 4 | min(1,4)×5=5 | h[L]<h[R] → L++ |
| 2 | 1 | 5 | 8 | 4 | min(8,4)×4=16 | h[L]>h[R] → R-- |
| 3 | 1 | 4 | 8 | 5 | min(8,5)×3=15 | h[L]>h[R] → R-- |
| 4 | 1 | 3 | 8 | 2 | min(8,2)×2=4 | h[L]>h[R] → R-- |
| 5 | 1 | 2 | 8 | 6 | min(8,6)×1=6 | h[L]>h[R] → R-- |
| 6 | L >= R | STOP | | | | ans = 16 |

---

## 6. Valid Palindrome

### Problem Statement
Cek apakah string merupakan palindrome, hanya mempertimbangkan karakter alphanumeric (huruf dan angka), dan mengabaikan kapitalisasi.

### Contoh
- `"A man a plan a canal Panama"` → `"amanaplanacanalpanama"` → YES
- `"race a car"` → `"raceacar"` → NO

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);

    // Filter hanya alphanumeric, lowercase
    string clean = "";
    for (char c : s) {
        if (isalpha(c)) clean += tolower(c);
        else if (isdigit(c)) clean += c;
    }

    int L = 0, R = (int)clean.size() - 1;
    bool ok = true;
    while (L < R) {
        if (clean[L] != clean[R]) { ok = false; break; }
        L++; R--;
    }

    cout << (ok ? "YES" : "NO") << "\n";
    return 0;
}
```

### Visualisasi

```
String: "racecar"
         r a c e c a r
         L           R
Step 1: r==r → L++, R--
         r a c e c a r
           L       R
Step 2: a==a → L++, R--
         r a c e c a r
             L   R
Step 3: c==c → L++, R--
         r a c e c a r
               L R
               L R → L++, R--
Step 4: L > R → STOP → YES
```

**Kompleksitas**: O(n) time, O(n) space (untuk string clean) atau O(1) dengan skip langsung

---

## 7. Same Direction Pointers (Slow-Fast)

Dalam pola ini, kedua pointer bergerak ke arah **yang sama** (dari kiri ke kanan):
- **Slow pointer** (`slow`): posisi "write" atau posisi elemen valid terakhir
- **Fast pointer** (`fast`): advance setiap iterasi, "read" semua elemen

```
Array: [1, 1, 2, 3, 3, 3, 4]
        S
        F→ F→ F→ F→ F→ F→

Ketika A[fast] valid → tulis ke A[slow], slow++
Ketika A[fast] tidak valid → skip, slow tidak maju
```

### Template

```cpp
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (kondisi_valid(A[fast])) {
        A[slow] = A[fast];
        slow++;
    }
    // Jika tidak valid, fast maju tapi slow diam
}
// slow = jumlah elemen valid
```

---

## 8. Remove Duplicates In-Place

### Problem Statement
Diberikan sorted array, hapus duplikat in-place. Return panjang array baru.

### Strategi
- `slow` = posisi penulisan (elemen unik terakhir)
- `fast` scan semua elemen
- Jika `A[fast] != A[slow]`, elemen baru → tulis ke `A[++slow]`

### Visualisasi

```
A = [1, 1, 2, 3, 3, 3, 4]
     S
     F

Step: F=0, A[0]=1. Pertama kali → A[slow=0]=1. slow=0.
     [1, 1, 2, 3, 3, 3, 4]
      S  F

Step: F=1, A[1]=1 == A[slow]=A[0]=1. Duplikat → skip.
     [1, 1, 2, 3, 3, 3, 4]
      S     F

Step: F=2, A[2]=2 != A[slow]=A[0]=1. Unik → A[++slow]=A[1]=2. slow=1.
     [1, 2, 2, 3, 3, 3, 4]
         S     F

Step: F=3, A[3]=3 != A[slow]=A[1]=2. Unik → A[++slow]=A[2]=3. slow=2.
     [1, 2, 3, 3, 3, 3, 4]
            S     F

Step: F=4, A[4]=3 == A[slow]=3. Duplikat → skip.
Step: F=5, A[5]=3 == A[slow]=3. Duplikat → skip.
Step: F=6, A[6]=4 != A[slow]=3. Unik → A[++slow]=A[3]=4. slow=3.

Result: [1, 2, 3, 4, 3, 3, 4], len = slow+1 = 4
```

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    if (n == 0) { cout << "0\n"; return 0; }

    int slow = 0;
    for (int fast = 1; fast < n; fast++) {
        if (A[fast] != A[slow]) {
            A[++slow] = A[fast];
        }
    }
    int len = slow + 1;

    cout << len << "\n";
    for (int i = 0; i < len; i++)
        cout << A[i] << " \n"[i == len - 1];

    return 0;
}
```

**Kompleksitas**: O(n) time, O(1) space

---

## 9. Longest Subarray Sum ≤ K

### Problem Statement
Diberikan array positif dan bilangan K. Temukan panjang subarray terpanjang dengan sum ≤ K.

### Strategi (Two Pointer / Sliding Window)
- `L` = awal window
- `R` = akhir window (advance terus)
- Jika `sum > K`, shrink dari kiri (L++)
- Update jawaban setiap kali kondisi terpenuhi

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n; ll K;
    cin >> n >> K;
    vector<ll> A(n);
    for (auto& x : A) cin >> x;

    int ans = 0;
    ll sum = 0;
    int L = 0;

    for (int R = 0; R < n; R++) {
        sum += A[R];
        // Shrink window jika sum melebihi K
        while (sum > K && L <= R) {
            sum -= A[L];
            L++;
        }
        // Window [L, R] valid
        ans = max(ans, R - L + 1);
    }

    cout << ans << "\n";
    return 0;
}
```

### Trace Table

Array: `[1, 3, 2, 5, 1]`, K = 6

| R | L | sum sebelum | A[R] | sum setelah | Window valid? | ans |
|---|---|-------------|------|-------------|---------------|-----|
| 0 | 0 | 0 | 1 | 1 | sum≤6 → YES | 1 |
| 1 | 0 | 1 | 3 | 4 | sum≤6 → YES | 2 |
| 2 | 0 | 4 | 2 | 6 | sum≤6 → YES | 3 |
| 3 | 0 | 6 | 5 | 11 | sum>6 → L++ |  |
| 3 | 1 | 11 | - | 10 | sum>6 → L++ |  |
| 3 | 2 | 10 | - | 7 | sum>6 → L++ |  |
| 3 | 3 | 7 | - | 6 | sum≤6 → YES | 3 |
| 4 | 3 | 6 | 1 | 7 | sum>6 → L++ |  |
| 4 | 4 | 7 | - | 2 | sum≤6 → YES | 3 |

Jawaban: 3 (subarray `[1,3,2]` atau `[2,5]` tidak valid, `[5,1]`=6 valid panjang 2)

**Kompleksitas**: O(n) time (setiap elemen masuk dan keluar window paling satu kali), O(1) space

---

## 10. Merge Two Sorted Arrays

### Problem Statement
Diberikan dua sorted array A[n] dan B[m]. Gabungkan menjadi satu sorted array.

### Strategi
Gunakan dua pointer `i` dan `j`, masing-masing untuk A dan B. Selalu ambil elemen yang lebih kecil.

```
A: [1, 3, 5]     i→
B: [2, 4, 6]     j→
Result: []

Step 1: A[0]=1 < B[0]=2 → ambil A[0], i++
Result: [1]

Step 2: A[1]=3 > B[0]=2 → ambil B[0], j++
Result: [1, 2]

Step 3: A[1]=3 < B[1]=4 → ambil A[1], i++
Result: [1, 2, 3]

Step 4: A[2]=5 > B[1]=4 → ambil B[1], j++
Result: [1, 2, 3, 4]

Step 5: A[2]=5 < B[2]=6 → ambil A[2], i++
Result: [1, 2, 3, 4, 5]

i = n, selesai. Sisa B: [6]
Step 6: ambil B[2]=6
Result: [1, 2, 3, 4, 5, 6]
```

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> A(n), B(m);
    for (auto& x : A) cin >> x;
    for (auto& x : B) cin >> x;

    vector<int> res;
    int i = 0, j = 0;

    while (i < n && j < m) {
        if (A[i] <= B[j]) res.push_back(A[i++]);
        else               res.push_back(B[j++]);
    }
    while (i < n) res.push_back(A[i++]);
    while (j < m) res.push_back(B[j++]);

    for (int k = 0; k < (int)res.size(); k++)
        cout << res[k] << " \n"[k == (int)res.size() - 1];

    return 0;
}
```

**Kompleksitas**: O(n+m) time, O(n+m) space

---

## 11. Dutch National Flag

### Problem Statement
Diberikan array yang hanya berisi 0, 1, dan 2. Sort in-place tanpa menggunakan sorting biasa.

### Strategi: Three Pointers
- `low`: batas 0s (semua 0 di kiri low)
- `mid`: elemen yang sedang diproses
- `high`: batas 2s (semua 2 di kanan high)

**Invariant**:
- `A[0..low-1]` = semua 0
- `A[low..mid-1]` = semua 1
- `A[mid..high]` = belum diproses
- `A[high+1..n-1]` = semua 2

### Visualisasi

```
A = [0, 1, 2, 1, 0, 2]
     0  1  2  3  4  5

low=0, mid=0, high=5

Step 1: A[mid=0]=0 → swap(A[low],A[mid]), low++, mid++
A = [0, 1, 2, 1, 0, 2]
low=1, mid=1, high=5

Step 2: A[mid=1]=1 → mid++
A = [0, 1, 2, 1, 0, 2]
low=1, mid=2, high=5

Step 3: A[mid=2]=2 → swap(A[mid],A[high]), high--
A = [0, 1, 2, 1, 0, 2] → swap(A[2],A[5]) → [0, 1, 2, 1, 0, 2]
     hmm: A[2]=2, A[5]=2. No change visually.
A = [0, 1, 2, 1, 0, 2]
low=1, mid=2, high=4

Step 4: A[mid=2]=2 → swap(A[mid],A[high]), high--
A = swap(A[2],A[4]) = [0, 1, 0, 1, 2, 2]
low=1, mid=2, high=3

Step 5: A[mid=2]=0 → swap(A[low],A[mid]), low++, mid++
A = swap(A[1],A[2]) = [0, 0, 1, 1, 2, 2]
low=2, mid=3, high=3

Step 6: A[mid=3]=1 → mid++
mid=4 > high=3 → STOP

Result: [0, 0, 1, 1, 2, 2] ← Sorted!
```

### Implementasi

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    int low = 0, mid = 0, high = n - 1;

    while (mid <= high) {
        if (A[mid] == 0) {
            swap(A[low], A[mid]);
            low++; mid++;
        } else if (A[mid] == 1) {
            mid++;
        } else { // A[mid] == 2
            swap(A[mid], A[high]);
            high--;
            // Jangan mid++! A[mid] baru belum diproses
        }
    }

    for (int i = 0; i < n; i++)
        cout << A[i] << " \n"[i == n-1];

    return 0;
}
```

**Penting**: Ketika swap dengan `high`, kita TIDAK increment `mid` karena elemen yang baru di `mid` belum diproses!

**Kompleksitas**: O(n) time, O(1) space

---

## 12. Kapan Two Pointers Efektif

### Decision Guide

```
Apakah array perlu di-sort?
    └─ Pair sum = target?   → YES, sort dulu → Opposite Direction
    └─ Palindrome?          → Tidak perlu sort → Opposite Direction
    └─ Container Water?     → Tidak perlu sort → Opposite Direction

Apakah masalah melibatkan subarray/window?
    └─ Sum ≤ K? Length constraint? → Same Direction (Sliding Window)
    └─ Remove duplicates? → Same Direction (Slow-Fast)

Apakah ada dua struktur data terpisah?
    └─ Merge dua sorted array → Two Independent Pointers

Apakah perlu partition/grouping?
    └─ 3 grup (0, 1, 2) → Dutch National Flag
    └─ 2 grup → Satu pointer saja
```

### Tabel Perbandingan

| Problem Type | Pola | Sort Required? | Time | Space |
|-------------|------|----------------|------|-------|
| Pair sum = K | Opposite | YES | O(n) | O(1) |
| 3 sum = 0 | Outer + Opposite | YES | O(n²) | O(1) |
| Palindrome check | Opposite | NO | O(n) | O(1) |
| Container water | Opposite + Greedy | NO | O(n) | O(1) |
| Remove duplicates | Slow-Fast | Sorted input | O(n) | O(1) |
| Subarray sum ≤ K | Sliding Window | NO | O(n) | O(1) |
| Merge sorted | Two independent | Sorted input | O(n+m) | O(n+m) |
| Dutch Flag | 3 pointers | NO | O(n) | O(1) |

---

## 13. Analisis Kompleksitas

### Mengapa O(n)?

Dalam two pointers (opposite direction):
- L dimulai di 0, bisa bergerak paling banyak **n** langkah ke kanan
- R dimulai di n-1, bisa bergerak paling banyak **n** langkah ke kiri
- Total langkah ≤ L_steps + R_steps ≤ n
- Setiap iterasi, minimal satu pointer bergerak → paling banyak n iterasi

```
Pointer L: 0 → 1 → 2 → ... → n-1    (at most n steps)
Pointer R: n-1 → n-2 → ... → 0     (at most n steps)
Total: O(n) combined steps
```

### Perbandingan dengan Brute Force

| Approach | Two Sum | Three Sum | Container |
|----------|---------|-----------|-----------|
| Brute Force | O(n²) | O(n³) | O(n²) |
| Two Pointers | O(n) | O(n²) | O(n) |
| Speedup | n× | n× | n× |

### Sliding Window Complexity

Sliding window (same direction):
- R bergerak dari 0 ke n-1: **n** steps
- L bergerak dari 0 ke n-1: **n** steps
- Total: O(2n) = **O(n)**

Setiap elemen masuk window tepat **1** kali dan keluar window tepat **1** kali.

---

## 14. Pitfalls & Tips

### Pitfall 1: Array Tidak Sorted

```cpp
// SALAH: array tidak sorted!
int A[] = {5, 1, 3, 7, 2};
// Two pointer tidak akan bekerja dengan benar

// BENAR: sort dulu
sort(A, A+n);
// Sekarang bisa pakai two pointer
```

### Pitfall 2: Infinite Loop

```cpp
// BAHAYA: tidak ada pointer yang bergerak jika keduanya sama
while (L < R) {
    if (A[L] + A[R] == T) {
        // process
        // LUPA L++ dan R-- ← INFINITE LOOP!
    }
}

// BENAR:
while (L < R) {
    if (A[L] + A[R] == T) {
        // process
        L++; R--;  // Selalu gerakkan setidaknya satu pointer
    }
}
```

### Pitfall 3: Skip Duplikat Pada Three Sum

```cpp
// SALAH: tanpa skip duplikat → triplet duplikat
while (L < R) {
    if (A[i]+A[L]+A[R] == 0) {
        ans.push_back({A[i], A[L], A[R]});
        L++; R--;  // Tidak skip duplikat
    }
}

// BENAR: skip duplikat
while (L < R) {
    if (A[i]+A[L]+A[R] == 0) {
        ans.push_back({A[i], A[L], A[R]});
        while (L < R && A[L] == A[L+1]) L++;
        while (L < R && A[R] == A[R-1]) R--;
        L++; R--;
    }
}
```

### Pitfall 4: Dutch Flag — Jangan Increment mid Saat Swap dengan high

```cpp
// SALAH:
if (A[mid] == 2) {
    swap(A[mid], A[high]);
    high--;
    mid++;  // SALAH! Elemen baru di mid belum diproses
}

// BENAR:
if (A[mid] == 2) {
    swap(A[mid], A[high]);
    high--;
    // mid TIDAK di-increment
}
```

### Pitfall 5: Off-by-One Boundary

```cpp
// Opposite Direction: gunakan L < R, bukan L <= R
// L == R berarti pointer menunjuk elemen yang sama
// Kita tidak ingin menggunakan satu elemen dua kali

while (L < R) { ... }   // BENAR
while (L <= R) { ... }  // SALAH untuk pair problems
```

### Tips Praktis

1. **Sort dulu** jika problem melibatkan pair/triplet sum
2. **Gambar trace table** untuk debug — tulis L, R, sum di setiap langkah
3. **Handle edge cases**: array kosong, satu elemen, semua elemen sama
4. **Untuk three sum**: sort + skip outer duplicates + skip inner duplicates
5. **Sliding window**: gunakan `while` untuk shrink (bukan `if`) karena mungkin perlu shrink beberapa kali
6. **Dutch Flag**: ingat `mid` tidak maju saat swap dengan `high`

---

## Summary: Semua Pola Two Pointers

```
┌──────────────────────────────────────────────────────────────────┐
│                     TWO POINTERS PATTERNS                        │
├──────────────────┬───────────────────────────────────────────────┤
│ POLA             │ KAPAN DIGUNAKAN                               │
├──────────────────┼───────────────────────────────────────────────┤
│ Opposite Dir     │ Pair sum, palindrome, container water         │
│ L=0, R=n-1       │ PRE: sorted (untuk sum problems)             │
│ Bertemu di tengah│ MOVE: pointer kecil ke arah yang besar        │
├──────────────────┼───────────────────────────────────────────────┤
│ Same Direction   │ Remove duplicates, move zeros, valid          │
│ slow=0, fast=0   │ subarray/window problems                      │
│ fast selalu maju │ MOVE: slow hanya saat kondisi valid           │
├──────────────────┼───────────────────────────────────────────────┤
│ Sliding Window   │ Subarray dengan constraint (sum, length)      │
│ L=0, R=0         │ PRE: elemen non-negatif untuk sum ≤ K        │
│ Shrink dari kiri │ SHRINK: saat constraint violated              │
├──────────────────┼───────────────────────────────────────────────┤
│ Merge            │ Combine dua sorted arrays/lists               │
│ i=0, j=0         │ PRE: kedua array sorted                      │
│ Independent ptrs │ ADVANCE: pointer dengan elemen lebih kecil    │
├──────────────────┼───────────────────────────────────────────────┤
│ Dutch Flag       │ 3-way partition (0, 1, 2)                     │
│ low,mid,high     │ PRE: elemen hanya 0, 1, 2                    │
│ mid hingga high  │ CAREFUL: jangan mid++ saat swap dengan high   │
└──────────────────┴───────────────────────────────────────────────┘
```

---

*Day 19 — Two Pointers | Competitive Programming Learning*
