#include <iostream>
#include <stack>

// Hàm đổi số thập phân sang cơ số nhị phân
void decimal_to_binary(int decimal) {
    std::stack<int> binary_stack;

    while (decimal > 0) {
        binary_stack.push(decimal % 2);
        decimal /= 2;
    }

    std::cout << "Binary equivalent: ";
    while (!binary_stack.empty()) {
        std::cout << binary_stack.top();
        binary_stack.pop();
    }
    std::cout << std::endl;
}

int main() {
    int decimal_number;
    std::cout << "Enter a decimal number: ";
    std::cin >> decimal_number;

    decimal_to_binary(decimal_number);

    return 0;
}
