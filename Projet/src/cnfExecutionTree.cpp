//
// Created by Raphael on 3/23/2018.
//

#include "cnfExecutionTree.h"

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses) : literals(
        literals), clauses(clauses) {
    for(const clauseList& l: literals){
        this->literals.push_back(l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(c.copyLiteralList());
    }
}

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                                   const vector<int> &currentModel) : literals(literals), clauses(clauses),
                                                                      currentModel(currentModel) {
    for(const clauseList& l: literals){
        this->literals.push_back(l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(c.copyLiteralList());
    }
}

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                                   const vector<int> &currentModel, cnfExecutionTree *pred) : literals(literals),
                                                                                              clauses(clauses),
                                                                                              currentModel(
                                                                                                      currentModel),
                                                                                              pred(pred) {
    for(const clauseList& l: literals){
        this->literals.push_back(l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(c.copyLiteralList());
    }
}

vector<clauseList> &cnfExecutionTree::getLiterals(){
    return literals;
}

void cnfExecutionTree::setLiterals(const vector<clauseList> &literals) {
    cnfExecutionTree::literals = literals;
}

vector<literalList> &cnfExecutionTree::getClauses(){
    return clauses;
}

void cnfExecutionTree::setClauses(const vector<literalList> &clauses) {
    cnfExecutionTree::clauses = clauses;
}

const vector<int> &cnfExecutionTree::getCurrentModel() const {
    return currentModel;
}

void cnfExecutionTree::setCurrentModel(const vector<int> &currentModel) {
    cnfExecutionTree::currentModel = currentModel;
}

cnfExecutionTree *cnfExecutionTree::getLeft() const {
    return left;
}

void cnfExecutionTree::setLeft(cnfExecutionTree *left) {
    cnfExecutionTree::left = left;
}

cnfExecutionTree *cnfExecutionTree::getRight() const {
    return right;
}

void cnfExecutionTree::setRight(cnfExecutionTree *right) {
    cnfExecutionTree::right = right;
}

cnfExecutionTree *cnfExecutionTree::getPred() const {
    return pred;
}

void cnfExecutionTree::setPred(cnfExecutionTree *pred) {
    cnfExecutionTree::pred = pred;
}

std::ostream &operator<<(std::ostream &os, const cnfExecutionTree &tree) {
    os << "literals: [";

    for (auto literal : tree.literals) {
        os << literal;
    }
    os << "] clauses: [";
    for(auto clause :tree.clauses){
        os << clause;
    }
/*
    os << "] currentModel: " << tree.currentModel
       << " left: " << tree.left << " right: " << tree.right << " pred: " << tree.pred;
*/
    return os;
}
