/*
============================================================
🏋️ Exercise 5: Sum of Two Values (Two Sum)
============================================================
Day: 4 | Difficulty: Medium-Hard
Topic: Unordered_map, complement search
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan array N bilangan dan target X. Cari DUA POSISI (1-indexed)
yang elemen-elemennya berjumlah tepat X. Output posisi keduanya.
Jika ada beberapa jawaban, output salah satu. Jika tidak ada, output "IMPOSSIBLE".

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan X
- Baris kedua: N buah integer

📤 OUTPUT FORMAT:
- Dua integer: posisi (1-indexed), atau "IMPOSSIBLE"

📏 CONSTRAINTS:
- 1 ≤ N ≤ 200,000
- 1 ≤ X ≤ 2,000,000,000
- 1 ≤ a[i] ≤ 1,000,000,000
- Semua elemen mungkin tidak distinct

📎 SAMPLE INPUT 1:
4 8
2 7 5 1

📎 SAMPLE OUTPUT 1:
2 4

📎 SAMPLE INPUT 2:
5 5
1 2 3 4 5

📎 SAMPLE OUTPUT 2:
1 4

📎 SAMPLE INPUT 3:
3 100
1 2 3

📎 SAMPLE OUTPUT 3:
IMPOSSIBLE

💡 HINT: Untuk setiap elemen a[i], cari apakah (X - a[i]) sudah pernah
         dilihat sebelumnya. Pakai unordered_map<int, int> value→index.

🎯 Learning Goals:
- [ ] Gunakan unordered_map untuk O(1) lookup
- [ ] Two sum pattern (complement search)
- [ ] Handle 1-indexed output
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan X

    int n, x;
    cin >> n >> x;

    unordered_map<int, int> val;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;

        int need = x - a;

        auto it = val.find(need);

        if (it != val.end())
        {
            cout << it->second << " " << i + 1 << '\n';
            return 0;
        }

        val[a] = i + 1;
    }
    cout << "IMPOSSIBLE" << endl;

    // TODO: Baca array

    // TODO: Iterasi array, untuk setiap elemen:
    //       - Hitung complement = X - arr[i]
    //       - Cek apakah complement ada di map
    //       - Jika ya: output kedua posisi (1-indexed)
    //       - Jika tidak: simpan arr[i] → index ke map

    // TODO: Jika selesai loop tanpa menemukan: output "IMPOSSIBLE"

    return 0;
}
