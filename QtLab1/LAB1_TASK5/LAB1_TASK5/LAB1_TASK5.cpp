struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression() {};
};

struct Number : Expression
{

    Number(double value) : value(value) {}
    ~Number() {};
    double evaluate() { return value; }
    virtual double evaluate() const { return value; }


private:
    double value;
};

struct BinaryOperation : Expression
{
         
    BinaryOperation(Expression const* left, char sim, Expression const* right)
        : left(left), sim(sim), right(right)
    { }
    ~BinaryOperation() {
        delete left;
        delete right;
    }

    virtual double evaluate() const {

        if (sim == '+') {
            return (left->evaluate() + right->evaluate());
        }
        else if (sim == '-') {
            return (left->evaluate() - right->evaluate());
        }
        else if (sim == '*') {
            return (left->evaluate() * right->evaluate());
        }
        else if (sim == '/') {
            return (left->evaluate() / right->evaluate());
        }

    }

private:
    Expression const* left;
    Expression const* right;
    char sim;
};
bool check_equals(Expression const* left, Expression const* right)
{
    return (*((size_t*)left) == *((size_t*)right));
}
int main()
{}