#!/usr/bin/env python3
"""Day 19 — Two Pointers: opposite, same direction, merge."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["L →", "← R", "merge"]
        cols = [PRIMARY, AMBER, EMERALD]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.5 + i * 1.85
            rounded_rect(slide, cx, 5.6, 1.7, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.7, 0.4,
               size=12, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    cover_slide(prs, 19, "Two Pointers",
                ["Opposite · Same direction · Merge",
                 "O(n) elegan untuk array & string"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 19", [
        ("01", "Konsep\nTwo Pointers", PRIMARY,
         ["Intuisi & 3 pola", "Kapan O(n²) → O(n)", "Pre-conditions", "Pointer L, R"]),
        ("02", "Opposite\nDirection", EMERALD,
         ["Two Sum sorted", "Palindrome check", "Container water", "Sorted required"]),
        ("03", "Same\nDirection", AMBER,
         ["Slow + fast", "Remove dup in-place", "Substring problem", "Sliding window"]),
        ("04", "Merge &\n3-Pointers", VIOLET,
         ["Merge 2 sorted", "Three Sum", "Dutch flag 3-way", "Tips & pitfall"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Konsep Two Pointers",
                    "Hindari O(n²) dengan dua index yang bergerak cerdas")

    slide = new_slide(prs)
    slide_header(slide, "Apa itu Two Pointers?",
                 "2 pointer bergerak menuju target atau pola tertentu")

    # Left: explanation
    info_card(slide, "Konsep Inti", [
        "• 2 indeks (L dan R) menelusuri",
        "• Hindari nested loop O(n²)",
        "• Gerakkan pointer berdasar kondisi",
        "• Total kerja O(n) — setiap pointer",
        "  bergerak max n kali",
    ], 0.5, 1.1, 5.7, 3.0, accent=PRIMARY)

    info_card(slide, "3 Pola Utama", [
        ("• Opposite Direction (L→ ←R)", PRIMARY),
        ("• Same Direction (slow + fast)", EMERALD),
        ("• Merge (i di A, j di B)", AMBER),
    ], 0.5, 4.25, 5.7, 2.0, accent=AMBER)

    # Right: visual
    tb(slide, "🎯 Visual: Two Sum Sorted",
       6.4, 1.1, 6.5, 0.4, size=13, bold=True, color=AMBER)
    tb(slide, "Cari A[i]+A[j] = 10",
       6.4, 1.55, 6.5, 0.3, size=11, italic=True, color=SLATE)

    array_cells(slide, [1, 3, 4, 6, 8, 9], 6.4, 2.0,
                cell_w=0.85, cell_h=0.6,
                highlights={0: PRIMARY, 5: AMBER},
                colors_map={0: BG_DEEP, 5: BG_DEEP})

    # Pointers
    tb(slide, "↑", 6.4 + 0.0 * 0.9, 2.7, 0.85, 0.3,
       size=18, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "L", 6.4 + 0.0 * 0.9, 3.0, 0.85, 0.3,
       size=12, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "↑", 6.4 + 5 * 0.9, 2.7, 0.85, 0.3,
       size=18, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
    tb(slide, "R", 6.4 + 5 * 0.9, 3.0, 0.85, 0.3,
       size=12, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # Trace
    tb(slide, "🎬 Trace:", 6.4, 3.5, 6.5, 0.3, size=12, bold=True, color=EMERALD)
    traces = [
        ("L=0,R=5", "1+9=10", "FOUND!", EMERALD),
    ]
    for i, (state, sum_str, action, col) in enumerate(traces):
        ty = 3.85 + i * 0.55
        rounded_rect(slide, 6.4, ty, 6.5, 0.5, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, state, 6.6, ty + 0.05, 1.8, 0.4,
           size=11, bold=True, color=PRIMARY, font_name="Menlo")
        tb(slide, sum_str, 8.5, ty + 0.05, 1.8, 0.4,
           size=11, color=SILVER, font_name="Menlo")
        tb(slide, action, 10.4, ty + 0.05, 2.0, 0.4,
           size=11, bold=True, color=col)

    metric_card(slide, "Naif", "O(n²)", 6.4, 4.7, 3.0, 1.2, accent=ROSE)
    metric_card(slide, "Two Pointers", "O(n)", 9.6, 4.7, 3.3, 1.2, accent=EMERALD)

    callout(slide, "PRE-CONDITION: opposite direction butuh sorted array",
            6.4, 6.0, 6.5, 0.7, color=AMBER, icon="⚠")

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "Opposite Direction",
                    "L bergerak →, R bergerak ← — paling klasik",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Two Sum Sorted — O(n) Template")
    code = """int L = 0, R = n - 1;
