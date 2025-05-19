#include <iostream>

class Expression {
   public:
    virtual double evaluate() const = 0;
};

class Number : public Expression {
    double value_;

   public:
    Number(double value) { value_ = value; }
    double evaluate() const override { return value_; }
};

class BinaryOperation : public Expression {
    Expression* left_;
    Expression* right_;
    char oper_;

   public:
    BinaryOperation(Expression* left, char oper, Expression* right) {
        left_ = left;
        oper_ = oper;
        right_ = right;
    }

    ~BinaryOperation() {
        delete left_;
        delete right_;
    }

    double evaluate() const override {

        switch (oper_) {
            case '*':
                return left_->evaluate() * right_->evaluate();
            case '+':
                return left_->evaluate() + right_->evaluate();
            case '-':
                return left_->evaluate() - right_->evaluate();
            case '/':
                return left_->evaluate() / right_->evaluate();
            default:
                return -1;
        }
    }
};


int main() {
    Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
    Expression* expr = new BinaryOperation(new Number(3), '+', sube);

    std::cout << expr->evaluate() << std::endl;

    delete expr;

    return 0;
}
