// https://blog.csdn.net/2301_76848549/article/details/138108995?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22138108995%22%2C%22source%22%3A%222301_76848549%22%7D
// * Clearer specification
// For an array \{a_i\} of positive numbers, and a positive number t,
// find the smallest number v, which satisifies
// \[ \sum_i \lceil a_i / v \rceil \le t \]
// * Solution
// Let's loosen the condition:
// $ \sum \lceil a_i / v \rceil \le t $ and $ \sum (a_i / (v - 1) + 1) \lt t $.
//
// Maybe we can maintain the remainders.
// No, just directly find when is the resulting ceiling sum going to increment.
// Maybe bisection can be used in the worst situation of estimation.
