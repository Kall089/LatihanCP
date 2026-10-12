/*
============================================================
✅ Solution 6: Student Records (Multi-Criteria Sort + Tuple)
============================================================
Approach: Vector of Tuples + Negate Trick for Descending
Complexity: Time O(N log N) | Space O(N)
Key Insight: Untuk sort multi-criteria dengan arah berbeda
             (desc IPK, asc angkatan, asc nama), kita bisa:
             - Negate field yang mau descending
             - Atau pakai custom comparator

📖 PENJELASAN PENDEKATAN:
1. Baca data mahasiswa
2. Simpan tuple: (-IPK_int, angkatan, nama)
   (Trick: kalikan IPK*100 jadi integer untuk hindari floating point issues)
3. Sort ascending → otomatis: IPK desc, angkatan asc, nama asc
4. Output nama

🔄 ALTERNATIVE APPROACHES:
- Custom comparator (lambda): lebih readable
- Struct + operator<: lebih OOP tapi verbose
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

    // Step 2: Simpan data sebagai tuple(-ipk_scaled, angkatan, nama)
    vector<tuple<int, int, string>> students;
    students.reserve(n);

    for (int i = 0; i < n; i++)
    {
        string nama;
        double ipk;
        int angkatan;
        cin >> nama >> ipk >> angkatan;

        // Konversi IPK ke integer (x100) untuk hindari floating point error
        // Negate supaya sort ascending = IPK descending
        int ipk_scaled = -(int)round(ipk * 100);

        students.emplace_back(ipk_scaled, angkatan, nama);
    }

    // Step 3: Sort (default lexicographic on tuple)
    // Urutan: -ipk_scaled asc (= ipk desc), angkatan asc, nama asc
    sort(students.begin(), students.end());

    // Step 4: Output nama
    for (auto &[ipk_neg, angkatan, nama] : students)
    {
        cout << nama << '\n';
    }

    return 0;
}
