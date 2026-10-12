/*
============================================================
✅ Solution 2: Palindrome Check (Cek Palindrom)
============================================================
Approach: Reverse & Compare
Complexity: Time O(N) | Space O(N)
Key Insight: Palindrome = string sama jika di-reverse.
             Bisa juga cek s[i] == s[n-1-i] tanpa buat salinan.

📖 PENJELASAN PENDEKATAN:
1. Baca string s
2. Buat salinan rev = s
3. Reverse rev
4. Bandingkan s == rev

🔄 ALTERNATIVE APPROACHES:
- Two pointer: compare s[i] vs s[n-1-i] — O(N) time, O(1) space
- Recursive: compare first & last, lalu substr — O(N) tapi overhead
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca string
    string s;
    cin >> s;

    // Step 2: Buat salinan dan reverse
    string rev = s;
    reverse(rev.begin(), rev.end());

    // Step 3: Bandingkan dan output
    if (s == rev) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}
