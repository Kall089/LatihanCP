#!/usr/bin/env python3
"""Day 6 — STL Algorithms (sort, binary search, permutation, accumulate, dll)."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ───────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["sort", "lower_bound", "accumulate", "next_perm"]
        cols = [PRIMARY, EMERALD, AMBER, VIOLET]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.4 + i * 1.6
            rounded_rect(slide, cx, 5.6, 1.5, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.5, 0.4,
               size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 6, "STL Algorithms",
                ["sort  ·  binary search  ·  permutation",
                 "Toolbox lengkap untuk transform & query"],
                decoration=cov_deco)

    # ── Agenda ──────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 6", [
        ("01", "Sort &\nComparator", PRIMARY,
         ["sort + lambda", "stable_sort", "Multi-criteria", "greater<int>()"]),
        ("02", "Binary\nSearch", EMERALD,
         ["lower_bound", "upper_bound", "binary_search", "Count in range"]),
        ("03", "Reduksi &\nTransform", AMBER,
         ["accumulate", "max/min_element", "transform", "iota & fill"]),
        ("04", "Permutation\n& Lainnya", VIOLET,
         ["next_permutation", "all/any/none_of", "Coordinate Compress", "set_union/intersect"]),
    ])

    # ── Section 01: Sort ────────────────────────────────────────
    section_divider(prs, "01", "Sort & Comparator",
                    "O(n log n) — fondasi banyak teknik CP")

    slide = new_slide(prs)
    slide_header(slide, "sort() — Built-in Introsort O(n log n)")
    code = """// === SORT DEFAULT (ASCENDING) ===
vector<int> A = {3, 1, 4, 1, 5, 9, 2, 6};
sort(A.begin(), A.end());
// → {1, 1, 2, 3, 4, 5, 6, 9}

// === DESCENDING ===
sort(A.begin(), A.end(), greater<int>());
// atau pakai reverse iterator:
sort(A.rbegin(), A.rend());

// === LAMBDA CUSTOM ===
sort(A.begin(), A.end(), [](int a, int b) {
    return a > b;   // descending
});

