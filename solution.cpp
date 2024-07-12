#include <bits/stdc++.h>
using namespace std;
int dp[11][12][12][10000];
int fun(int index, int recharge_left, int skip_left, int power_left, int original_power, vector<int> &level, int flag)
{
    if (index == 11)
        return 1;
    if (skip_left == 0 && original_power < level[index])
        return 0;
    if (recharge_left == 0 && skip_left == 0 && power_left < level[index])
        return 0;
    if (dp[index][recharge_left][skip_left][power_left] != -1)
        return dp[index][recharge_left][skip_left][power_left];
    int help = 0;
    if (index == 2 || index == 6)
    {
        if (power_left >= level[index])
        {
            help = fun(index + 1, recharge_left, skip_left, power_left - level[index], original_power, level, 0);
        }
        else
        {
            if (recharge_left > 0 && (level[index] <= original_power))
                help = ((fun(index + 1, recharge_left - 1, skip_left, original_power - level[index], original_power, level, 0)));
            if (skip_left > 0)
                help = (help | (fun(index + 1, recharge_left, skip_left - 1, power_left, original_power, level, 1)));
        }
    }
    else
    {
        if (flag == 1)
        {
            if (power_left >= level[index])
            {
                help = fun(index + 1, recharge_left, skip_left, power_left - level[index], original_power, level, 1);
            }
            else
            {
                if (recharge_left > 0 && (level[index] <= original_power))
                    help = ((fun(index + 1, recharge_left - 1, skip_left, original_power - level[index], original_power, level, 1)));
                if (skip_left > 0)
                    help = (help | fun(index + 1, recharge_left, skip_left - 1, power_left, original_power, level, 1));
            }
        }
        else
        {
            int temp = level[index];
            level[index] += (level[index - 1]+1) / 2;
            if (power_left >= level[index])
            {
                help = fun(index + 1, recharge_left, skip_left, power_left - level[index], original_power, level, 1);
            }
            else
            {
                if (recharge_left > 0 && (level[index] <= original_power))
                    help = ((fun(index + 1, recharge_left - 1, skip_left, original_power - level[index], original_power, level, 1)));
                if (skip_left > 0){
                      help = (help | fun(index + 1, recharge_left, skip_left - 1, power_left, original_power, level, 1));
                }
                  
            }
            level[index] = temp;
        }
    }

    return dp[index][recharge_left][skip_left][power_left] = help;
}
int32_t main()
{
    int power_initial, recharge, skip;
    cin >> power_initial >> recharge >> skip;
    vector<int> level(11, 0);
    for (int i = 0; i < 11; i++)
        cin >> level[i];

    if (skip >= 11)
        cout << 1 << endl;
    else
    {
        memset(dp, -1, sizeof(dp));
        int a = fun(0, recharge, skip, power_initial, power_initial, level, 1);
        if(a==1){
            cout<<"Abhmanyu wins";
        }
        else{
            cout<<"Abhmanyu fails and dies";
        }
    }
}
