//
// Created by Raphael on 3/23/2018.
//

#include "cnfExecutionTree.h"

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses){
    for(const clauseList& l: literals){
        this->literals.push_back(*l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(*c.copyLiteralList());
    }
}

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                                   const vector<int> &currentModel) : currentModel(currentModel) {
    for(const clauseList& l: literals){
        this->literals.push_back(*l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(*c.copyLiteralList());
    }
}

cnfExecutionTree::cnfExecutionTree(const vector<clauseList> &literals, const vector<literalList> &clauses,
                                   const vector<int> &currentModel, cnfExecutionTree *pred) : currentModel(
                                                                                                      currentModel),
                                                                                              pred(pred) {
    for(const clauseList& l: literals){
        this->literals.push_back(*l.copyClauseList());
    }

    for(const literalList& c: clauses){
        this->clauses.push_back(*c.copyLiteralList());
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

vector<int> &cnfExecutionTree::getCurrentModel() {
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
        os << "{" << literal << "}";
    }
    os << "] clauses: [";
    for(auto clause :tree.clauses){
        os << "{"  << clause << "}";
    }

    os << "] currentModel: [";

    for(auto model :tree.currentModel){
        os << model << " ";
    }

    os << "]" << endl;

    return os;
}

bool cnfExecutionTree::assignLiteral(int literal, int negLiteral) {
    //remove clauses with literal
    clauseList *currentClause = &this->getLiterals()[literal - 1];
    vector<int> clausesRemoved;
    while(currentClause != nullptr){
        int clause = currentClause->getClause();
        this->getClauses()[clause - 1].setLiteral(-1);
        this->getClauses()[clause - 1].setNext(nullptr);
        clausesRemoved.push_back(clause);

        currentClause = currentClause->getNext();
    }


    //remove from litteral list
    for(auto &i : clausesRemoved)
        for (auto &j : this->getLiterals())
            j.removeClause(i);

    this->getLiterals()[literal - 1].setNext(nullptr);
    this->getLiterals()[literal - 1].setClause(-1);

    //remove currentNegLiterals from all clauses
    if(this->getLiterals()[negLiteral - 1].getClause() > 0)//there are NegLiterals to remove
    {
        currentClause = &this->getLiterals()[negLiteral - 1];
        while (currentClause != nullptr) {
            this->getClauses()[currentClause->getClause() - 1].deleteLiteral(negLiteral);

            currentClause = currentClause->getNext();
        }
    }

    this->getLiterals()[negLiteral - 1].setNext(nullptr);
    this->getLiterals()[negLiteral - 1].setClause(-1);

    this->getCurrentModel().push_back(literal);

}

cnfExecutionTree::cnfExecutionTree() {

}
