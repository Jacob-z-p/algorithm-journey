// 单词搜索（无法改成动态规划）
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word
// 如果 word 存在于网格中，返回 true ；否则，返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成
// 其中"相邻"单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母不允许被重复使用
// 测试链接 : https://leetcode.cn/problems/word-search/

#include <bits/stdc++.h>
using namespace std;
#define int long long

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int xlen = board.size();
        int ylen = board[0].size();

        for (int i = 0; i < xlen; i++) {
            for (int j = 0; j < ylen; j++) {
                if (check(board, i, j, word, 0)) {
                    return true;
                }
            }
        }

        return false;
    }

    // 因为board会改其中的字符
	// 用来标记哪些字符无法再用
	// 带路径的递归无法改成动态规划或者说没必要
	// 从(i,j)出发，来到w[k]，请问后续能不能把word走出来w[k...]
    bool check(vector<vector<char>>& board, int i, int j, string word, int k) {
        if (k == word.length()) {
            return true;
        }
        if (i<0 || i==board.size() || j<0 || j==board[0].size() || word[k]!=board[i][j]) {
            return false;
        }
        // 不越界，board[i][j] == word[k]
        char tmp = board[i][j];
        board[i][j] = 0;

        bool ans = check(board, i-1, j, word, k+1)
                || check(board, i+1, j, word, k+1)
                || check(board, i, j-1, word, k+1)
                || check(board, i, j+1, word, k+1);

        board[i][j] = tmp;

        return ans;
    }
};