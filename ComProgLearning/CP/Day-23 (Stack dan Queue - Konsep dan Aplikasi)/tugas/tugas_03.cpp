/*
============================================================
📋 TUGAS 3: Stack — Postfix Evaluation
============================================================
Source: Classic
Difficulty: Easy
Topics: stack, expression evaluation

PROBLEM:
Evaluasi ekspresi postfix (Reverse Polish Notation).
Operator: +, -, *, /
Operand: bilangan bulat (bisa negatif)

Dalam notasi postfix: "3 4 +" berarti 3 + 4 = 7
"5 3 - 2 *" berarti (5-3) * 2 = 4

INPUT:
- Satu baris: ekspresi postfix (token dipisah spasi)

OUTPUT:
- Satu integer: hasil evaluasi

CONSTRAINTS:
- Jumlah token ≤ 100
- Operand: -1000 ≤ x ≤ 1000
- Hasil intermediate & final fit dalam int
- Pembagian integer (bulatkan ke nol)

SAMPLE INPUT:
3 4 + 2 *

SAMPLE OUTPUT:
14

SAMPLE INPUT 2:
5 1 2 + 4 * + 3 -

SAMPLE OUTPUT 2:
14

NOTE: 5 + ((1+2) * 4) - 3 = 5 + 12 - 3 = 14
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hint: Baca token per token. Jika angka: push. Jika operator: pop 2, hitung, push result.

    return 0;
}
