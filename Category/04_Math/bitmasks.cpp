// 【从集合论到位运算，常见位运算技巧分类总结！】(https://leetcode.cn/circle/discuss/CaOJ45/)


// 一些结论：
// > x + y = (x | y) + (x & y)
// > (x ^ y) != (x + y) - 2 * (x & y)
// > a % 2^k = a & (2^k - 1)


// 枚举集合 s 的非空子集
for (int sub = s; sub; sub = (sub - 1) & s) {}
// 枚举集合 s 的所有子集
for (int sub = s; sub != s; sub = (sub - 1) & s) {}
// 枚举集合 s 的所有超集（全集内）
for (int sup = s; sup < (1 << n); sup = (sup + 1) | s) {}


//* Gosper's Hack
// 查找下一个置位数与 num 相等的数
int Gosper(int num) {
    int lb = num & -num;
    int x = num + lb;
    int y = (num ^ x) / lb >> 2;
    return x | y;
}


//* 连续四个数的异或值
// 4i ^ (4i+1) ^ (4i+2) ^ (4i+3) = 0
i64 get(i64 n) {
    if (n % 4 == 0) {
        return n;
    } else if (n % 4 == 1) {
        return 1;
    } else if (n % 4 == 2) {
        return n + 1;
    } else {
        return 0;
    }
}
