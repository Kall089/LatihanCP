#!/usr/bin/env python3
"""Day 13 — Bitmask Enumeration: bitwise ops, subset enumeration, builtin."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["1010", "0101", "1111"]
        cols = [PRIMARY, EMERALD, AMBER]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.5 + i * 1.85
            rounded_rect(slide, cx, 5.6, 1.7, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.7, 0.4,
               size=14, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    cover_slide(prs, 13, "Bitmask Enumeration",
                ["Set as integer  ·  Bitwise ops",
                 "Iterasi semua 2ⁿ subset dengan elegan"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 13", [
        ("01", "Konsep\nBitmask", PRIMARY,
         ["Set as integer", "Mapping bit ↔ elemen", "Kapan pakai bitmask", "Batas n ≤ 20"]),
        ("02", "Bitwise\nOperators", EMERALD,
         ["AND, OR, XOR", "Shift << >>", "Cek/set/clear/toggle", "popcount, ctz"]),
        ("03", "Subset\nEnumeration", AMBER,
         ["Iterasi 2ⁿ subset", "Subset sum", "Submask enum", "Pola O(3ⁿ)"]),
        ("04", "Aplikasi\nCP", VIOLET,
         ["Travelling Salesman", "Bitmask DP", "Hamiltonian path", "Tips & pitfall"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Konsep Bitmask",
                    "Set elemen direpresentasikan sebagai integer biner")

    slide = new_slide(prs)
    slide_header(slide, "Set as Integer — Mapping Bit ↔ Elemen")

    # Left: explanation
    info_card(slide, "Konsep Dasar", [
        "• Setiap bit = 1 elemen",
        "• bit i aktif → elemen i ADA",
        "• bit i = 0 → elemen i TIDAK ada",
        "• int 32-bit → maks 32 elemen",
        "• long long → maks 64 elemen",
    ], 0.5, 1.1, 5.5, 3.0, accent=PRIMARY)

    insight_card(slide, "Keunggulan",
                 ["Operasi set O(1) — cepat",
                  "Kompak: n elemen di 1 integer",
                  "Iterasi semua subset O(2ⁿ)",
                  "Mudah hash sebagai key"],
                 0.5, 4.25, 5.5, 2.5)

    # Right: visualization
    tb(slide, "🎯 Contoh: 4 elemen {A, B, C, D}",
       6.3, 1.1, 6.5, 0.4, size=13, bold=True, color=AMBER)

    # Header row
    headers = [("Bit 3", VIOLET), ("Bit 2", VIOLET),
               ("Bit 1", VIOLET), ("Bit 0", VIOLET)]
    for i, (txt, col) in enumerate(headers):
        cx = 6.5 + i * 1.4
        rounded_rect(slide, cx, 1.7, 1.3, 0.4, col)
        tb(slide, txt, cx, 1.78, 1.3, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    elements = ["D", "C", "B", "A"]
    for i, e in enumerate(elements):
        cx = 6.5 + i * 1.4
        tb(slide, e, cx, 2.18, 1.3, 0.3,
           size=11, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)

    # Examples
    examples = [
        ("0000", " = 0", "{} (kosong)", VIOLET),
        ("0001", " = 1", "{A}", PRIMARY),
        ("0101", " = 5", "{A, C}", EMERALD),
        ("1011", " = 11", "{A, B, D}", AMBER),
        ("1111", " = 15", "{A, B, C, D}", ROSE),
    ]
    for i, (binary, dec, set_repr, col) in enumerate(examples):
        ty = 2.65 + i * 0.55
        rounded_rect(slide, 6.5, ty, 6.3, 0.45, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, binary, 6.65, ty + 0.05, 1.0, 0.35,
           size=12, bold=True, color=col, font_name="Menlo")
        tb(slide, dec, 7.7, ty + 0.05, 1.2, 0.35,
           size=11, color=SLATE, font_name="Menlo")
        tb(slide, set_repr, 8.95, ty + 0.05, 3.85, 0.35,
           size=11, bold=True, color=WHITE)

    callout(slide, "n ≤ 20 → 1M kombinasi (aman). n > 25 → TLE!",
            6.3, 5.55, 6.5, 0.65, color=AMBER, icon="⚠")

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "Bitwise Operators",
                    "AND, OR, XOR, shift — dasar manipulasi bit",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Operator Bitwise — 5 Esensial")

    # 4 panels: AND, OR, XOR, NOT
    ops = [
        ("&", "AND", "Hasil 1 jika KEDUA bit 1",
         "1010 & 1100 = 1000", "Cek bit aktif, intersect", PRIMARY),
        ("|", "OR", "Hasil 1 jika SALAH SATU bit 1",
         "1010 | 0100 = 1110", "Set bit, union", EMERALD),
        ("^", "XOR", "Hasil 1 jika BERBEDA",
         "1010 ^ 1100 = 0110", "Toggle bit, find unique", AMBER),
        ("<<", "Shift Left", "Geser kiri = kalikan 2^k",
         "0001 << 3 = 1000", "Buat mask: 1 << i", VIOLET),
    ]
    for i, (sym, name, desc, exam, use, col) in enumerate(ops):
        cn = i % 2
        rn = i // 2
        cx = 0.5 + cn * 6.3
        cy = 1.1 + rn * 2.95
        rounded_rect(slide, cx, cy, 6.1, 2.7, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, cx, cy, 6.1, 0.42, col)
        tb(slide, sym, cx + 0.15, cy + 0.04, 0.8, 0.36,
           size=18, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
           font_name="Menlo")
        tb(slide, name, cx + 1.0, cy + 0.08, 4.5, 0.32,
           size=14, bold=True, color=BG_DEEP)
        tb(slide, desc, cx + 0.2, cy + 0.55, 5.7, 0.4,
           size=11, color=SILVER)
        plain_code_box(slide, exam, cx + 0.2, cy + 1.0,
                       5.7, 0.85, font_size=12, accent=col)
        tb(slide, "🎯 " + use, cx + 0.2, cy + 2.0, 5.7, 0.4,
           size=10.5, bold=True, color=col)

    # ── Slide: Operasi bitmask umum ────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Operasi Bitmask Umum — Cek/Set/Clear/Toggle")

    code = """// === CEK bit ke-i aktif? ===
