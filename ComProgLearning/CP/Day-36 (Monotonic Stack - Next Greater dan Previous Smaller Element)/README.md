# Day 36 — Stack Applications

## Tujuan Pembelajaran

- [ ] Mengimplementasikan validasi balanced brackets dengan stack
- [ ] Memahami konsep **Monotonic Stack** dan mengapa O(n)
- [ ] Menguasai Next Greater Element (NGE) dan Previous Smaller Element (PSE)
- [ ] Menyelesaikan Stock Span Problem
- [ ] Mengimplementasikan Largest Rectangle in Histogram
- [ ] Memecahkan Trapping Rain Water dengan dua pendekatan
- [ ] Mengaplikasikan teknik histogram ke masalah binary matrix

---

## Struktur Folder

```
Day-36 (Stack Applications)/
├── README.md
├── teori/
│   ├── Day_36_Teori_Lengkap.md       ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_36_Presentation.pptx     ← Presentasi 16 slide
├── latihan/
│   ├── exercise_1.cpp  ← Balanced Brackets
│   ├── exercise_2.cpp  ← Next Greater Element
│   ├── exercise_3.cpp  ← Previous Smaller Element
│   ├── exercise_4.cpp  ← Stock Span Problem
│   ├── exercise_5.cpp  ← Largest Rectangle in Histogram
│   └── exercise_6.cpp  ← Trapping Rain Water
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_36_Teori_Lengkap.md` (atau buka PPT)
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | Balanced Brackets () [] {} | Warm-up |
| exercise_2.cpp | Next Greater Element | Core |
| exercise_3.cpp | Previous Smaller Element | Core |
| exercise_4.cpp | Stock Span Problem | Core |
| exercise_5.cpp | Largest Rectangle in Histogram | Challenge |
| exercise_6.cpp | Trapping Rain Water | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Balanced Parentheses Count | Easy |
| tugas_02 | Valid Bracket Min Add | Easy |
| tugas_03 | Remove Outer Brackets | Easy |
| tugas_04 | Score of Brackets | Easy |
| tugas_05 | NGE Circular Array | Medium |
| tugas_06 | Daily Temperatures | Medium |
| tugas_07 | Max Area Rectangle in Binary Matrix | Medium |
| tugas_08 | Sliding Window Maximum | Medium |
| tugas_09 | 132 Pattern | Medium |
| tugas_10 | Decode String | Medium |
| tugas_11 | Largest Rectangle Sum | Hard |
| tugas_12 | Asteroid Collision | Hard |
| tugas_13 | Min Stack Design | Hard |
| tugas_14 | Maximal Score After Removals | Hard |
| tugas_15 | Rain Water Histogram Variant | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 20    | Valid Parentheses | Balanced Brackets |
| LC 496   | Next Greater Element I | NGE |
| CSES     | Nearest Smaller Values | PSE |
| LC 739   | Daily Temperatures | NGE variasi |
| LC 84    | Largest Rectangle in Histogram | Histogram |
| LC 42    | Trapping Rain Water | Rain water |
| LC 85    | Maximal Rectangle | Matrix + Histogram |
| LC 503   | Next Greater Element II | NGE Circular |

---

## Common Mistakes

1. **Lupa cek `st.empty()` sebelum `st.top()`** → segfault/UB
2. **Histogram width = `i - st.top() - 1`** (bukan `i - st.top()`)
3. **NGE: push index SETELAH while loop**, bukan di dalam
4. **Balanced: cek `st.empty()` di akhir** (bukan hanya saat traversal)

---

## Quick Cheatsheet

```cpp
// Balanced Brackets
if (c == '(' || c == '[' || c == '{') st.push(c);
else { /* match & pop */ }
return st.empty();

// NGE: monotonic decreasing stack
while (!st.empty() && A[st.top()] < A[i])
    { nge[st.top()] = A[i]; st.pop(); }
st.push(i);

// Histogram
while (!st.empty() && h[st.top()] > cur) {
    ll H = h[st.top()]; st.pop();
    ll W = st.empty() ? i : i - st.top() - 1;
    ans = max(ans, H * W);
}
```
