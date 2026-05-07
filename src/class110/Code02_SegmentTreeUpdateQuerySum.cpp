// 线段树支持范围重置、范围查询
// 维护累加和
// 对数器验证
// 当你写线段树出错了，就需要用对数器的方式来排查
// 所以本题选择对数器验证，来展示一下怎么写测试
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 100000;
int arr[maxn + 5];
int sum[maxn * 4 + 5];
int change[maxn * 4 + 5];
bool update[maxn * 4 + 5];

void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    return;
}

void lazy(int i, int v, int n) {
    sum[i] = v * n; // 因为是区间每个数更新成v,所以是 v * n
    change[i] = v;
    update[i] = true;
    return;
}

void down(int i, int ln, int rn) {
    if (update[i]) {
        lazy(i << 1, change[i], ln);
        lazy(i << 1 | 1, change[i], rn);
        update[i] = false;
    }
    return;
}

void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    change[i] = 0;
    update[i] = false;
    return;
}

void Update(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) {
            Update(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (mid < jobr) {
            Update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
    return;
}

int Query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid) {
        ans += Query(jobl, jobr, l, mid, i << 1);
    }
    if (mid < jobr) {
        ans += Query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

void randomArray(int n, int v) {
    for (int i = 1; i <= n; i++) {
        // 生成[0, v)范围内的随机整数
        arr[i] = rand() % v;
    }
    return;
}

// 验证结构的更新
// 暴力更新
// 为了验证
void checkUpdate(int check[], int jobl, int jobr, int jobv) {
    for (int i = jobl; i <= jobr; i++) {
        check[i] = jobv;
    }
}

// 验证结构的查询
// 暴力查询
// 为了验证
int checkQuery(int check[], int jobl, int jobr) {
    int ans = 0;
    for (int i = jobl; i <= jobr; i++) {
        ans += check[i];
    }
    return ans;
}

// 对数器逻辑
// 展示了线段树的建立和使用
// 使用验证结构来检查线段树是否正常工作
int32_t main() {
    system("chcp 65001");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // 初始化随机数种子，只需执行一次
    srand((unsigned)time(NULL));

    cout << "测试开始" << endl;
    int n = 1000;
    int v = 2000;
    int t = 5000000;
    // 生成随机值填入arr数组
    randomArray(n, v);
    // 建立线段树
    build(1, n, 1);
    // 生成验证的结构
    int check[n + 1];
    for (int i = 1; i <= n; i++) {
        check[i] = arr[i];
    }
    for (int i = 1; i <= t; i++) {
        // 生成操作类型
        // op = 0 更新操作
        // op = 1 查询操作
        int op = (int) (rand() % 2);
        // 下标从1开始，不从0开始，生成两个随机下标
        int a = (int) (rand() % n) + 1;
        int b = (int) (rand() % n) + 1;
        // 确保 jobl <= jobr
        int jobl = min(a, b);
        int jobr = max(a, b);
        if (op == 0) {
            // 更新操作
            // 线段树、验证结构同步更新
            int jobv = (int) (rand() % v * 2) - v;
            Update(jobl, jobr, jobv, 1, n, 1);
            checkUpdate(check, jobl, jobr, jobv);
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