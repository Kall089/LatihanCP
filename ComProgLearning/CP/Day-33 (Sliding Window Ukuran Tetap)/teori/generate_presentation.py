#!/usr/bin/env python3
"""Day 20 — Sliding Window (Fixed, Variable, Monotonic Deque)."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ───────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["fixed", "variable", "freq-map", "monotonic"]
        cols = [PRIMARY, EMERALD, AMBER, VIOLET]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.2 + i * 1.7
            rounded_rect(slide, cx, 5.6, 1.6, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.6, 0.4,
               size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 20, "Sliding Window",
                ["Fixed  ·  Variable  ·  Monotonic Deque",
                 "Subarray kontinu O(n) — amortized analysis"],
                decoration=cov_deco)

    # ── Agenda ──────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 20", [
        ("01", "Konsep &\nIntuisi", PRIMARY,
         ["Sliding window", "Reuse antar window", "Fixed vs Variable", "Amortized O(n)"]),
        ("02", "Fixed-Size\nWindow", EMERALD,
         ["Sum / Avg / Count", "Slide-add-remove", "Anagram check", "K tetap"]),
        ("03", "Variable\nSize", AMBER,
         ["Longest constraint", "Shortest constraint", "Freq map", "K distinct"]),
        ("04", "Monotonic\nDeque", VIOLET,
         ["Window max/min", "O(n) total", "Decreasing dq", "Index-based"]),
    ])

    # ═══════════════════════════════════════════════════════════
    # SECTION 01 — Konsep
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "01", "Konsep & Intuisi",
                    "Reuse antar window — tiap elemen masuk & keluar 1×")

    # ── Apa itu Sliding Window? ────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Sliding Window?",
                 "Geser jendela ukuran K, manfaatkan tumpang-tindih")

    info_card(slide, "Properti Sliding Window", [
        "• Subarray/substring KONTINU yang bergerak",
        "• 1 elemen masuk (kanan), 1 keluar (kiri)",
        "• Reuse hasil → O(1) per slide",
        "• Total operasi 2n → amortized O(n)",
        "• Pointer L, R hanya MAJU (tidak mundur)",
    ], 0.5, 1.1, 5.8, 3.0, accent=PRIMARY)

    # Right: Visualisasi sliding K=3 pada [2,1,5,1,3,2]
    tb(slide, "A = [2, 1, 5, 1, 3, 2],  K = 3",
       6.5, 1.1, 6.3, 0.4, size=12, bold=True, color=AMBER, font_name="Menlo")

    # Window 1: highlight 0..2
    tb(slide, "W1: sum = 2+1+5 = 8", 6.5, 1.6, 6.3, 0.3,
       size=10, color=PRIMARY, font_name="Menlo")
    array_cells(slide, [2, 1, 5, 1, 3, 2], 6.5, 2.0,
                cell_w=0.55, cell_h=0.5,
                highlights={0: PRIMARY, 1: PRIMARY, 2: PRIMARY})

    # Window 2: highlight 1..3
    tb(slide, "W2: 8 - 2 + 1 = 7", 6.5, 2.7, 6.3, 0.3,
       size=10, color=EMERALD, font_name="Menlo")
    array_cells(slide, [2, 1, 5, 1, 3, 2], 6.5, 3.1,
                cell_w=0.55, cell_h=0.5,
                highlights={1: EMERALD, 2: EMERALD, 3: EMERALD})

    # Window 3: highlight 2..4
    tb(slide, "W3: 7 - 1 + 3 = 9   ← MAX", 6.5, 3.8, 6.3, 0.3,
       size=10, color=AMBER, font_name="Menlo")
    array_cells(slide, [2, 1, 5, 1, 3, 2], 6.5, 4.2,
                cell_w=0.55, cell_h=0.5,
                highlights={2: AMBER, 3: AMBER, 4: AMBER})

    metric_card(slide, "Brute Force", "O(n·k)", 0.5, 4.6, 3.0, 1.2, accent=ROSE)
    metric_card(slide, "Sliding Window", "O(n)", 3.7, 4.6, 3.0, 1.2, accent=EMERALD)
    tb(slide, "Speedup: k× untuk fixed, n× untuk variable",
       0.5, 6.0, 6.5, 0.3, size=10, color=MUTED, italic=True)

    # ── Fixed vs Variable ──────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Dua Varian Utama",
                 "Fixed: ukuran tetap K. Variable: window membesar/mengecil.")

    # Fixed visualization
    tb(slide, "FIXED-SIZE — slide 1 langkah", 0.5, 1.1, 6.3, 0.4,
       size=14, bold=True, color=PRIMARY)
    rounded_rect(slide, 0.5, 1.55, 6.3, 2.6, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 1.55, 6.3, 0.08, PRIMARY)

    # Step 1
    tb(slide, "Step 1: [L=0, R=2]", 0.7, 1.75, 5.0, 0.3,
       size=10, color=PRIMARY)
    array_cells(slide, [1, 2, 3, 4, 5, 6], 0.7, 2.1,
                cell_w=0.45, cell_h=0.45,
                highlights={0: PRIMARY, 1: PRIMARY, 2: PRIMARY},
                value_size=10)

    # Step 2
    tb(slide, "Step 2: [L=1, R=3]", 0.7, 2.75, 5.0, 0.3,
       size=10, color=EMERALD)
    array_cells(slide, [1, 2, 3, 4, 5, 6], 0.7, 3.1,
                cell_w=0.45, cell_h=0.45,
                highlights={1: EMERALD, 2: EMERALD, 3: EMERALD},
                value_size=10)

    tb(slide, "L & R maju bersamaan, K tetap",
       0.7, 3.7, 6.0, 0.3, size=10, italic=True, color=SLATE)

    # Variable visualization
    tb(slide, "VARIABLE-SIZE — expand & shrink", 6.9, 1.1, 6.3, 0.4,
       size=14, bold=True, color=AMBER)
    rounded_rect(slide, 6.9, 1.55, 6.3, 2.6, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    rect(slide, 6.9, 1.55, 6.3, 0.08, AMBER)

    # Step 1
    tb(slide, "Expand R → window membesar", 7.1, 1.75, 5.5, 0.3,
       size=10, color=EMERALD)
    array_cells(slide, [1, 2, 3, 4, 5, 6], 7.1, 2.1,
                cell_w=0.45, cell_h=0.45,
                highlights={0: EMERALD, 1: EMERALD, 2: EMERALD,
                            3: EMERALD},
                value_size=10)

    # Step 2
    tb(slide, "Shrink L → window mengecil saat invalid",
       7.1, 2.75, 5.5, 0.3, size=10, color=ROSE)
    array_cells(slide, [1, 2, 3, 4, 5, 6], 7.1, 3.1,
                cell_w=0.45, cell_h=0.45,
                highlights={2: ROSE, 3: ROSE},
                value_size=10)

    tb(slide, "L & R independen, ukuran berubah",
       7.1, 3.7, 6.0, 0.3, size=10, italic=True, color=SLATE)

    # Decision tree at bottom
    rounded_rect(slide, 0.5, 4.4, 12.7, 2.6, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 4.4, 12.7, 0.08, VIOLET)
    tb(slide, "🎯 Decision Tree: Pilih Varian", 0.7, 4.55, 8.0, 0.4,
       size=13, bold=True, color=VIOLET)

    decisions = [
        ("'Subarray ukuran TEPAT K'", "→ FIXED", PRIMARY),
        ("'Subarray TERPANJANG yang ...'", "→ VARIABLE LONGEST", EMERALD),
        ("'Subarray TERPENDEK yang ...'", "→ VARIABLE SHORTEST", AMBER),
        ("'Max/Min tiap window K'", "→ MONOTONIC DEQUE", VIOLET),
    ]
    for i, (q, ans, col) in enumerate(decisions):
        cn = i % 2
        rn = i // 2
        dx = 0.7 + cn * 6.2
        dy = 5.0 + rn * 0.95
        tb(slide, q, dx, dy, 4.0, 0.32, size=11, color=SILVER)
        tb(slide, ans, dx, dy + 0.35, 4.0, 0.32,
           size=11, bold=True, color=col)

    # ═══════════════════════════════════════════════════════════
    # SECTION 02 — Fixed-Size
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "02", "Fixed-Size Window",
                    "Ukuran K tetap — sum, avg, count, anagram",
                    color=EMERALD)

    # ── Fixed-Size Code + Visual ──────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Fixed-Size — Maximum Sum Subarray K",
                 "Inisialisasi window pertama, lalu slide")

    code = """// Init: hitung sum window pertama
