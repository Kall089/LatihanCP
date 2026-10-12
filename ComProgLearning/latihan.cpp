#include <bits/stdc++.h>
using namespace std;

class Latihan
{
private:
    string nama;

public:
    void setNama(string n) { nama = n; }

    void TukarHuruf()
    {
        int n = nama.length();

        for (int i = 0; i <= n; i++)
        {
            cout << nama[n - i];
        }
    }
};
int main()
{
    Latihan baliknama;

    string nama;
    cin >> nama;

    baliknama.setNama(nama);
    baliknama.TukarHuruf();
}
