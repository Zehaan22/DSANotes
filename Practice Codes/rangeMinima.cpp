#include <iostream>

using namespace std;

int maxPower(int L)
{
    int ans = 0;
    while (L > 1)
    {
        L /= 2;
        ans++;
    }
    return ans;
}

int main()
{
    int searchArray[] = {3, 2, 6, 4, 0, 9, 1, 5, 7, 8};

    cout << maxPower(40);
}