// === STABLE_SORT ===
// Pertahankan urutan relatif elemen sama
stable_sort(A.begin(), A.end(), comp);"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.5, font_size=11, accent=PRIMARY)

    # Right side: visualization of sort
    tb(slide, "Visualisasi sort([3,1,4,1,5])", 7.3, 1.1, 5.7, 0.4,
       size=13, bold=True, color=AMBER)
    array_cells(slide, [3, 1, 4, 1, 5], 7.3, 1.7,
                cell_w=0.55, cell_h=0.5,
                highlights={i: BG_CARD_2 for i in range(5)})
    tb(slide, "↓ sort", 9.5, 2.3, 1.0, 0.3, size=11, color=PRIMARY)
    array_cells(slide, [1, 1, 3, 4, 5], 7.3, 2.7,
                cell_w=0.55, cell_h=0.5,
                highlights={i: EMERALD for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)})

    info_card(slide, "Multi-Criteria Sort",
              ["• Sort score desc, name asc",
               "if (a.score != b.score)",
               "    return a.score > b.score;",
               "return a.name < b.name;"],
              7.3, 3.5, 5.7, 1.7, accent=EMERALD)

    metric_card(slide, "sort", "O(n log n)", 7.3, 5.4, 2.7, 1.2, accent=PRIMARY)
    metric_card(slide, "stable_sort", "O(n log² n)", 10.2, 5.4, 2.8, 1.2, accent=EMERALD)

    # ── Section 02: Binary Search ──────────────────────────────
    section_divider(prs, "02", "Binary Search",
                    "lower_bound, upper_bound — O(log n) di sorted array",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "lower_bound vs upper_bound")
    # Concept
    info_card(slide, "Konsep", [
        "• lower_bound(it, x) → iterator pertama ≥ x",
        "• upper_bound(it, x) → iterator pertama > x",
        "• binary_search(it, x) → bool (ada/tidak)",
        "• Selisih hi - lo = jumlah elemen == x",
        "• Array HARUS sorted dulu!",
    ], 0.5, 1.1, 5.8, 3.0, accent=EMERALD)

    code = """vector<int> A = {1, 2, 2, 3, 4, 4};

auto lo = lower_bound(A.begin(), A.end(), 2);
auto hi = upper_bound(A.begin(), A.end(), 2);

int idx = lo - A.begin();   // 1
int cnt = hi - lo;          // 2 (banyaknya '2')
bool ada = binary_search(A.begin(),
                          A.end(), 2); // true"""
    code_box(slide, code, 0.5, 4.25, 5.8, 2.5, font_size=10, accent=EMERALD)

    # Right: visual
    tb(slide, "Array sorted: [1, 2, 2, 3, 4, 4]", 6.6, 1.1, 6.4, 0.4,
       size=12, bold=True, color=AMBER, font_name="Menlo")
    array_cells(slide, [1, 2, 2, 3, 4, 4], 6.6, 1.7,
                cell_w=0.7, cell_h=0.55,
                highlights={1: PRIMARY, 2: PRIMARY},
                colors_map={1: BG_DEEP, 2: BG_DEEP})

    # pointers
    tb(slide, "↑ lower_bound(2) = idx 1",
       6.6, 2.5, 6.4, 0.3, size=11, bold=True, color=PRIMARY)
    tb(slide, "↑ upper_bound(2) = idx 3",
       6.6, 2.85, 6.4, 0.3, size=11, bold=True, color=AMBER)

    info_card(slide, "Pola: Hitung dalam range [l, r]",
              ["int cnt = upper_bound(A,r)",
               "        - lower_bound(A,l);",
               "// jumlah elemen di [l, r]"],
              6.6, 3.5, 6.4, 1.7, accent=PRIMARY)

    info_card(slide, "Hati-hati",
              [("× Tanpa sort → undefined!", ROSE),
               ("• Selalu sort dulu sebelum BS", SILVER),
               ("• lower_bound return iterator,", SILVER),
               ("  kurangi begin() → index", SILVER)],
              6.6, 5.35, 6.4, 1.5, accent=ROSE)

    # ── Section 03: Reduksi ────────────────────────────────────
    section_divider(prs, "03", "Reduksi & Transform",
                    "accumulate, transform, fill, iota, max_element",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "accumulate, max_element, count_if")
    code = """#include <numeric>

vector<int> A = {1, 2, 3, 4, 5};

// === SUM ===
ll sum = accumulate(A.begin(), A.end(), 0LL);  // 15

// === PRODUCT ===
ll prod = accumulate(A.begin(), A.end(), 1LL,
    [](ll acc, int x){ return acc * x; });    // 120

// === SUM OF SQUARES ===
ll sq = accumulate(A.begin(), A.end(), 0LL,
    [](ll acc, int x){ return acc + (ll)x*x; });

// === MAX & MIN ===
int mx = *max_element(A.begin(), A.end());     // 5
int mn = *min_element(A.begin(), A.end());     // 1
int idx = max_element(A.begin(), A.end())
         - A.begin();                          // index

// === COUNT_IF ===
int evens = count_if(A.begin(), A.end(),
    [](int x){ return x%2==0; });              // 2"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.7, font_size=10.5, accent=AMBER)

    # Right side
    insight_card(slide, "Tips Akumulasi", [
        "Inisial 0LL/1LL untuk hindari overflow",
        "Pakai callable untuk produk/mod",
        "Lambda dengan capture [&] aman",
        "Lebih singkat daripada loop manual",
    ], 7.3, 1.1, 5.8, 2.0)

    code2 = """// MOD product
const int MOD = 1e9+7;
ll p = accumulate(A.begin(), A.end(), 1LL,
    [&](ll acc, int x){
        return acc * x % MOD;
    });

