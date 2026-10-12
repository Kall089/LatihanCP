#!/usr/bin/env python3
"""Day 3 — STL Containers 1 (Vector, String, Pair, Tuple)."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── 1. Cover ─────────────────────────────────────────────────
    def cov_deco(slide):
        # Visualisasi vector cells dengan label
        labels = ["vector", "string", "pair", "tuple"]
        cols = [PRIMARY, EMERALD, AMBER, VIOLET]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cy = 5.4 + i * 0.0  # pakai semua di satu baris
            cx = 6.5 + i * 1.6
            rounded_rect(slide, cx, 5.6, 1.4, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.4, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 3, "STL Containers I",
                ["Vector  ·  String  ·  Pair  ·  Tuple",
                 "Foundation untuk Semua CP Solutions"],
                decoration=cov_deco)

    # ── 2. Agenda ────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 3", [
        ("01", "Vector\nDinamis", PRIMARY,
         ["Deklarasi & init", "push/pop/access", "Iterasi & sort", "2D vector"]),
        ("02", "String\nManipulation", EMERALD,
         ["Substring & find", "Reverse & sort", "Konversi int↔string", "Frequency count"]),
        ("03", "Pair\nDua Nilai", AMBER,
         [".first / .second", "make_pair", "Sort by first/second", "Negate trick"]),
        ("04", "Tuple\nMulti-Nilai", VIOLET,
         ["get<i>", "make_tuple", "Structured binding", "Multi-criteria sort"]),
    ])

    # ── 3. Section 01 ────────────────────────────────────────────
    section_divider(prs, "01", "Vector — Array Dinamis",
                    "Container paling penting di CP, hampir di setiap soal")

    # ── 4. Vector Concept ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Vector?",
                 "Array yang ukurannya bisa berubah dinamis")
    # Kiri: penjelasan
    info_card(slide, "Konsep Vector", [
        "• Array dinamis — ukuran bisa bertambah/berkurang",
        "• Akses index O(1) — sama seperti array biasa",
        "• push_back() amortized O(1)",
        "• Otomatis manage memori — tidak perlu malloc/new",
        "• Default value 0 saat init dengan ukuran",
    ], 0.5, 1.1, 5.5, 3.2, accent=PRIMARY)

    # Kanan: vector visualization
    tb(slide, "vector<int> v = {3, 1, 4, 1, 5};", 6.3, 1.1, 6.5, 0.4,
       size=12, bold=True, color=AMBER, font_name="Menlo")
    array_cells(slide, [3, 1, 4, 1, 5], 6.3, 1.7,
                cell_w=0.7, cell_h=0.55,
                highlights={0: PRIMARY, 1: PRIMARY, 2: PRIMARY,
                            3: PRIMARY, 4: PRIMARY})

    tb(slide, "v.push_back(9);", 6.3, 2.7, 6.5, 0.35,
       size=11, color=EMERALD, font_name="Menlo")
    array_cells(slide, [3, 1, 4, 1, 5, 9], 6.3, 3.1,
                cell_w=0.7, cell_h=0.55,
                highlights={0: PRIMARY, 1: PRIMARY, 2: PRIMARY,
                            3: PRIMARY, 4: PRIMARY, 5: EMERALD})
    tb(slide, "↑ baru!", 10.6, 3.7, 1.0, 0.3, size=10, color=EMERALD)

    # Kompleksitas
    metric_card(slide, "Akses v[i]", "O(1)", 0.5, 4.7, 3.0, 1.2, accent=EMERALD)
    metric_card(slide, "push_back", "O(1)*", 3.7, 4.7, 3.0, 1.2, accent=PRIMARY)
    metric_card(slide, "Insert tengah", "O(n)", 6.9, 4.7, 3.0, 1.2, accent=ROSE)
    metric_card(slide, "Sort", "O(n log n)", 10.1, 4.7, 2.7, 1.2, accent=AMBER)
    tb(slide, "* amortized — kadang O(n) saat reallocation",
       0.5, 6.05, 12.0, 0.3, size=10, color=MUTED, italic=True)

    # ── 5. Vector Operations Code ────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Vector — Operasi Penting")

    code = """// === DEKLARASI ===
vector<int> v;              // kosong
vector<int> v(5);           // [0,0,0,0,0]
vector<int> v(5, -1);       // [-1,-1,-1,-1,-1]
vector<int> v = {3, 1, 4};  // initializer list

// === MODIFIKASI ===
v.push_back(10);   // tambah belakang   O(1)
v.pop_back();      // hapus belakang    O(1)
v.clear();         // hapus semua

