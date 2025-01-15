//// 银行家舍入法（四舍六入五取偶、四舍六入五留双）
//
// 这是一种在金融计算中常用的取整方法，旨在减少连续舍入操作中的累积误差，使结果更加公平和中性。
// 这种方法由IEEE 754标准规定，并被大多数编程软件采用。

//// 银行家舍入法的规则
//
// 银行家舍入法的核心规则是：
// 当舍去位的数值小于5时，直接舍去。
// 当舍去位的数值大于5时，进位舍去。
// 当舍去位的数值等于5时，若5后面还有其他数字（非0），则进位后舍去；若5后面是0，则根据5前一位数的奇偶性来判断（奇进偶舍）。

//// 银行家舍入法的优势
//
// 与传统的四舍五入方法相比，银行家舍入法在平均数方面更能保持原有数据的特性，减少舍入操作带来的累计误差。
// 在大量计算中，传统的四舍五入方法可能会导致偏差，因为经常都是朝着一个方向舍入。
// 而银行家舍入法则通过在.5的情况下“均衡”舍入，从长远来看，向上和向下舍入的次数大致相同，从而减少了偏差。

//// 实际应用示例
//
// 在实际应用中，银行家舍入法的表现如下：
// 9.8249 舍入为 9.82
// 9.82671 舍入为 9.83
// 9.835 舍入为 9.84
// 9.8351 仍舍入为 9.84
// 9.825 舍入为 9.82
// 9.82501 舍入为 9.83


//// 编程中的体现
//
// Python：
// round() 函数就是采用的银行家舍入法，如果想要四舍五入，可以用下面的代码。
//     a1 = Decimal('1.125').quantize(Decimal('0.00'), rounding=ROUND_HALF_UP)
