//
// Created by Raphael on 3/23/2018.
//

#ifndef PROJET_CNFEXECUTIONTREE_H
#define PROJET_CNFEXECUTIONTREE_H


#include "clauseList.h"
#include "literalList.h"
#include <vector>
#include <ostream>

using namespace std;

class cnfExecutionTree {
private:
    vector<clauseList> literals;
    vector<literalList> clauses;
    vector<int> currentModel;
    cnfExecutionTree *left = nullptr, *right = nullptr, *pred;


public:
    cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses);

    cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                     const vector<int> &currentModel);

    cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                     const vector<int> &currentModel, cnfExecutionTree *pred);

    vector<clauseList> &getLiterals();

    void setLiterals(const vector<clauseList> &literals);

    vector<literalList> &getClauses();

    void setClauses(const vector<literalList> &clauses);

    vector<int> &getCurrentModel();

    void setCurrentModel(const vector<int> &currentModel);

    cnfExecutionTree *getLeft() const;

    void setLeft(cnfExecutionTree *left);

    cnfExecutionTree *getRight() const;

    void setRight(cnfExecutionTree *right);

    cnfExecutionTree *getPred() const;

    void setPred(cnfExecutionTree *pred);

    friend std::ostream &operator<<(std::ostream &os, const cnfExecutionTree &tree);
};


#endif //PROJET_CNFEXECUTIONTREE_H
