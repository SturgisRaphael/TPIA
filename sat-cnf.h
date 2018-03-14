//
// Created by raphael on 3/13/18.
//

#ifndef TPIA_SAT_CNF_H
#define TPIA_SAT_CNF_H

class satcnf {
public:
    bool isSatCnf();
private:
    clauses clauses1;
    clauses clauseUnit();
    int litteralPure();
};

class clauses {
public:
    bool isUnit();
    bool isSatified(int model[]);


private:
    int a;
    clauses next;

};
#endif //TPIA_SAT_CNF_H
