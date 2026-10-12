/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : solution_3.cpp
 * Topik : Task Scheduler (CPU Cooldown)
 * -----------------------------------------------
 * Diberikan task dengan cooldown n, temukan waktu minimum penyelesaian semua task.
 *
 * Input format:
 * Baris 1: n (cooldown)
Baris 2: string task (A-Z)
 *
 * Output format:
 * Satu bilangan: waktu minimum
 *
 * Constraints:
 * 1 ≤ |tasks| ≤ 10^4, 0 ≤ n ≤ 100
 *
 * Sample Input 1:
 * 2
 * AAABBB
 *
 * Sample Output 1:
 * 8
 *
 * Sample Input 2:
 * 0
 * AAABBB
 *
 * Sample Output 2:
 * 6
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int leastInterval(string& tasks, int n) {
    int freq[26] = {};
    for (char c : tasks) freq[c-'A']++;

    priority_queue<int> maxPQ;
    for (int f : freq) if (f > 0) maxPQ.push(f);

    int time = 0;
    while (!maxPQ.empty()) {
        vector<int> temp;
        int cycle = n + 1;
        while (cycle-- && !maxPQ.empty()) {
            int f = maxPQ.top(); maxPQ.pop();
            if (f > 1) temp.push_back(f - 1);
            time++;
        }
        for (int f : temp) maxPQ.push(f);
        if (!maxPQ.empty()) time += cycle + 1; // idle slots
    }
    return time;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string tasks;
    cin >> n >> tasks;
    cout << leastInterval(tasks, n) << "\n";
    return 0;
}
