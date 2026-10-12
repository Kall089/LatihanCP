/*
============================================================
🏋️ Exercise 3: Sort by Score (Ranking Siswa)
============================================================
Day: 3 | Difficulty: Medium
Topic: Vector of Pairs, Custom Sort
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N siswa, masing-masing punya nama dan nilai. Urutkan siswa
berdasarkan nilai dari TERTINGGI ke TERENDAH. Jika nilainya sama,
urutkan berdasarkan nama secara LEXICOGRAPHIC (A-Z).

📥 INPUT FORMAT:
- Baris pertama: integer N (jumlah siswa)
- N baris berikutnya: string nama dan integer nilai (dipisah spasi)

📤 OUTPUT FORMAT:
- N baris: nama dan nilai setelah diurutkan

📏 CONSTRAINTS:
- 1 ≤ N ≤ 100,000
- 1 ≤ |nama| ≤ 20
- 0 ≤ nilai ≤ 100

📎 SAMPLE INPUT 1:
5
Alice 85
Bob 92
Charlie 85
Dave 78
Eve 92

📎 SAMPLE OUTPUT 1:
Bob 92
Eve 92
Alice 85
Charlie 85
Dave 78

📎 SAMPLE INPUT 2:
3
Zara 100
Yuki 100
Xander 100

📎 SAMPLE OUTPUT 2:
Xander 100
Yuki 100
Zara 100

💡 HINT: Gunakan vector<pair<int,string>> dengan custom comparator,
         atau trick: simpan (-nilai, nama) lalu sort ascending

🎯 Learning Goals:
- [ ] Input data ke vector of pairs
- [ ] Sort dengan custom comparator (lambda)
- [ ] Atau gunakan trick negate untuk sort descending
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N
    int N;
    cin >> N;

    // TODO: Baca N pasangan (nama, nilai) ke vector<pair<...>>
    vector<pair<string, int>> students(N);

    // TODO: Sort berdasarkan:
    //       1. Nilai DESCENDING (tertinggi dulu)
    //       2. Nama ASCENDING (lexicographic) jika nilai sama

    for (int i = 0; i < N; i++)
    {
        cin >> students[i].first >> students[i].second;
    }

    auto cmp = [](const auto &a, const auto &b)
    {
        if (a.second != b.second)
        {
            return a.second > b.second;
        }

        return a.first < b.first;
    };

    sort(students.begin(), students.end(), cmp);
    cout << endl;

    // TODO: Output semua pasangan setelah sort

    for (auto [f, s] : students)
    {
        cout << f << " " << s << endl;
    }

    return 0;
}
