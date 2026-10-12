/*
============================================================
📋 TUGAS 15: Bandingkan BIT dengan Segment Tree
============================================================
Source: Original
Difficulty: Hard
Topics: analisis empiris

PROBLEM:
Bangkitkan array acak berukuran N dan Q operasi acak (campuran update titik
dan query rentang), lalu jawab dengan DUA cara: Fenwick Tree dan segment
tree. Ukur waktu build dan waktu total operasi masing-masing, cetak keempat
angkanya dalam milidetik. Lakukan untuk beberapa nilai N dan Q, lalu
simpulkan sendiri seberapa besar selisih konstantanya.

INPUT FORMAT:
- Baris pertama: N dan Q

OUTPUT FORMAT:
- Empat bilangan

CONSTRAINTS:
- 1 <= N, Q <= 10^6

SAMPLE INPUT 1:
1000000 1000000

SAMPLE OUTPUT 1:
(bergantung mesin)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // BIT biasanya 3-5x lebih cepat untuk operasi yang sama, karena tidak ada rekursi dan aksesnya ramah cache. Buktikan sendiri dengan angka, lalu ingat bahwa segment tree tetap menang untuk min/max/gcd.

    return 0;
}
