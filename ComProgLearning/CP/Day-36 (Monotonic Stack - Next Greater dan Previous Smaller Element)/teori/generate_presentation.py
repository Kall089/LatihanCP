#!/usr/bin/env python3
"""Day 36 — Stack Applications: brackets, NGE, histogram, rain water.
Rich advanced visuals with proper diagrams for each subtopic."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def draw_stack(slide, items, x, base_y, w=1.3, h=0.4,
               highlights=None, label="stack",
               growth="up", show_labels=True):
    """Gambar stack dengan bottom di base_y. growth='up' artinya
    push menambah ke atas (top di paling atas)."""
    if highlights is None:
        highlights = {}
    n = len(items)
    # Container outline
    container_h = (n + 1) * h + 0.1
    rect(slide, x - 0.06, base_y - container_h + h + 0.08,
         0.05, container_h - 0.05, BORDER)  # left wall
    rect(slide, x + w + 0.01, base_y - container_h + h + 0.08,
         0.05, container_h - 0.05, BORDER)  # right wall
    rect(slide, x - 0.06, base_y + h + 0.08,
         w + 0.12, 0.05, BORDER)  # bottom
    # Items
    for i, val in enumerate(items):
        col = highlights.get(i, BG_CARD_2)
        cy = base_y - i * h
        rounded_rect(slide, x, cy, w, h - 0.04, col,
                     line_color=BORDER, line_w=0.5)
        text_color = BG_DEEP if i in highlights else WHITE
        tb(slide, str(val), x, cy + 0.04, w, h - 0.12,
           size=12, bold=True, color=text_color, align=PP_ALIGN.CENTER,
           font_name="Menlo")
    # TOP label arrow on rightmost top item
    if show_labels and items:
        top_y = base_y - (n - 1) * h
        tb(slide, "← TOP", x + w + 0.15, top_y, 0.85, h - 0.1,
           size=10, bold=True, color=AMBER)
    if show_labels:
        tb(slide, label, x, base_y + h + 0.15,
           w, 0.3, size=10, bold=True, color=SLATE,
           align=PP_ALIGN.CENTER)


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["[", "{", "(", ")"]
        cols = [PRIMARY, EMERALD, AMBER, ROSE]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.5 + i * 1.4
            rounded_rect(slide, cx, 5.6, 1.3, 0.5, col)
            tb(slide, lbl, cx, 5.65, 1.3, 0.45,
               size=18, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 36, "Stack Applications",
                ["Bracket · NGE · Histogram · Rain Water",
                 "5 pola O(n) yang elegan dengan stack"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 36", [
        ("01", "Balanced\nBrackets", PRIMARY,
         ["Match (), [], {}", "Stack push/pop", "Cek empty di akhir", "Simple O(n)"]),
        ("02", "NGE & PSE\nMonotonic Stack", EMERALD,
         ["Next Greater", "Prev Smaller", "Mengapa O(n)?", "Index vs value"]),
        ("03", "Histogram\nRectangle", AMBER,
         ["Largest rect", "Width = i-top-1", "Stock span", "Sentinel trick"]),
        ("04", "Trapping\nRain Water", VIOLET,
         ["Stack approach", "Two pointers alt", "Visualisasi kontainer", "Tips & pitfall"]),
    ])

    # ── Section 01: BRACKETS ────────────────────────────────────
    section_divider(prs, "01", "Balanced Brackets",
                    "Validasi nesting () [] {} dengan stack — O(n)")

    # Slide: Konsep dasar stack
    slide = new_slide(prs)
    slide_header(slide, "Stack — LIFO Recap & Visualisasi",
                 "Last-In-First-Out: yang masuk terakhir, keluar pertama")

    # Left: Stack operations
    code = """#include <stack>

stack<int> st;
st.push(x);    // O(1) — tambah ke atas
st.pop();      // O(1) — hapus paling atas
st.top();      // O(1) — peek paling atas
st.empty();    // bool kosong
st.size();     // jumlah elemen

