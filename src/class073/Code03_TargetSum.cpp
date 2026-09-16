// 目标和
// 给你一个非负整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数
// 可以构造一个表达式
// 例如nums=[2, 1]，可以在2之前添加'+' ，在1之前添加'-'
// 然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的，运算结果等于 target 的不同表达式的数目
// 测试链接 : https://leetcode.cn/problems/target-sum/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {

        // n:nums的个数
        int n = nums.size();

        // 求nums的和
        int numsSum = 0;
        for (auto num: nums) { 
            numsSum += num; 
        }

        // 剪枝1: -abs(target) <= nums_sum <= abs(target)
        if (target < -numsSum || target > numsSum) {
            return 0;
        }

        // 剪枝2: nums_sum 与 target 的奇偶性应该是相同的
        if (abs(numsSum % 2) != abs(target % 2)) {
            return 0;
        }

        // 把正数放到集合sumA中,负数(对应的相反数)放到集合sumB中
        // 有 sumA-sumB=target
        //  => (sumA-sumB)+(sumA+sumB)=target+numsSum
        //  => 2*sumA=target+numsSum
        //  => sumA = (target+numsSum)/2

        // 剪枝3:target+numsSum必须是个偶数
        //  哦哦,突然发现,其实剪枝2能推出剪枝3
        if ((target + numsSum) % 2) {
            return 0;
        }

        // 现在问题等价于:
        //  在nums中选出一些数求和恰好为(target+numsSum)/2的可能数
        //  01背包问题:
        //    dp[i][j]:在前i个数中和为j的可能数
        //    dp[i][j]=(dp[i-1][j])+(dp[i-1][j-nums[i]])

        // 新目标
        int new_target = (target + numsSum) / 2;
        
        vector<int> dp(new_target + 1, 0);

        // 如果选0个数和为0的可能性有1种,就是空集
        dp[0] = 1;

        // 01背包模板
        for (int i = 0; i < n; i++) {
            for (int j = new_target; j >= nums[i]; j--) {
                dp[j] = dp[j] + dp[j-nums[i]];
            }
        }

        return dp[new_target];
    }
};