# Day 20 — Sliding Window

## Deskripsi Topik

**Sliding Window** adalah teknik untuk memproses subarray/substring kontinu secara efisien dengan "menggeser" sebuah window di sepanjang array. Alih-alih menghitung ulang setiap window dari awal (O(n·k)), kita memanfaatkan tumpang-tindih antar window untuk turun menjadi O(n).

Ada dua varian utama:
- **Fixed-Size Window** — ukuran window K tetap, geser 1 langkah ke kanan tiap iterasi
- **Variable-Size Window** — ukuran window dinamis, expand R sampai kondisi tercapai/violated, lalu shrink L

---

## Tujuan Pembelajaran

- [ ] Memahami konsep sliding window dan kapan menggunakannya
- [ ] Mengimplementasikan **Fixed-Size Sliding Window** untuk sum/average subarray
- [ ] Mengimplementasikan **Variable-Size Sliding Window** untuk longest/smallest subarray dengan constraint
- [ ] Menggunakan **frequency map** di dalam window untuk konstrain karakter
- [ ] Mengimplementasikan **Monotonic Deque** untuk window maximum/minimum O(n)
- [ ] Membedakan kapan pakai sliding window vs two pointers vs prefix sum
- [ ] Memahami kondisi pre-syarat: monotonicity / non-negative
- [ ] Menganalisis kompleksitas amortized O(n) — tiap elemen masuk & keluar window 1× saja
- [ ] Menghindari pitfalls umum (off-by-one, window invalid, shrink berlebihan)

---

## Struktur Folder

```
Day-20 (Sliding Window)/
├── README.md                      ← Panduan ini
├── teori/
│   ├── Day_20_Teori_Lengkap.md   ← Teori lengkap dengan trace table
│   ├── generate_presentation.py  ← Script untuk generate PPT
│   └── Day_20_Presentation.pptx  ← (generated)
├── latihan/
│   ├── exercise_1.cpp            ← Maximum Sum Subarray Size K (Fixed)
│   ├── exercise_2.cpp            ← First Negative in Every Window (Fixed)
│   ├── exercise_3.cpp            ← Smallest Subarray with Sum ≥ S (Variable)
│   ├── exercise_4.cpp            ← Longest Substring K Distinct Chars (Variable)
│   ├── exercise_5.cpp            ← Sliding Window Maximum (Deque)
│   └── exercise_6.cpp            ← Longest Substring Without Repeat (Variable)
├── solusi/
│   ├── solution_1.cpp — solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp — tugas_15.cpp   ← 15 tugas mandiri
└── template/
    └── template.cpp              ← Template pola sliding window
```

---

## Panduan Belajar

### Langkah 1 — Baca Teori (45 menit)
Baca `teori/Day_20_Teori_Lengkap.md` dari awal hingga akhir. Perhatikan:
- Diagram window yang bergerak (ASCII)
- Trace table per langkah expand/shrink
- Proof correctness amortized O(n)

### Langkah 2 — Lihat Presentasi (15 menit)
```bash
cd teori/
python3 generate_presentation.py
```
Buka `Day_20_Presentation.pptx`.

### Langkah 3 — Kerjakan Latihan (60–90 menit)
Kerjakan exercise 1–6 **tanpa melihat solusi**. Mulai dari fixed-size dulu, baru variable-size.

### Langkah 4 — Cek Solusi
Bandingkan approach kamu dengan `solusi/`. Perhatikan edge cases (window kosong, n < k).

### Langkah 5 — Kerjakan Tugas (90–120 menit)
- Easy: tugas_01–05 (semua harus dikerjakan)
- Medium: pilih 3 dari tugas_06–10
- Hard: pilih 2 dari tugas_11–15

### Langkah 6 — Online Judge
Submit ke platform online judge untuk validasi.

---

## Ringkasan Latihan

