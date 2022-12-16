//
// Created by ghuno on 2022-05-05.
//

#ifndef TESTER_GEN_NUMBER_H
#define TESTER_GEN_NUMBER_H
class extended_int {
    struct node{
        *node next;
        unsigned int value;
    };
    // it could handle more
    // if int* --> at overflow, creates a 2 big array, and the second int acts as a node, or just unsigned int
    node* initn;
    int basen;
    extended_int();
    ~extended_int();
    //=, +, -, *, /, %,
    //logic ones?
}

/// big float : two int (extended one?)
/// big fix point : two extended int;

class gen_number {
    ///all the different representation
    /// classic int
    /// expended int
    ///classic fix point
    /// float
    /// ratio
    /// multiple float sum
    /// multiplicant

};

class Fraction
{
private:
    int num, den;
public:
    Fraction(int n, int d) { num = n; den = d; }

    // Conversion operator: return float value of fraction
    operator float() const {
        return float(num) / float(den);
    }
};


#endif //TESTER_GEN_NUMBER_H
