#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<double>> topsis(n, vector<double>(m, 0));
    vector<double> pembagi(m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> topsis[i][j];
            pembagi[j] += topsis[i][j] * topsis[i][j];
        }
    }

    // vector<double> pembagi(m);

    // for (int j = 0; j < m; j++)
    // {
    //     double jumlahKuadrat = 0;
    //     for (int i = 0; i < n; i++)
    //     {
    //         jumlahKuadrat += topsis[i][j] * topsis[i][j];
    //     }
    //     pembagi[j] = sqrt(jumlahKuadrat);
    // }

    vector<vector<double>> r(n, vector<double>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            r[i][j] = topsis[i][j] / sqrt(pembagi[j]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << r[i][j] << " ";
        }
        cout << endl;
    }

    vector<double> bobot(m);

    for (int j = 0; j < m; j++)
    {
        cin >> bobot[j];
    }

    vector<vector<double>> y(n, vector<double>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            y[i][j] = bobot[j] * r[i][j];
            cout << y[i][j] << " ";
        }
        cout << endl;
    }
}