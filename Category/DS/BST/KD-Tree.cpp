// KD-Tree 是一种高效处理 k 维空间信息的数据结构，维护 k 维空间 n 个点的信息，是一棵平衡二叉树。
// 树上的每个节点对应 k 维空间的一个点。
// 在结点数 n 远大于 2^k 时，应用 k-D Tree 的时间效率很好。

// 交替建树：
// 1. 选择切割维度：交替选择垂直 x 轴和垂直 y 轴方向切割平面。
// 2. 选择切割点：每次选择该维度上的中位数作为切割点。
// 3. 递归切割平面子区域，直到区域内没有点。

// 主要用于多维空间关键数据的搜索：
// 1. 最临近搜索：找出在树中与目标点最接近的点。
// 2. 范围搜索：找出所有位于给定区域中的点。


// 参考链接：
// https://www.luogu.com/article/cod5s33o
