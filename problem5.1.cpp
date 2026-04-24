#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    stack<char> operators;
    vector<int> postfix;
    int sum = 0;

public:

    void evaluate(const string& infix_input) {
        while (!operators.empty()) operators.pop();
        postfix.clear();

        int size = static_cast<int>(infix_input.size());
        infixToPostfix(infix_input, size);

        stack<int> numbers;

        for (int token : postfix) {
            if (token == -1) {
                const int right = numbers.top(); numbers.pop();
                const int left = numbers.top(); numbers.pop();
                numbers.push(left + right);
            }
            else if (token == -2) {
                const int right = numbers.top(); numbers.pop();
                const int left = numbers.top(); numbers.pop();
                numbers.push(left - right);
            }
            else {
                numbers.push(token);
            }
        }

        sum = numbers.top();
        print(sum);
    }

    void infixToPostfix(const string& infix_input, int& size) {
        for (int i = 0; i < size; i++) {
            char c = infix_input[i];

            if (c == ' ') continue;

            if (c == '(') {
                operators.push(c);
            }
            else if (c == ')') {
                while (operators.top() != '(') {
                    if (operators.top() == '+') postfix.push_back(-1);
                    else if (operators.top() == '-') postfix.push_back(-2);
                    operators.pop();
                }
                operators.pop();
            }
            else if (c == '+' || c == '-') {
                bool isUnary = postfix.empty() && operators.empty();
                if (!isUnary && !operators.empty())
                    isUnary = operators.top() == '(';

                if (isUnary && c == '-') {
                    postfix.push_back(0);
                    operators.push(c);
                    continue;
                }

                while (!operators.empty() && (operators.top() == '+' || operators.top() == '-')) {
                    if (operators.top() == '+') postfix.push_back(-1);
                    else postfix.push_back(-2);
                    operators.pop();
                }
                operators.push(c);
            }
            else if (isdigit(c)) {
                int number = c - '0';
                while (i + 1 < size && isdigit(infix_input[i + 1])) {
                    number = number * 10 + (infix_input[++i] - '0');
                }
                postfix.push_back(number);
            }
        }

        while (!operators.empty()) {
            if (operators.top() == '+') postfix.push_back(-1);
            else if (operators.top() == '-') postfix.push_back(-2);
            operators.pop();
        }
    }

    void print(const int& sum) const{
        cout << sum << endl;
    }
};

int main() {
    Solution s;

    s.evaluate("2 + 3");
    s.evaluate("10 - 4 + 2");
    s.evaluate("(2 + 3) - 1");
    s.evaluate("100 + 200");
    s.evaluate(" -(2 + 2) + 10");

    return 0;
}
