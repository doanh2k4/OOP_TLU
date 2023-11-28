#include <iostream>

class Calculator 

{
private:

    int operand1;
    int operand2;

public:

    Calculator(int a, int b) : operand1(a), operand2(b) {}

    int add()
    {
        return operand1 + operand2;
    }
};

int main() 
{
    int A, B;

    std::cin >> A >> B;

    Calculator calculator(A, B);
    int sum = calculator.add();

    std::cout << sum << std::endl;

    return 0;
}
