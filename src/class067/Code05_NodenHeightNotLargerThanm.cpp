// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 51;
const int mod = 1e9+7;
// 记忆化搜索
vector<vector<int>> dp1(maxn, vector<int>(maxn, -1));
// 严格位置依赖的动态规划
vector<vector<int>> dp2(maxn, vector<int>(maxn, 0));
// 空间压缩
vector<int> dp3(maxn);

// 二叉树节点数为n
// 高度不能超过m
// 结构数返回
// 记忆化搜索
int compute1(int n, int m) {
    if (n == 0) {
        return 1;
    }
    if (m == 0) {
        return 0;
    }
    if (dp1[n][m] != -1) {
        return dp1[n][m];
    }
    int ans = 0;
    // n个点，头占掉1个
    for (int k = 0; k < n; k++) {
        // 一共n个节点，头节点已经占用了1个名额
		// 如果左树占用k个，那么右树就占用i-k-1个
        ans = (ans + (compute1(k, m-1) * compute1(n-k-1, m-1)) % mod) % mod;
    }
    dp1[n][m] = ans;
    return ans;
}

int compute2(int n, int m) {
    for (int i = 0; i <= m; i++) {
        dp2[0][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 0; k < i; k++) {
                dp2[i][j] = (dp2[i][j] + (dp2[k][j-1] * dp2[i-k-1][j-1]) % mod) % mod;
            }
        }
    }
    return dp2[n][m];
}

int compute3(int n, int m) {
    dp3[0] = 1;
    for (int j = 1; j <= m; j++) {
        for (int i = n; i >= 1; i--) {
            dp3[i] = 0;
            for (int k = 0; k < i; k++) {
                dp3[i] = (dp3[i] + (dp3[k] * dp3[i-k-1]) % mod) % mod;
            }
        }
    }
    return dp3[n];
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;

    // // 方法一: 递归
    // compute1(n, m);
    // cout << dp1[n][m] << endl;

    // // 方法二: 严格位置依赖的动态规划
    // compute2(n, m);
    // cout << dp2[n][m] << endl;

    // 方法三: 空间压缩
    compute3(n, m);
    cout << dp3[n] << endl;

    return 0;
}