while (L < R) {
    ll s = A[L] + A[R];
    if (s == T) {
        cout << L+1 << " " << R+1 << "\\n";
        return 0;                  // FOUND
    } else if (s < T) {
        L++;     // sum kekecilan → naikkan L
    } else {
        R--;     // sum kebesaran → turunkan R
    }
}
cout << "IMPOSSIBLE\\n";"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.7, font_size=11, accent=EMERALD)

    # Right: trace table
    tb(slide, "📊 Trace: T=7 pada [1,3,4,6,8,9]",
       7.2, 1.1, 5.7, 0.4, size=12, bold=True, color=AMBER)
    rows = [
        ["0,5", "1,9", "10", "R--"],
        ["0,4", "1,8", "9",  "R--"],
        [("0,3", EMERALD), ("1,6", EMERALD), ("7", EMERALD), ("FOUND!", EMERALD)],
    ]
    styled_table(slide, ["L,R", "A[L],A[R]", "Sum", "Aksi"], rows,
                 7.2, 1.65, [1.3, 1.6, 1.0, 1.7], row_h=0.55,
                 header_colors=[PRIMARY, EMERALD, AMBER, ROSE],
                 body_size=10, header_size=10)

    insight_card(slide, "🧠 Bukti Korektsi",
                 ["s > T → A[R] tidak bisa pair dengan",
                  "  manapun di kanan L → R-- aman",
                  "s < T → A[L] tidak bisa pair dengan",
                  "  manapun di kiri R → L++ aman"],
                 7.2, 4.0, 5.7, 2.0)

    callout(slide, "Wajib SORTED untuk pola ini",
            7.2, 6.15, 5.7, 0.6, color=ROSE, icon="🔑")

    # ── Slide: Palindrome check ───────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Palindrome Check — Same Pattern, No Sort")

    code = """bool isPalindrome(const string& s) {
    int L = 0, R = s.size() - 1;
    while (L < R) {
        if (s[L] != s[R]) return false;
        L++;
        R--;
    }
    return true;
}

// Variasi: skip non-alphanumeric
while (L < R) {
    while (L<R && !isalnum(s[L])) L++;
    while (L<R && !isalnum(s[R])) R--;
    if (tolower(s[L]) != tolower(s[R]))
        return false;
    L++; R--;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=11, accent=PRIMARY)

    # Right: trace
    tb(slide, "🎬 Trace: 'racecar'",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    word = list("racecar")
    array_cells(slide, word, 7.2, 1.7,
                cell_w=0.7, cell_h=0.55,
                highlights={i: BG_CARD_2 for i in range(7)})

    steps = [
        ("L=0,R=6", "r==r", "OK ✓", EMERALD),
        ("L=1,R=5", "a==a", "OK ✓", EMERALD),
        ("L=2,R=4", "c==c", "OK ✓", EMERALD),
        ("L=3,R=3", "stop", "PALINDROME", AMBER),
    ]
    for i, (state, check, result, col) in enumerate(steps):
        ty = 2.6 + i * 0.55
        rounded_rect(slide, 7.2, ty, 5.7, 0.5, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, state, 7.35, ty + 0.05, 1.5, 0.4,
           size=11, bold=True, color=PRIMARY, font_name="Menlo")
        tb(slide, check, 8.85, ty + 0.05, 1.5, 0.4,
           size=11, color=SILVER, font_name="Menlo")
        tb(slide, result, 10.35, ty + 0.05, 2.5, 0.4,
           size=11, bold=True, color=col)

    insight_card(slide, "Aplikasi Lain Opposite",
                 ["Container with most water",
                  "Reverse string in-place",
                  "Trapping rain water",
                  "Three sum (fix + two pointer)"],
                 7.2, 4.95, 5.7, 1.8)

    # ── Section 03 ─────────────────────────────────────────────
    section_divider(prs, "03", "Same Direction",
                    "Slow + fast — overwrite in-place dengan O(1) memori",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Remove Duplicates — Slow + Fast Pointer")

    code = """// Remove duplicates dari sorted array, in-place