// Pakai vector sebagai stack
vector<int> v;
v.push_back(x);
v.pop_back();
int top = v.back();"""
    code_box(slide, code, 0.5, 1.1, 5.7, 4.8, font_size=11, accent=PRIMARY)

    insight_card(slide, "Kapan pakai Stack?",
                 ["Matching pasangan (bracket)",
                  "Track 'previous' di array",
                  "DFS, expression eval",
                  "Reverse, undo operations"],
                 0.5, 6.05, 5.7, 1.1)

    # Right: Visual stack push/pop sequence
    tb(slide, "🎬 Visualisasi push/pop",
       6.5, 1.1, 6.4, 0.4, size=13, bold=True, color=AMBER)

    # Show 4 stages of stack operations
    stages = [
        ("push 3",  [3],          {0: PRIMARY},           6.7, 1.7),
        ("push 7",  [3, 7],       {0: SLATE, 1: PRIMARY}, 8.3, 1.7),
        ("push 1",  [3, 7, 1],    {0: SLATE, 1: SLATE, 2: PRIMARY}, 9.9, 1.7),
        ("pop → 1", [3, 7],       {0: SLATE, 1: AMBER},   11.5, 1.7),
    ]
    for label, items, hl, sx, sy in stages:
        # Container background
        rounded_rect(slide, sx - 0.08, sy + 0.15, 1.0, 1.85, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        # Items stacked from bottom
        for i, val in enumerate(items):
            col = hl.get(i, BG_CARD_2)
            cy = sy + 1.75 - i * 0.45
            rounded_rect(slide, sx, cy, 0.85, 0.4, col,
                         line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if i in hl else WHITE
            tb(slide, str(val), sx, cy + 0.05, 0.85, 0.32,
               size=11, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")
        # Bottom line
        rect(slide, sx - 0.08, sy + 2.0, 1.0, 0.04, BORDER)
        # Label
        tb(slide, label, sx - 0.1, sy + 2.1, 1.05, 0.3,
           size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # Arrows between stages
    for i in range(3):
        x1 = 6.7 + i * 1.6 + 1.0
        y_mid = 2.7
        arrow(slide, x1 + 0.05, y_mid, x1 + 0.5, y_mid,
              color=EMERALD, thickness=1.5)

    callout(slide, "Operasi stack semua O(1) — sangat cepat",
            6.5, 4.65, 6.4, 0.6, color=EMERALD, icon="⚡")

    # Right bottom: warning
    rounded_rect(slide, 6.5, 5.4, 6.4, 1.7, BG_CARD,
                 line_color=ROSE, line_w=1.0)
    rect(slide, 6.5, 5.4, 6.4, 0.06, ROSE)
    tb(slide, "⚠ Hati-hati di empty stack",
       6.7, 5.5, 6.0, 0.32, size=12, bold=True, color=ROSE)
    code_warn = """// SALAH — st.top() pada empty
