// 通过图中所有边恰好一次且行遍所有顶点的通路称为欧拉通路(一笔画完图中全部边，画的顺序就是一个可行解);
// 欧拉路径起点与终点相同时，则称为欧拉回路；
// 具有欧拉回路的无向图称为欧拉图；
// 具有欧拉通路但不具有欧拉回路的无向图称为半欧拉图。

// 有向图欧拉路径存在判定：
// > 恰有一个点出度比入度多 1（为起点）
// > 恰有一个点入度比出度多 1（为终点）
// > 恰有 N-2 个点入度等于出度
// 如果是欧拉回路，则所有点入度都等于出度。

// Hierholzer 算法用于在连通图中寻找欧拉路径，其流程如下：
//
// 从起点出发，进行 DFS。每次沿着某条边从某个顶点移动到另外一个顶点的时候，都需要删除这条边。
// 如果没有可移动的路径，则将所在节点加入到栈中，并返回。
//
// 当我们顺序地考虑该问题时，我们也许很难解决该问题，因为我们无法判断当前节点的哪一个分支是「死胡同」分支。不妨倒过来思考。
// 注意到只有那个入度与出度差为 1 的节点会导致死胡同，而该节点必然是最后一个遍历到的节点。
// 我们可以改变入栈的规则，当我们遍历完一个节点所连的所有节点后，我们才将该节点入栈（即逆序入栈）。
// 对于当前节点而言，从它的每一个非「死胡同」分支出发进行 DFS，都将会搜回到当前节点。而从它的「死胡同」分支出发进行 DFS 将
// 不会搜回到当前节点。也就是说当前节点的死胡同分支将会优先于其他非「死胡同」分支入栈。
// 这样就能保证我们可以「一笔画」地走完所有边，最终的栈中逆序地保存了「一笔画」的结果。我们只要将栈中的内容反转，即可得到答案。


// 无向图欧拉路径存在判定：
// > 恰有两个点度数为奇数（为起点与终点）
// > 恰有 N-2 个点度数为偶数
// 如果是欧拉回路，则没有奇数度数的顶点。
