// 线段树支持范围增加、范围查询
// 维护最大值
// 对数器验证
// 当你写线段树出错了，就需要用对数器的方式来排查
// 所以本题选择对数器验证，来展示一下怎么写测试

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 100000;
int arr[maxn + 5];
int max_num[maxn * 4 + 5];
int add_num[maxn * 4 + 5];

void up(int i) {
    max_num[i] = max(max_num[i << 1], max_num[i << 1 | 1]);
    return;
}

void lazy(int i, int v) {
    max_num[i] += v; // 因为区间每个数加v, 等价于最大值也加v
    add_num[i] += v;
    return;
}

void down(int i) {
    if (add_num[i] != 0) {
        lazy(i << 1, add_num[i]);
        lazy (i << 1 | 1, add_num[i]);
        add_num[i] = 0;
    }
    return;
}

void build(int l, int r, int i) {
    if (l == r) {
        max_num[i] = arr[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    add_num[i] = 0;
    return;
}

void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv);
    }
    else {
        down(i);
        int mid = (l + r) >> 1;
        if (jobl <= mid) {
            Add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (mid < jobr) {
            Add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
    return;
}

int Query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return max_num[i];
    }
    down(i);
    int mid = (l + r) >> 1;
    int ans = numeric_limits<int>::min();
    if (jobl <= mid) {
        ans = max(ans, Query(jobl, jobr, l, mid, i << 1));
    }
    if (mid < jobr) {
        ans = max(ans, Query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
}

// 生成随机值填入arr数组
// 为了验证
void randomArray(int n, int v) {
    for (int i = 1; i <= n; i++) {
        arr[i] = rand() % v;
    }
    return;
}

// 验证结构的增加
// 暴力增加
// 为了验证
void checkAdd(int check[], int jobl, int jobr, int jobv) {
    for (int i = jobl; i <= jobr; i++) {
        check[i] += jobv;
    }
    return;
}

// 验证结构的查询
// 暴力查询
// 为了验证
int checkQuery(int check[], int jobl, int jobr) {
    int ans = numeric_limits<int>::min();
    for (int i = jobl; i <= jobr; i++) {
        ans = max(ans, check[i]);
    }
    return ans;
}

int32_t main() {
    system("chcp 65001");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << "测试开始" << endl;
    int n = 1000;
    int v = 2000;
    int t = 5000000;
    // 生成随机值填入arr数组
    randomArray(n, v);
    // 建立线段树
    build(1, n, 1);
    // 生成验证结构
    int check[n + 1];
    for (int i = 1; i <= n; i++) {
        check[i] = arr[i];
    }
    for (int i = 1; i <= t; i++) {
        // 生成操作类型
        // op = 0 增加操作
        // op = 1 查询操作
        int op = (int) (rand() % 2);
        // 下标从1开始, 不从0开始, 生成两个随机下标
        int a = (int) (rand() % n) + 1;
        int b = (int) (rand() % n) + 1;
        // 确保 jobl <= jobr
        int jobl = min(a, b);
        int jobr = min(a, b);
        if (op == 0) {
            // 增加操作
            // 线段树、验证结构同步增加
            int jobv = (int) (rand() % v * 2) - v;
            Add(jobl, jobr, jobv, 1, n, 1);
            checkAdd(check, jobl, jobr, jobv);
        }
        else {
            // 查询操作
            // 线段树、验证结构同步查询
            // 比对答案
            int ans1 = Query(jobl, jobr, 1, n, 1);
            int ans2 = checkQuery(check, jobl, jobr);
            if (ans1 != ans2) {
                cout << "出错了!" << endl;
            }
        }
    }
    cout << "测试结束" << endl;
    return 0;
}