// === AKSES ===
v[i];              // by index
v.front();         // elemen pertama
v.back();          // elemen terakhir
v.size();          // jumlah elemen
v.empty();         // bool kosong"""
    code_box(slide, code, 0.5, 1.1, 6.0, 5.5, font_size=10, accent=PRIMARY)

    code2 = """// === ITERASI ===
// Cara 1: index
for (int i = 0; i < v.size(); i++)
    cout << v[i] << " ";

// Cara 2: range-based (RECOMMENDED)
for (int x : v) cout << x << " ";

// Cara 3: reference (untuk modify)
for (int& x : v) x *= 2;

// === SORT & UNIQUE ===
sort(v.begin(), v.end());          // asc
sort(v.rbegin(), v.rend());        // desc
v.erase(unique(v.begin(),
        v.end()), v.end());        // remove dup"""
    code_box(slide, code2, 6.7, 1.1, 6.1, 5.5, font_size=10, accent=EMERALD)

    # ── 5b. Vector Internals: Capacity Trace + 2D Grid ──────────
    slide = new_slide(prs)
    slide_header(slide, "Vector Internals — Capacity & 2D Grid",
                 "Mengapa push_back amortized O(1)? Capacity digandakan!")

    # Left: Capacity trace table
    tb(slide, "Trace: push_back & Capacity Growth",
       0.5, 1.1, 6.3, 0.4, size=13, bold=True, color=PRIMARY)

    cap_rows = [
        ("vector<int> v;", "[]", "0", "0"),
        ("v.push_back(10);", "[10]", "1", "1"),
        ("v.push_back(20);", "[10,20]", "2", "2"),
        ("v.push_back(30);", "[10,20,30]", "3", "4 ← grow"),
        ("v.push_back(40);", "[10,20,30,40]", "4", "4"),
        ("v.push_back(50);", "[10,20,30,40,50]", "5", "8 ← grow"),
        ("v.pop_back();", "[10,20,30,40]", "4", "8"),
    ]
    headers = ["Operasi", "State", "Size", "Cap"]
    widths = [2.5, 2.0, 0.7, 1.0]
    rect(slide, 0.5, 1.55, sum(widths) - 0.04, 0.4, PRIMARY)
    cumx = 0.5
    for h, w in zip(headers, widths):
        tb(slide, h, cumx + 0.05, 1.6, w - 0.1, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cumx += w
    for ri, row in enumerate(cap_rows):
        ry = 1.96 + ri * 0.42
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        rect(slide, 0.5, ry, sum(widths) - 0.04, 0.4, bg)
        cumx = 0.5
        for ci, (cell, w) in enumerate(zip(row, widths)):
            col = AMBER if "grow" in cell else WHITE
            font = "Menlo" if ci != 0 else None
            tb(slide, cell, cumx + 0.05, ry + 0.07, w - 0.1, 0.3,
               size=9.5, color=col, font_name=font,
               align=PP_ALIGN.LEFT if ci == 0 else PP_ALIGN.CENTER)
            cumx += w

    callout(slide, "Capacity selalu power of 2 → amortized O(1)",
            0.5, 5.0, 6.3, 0.55, color=EMERALD)

    insight_card(slide, "Tips Performance",
                 ["v.reserve(n) jika tahu ukuran",
                  "Hindari realokasi berulang",
                  "emplace_back > push_back",
                  "vector<int>().swap(v) = free memory"],
                 0.5, 5.7, 6.3, 1.5)

    # Right: 2D Vector grid visualization
    tb(slide, "2D Vector — Grid / Matrix",
       7.0, 1.1, 5.8, 0.4, size=13, bold=True, color=AMBER)

    code_2d = """vector<vector<int>> grid(3, vector<int>(4, 0));
grid[1][2] = 5;
// 3 baris × 4 kolom, default 0"""
    plain_code_box(slide, code_2d, 7.0, 1.55, 5.8, 1.0, font_size=10,
                   accent=AMBER, text_color=SILVER)

    # Visualisasi 3x4 grid
    grid_x, grid_y = 7.5, 2.85
    cw, ch = 0.7, 0.55
    for r in range(3):
        for c in range(4):
            val = 5 if (r == 1 and c == 2) else 0
            cx = grid_x + c * (cw + 0.08)
            cy = grid_y + r * (ch + 0.08)
            cell_col = AMBER if val == 5 else BG_CARD_2
            txt_col = BG_DEEP if val == 5 else SLATE
            rounded_rect(slide, cx, cy, cw, ch, cell_col,
                         line_color=BORDER, line_w=0.5)
            tb(slide, str(val), cx, cy + 0.12, cw, 0.35,
               size=14, bold=True, color=txt_col, align=PP_ALIGN.CENTER)
            # Index labels (top row & left col)
            if r == 0:
                tb(slide, f"c={c}", cx, cy - 0.27, cw, 0.22,
                   size=9, color=MUTED, align=PP_ALIGN.CENTER)
            if c == 0:
                tb(slide, f"r={r}", cx - 0.45, cy + 0.17, 0.4, 0.25,
                   size=9, color=MUTED, align=PP_ALIGN.RIGHT)

    tb(slide, "↑ grid[1][2] = 5", 9.0, 4.8, 3.0, 0.3,
       size=11, bold=True, color=AMBER)

    info_card(slide, "Iterasi Grid",
              ["for (int i=0; i<n; i++)",
               "  for (int j=0; j<m; j++)",
               "    process(grid[i][j]);",
               "Inisial: vector<vector<T>>(n, vector<T>(m, val))"],
              7.0, 5.4, 5.8, 1.7, accent=PRIMARY)

    # ── 6. Section 02 ────────────────────────────────────────────
    section_divider(prs, "02", "String — Sequence of Characters",
                    "Manipulasi teks yang sering muncul di CP")

    # ── 7. String Operations ─────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "String — Operations Cheat Sheet")

    code = """string s = "hello";

// UKURAN
s.size() / s.length();      // 5

// AKSES
s[0];                       // 'h'
s.back();                   // 'o'

// MODIFIKASI
s += " world";              // concat
s.push_back('!');           // append char

// SUBSTRING & SEARCH
s.substr(0, 5);             // "hello"
s.substr(6);                // "world!"
s.find("lo");               // 3 (atau npos)

// REVERSE & SORT
reverse(s.begin(), s.end());
sort(s.begin(), s.end());

// KONVERSI
to_string(123);             // "123"
stoi("123");                // 123
stoll("999999999999");      // long long"""
    code_box(slide, code, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=EMERALD)

    # Right: Pattern usage
    tb(slide, "Pattern Umum di CP", 7.0, 1.1, 5.8, 0.4,
       size=14, bold=True, color=AMBER)

    info_card(slide, "Cek Palindrome", [
        "string rev = s;",
        "reverse(rev.begin(), rev.end());",
        "if (s == rev) // palindrome!",
    ], 7.0, 1.6, 5.8, 1.6, accent=PRIMARY)

    info_card(slide, "Frequency Count", [
        "int freq[26] = {};",
        "for (char c : s) freq[c-'a']++;",
        "// freq[0]=jumlah 'a', dst",
    ], 7.0, 3.4, 5.8, 1.6, accent=EMERALD)

    info_card(slide, "Konversi & Parsing", [
        "int n = stoi(s);    // string→int",
        "string s = to_string(n); // int→string",
        "Hati-hati: stoi throw exception",
    ], 7.0, 5.2, 5.8, 1.6, accent=VIOLET)

    # ── 8. Section 03 ────────────────────────────────────────────
    section_divider(prs, "03", "Pair — Dua Nilai Terkait",
                    ".first dan .second — sederhana tapi powerful")

    # ── 9. Pair Concept & Sort ───────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pair — Pasangan Nilai")

    code = """// DEKLARASI & AKSES
pair<int,int> p = {3, 5};
pair<string,int> q = {"Alice", 95};

cout << p.first << " " << p.second;  // 3 5

// STRUCTURED BINDING (C++17)
auto [name, score] = q;
cout << name << " got " << score;

// VECTOR OF PAIRS
vector<pair<int,int>> vp = {{3,1},{1,5},{3,2}};
sort(vp.begin(), vp.end());
// Result: {1,5}, {3,1}, {3,2}
//         ↑ by first, lalu by second

// SORT BY SECOND
sort(vp.begin(), vp.end(),
    [](auto& a, auto& b){
        return a.second < b.second;
    });"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=10, accent=AMBER)

    # Right: Common pattern
    tb(slide, "💡 Pattern: Sort + Index Tracking",
       7.2, 1.1, 5.6, 0.4, size=13, bold=True, color=AMBER)

    code3 = """// Simpan (value, original_index)
vector<pair<int,int>> v;
for (int i = 0; i < n; i++)
    v.push_back({arr[i], i});
sort(v.begin(), v.end());

// Sekarang:
// v[0].first  = nilai terkecil
// v[0].second = index aslinya"""
    code_box(slide, code3, 7.2, 1.6, 5.6, 2.5, font_size=10, accent=EMERALD)

    # Pair vs struct comparison
    tb(slide, "Pair vs Struct?", 7.2, 4.3, 5.6, 0.4,
       size=12, bold=True, color=VIOLET)
    info_card(slide, "Kapan pakai mana?", [
        ("• Pair: 2 elemen, tidak perlu nama", SILVER),
        ("• Tuple: 3+ elemen sementara", SILVER),
        ("• Struct: butuh field names jelas", SILVER),
    ], 7.2, 4.7, 5.6, 1.9, accent=VIOLET)

    # ── 10. Section 04 ───────────────────────────────────────────
    section_divider(prs, "04", "Tuple — Tiga atau Lebih",
                    "Multi-criteria sort dengan trick negate")

    # ── 11. Tuple Operations ─────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Tuple — Multi-Value Container")

    code = """// DEKLARASI
tuple<int,int,int> t = {1, 2, 3};
tuple<string,int,double> s = {"Bob", 20, 3.5};

// AKSES dengan get<index>
cout << get<0>(t);   // 1
cout << get<1>(t);   // 2

// STRUCTURED BINDING (C++17) — RECOMMENDED
auto [name, age, gpa] = s;

// TIE — unpack ke variable
int a, b, c;
tie(a, b, c) = t;

// SORTING — lexicographic by default
vector<tuple<int,int,int>> vt = {
    {3,1,4}, {1,5,9}, {3,1,2}};
sort(vt.begin(), vt.end());
// Result: {1,5,9}, {3,1,2}, {3,1,4}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=10, accent=VIOLET)

    # Right: Multi-criteria sort trick
    tb(slide, "🎯 Multi-Criteria Sort dengan Negate Trick",
       7.2, 1.1, 5.6, 0.4, size=12, bold=True, color=AMBER)

    callout(slide,
            "Sort siswa: IPK desc, angkatan asc, nama asc",
            7.2, 1.6, 5.6, 0.6, color=AMBER)

    code4 = """// Trick: negate field yg mau desc
vector<tuple<int,int,string>> students;
// (-ipk_x100, angkatan, nama)
students.emplace_back(-380, 2021, "Alice");
students.emplace_back(-390, 2020, "Bob");

sort(students.begin(), students.end());
// Sort default ascending → karena -ipk
// Result: ipk DESC, angkatan ASC, nama ASC"""
    code_box(slide, code4, 7.2, 2.4, 5.6, 2.4, font_size=9.5, accent=EMERALD)

    insight_card(slide, "Tuple vs Struct",
                 ["Tuple OK untuk sementara",
                  "Struct + operator< lebih readable",
                  "Pilih struct untuk kode yg di-reuse"],
                 7.2, 5.05, 5.6, 1.7)

    # ── 11b. Sort Trace Visualization ────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Trace Visualization — Sort Pairs & Remove Duplicates",
                 "Lexicographic sort + unique-erase pattern")

    # Left: Sort vector<pair> trace
    tb(slide, "Sort vector<pair<int,int>>",
       0.5, 1.1, 6.3, 0.4, size=13, bold=True, color=AMBER)
    tb(slide, "Input: {(3,1), (1,5), (3,2), (1,3)}",
       0.5, 1.5, 6.3, 0.3, size=11, color=AMBER, font_name="Menlo")

    # Before sort
    tb(slide, "Before:", 0.5, 1.95, 6.3, 0.3, size=10, color=SLATE)
    pair_before = [("3", "1"), ("1", "5"), ("3", "2"), ("1", "3")]
    for i, (a, b) in enumerate(pair_before):
        cx = 0.5 + i * 1.5
        rounded_rect(slide, cx, 2.3, 1.35, 0.7, BG_CARD_2,
                     line_color=BORDER, line_w=0.5)
        rect(slide, cx, 2.3, 1.35, 0.05, ROSE)
        tb(slide, f"({a}, {b})", cx, 2.45, 1.35, 0.45,
           size=14, bold=True, color=WHITE, align=PP_ALIGN.CENTER)

    # Arrow
    tb(slide, "↓ sort()", 2.7, 3.1, 2.0, 0.35,
       size=12, bold=True, color=PRIMARY)

    # After sort
    tb(slide, "After (sort by first, then by second):",
       0.5, 3.55, 6.3, 0.3, size=10, color=EMERALD)
    pair_after = [("1", "3"), ("1", "5"), ("3", "1"), ("3", "2")]
    pair_colors = [PRIMARY, PRIMARY, EMERALD, EMERALD]
    for i, ((a, b), col) in enumerate(zip(pair_after, pair_colors)):
        cx = 0.5 + i * 1.5
        rounded_rect(slide, cx, 3.9, 1.35, 0.7, col,
                     line_color=BORDER, line_w=0.5)
        tb(slide, f"({a}, {b})", cx, 4.05, 1.35, 0.45,
           size=14, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    tb(slide, "← first=1 grup",
       0.5, 4.7, 3.0, 0.3, size=10, color=PRIMARY)
    tb(slide, "← first=3 grup",
       3.5, 4.7, 3.0, 0.3, size=10, color=EMERALD)

    insight_card(slide, "Default Lexicographic",
                 ["Sort primary by .first ascending",
                  "Tiebreak by .second ascending",
                  "Tuple sama: by elemen 0, lalu 1, ..."],
                 0.5, 5.2, 6.3, 1.6)

    # Right: Sort + Unique + Erase trace
    tb(slide, "Sort + Unique + Erase",
       7.0, 1.1, 5.8, 0.4, size=13, bold=True, color=VIOLET)
    tb(slide, "v = [3, 1, 4, 1, 5, 3, 2, 1]",
       7.0, 1.5, 5.8, 0.3, size=11, color=AMBER, font_name="Menlo")

    # Step 1: sort
    tb(slide, "Step 1: sort()",
       7.0, 1.95, 5.8, 0.3, size=10, color=PRIMARY)
    array_cells(slide, [1, 1, 1, 2, 3, 3, 4, 5], 7.0, 2.3,
                cell_w=0.55, cell_h=0.5,
                highlights={i: PRIMARY for i in range(8)},
                value_size=12)

    # Step 2: unique
    tb(slide, "Step 2: unique() — geser unik ke depan",
       7.0, 2.95, 5.8, 0.3, size=10, color=AMBER)
    unique_highlights = {0: AMBER, 1: AMBER, 2: AMBER, 3: AMBER, 4: AMBER}
    cm = {0: BG_DEEP, 1: BG_DEEP, 2: BG_DEEP, 3: BG_DEEP, 4: BG_DEEP}
    for i in range(5, 8):
        unique_highlights[i] = DIM
    array_cells(slide, [1, 2, 3, 4, 5, "?", "?", "?"], 7.0, 3.3,
                cell_w=0.55, cell_h=0.5,
                highlights=unique_highlights,
                colors_map=cm, value_size=12)
    tb(slide, "↑ iterator unique() return di sini",
       7.0, 3.95, 5.8, 0.3, size=9, color=AMBER, italic=True)

    # Step 3: erase
    tb(slide, "Step 3: erase(unique_end, end()) — buang garbage",
       7.0, 4.3, 5.8, 0.3, size=10, color=EMERALD)
    array_cells(slide, [1, 2, 3, 4, 5], 7.0, 4.65,
                cell_w=0.55, cell_h=0.5,
                highlights={i: EMERALD for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=12)

    callout(slide, "5 elemen unik. Total: O(n log n).",
            7.0, 5.4, 5.8, 0.55, color=EMERALD)

    warn_card(slide, "Hati-hati!",
              ["unique() HARUS setelah sort()",
               "unique() saja tidak cukup — hapus garbage",
               "Wajib pasangan: sort + unique + erase"],
              7.0, 6.05, 5.8, 1.15)

    # ── 12. Pattern Recognition ──────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pattern Recognition — Container Mana?")

    rows = [
        ["Butuh array dinamis", "vector", "O(1) access, O(1) push", "Hampir semua soal"],
        ["Manipulasi teks", "string", "find/substr built-in", "String problems"],
        ["2 nilai terkait", "pair", ".first/.second", "(value, index) tracking"],
        ["3+ nilai terkait", "tuple", "get<i> / structured", "Multi-criteria sort"],
        ["Sort + remove dup", "vector + sort + unique", "O(n log n)", "Distinct count"],
        ["Sort by 2 kriteria", "vector<pair>", "default lexicographic", "Score + name"],
        ["Sort 3+ kriteria", "vector<tuple>", "negate untuk desc", "Tournament rank"],
    ]
    styled_table(slide,
                 ["Situasi", "Container", "Operasi Kunci", "Contoh Soal"],
                 rows,
                 0.5, 1.2, [3.0, 3.2, 3.4, 2.7],
                 row_h=0.55,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET])

    # ── 13. Common Mistakes ──────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Hati-hati!")

    mistakes = [
        ("1. v.size() unsigned underflow",
         "v.size() return size_t (unsigned).\n"
         "v.size() - 1 saat empty = HUGE number!\n"
         "Fix: cast (int)v.size() - 1",
         ROSE),
        ("2. Akses out of bounds",
         "v[5] saat size=3 → undefined behavior.\n"
         "Selalu cek: if (i < v.size())\n"
         "Atau pakai v.at(i) yang throw exception",
         ROSE),
        ("3. push_back saat iterating",
         "Iterator invalidation jika resize!\n"
         "Pakai index-based loop, atau\n"
         "kumpulkan dulu, baru push setelah loop",
         AMBER),
        ("4. String compare dengan strcmp",
         "Di C++, gunakan operator==\n"
         "string s1, s2; if (s1 == s2) ...\n"
         "strcmp untuk char[] gaya C",
         AMBER),
        ("5. Pair sort tidak custom",
         "Default sort by .first lalu .second.\n"
         "Untuk sort by .second saja, butuh\n"
         "custom comparator (lambda).",
         AMBER),
        ("6. Tuple get<> butuh constexpr index",
         "get<i>(t) dimana i HARUS literal.\n"
         "get<n>(t) di runtime → compile error!\n"
         "Pakai std::tie atau structured binding.",
         AMBER),
    ]
    for i, (title, desc, col) in enumerate(mistakes):
        cn = i % 3
        rn = i // 3
        mx = 0.4 + cn * 4.25
        my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 4.1, 2.7, BG_CARD, line_color=col, line_w=1.0)
        rect(slide, mx, my, 4.1, 0.08, col)
        tb(slide, title, mx + 0.2, my + 0.2, 3.85, 0.5,
           size=12, bold=True, color=col)
        tb(slide, desc, mx + 0.2, my + 0.75, 3.85, 1.85,
           size=10, color=SILVER)

    # ── 14. Tips & Cheatsheet ────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Quick Reference")

    cheat_left = """// VECTOR
vector<int> v(n);
for (int& x : v) cin >> x;
sort(v.begin(), v.end());
v.erase(unique(all(v)), v.end());

// STRING
string s; cin >> s;
s.substr(pos, len);
s.find("pattern");  // npos jika gagal
reverse(s.begin(), s.end());
to_string(n); stoi(s);"""

    cheat_right = """// PAIR
pair<int,int> p = {a, b};
auto [x, y] = p;             // C++17
sort(vp.begin(), vp.end()); // by first

// TUPLE
tuple<int,int,int> t = {a,b,c};
get<0>(t); get<1>(t);
auto [a, b, c] = t;          // C++17
// negate trick untuk desc:
emplace_back(-key, ...);"""

    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 4.5, font_size=11, accent=PRIMARY)
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 4.5, font_size=11, accent=AMBER)

    # Aturan emas
    rounded_rect(slide, 0.5, 5.85, 12.3, 1.4, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.85, 12.3, 0.08, EMERALD)
    tb(slide, "🌟 Aturan Emas Hari Ini",
       0.7, 5.95, 5.0, 0.4, size=13, bold=True, color=EMERALD)
    rules = [
        ("• reserve(n) jika tahu ukuran (avoid realloc)", SILVER),
        ("• emplace_back > push_back untuk objects", SILVER),
        ("• cast (int)v.size() saat aritmatika", SILVER),
        ("• structured binding [a,b,c] sangat readable", SILVER),
    ]
    for i, (text, col) in enumerate(rules):
        cn = i % 2
        rn = i // 2
        tb(slide, text, 0.7 + cn * 6.0, 6.3 + rn * 0.35,
           5.8, 0.32, size=10, color=col)

    # ── 15. Closing ──────────────────────────────────────────────
    closing_slide(prs, 3, "Foundation containers untuk semua CP problems", [
        (PRIMARY, "Vector", "Array dinamis. push_back O(1), sort O(n log n). Default container CP."),
        (EMERALD, "String", "Manipulasi teks. substr, find, reverse, to_string/stoi."),
        (AMBER, "Pair", ".first/.second. Sort lexicographic default. Trick (value, index)."),
        (VIOLET, "Tuple", "3+ nilai. get<i>, structured binding. Negate trick untuk desc sort."),
        (ROSE, "Pitfall", "v.size() unsigned, akses out-of-bounds, iterator invalidation."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_3_Presentation.pptx"))


if __name__ == "__main__":
    main()
