//
// Created by Raphael on 4/10/2018.
//

#include <iostream>
#include "cnfExecutionTree.h"

cnfExecutionTree::cnfExecutionTree(const vector<linkedList> &literals, const vector<linkedList> &clauses) : literals(
        literals), clauses(clauses) {}

cnfExecutionTree::cnfExecutionTree() {}

vector<linkedList> &cnfExecutionTree::getLiterals(){
    return literals;
}

void cnfExecutionTree::setLiterals(const vector<linkedList> &literals) {
    cnfExecutionTree::literals = literals;
}

vector<linkedList> &cnfExecutionTree::getClauses(){
    return clauses;
}

void cnfExecutionTree::setClauses(const vector<linkedList> &clauses) {
    cnfExecutionTree::clauses = clauses;
}

vector<int> &cnfExecutionTree::getCurrentModel(){
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

ostream &operator<<(ostream &os, const cnfExecutionTree &tree) {
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

bool cnfExecutionTree::assignLiteral(int literal) {

    int negLiteral = CNF::negationOfVariable(literal);
    //remove clauses with literal
    linkedList *currentClause = &this->getLiterals()[literal - 1];
    vector<int> clausesRemoved;
    while(currentClause != nullptr && currentClause->getElement() != -1){
        int clause = currentClause->getElement();
        this->getClauses()[clause - 1].deleteList();
        clausesRemoved.push_back(clause);

        currentClause = currentClause->getNext();
    }


    //remove from litteral list
    for(auto &i : clausesRemoved)
        for (auto &j : this->getLiterals())
            j.deleteElement(i);

    this->getLiterals()[literal - 1].deleteList();

    //remove currentNegLiterals from all clauses
    if(this->getLiterals()[negLiteral - 1].getElement() > 0)//there are NegLiterals to remove
    {
        currentClause = &this->getLiterals()[negLiteral - 1];
        while (currentClause != nullptr && currentClause->getElement() != -1) {
            this->getClauses()[currentClause->getElement() - 1].deleteElement(negLiteral);

            currentClause = currentClause->getNext();
        }
    }

    this->getLiterals()[negLiteral - 1].deleteList();

    this->getCurrentModel().push_back(literal);

}

cnfExecutionTree::cnfExecutionTree( vector<linkedList> &literals, vector<linkedList> &clauses,
                                   vector<int> &currentModel) {
    for (auto literal : literals) {
        this->literals.push_back(literal.copy());
    }
    for (auto clause : clauses) {
        this->clauses.push_back(clause.copy());
    }
    for (int i : currentModel) {
        this->currentModel.push_back(i);
    }
}
/*
cnfExecutionTree::cnfExecutionTree(CNF cnf) {
    this->literals = cnf.getLiterals();
    this->clauses = cnf.getClauses();
}*/

bool cnfExecutionTree::UnitPropagation() {
    cnfExecutionTree *pTree = this;
    bool finish = false;
    while(!finish) {
        finish = true;
        for (int i = 0; i < pTree->getClauses().size(); i++) {
            if (pTree->getClauses()[i].getNext() == nullptr && pTree->getClauses()[i].getElement() > 0) {
                finish = false;
                int currentLiteral = pTree->getClauses()[i].getElement(), currentNegLiteral;//-1 neccesary because of indices

                if (currentLiteral % 2 == 1)//positive
                    currentNegLiteral = currentLiteral + 1;
                else
                    currentNegLiteral = currentLiteral - 1;

                //verify negation not also a unit clause
                for (auto &j : pTree->getClauses())
                    if (j.getElement() == currentNegLiteral && j.getNext() == nullptr)
                        return false;

                //verify negation not in model
                for (auto &j : pTree->getCurrentModel())
                    if (j == currentNegLiteral)
                        return false;

                pTree->assignLiteral(currentLiteral);
            }
        }
    }
    return true;
}

bool cnfExecutionTree::isPureLiteral(int i) {
    if(this->getLiterals()[CNF::negationOfVariable(i) - 1].getElement() == -1){
        return true;
    }
}

int cnfExecutionTree::noHeuristic() {
    int currentLiteral = -1;
    for(int i = 0; i < this->getLiterals().size(); i++) {
        if (this->getLiterals()[i].getElement() != -1) {
            currentLiteral = i;

            if(isPureLiteral(currentLiteral + 1))
                return currentLiteral;
        }
    }
    return currentLiteral;
}

int cnfExecutionTree::firstSatisfyHeuristic() {
    int max = 0;
    int currentLiteral = -1;
    for(int i = 0; i < this->getLiterals().size(); i++)
    {
        if(this->getLiterals()[i].countElement() >= max){
            max = this->getLiterals()[i].countElement();
            currentLiteral = i;
        }
    }
    return currentLiteral;
}