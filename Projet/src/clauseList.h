//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_CLAUSELIST_H
#define PROJET_CLAUSELIST_H


class clauseList {
private:
    int clause;
    clauseList *next = nullptr;
public:
    clauseList();

    explicit clauseList(int clause);

    int getClause() const;

    void setClause(int clause);

    const clauseList &getNext() const;

    void setNext(const clauseList &next);
};


#endif //PROJET_CLAUSELIST_H
