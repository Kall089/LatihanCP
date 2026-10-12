/*
============================================================
  Solution 2: Deque Operations
============================================================
Kompleksitas: O(1) per operasi
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> q;
    deque<int> dq;
    while (q--) {
        string op; cin >> op;
        if (op == "PUSH_FRONT") { int x; cin>>x; dq.push_front(x); }
        else if (op == "PUSH_BACK") { int x; cin>>x; dq.push_back(x); }
        else if (op == "POP_FRONT") { cout<<dq.front()<<"\n"; dq.pop_front(); }
        else if (op == "POP_BACK")  { cout<<dq.back()<<"\n";  dq.pop_back(); }
        else if (op == "FRONT") cout << dq.front() << "\n";
        else if (op == "BACK")  cout << dq.back()  << "\n";
        else cout << dq.size() << "\n";
    }
    return 0;
}
