//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_CNF_H
#define PROJET_CNF_H


#include "literalList.h"
#include "clauseList.h"
#include "cnfExecutionTree.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Generator {

public:
static void GenereFile (int nbClauses, int nbLiterals);

};

class CNF {
private:
    vector<clauseList> literals;
    vector<literalList> clauses;
    vector<vector<int>> solutions;
    int nbSolutionsFound;

public:
    enum heuristic {NO, FIRST_SATISFY, FIRST_FAIL};
    CNF(const vector<clauseList> &literals, const vector<literalList> &clauses);

    const vector<clauseList> &getLiterals() const;

    void setLiterals(const vector<clauseList> &literals);

    const vector<literalList> &getClauses() const;

    void setClauses(const vector<literalList> &clauses);

    const vector<vector<int>> &getSolutions() const;

    void setSolutions(const vector<vector<int>> &solutions);

    int getNbSolutionsFound() const;

    void setNbSolutionsFound(int nbSolutionsFound);

    static void readFromFile(string addr);
    void solve();
    void solve(heuristic h);
    void solve(int nbSolution, heuristic h);

    static bool UnitPropagation(cnfExecutionTree *pTree);
};


#endif //PROJET_CNF_H
