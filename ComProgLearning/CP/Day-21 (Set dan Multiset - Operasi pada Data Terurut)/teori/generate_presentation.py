#!/usr/bin/env python3
"""Day 4 — STL Containers 2 (Set, Map, Unordered_Set, Unordered_Map, Multiset)."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        items = [("set", PRIMARY), ("map", EMERALD),
                 ("multiset", AMBER), ("hash", VIOLET)]
        for i, (lbl, col) in enumerate(items):
            cx = 6.5 + i * 1.6
            rounded_rect(slide, cx, 5.6, 1.4, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.4, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    cover_slide(prs, 4, "STL Containers II",
                ["Set  ·  Map  ·  Multiset",
                 "Unordered (Hash) Variants"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 4", [
        ("01", "Set &\nMultiset", PRIMARY,
         ["Unique elements", "Auto-sorted", "lower/upper_bound", "O(log n) ops"]),
        ("02", "Map\n(Ordered)", EMERALD,
         ["Key→Value", "Auto-sorted by key", "Frequency count", "O(log n) lookup"]),
        ("03", "Unordered\nVariants", AMBER,
         ["Hash-based", "O(1) average", "No ordering", "Worst case O(n)"]),
        ("04", "Tradeoff &\nPattern", VIOLET,
         ["Ordered vs Hash", "When to use", "lower_bound trick", "Common patterns"]),
    ])

    # ── Decision Tree: Container Mana? ──────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Decision Tree — Container Mana yang Dipakai?",
                 "Flowchart cepat untuk pilih container di CP")

    # Root question
    rounded_rect(slide, 4.5, 1.1, 4.3, 0.6, PRIMARY)
    tb(slide, "Butuh simpan data dengan KEY?",
       4.5, 1.2, 4.3, 0.45, size=13, bold=True, color=BG_DEEP,
       align=PP_ALIGN.CENTER)

    # Two branches: YES (key→value) and NO (only value)
    tb(slide, "YES (key → value)", 1.3, 1.95, 3.5, 0.35,
       size=12, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)
    tb(slide, "NO (hanya value)", 8.5, 1.95, 3.5, 0.35,
       size=12, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # YES branch
    rounded_rect(slide, 0.5, 2.4, 5.0, 0.55, BG_CARD,
                 line_color=EMERALD, line_w=0.75)
    tb(slide, "Butuh urut by key?", 0.5, 2.5, 5.0, 0.4,
       size=11, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)

    rounded_rect(slide, 0.5, 3.15, 2.4, 0.5, EMERALD)
    tb(slide, "YES → map", 0.5, 3.22, 2.4, 0.4,
       size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    rounded_rect(slide, 3.1, 3.15, 2.4, 0.5, VIOLET)
    tb(slide, "NO → unordered_map", 3.1, 3.22, 2.4, 0.4,
       size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    # NO branch
    rounded_rect(slide, 7.7, 2.4, 5.0, 0.55, BG_CARD,
                 line_color=AMBER, line_w=0.75)
    tb(slide, "Boleh duplikat?", 7.7, 2.5, 5.0, 0.4,
       size=11, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # Sub-branch: NO duplikat → urut?
    tb(slide, "NO duplikat", 7.85, 3.1, 2.2, 0.3,
       size=10, color=EMERALD, align=PP_ALIGN.CENTER)
    rounded_rect(slide, 7.85, 3.4, 2.2, 0.5, PRIMARY)
    tb(slide, "urut → set", 7.85, 3.47, 2.2, 0.4,
       size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    rounded_rect(slide, 7.85, 3.95, 2.2, 0.5, VIOLET)
    tb(slide, "tdk → unordered_set", 7.85, 4.02, 2.2, 0.4,
       size=9, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    # Sub-branch: YES duplikat
    tb(slide, "YES duplikat", 10.3, 3.1, 2.2, 0.3,
       size=10, color=AMBER, align=PP_ALIGN.CENTER)
    rounded_rect(slide, 10.3, 3.4, 2.2, 0.5, AMBER)
    tb(slide, "→ multiset", 10.3, 3.47, 2.2, 0.4,
       size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    # Bottom: pattern table
    rounded_rect(slide, 0.5, 4.85, 12.3, 2.4, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 4.85, 12.3, 0.08, PRIMARY)
    tb(slide, "Pattern Soal → Container", 0.7, 4.95, 8.0, 0.4,
       size=13, bold=True, color=PRIMARY)

    patterns = [
        ("Hitung distinct", "set", PRIMARY),
        ("Cari ≥ X (predecessor)", "set + lower_bound", AMBER),
        ("Frequency count", "map / unordered_map", EMERALD),
        ("Cek exists O(1)", "unordered_set", VIOLET),
        ("Sorted + delete arbitrary", "multiset", AMBER),
        ("Top-K dynamic", "multiset / pq", PRIMARY),
    ]
    for i, (sit, cont, col) in enumerate(patterns):
        cn = i % 3
        rn = i // 3
        px = 0.7 + cn * 4.05
        py = 5.4 + rn * 0.85
        tb(slide, "▸ " + sit, px, py, 4.0, 0.32, size=10, color=SILVER)
        tb(slide, cont, px + 0.2, py + 0.35, 3.8, 0.32,
           size=11, bold=True, color=col)

    # ═══════════════════════════════════════════════════════════
    # SECTION 01 — Set & Multiset
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "01", "Set & Multiset",
                    "Koleksi terurut — set unique, multiset boleh duplikat")

    # ── Set Concept ──────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Set?",
                 "Koleksi nilai unik yang otomatis terurut")

    info_card(slide, "Properti Set", [
        "• Semua elemen UNIK (no duplicates)",
        "• Otomatis tersorted (ascending default)",
        "• Berbasis Red-Black Tree (balanced BST)",
        "• Insert/erase/find → O(log n)",
        "• Iterasi memberikan urutan terurut",
    ], 0.5, 1.1, 5.8, 3.0, accent=PRIMARY)

    tb(slide, "set<int> s = {3, 1, 4, 1, 5, 9, 2, 6};",
       6.5, 1.1, 6.3, 0.4, size=12, bold=True, color=AMBER, font_name="Menlo")
    tb(slide, "Setelah masuk set:", 6.5, 1.55, 6.3, 0.3,
       size=11, color=SLATE, italic=True)
    array_cells(slide, [1, 2, 3, 4, 5, 6, 9], 6.5, 1.95,
                cell_w=0.65, cell_h=0.55,
                highlights={i: PRIMARY for i in range(7)})
    tb(slide, "↑ duplikat 1 hilang, otomatis ASC",
       6.5, 2.65, 6.3, 0.3, size=10, color=EMERALD, italic=True)

    # Multiset visual
    tb(slide, "multiset<int> ms = {3, 1, 4, 1, 5};",
       6.5, 3.2, 6.3, 0.4, size=12, bold=True, color=AMBER, font_name="Menlo")
    array_cells(slide, [1, 1, 3, 4, 5], 6.5, 3.7,
                cell_w=0.65, cell_h=0.55,
                highlights={i: EMERALD for i in range(5)})
    tb(slide, "↑ multiset PERTAHANKAN duplikat",
       6.5, 4.4, 6.3, 0.3, size=10, color=AMBER, italic=True)

    metric_card(slide, "insert", "O(log n)", 0.5, 4.5, 3.0, 1.2, accent=PRIMARY)
    metric_card(slide, "find", "O(log n)", 3.7, 4.5, 3.0, 1.2, accent=EMERALD)
    metric_card(slide, "erase", "O(log n)", 6.9, 4.5, 3.0, 1.2, accent=AMBER)
    metric_card(slide, "iterate", "O(n)", 10.1, 4.5, 2.7, 1.2, accent=VIOLET)

    # ── Set/Multiset Code ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Set & Multiset — Operations")

    code1 = """// === SET ===