ll sum = 0;
for (int i = 0; i < k; i++)
    sum += A[i];
ll ans = sum;

// Slide: tambah kanan, kurangi kiri
for (int i = k; i < n; i++) {
    sum += A[i] - A[i - k];
    ans = max(ans, sum);
}

// Window pada iterasi i: [i-k+1, i]
// +A[i] = elemen baru masuk
// -A[i-k] = elemen lama keluar"""
    code_box(slide, code, 0.5, 1.1, 6.3, 4.2, font_size=11, accent=EMERALD)

    # Right: Trace visualization
    tb(slide, "Trace: A=[2,1,5,1,3,2], K=3",
       7.0, 1.1, 5.8, 0.4, size=12, bold=True, color=AMBER)

    trace = [
        ("init", "[2,1,5]", "8", "8"),
        ("i=3", "[1,5,1]", "7", "8"),
        ("i=4", "[5,1,3]", "9", "9"),
        ("i=5", "[1,3,2]", "6", "9"),
    ]
    # Header row
    rect(slide, 7.0, 1.6, 5.8, 0.4, EMERALD)
    headers = ["Step", "Window", "Sum", "Ans"]
    for j, h in enumerate(headers):
        tb(slide, h, 7.0 + j * 1.45, 1.65, 1.45, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    for i, row in enumerate(trace):
        ry = 2.05 + i * 0.45
        bg = BG_CARD if i % 2 == 0 else BG_CARD_2
        rect(slide, 7.0, ry, 5.8, 0.4, bg)
        for j, cell in enumerate(row):
            col = AMBER if j == 3 and i == 2 else WHITE
            tb(slide, cell, 7.0 + j * 1.45, ry + 0.07, 1.45, 0.3,
               size=10, color=col, font_name="Menlo",
               align=PP_ALIGN.CENTER)

    callout(slide, "Window terbaik [5,1,3] dengan sum = 9",
            7.0, 4.05, 5.8, 0.6, color=EMERALD)

    # Bottom: anagram pattern
    rounded_rect(slide, 0.5, 5.5, 12.3, 1.7, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 5.5, 12.3, 0.08, PRIMARY)
    tb(slide, "Pattern: Fixed Window + Frequency (Anagram Check)",
       0.7, 5.6, 8.0, 0.4, size=12, bold=True, color=PRIMARY)
    code2 = """vector<int> need(26), have(26);
for (char c : t) need[c - 'a']++;
for (int i = 0; i < n; i++) {
    have[s[i] - 'a']++;
    if (i >= m) have[s[i - m] - 'a']--;
    if (i >= m - 1 && have == need) cout << i - m + 1;
}"""
    plain_code_box(slide, code2, 0.7, 6.0, 12.0, 1.1, font_size=10,
                   accent=PRIMARY, text_color=SILVER)

    # ═══════════════════════════════════════════════════════════
    # SECTION 03 — Variable-Size
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "03", "Variable-Size Window",
                    "Expand R, shrink L — longest / shortest / freq",
                    color=AMBER)

    # ── Variable Longest ──────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Variable Longest — Subarray Sum ≤ K",
                 "Expand R selalu, shrink L sampai valid")

    code = """int L = 0, ans = 0;
ll sum = 0;

for (int R = 0; R < n; R++) {
    sum += A[R];                  // expand kanan

    while (sum > K && L <= R) {   // shrink kiri sampai valid
        sum -= A[L];
        L++;
    }

    ans = max(ans, R - L + 1);    // window valid
}"""
    code_box(slide, code, 0.5, 1.1, 6.3, 4.0, font_size=11, accent=AMBER)

    # Right: Pattern template
    insight_card(slide, "Pola Variable LONGEST", [
        "Expand R tanpa syarat",
        "while (INVALID) shrink L",
        "Update ans SETELAH valid",
        "Pre-condition: A[i] ≥ 0",
    ], 7.0, 1.1, 5.8, 2.0)

    code2 = """// TEMPLATE GENERIK:
for (int R = 0; R < n; R++) {
    add(A[R]);
    while (invalid()) {
        remove(A[L++]);
    }
    ans = max(ans, R - L + 1);
}"""
    code_box(slide, code2, 7.0, 3.25, 5.8, 1.85, font_size=10.5, accent=PRIMARY)

    warn_card(slide, "Hati-hati Pre-condition!",
              ["Sliding window sum-based hanya jalan jika A[i] ≥ 0",
               "Kalau ada nilai negatif → sum bisa naik-turun",
               "Pakai prefix sum + map untuk array negatif"],
              0.5, 5.3, 12.3, 1.9)

    # ── Variable Shortest ─────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Variable Shortest — Subarray Sum ≥ S",
                 "Update ans DI DALAM loop shrink (saat masih valid)")

    code = """int L = 0, ans = INT_MAX;
ll sum = 0;

for (int R = 0; R < n; R++) {
    sum += A[R];                 // expand

    while (sum >= S) {           // selama valid
        ans = min(ans, R - L + 1); // update di sini!
        sum -= A[L];
        L++;
    }
}
cout << (ans == INT_MAX ? 0 : ans);"""
    code_box(slide, code, 0.5, 1.1, 6.3, 4.5, font_size=11, accent=AMBER)

    # Right: comparison
    comparison_panel(slide, 7.0, 1.1, 5.8, 4.5,
                     "LONGEST",
                     ["• while (INVALID) shrink",
                      "• Update ans SETELAH while",
                      "• Cari max length",
                      "• ans = max(...)",
                      "• Init ans = 0"],
                     "SHORTEST",
                     ["• while (VALID) shrink",
                      "• Update ans DI DALAM while",
                      "• Cari min length",
                      "• ans = min(...)",
                      "• Init ans = INT_MAX"],
                     left_color=EMERALD, right_color=AMBER)

    # Bottom: trace
    rounded_rect(slide, 0.5, 5.75, 12.3, 1.45, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 5.75, 12.3, 0.08, VIOLET)
    tb(slide, "Trace: A=[2,1,5,2,3,2], S=7  →  output = 2 (window [5,2])",
       0.7, 5.85, 12.0, 0.35, size=12, bold=True, color=VIOLET)
    tb(slide,
       "R=2: sum=8≥7 → ans=3 [2,1,5];  shrink L=1 sum=6.   "
       "R=3: sum=8 → ans=3 [1,5,2]; shrink L=2 sum=7→ans=2 [5,2]; shrink L=3.",
       0.7, 6.25, 12.0, 0.85, size=10, color=SILVER)

    # ── Frequency Map: K Distinct ─────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Variable + Frequency Map — Longest K Distinct",
                 "Substring dengan paling banyak K karakter berbeda")

    code = """unordered_map<char, int> freq;
int L = 0, ans = 0;

for (int R = 0; R < n; R++) {
    freq[s[R]]++;                          // tambah char baru

    while ((int)freq.size() > K) {         // > K distinct → shrink
        freq[s[L]]--;
        if (freq[s[L]] == 0)
            freq.erase(s[L]);              // ⚠ wajib erase!
        L++;
    }

    ans = max(ans, R - L + 1);
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.5, font_size=10.5, accent=AMBER)

    # Right: trace
    tb(slide, "Trace: s=\"araaci\", K=2",
       7.2, 1.1, 5.6, 0.4, size=12, bold=True, color=AMBER)

    trace2 = [
        ("0", "a", "{a:1}", "1", "0", "1"),
        ("1", "r", "{a:1,r:1}", "2", "0", "2"),
        ("2", "a", "{a:2,r:1}", "2", "0", "3"),
        ("3", "a", "{a:3,r:1}", "2", "0", "4"),
        ("4", "c", "{a:2,c:1}", "2", "2", "4"),
        ("5", "i", "{c:1,i:1}", "2", "4", "4"),
    ]
    rect(slide, 7.2, 1.6, 5.7, 0.38, AMBER)
    headers2 = ["R", "ch", "freq", "sz", "L", "ans"]
    widths2 = [0.45, 0.45, 1.95, 0.55, 0.55, 0.55]
    cum = 7.2
    for h, w in zip(headers2, widths2):
        tb(slide, h, cum + 0.03, 1.65, w - 0.06, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cum += w
    for i, row in enumerate(trace2):
        ry = 2.0 + i * 0.42
        bg = BG_CARD if i % 2 == 0 else BG_CARD_2
        rect(slide, 7.2, ry, 5.7, 0.38, bg)
        cum = 7.2
        for cell, w in zip(row, widths2):
            tb(slide, cell, cum + 0.03, ry + 0.06, w - 0.06, 0.3,
               size=9, color=WHITE, font_name="Menlo",
               align=PP_ALIGN.CENTER)
            cum += w

    callout(slide, "Hasil: ans = 4 (substring \"araa\")",
            7.2, 4.65, 5.6, 0.55, color=EMERALD)

    warn_card(slide, "Wajib erase!",
              ["freq[s[L]]-- saja TIDAK CUKUP",
               "Harus erase saat count = 0,",
               "kalau tidak freq.size() over-count!"],
              0.5, 5.85, 12.3, 1.4)

    # ═══════════════════════════════════════════════════════════
    # SECTION 04 — Monotonic Deque
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "04", "Monotonic Deque",
                    "Sliding window max / min — O(n) total",
                    color=VIOLET)

    # ── Monotonic Deque Code ──────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Sliding Window Maximum — Monotonic Deque",
                 "Deque simpan INDEX, A[idx] decreasing dari front")

    code = """deque<int> dq;   // simpan index