// COUNT exact
int c = count(A.begin(), A.end(), 3);"""
    code_box(slide, code2, 7.3, 3.25, 5.8, 2.0, font_size=10, accent=EMERALD)

    info_card(slide, "Big Picture",
              ["• accumulate = reduce / fold",
               "• transform = map",
               "• count_if = filter + count",
               "• Pikir functional programming!"],
              7.3, 5.4, 5.8, 1.5, accent=VIOLET)

    # ── Slide: transform, fill, iota ───────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "transform, fill, iota — Inisialisasi & Map")

    code_left = """// === TRANSFORM (map) ===
vector<int> A = {1, 2, 3, 4};
vector<int> B(A.size());

transform(A.begin(), A.end(),
          B.begin(),
          [](int x){ return x*x; });
// B = {1, 4, 9, 16}

// 2 input range:
vector<int> C(A.size());
transform(A.begin(), A.end(),
          B.begin(), C.begin(),
          plus<int>());
// C[i] = A[i] + B[i]"""
    code_box(slide, code_left, 0.5, 1.1, 6.0, 4.0, font_size=10.5, accent=PRIMARY)

    code_right = """// === FILL & IOTA ===
vector<int> A(5);
fill(A.begin(), A.end(), 7);
// A = {7, 7, 7, 7, 7}

iota(A.begin(), A.end(), 0);
// A = {0, 1, 2, 3, 4}

// === INDEX SORTING TRICK ===
vector<int> idx(n);
iota(idx.begin(), idx.end(), 0);
sort(idx.begin(), idx.end(),
    [&](int i, int j){
        return val[i] < val[j];
    });"""
    code_box(slide, code_right, 6.7, 1.1, 6.1, 4.0, font_size=10.5, accent=EMERALD)

    # Bottom: callout about all_of/any_of
    rounded_rect(slide, 0.5, 5.3, 12.3, 1.7, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 5.3, 12.3, 0.08, VIOLET)
    tb(slide, "all_of / any_of / none_of — Cek Batch Cepat",
       0.7, 5.4, 7.0, 0.4, size=13, bold=True, color=VIOLET)
    code3 = """bool semuaGenap = all_of(A.begin(), A.end(), [](int x){ return x%2==0; });
bool adaNeg     = any_of(A.begin(), A.end(), [](int x){ return x<0; });
bool tidakNol   = none_of(A.begin(), A.end(), [](int x){ return x==0; });"""
    plain_code_box(slide, code3, 0.7, 5.85, 12.0, 1.0, font_size=10.5,
                   accent=VIOLET, text_color=SILVER)

    # ── Slide: find / reverse / rotate / unique ─────────────────
    slide = new_slide(prs)
    slide_header(slide, "find · reverse · rotate · unique",
                 "Manipulasi array klasik — semua O(n)")

    code = """// === FIND — cari elemen ===
auto it = find(A.begin(), A.end(), 5);
if (it != A.end())
    cout << "Found at " << it - A.begin();
else
    cout << "Not found";

// === REVERSE — balik in-place ===
reverse(A.begin(), A.end());

// === ROTATE — rotasi kiri k posisi ===
rotate(A.begin(), A.begin() + k, A.end());
// untuk rotasi kanan k:
rotate(A.begin(), A.begin() + n - k, A.end());

// === UNIQUE — hapus duplicate consecutive ===
sort(A.begin(), A.end());                    // WAJIB sort dulu!
A.erase(unique(A.begin(), A.end()), A.end());"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.7, font_size=10.5, accent=PRIMARY)

    # Right: visualizations
    tb(slide, "🔄 reverse([1,2,3,4,5])",
       7.3, 1.1, 5.7, 0.4, size=12, bold=True, color=AMBER)
    array_cells(slide, [1, 2, 3, 4, 5], 7.3, 1.55,
                cell_w=0.5, cell_h=0.45,
                highlights={i: PRIMARY for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=11)
    tb(slide, "↓", 9.3, 2.05, 0.5, 0.3, size=14, color=PRIMARY,
       bold=True, align=PP_ALIGN.CENTER)
    array_cells(slide, [5, 4, 3, 2, 1], 7.3, 2.4,
                cell_w=0.5, cell_h=0.45,
                highlights={i: EMERALD for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=11)

    # rotate visualization
    tb(slide, "🔁 rotate([1,2,3,4,5], k=2)",
       7.3, 3.05, 5.7, 0.4, size=12, bold=True, color=VIOLET)
    array_cells(slide, [1, 2, 3, 4, 5], 7.3, 3.5,
                cell_w=0.5, cell_h=0.45,
                highlights={0: ROSE, 1: ROSE, 2: PRIMARY, 3: PRIMARY, 4: PRIMARY},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=11)
    tb(slide, "↓ rotate kiri 2", 9.0, 3.95, 1.5, 0.3, size=10, color=VIOLET)
    array_cells(slide, [3, 4, 5, 1, 2], 7.3, 4.3,
                cell_w=0.5, cell_h=0.45,
                highlights={0: PRIMARY, 1: PRIMARY, 2: PRIMARY, 3: ROSE, 4: ROSE},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=11)

    # unique visualization
    tb(slide, "✂ sort+unique([3,1,4,1,5,3])",
       7.3, 5.0, 5.7, 0.4, size=12, bold=True, color=EMERALD)
    array_cells(slide, [1, 1, 3, 3, 4, 5], 7.3, 5.45,
                cell_w=0.5, cell_h=0.45,
                highlights={0: AMBER, 1: ROSE, 2: AMBER, 3: ROSE, 4: AMBER, 5: AMBER},
                colors_map={i: BG_DEEP for i in range(6)},
                value_size=11)
    tb(slide, "↓ erase consecutive dup", 9.0, 5.9, 2.5, 0.3,
       size=10, color=EMERALD)
    array_cells(slide, [1, 3, 4, 5], 7.3, 6.25,
                cell_w=0.5, cell_h=0.45,
                highlights={i: EMERALD for i in range(4)},
                colors_map={i: BG_DEEP for i in range(4)},
                value_size=11)
    tb(slide, "↑ unique values",
       9.6, 6.7, 2.0, 0.3, size=9.5, color=EMERALD, italic=True)

    # ── Slide: nth_element & partial_sort ─────────────────────
    slide = new_slide(prs)
    slide_header(slide, "nth_element & partial_sort — Top-K Tanpa Full Sort",
                 "Cari k-th element atau k terkecil tanpa O(n log n) penuh")

    code = """vector<int> A = {7, 3, 9, 1, 5, 8, 2};