set<int> s;
s.insert(5);              // O(log n)
s.insert(5);              // ignored — duplicate
s.erase(5);               // erase by value
s.count(5);               // 0 atau 1
if (s.find(5) != s.end()) // ada?
    cout << "found";

// AKSES
*s.begin();               // min element
*s.rbegin();              // max element
s.size();
s.empty();

// ITERASI (sudah terurut)
for (int x : s) cout << x;"""

    code2 = """// === MULTISET ===
multiset<int> ms;
ms.insert(5);
ms.insert(5);             // OK — duplikat
ms.count(5);              // bisa > 1

// HATI-HATI: erase value MENGHAPUS SEMUA
ms.erase(5);              // hapus semua 5

// Untuk hapus 1 instance:
auto it = ms.find(5);
if (it != ms.end()) ms.erase(it);

// LOWER/UPPER BOUND
auto lb = ms.lower_bound(5);  // ≥ 5
auto ub = ms.upper_bound(5);  // > 5

// distance(lb, ub) = jumlah 5"""

    code_box(slide, code1, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)
    code_box(slide, code2, 6.7, 1.1, 6.1, 5.7, font_size=10, accent=EMERALD)

    # ── lower_bound / upper_bound ────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "lower_bound vs upper_bound — Trik Penting",
                 "Cari element ≥ X atau > X dalam set/multiset")

    code = """set<int> s = {2, 4, 6, 8, 10};

// lower_bound(x): iterator ke element PERTAMA ≥ x
auto it1 = s.lower_bound(5);
// *it1 = 6  (yang pertama ≥ 5)

// upper_bound(x): iterator ke element PERTAMA > x
auto it2 = s.upper_bound(6);
// *it2 = 8  (yang pertama > 6)

// CARA CARI ELEMEN < X (predecessor)
auto it = s.lower_bound(7);
if (it != s.begin()) {
    --it;        // mundur 1 step
    cout << *it; // 6 = max yang < 7
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=10, accent=AMBER)

    # Right: Visual
    tb(slide, "Visualisasi: s = {2,4,6,8,10}", 7.0, 1.1, 6.0, 0.4,
       size=12, bold=True, color=AMBER)
    array_cells(slide, [2, 4, 6, 8, 10], 7.0, 1.6,
                cell_w=0.7, cell_h=0.55,
                highlights={i: PRIMARY for i in range(5)})

    callout(slide, "lower_bound(5) → 6  (pertama ≥ 5)",
            7.0, 2.5, 5.8, 0.6, color=EMERALD)
    callout(slide, "upper_bound(6) → 8  (pertama > 6)",
            7.0, 3.2, 5.8, 0.6, color=AMBER)
    callout(slide, "Predecessor 7 → 6  (mundur dari lower_bound)",
            7.0, 3.9, 5.8, 0.6, color=VIOLET)

    insight_card(slide, "Kapan Pakai Apa?",
                 ["lower_bound = ≥ x  (≥)",
                  "upper_bound = > x  (strict)",
                  "Untuk count(x): distance(lb, ub)",
                  "Untuk < x: --lower_bound(x)"],
                 7.0, 4.7, 5.8, 2.1)

    # ── Trace: Set Insert + Multiset Erase Trap ─────────────────
    slide = new_slide(prs)
    slide_header(slide, "Trace — Set Insert & Multiset Erase Trap",
                 "Visualisasi step-by-step + jebakan umum")

    # Left: Set Insert + lower_bound trace
    tb(slide, "Set Insert + lower_bound",
       0.5, 1.1, 6.3, 0.4, size=13, bold=True, color=PRIMARY)

    set_trace = [
        ("set<int> s;", "{}", "0"),
        ("s.insert(5);", "{5}", "1"),
        ("s.insert(2);", "{2, 5}", "2"),
        ("s.insert(8);", "{2, 5, 8}", "3"),
        ("s.insert(5); ✗", "{2, 5, 8}", "3"),
        ("s.insert(1);", "{1, 2, 5, 8}", "4"),
        ("s.lower_bound(3);", "→ iter ke 5", "4"),
        ("s.upper_bound(5);", "→ iter ke 8", "4"),
        ("s.erase(2);", "{1, 5, 8}", "3"),
    ]
    headers = ["Operasi", "State (sorted)", "Size"]
    widths = [2.5, 2.7, 1.0]

    rect(slide, 0.5, 1.55, sum(widths) - 0.04, 0.4, PRIMARY)
    cumx = 0.5
    for h, w in zip(headers, widths):
        tb(slide, h, cumx + 0.05, 1.6, w - 0.1, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cumx += w
    for ri, row in enumerate(set_trace):
        ry = 1.96 + ri * 0.4
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        rect(slide, 0.5, ry, sum(widths) - 0.04, 0.38, bg)
        cumx = 0.5
        for ci, (cell, w) in enumerate(zip(row, widths)):
            col = ROSE if "✗" in cell else (
                AMBER if "iter" in cell else WHITE)
            tb(slide, cell, cumx + 0.05, ry + 0.06, w - 0.1, 0.3,
               size=9.5, color=col, font_name="Menlo",
               align=PP_ALIGN.LEFT if ci == 0 else PP_ALIGN.CENTER)
            cumx += w

    tb(slide, "✗ duplikat ditolak  •  iter dipakai untuk navigasi",
       0.5, 5.62, 6.3, 0.3, size=10, color=SLATE, italic=True)

    # Right: Multiset Erase trap
    tb(slide, "⚠ Multiset Erase Trap",
       7.0, 1.1, 5.8, 0.4, size=13, bold=True, color=ROSE)

    ms_trace = [
        ("multiset<int> ms;", "{}", "0"),
        ("ms.insert(3);", "{3}", "1"),
        ("ms.insert(3);", "{3, 3}", "2"),
        ("ms.insert(3);", "{3, 3, 3}", "3"),
        ("ms.insert(5);", "{3, 3, 3, 5}", "4"),
        ("ms.erase(ms.find(3));", "{3, 3, 5} ✓", "3"),
        ("ms.erase(3); ⚠", "{5}  HAPUS SEMUA!", "1"),
    ]
    rect(slide, 7.0, 1.55, sum(widths) - 0.04 + 0.2, 0.4, ROSE)
    widths2 = [2.4, 2.85, 0.95]
    cumx = 7.0
    for h, w in zip(headers, widths2):
        tb(slide, h, cumx + 0.05, 1.6, w - 0.1, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cumx += w
    for ri, row in enumerate(ms_trace):
        ry = 1.96 + ri * 0.42
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        rect(slide, 7.0, ry, sum(widths2) - 0.04, 0.4, bg)
        cumx = 7.0
        for ci, (cell, w) in enumerate(zip(row, widths2)):
            col = EMERALD if "✓" in cell else (
                ROSE if ("⚠" in cell or "HAPUS" in cell) else WHITE)
            tb(slide, cell, cumx + 0.05, ry + 0.07, w - 0.1, 0.3,
               size=9.5, color=col, font_name="Menlo",
               align=PP_ALIGN.LEFT if ci == 0 else PP_ALIGN.CENTER)
            cumx += w

    warn_card(slide, "Aturan Emas Multiset",
              ["erase(VALUE) → hapus SEMUA",
               "erase(ITERATOR) → hapus 1 saja",
               "Pakai: ms.erase(ms.find(x))"],
              7.0, 5.45, 5.8, 1.5)

    # ═══════════════════════════════════════════════════════════
    # SECTION 02 — Map
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "02", "Map — Key→Value",
                    "Buku telepon: nama → nomor, otomatis terurut by key")

    # ── Map Concept ──────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Map — Key-Value Pairs",
                 "Berbasis Red-Black Tree, otomatis sorted by key")

    code = """// === DEKLARASI ===
