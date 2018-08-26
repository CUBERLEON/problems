#include <iostream>

using namespace std;

bool statuses[10];
int opers[4];
int n, op, limit, target;

int a[1000], a_count;
int a_len[1000];

int mem[2010];

bool check(int x)
{
    if (!x) return statuses[0];

    while (x > 0)
    {
        if (!statuses[x % 10]) return false;
        x /= 10;
    }

    return true;
}

int count(int x)
{
    if (!x) return 1;

    int len = 0;
    while (x > 0)
    {
        ++len;
        x /= 10;
    }

    return len;
}

void solve(int number, int operations)
{
    if (number < -999 || number > 999) return;
    if (operations > limit) return;
    if (mem[number + 1000] != -1 && mem[number + 1000] <= operations) return;

    mem[number + 1000] = operations;

    for (int i = 0; i < op; ++i)
    {
        for (int j = 0; j < a_count; ++j)
        {
            if (opers[i] == 1)
            {
                solve(number + a[j], operations + a_len[j] + 1);
            }
            else if (opers[i] == 2)
            {
                solve(number - a[j], operations + a_len[j] + 1);
            }
            else if (opers[i] == 3)
            {
                solve(number * a[j], operations + a_len[j] + 1);
            }
            else if (opers[i] == 4 && a[j] != 0)
            {
                solve(number / a[j], operations + a_len[j] + 1);
            }
        }
    }
}

int solve()
{
    cin >> n >> op >> limit;

    for (int i = 0; i < 10; ++i)
    {
        statuses[i] = false;
    }

    for (int i = 0; i < n; ++i)
    {
        int tmp;
        cin >> tmp;
        statuses[tmp] = true;
    }

    for (int i = 0; i < op; ++i)
    {
        cin >> opers[i];
    }

    cin >> target;

    a_count = 0;
    for (int i = 0; i <= 999; ++i)
    {
        if (check(i))
        {
            if (i == target) return count(i);

            a_len[a_count] = count(i);
            a[a_count++] = i;
        }
    }

    for (int i = -999; i <= 999; ++i)
    {
        mem[i + 1000] = -1;
    }

    for (int i = 0; i < a_count; ++i)
    {
        solve(a[i], a_len[i]);
    }
    
    return mem[target + 1000] == -1 ? -1 : mem[target + 1000] + 1;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tests;
    cin >> tests;

    for (int t = 0; t < tests; ++t)
    {
        int result = solve();

        cout << "Case #" << t << ": " << result << endl;
    }

    return 0;
}