for (int i = 0; i < n; i++) {
    // 1. Buang front yang sudah keluar window
    while (!dq.empty() && dq.front() <= i - k)
        dq.pop_front();

    // 2. Buang back yang nilainya ≤ A[i]
    //    (mereka tidak akan jadi max selama A[i] ada)
    while (!dq.empty() && A[dq.back()] <= A[i])
        dq.pop_back();

    // 3. Push index sekarang
    dq.push_back(i);

    // 4. Output max ketika window penuh
    if (i >= k - 1)
        cout << A[dq.front()] << ' ';
}"""
    code_box(slide, code, 0.5, 1.1, 6.7, 5.5, font_size=10.5, accent=VIOLET)

    # Right: invariants
    insight_card(slide, "Invariant Deque", [
        "Index di dq selalu di [i-k+1, i]",
        "A[front] ≥ A[next] ≥ ... ≥ A[back]",
        "A[front] = MAX di window sekarang",
        "Tiap elemen masuk & keluar 1× → O(n)",
    ], 7.4, 1.1, 5.6, 2.4)

    info_card(slide, "Untuk window MIN",
              [("• Tukar perbandingan saja:", SILVER),
               ("while A[dq.back()] >= A[i]", AMBER),
               ("• Sisanya identik dengan max", SILVER),
               ("• Front = MIN di window", SILVER)],
              7.4, 3.65, 5.6, 1.85, accent=EMERALD)

    metric_card(slide, "Brute Force", "O(n·k)", 7.4, 5.7, 2.7, 1.0,
                accent=ROSE)
    metric_card(slide, "Mono Deque", "O(n)", 10.3, 5.7, 2.7, 1.0,
                accent=EMERALD)

    # ── Monotonic Deque Trace ─────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Trace Monotonic Deque",
                 "A=[1,3,-1,-3,5,3,6,7], K=3")

    # Trace table
    trace3 = [
        ("0", "1", "-", "-", "[0]", "—"),
        ("1", "3", "-", "pop A[0]=1", "[1]", "—"),
        ("2", "-1", "-", "-", "[1,2]", "3"),
        ("3", "-3", "-", "-", "[1,2,3]", "3"),
        ("4", "5", "-", "pop A[3,2,1]", "[4]", "5"),
        ("5", "3", "-", "-", "[4,5]", "5"),
        ("6", "6", "-", "pop A[5,4]", "[6]", "6"),
        ("7", "7", "-", "pop A[6]", "[7]", "7"),
    ]
    headers3 = ["i", "A[i]", "Pop front", "Pop back", "dq (idx)", "Out"]
    widths3 = [0.6, 0.85, 1.6, 2.6, 2.4, 0.85]

    # Header
    cumx = 0.5
    for h, w in zip(headers3, widths3):
        rect(slide, cumx, 1.2, w - 0.04, 0.45, VIOLET)
        tb(slide, h, cumx + 0.05, 1.27, w - 0.1, 0.32,
           size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cumx += w

    for ri, row in enumerate(trace3):
        ry = 1.7 + ri * 0.42
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        total_w = sum(widths3) - 0.04
        rect(slide, 0.5, ry, total_w, 0.4, bg)
        cumx = 0.5
        for cell, w in zip(row, widths3):
            tb(slide, cell, cumx + 0.05, ry + 0.06, w - 0.1, 0.3,
               size=10, color=WHITE, font_name="Menlo",
               align=PP_ALIGN.CENTER)
            cumx += w

    # Output box
    rounded_rect(slide, 0.5, 5.2, 12.3, 1.0, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.2, 12.3, 0.08, EMERALD)
    tb(slide, "✓ Output: 3 3 5 5 6 7  (max tiap window K=3)",
       0.7, 5.45, 12.0, 0.5, size=14, bold=True, color=EMERALD,
       align=PP_ALIGN.CENTER)

    # Visualization of array
    array_cells(slide, [1, 3, -1, -3, 5, 3, 6, 7], 1.3, 6.5,
                cell_w=0.6, cell_h=0.5,
                highlights={4: AMBER, 5: AMBER, 6: AMBER, 7: AMBER})
    tb(slide, "Window terakhir [5,3,6,7] → max akhir = 7",
       7.5, 6.6, 5.4, 0.35, size=11, color=AMBER, italic=True)

    # ═══════════════════════════════════════════════════════════
    # PATTERNS
    # ═══════════════════════════════════════════════════════════
    slide = new_slide(prs)
    slide_header(slide, "Pattern Recognition — Mana Sliding Window?")
    rows = [
        ["Subarray ukuran TEPAT K", "Fixed-size", "O(n)", "Max sum K"],
        ["Subarray TERPANJANG, sum ≤ K", "Var Longest", "O(n)", "A[i] ≥ 0"],
        ["Subarray TERPENDEK, sum ≥ S", "Var Shortest", "O(n)", "Min length"],
        ["Substring ≤ K karakter unik", "Var + freq map", "O(n)", "freq.size()"],
        ["Hitung subarray sum ≤ K", "Var + count", "O(n)", "cnt += R-L+1"],
        ["Exactly K distinct", "atMost(K) - atMost(K-1)", "O(n)", "Trick"],
        ["Anagram windows", "Fixed + freq array", "O(n)", "Compare arrays"],
        ["Maximum/Minimum tiap window K", "Monotonic Deque", "O(n)", "Index-based"],
    ]
    styled_table(slide, ["Situasi", "Strategi", "Kompleksitas", "Catatan"],
                 rows, 0.5, 1.2, [4.0, 3.4, 2.5, 2.4], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET])

    # ═══════════════════════════════════════════════════════════
    # COMMON MISTAKES
    # ═══════════════════════════════════════════════════════════
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Hindari Ini!")
    mistakes = [
        ("1. Pakai `if` bukan `while`",
         "Kondisi violated bisa berlangsung beberapa langkah!\n"
         "while (sum > K) shrink, BUKAN if.",
         ROSE),
        ("2. Update ans sebelum shrink",
         "Window mungkin masih invalid!\n"
         "Pola LONGEST: shrink dulu, baru update.",
         ROSE),
        ("3. Lupa erase di freq map",
         "freq[s[L]]-- saja tidak cukup.\n"
         "if (freq[c]==0) freq.erase(c); WAJIB.",
         AMBER),
        ("4. Sliding window pada negatif",
         "Sum bisa naik-turun → monotonicity hilang!\n"
         "Untuk negatif: prefix sum + map.",
         AMBER),
        ("5. Off-by-one panjang window",
         "Panjang [L, R] inclusive = R - L + 1\n"
         "BUKAN R - L (itu kurang 1)!",
         AMBER),
        ("6. Lupa init window pertama (Fixed)",
         "Loop tunggal sering bug saat i < k-1\n"
         "Lebih aman: init [0..k-1], lalu slide.",
         VIOLET),
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

    # ═══════════════════════════════════════════════════════════
    # CHEATSHEET
    # ═══════════════════════════════════════════════════════════
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Quick Reference")

    cheat_left = """// FIXED-SIZE
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
}"""

    cheat_right = """// VARIABLE SHORTEST
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
    while (!dq.empty() && dq.front() <= i-k)
        dq.pop_front();
    while (!dq.empty() && A[dq.back()] <= A[i])
        dq.pop_back();
    dq.push_back(i);
    if (i >= k-1) cout << A[dq.front()];
}"""

    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 4.5, font_size=10.5, accent=PRIMARY)
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 4.5, font_size=10.5, accent=VIOLET)

    # Aturan emas
    rounded_rect(slide, 0.5, 5.85, 12.3, 1.4, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.85, 12.3, 0.08, EMERALD)
    tb(slide, "🌟 Aturan Emas",
       0.7, 5.95, 5.0, 0.4, size=13, bold=True, color=EMERALD)
    rules = [
        ("• Pakai while, BUKAN if untuk shrink", SILVER),
        ("• Pakai long long untuk sum (overflow!)", SILVER),
        ("• Panjang window = R - L + 1", SILVER),
        ("• Test edge: k=1, k=n, n=0", SILVER),
    ]
    for i, (text, col) in enumerate(rules):
        cn = i % 2
        rn = i // 2
        tb(slide, text, 0.7 + cn * 6.0, 6.3 + rn * 0.35,
           5.8, 0.32, size=10, color=col)

    # ═══════════════════════════════════════════════════════════
    # CLOSING
    # ═══════════════════════════════════════════════════════════
    closing_slide(prs, 20, "Sliding Window — Subarray kontinu O(n)", [
        (PRIMARY, "Konsep",
         "Reuse hasil antar window. Pointer L,R hanya maju → tiap elemen 1× masuk & keluar."),
        (EMERALD, "Fixed-Size",
         "Init window [0..k-1], lalu sum += A[i] - A[i-k]. Pattern anagram: freq array."),
        (AMBER, "Variable",
         "Longest: shrink saat invalid, update setelah. Shortest: shrink saat valid, update di dalam."),
        (VIOLET, "Monotonic Deque",
         "Simpan INDEX, A[idx] decreasing. Front = max window. O(n) untuk window max/min."),
        (ROSE, "Pitfall",
         "while bukan if, A[i]≥0 untuk sum, freq.erase wajib, panjang R-L+1, init window pertama."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_20_Presentation.pptx"))


if __name__ == "__main__":
    main()