bool isSet = (mask >> i) & 1;
// alternatif: (mask & (1 << i)) != 0

// === SET bit ke-i jadi 1 ===
mask |= (1 << i);

// === CLEAR bit ke-i jadi 0 ===
mask &= ~(1 << i);

// === TOGGLE bit ke-i (flip) ===
mask ^= (1 << i);

// === HITUNG bit aktif ===
int cnt = __builtin_popcount(mask);     // int
int cnt = __builtin_popcountll(mask);   // ll

// === LOWEST set bit ===
int low_val = mask & -mask;
int low_idx = __builtin_ctz(mask);

// === HAPUS lowest set bit ===
mask &= mask - 1;"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.7, font_size=10.5, accent=EMERALD)

    # Right: visual examples
    tb(slide, "🎬 Visual: mask = 1010 (= 10)",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)
    array_cells(slide, [1, 0, 1, 0], 7.2, 1.7,
                cell_w=0.7, cell_h=0.55,
                highlights={0: PRIMARY, 2: PRIMARY},
                colors_map={0: BG_DEEP, 2: BG_DEEP})
    # Index labels (reverse - bit 3,2,1,0 from left to right)
    bit_labels = ["bit 3", "bit 2", "bit 1", "bit 0"]
    for i, lbl in enumerate(bit_labels):
        tb(slide, lbl, 7.2 + i * 0.75, 2.4, 0.7, 0.3,
           size=8.5, color=MUTED, align=PP_ALIGN.CENTER)

    # Operations
    ops_examples = [
        ("Set bit 0 (|=1)",  "1010 | 0001 = 1011 (11)", PRIMARY),
        ("Clear bit 3",       "1010 & 0111 = 0010 (2)",  ROSE),
        ("Toggle bit 1",      "1010 ^ 0010 = 1000 (8)",  AMBER),
        ("popcount(1010)",    "= 2 (jumlah bit 1)",      EMERALD),
        ("ctz(1010)",         "= 1 (trailing zero)",     VIOLET),
    ]
    for i, (op, result, col) in enumerate(ops_examples):
        ty = 3.0 + i * 0.66
        rounded_rect(slide, 7.2, ty, 5.7, 0.55, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, op, 7.35, ty + 0.05, 2.4, 0.45,
           size=10.5, bold=True, color=col)
        tb(slide, result, 9.8, ty + 0.05, 3.05, 0.45,
           size=10.5, color=SILVER, font_name="Menlo")

    # ── Section 03 ─────────────────────────────────────────────
    section_divider(prs, "03", "Subset Enumeration",
                    "Iterasi 2ⁿ subset & submask iteration O(3ⁿ)",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Iterasi Semua Subset O(2ⁿ)")
    code = """int n = 3;

for (int mask = 0; mask < (1 << n); mask++) {
    cout << "{";
    for (int i = 0; i < n; i++) {
        if ((mask >> i) & 1)
            cout << i << " ";
    }
    cout << "}\\n";
}

// Total: 2^n iterasi
// Pemrosesan O(n) per subset → O(n · 2^n)"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.0, font_size=11, accent=AMBER)

    # Right: trace table
    tb(slide, "📊 Trace n=3 — semua 8 subset",
       7.1, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)
    rows = [
        ["0", "000", "{}"],
        ["1", "001", "{0}"],
        ["2", "010", "{1}"],
        ["3", "011", "{0,1}"],
        ["4", "100", "{2}"],
        ["5", "101", "{0,2}"],
        ["6", "110", "{1,2}"],
        [("7", AMBER), ("111", AMBER), ("{0,1,2}", AMBER)],
    ]
    styled_table(slide, ["mask", "biner", "subset"], rows,
                 7.1, 1.7, [1.5, 1.7, 2.5], row_h=0.4,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    # Bottom: warning + example
    rounded_rect(slide, 0.5, 5.4, 12.3, 1.6, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.4, 12.3, 0.06, EMERALD)
    tb(slide, "🎯 Contoh Aplikasi: Subset Sum O(n · 2ⁿ)",
       0.7, 5.5, 6.0, 0.3, size=12, bold=True, color=EMERALD)
    code2 = """for (int mask = 0; mask < (1<<n); mask++) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        if ((mask >> i) & 1) sum += a[i];
    if (sum == K) { found = true; break; }   // ada subset dengan sum = K
}"""
    plain_code_box(slide, code2, 0.7, 5.85, 12.0, 1.05,
                   font_size=10, accent=EMERALD)

    # ── Slide: Submask iteration ───────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Submask Iteration — O(3ⁿ) Trick")

    code = """// Iterasi semua submask dari mask