map<string, int> phonebook;
map<int, string> id_to_name;

// === INSERT ===
phonebook["Alice"] = 123;     // operator[]
phonebook.insert({"Bob", 456});

// === ACCESS (HATI-HATI!) ===
phonebook["Alice"];            // 123
phonebook["Charlie"];          // 0 (CREATE entry!)

// CARA AMAN — pakai find:
auto it = phonebook.find("Charlie");
if (it != phonebook.end())
    cout << it->second;
else cout << "not found";

// === COUNT / ERASE ===
phonebook.count("Alice");      // 0 atau 1
phonebook.erase("Alice");

// === ITERASI (urut by key) ===
for (auto& [k, v] : phonebook)
    cout << k << " " << v;"""
    code_box(slide, code, 0.5, 1.1, 7.0, 5.7, font_size=10, accent=EMERALD)

    # Right: Visualisation
    tb(slide, "Map sebagai Tabel", 7.7, 1.1, 5.0, 0.4,
       size=13, bold=True, color=EMERALD)

    rounded_rect(slide, 7.7, 1.6, 5.0, 4.0, BG_CARD, line_color=EMERALD, line_w=1.0)
    rect(slide, 7.7, 1.6, 5.0, 0.45, EMERALD)
    tb(slide, "Key", 7.85, 1.65, 1.5, 0.35,
       size=12, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    tb(slide, "Value", 9.5, 1.65, 1.5, 0.35,
       size=12, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    rows = [("Alice", "123"), ("Bob", "456"), ("Charlie", "789")]
    for i, (k, v) in enumerate(rows):
        ry = 2.15 + i * 0.5
        if i % 2 == 0:
            rect(slide, 7.75, ry, 4.9, 0.45, BG_CARD_2)
        tb(slide, k, 7.9, ry + 0.07, 1.5, 0.35,
           size=11, color=WHITE, align=PP_ALIGN.CENTER)
        tb(slide, v, 9.55, ry + 0.07, 1.5, 0.35,
           size=11, color=AMBER, align=PP_ALIGN.CENTER)

    warn_card(slide, "Pitfall: operator[]",
              ["Akses key yang tidak ada → CREATE entry!",
               "Map size bertambah secara diam-diam",
               "Pakai .find() atau .count() untuk cek"],
              7.7, 5.9, 5.0, 1.2)

    # ── Frequency Count Pattern ──────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pattern: Frequency Count",
                 "Use case map paling sering di CP")

    code = """// === FREQUENCY COUNT ===
