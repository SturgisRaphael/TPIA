//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_CLAUSELIST_H
#define PROJET_CLAUSELIST_H


#include <ostream>

class clauseList {
private:
    int clause;
    clauseList *next = nullptr;

    clauseList(int clause, clauseList *next);

public:
    clauseList();

    explicit clauseList(int clause);

    int getClause() const;

    void setClause(int clause);

    clauseList * getNext();

    void setNext(clauseList *next);

    void addClause(int clause);

    bool isInList(int clause);

    void removeClause(int clause);

    clauseList * copyClauseList()const;

    friend std::ostream &operator<<(std::ostream &os, const clauseList &list);
};


#endif //PROJET_CLAUSELIST_H
