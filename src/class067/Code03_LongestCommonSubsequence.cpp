// 最长公共子序列
// 给定两个字符串text1和text2
// 返回这两个字符串的最长 公共子序列 的长度
// 如果不存在公共子序列，返回0
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
// 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/

#include <bits/stdc++.h>
using namespace std;
#define int long long

class Solution {
public:
    int longestCommonSubsequence1(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        return f1(text1, text2, n-1, m-1);
    }

    // s1[0....i1]与s2[0....i2]最长公共子序列长度
    int f1(string text1, string text2, int i1, int i2) {
        if (i1 < 0 || i2 < 0) {
            return 0;
        }
        int p1 = f1(text1, text2, i1-1, i2-1);
        int p2 = f1(text1, text2, i1-1, i2);
        int p3 = f1(text1, text2, i1, i2-1);
        int p4 = (text1[i1] == text2[i2] ? p1+1 : 0);
        return max(max(p1, p2), max(p3, p4));
    }

	// 为了避免很多边界讨论
	// 很多时候往往不用下标来定义尝试，而是用长度来定义尝试
	// 因为长度最短是0，而下标越界的话讨论起来就比较麻烦
    int longestCommonSubsequence2(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        return f2(text1, text2, n, m);
    }

    int f2(string text1, string text2, int len1, int len2) {
        if (len1 == 0 || len2 == 0) {
            return 0;
        }
        int ans = 0;
        if (text1[len1-1] == text2[len2-1]) {
            ans = f2(text1, text2, len1-1, len2-1) + 1;
        }
        else {
            ans = max(f2(text1, text2, len1-1, len2), f2(text1, text2, len1, len2-1));
        }
        return ans;
    }

    // 记忆化搜索
    int longestCommonSubsequence3(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return f3(text1, text2, n, m, dp);
    }
    int f3(string text1, string text2, int len1, int len2, vector<vector<int>>& dp) {
        if (len1 == 0 || len2 == 0) {
            return 0;
        }
        if (dp[len1][len2] != -1) return dp[len1][len2]; 
        int ans = 0;
        if (text1[len1-1] == text2[len2-1]) {
            ans = f3(text1, text2, len1-1, len2-1, dp) + 1;
        }
        else {
            ans = max(f3(text1, text2, len1-1, len2, dp), f3(text1, text2, len1, len2-1, dp));
        }
        dp[len1][len2] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划
    int longestCommonSubsequence4(string text1, string text2) {
        int n = text1.length();
        int m = text2.length();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for (int len1 = 1; len1 <= n; len1++) {
            for (int len2 = 1; len2 <= m; len2++) {
                if (text1[len1-1] == text2[len2-1]) {
                    dp[len1][len2] = dp[len1-1][len2-1] + 1;
                }
                else {
                    dp[len1][len2] = max(dp[len1-1][len2], dp[len1][len2-1]);
                }
            }
        }
        return dp[n][m];
    } 

    // 严格位置依赖的动态规划 + 空间压缩
    int longestCommonSubsequence5(string text1, string text2) {
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