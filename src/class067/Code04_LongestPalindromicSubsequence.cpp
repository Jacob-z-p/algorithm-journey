// 最长回文子序列
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度
// 测试链接 : https://leetcode.cn/problems/longest-palindromic-subsequence/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

class Solution {
public:
    int longestPalindromeSubseq1(string s) {
        int n = s.length();
        return f1(s, 0, n - 1);
    }
	// s[l...r]最长回文子序列长度
	// l <= r
    int f1(string s, int l, int r) {
        if (l == r) {
            return 1;
        }
        if (l + 1 == r) {
            return (s[l] == s[r] ? 2 : 1);
        }
        int ans = 0;
        if (s[l] == s[r]) {
            ans = 2 + f1(s, l + 1, r - 1);
        }
        else {
            ans  = max(f1(s, l, r - 1), f1(s, l + 1, r));
        }
        return ans;
    }

    int longestPalindromeSubseq2(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        return f2(s, 0, n - 1, dp);
    }
	// s[l...r]最长回文子序列长度
	// l <= r  => 正方形表,且只有一半
    int f2(string s, int l, int r, vector<vector<int>>& dp) {
        if (l == r) {
            return 1;
        }
        if (l + 1 == r) {
            return (s[l] == s[r] ? 2 : 1);
        }
        if (dp[l][r] != 0) {
            return dp[l][r];
        }
        int ans = 0;
        if (s[l] == s[r]) {
            ans = 2 + f2(s, l + 1, r - 1, dp);
        }
        else {
            ans  = max(f2(s, l, r - 1, dp), f2(s, l + 1, r, dp));
        }
        dp[l][r] = ans;
        return ans;
    }

    int longestPalindromeSubseq3(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int l = n - 1;  l >= 0; l--) {
            dp[l][l] = 1;
            if (l + 1 < n) {
                dp[l][l+1] = (s[l] == s[l+1] ? 2 : 1);
            }
            for (int r = l + 2; r < n; r++) {
                if (s[l] == s[r]) {
                    dp[l][r] = 2 + dp[l+1][r-1];
                }
                else {
                    dp[l][r] = max(dp[l][r-1], dp[l+1][r]);
                }
            }
        }
        return dp[0][n-1];
    }

    int longestPalindromeSubseq4(string s) {
        int n = s.length();
        vector<int> dp(n);
        for (int l = n - 1; l >= 0; l--) {
            // dp[l] : 想象中的dp[l][l]
            dp[l] = 1;
            if (l + 1 < n) {
                dp[l+1] = (s[l] == s[l+1] ? 2 : 1);
            }
            // 我对 leftDown 进行了改进，因为在第一次使用 leftDown 一定是 1
            int leftDown = 1, backDown; 
            for (int r = l + 2; r < n; r++) {
                backDown = dp[r];
                if (s[l] == s[r]) {
                    dp[r] = 2 + leftDown;
                }
                else {
                    dp[r] = max(dp[r-1], dp[r]);
                }
                leftDown = backDown;
            }
        }
        return dp[n-1];
    }


    // 扩展: 这个左程云老师代码没有, 但是这个经典的尝试
    // 就是求 s 的逆序串 s'
    // s串的最长回文子序列就是 s与s'的最长公共子序列
    int longestPalindromeSubseq5(string s) {
        string s_rev(s.rbegin(), s.rend());
        return longestCommonSubsequence(s, s_rev);
    }
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.length() < text2.length()) {
            swap(text1, text2);
        }
        int n = text1.length();
        int m = text2.length();
        vector<int> dp(m+1);
        for (int len1 = 1; len1 <= n; len1++) {
            int leftUp = 0, backUp;
            for (int len2 = 1; len2 <= m; len2++) {
                backUp = dp[len2];
                if (text1[len1-1] == text2[len2-1]) {
                    dp[len2] = leftUp + 1;
                }
                else {
                    dp[len2] = max(dp[len2-1], dp[len2]);
                }
                leftUp = backUp;
            }
        }
        return dp[m];
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}