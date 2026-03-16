#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, a, b) for (int i = a; i < b; i++)

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, N;
    cin >> R >> C >> N;

    vector<vector<bool>> visited(R + 1, vector<bool>(C + 1, false));

    while (N--)
    {
        int X, Y;
        cin >> X >> Y;
        X--;
        Y--;
        for (int i = 0; i < R; i++)
            visited[i][Y] = !visited[i][Y];

        for (int j = 0; j < C; j++)
        {
            if (j == Y)
                continue;
            visited[X][j] = !visited[X][j];
        }
    }

    int cnt = 0;

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (visited[i][j])
                cnt++;
        }
    }

    cout << cnt << endl;
}