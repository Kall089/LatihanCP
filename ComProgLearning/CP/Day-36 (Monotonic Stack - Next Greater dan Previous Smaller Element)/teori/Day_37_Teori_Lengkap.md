# Day 37 — Monotonic Stack (Advanced)

## Tujuan Pembelajaran
- [ ] Memahami teknik kontribusi untuk Sum of Subarray Minimums
- [ ] Menguasai Remove K Digits dengan monotonic stack greedy
- [ ] Memahami Car Fleet problem dengan stack
- [ ] Mengimplementasikan evaluasi ekspresi RPN
- [ ] Memecahkan Longest Valid Parentheses dalam O(n)
- [ ] Menggunakan Maximum Width Ramp dengan two-pass monotonic stack

---

## 1. Kontribusi Elemen — Sum of Subarray Minimums

### Masalah
Diberikan array A, hitung jumlah semua minimum dari setiap subarray.

### Kunci Ide: Kontribusi Elemen
Untuk setiap elemen A[i], hitung berapa banyak subarray yang memiliki A[i] sebagai minimum-nya, lalu kontribusinya = A[i] × count.

### Definisi Batas
- `left[i]` = jumlah elemen berturut-turut dari kiri di mana A[i] adalah yang terkecil (termasuk A[i])
- `right[i]` = jumlah elemen berturut-turut dari kanan di mana A[i] adalah yang terkecil (termasuk A[i])

**Catatan**: Gunakan strict (<) di satu sisi dan non-strict (≤) di sisi lain untuk menghindari double counting duplikat.

### Algoritma

```cpp
const int MOD = 1e9 + 7;

long long sumSubarrayMins(vector<int>& A) {
    int n = A.size();
    vector<long long> left(n), right(n);
    stack<int> st;

    // left[i]: berapa subarray dengan A[i] sebagai min dari kiri
    for (int i = 0; i < n; i++) {
        while (!st.empty() && A[st.top()] >= A[i]) st.pop(); // strict >=
        left[i] = st.empty() ? i + 1 : i - st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // right[i]: berapa subarray dengan A[i] sebagai min dari kanan
    for (int i = n-1; i >= 0; i--) {
        while (!st.empty() && A[st.top()] > A[i]) st.pop(); // non-strict >
        right[i] = st.empty() ? n - i : st.top() - i;
        st.push(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans = (ans + (long long)A[i] % MOD * left[i] % MOD * right[i]) % MOD;

    return ans;
}
```

### Contoh Trace
Array: `[3, 1, 2, 4]`

| i | A[i] | left[i] | right[i] | Kontribusi |
|---|------|---------|----------|------------|
| 0 | 3    | 1       | 1        | 3×1×1 = 3  |
| 1 | 1    | 2       | 3        | 1×2×3 = 6  |
| 2 | 2    | 1       | 2        | 2×1×2 = 4  |
| 3 | 4    | 1       | 1        | 4×1×1 = 4  |

Total = 3 + 6 + 4 + 4 = **17**

**Verifikasi manual**: semua subarray = [3],[1],[2],[4],[3,1],[1,2],[2,4],[3,1,2],[1,2,4],[3,1,2,4]
Min-nya = 3,1,2,4,1,1,2,1,1,1 → sum = 17 ✓

---

## 2. Remove K Digits

### Masalah
Diberikan string angka dan integer k, hapus k digit sehingga angka yang tersisa adalah yang terkecil.

### Strategi Greedy
Gunakan monotonic increasing stack. Saat digit baru lebih kecil dari top stack dan masih ada k penghapusan, pop top (artinya kita hapus digit lebih besar di sebelah kiri).

```cpp
string removeKdigits(string num, int k) {
    string st; // digunakan sebagai stack (string itu sendiri)
    for (char c : num) {
        while (k > 0 && !st.empty() && st.back() > c) {
            st.pop_back();
            k--;
        }
        st.push_back(c);
    }
    // Hapus sisa k dari belakang
    while (k--) st.pop_back();

    // Hapus leading zeros
    int start = 0;
    while (start < (int)st.size() - 1 && st[start] == '0') start++;

    return st.substr(start);
}
```

### Contoh Trace
`num = "1432219"`, `k = 3`

| Langkah | Stack  | Aksi              |
|---------|--------|-------------------|
| '1'     | "1"    | push              |
| '4'     | "14"   | push (4 > 1)      |
| '3'     | "13"   | pop '4', k=2      |
| '2'     | "12"   | pop '3', k=1      |
| '2'     | "122"  | push (2 = 2)      |
| '1'     | "121"  | pop '2', k=0      |
| '9'     | "1219" | push (k=0 stop)   |

Hasil: `"1219"` ✓

---

## 3. Car Fleet

### Masalah
n mobil menuju target. Setiap mobil di posisi `pos[i]` dengan kecepatan `speed[i]`. Mobil yang lebih lambat akan membentuk fleet bersama mobil yang mengejarnya. Hitung jumlah fleet.

### Algoritma
1. Urutkan mobil berdasarkan posisi (terdekat ke target → terjauh)
2. Hitung waktu tempuh setiap mobil: `time[i] = (target - pos[i]) / speed[i]`
3. Gunakan stack: jika `time[i] ≤ stack.top()`, mobil bergabung ke fleet → tidak push
4. Jumlah fleet = ukuran stack akhir

