//
// Created by Raphael on 4/10/2018.
//

#ifndef PROJETV2_0_CNF_H
#define PROJETV2_0_CNF_H


#include "linkedList.h"
#include "cnfExecutionTree.h"
#include <vector>
#include <ostream>

using namespace std;

class CNF {
private:
    vector<linkedList> literals;
    vector<linkedList> clauses;
    vector<vector<int>> solutions;
    int nbSolutionsFound = 0;

public:
    enum heuristic {NO, FIRST_SATISFY, FIRST_FAIL};

    CNF(const vector<linkedList> &literals, const vector<linkedList> &clauses);

    CNF();



    vector<linkedList> &getLiterals();

    void setLiterals(const vector<linkedList> &literals);

    vector<linkedList> &getClauses();

    void setClauses(const vector<linkedList> &clauses);

    const vector<vector<int>> &getSolutions() const;

    int getNbSolutionsFound() const;

    friend ostream &operator<<(ostream &os, const CNF &cnf);

    void solve();
    void solve(heuristic h);
    void solve(int nbSolution, heuristic h);

    static bool UnitPropagation(cnfExecutionTree *pTree);

    void generateProblemFile(string addr)const;
    void generateSolutionFile(string addr);

    void readFromFile(string addr);
};


#endif //PROJETV2_0_CNF_H