for (int sub = mask; sub > 0; sub = (sub-1) & mask) {
    // sub adalah subset dari mask
    // proses sub
}
// Termasuk submask 0:
int sub = mask;
do {
    // proses sub
    sub = (sub - 1) & mask;
} while (sub != mask);

// Total: untuk semua mask + submask = 3^n"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.0, font_size=11, accent=VIOLET)

    # Right: Why 3^n?
    insight_card(slide, "🧮 Mengapa O(3ⁿ)?",
                 ["• Setiap elemen punya 3 status:",
                  "  - Tidak di mask",
                  "  - Di mask, di sub",
                  "  - Di mask, tidak di sub",
                  "• Total: 3 × 3 × ... × 3 = 3ⁿ"],
                 7.2, 1.1, 5.7, 2.7)

    # Comparison
    tb(slide, "📊 Kompleksitas", 7.2, 4.0, 5.7, 0.4,
       size=12, bold=True, color=AMBER)
    rows = [
        ["10", "1,024", "59,049"],
        ["15", "32,768", "14M"],
        ["20", "1M", "3.5B (TLE)"],
    ]
    styled_table(slide, ["n", "2ⁿ", "3ⁿ"], rows,
                 7.2, 4.45, [1.0, 2.2, 2.5], row_h=0.45,
                 header_colors=[PRIMARY, EMERALD, ROSE],
                 body_size=10, header_size=10)

    callout(slide, "Submask enum berguna untuk SOS DP, partition DP",
            0.5, 5.3, 6.5, 0.7, color=EMERALD, icon="💡")

    insight_card(slide, "Tips Implementation",
                 ["sub = (sub-1) & mask",
                  "→ next submask",
                  "Berhenti saat sub = 0 lalu break"],
                 0.5, 6.1, 6.5, 1.0)

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Aplikasi CP",
                    "Bitmask DP, TSP, Hamiltonian — bitmask shines untuk n ≤ 20",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Travelling Salesman Problem (TSP) Bitmask DP")

    code = """// dp[mask][i] = min cost untuk visit semua kota di mask,
//               berakhir di kota i
const int INF = 1e9;
int dp[1<<MAXN][MAXN];
int dist[MAXN][MAXN];

int tsp(int mask, int i) {
    if (mask == (1<<n) - 1) return dist[i][0]; // back to start
    if (dp[mask][i] != -1) return dp[mask][i];

    int ans = INF;
    for (int j = 0; j < n; j++) {
        if (mask & (1<<j)) continue;          // already visited
        ans = min(ans, dist[i][j] + tsp(mask | (1<<j), j));
    }
    return dp[mask][i] = ans;
}
// Panggil: tsp(1, 0) → mulai di kota 0"""
    code_box(slide, code, 0.5, 1.1, 7.5, 5.5, font_size=10, accent=VIOLET)

    # Right: complexity & insight
    tb(slide, "📊 Kompleksitas TSP", 8.3, 1.1, 4.6, 0.4,
       size=13, bold=True, color=AMBER)

    metric_card(slide, "Time", "O(n² · 2ⁿ)", 8.3, 1.7, 4.6, 1.1, accent=PRIMARY)
    metric_card(slide, "Space", "O(n · 2ⁿ)", 8.3, 2.95, 4.6, 1.1, accent=EMERALD)

    rows = [
        ["10", "10K", "Aman"],
        ["15", "500K", "Aman"],
        ["18", "5M", "Aman"],
        [("22", AMBER), ("90M", AMBER), ("Borderline", AMBER)],
    ]
    styled_table(slide, ["n", "Ops", "Status"], rows,
                 8.3, 4.2, [0.9, 1.7, 2.0], row_h=0.45,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    callout(slide, "Bitmask DP shine: n ≤ 20",
            8.3, 6.4, 4.6, 0.6, color=EMERALD, icon="✨")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Bitmask Pitfalls")

    mistakes = [
        ("1. 1 << i untuk i ≥ 32",
         "Overflow di int!\nPakai 1LL << i untuk long long.",
         ROSE),
        ("2. Lupa precedence operator",
         "(mask & 1<<i) != 0 SALAH.\nPakai ((mask>>i)&1) yang aman.",
         ROSE),
        ("3. Loop sampai (1<<n) saja",
         "Iterasi 0..2^n-1.\nfor mask = 0; mask < (1<<n); ✓",
         AMBER),
        ("4. Dimensi dp[1<<n][n]",
         "Untuk n=20: 1M × 20 × 4B = 80MB.\nHati-hati MLE!",
         AMBER),
        ("5. Submask loop salah",
         "sub = (sub-1) & mask, BUKAN sub--.\nBerhenti saat sub == 0 jika sudah proses.",
         AMBER),
        ("6. __builtin_popcount untuk ll",
         "popcount → 32-bit saja.\nPakai popcountll untuk long long.",
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
    slide_header(slide, "Cheatsheet — Bitmask Quick Reference")

    cheat_left = """// === OPERATIONS ===
mask & (1 << i)     // cek bit i
mask | (1 << i)     // set bit i
mask & ~(1 << i)    // clear bit i
mask ^ (1 << i)     // toggle bit i

// === BUILTIN ===
__builtin_popcount(x)    // count 1
__builtin_popcountll(x)  // ll version
__builtin_ctz(x)         // trailing zeros
__builtin_clz(x)         // leading zeros

// === LOWEST BIT ===
int low = mask & -mask;
int idx = __builtin_ctz(mask);
mask &= mask - 1;        // clear lowest"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10.5, accent=PRIMARY)

    cheat_right = """// === ENUM SEMUA SUBSET ===
for (int m = 0; m < (1<<n); m++) {
    for (int i = 0; i < n; i++)
        if ((m>>i) & 1) ...
}

// === ENUM SUBMASK O(3^n) ===
for (int s = m; s > 0; s = (s-1) & m) {
    // s adalah submask dari m
}

// === ALL ELEMENTS ===
int full = (1 << n) - 1;  // 11...1
int empty = 0;            // 00...0"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10.5, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 13, "Bitmask: representasi set elegan & operasi O(1)", [
        (PRIMARY, "Konsep", "Set sebagai integer. Bit i = elemen i. Maks n=20 untuk int, 60 untuk ll."),
        (EMERALD, "Operators", "AND/OR/XOR/shift. Cek/set/clear/toggle bit. popcount untuk hitung 1."),
        (AMBER, "Subset Enum", "for mask=0..2ⁿ. Submask O(3ⁿ): sub=(sub-1)&mask. Berhenti di 0."),
        (VIOLET, "Aplikasi", "TSP bitmask DP O(n²·2ⁿ). SOS DP, Hamiltonian path. Shine untuk n≤20."),
        (ROSE, "Pitfall", "1<<i untuk i≥32 overflow. Pakai 1LL. popcountll untuk ll. Hati-hati precedence."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_13_Presentation.pptx"))


if __name__ == "__main__":
    main()
