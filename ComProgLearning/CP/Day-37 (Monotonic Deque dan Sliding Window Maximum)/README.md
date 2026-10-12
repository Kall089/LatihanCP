# Day 38 — Queue & Deque Applications

## Tujuan Pembelajaran

- [ ] Menguasai operasi Queue FIFO di C++ (`std::queue`)
- [ ] Memahami Deque double-ended dan bedanya dengan Queue/Stack
- [ ] Mengimplementasikan Sliding Window Maximum dalam O(n) dengan deque
- [ ] Mengimplementasikan Sliding Window Minimum dalam O(n) dengan deque
- [ ] Memecahkan First Non-Repeating Character in Stream
- [ ] Menggunakan Queue untuk BFS Level Order Traversal

---

## Struktur Folder

```
Day-38 (Queue and Deque Applications)/
├── README.md
├── teori/
│   ├── Day_38_Teori_Lengkap.md       ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_38_Presentation.pptx     ← Presentasi 15 slide
├── latihan/
│   ├── exercise_1.cpp  ← Round-Robin Queue Simulation
│   ├── exercise_2.cpp  ← Deque as Stack & Queue
│   ├── exercise_3.cpp  ← Sliding Window Maximum
│   ├── exercise_4.cpp  ← Sliding Window Minimum
│   ├── exercise_5.cpp  ← First Non-Repeating in Stream
│   └── exercise_6.cpp  ← BFS Level Order Traversal
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_38_Teori_Lengkap.md` (atau buka PPT)
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | Round-Robin Queue Simulation | Warm-up |
| exercise_2.cpp | Deque as Stack & Queue | Warm-up |
| exercise_3.cpp | Sliding Window Maximum | Core |
| exercise_4.cpp | Sliding Window Minimum | Core |
| exercise_5.cpp | First Non-Repeating in Stream | Core |
| exercise_6.cpp | BFS Level Order Traversal | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Queue Reversal | Easy |
| tugas_02 | Implement Stack using Queue | Easy |
| tugas_03 | Implement Queue using Stack | Easy |
| tugas_04 | Moving Average in Data Stream | Easy |
| tugas_05 | Number of Recent Calls | Medium |
| tugas_06 | Sliding Window Min-Max Range | Medium |
| tugas_07 | Jump Game VI | Medium |
| tugas_08 | Constrained Subsequence Sum | Medium |
| tugas_09 | Shortest Subarray Sum ≥ K | Medium |
| tugas_10 | Longest Subarray with AbsDiff ≤ K | Medium |
| tugas_11 | Max Sum Non-Adjacent (Deque DP) | Hard |
| tugas_12 | Minimum Cost to Cut Stick | Hard |
| tugas_13 | Sliding Window Median | Hard |
| tugas_14 | Minimum Window Subsequence | Hard |
| tugas_15 | Minimum Swaps to Sort Subarrays | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 239   | Sliding Window Maximum | Deque Monotonic |
| LC 862   | Shortest Subarray Sum ≥ K | Deque |
| LC 1438  | Longest Subarray Abs Diff ≤ K | Deque |
| GFG      | First Non-Repeating Character | Queue + freq |
| LC 933   | Number of Recent Calls | Queue |
| LC 102   | Binary Tree Level Order | BFS Queue |
| CSES     | Sliding Window Cost | Deque |
| LC 1696  | Jump Game VI | Deque DP |

---

## Common Mistakes

1. **Lupa pop_front sebelum compare nilai** → cek `dq.front() <= i - k` DULU
2. **Max vs Min: arah pop_back terbalik** → max: `<=`, min: `>=`
3. **BFS: loop inner tidak pakai sz** → simpan `sz = q.size()` di awal level
4. **First Non-Repeating: pakai if, bukan while** → harus WHILE untuk strip semua duplikat
5. **Deque menyimpan nilai, bukan index** → sliding window wajib simpan INDEX

---

## Quick Cheatsheet

```cpp
// Sliding Window MAX — monotonic decreasing deque
while (!dq.empty() && dq.front() <= i-k) dq.pop_front();  // out of window
while (!dq.empty() && A[dq.back()] <= A[i]) dq.pop_back(); // useless
dq.push_back(i);
if (i >= k-1) res.push_back(A[dq.front()]);

// Sliding Window MIN — ganti <= dengan >=
while (!dq.empty() && A[dq.back()] >= A[i]) dq.pop_back();

// First Non-Repeating
freq[c-'a']++;
q.push(c);
while (!q.empty() && freq[q.front()-'a'] > 1) q.pop();
ans += q.empty() ? '#' : q.front();

// BFS Level Order
while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; i++) { /* process + push children */ }
}
```
