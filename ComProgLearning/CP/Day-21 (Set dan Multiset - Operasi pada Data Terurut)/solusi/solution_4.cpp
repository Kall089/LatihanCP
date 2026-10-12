/*
============================================================
✅ Solution 4: Registration System (Map)
============================================================
Approach: map<string, int> to track request count per name
Complexity: Time O(N log N) | Space O(N)
Key Insight: Map tracks berapa kali setiap nama sudah di-request.
             Jika pertama kali → "OK", jika sudah ada → "nama_count".

📖 PENJELASAN PENDEKATAN:
1. Maintain map<string, int> db
2. Untuk setiap nama:
   - Jika db[nama] == 0: output "OK", set db[nama] = 1
   - Jika db[nama] > 0: output "nama_" + to_string(db[nama]), increment

🔄 ALTERNATIVE APPROACHES:
- unordered_map: O(1) average per query, total O(N)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    map<string, int> db;
    for (int i = 0; i < n; i++) {
        string name;
        cin >> name;

        if (db[name] == 0) {
            cout << "OK" << '\n';
        } else {
            cout << name << '_' << db[name] << '\n';
        }
        db[name]++;
    }

    return 0;
}