| No | File | Topik | Kesulitan | Konsep Kunci |
|----|------|-------|-----------|--------------|
| 1 | exercise_1.cpp | Maximum Sum Subarray Size K | ★☆☆☆☆ | Fixed window, sum maintenance |
| 2 | exercise_2.cpp | First Negative in Every Window | ★★☆☆☆ | Fixed window, deque tracking |
| 3 | exercise_3.cpp | Smallest Subarray with Sum ≥ S | ★★☆☆☆ | Variable window, shrink while valid |
| 4 | exercise_4.cpp | Longest Substring K Distinct | ★★★☆☆ | Variable window + freq map |
| 5 | exercise_5.cpp | Sliding Window Maximum | ★★★☆☆ | Monotonic deque |
| 6 | exercise_6.cpp | Longest Substring Without Repeat | ★★★☆☆ | Variable window + last-seen map |

---

## Ringkasan Tugas (15 Soal)

| No | Topik | Kesulitan | Kategori |
|----|-------|-----------|----------|
| 01 | Sum of All Subarrays Size K | ★☆☆☆☆ | Easy |
| 02 | Maximum Average Subarray | ★☆☆☆☆ | Easy |
| 03 | Count Vowels in Window K | ★☆☆☆☆ | Easy |
| 04 | Find All Anagrams (Fixed Window) | ★★☆☆☆ | Easy |
| 05 | Longest Subarray Sum ≤ K | ★★☆☆☆ | Easy |
| 06 | Subarray with Exactly K Distinct | ★★★☆☆ | Medium |
| 07 | Longest Repeating Character Replacement | ★★★☆☆ | Medium |
| 08 | Maximum Erasure Value (Unique Subarray) | ★★★☆☆ | Medium |
| 09 | Permutation in String | ★★★☆☆ | Medium |
| 10 | Count Number of Nice Subarrays (Odd K) | ★★★☆☆ | Medium |
| 11 | Minimum Window Substring | ★★★★☆ | Hard |
| 12 | Sliding Window Median | ★★★★★ | Hard |
| 13 | Subarrays with K Different Integers | ★★★★☆ | Hard |
| 14 | Longest Substring with At Most 2 Distinct | ★★★☆☆ | Hard |
| 15 | Maximum Number of Vowels in Substring | ★★☆☆☆ | Hard |

---

## Rekomendasi Online Judge

### LeetCode
| Problem | Judul | Tingkat |
|---------|-------|---------|
| #643 | Maximum Average Subarray I | Easy |
| #209 | Minimum Size Subarray Sum | Medium |
| #3 | Longest Substring Without Repeat | Medium |
| #438 | Find All Anagrams in a String | Medium |
| #239 | Sliding Window Maximum | Hard |
| #76 | Minimum Window Substring | Hard |
| #340 | Longest Substring K Distinct | Medium |
| #424 | Longest Repeating Char Replacement | Medium |
| #1004 | Max Consecutive Ones III | Medium |
| #992 | Subarrays with K Different | Hard |

### CSES (cses.fi)
| Problem | Judul |
|---------|-------|
| 1141 | Playlist (longest unique subarray) |
| 1640 | Sum of Two Values |
| 1077 | Sliding Median |
| 1076 | Sliding Window Cost |

### Codeforces
| Round | Problem | Topik |
|-------|---------|-------|
| CF 1208B | Uniqueness | Variable window |
| CF 814C | An impassioned circulation | Sliding window |
| CF 488B | Candy Boxes | Two pointer/window |

---

## Kesalahan Umum (Common Mistakes)

1. **Pakai `if` bukan `while` saat shrink** — Kondisi violated bisa berlangsung beberapa langkah, harus pakai `while` agar window benar-benar valid kembali.

2. **Lupa update jawaban setelah shrink** — Update `ans` setelah window valid, bukan sebelum. Kalau di-update sebelum shrink, kemungkinan ans di-update dengan window invalid.

3. **Inisialisasi window pertama salah** — Untuk fixed-size window, inisialisasi sum 0..K-1 dulu sebelum memulai loop slide dari K.

