/*
============================================================
📋 TUGAS 03: Course Schedule (CSES)
============================================================
Source: CSES 1679 — Course Schedule
Difficulty: Easy
Topics: Kahn, IMPOSSIBLE

PROBLEM:
N kursus, M syarat "a b" artinya a harus sebelum b. Cetak urutan valid, atau
"IMPOSSIBLE".

INPUT FORMAT:
- Baris 1: N M
- M baris: a b

OUTPUT FORMAT:
- N bilangan, atau IMPOSSIBLE

CONSTRAINTS:
- 1 <= N <= 10^5, 1 <= M <= 2*10^5

SAMPLE INPUT 1:        SAMPLE OUTPUT 1:
5 3                    1 4 5 2 3
1 2
3 1
4 5

SAMPLE INPUT 2:        SAMPLE OUTPUT 2:
3 3                    IMPOSSIBLE
1 2
2 3
3 1

SAMPLE INPUT 3:        SAMPLE OUTPUT 3:
4 2                    1 2 3 4
1 2
3 4
(urutan valid lain juga diterima pada sampel 1 dan 3)
============================================================
*/