// === nth_element (k=3) — letakkan elemen ke-k di posisi yg benar
nth_element(A.begin(), A.begin() + 3, A.end());
// A[3] = elemen yg seharusnya di posisi 3 setelah sort
// A[0..2] semua ≤ A[3], A[4..n] semua ≥ A[3]
// O(n) RATA-RATA (quickselect)

// === Cari median ===
nth_element(A.begin(), A.begin() + n/2, A.end());
int median = A[n/2];

// === partial_sort (k=3) — sort 3 elemen pertama saja
partial_sort(A.begin(), A.begin() + 3, A.end());
// A[0] ≤ A[1] ≤ A[2] dan keduanya ≤ A[3..n]
// O(n log k) — lebih cepat dari sort()

// === Top-K terbesar (descending) ===
partial_sort(A.begin(), A.begin() + k, A.end(), greater<int>());"""
    code_box(slide, code, 0.5, 1.1, 7.0, 5.0, font_size=10.5, accent=AMBER)

    # Right: visualization
    tb(slide, "📊 nth_element vs partial_sort vs sort",
       7.7, 1.1, 5.3, 0.4, size=12, bold=True, color=PRIMARY)

    rows = [
        [("Algoritma", PRIMARY), ("Time", EMERALD), ("Hasil", AMBER)],
        ["sort", "O(n log n)", "Fully sorted"],
        ["partial_sort(k)", "O(n log k)", "K terkecil sorted"],
        [("nth_element(k)", AMBER), ("O(n) avg", AMBER), ("A[k] correct, rest unsorted", AMBER)],
    ]
    rs = rows[1:]
    styled_table(slide, ["Algo", "Time", "Hasil"], rs,
                 7.7, 1.7, [1.7, 1.6, 2.0], row_h=0.55,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    # Visual nth_element
    tb(slide, "Trace nth_element k=3:",
       7.7, 3.95, 5.3, 0.3, size=11, bold=True, color=VIOLET)
    array_cells(slide, [7, 3, 9, 1, 5, 8, 2], 7.7, 4.3,
                cell_w=0.45, cell_h=0.45,
                highlights={i: BG_CARD_2 for i in range(7)},
                value_size=11)
    tb(slide, "↓ nth_element(begin+3)",
       8.7, 4.9, 3.3, 0.3, size=10, color=AMBER)
    array_cells(slide, [2, 1, 3, 5, 7, 9, 8], 7.7, 5.3,
                cell_w=0.45, cell_h=0.45,
                highlights={0: EMERALD, 1: EMERALD, 2: EMERALD,
                            3: AMBER, 4: VIOLET, 5: VIOLET, 6: VIOLET},
                colors_map={i: BG_DEEP for i in range(7)},
                value_size=11)
    tb(slide, "≤5", 7.85, 5.85, 1.2, 0.3, size=9.5, color=EMERALD)
    tb(slide, "k=5", 9.05, 5.85, 0.65, 0.3, size=9.5, color=AMBER, bold=True)
    tb(slide, "≥5", 9.7, 5.85, 1.5, 0.3, size=9.5, color=VIOLET)

    callout(slide, "Use case: median, top-K, quickselect",
            0.5, 6.3, 7.0, 0.6, color=EMERALD, icon="🎯")

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Permutation & Set Operations",
                    "next_permutation, set_intersection, coordinate compression",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "next_permutation — Generate Semua Permutasi")

    code = """vector<int> A = {1, 2, 3};
