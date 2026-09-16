// 夏季特惠
// 某公司游戏平台的夏季特惠开始了，你决定入手一些游戏
// 现在你一共有X元的预算，平台上所有的 n 个游戏均有折扣
// 标号为 i 的游戏的原价a_i元，现价只要b_i元
// 也就是说该游戏可以优惠 a_i - b_i，并且你购买该游戏能获得快乐值为w_i
// 由于优惠的存在，你可能做出一些冲动消费导致最终买游戏的总费用超过预算
// 只要满足 : 获得的总优惠金额不低于超过预算的总金额
// 那在心理上就不会觉得吃亏。
// 现在你希望在心理上不觉得吃亏的前提下，获得尽可能多的快乐值。
// 测试链接 : https://leetcode.cn/problems/tJau2o/

#include <iostream>
#include <vector>
#define ll long long

// n:游戏数量 X:预算
int n, X;
// 答案: 在心里不觉得吃亏的前提下,获得尽可能多的快乐值 
ll maxHappy = 0;
// 01背包中讨论的游戏数量
int gameCount = 0;

ll countGameMaxHappy(const std::vector<int>& price,
    const std::vector<int>& happy,
    std::vector<ll>& dp
) {
    // 01背包模板
    for (int i = 1; i <= gameCount; i++) {
        for (int j = X; j >= price[i]; j--) {
            dp[j] = std::max(dp[j], dp[j-price[i]] + happy[i]);
        }
    }
    return dp[X];
}

int main() {

    std::cin >> n >> X;

    // 代价数组和收益数组
    std::vector<int> price(n+5, 0), happy(n+5, 0);
    // dp数组:前i个游戏中花费不高于j获得的最多快乐值
    std::vector<ll> dp(X+500*500, 0);

    for (int i = 1; i <= n; i++) {

        // a:原价 b:现价 w:快乐值
        int a, b, w; std::cin >> a >> b >> w;

        // 收益: 购买后获得的收益
        int profit = (a - b) - b;
        // 代价: 购买后付出的真实代价
        int cost = b - (a - b);

        // 就算购买了也有收益,那肯定要买呀
        if (profit >= 0) {
            X += profit; // 添加收益
            maxHappy += w; // 添加快乐值
        }
        // 否则就是放入01背包问题中讨论
        else {
            gameCount++; // 游戏+1
            price[gameCount] = cost; // 游戏的真实代价
            happy[gameCount] = w; // 游戏的快乐值
        }

    }

    maxHappy += countGameMaxHappy(price, happy, dp);

    std::cout << maxHappy << std::endl;

    return 0;
}