```cpp
int carFleet(int target, vector<int>& pos, vector<int>& speed) {
    int n = pos.size();
    vector<pair<int,double>> cars(n);
    for (int i = 0; i < n; i++)
        cars[i] = {pos[i], (double)(target - pos[i]) / speed[i]};

    sort(cars.begin(), cars.end(), greater<>());

    stack<double> st;
    for (auto& [p, t] : cars) {
        if (st.empty() || t > st.top())
            st.push(t);
        // else: bergabung ke fleet yang lebih depan
    }
    return st.size();
}
```

---

## 4. Evaluate Reverse Polish Notation (RPN)

### Masalah
Evaluasi ekspresi dalam notasi RPN (postfix). Operand di-push ke stack, operator mengambil dua operand dari stack.

```cpp
int evalRPN(vector<string>& tokens) {
    stack<long long> st;
    for (auto& t : tokens) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            long long b = st.top(); st.pop();
            long long a = st.top(); st.pop();
            if      (t == "+") st.push(a + b);
            else if (t == "-") st.push(a - b);
            else if (t == "*") st.push(a * b);
            else               st.push(a / b); // truncate toward zero
        } else {
            st.push(stoll(t));
        }
    }
    return st.top();
}
```

**Contoh**: `["2","1","+","3","*"]`
- push 2 → [2]
- push 1 → [2,1]
- `+` → pop 2,1 → push 3 → [3]
- push 3 → [3,3]
- `*` → pop 3,3 → push 9 → [9]
- Hasil: **9**

---

## 5. Longest Valid Parentheses

### Masalah
Temukan substring valid parentheses terpanjang.

### Algoritma dengan Stack
Stack menyimpan **index**. Inisialisasi dengan sentinel `-1`.

```cpp
int longestValidParentheses(string s) {
    stack<int> st;
    st.push(-1); // sentinel
    int ans = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            st.pop();
            if (st.empty()) {
                st.push(i); // new base
            } else {
                ans = max(ans, i - st.top());
            }
        }
    }
    return ans;
}
```

### Trace
`s = "()()"`

| i | s[i] | Stack   | ans |
|---|------|---------|-----|
| - | -    | [-1]    | 0   |
| 0 | '('  | [-1,0]  | 0   |
| 1 | ')'  | [-1]    | 2   |
| 2 | '('  | [-1,2]  | 2   |
| 3 | ')'  | [-1]    | 4   |

Jawaban: **4** ✓

---

## 6. Maximum Width Ramp

### Masalah
Ramp adalah (i, j) di mana i < j dan A[i] ≤ A[j]. Temukan j - i maksimum.

### Two-Pass Monotonic Stack

**Pass 1 (kanan ke kiri)**: Bangun monotonic decreasing stack dari indices (kandidat i terbaik).

**Pass 2 (kanan ke kiri)**: Untuk setiap j dari kanan, pop stack selama A[stack.top()] ≤ A[j] dan update jawaban.

```cpp
int maxWidthRamp(vector<int>& A) {
    int n = A.size();
    stack<int> st;

    // Pass 1: indices dengan nilai turun dari bawah ke atas
    for (int i = 0; i < n; i++)
        if (st.empty() || A[st.top()] > A[i])
            st.push(i);

    int ans = 0;
    // Pass 2: scan dari kanan
    for (int j = n-1; j >= 0 && !st.empty(); j--) {
        while (!st.empty() && A[st.top()] <= A[j]) {
            ans = max(ans, j - st.top());
            st.pop();
        }
    }
    return ans;
}
```

---

## 7. Kompleksitas

| Algoritma | Waktu | Ruang | Catatan |
|-----------|-------|-------|---------|
| Sum of Subarray Minimums | O(n) | O(n) | 2 pass monotonic |
| Remove K Digits | O(n) | O(n) | Greedy + stack |
| Car Fleet | O(n log n) | O(n) | Sort + stack |
| Evaluate RPN | O(n) | O(n) | Stack klasik |
| Longest Valid Parentheses | O(n) | O(n) | Index stack + sentinel |
| Maximum Width Ramp | O(n) | O(n) | Two-pass |

---

## 8. Common Mistakes

1. **Sum of Subarray Mins: double counting duplikat**
   - Gunakan `>=` di satu sisi dan `>` di sisi lain
   - Konsisten: left pakai `>=` (pop saat equal), right pakai `>` (tidak pop saat equal)

2. **Remove K Digits: leading zeros**
   - Setelah remove, trim leading zeros (tapi jaga minimal 1 digit "0")

3. **RPN: urutan operand**
   - `b = st.top(); pop(); a = st.top(); pop();` → operasi `a OP b` (bukan `b OP a`)
   - Penting untuk `-` dan `/`

4. **Longest Valid Parentheses: sentinel**
   - Tanpa sentinel `-1` awal, logika `st.empty()` tidak benar

5. **Maximum Width Ramp: pass 2 dari kanan**
   - Harus scan j dari kanan (n-1 ke 0), bukan dari kiri

---

## 9. Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 907 | Sum of Subarray Minimums | Kontribusi + monotonic |
| LC 402 | Remove K Digits | Greedy stack |
| LC 853 | Car Fleet | Sort + stack |
| LC 150 | Evaluate Reverse Polish Notation | Stack klasik |
| LC 32 | Longest Valid Parentheses | Index stack |
| LC 962 | Maximum Width Ramp | Two-pass stack |
| CSES | Nearest Smaller Values | Monotonic stack |
