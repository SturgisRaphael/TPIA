//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_LITERALLIST_H
#define PROJET_LITERALLIST_H


#include <ostream>

class literalList {
private:

    int literal;
    literalList *next = nullptr;
    literalList(int literal, literalList *next);

public:
    explicit literalList(int literal);

    int getLiteral() const;

    void setLiteral(int literal);

    literalList *getNext() const;

    void setNext(literalList *next);

    void addLiteral(int literal);

    int getNextLiteral() const;

    void deleteLiteral(int literal);

    bool isInList(int literal);

    literalList copyLiteralList()const;

    literalList();

    friend std::ostream &operator<<(std::ostream &os, const literalList &list);
};


#endif //PROJET_LITERALLIST_H
