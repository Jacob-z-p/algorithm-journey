// 线段树支持范围增加、范围查询
// 维护累加和
// 测试链接 : https://www.luogu.com.cn/problem/P3372
// 题目的数据范围 1≤n,m≤10^5, ai,k为正数, 且任意时刻数列的和不超过2*10^18

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 100000;
int arr[maxn + 5];
int sum[maxn * 4 + 5];
int add[maxn * 4 + 5];

// 累加和信息的汇总
void up(int i) {
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    return;
}

// 当前来到l~r范围，对应的信息下标是i，范围上数字的个数是n = r-l+1
// 现在收到一个懒更新任务 : l~r范围上每个数字增加v
// 这个懒更新任务有可能是任务范围把当前线段树范围全覆盖导致的
// 也有可能是父范围的懒信息下发下来的
// 总之把线段树当前范围的sum数组和add数组调整好
// 就不再继续往下下发了，懒住了
void lazy(int i, int v, int n) {
    sum[i] += (v * n);
    add[i] += v;
    return;
}

// 懒信息的下发
void down(int i, int ln, int rn) {
    if (add[i] != 0) {
        // 发左
        lazy(i << 1, add[i], ln);
        // 发右
        lazy(i << 1 | 1, add[i], rn);
        // 父范围懒信息清空
        add[i] = 0;
    }
    return;
}

// 建树
void build(int l, int r, int i) {
    if (l == r) {
        sum[i] = arr[l];
    }
    else {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid+1, r, i << 1 | 1);
        up(i);
    }
    add[i] = 0;
    return;
}

// 范围修改
// jobl ~ jobr范围上每个数字增加jobv
void Add(int jobl, int jobr, int jobv, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        lazy(i, jobv, r - l + 1);
    }
    else {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
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

// 查询累加和
int query(int jobl, int jobr, int l, int r, int i) {
    if (jobl <= l && r <= jobr) {
        return sum[i];
    }
    int mid = (l + r) >> 1;
    down(i, mid - l + 1, r - mid);
    int ans = 0;
    if (jobl <= mid) {
        ans += query(jobl, jobr, l, mid, i << 1);
    }
    if (mid < jobr) {
        ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
    }
    return ans;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    build(1, n, 1);
    for (int i = 1, op, jobl, jobr, jobv; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            cin >> jobl >> jobr >> jobv;
            Add(jobl, jobr, jobv, 1, n, 1);
        }
        else {
            cin >> jobl >> jobr;
            cout << query(jobl, jobr, 1, n, 1) << endl;
        }
    }

    return 0;
}