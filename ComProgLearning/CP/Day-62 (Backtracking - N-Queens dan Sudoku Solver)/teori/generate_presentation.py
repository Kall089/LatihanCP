#!/usr/bin/env python3
"""Day 12 — Backtracking: permutation, subset, N-Queens, combination sum."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["Choose", "Explore", "Undo"]
        cols = [PRIMARY, AMBER, EMERALD]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.5 + i * 2.0
            rounded_rect(slide, cx, 5.6, 1.85, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.85, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 12, "Backtracking",
                ["Choose · Explore · Undo",
                 "Eksplorasi sistematis dengan pruning"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 12", [
        ("01", "Paradigma\nBacktracking", PRIMARY,
         ["Choose-Explore-Undo", "Recursion tree", "Pruning", "State management"]),
        ("02", "Permutation\n& Subset", EMERALD,
         ["Permutation O(n!)", "Subset O(2ⁿ)", "used[] array", "start index"]),
        ("03", "N-Queens &\nCombination", AMBER,
         ["N-Queens", "Diagonal check", "Combination sum", "Sort + break"]),
        ("04", "Word Search\n& Aplikasi", VIOLET,
         ["DFS di grid", "Mark & restore", "Graph coloring", "BT vs DP"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Paradigma Backtracking",
                    "3 langkah: Choose → Explore → Undo (CEU)")

    slide = new_slide(prs)
    slide_header(slide, "Pola Universal Backtracking",
                 "Sebuah template yang akan kamu pakai berulang kali")

    code = """void backtrack(state) {
    // 1. BASE CASE — solusi ditemukan
    if (goal_reached) {
        record_solution();
        return;
    }

    // 2. CABANG — coba setiap pilihan
    for (each choice) {
        if (is_valid(choice)) {  // ← PRUNING
            make_choice(choice);     // CHOOSE
            backtrack(next_state);   // EXPLORE
            undo_choice(choice);     // UNDO
        }
    }
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.0, font_size=11.5, accent=PRIMARY)

    # Right: 3-step diagram
    tb(slide, "🔄 3 Langkah Inti", 7.2, 1.1, 5.7, 0.4,
       size=14, bold=True, color=AMBER)
    steps = [
        ("CHOOSE", "Tambah pilihan ke state\n(push_back, mark visited)", PRIMARY),
        ("EXPLORE", "Rekursi ke level berikutnya\ndengan state baru", EMERALD),
        ("UNDO", "Restore state ke kondisi\nsebelum CHOOSE (pop, unmark)", AMBER),
    ]
    for i, (title, desc, col) in enumerate(steps):
        ty = 1.65 + i * 1.5
        rounded_rect(slide, 7.2, ty, 5.7, 1.35, BG_CARD,
                     line_color=col, line_w=1.0)
        circle(slide, 7.55, ty + 0.5, 0.32, col)
        tb(slide, str(i + 1), 7.25, ty + 0.27, 0.65, 0.5,
           size=18, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        tb(slide, title, 8.0, ty + 0.18, 4.5, 0.35,
           size=13, bold=True, color=col)
        tb(slide, desc, 8.0, ty + 0.55, 4.5, 0.75,
           size=10.5, color=SILVER)

    callout(slide, "KUNCI: setiap make_choice WAJIB di-undo!",
            7.2, 6.3, 5.7, 0.6, color=ROSE, icon="⚠")

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "Permutation & Subset",
                    "Dua pola fondasi: used[] untuk permutasi, start untuk subset",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Generate Permutations — used[] Array")
    code = """vector<int> perm;
vector<bool> used(n+1, false);

void backtrack() {
    if ((int)perm.size() == n) {
        print(perm);   // 1 solusi
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        used[i] = true;            // CHOOSE
        perm.push_back(i);
        backtrack();               // EXPLORE
        perm.pop_back();           // UNDO
        used[i] = false;
    }
}
// Total: n! permutasi"""
    code_box(slide, code, 0.5, 1.1, 6.4, 5.5, font_size=11, accent=EMERALD)

    # Right: Tree visualization for n=3 with proper edges
    tb(slide, "🌳 Recursion Tree — perm of {1,2,3}",
       7.1, 1.1, 5.8, 0.4, size=12, bold=True, color=AMBER)

    # Helper to draw a "pill" node + draw edges using line()
    pill_nodes = [
        # (text, cx, cy, color)
        ("[]",     10.0, 1.75, PRIMARY),    # 0: root
        ("[1]",     7.5, 2.65, EMERALD),    # 1
        ("[2]",    10.0, 2.65, EMERALD),    # 2
        ("[3]",    12.5, 2.65, EMERALD),    # 3
        ("[1,2]",   6.6, 3.7,  AMBER),      # 4
        ("[1,3]",   8.4, 3.7,  AMBER),      # 5
        ("[2,1]",   9.3, 3.7,  AMBER),      # 6
        ("[2,3]",  10.7, 3.7,  AMBER),      # 7
        ("[3,1]",  11.7, 3.7,  AMBER),      # 8
        ("[3,2]",  13.1, 3.7,  AMBER),      # 9
    ]
    pill_edges = [(0, 1), (0, 2), (0, 3),
                  (1, 4), (1, 5),
                  (2, 6), (2, 7),
                  (3, 8), (3, 9)]
    # Draw edges first
    pill_w, pill_h = 0.8, 0.36
    for a, b in pill_edges:
        x1, y1 = pill_nodes[a][1], pill_nodes[a][2]
        x2, y2 = pill_nodes[b][1], pill_nodes[b][2]
        # Start from bottom of parent, end at top of child
        line(slide, x1, y1 + pill_h / 2, x2, y2 - pill_h / 2,
             color=SLATE, thickness=1.25)
    # Draw pills on top
    for txt, cx, cy, col in pill_nodes:
        rounded_rect(slide, cx - pill_w / 2, cy - pill_h / 2,
                     pill_w, pill_h, col)
        tb(slide, txt, cx - pill_w / 2, cy - pill_h / 2 + 0.04,
           pill_w, pill_h - 0.08,
           size=9, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    info_card(slide, "Kompleksitas",
              ["• Total: O(n! × n)",
               "• Depth: O(n)",
               "• n=8 → 40,320 permutasi",
               "• n=12 → ~479M (TLE)"],
              7.1, 4.2, 5.8, 1.7, accent=PRIMARY)

    callout(slide, "Untuk n>11, permutasi sudah TLE. Pakai DP / bitmask.",
            7.1, 6.05, 5.8, 0.7, color=AMBER, icon="💡")

    # ── Slide: Subset ──────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Generate Subsets (Power Set) — start Index")
    code = """vector<int> subset;

void backtrack(int start) {
    print(subset);   // termasuk subset kosong

    for (int i = start; i <= n; i++) {
        subset.push_back(i);    // CHOOSE
        backtrack(i + 1);       // i+1: tidak ulang
        subset.pop_back();      // UNDO
    }
}
// Panggil: backtrack(1)
// Total: 2^n subset"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.6, font_size=11, accent=AMBER)

    # Right: example output
    tb(slide, "📋 Output untuk n=3 — 2³=8 subset",
       7.1, 1.1, 5.8, 0.4, size=13, bold=True, color=PRIMARY)

    subsets_list = [
        ("{}", VIOLET),
        ("{1}", PRIMARY),
        ("{1, 2}", EMERALD),
        ("{1, 2, 3}", EMERALD),
        ("{1, 3}", PRIMARY),
        ("{2}", PRIMARY),
        ("{2, 3}", EMERALD),
        ("{3}", PRIMARY),
    ]
    for i, (txt, col) in enumerate(subsets_list):
        cn = i % 2
        rn = i // 2
        cx = 7.1 + cn * 2.95
        cy = 1.65 + rn * 0.55
        rounded_rect(slide, cx, cy, 2.85, 0.45, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, txt, cx, cy + 0.05, 2.85, 0.35,
           size=11, bold=True, color=col, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    info_card(slide, "Kompleksitas",
              ["• Total: O(2ⁿ × n)",
               "• n=20 → 1M subset",
               "• n=25 → 33M (kemungkinan TLE)"],
              7.1, 4.2, 5.8, 1.5, accent=AMBER)

    callout(slide, "Alternatif: Bitmask enumeration (lebih cepat & bersih)",
            7.1, 5.85, 5.8, 0.7, color=EMERALD, icon="✨")

    # Bottom rule
    rounded_rect(slide, 0.5, 5.85, 6.4, 1.1, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 5.85, 6.4, 0.05, VIOLET)
    tb(slide, "🔑 Trick start: hindari duplicate subset",
       0.7, 5.95, 6.0, 0.3, size=11, bold=True, color=VIOLET)
    tb(slide, "i+1 dalam rekursi memastikan setiap elemen dipakai\n"
              "maksimal sekali per cabang → tidak ada {1,2} & {2,1}.",
       0.7, 6.25, 6.0, 0.6, size=10, color=SILVER)

    # ── Section 03 ─────────────────────────────────────────────
    section_divider(prs, "03", "N-Queens & Combination Sum",
                    "Aplikasi klasik dengan pruning constraint",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "N-Queens — Constraint dengan 3 array")

    code = """bool cols[N], diag1[2*N], diag2[2*N];
int solutions = 0;

void solve(int row) {
    if (row == n) { solutions++; return; }
    for (int col = 0; col < n; col++) {
        if (cols[col] || diag1[row-col+n]
                      || diag2[row+col]) continue;
        // CHOOSE: tempatkan ratu
        cols[col] = diag1[row-col+n]
                  = diag2[row+col] = true;
        solve(row + 1);                // EXPLORE
        // UNDO: angkat ratu
        cols[col] = diag1[row-col+n]
                  = diag2[row+col] = false;
    }
}"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.5, font_size=10.5, accent=AMBER)

    # Right: 4-queens visualization
    tb(slide, "♛ N-Queens 4×4 — 1 dari 2 solusi",
       7.3, 1.1, 5.8, 0.4, size=13, bold=True, color=PRIMARY)

    # Mini chess board
    queen_positions = {(0, 1), (1, 3), (2, 0), (3, 2)}  # rows, cols
    cell_size = 0.55
    board_x = 7.3
    board_y = 1.7
    for r in range(4):
        for c in range(4):
            cx = board_x + c * cell_size
            cy = board_y + r * cell_size
            cell_color = BG_CARD_2 if (r + c) % 2 == 0 else BG_CARD
            rect(slide, cx, cy, cell_size, cell_size, cell_color,
                 line_color=BORDER, line_w=0.5)
            if (r, c) in queen_positions:
                circle(slide, cx + cell_size / 2, cy + cell_size / 2,
                       0.2, AMBER)
                tb(slide, "♛", cx, cy + 0.05, cell_size, cell_size - 0.1,
                   size=18, color=BG_DEEP, align=PP_ALIGN.CENTER, bold=True)

    # Solutions table
    tb(slide, "📊 Jumlah Solusi", 9.8, 1.7, 3.2, 0.4,
       size=12, bold=True, color=EMERALD)
    rows = [
        ["4", "2"],
        ["8", "92"],
        ["10", "724"],
        ["12", "14,200"],
    ]
    styled_table(slide, ["N", "Solusi"], rows,
                 9.8, 2.2, [1.3, 1.9], row_h=0.45,
                 header_colors=[AMBER, EMERALD], body_size=10, header_size=10)

    insight_card(slide, "Diagonal Index Trick",
                 ["diag1: r-c+n  → ↘ kanan bawah",
                  "diag2: r+c    → ↙ kiri bawah",
                  "+n untuk hindari index negatif"],
                 7.3, 4.7, 5.8, 1.7)

    # ── Slide: Combination Sum ────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Combination Sum — Pruning dengan Sort + Break")

    code = """sort(cands.begin(), cands.end()); // WAJIB!

void backtrack(int start, int target) {
    if (target == 0) {
        result.push_back(current);
        return;
    }
    for (int i = start; i < (int)cands.size(); i++) {
        if (cands[i] > target) break;  // ← PRUNING
        current.push_back(cands[i]);
        backtrack(i, target - cands[i]); // i: boleh ulang
        current.pop_back();
    }
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.5, font_size=11, accent=AMBER)

    # Right: example
    tb(slide, "📋 Contoh: cands=[2,3,5], target=8",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)

    examples = [
        ("[2, 2, 2, 2]", "2+2+2+2 = 8", PRIMARY),
        ("[2, 3, 3]",    "2+3+3 = 8",   EMERALD),
        ("[3, 5]",       "3+5 = 8",     AMBER),
    ]
    for i, (combo, sum_eq, col) in enumerate(examples):
        ty = 1.7 + i * 0.65
        rounded_rect(slide, 7.2, ty, 5.7, 0.55, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, combo, 7.35, ty + 0.05, 2.5, 0.45,
           size=12, bold=True, color=col, font_name="Menlo")
        tb(slide, sum_eq, 9.9, ty + 0.05, 2.95, 0.45,
           size=11, color=SILVER, font_name="Menlo")

    insight_card(slide, "Kenapa Sort + Break?",
                 ["Setelah sort, jika cands[i] > target,",
                  "semua cands[j>i] juga > target",
                  "→ Tidak perlu cek lagi → break",
                  "Memangkas banyak cabang!"],
                 7.2, 3.85, 5.7, 1.9)

    callout(slide,
            "Boleh ulang? Pakai i. Tidak boleh? Pakai i+1.",
            7.2, 5.95, 5.7, 0.7, color=VIOLET, icon="🎯")

    # Bottom: visual of pruning effect
    rounded_rect(slide, 0.5, 5.85, 6.5, 1.4, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.85, 6.5, 0.05, EMERALD)
    tb(slide, "🌳 Pruning Effect: dari 3⁸ → ratusan saja",
       0.7, 5.95, 6.2, 0.3, size=11, bold=True, color=EMERALD)
    tb(slide, "Sort + break pada combination sum mengurangi search space\n"
              "secara drastis. Kompleksitas: O(2^target / min(cands))",
       0.7, 6.3, 6.2, 0.85, size=10, color=SILVER)

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Word Search & Backtracking vs DP",
                    "DFS di grid, mark-restore trick, dan kapan pilih BT vs DP",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Word Search — DFS + Mark/Restore Trick")

    code = """int dr[]={-1,1,0,0}, dc[]={0,0,-1,1};

bool dfs(int r, int c, int idx) {
    if (idx == (int)word.size()) return true;
    if (r<0||r>=R||c<0||c>=C) return false;
    if (grid[r][c] != word[idx]) return false;

    char tmp = grid[r][c];
    grid[r][c] = '#';            // CHOOSE: mark visited

    bool found = false;
    for (int d = 0; d < 4; d++)
        if (dfs(r+dr[d], c+dc[d], idx+1))
            { found = true; break; }

    grid[r][c] = tmp;            // UNDO: restore
    return found;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=10.5, accent=VIOLET)

    # Right: grid visualization
    tb(slide, "🔠 Grid Word Search — cari 'ABCD'",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)

    grid_data = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E'],
    ]
    visited = {(0, 0), (0, 1), (0, 2), (1, 2)}  # path A→B→C→C
    cell_w = 0.62
    cell_h = 0.6
    gx, gy = 7.6, 1.7
    for r in range(3):
        for c in range(4):
            cx = gx + c * cell_w
            cy = gy + r * cell_h
            col = AMBER if (r, c) in visited else BG_CARD_2
            rect(slide, cx, cy, cell_w, cell_h, col,
                 line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if (r, c) in visited else WHITE
            tb(slide, grid_data[r][c], cx, cy + 0.1, cell_w, cell_h - 0.2,
               size=14, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    insight_card(slide, "Mark & Restore Trick",
                 ["grid[r][c] = '#' → tandai visited",
                  "→ rekursi tidak akan kembali",
                  "Setelah rekursi: restore dengan tmp",
                  "Hemat memori vs visited[][]"],
                 7.2, 3.85, 5.7, 1.9)

    callout(slide,
            "Kompleksitas: O(R·C · 4ᴸ) di mana L=panjang word",
            7.2, 5.95, 5.7, 0.7, color=AMBER, icon="📊")

    # ── Slide: BT vs DP ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Backtracking vs Dynamic Programming")

    rows = [
        [("Tujuan", PRIMARY),
         "Cari semua / 1 solusi", "Hitung optimal (min/max/count)"],
        [("State", PRIMARY),
         "Eksplisit (modify+undo)", "Tabular (dp[i][j])"],
        [("Overlap", PRIMARY),
         "Sedikit / tidak", "Banyak (cache wajib)"],
        [("Memori", PRIMARY),
         "O(depth)", "O(state space)"],
        [("Range N", PRIMARY),
         "N ≤ 20 (eksponensial OK)", "N besar (polynomial)"],
        [("Output", PRIMARY),
         "Daftar / satu solusi", "Angka tunggal"],
        [("Contoh", PRIMARY),
         "N-Queens, Sudoku, perm", "LCS, knapsack, fib"],
    ]
    styled_table(slide, ["Aspek", "Backtracking", "Dynamic Programming"],
                 rows, 0.5, 1.2, [3.0, 4.6, 4.6], row_h=0.55,
                 header_colors=[PRIMARY, AMBER, EMERALD])

    callout(slide,
            "Hybrid: BT + memoization = top-down DP. Cocok jika ada overlap.",
            0.5, 6.4, 12.3, 0.6, color=VIOLET, icon="🔀")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Backtracking Pitfalls")
    mistakes = [
        ("1. Lupa UNDO state",
         "Kamu push tapi tidak pop.\nResult akan korup setelah loop.",
         ROSE),
        ("2. Salah start index",
         "Boleh ulang → pakai i\nTidak boleh → pakai i+1",
         ROSE),
        ("3. used[] tidak di-reset",
         "Antar test case, used[] harus\ndi-reset → fill(used, false)",
         AMBER),
        ("4. N-Queens diagonal salah",
         "diag1: r-c+n (anti-diagonal)\ndiag2: r+c (main diagonal).",
         AMBER),
        ("5. Pruning telat",
         "Cek validity SEBELUM rekursi.\nKalau di awal fungsi → kalkulasi sia-sia.",
         AMBER),
        ("6. Stack overflow",
         "Backtracking depth bisa O(n).\nUntuk n>10⁴ → konversi iteratif.",
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
    slide_header(slide, "Cheatsheet — Backtracking Templates")

    cheat_left = """// === PERMUTATION ===
vector<int> perm;
vector<bool> used(n+1, 0);
void perms() {
    if (perm.size() == n) { print(); return; }
    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        used[i] = 1;
        perm.push_back(i);
        perms();
        perm.pop_back();
        used[i] = 0;
    }
}

// === SUBSET ===
void subsets(int start) {
    print(cur);
    for (int i = start; i <= n; i++) {
        cur.push_back(i);
        subsets(i + 1);
        cur.pop_back();
    }
}"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)

    cheat_right = """// === N-QUEENS ===
bool col[N], d1[2*N], d2[2*N];
void queens(int r) {
    if (r == n) { ans++; return; }
    for (int c = 0; c < n; c++) {
        if (col[c]||d1[r-c+n]||d2[r+c]) continue;
        col[c]=d1[r-c+n]=d2[r+c]=1;
        queens(r+1);
        col[c]=d1[r-c+n]=d2[r+c]=0;
    }
}

// === COMBINATION SUM ===
sort(cands.begin(), cands.end());
void cs(int s, int t) {
    if (t == 0) { record(); return; }
    for (int i = s; i < n; i++) {
        if (cands[i] > t) break;
        cur.push_back(cands[i]);
        cs(i, t - cands[i]);
        cur.pop_back();
    }
}"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 12, "Backtracking: Choose-Explore-Undo dengan pruning cerdas", [
        (PRIMARY, "Paradigma", "3 langkah: Choose, Explore, Undo. Setiap modify state WAJIB di-undo."),
        (EMERALD, "Permutation & Subset", "used[] untuk perm O(n!). start untuk subset O(2ⁿ). Hindari duplicate."),
        (AMBER, "N-Queens & Combination", "Constraint check 3 array. Sort + break untuk pruning combination sum."),
        (VIOLET, "Word Search", "DFS di grid. Mark dengan '#', restore dengan tmp. Hemat memori."),
        (ROSE, "BT vs DP", "BT: semua solusi, N≤20. DP: 1 angka optimal, N besar. Hybrid: top-down DP."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_12_Presentation.pptx"))


if __name__ == "__main__":
    main()
