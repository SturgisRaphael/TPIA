//
// Created by raphael on 3/14/18.
//

#include "clauseList.h"



clauseList::clauseList(int clause) : clause(clause) {}

int clauseList::getClause() const {
    return clause;
}

void clauseList::setClause(int clause) {
    clauseList::clause = clause;
}

clauseList *clauseList::getNext() {
    return next;
}

void clauseList::setNext(clauseList *next) {
    clauseList::next = next;
}

clauseList *clauseList::copyClauseList()const {
    if(this->next != nullptr)
        return new clauseList(this->clause, this->next->copyClauseList());
    else
        return new clauseList(this->clause, nullptr);
}

clauseList::clauseList(int clause, clauseList *next) : clause(clause), next(next) {}

clauseList::clauseList() : clause(-1){}

std::ostream &operator<<(std::ostream &os, const clauseList &list) {
    os << list.clause;

    if(list.next != nullptr)
        os << ", " << *list.next;

    return os;
}

void clauseList::addClause(int clause) {
    if(this->clause == -1)
    {
        this->clause = clause;
        return;
    }
    clauseList *end = this;

    while(end->getNext() != nullptr)
        end = end->getNext();

    end->setNext(new clauseList(clause));
}

bool clauseList::isInList(int clause) {
    clauseList *tmp = this;
    while(tmp != nullptr){
        if(tmp->getClause() == clause)
            return true;
        tmp = tmp->getNext();
    }

    return false;
}

void clauseList::removeClause(int clause) {
    clauseList *tmp = this , *root = this;
    clauseList *pred = nullptr;

    while(tmp != nullptr){
        if(tmp->getClause() == clause)
        {

            if(tmp->getNext() != nullptr)
            {
                tmp->setClause(tmp->getNext()->getClause());
                tmp->setNext(tmp->getNext()->getNext());
                break;
            }
            else if(pred == nullptr)
            {
                tmp->setClause(-1);
            } else{
                pred->setNext(nullptr);
            }
        }
        pred = tmp;
        tmp = tmp->getNext();
    }
}

int clauseList::countClauses() {
    int result = 0;
    clauseList *tmp = this;
    while(tmp != nullptr){
        result++;
        tmp = tmp->getNext();
    }
    return result;
}