if (st.empty()) return false;  // ✓ cek dulu
int t = st.top(); st.pop();"""
    plain_code_box(slide, code_warn, 6.7, 5.85, 6.0, 1.2,
                   font_size=10, accent=ROSE)

    # Slide: Balanced brackets algorithm
    slide = new_slide(prs)
    slide_header(slide, "Balanced Brackets — Algoritma & Visualisasi",
                 "Stack memetakan struktur nested secara natural")

    code = """bool isBalanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c=='('||c=='['||c=='{') {
            st.push(c);   // OPEN → push
        } else {          // CLOSE
            if (st.empty()) return false;
            char t = st.top(); st.pop();
            if ((c==')' && t!='(') ||
                (c==']' && t!='[') ||
                (c=='}' && t!='{')) return false;
        }
    }
    return st.empty();   // semua tertutup
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.0, font_size=11, accent=PRIMARY)

    # Right: trace step-by-step with stack visual
    tb(slide, "🎬 Trace s = '({[]})'",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    # Each step shows stack visually
    bracket_steps = [
        ("(",   "push (",   ["("],                     PRIMARY),
        ("{",   "push {",   ["(", "{"],                PRIMARY),
        ("[",   "push [",   ["(", "{", "["],           PRIMARY),
        ("]",   "match [",  ["(", "{"],                EMERALD),
        ("}",   "match {",  ["("],                     EMERALD),
        (")",   "match (",  [],                        EMERALD),
        ("EOF", "empty? ✓", [],                        AMBER),
    ]
    for i, (ch, action, st_state, col) in enumerate(bracket_steps):
        ty = 1.7 + i * 0.62
        rounded_rect(slide, 7.2, ty, 5.7, 0.55, BG_CARD,
                     line_color=col, line_w=0.5)
        # Char
        rounded_rect(slide, 7.3, ty + 0.07, 0.5, 0.4, col)
        tb(slide, ch, 7.3, ty + 0.13, 0.5, 0.3,
           size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
           font_name="Menlo")
        # Action
        tb(slide, action, 7.95, ty + 0.13, 1.7, 0.32,
           size=10, color=SLATE, italic=True)
        # Stack state (mini)
        st_str = "[" + ",".join(st_state) + "]" if st_state else "[ ]"
        rounded_rect(slide, 9.7, ty + 0.07, 3.1, 0.4, BG_CODE,
                     line_color=col, line_w=0.5)
        tb(slide, st_str, 9.7, ty + 0.13, 3.1, 0.3,
           size=11, bold=True, color=col, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    callout(slide, "BALANCED ✓ — semua bracket cocok dan stack kosong di akhir",
            0.5, 6.4, 6.5, 0.6, color=EMERALD, icon="🎯")

    # ── Section 02: NGE / Monotonic Stack ──────────────────────
    section_divider(prs, "02", "Next Greater Element & Monotonic Stack",
                    "Mengapa O(n)? Setiap elemen push/pop maksimal 1 kali",
                    color=EMERALD)

    # Slide: Konsep monotonic stack
    slide = new_slide(prs)
    slide_header(slide, "Monotonic Stack — Konsep Inti",
                 "Stack yang nilainya selalu monoton (naik atau turun)")

    # Left: explanation
    info_card(slide, "Monotonic Decreasing (untuk NGE)",
              [("• Top = nilai terkecil saat ini", SILVER),
               ("• Pop semua yang ≤ nilai baru", SILVER),
               ("• Setelah pop, push nilai baru", SILVER),
               ("→ stack tetap monoton turun", AMBER)],
              0.5, 1.1, 6.0, 2.5, accent=EMERALD)

    info_card(slide, "Monotonic Increasing (untuk NSE)",
              [("• Top = nilai terbesar saat ini", SILVER),
               ("• Pop semua yang ≥ nilai baru", SILVER),
               ("• Setelah pop, push nilai baru", SILVER),
               ("→ stack tetap monoton naik", AMBER)],
              0.5, 3.75, 6.0, 2.5, accent=PRIMARY)

    insight_card(slide, "Mengapa O(n)?",
                 ["Setiap elemen masuk stack 1×",
                  "Setiap elemen keluar stack 1×",
                  "→ Total: 2n operasi → O(n)"],
                 0.5, 6.4, 6.0, 0.85)

    # Right: Visual of monotonic stack growing
    tb(slide, "🎯 Monotonic Decreasing — A = [4, 5, 2, 25]",
       6.7, 1.1, 6.3, 0.4, size=12, bold=True, color=AMBER)

    # Show stack at 4 stages
    mono_stages = [
        ("i=0: push 4",  [4],             {0: PRIMARY}),
        ("i=1: pop 4, push 5", [5],       {0: EMERALD}),
        ("i=2: push 2",  [5, 2],          {0: SLATE, 1: PRIMARY}),
        ("i=3: pop 2,5, push 25", [25],   {0: EMERALD}),
    ]
    for i, (label, items, hl) in enumerate(mono_stages):
        sx = 6.7 + (i % 2) * 3.3
        sy_top = 1.7 + (i // 2) * 2.55
        # Container background
        rounded_rect(slide, sx, sy_top, 3.0, 2.2, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        tb(slide, label, sx, sy_top + 0.05, 3.0, 0.3,
           size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
        # Stack items
        base_x = sx + 1.0
        base_y = sy_top + 1.7
        for k, val in enumerate(items):
            col = hl.get(k, BG_CARD_2)
            cy = base_y - k * 0.38
            rounded_rect(slide, base_x, cy, 1.0, 0.34, col,
                         line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if k in hl else WHITE
            tb(slide, str(val), base_x, cy + 0.04, 1.0, 0.28,
               size=11, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")
        # Container bottom
        rect(slide, base_x - 0.05, base_y + 0.34, 1.1, 0.04, BORDER)

    # Slide: NGE algorithm with detailed visualization
    slide = new_slide(prs)
    slide_header(slide, "NGE — Next Greater Element O(n)")

    code = """vector<int> nge(vector<int>& A) {
    int n = A.size();
    vector<int> ans(n, -1);
    stack<int> st;             // simpan INDEX (mono dec)

    for (int i = 0; i < n; i++) {
        // Saat ada nilai di stack < A[i],
        // berarti A[i] adalah NGE-nya
        while (!st.empty() && A[st.top()] < A[i]) {
            ans[st.top()] = A[i];
            st.pop();
        }
        st.push(i);
    }
    return ans;
}"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.8, font_size=11, accent=EMERALD)

    # Right: full trace with arrays
    tb(slide, "🎯 A = [4, 5, 2, 25, 21]   ans?",
       7.0, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)
    array_cells(slide, [4, 5, 2, 25, 21], 7.0, 1.7,
                cell_w=0.85, cell_h=0.6,
                highlights={0: BG_CARD_2, 1: BG_CARD_2, 2: BG_CARD_2,
                            3: BG_CARD_2, 4: BG_CARD_2})

    # Trace table
    rows = [
        ["0", "4",  "[]",      "push 0",      "[0]"],
        ["1", "5",  "[0]",     "5>4: ans[0]=5", "[1]"],
        ["2", "2",  "[1]",     "2<5: push 2", "[1,2]"],
        ["3", "25", "[1,2]",   "ans[2]=25,ans[1]=25", "[3]"],
        ["4", "21", "[3]",     "21<25: push", "[3,4]"],
    ]
    styled_table(slide, ["i", "A[i]", "stack(in)", "aksi", "stack(out)"],
                 rows, 7.0, 2.4, [0.5, 0.7, 1.1, 2.4, 1.3], row_h=0.42,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET, ROSE],
                 body_size=9.5, header_size=9.5)

    # Final answer with arrows
    tb(slide, "Result: ans = [5, 25, 25, -1, -1]",
       7.0, 5.0, 6.0, 0.35, size=12, bold=True, color=EMERALD,
       font_name="Menlo")
    array_cells(slide, [5, 25, 25, -1, -1], 7.0, 5.45,
                cell_w=0.85, cell_h=0.6,
                highlights={i: EMERALD for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)})

    callout(slide, "Setiap elemen push 1× & pop 1× → total O(n)",
            0.5, 6.05, 6.4, 0.6, color=EMERALD, icon="⚡")

    # Slide: 4 patterns of monotonic stack
    slide = new_slide(prs)
    slide_header(slide, "4 Pola Monotonic Stack — Tabel Lengkap")
    rows = [
        [("NGE", PRIMARY), "Next Greater", "→ kanan", "while A[top] < cur", "monoton turun"],
        [("NSE", EMERALD), "Next Smaller", "→ kanan", "while A[top] > cur", "monoton naik"],
        [("PGE", AMBER),   "Prev Greater", "← kiri",  "while A[top] ≤ cur", "monoton turun"],
        [("PSE", VIOLET),  "Prev Smaller", "← kiri",  "while A[top] ≥ cur", "monoton naik"],
    ]
    styled_table(slide, ["Pola", "Makna", "Arah", "Pop Kondisi", "Stack Type"],
                 rows, 0.5, 1.2, [1.4, 2.6, 1.5, 4.0, 2.8], row_h=0.55,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET, ROSE])

    # PSE example with visualization
    tb(slide, "🎯 Contoh PSE (Previous Smaller) — A = [2, 5, 3, 7, 8]",
       0.5, 4.2, 12.4, 0.4, size=12, bold=True, color=PRIMARY)

    # 2 arrays side by side
    tb(slide, "Input:", 0.5, 4.7, 1.0, 0.3, size=11, color=SLATE)
    array_cells(slide, [2, 5, 3, 7, 8], 1.5, 4.7,
                cell_w=0.65, cell_h=0.5,
                highlights={i: BG_CARD_2 for i in range(5)})
    tb(slide, "PSE:", 5.5, 4.7, 1.0, 0.3, size=11, color=SLATE)
    array_cells(slide, [-1, 2, 2, 3, 7], 6.5, 4.7,
                cell_w=0.65, cell_h=0.5,
                highlights={i: PRIMARY for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)})

    # Visual arrow showing relations
    tb(slide, "Penjelasan:", 0.5, 5.55, 12.0, 0.3,
       size=11, bold=True, color=AMBER)
    rules = [
        "A[0]=2: tidak ada elemen di kiri → -1",
        "A[1]=5: prev smaller = 2 (index 0)",
        "A[2]=3: prev smaller = 2 (index 0)  ← bukan 5!",
        "A[3]=7: prev smaller = 3 (index 2)",
        "A[4]=8: prev smaller = 7 (index 3)",
    ]
    for i, r in enumerate(rules):
        cn = i % 2
        rn = i // 2
        tb(slide, "▸ " + r, 0.7 + cn * 6.0, 5.95 + rn * 0.32,
           5.8, 0.3, size=10.5, color=SILVER)

    # ── Section 03: Histogram ──────────────────────────────────
    section_divider(prs, "03", "Largest Rectangle in Histogram",
                    "Pola monotonic stack + sentinel — O(n) elegan",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Histogram — Visualisasi Largest Rectangle",
                 "Tujuan: cari rectangle terbesar di antara bar")

    # Big visual of histogram
    tb(slide, "📊 h = [2, 1, 5, 6, 2, 3]",
       0.5, 1.1, 12.4, 0.4, size=14, bold=True, color=AMBER,
       align=PP_ALIGN.CENTER, font_name="Menlo")

    heights = [2, 1, 5, 6, 2, 3]
    bar_w = 1.15
    base_y = 4.5
    base_x = 1.0
    max_h = 6
    for i, h in enumerate(heights):
        bx = base_x + i * (bar_w + 0.1)
        bh = h * 0.45
        # Highlight the best rectangle (index 2-3, height 5)
        if i in (2, 3):
            col = AMBER
            tc = BG_DEEP
        else:
            col = BG_CARD_2
            tc = WHITE
        rect(slide, bx, base_y - bh, bar_w, bh, col,
             line_color=BORDER, line_w=0.75)
        tb(slide, str(h), bx, base_y - bh + 0.05, bar_w, 0.4,
           size=14, bold=True, color=tc, align=PP_ALIGN.CENTER)
        tb(slide, f"i={i}", bx, base_y + 0.08, bar_w, 0.3,
           size=10, color=MUTED, align=PP_ALIGN.CENTER)

    # Best rectangle outline overlay
    bx_best = base_x + 2 * (bar_w + 0.1)
    bw_best = 2 * (bar_w + 0.1) - 0.1
    bh_best = 5 * 0.45
    # Outline highlight
    rect(slide, bx_best - 0.04, base_y - bh_best - 0.04,
         bw_best + 0.08, 0.04, EMERALD)  # top
    rect(slide, bx_best - 0.04, base_y - 0.04,
         bw_best + 0.08, 0.04, EMERALD)  # bottom
    rect(slide, bx_best - 0.04, base_y - bh_best - 0.04,
         0.04, bh_best + 0.08, EMERALD)  # left
    rect(slide, bx_best + bw_best, base_y - bh_best - 0.04,
         0.04, bh_best + 0.08, EMERALD)  # right

    # Floor line
    rect(slide, base_x - 0.1, base_y, 12.0, 0.04, SLATE)

    # Result callout
    rounded_rect(slide, 0.5, 5.0, 12.4, 1.0, BG_CARD,
                 line_color=EMERALD, line_w=1.2)
    rect(slide, 0.5, 5.0, 12.4, 0.06, EMERALD)
    tb(slide, "🎯 Largest Rectangle = H × W = 5 × 2 = 10",
       0.5, 5.15, 12.4, 0.4, size=18, bold=True, color=EMERALD,
       align=PP_ALIGN.CENTER)
    tb(slide, "Bar tinggi 5 (i=2) dan tinggi 6 (i=3) dapat membentuk rectangle 5×2",
       0.5, 5.6, 12.4, 0.35, size=12, color=SLATE, italic=True,
       align=PP_ALIGN.CENTER)

    # Naive vs optimal
    metric_card(slide, "Naive O(n²)", "TLE n>10⁴", 0.5, 6.2, 4.0, 1.1, accent=ROSE)
    metric_card(slide, "Stack O(n)", "Aman 10⁶", 4.7, 6.2, 4.0, 1.1, accent=EMERALD)
    metric_card(slide, "Memori", "O(n) stack", 8.9, 6.2, 4.0, 1.1, accent=PRIMARY)

    # Slide: Algorithm with width formula visualization
    slide = new_slide(prs)
    slide_header(slide, "Histogram — Algoritma & Width Formula")

    code = """ll largestRect(vector<int>& h) {
    int n = h.size();
    stack<int> st;
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        int cur = (i == n ? 0 : h[i]);  // SENTINEL!
        while (!st.empty() && h[st.top()] > cur) {
            ll H = h[st.top()]; st.pop();
            ll W = st.empty() ? i : i - st.top() - 1;
            ans = max(ans, H * W);
        }
        st.push(i);
    }
    return ans;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.7, font_size=11, accent=AMBER)

    # Right: width formula visualization
    tb(slide, "🔑 Width Formula Visualization",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)

    # Mini histogram with width labeled
    mini_h = [2, 5, 5, 5, 2]
    mini_bw = 0.55
    mini_x = 7.3
    mini_y = 4.0
    for i, h in enumerate(mini_h):
        bx = mini_x + i * (mini_bw + 0.05)
        bh = h * 0.32
        col = AMBER if i in (1, 2, 3) else BG_CARD_2
        tc = BG_DEEP if i in (1, 2, 3) else WHITE
        rect(slide, bx, mini_y - bh, mini_bw, bh, col,
             line_color=BORDER, line_w=0.5)
        tb(slide, str(h), bx, mini_y - bh + 0.05, mini_bw, 0.3,
           size=11, bold=True, color=tc, align=PP_ALIGN.CENTER)
        tb(slide, f"i={i}", bx, mini_y + 0.08, mini_bw, 0.25,
           size=8, color=MUTED, align=PP_ALIGN.CENTER)

    rect(slide, mini_x, mini_y, 5 * (mini_bw + 0.05), 0.04, SLATE)

    # Width arrow
    arrow(slide, mini_x + 0.55 + 0.05, mini_y + 0.55,
          mini_x + 4 * 0.6 - 0.05, mini_y + 0.55,
          color=EMERALD, thickness=2.0)
    arrow(slide, mini_x + 4 * 0.6 - 0.05, mini_y + 0.55,
          mini_x + 0.55 + 0.05, mini_y + 0.55,
          color=EMERALD, thickness=2.0)
    tb(slide, "W = 3", mini_x + 1.4, mini_y + 0.7, 1.5, 0.3,
       size=11, bold=True, color=EMERALD)

    # Formula explanation
    rounded_rect(slide, 7.2, 4.5, 5.7, 1.5, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 7.2, 4.5, 5.7, 0.06, PRIMARY)
    tb(slide, "📐 Rumus W (saat pop top)",
       7.35, 4.6, 5.5, 0.3, size=11, bold=True, color=PRIMARY)
    tb(slide, "• Stack kosong → W = i",
       7.35, 4.95, 5.5, 0.3, size=10, color=SILVER, font_name="Menlo")
    tb(slide, "• Stack ada → W = i - top - 1",
       7.35, 5.27, 5.5, 0.3, size=10, color=AMBER, font_name="Menlo")
    tb(slide, "• 'i' = posisi sekarang",
       7.35, 5.6, 5.5, 0.3, size=10, color=SLATE, font_name="Menlo")

    # Sentinel trick
    rounded_rect(slide, 7.2, 6.1, 5.7, 1.0, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 7.2, 6.1, 5.7, 0.05, EMERALD)
    tb(slide, "💡 Sentinel Trick",
       7.35, 6.2, 5.5, 0.3, size=11, bold=True, color=EMERALD)
    tb(slide, "Loop sampai i ≤ n. Saat i=n, anggap h=0\n"
              "→ flush semua sisa stack di akhir.",
       7.35, 6.5, 5.5, 0.65, size=10, color=SILVER)

    # Bottom warning
    callout(slide,
            "Width = i - st.top() - 1 (BUKAN i - st.top())",
            0.5, 6.2, 6.5, 0.7, color=ROSE, icon="⚠")

    # ── Section 04: Rain Water ─────────────────────────────────
    section_divider(prs, "04", "Trapping Rain Water",
                    "Dua pendekatan: stack (O(n)/O(n)) atau two pointers (O(n)/O(1))",
                    color=VIOLET)

    # Slide: Konsep & visual rain water
    slide = new_slide(prs)
    slide_header(slide, "Trapping Rain Water — Visualisasi",
                 "Hitung total air yang terjebak di antara bar")

    # Big visual of rain water
    heights = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    n_bars = len(heights)
    L_max = [0] * n_bars
    R_max = [0] * n_bars
    L_max[0] = heights[0]
    for i in range(1, n_bars):
        L_max[i] = max(L_max[i - 1], heights[i])
    R_max[-1] = heights[-1]
    for i in range(n_bars - 2, -1, -1):
        R_max[i] = max(R_max[i + 1], heights[i])
    water = [max(0, min(L_max[i], R_max[i]) - heights[i]) for i in range(n_bars)]

    bar_w = 0.85
    base_y = 4.4
    base_x = 0.7
    bar_h_unit = 0.6
    total_water = sum(water)

    for i, h in enumerate(heights):
        bx = base_x + i * (bar_w + 0.04)
        bh = h * bar_h_unit
        # Bar
        rect(slide, bx, base_y - bh, bar_w, bh, SLATE,
             line_color=BORDER, line_w=0.5)
        # Water on top
        if water[i] > 0:
            wh = water[i] * bar_h_unit
            rect(slide, bx, base_y - bh - wh, bar_w, wh, CYAN)
        # Index
        tb(slide, str(i), bx, base_y + 0.08, bar_w, 0.25,
           size=9, color=MUTED, align=PP_ALIGN.CENTER)
        # Height label inside or above
        if h > 0:
            tb(slide, str(h), bx, base_y - bh + 0.05, bar_w, 0.3,
               size=11, bold=True, color=WHITE, align=PP_ALIGN.CENTER)

    # Floor line
    rect(slide, base_x, base_y, n_bars * (bar_w + 0.04), 0.04, BORDER)

    # Total water
    rounded_rect(slide, 0.5, 5.0, 12.4, 0.85, BG_CARD,
                 line_color=CYAN, line_w=1.5)
    rect(slide, 0.5, 5.0, 12.4, 0.06, CYAN)
    tb(slide, f"💧 Total air terjebak = {total_water} unit",
       0.5, 5.15, 12.4, 0.45, size=18, bold=True, color=CYAN,
       align=PP_ALIGN.CENTER)
    tb(slide, "Air[i] = min(L_max[i], R_max[i]) - h[i]",
       0.5, 5.55, 12.4, 0.3, size=11, color=SLATE, italic=True,
       align=PP_ALIGN.CENTER, font_name="Menlo")

    # Comparison
    rounded_rect(slide, 0.5, 6.05, 6.0, 1.2, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 6.05, 6.0, 0.06, PRIMARY)
    tb(slide, "Stack Approach", 0.7, 6.15, 5.5, 0.32,
       size=12, bold=True, color=PRIMARY)
    tb(slide, "• Time: O(n)\n• Space: O(n) untuk stack",
       0.7, 6.45, 5.5, 0.7, size=11, color=SILVER)

    rounded_rect(slide, 6.85, 6.05, 6.05, 1.2, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 6.85, 6.05, 6.05, 0.06, EMERALD)
    tb(slide, "Two Pointers Approach", 7.05, 6.15, 5.5, 0.32,
       size=12, bold=True, color=EMERALD)
    tb(slide, "• Time: O(n)\n• Space: O(1) — pakai ini!",
       7.05, 6.45, 5.5, 0.7, size=11, color=SILVER)

    # Slide: Two approaches side by side
    slide = new_slide(prs)
    slide_header(slide, "Rain Water — 2 Algoritma Side by Side")

    code_stack = """// === STACK APPROACH ===
ll trap(vector<int>& h) {
    stack<int> st;
    ll ans = 0;
    for (int i = 0; i < (int)h.size(); i++) {
        while (!st.empty() && h[st.top()] < h[i]) {
            int bot = h[st.top()]; st.pop();
            if (st.empty()) break;
            int W = i - st.top() - 1;
            int H = min(h[st.top()], h[i]) - bot;
            ans += (ll)W * H;
        }
        st.push(i);
    }
    return ans;
}"""
    code_box(slide, code_stack, 0.5, 1.1, 6.4, 5.5, font_size=10.5, accent=PRIMARY)

    code_2p = """// === TWO POINTERS — RECOMMENDED ===
ll trap2(vector<int>& h) {
    int L = 0, R = h.size() - 1;
    int lmax = 0, rmax = 0;
    ll ans = 0;
    while (L < R) {
        if (h[L] < h[R]) {
            lmax = max(lmax, h[L]);
            ans += lmax - h[L];
            L++;
        } else {
            rmax = max(rmax, h[R]);
            ans += rmax - h[R];
            R--;
        }
    }
    return ans;
}"""
    code_box(slide, code_2p, 7.0, 1.1, 6.0, 5.5, font_size=10.5, accent=EMERALD)

    # Bottom: VS comparison
    rounded_rect(slide, 0.5, 6.75, 12.4, 0.5, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    tb(slide, "🎯 Two pointers menang di space O(1) — selalu pakai jika bisa",
       0.5, 6.85, 12.4, 0.35, size=12, bold=True, color=AMBER,
       align=PP_ALIGN.CENTER)

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Stack Pitfalls")
    mistakes = [
        ("1. st.top() pada empty stack",
         "SIGSEGV / undefined!\nSelalu cek if (!st.empty()) dulu.",
         ROSE),
        ("2. Histogram width salah",
         "W = i - st.top() - 1.\nBukan i - st.top()!",
         ROSE),
        ("3. NGE: push setelah while",
         "Push index SETELAH popping.\nDi luar while loop, bukan dalam.",
         AMBER),
        ("4. Balanced lupa cek di akhir",
         "Tidak hanya saat traversal.\nReturn st.empty() di akhir.",
         AMBER),
        ("5. Tipe data overflow",
         "Histogram H*W bisa overflow int.\nPakai long long di kalikan.",
         AMBER),
        ("6. Lupa sentinel di histogram",
         "Loop hanya sampai i<n → sisa\nelemen di stack tidak diproses!",
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
    slide_header(slide, "Cheatsheet — Stack Templates")
    cheat_left = """// === BALANCED ===
stack<char> st;
for (char c : s) {
    if (open(c)) st.push(c);
    else {
        if (st.empty()) return false;
        if (!match(st.top(), c)) return false;
        st.pop();
    }
}
return st.empty();

// === NGE (Next Greater) ===
stack<int> st;
vector<int> nge(n, -1);
for (int i = 0; i < n; i++) {
    while (!st.empty() && A[st.top()] < A[i]) {
        nge[st.top()] = A[i];
        st.pop();
    }
    st.push(i);
}"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)

    cheat_right = """// === HISTOGRAM ===
stack<int> st;
ll ans = 0;
for (int i = 0; i <= n; i++) {  // sentinel
    int cur = (i == n ? 0 : h[i]);
    while (!st.empty() && h[st.top()] > cur) {
        ll H = h[st.top()]; st.pop();
        ll W = st.empty() ? i : i - st.top() - 1;
        ans = max(ans, H * W);
    }
    st.push(i);
}

// === RAIN WATER (2 PTR) ===
int L = 0, R = n-1, lmax = 0, rmax = 0;
ll ans = 0;
while (L < R) {
    if (h[L] < h[R]) {
        lmax = max(lmax, h[L]);
        ans += lmax - h[L]; L++;
    } else { /* mirror untuk R */ }
}"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 36, "Stack Applications — pola O(n) yang elegan", [
        (PRIMARY, "Brackets", "LIFO matching. Stack untuk track open. Cek empty di akhir."),
        (EMERALD, "Monotonic Stack", "NGE/PSE O(n) karena setiap elemen push/pop max 1×. Simpan index."),
        (AMBER, "Histogram", "W = i - top - 1. Sentinel (h=0) di akhir untuk flush sisa stack."),
        (VIOLET, "Rain Water", "Stack atau 2 pointer. 2 pointer lebih hemat memori O(1)."),
        (ROSE, "Pitfall", "top() pada empty → UB. Histogram width formula. Overflow di H*W."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_36_Presentation.pptx"))


if __name__ == "__main__":
    main()
