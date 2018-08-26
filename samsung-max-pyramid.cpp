#include <iostream>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

struct Box {
    int id;
    int a, h, b;

    Box(int a=0, int b=0, int h=0, int id=0)
    : a(a), b(b), h(h), id(id) {}
};

Box boxes[60];
int dp[60][1 << 20];

void swap(Box &a, Box &b) {
    Box temp = a;
    a = b;
    b = temp;
}

bool less_B(Box &box_1, Box &box_2) {
    if (box_1.a != box_2.a) return box_1.a < box_2.a;
    return box_1.b < box_2.b;
}

int max(const int &first,const int &second) {
    return first < second ? second : first;
}

int solve()
{
    int n;
    cin >> n;

    int p = 0;
    for (int i = 0; i < n; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        //rotation
        if (b < a) swap(a, b);
        if (c < b) {
            swap(c, b);
            if (b < a) swap(a, b);
        }

        boxes[p++] = Box(a, b, c, i);
        boxes[p++] = Box(a, c, b, i);
        boxes[p++] = Box(b, c, a, i);
    }
    //sort Boxes, min to max
    for (int i = 0; i < 3 * n; i++) {
        for (int j = i + 1; j < 3 * n; j++) {
            if (less_B(boxes[i], boxes[j])) swap(boxes[i], boxes[j]);
        }
    }
       
    int result = 0;
    //clean old values
    for (int i = 0; i < 3 * n; i++)
    {
        for(int mask=0;mask<(1<<n);mask++)
            dp[i][mask] = -1;
    }
    //init_state
    dp[0][0] = 0;

    for (int i = 0; i <= 3 * n; i++) // кол-во рассмотренных кубиков
    {
        for (int mask = 0; mask < (1 << n); mask++)
        {
            if (dp[i][mask] == -1) continue; //invalid state
            result = max(result, dp[i][mask]); // refresh res
            for (int j=i+1; j <= 3 * n; j++) {
                if (mask&(1 << boxes[j-1].id)) continue; // if already exist
                if (i > 0 && boxes[i-1].b < boxes[j-1].b) continue; // check for b, if a_1 and a_2 are different

                int new_mask=mask|(1<<boxes[j-1].id); //new mask where we added box_j
                dp[j][new_mask] = max(dp[j][new_mask], dp[i][mask]+boxes[j-1].h);
            }
        }
    }
    return result;
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