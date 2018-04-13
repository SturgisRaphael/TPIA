//
// Created by Raphael on 4/10/2018.
//

#ifndef PROJETV2_0_CNFEXECUTIONTREE_H
#define PROJETV2_0_CNFEXECUTIONTREE_H


#include "linkedList.h"
#include "CNF.h"
#include <vector>
#include <ostream>

using namespace std;

class cnfExecutionTree {
private:
    vector<linkedList> literals;
    vector<linkedList> clauses;
    vector<int> currentModel;
    cnfExecutionTree *left = nullptr, *right = nullptr, *pred;


public:
    cnfExecutionTree();
    bool UnitPropagation();
    cnfExecutionTree(const vector<linkedList> &literals, const vector<linkedList> &clauses);

    cnfExecutionTree(vector<linkedList> &literals, vector<linkedList> &clauses,
                     vector<int> &currentModel);

    vector<linkedList> &getLiterals();

    void setLiterals(const vector<linkedList> &literals);

    vector<linkedList> &getClauses();

    void setClauses(const vector<linkedList> &clauses);

    vector<int> &getCurrentModel();

    void setCurrentModel(const vector<int> &currentModel);

    cnfExecutionTree *getLeft() const;

    void setLeft(cnfExecutionTree *left);

    cnfExecutionTree *getRight() const;

    void setRight(cnfExecutionTree *right);

    cnfExecutionTree *getPred() const;

    void setPred(cnfExecutionTree *pred);

    int noHeuristic();

    int firstSatisfyHeuristic();

    bool assignLiteral(int literal);

    friend ostream &operator<<(ostream &os, const cnfExecutionTree &tree);

    bool isPureLiteral(int i);
};


#endif //PROJETV2_0_CNFEXECUTIONTREE_H
