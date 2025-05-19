#include <iostream>

class Expression {
   public:
    virtual double evaluate() const = 0;
};

class Number : public Expression {
   private:
    double value_;

   public:
    Number(double value) {
        value_ = value;
    }
    double evaluate() const override {
        return value_;
    }
};

class BinaryOperation : public Expression {
   private:
    Expression* left_;
    Expression* right_;
    char operation_;

   public:
    BinaryOperation(Expression* left, char operation, Expression* right)
       {
        left_= left, right_ = right, operation_ = operation;
       }

    ~BinaryOperation() {
        delete left_;
        delete right_;
    }

    double evaluate() const override {
        double left_value = left_->evaluate();
        double right_value = right_->evaluate();
        switch (operation_) {
            case '+':
                return left_value + right_value;
            case '-':
                return left_value - right_value;
            case '*':
                return left_value * right_value;
            case '/':
                return left_value / right_value;
            default:
                return -1;
        }
    }
};


bool check_equals(Expression const* leftNumber, Expression const* rightNumber) {
    return *(double**)leftNumber == *(double**)rightNumber;
}


int main() {
    Expression* n1 = new Number(69);
    Expression* n2 = new Number(96);
    Expression* a = new BinaryOperation(n1, '+', n2);
    Expression* b = new BinaryOperation(n1, '*', n2);

    std::cout << (check_equals(a, b) ? "Равны\n" : "Не равны\n");
    std::cout << (check_equals(n1, b) ? "Равны\n" : "Не равны\n");

    return 0;
}
