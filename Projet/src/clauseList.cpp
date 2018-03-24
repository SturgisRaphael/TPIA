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

clauseList clauseList::copyClauseList()const {
    clauseList next;
    if(this->next != nullptr)
        next = this->next->copyClauseList();
    else
        next = nullptr;

    return clauseList(this->clause, &next);
}

clauseList::clauseList(int clause, clauseList *next) : clause(clause), next(next) {}

clauseList::clauseList() : clause(-1){}

std::ostream &operator<<(std::ostream &os, const clauseList &list) {
    os << "clause: " << list.clause;

    if(list.next != nullptr)
        os << ", " << list.next;

    return os;
}

void clauseList::addClause(int clause) {
    clauseList *end = this;

    while(end->getNext() != nullptr)
        end = end->getNext();

    end->setNext(new clauseList(clause));
}
