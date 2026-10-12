/*
============================================================
✅ Solution 3: Sort by Score (Ranking Siswa)
============================================================
Approach: Vector of Pairs + Custom Comparator
Complexity: Time O(N log N) | Space O(N)
Key Insight: Gunakan pair<int, string> dengan trick:
             simpan (-nilai, nama) supaya sort ascending = nilai descending

📖 PENJELASAN PENDEKATAN:
1. Baca N pasangan (nama, nilai)
2. Simpan sebagai pair(-nilai, nama) — negate trick!
3. Sort ascending → otomatis: nilai descending, nama ascending
4. Output nama dan -nilai (kembalikan ke positif)

🔄 ALTERNATIVE APPROACHES:
- Custom comparator lambda — lebih readable tapi sedikit lebih lambat
- Struct + overload operator< — lebih proper tapi verbose
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca input
    int n;
    cin >> n;

    // Step 2: Simpan sebagai pair(-nilai, nama)
    vector<pair<int, string>> students(n);
    for (int i = 0; i < n; i++)
    {
        string nama;
        int nilai;
        cin >> nama >> nilai;
        students[i] = {-nilai, nama}; // negate trick!
    }

    // Step 3: Sort ascending
    // Karena first = -nilai, sort ascending = nilai descending
    // Jika -nilai sama, sort by nama ascending (default behavior)
    sort(students.begin(), students.end());

    // Step 4: Output
    for (auto &[neg_val, nama] : students)
    {
        cout << nama << ' ' << -neg_val << '\n';
    }

    return 0;
}
