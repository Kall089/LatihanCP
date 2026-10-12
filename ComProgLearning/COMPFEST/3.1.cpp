#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Task
{
    ll L;
    ll R;
    ll W;

    int openRank;
    int closeRank;
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Task> task(N);

    for (int i = 0; i < N; i++)
    {
        cin >> task[i].L >> task[i].R >> task[i].W;
    }

    /*
        openOrder menyimpan ID tugas dalam
        urutan pengambilan.

        Awalnya:
        openOrder = [0, 1, 2, ..., N-1]
    */
    vector<int> openOrder(N);

    iota(
        openOrder.begin(),
        openOrder.end(),
        0);

    /*
        Aturan urutan pengambilan:

        1. L lebih kecil terlebih dahulu.
        2. Jika L sama, R lebih besar dahulu.
    */
    sort(
        openOrder.begin(),
        openOrder.end(),

        [&](int a, int b)
        {
            if (task[a].L != task[b].L)
            {
                return task[a].L < task[b].L;
            }

            return task[a].R > task[b].R;
        });

    /*
        Memberikan openRank kepada setiap tugas.
    */
    for (int posisi = 0; posisi < N; posisi++)
    {
        int id = openOrder[posisi];

        task[id].openRank = posisi + 1;
    }

    /*
        closeOrder menyimpan ID tugas dalam
        urutan pengumpulan.
    */
    vector<int> closeOrder(N);

    iota(
        closeOrder.begin(),
        closeOrder.end(),
        0);

    /*
        Aturan urutan pengumpulan:

        1. R lebih kecil terlebih dahulu.
        2. Jika R sama, L lebih besar dahulu.
    */
    sort(
        closeOrder.begin(),
        closeOrder.end(),

        [&](int a, int b)
        {
            if (task[a].R != task[b].R)
            {
                return task[a].R < task[b].R;
            }

            return task[a].L > task[b].L;
        });

    /*
        Memberikan closeRank kepada setiap tugas.
    */
    for (int posisi = 0; posisi < N; posisi++)
    {
        int id = closeOrder[posisi];

        task[id].closeRank = posisi + 1;
    }

    cout << "Urutan pengambilan tugas:\n";

    for (int posisi = 0; posisi < N; posisi++)
    {
        int id = openOrder[posisi];

        cout << posisi + 1
             << ". Tugas " << id + 1
             << " [" << task[id].L
             << ", " << task[id].R << "]"
             << " poin = " << task[id].W
             << '\n';
    }

    cout << '\n';

    cout << "Urutan pengumpulan tugas:\n";

    for (int posisi = 0; posisi < N; posisi++)
    {
        int id = closeOrder[posisi];

        cout << posisi + 1
             << ". Tugas " << id + 1
             << " [" << task[id].L
             << ", " << task[id].R << "]"
             << " poin = " << task[id].W
             << '\n';
    }

    cout << '\n';

    cout << "Rank setiap tugas:\n";

    for (int i = 0; i < N; i++)
    {
        cout << "Tugas " << i + 1
             << ": openRank = "
             << task[i].openRank
             << ", closeRank = "
             << task[i].closeRank
             << '\n';
    }

    return 0;
}