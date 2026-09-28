// https://leetcode.cn/problems/valid-parentheses/?envType=study-plan-v2&envId=top-100-liked
class Solution {
    public boolean isValid(String s) {
        Stack<Character> stack = new Stack<>();
        for (int i = 0; i < s.length(); ++i) { // int? yes
            char c = s.charAt(i);
            if (stack.empty() || !match(stack.peek(), c)) {
                if (c == '(' || c == '[' || c == '{')
                    stack.push(c);
                else
                    return false;
            }
            else
                stack.pop();
        }
        return stack.empty();
    }
    public boolean match(char lhs, char rhs) {
        return lhs == '(' && rhs == ')'
            || lhs == '[' && rhs == ']'
            || lhs == '{' && rhs == '}';
    }
}
