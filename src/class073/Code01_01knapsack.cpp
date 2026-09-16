#include <iostream>
#include <vector>
#include <algorithm>

/**
 * T:采药时间 M:采药数量
 * herbTime:每株草药的时间
 * herbValue:每株草药的价值
 */
int compute1(int T, int M, 
    const std::vector<int>& herbTime,
    const std::vector<int>& herbValue
) {
    // dp[i][j]:前i株草药中采药时间不多于j的最大价值
    std::vector<std::vector<int>> dp(M+1, std::vector<int>(T+1, 0));

    // dp[i][j] = max(dp[i-1][j], 
    //              dp[i-1][j-herbTime[i]] + herbValue[i])
    for (int i = 1; i <= M; i++) { // 遍历每株草药
        for (int j = 0; j <= T; j++) { // 遍历时间(代价)
            // 不采第i株草药
            dp[i][j] = dp[i-1][j];
            
            // 如果 j>=herbTime[i], 那么能够采第i株草药
            if (j >= herbTime[i]) {
                dp[i][j] = std::max(dp[i][j], dp[i-1][j-herbTime[i]]+herbValue[i]);
            }
        }
    }

    return dp[M][T];
}

int compute2(int T, int M, 
    const std::vector<int>& herbTime,
    const std::vector<int>& herbValue
) {
    // dp[i][j]:前i株草药中采药时间不多于j的最大价值
    std::vector<int> dp(T + 1, 0);

    // dp[i][j] = max(dp[i-1][j], 
    //              dp[i-1][j-herbTime[i]] + herbValue[i])
    for (int i = 1; i <= M; i++) { // 遍历每株草药
        for (int j = T; j >= herbTime[i]; j--) { // 遍历时间(代价)
            // 不采第i株草药, 就是dp[j]
            
            // 如果 j>=herbTime[i], 那么能够采第i株草药
            dp[j] = std::max(dp[j], dp[j-herbTime[i]]+herbValue[i]);
        }
    }

    return dp[T];
}

int main() {

    // t:采药的时间 m:山洞中草药的数量
    int T, M;
    std::cin >> T >> M;

    // herbTime:采某株草药的时间 herbValue:采某株草药的价值
    std::vector<int> herbTime(M + 1), herbValue(M + 1);

    // 读入
    for (int i = 1; i <= M; i++) {
        std::cin >> herbTime[i] >> herbValue[i];
    }

    // int ans1 = compute1(T, M, herbTime, herbValue);
    int ans2 = compute2(T, M, herbTime, herbValue);

    // 输出结果, 答案存在 dp[M][T]中
    std::cout << ans2 << std::endl;

    return 0;

}