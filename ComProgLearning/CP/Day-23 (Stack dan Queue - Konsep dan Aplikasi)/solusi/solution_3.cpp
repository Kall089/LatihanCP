/*
============================================================
✅ Solution 3: Reverse String with Stack (Backspace)
============================================================
Approach: Use string as stack (push_back / pop_back)
Complexity: Time O(N) | Space O(N)
Key Insight: String itself can act as a stack.
             push_back = type char, pop_back = backspace.

📖 PENJELASAN PENDEKATAN:
1. Buat string result kosong
2. Untuk setiap karakter di input:
   - Jika huruf: push_back ke result
   - Jika '#': pop_back dari result (jika tidak kosong)
3. Output result

🔄 ALTERNATIVE APPROACHES:
- Stack<char> lalu reconstruct: sama O(N) tapi perlu reverse
- Two pointer (in-place): O(1) space tapi lebih kompleks
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    string result;
    for (char c : s) {
        if (c == '#') {
            if (!result.empty()) {
                result.pop_back();
            }
        } else {
            result.push_back(c);
        }
    }

    cout << result << '\n';

    return 0;
}