sort(A.begin(), A.end());   // mulai dari terkecil!

do {
    for (int x : A) cout << x;
    cout << "\\n";
} while (next_permutation(A.begin(), A.end()));

// Output (n! = 6 permutasi):
// 123
// 132
// 213
// 231
// 312
// 321"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.5, font_size=11, accent=VIOLET)

    # Right: insight
    insight_card(slide, "Catatan Penting", [
        "Harus sort dulu (mulai terkecil)",
        "Return false saat balik ke awal",
        "n! permutasi → maks n ≈ 11",
        "Berguna untuk brute force",
    ], 7.0, 1.1, 5.8, 2.2)

    info_card(slide, "Coordinate Compression",
              ["• Mengubah nilai besar → rank kecil",
               "sort + unique + lower_bound",
               "Sangat berguna untuk BIT/segtree",
               "Kompleksitas O(n log n)"],
              7.0, 3.5, 5.8, 2.1, accent=AMBER)

    code2 = """// COORDINATE COMPRESSION
vector<int> v = A;  // copy
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
for (int& x : A)
    x = lower_bound(v.begin(), v.end(), x) - v.begin();
// A diubah jadi rank-nya"""
    code_box(slide, code2, 0.5, 5.85, 12.3, 1.1, font_size=10, accent=EMERALD)

    # ── Slide: Set Operations on Sorted Ranges ────────────────
    slide = new_slide(prs)
    slide_header(slide, "Set Operations on Sorted Ranges",
                 "set_intersection / set_union / set_difference / merge — O(n+m)")

    code = """// PRASYARAT: kedua range harus SORTED
vector<int> A = {1, 2, 3, 4};
vector<int> B = {2, 4, 6};
vector<int> result;

// === INTERSECTION (irisan) ===
set_intersection(A.begin(), A.end(), B.begin(), B.end(),
                 back_inserter(result));
// result = {2, 4}

// === UNION (gabungan) ===
result.clear();
set_union(A.begin(), A.end(), B.begin(), B.end(),
          back_inserter(result));
// result = {1, 2, 3, 4, 6}

// === DIFFERENCE (A \\ B) ===
result.clear();
set_difference(A.begin(), A.end(), B.begin(), B.end(),
               back_inserter(result));
// result = {1, 3}

// === MERGE — gabung sorted, KEEP DUPLIKAT ===
result.clear();
merge(A.begin(), A.end(), B.begin(), B.end(),
      back_inserter(result));
// result = {1, 2, 2, 3, 4, 4, 6}"""
    code_box(slide, code, 0.5, 1.1, 7.5, 5.7, font_size=10, accent=PRIMARY)

    # Right: visualizations
    tb(slide, "🎯 Visual Set Operations",
       8.2, 1.1, 4.8, 0.4, size=12, bold=True, color=AMBER)

    # A & B reference
    tb(slide, "A = {1,2,3,4}", 8.2, 1.55, 4.8, 0.3,
       size=11, color=PRIMARY, font_name="Menlo")
    tb(slide, "B = {2,4,6}", 8.2, 1.85, 4.8, 0.3,
       size=11, color=AMBER, font_name="Menlo")

    # 4 results
    set_results = [
        ("∩ intersection", "{2, 4}", EMERALD),
        ("∪ union", "{1,2,3,4,6}", PRIMARY),
        ("− difference (A−B)", "{1, 3}", AMBER),
        ("merge (keep dup)", "{1,2,2,3,4,4,6}", VIOLET),
    ]
    for i, (label, result, col) in enumerate(set_results):
        ty = 2.3 + i * 1.05
        rounded_rect(slide, 8.2, ty, 4.8, 0.95, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, 8.2, ty, 4.8, 0.05, col)
        tb(slide, label, 8.35, ty + 0.1, 4.5, 0.3,
           size=11, bold=True, color=col)
        tb(slide, "→ " + result, 8.35, ty + 0.45, 4.5, 0.4,
           size=11, color=SILVER, font_name="Menlo")

    callout(slide, "Wajib SORTED dulu! Kompleksitas O(n+m).",
            0.5, 6.95, 7.5, 0.3, color=ROSE, icon="⚠")

    # ── Slide: Coordinate Compression Detailed Trace ──────────
    slide = new_slide(prs)
    slide_header(slide, "Coordinate Compression — Trace Detail",
                 "Mengubah nilai besar → rank kecil. Kunci untuk Fenwick/Segment Tree.")

    # Step 0: Original
    tb(slide, "Step 0: Original A = [100, 5, 50, 100, 5]",
       0.5, 1.1, 12.3, 0.35, size=12, bold=True, color=ROSE)
    array_cells(slide, [100, 5, 50, 100, 5], 0.5, 1.5,
                cell_w=0.85, cell_h=0.55,
                highlights={i: BG_CARD_2 for i in range(5)},
                value_size=12)
    tb(slide, "Nilai bisa sampai 10⁹ → susah index langsung",
       0.5, 2.15, 12.3, 0.3, size=10, color=MUTED, italic=True)

    # Step 1: Copy & Sort
    tb(slide, "Step 1: Copy & Sort",
       0.5, 2.55, 6.0, 0.35, size=12, bold=True, color=PRIMARY)
    array_cells(slide, [5, 5, 50, 100, 100], 0.5, 2.95,
                cell_w=0.85, cell_h=0.55,
                highlights={i: PRIMARY for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=12)

    # Step 2: Unique + Erase
    tb(slide, "Step 2: unique + erase",
       7.0, 2.55, 6.0, 0.35, size=12, bold=True, color=AMBER)
    array_cells(slide, [5, 50, 100], 7.0, 2.95,
                cell_w=0.85, cell_h=0.55,
                highlights={i: AMBER for i in range(3)},
                colors_map={i: BG_DEEP for i in range(3)},
                value_size=12)
    tb(slide, "rank: 0   1    2", 7.0, 3.55, 4.5, 0.3,
       size=10, color=AMBER, font_name="Menlo")

    # Step 3: Replace with rank
    tb(slide, "Step 3: lower_bound — replace each value with its rank",
       0.5, 3.95, 12.3, 0.35, size=12, bold=True, color=EMERALD)

    # Mapping table
    mapping = [
        ("100", "→", "rank 2"),
        ("5", "→", "rank 0"),
        ("50", "→", "rank 1"),
        ("100", "→", "rank 2"),
        ("5", "→", "rank 0"),
    ]
    for i, (orig, arrow, rank) in enumerate(mapping):
        cx = 0.5 + i * 2.5
        rounded_rect(slide, cx, 4.4, 2.35, 0.55, BG_CARD,
                     line_color=EMERALD, line_w=0.5)
        tb(slide, orig, cx, 4.5, 0.7, 0.4,
           size=11, color=ROSE, bold=True, align=PP_ALIGN.CENTER,
           font_name="Menlo")
        tb(slide, arrow, cx + 0.7, 4.5, 0.5, 0.4,
           size=11, color=SLATE, align=PP_ALIGN.CENTER)
        tb(slide, rank, cx + 1.2, 4.5, 1.1, 0.4,
           size=11, color=EMERALD, bold=True, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    # Final result
    tb(slide, "Hasil: A_compressed = [2, 0, 1, 2, 0]",
       0.5, 5.15, 12.3, 0.35, size=13, bold=True, color=AMBER)
    array_cells(slide, [2, 0, 1, 2, 0], 0.5, 5.55,
                cell_w=0.85, cell_h=0.55,
                highlights={i: EMERALD for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)},
                value_size=12)

    # Use cases
    rounded_rect(slide, 0.5, 6.2, 12.3, 1.0, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 6.2, 12.3, 0.06, VIOLET)
    tb(slide, "💡 Use Cases", 0.7, 6.3, 6.0, 0.3,
       size=12, bold=True, color=VIOLET)
    use_cases = [
        "Fenwick / BIT (index 0..n-1)",
        "Segment Tree (kompak)",
        "Counting inversions",
        "Range queries dengan koordinat besar",
    ]
    for i, uc in enumerate(use_cases):
        cn = i % 2
        rn = i // 2
        tb(slide, "• " + uc, 0.7 + cn * 6.0, 6.6 + rn * 0.3,
           5.8, 0.28, size=10, color=SILVER)

    # ── Pattern Recognition ────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pattern Recognition — Algoritma Mana?")
    rows = [
        ["Sort biasa", "sort", "O(n log n)", "Hampir semua soal"],
        ["Sort multi-criteria", "sort + lambda", "O(n log n)", "Score+name"],
        ["Cari elemen", "find / binary_search", "O(n) / O(log n)", "Pencarian"],
        ["Hitung occurrence", "count / count_if", "O(n)", "Frequency"],
        ["Cek semua memenuhi", "all_of", "O(n)", "Validasi"],
        ["Sum / product", "accumulate", "O(n)", "Reduksi"],
        ["Generate permutasi", "next_permutation", "O(n!)", "Brute force"],
        ["Range query <= k", "lower/upper_bound", "O(log n)", "Sorted array"],
    ]
    styled_table(slide, ["Situasi", "Algoritma", "Kompleksitas", "Contoh"],
                 rows, 0.5, 1.2, [3.2, 3.4, 2.8, 2.9], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET])

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Hindari Ini!")
    mistakes = [
        ("1. lower_bound tanpa sort",
         "Hasilnya undefined!\nSelalu sort dulu sebelum binary search.",
         ROSE),
        ("2. unique tanpa sort",
         "unique hanya hapus consecutive dup.\nSort → unique → erase.",
         ROSE),
        ("3. accumulate dengan int 0",
         "0 → int → overflow!\nPakai 0LL untuk long long sum.",
         AMBER),
        ("4. next_permutation tanpa sort awal",
         "Loop tidak akan kembali ke awal.\nSort dulu = mulai dari terkecil.",
         AMBER),
        ("5. transform output kurang space",
         "Output range harus cukup,\nataupakai back_inserter().",
         AMBER),
        ("6. all_of pada vector kosong",
         "Selalu return true (vacuous truth).\nCek !A.empty() jika perlu.",
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
           size=10.5, color=SILVER)

    # ── Cheatsheet ─────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Quick Reference")
    cheat_left = """// SORT
sort(v.begin(), v.end());
sort(v.begin(), v.end(), greater<int>());

// BINARY SEARCH (sorted!)
auto lo = lower_bound(v.begin(), v.end(), x);
auto hi = upper_bound(v.begin(), v.end(), x);
int cnt = hi - lo;
int idx = lo - v.begin();

// REDUKSI
ll sum = accumulate(v.begin(), v.end(), 0LL);
int mx = *max_element(v.begin(), v.end());
int cnt = count_if(v.begin(), v.end(), pred);"""

    cheat_right = """// TRANSFORM
transform(v.begin(), v.end(), v.begin(),
    [](int x){ return x*2; });
iota(idx.begin(), idx.end(), 0);
fill(v.begin(), v.end(), 0);

// CEK BATCH
all_of(v.begin(), v.end(), pred);
any_of(v.begin(), v.end(), pred);

// PERMUTATION
sort(v.begin(), v.end());
do { ... } while (next_permutation(...));

// DEDUP
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());"""

    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 4.5, font_size=10.5, accent=PRIMARY)
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 4.5, font_size=10.5, accent=AMBER)

    # Aturan emas
    rounded_rect(slide, 0.5, 5.85, 12.3, 1.4, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.85, 12.3, 0.08, EMERALD)
    tb(slide, "🌟 Aturan Emas",
       0.7, 5.95, 5.0, 0.4, size=13, bold=True, color=EMERALD)
    rules = [
        ("• Sort sebelum binary search / unique", SILVER),
        ("• Pakai 0LL/1LL untuk akumulasi long long", SILVER),
        ("• Lambda untuk custom comparator/predicate", SILVER),
        ("• stable_sort jika butuh urutan relatif", SILVER),
    ]
    for i, (text, col) in enumerate(rules):
        cn = i % 2
        rn = i // 2
        tb(slide, text, 0.7 + cn * 6.0, 6.3 + rn * 0.35,
           5.8, 0.32, size=10, color=col)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 6, "STL Algorithms — Toolbox lengkap untuk transform & query", [
        (PRIMARY, "Sort", "O(n log n) introsort. Lambda untuk custom. stable_sort jika urutan relatif penting."),
        (EMERALD, "Binary Search", "lower/upper_bound — O(log n). Hitung jumlah dalam range dengan selisih iterator."),
        (AMBER, "Reduksi", "accumulate, max_element, count_if. Pakai 0LL untuk hindari overflow."),
        (VIOLET, "Permutation & Set", "next_permutation untuk brute force. set_intersection/union pada sorted ranges."),
        (ROSE, "Pitfall", "Sort dulu sebelum BS/unique. accumulate butuh 0LL. transform butuh space output."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_6_Presentation.pptx"))


if __name__ == "__main__":
    main()
