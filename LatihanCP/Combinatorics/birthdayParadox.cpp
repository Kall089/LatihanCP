#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int people = 0;

    float num = 365;
    float denom = 365;

    float prob_diff_bday = 1;

    while (1)
    {
        prob_diff_bday *= (num / denom);
        if (prob_diff_bday < 0.5)
        {
            break;
        }
        cout << "People " << people << " Prob : " << prob_diff_bday << endl;
        num = num - 1;
        people = people + 1;
    }

    cout << "Final Ans " << people << endl;
}