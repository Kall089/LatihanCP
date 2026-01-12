#include <iostream>

using namespace std;

void primeFact(int n)
{
    for (int i = 2; i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                cnt++;
                n = n / i;
            }
            cout << i << "^" << cnt << ", ";
        }
    }
}

int main()
{
    primeFact(210);
}