int slow = 0;
for (int fast = 1; fast < n; fast++) {
    if (A[fast] != A[slow]) {
        slow++;
        A[slow] = A[fast];
    }
}
int newSize = slow + 1;
// A[0..newSize-1] adalah unique elements

// Trace: [1,1,2,2,3,4,4]
// slow=0, fast=1: A[1]==A[0], skip
// slow=0, fast=2: A[2]!=A[0], slow=1, A[1]=2
// slow=1, fast=3: A[3]==A[1], skip
// slow=1, fast=4: A[4]!=A[1], slow=2, A[2]=3
// slow=2, fast=5: A[5]!=A[2], slow=3, A[3]=4
// hasil: [1,2,3,4,...] newSize=4"""
    code_box(slide, code, 0.5, 1.1, 7.0, 5.7, font_size=10.5, accent=AMBER)

    # Right: visual
    tb(slide, "🎯 Visual: slow & fast",
       7.7, 1.1, 5.2, 0.4, size=13, bold=True, color=PRIMARY)

    # Initial array
    tb(slide, "Initial:", 7.7, 1.65, 5.2, 0.3, size=11, color=SLATE)
    array_cells(slide, [1, 1, 2, 2, 3, 4, 4], 7.7, 2.0,
                cell_w=0.65, cell_h=0.5,
                highlights={i: BG_CARD_2 for i in range(7)})

    # After
    tb(slide, "After (slow=3, newSize=4):",
       7.7, 2.85, 5.2, 0.3, size=11, color=EMERALD)
    array_cells(slide, [1, 2, 3, 4, "_", "_", "_"], 7.7, 3.2,
                cell_w=0.65, cell_h=0.5,
                highlights={0: EMERALD, 1: EMERALD, 2: EMERALD, 3: EMERALD,
                            4: BG_CARD, 5: BG_CARD, 6: BG_CARD},
                colors_map={i: BG_DEEP for i in range(4)})

    insight_card(slide, "Pola Slow+Fast",
                 ["fast: traversal seluruh array",
                  "slow: posisi tulis berikutnya",
                  "Ketika cocok kondisi → slow++",
                  "Hemat memori O(1), no copy"],
                 7.7, 4.15, 5.2, 2.2)

    callout(slide, "Pakai untuk: dedup, partition, move zero",
            0.5, 6.85, 12.4, 0.45, color=EMERALD, icon="✨")

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Merge & Three Pointers",
                    "Merge 2 sorted, Three Sum, Dutch national flag",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Merge Two Sorted Arrays — i + j")

    code = """// Merge A (size m) dan B (size n) → C
int i = 0, j = 0, k = 0;
while (i < m && j < n) {
    if (A[i] <= B[j]) C[k++] = A[i++];
    else              C[k++] = B[j++];
}
while (i < m) C[k++] = A[i++];   // sisa A
while (j < n) C[k++] = B[j++];   // sisa B

// Kompleksitas: O(m + n) time, O(m+n) space"""
    code_box(slide, code, 0.5, 1.1, 6.6, 4.0, font_size=11, accent=VIOLET)

    code_3sum = """// === THREE SUM ===
sort(A.begin(), A.end());
for (int i = 0; i < n-2; i++) {
    if (i>0 && A[i]==A[i-1]) continue;  // skip dup
    int L = i+1, R = n-1, target = -A[i];
    while (L < R) {
        int s = A[L] + A[R];
        if (s == target) {
            // record (A[i], A[L], A[R])
            L++; R--;
        } else if (s < target) L++;
        else R--;
    }
}"""
    code_box(slide, code_3sum, 0.5, 5.25, 6.6, 1.85, font_size=10, accent=EMERALD)

    # Right: visual merge
    tb(slide, "🎯 Visual Merge",
       7.3, 1.1, 5.6, 0.4, size=13, bold=True, color=PRIMARY)

    tb(slide, "A:", 7.3, 1.7, 0.5, 0.4, size=12, bold=True, color=PRIMARY)
    array_cells(slide, [1, 4, 7], 7.85, 1.7,
                cell_w=0.55, cell_h=0.5,
                highlights={i: PRIMARY for i in range(3)},
                colors_map={i: BG_DEEP for i in range(3)})
    tb(slide, "B:", 9.7, 1.7, 0.5, 0.4, size=12, bold=True, color=AMBER)
    array_cells(slide, [2, 5, 8], 10.25, 1.7,
                cell_w=0.55, cell_h=0.5,
                highlights={i: AMBER for i in range(3)},
                colors_map={i: BG_DEEP for i in range(3)})

    tb(slide, "↓ merge", 9.5, 2.4, 1.0, 0.3, size=11, color=EMERALD)

    tb(slide, "C:", 7.3, 2.85, 0.5, 0.4, size=12, bold=True, color=EMERALD)
    array_cells(slide, [1, 2, 4, 5, 7, 8], 7.85, 2.85,
                cell_w=0.55, cell_h=0.5,
                highlights={0: PRIMARY, 1: AMBER, 2: PRIMARY, 3: AMBER,
                            4: PRIMARY, 5: AMBER},
                colors_map={i: BG_DEEP for i in range(6)})

    info_card(slide, "Three Sum Strategy",
              ["1. Sort array",
               "2. Fix A[i] dengan loop",
               "3. Two pointers di sisanya",
               "4. Skip duplikat (i>0 cek)",
               "Total: O(n²)"],
              7.3, 3.85, 5.6, 2.5, accent=EMERALD)

    callout(slide, "Dutch Flag: 3 pointer untuk partisi 3-way",
            7.3, 6.5, 5.6, 0.55, color=VIOLET, icon="🇳🇱")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Two Pointers Pitfalls")

    mistakes = [
        ("1. Lupa sort untuk opposite",
         "Two Sum / 3Sum tanpa sort.\nWajib sorted dulu.",
         ROSE),
        ("2. Loop condition L<=R vs L<R",
         "Beda makna! Untuk pair butuh L<R.\nUntuk single pivot L<=R.",
         ROSE),
        ("3. Lupa skip duplikat di 3Sum",
         "Output triplet duplicate.\nCek if i>0 && A[i]==A[i-1].",
         AMBER),
        ("4. Overflow di sum",
         "A[L]+A[R] bisa overflow int.\nPakai long long untuk sum.",
         AMBER),
        ("5. Index off-by-one",
         "1-indexed vs 0-indexed.\nCek output format.",
         AMBER),
        ("6. Stop kondisi salah",
         "Slow+fast: fast<n.\nMerge: cek dua array selesai.",
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
    slide_header(slide, "Cheatsheet — Two Pointers Templates")

    cheat_left = """// === OPPOSITE (sorted) ===
int L = 0, R = n - 1;
while (L < R) {
    if (cond_match) {
        // proses
        L++; R--;       // atau break
    } else if (need_larger) {
        L++;
    } else {
        R--;
    }
}

// === PALINDROME ===
int L = 0, R = s.size() - 1;
while (L < R) {
    if (s[L++] != s[R--]) return false;
}
return true;"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10.5, accent=PRIMARY)

    cheat_right = """// === SAME DIRECTION ===
int slow = 0;
for (int fast = 0; fast < n; fast++) {
    if (cond) {
        A[slow++] = A[fast];
    }
}
int newSize = slow;

// === MERGE ===
int i = 0, j = 0, k = 0;
while (i < m && j < n) {
    if (A[i] <= B[j]) C[k++] = A[i++];
    else              C[k++] = B[j++];
}
while (i < m) C[k++] = A[i++];
while (j < n) C[k++] = B[j++];"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10.5, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 19, "Two Pointers: dari O(n²) ke O(n) dengan elegan", [
        (PRIMARY, "Konsep", "2 pointer bergerak cerdas. Total kerja O(n) — setiap pointer max n langkah."),
        (EMERALD, "Opposite Direction", "L→ ←R. Wajib sorted. Two Sum, palindrome, container water."),
        (AMBER, "Same Direction", "Slow+fast. Tidak perlu sort. Remove dup, move zero, in-place."),
        (VIOLET, "Merge & 3Sum", "i+j untuk merge sorted. Three Sum: sort + fix + 2P. Dutch flag 3-way."),
        (ROSE, "Pitfall", "Lupa sort, off-by-one, lupa skip dup di 3Sum, overflow di sum."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_19_Presentation.pptx"))


if __name__ == "__main__":
    main()
