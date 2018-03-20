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

const clauseList &clauseList::getNext() const {
    return next;
}

void clauseList::setNext(const clauseList &next) {
    clauseList::next = next;
}

clauseList::clauseList() {}
