#include <bits/stdc++.h>
using namespace std;

/**
 * Topik: Day-143 (DP Linear 1D)
 * Latihan 2: Tangga Rusak dengan Langkah 1..K
 *
 * Ada N anak tangga. Sekali melangkah boleh naik 1 sampai K anak tangga.
 * Beberapa anak tangga RUSAK dan tidak boleh diinjak sama sekali.
 * Cetak banyak cara mencapai anak tangga ke-N modulo 10^9+7, atau 0.
 *
 * Batas: 1 <= N <= 10^5, 1 <= K <= 100
 *
// Test Case 1:
// Input:
// 5 2 1
// 3
// Output:
// 2
// (anak tangga 3 rusak; jalur yang tersisa: 1-2-4-5 dan 2-4-5;
//  periksa dengan tanganmu)
//
// Test Case 2 (tidak ada yang rusak, K=3):
// Input:
// 4 3 0
// Output:
// 7
//
// Test Case 3 (tujuan rusak):
// Input:
// 5 2 1
// 5
// Output:
// 0
 */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k, r;
    cin >> n >> k >> r;

    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i <)
}