vector<int> a = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
map<int, int> freq;

for (int x : a) freq[x]++;

// Sekarang freq menyimpan:
// {1:2, 2:1, 3:2, 4:1, 5:3, 6:1, 9:1}

// CARI MOST FREQUENT
int max_count = 0, max_val = 0;
for (auto& [val, cnt] : freq) {
    if (cnt > max_count) {
        max_count = cnt;
        max_val = val;
    }
}
// Result: 5 muncul 3 kali"""
    code_box(slide, code, 0.5, 1.1, 6.3, 5.0, font_size=10, accent=AMBER)

    # Right: visualization
    tb(slide, "Visual: a = [3,1,4,1,5,9,2,6,5,3,5]",
       7.0, 1.1, 5.8, 0.4, size=12, bold=True, color=AMBER)

    # Frequency bars
    fmap = [(1, 2), (2, 1), (3, 2), (4, 1), (5, 3), (6, 1), (9, 1)]
    for i, (val, cnt) in enumerate(fmap):
        ry = 1.7 + i * 0.55
        # Key cell
        rounded_rect(slide, 7.0, ry, 0.7, 0.45, PRIMARY)
        tb(slide, str(val), 7.0, ry + 0.05, 0.7, 0.35,
           size=12, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        # Bar
        bar_w = cnt * 0.6
        rect(slide, 7.85, ry + 0.08, bar_w, 0.3,
             EMERALD if cnt >= 2 else AMBER)
        tb(slide, str(cnt), 7.9 + bar_w, ry + 0.05, 0.5, 0.35,
           size=11, bold=True, color=WHITE)

    insight_card(slide, "Most Frequent → 5 (3×)",
                 ["Pattern ini muncul di 30% soal CP",
                  "freq[x]++ dengan default 0 → berkat operator[]",
                  "Untuk top-K most frequent: pakai priority_queue"],
                 7.0, 5.5, 5.8, 1.5)

    # ── Real-World Patterns: Two Sum, Concert, Registration ─────
    slide = new_slide(prs)
    slide_header(slide, "Real-World Patterns — Soal Klasik CP",
                 "Two Sum, Concert Tickets, Registration System")

    # Pattern 1: Two Sum (top-left)
    rounded_rect(slide, 0.5, 1.1, 6.2, 2.95, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 1.1, 6.2, 0.42, PRIMARY)
    tb(slide, "🎯 Two Sum  —  unordered_map", 0.65, 1.16, 6.0, 0.32,
       size=12, bold=True, color=BG_DEEP)
    code_ts = """// Cari (i,j) dimana A[i]+A[j]==target
unordered_map<int, int> seen;  // value→idx
for (int i = 0; i < n; i++) {
    int need = target - A[i];
    if (seen.count(need)) {
        cout << seen[need] << " " << i;
        return;
    }
    seen[A[i]] = i;
}"""
    plain_code_box(slide, code_ts, 0.65, 1.6, 5.95, 2.4, font_size=9.5,
                   accent=PRIMARY, text_color=SILVER)

    # Pattern 2: Concert Tickets (top-right)
    rounded_rect(slide, 6.95, 1.1, 5.85, 2.95, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    rect(slide, 6.95, 1.1, 5.85, 0.42, AMBER)
    tb(slide, "🎫 Concert Tickets  —  multiset + upper_bound",
       7.1, 1.16, 5.7, 0.32, size=12, bold=True, color=BG_DEEP)
    code_ct = """multiset<int> tickets(prices.begin(), prices.end());
for (int budget : customers) {
    auto it = tickets.upper_bound(budget); // > budget
    if (it == tickets.begin()) {
        cout << -1;     // tidak ada tiket ≤ budget
    } else {
        --it;           // mundur → termahal yang ≤ budget
        cout << *it;
        tickets.erase(it);  // tiket terjual
    }
}"""
    plain_code_box(slide, code_ct, 7.1, 1.6, 5.6, 2.4, font_size=9.5,
                   accent=AMBER, text_color=SILVER)

    # Pattern 3: Registration System (bottom-left)
    rounded_rect(slide, 0.5, 4.2, 6.2, 2.95, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 4.2, 6.2, 0.42, EMERALD)
    tb(slide, "📝 Registration System  —  map<string, int>",
       0.65, 4.26, 6.0, 0.32, size=12, bold=True, color=BG_DEEP)
    code_rs = """map<string, int> names;
for (string& name : registrations) {
    if (names.count(name)) {
        cout << name << "_" << names[name];
        names[name]++;
    } else {
        cout << "OK";
        names[name] = 1;
    }
}"""
    plain_code_box(slide, code_rs, 0.65, 4.7, 5.95, 2.4, font_size=9.5,
                   accent=EMERALD, text_color=SILVER)

    # Pattern 4: Top-K Largest (bottom-right)
    rounded_rect(slide, 6.95, 4.2, 5.85, 2.95, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 6.95, 4.2, 5.85, 0.42, VIOLET)
    tb(slide, "🏆 Top-K Sliding  —  multiset",
       7.1, 4.26, 5.7, 0.32, size=12, bold=True, color=BG_DEEP)
    code_tk = """multiset<int> top_k;
for (int x : stream) {
    top_k.insert(x);
    if ((int)top_k.size() > k) {
        top_k.erase(top_k.begin());  // hapus terkecil
    }
}
// top_k = K terbesar (dynamic)
// Min: *top_k.begin(),  Max: *top_k.rbegin()"""
    plain_code_box(slide, code_tk, 7.1, 4.7, 5.6, 2.4, font_size=9.5,
                   accent=VIOLET, text_color=SILVER)

    # ═══════════════════════════════════════════════════════════
    # SECTION 03 — Unordered Variants
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "03", "Unordered (Hash) Variants",
                    "Hash-based: O(1) average tapi tidak terurut")

    # ── Unordered ────────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Unordered Set & Map",
                 "Hash table → lebih cepat tapi tanpa urutan")

    code = """// === SAMA API DENGAN ordered ===
unordered_set<int> us;
us.insert(5); us.count(5); us.erase(5);

unordered_map<string, int> um;
um["Alice"] = 100;
um.find("Bob");

// === BEDANYA ===
// 1. Tidak ada urutan
// 2. Tidak ada lower_bound/upper_bound
// 3. O(1) average, BUT O(n) worst case
// 4. Iterasi tidak terurut

// === COUNTER PATTERN ===
unordered_map<int, int> cnt;
for (int x : a) cnt[x]++;
// Lebih cepat dari map untuk lookup biasa"""
    code_box(slide, code, 0.5, 1.1, 6.3, 5.5, font_size=10, accent=VIOLET)

    # Right: ordered vs unordered
    tb(slide, "Ordered vs Unordered", 7.0, 1.1, 5.8, 0.4,
       size=14, bold=True, color=VIOLET)

    rows = [
        ["Operasi", "set / map", "unordered_*"],
        ["insert", "O(log n)", "O(1) avg"],
        ["find", "O(log n)", "O(1) avg"],
        ["erase", "O(log n)", "O(1) avg"],
        ["worst case", "O(log n)", "O(n) ⚠"],
        ["sorted iter", "✓", "✗"],
        ["lower_bound", "✓", "✗"],
    ]
    for ri, row in enumerate(rows):
        ry = 1.6 + ri * 0.45
        if ri == 0:
            rect(slide, 7.0, ry, 5.8, 0.4, VIOLET)
        else:
            bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
            rect(slide, 7.0, ry, 5.8, 0.4, bg)
        for ci, cell in enumerate(row):
            cx = 7.0 + ci * 1.95
            cw = 1.95
            color = BG_DEEP if ri == 0 else (
                VIOLET if ci == 0 else WHITE)
            bold_flag = (ri == 0)
            tb(slide, cell, cx + 0.1, ry + 0.07, cw - 0.2, 0.3,
               size=10, bold=bold_flag, color=color, align=PP_ALIGN.CENTER)

    warn_card(slide, "Codeforces Anti-Hash Tests",
              ["Codeforces punya test case yg sengaja jebak hash → O(n²)",
               "Solusi: pakai map saja, atau custom hash function",
               "Aman: pakai map kalau worst case matter"],
              0.5, 6.7, 12.3, 0.6)

    # ── Pattern Recognition ──────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pattern Recognition — Container Mana?")

    rows = [
        ["Hitung distinct elements", "set", "size() setelah insert", "Easy"],
        ["Cari ≥ X / predecessor", "set + lower_bound", "O(log n)", "Medium"],
        ["Frequency count", "unordered_map", "freq[x]++", "Easy"],
        ["Frequency count + sort by freq", "map + vector pair", "compare freq", "Medium"],
        ["Cek elemen ada (cepat)", "unordered_set", "count()", "Easy"],
        ["Multiple instance + remove 1", "multiset + erase(it)", "erase(find(x))", "Medium"],
        ["Min/Max yang masih ada", "set / multiset", "*begin() / *rbegin()", "Medium"],
        ["Codeforces / anti-hash", "map (TIDAK unordered)", "safer", "—"],
    ]
    styled_table(slide, ["Situasi", "Container", "Operasi", "Sulit"],
                 rows, 0.5, 1.1, [3.5, 3.2, 3.5, 1.8], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, ROSE])

    # ═══════════════════════════════════════════════════════════
    # SECTION 04 — Pitfalls & Cheatsheet
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "04", "Pitfalls & Cheatsheet",
                    "Hindari kesalahan umum, kuasai pola")

    # ── Common Mistakes ──────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes")

    mistakes = [
        ("1. operator[] di map = create",
         "map<int,int> m;\nm[5]; → entry baru!\n"
         "Pakai m.find(5) atau m.count(5).",
         ROSE),
        ("2. multiset.erase(value) hapus SEMUA",
         "ms.erase(5) → hapus semua 5\n"
         "Untuk 1 instance: erase(find(x))\n"
         "Atau: erase(lb) jika lb != end",
         ROSE),
        ("3. Iterator invalidation",
         "Hapus elemen di tengah iterasi → bug!\n"
         "Gunakan: it = m.erase(it);\n"
         "Atau collect dulu, hapus belakangan",
         AMBER),
        ("4. unordered di Codeforces",
         "Anti-hash test → TLE / O(n²)\n"
         "Pakai map biasa, atau\n"
         "Custom hash dengan random",
         AMBER),
        ("5. Range-based loop modify",
         "for (auto& [k,v] : m) v++;     ✓\n"
         "for (auto [k,v] : m) v++;       ✗ (copy)\n"
         "Selalu pakai & untuk modify",
         AMBER),
        ("6. set<vector<int>> sort lambat",
         "Comparison O(k) per ops → O(n·k·log n)\n"
         "Pertimbangkan hash atau encoding\n"
         "Jangan asal pakai set<complex_type>",
         VIOLET),
    ]
    for i, (title, desc, col) in enumerate(mistakes):
        cn = i % 3; rn = i // 3
        mx = 0.4 + cn * 4.25; my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 4.1, 2.7, BG_CARD, line_color=col, line_w=1.0)
        rect(slide, mx, my, 4.1, 0.08, col)
        tb(slide, title, mx + 0.2, my + 0.2, 3.85, 0.5,
           size=12, bold=True, color=col)
        tb(slide, desc, mx + 0.2, my + 0.75, 3.85, 1.85,
           size=10, color=SILVER)

    # ── Cheatsheet ───────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Quick Reference")

    left = """// SET
set<int> s;
s.insert(x); s.erase(x);
s.count(x);                  // 0/1
if (s.find(x) != s.end()) ..

// SET + lower_bound
auto it = s.lower_bound(x);  // ≥ x
auto it = s.upper_bound(x);  // > x
if (it != s.begin()) --it;   // < x

// MULTISET
multiset<int> ms;
ms.insert(x);
ms.erase(ms.find(x));        // 1 instance
ms.count(x);                 // bisa > 1"""

    right = """// MAP
map<string,int> m;
m["Alice"] = 100;
m.count("Alice");
auto it = m.find("Bob");
if (it != m.end()) it->second;

// FREQUENCY COUNT
unordered_map<int,int> cnt;
for (int x : a) cnt[x]++;

// ITERATE (sorted untuk map)
for (auto& [k, v] : m) ..

// Cf safe: pakai map, BUKAN unordered_map"""

    code_box(slide, left, 0.5, 1.1, 6.2, 4.7, font_size=10.5, accent=PRIMARY)
    code_box(slide, right, 6.7, 1.1, 6.1, 4.7, font_size=10.5, accent=EMERALD)

    rounded_rect(slide, 0.5, 6.0, 12.3, 1.3, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    rect(slide, 0.5, 6.0, 12.3, 0.08, AMBER)
    tb(slide, "🌟 Aturan Emas", 0.7, 6.1, 5.0, 0.4,
       size=13, bold=True, color=AMBER)
    rules = [
        ("• Codeforces: PILIH map > unordered_map", SILVER),
        ("• operator[] di map → create entry!", SILVER),
        ("• multiset.erase(it) hapus 1, erase(val) hapus SEMUA", SILVER),
        ("• Set + lower_bound = predecessor query O(log n)", SILVER),
    ]
    for i, (text, col) in enumerate(rules):
        cn = i % 2; rn = i // 2
        tb(slide, text, 0.7 + cn * 6.0, 6.45 + rn * 0.35,
           5.8, 0.32, size=10, color=col)

    # ── Closing ──────────────────────────────────────────────────
    closing_slide(prs, 4, "Associative containers — backbone CP problems", [
        (PRIMARY, "Set",
         "Unique + sorted. lower/upper_bound O(log n). Ideal untuk distinct & predecessor."),
        (EMERALD, "Map",
         "Key→Value sorted. Pattern frequency count, lookup. operator[] hati-hati!"),
        (AMBER, "Multiset",
         "Sorted dengan duplikat. erase(find(x)) untuk 1 instance saja."),
        (VIOLET, "Unordered",
         "O(1) avg via hash. Codeforces anti-hash → pilih map."),
        (ROSE, "Pitfall",
         "operator[] auto-create, multiset.erase(val) hapus semua, hash anti-test."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_4_Presentation.pptx"))


if __name__ == "__main__":
    main()