4. **Sliding window pada nilai negatif** — Sliding window untuk "subarray sum ≤ K" hanya bekerja jika semua elemen non-negatif. Jika ada negatif, gunakan prefix sum + map / deque.

5. **Frequency map tidak di-erase saat 0** — Saat element keluar window, `freq[x]--`. Jika menjadi 0, harus `erase` agar `map.size()` mencerminkan distinct count yang benar.

6. **Off-by-one window size** — Window [L, R] inclusive berarti panjang = R - L + 1, BUKAN R - L. Salah hitung sering jadi sumber bug.

7. **Monotonic deque tidak konsisten** — Saat window slide, harus pop dari front jika index out of window, dan pop dari back jika nilai baru lebih dominan. Lupa salah satu = bug.

---

## Quick Reference Cheatsheet

### Pola Sliding Window

```
POLA 1: FIXED-SIZE WINDOW
━━━━━━━━━━━━━━━━━━━━━━━━━
Use for: max/min/avg subarray ukuran K, count fitur per window

ll sum = 0;
for (int i = 0; i < k; i++) sum += A[i];   // initial window
ll ans = sum;
for (int i = k; i < n; i++) {
    sum += A[i] - A[i-k];                  // slide: tambah baru, kurangi lama
    ans = max(ans, sum);
}

─────────────────────────────────────────────

POLA 2: VARIABLE-SIZE WINDOW (Longest)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use for: longest subarray dengan constraint

int L = 0, ans = 0;
for (int R = 0; R < n; R++) {
    add(A[R]);                             // expand
    while (window_invalid()) {             // shrink sampai valid
        remove(A[L]);
        L++;
    }
    ans = max(ans, R - L + 1);             // update jawaban
}

─────────────────────────────────────────────

POLA 3: VARIABLE-SIZE WINDOW (Shortest ≥ Target)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use for: smallest subarray dengan sum ≥ S

int L = 0, ans = INT_MAX;
ll sum = 0;
for (int R = 0; R < n; R++) {
    sum += A[R];                           // expand
    while (sum >= S) {                     // shrink while valid
        ans = min(ans, R - L + 1);
        sum -= A[L];
        L++;
    }
}

─────────────────────────────────────────────

POLA 4: MONOTONIC DEQUE — WINDOW MAX/MIN O(n)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Use for: maximum/minimum tiap window ukuran K

deque<int> dq;  // simpan INDEX, bukan value
for (int i = 0; i < n; i++) {
    // Pop elemen yang sudah keluar window
    while (!dq.empty() && dq.front() <= i - k)
        dq.pop_front();
    // Pop elemen kecil dari belakang (untuk max)
    while (!dq.empty() && A[dq.back()] <= A[i])
        dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) cout << A[dq.front()] << " ";
}
```

### Keputusan Pola

```
Window ukurannya TETAP (= K)?
    └─ POLA 1: Fixed-Size Window
        └─ Butuh max/min? → Tambah Monotonic Deque (POLA 4)

Window ukurannya VARIABEL?
    ├─ Cari subarray TERPANJANG yang valid?
    │  └─ POLA 2: Expand R, shrink saat invalid
    └─ Cari subarray TERPENDEK ≥ target?
       └─ POLA 3: Expand R, shrink while valid
```

---

## Kompleksitas Algoritma

| Algoritma | Time | Space | Keterangan |
|-----------|------|-------|------------|
| Fixed Window Sum | O(n) | O(1) | Slide tambah/kurangi |
| Variable Window (sum/count) | O(n) | O(1) | Tiap elemen masuk/keluar 1× |
| Variable Window + Freq Map | O(n) | O(K) | K = jumlah karakter unik |
| Sliding Window Maximum (Deque) | O(n) | O(K) | Tiap elemen push/pop 1× |
| Sliding Window Median (Multiset) | O(n log n) | O(K) | Insert/erase log K per slide |

---

*Day 20 — Sliding Window | Competitive Programming Learning*
