//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_LITERALLIST_H
#define PROJET_LITERALLIST_H


class literalList {
private:
    int literal;
    literalList *next = nullptr;

public:
    explicit literalList(int literal);



    int getLiteral() const;

    void setLiteral(int literal);

    const literalList &getNext() const;

    void setNext(literalList *next);

    void addLiteral(int literal);

    int getNextLiteral() const;

    void deleteLiteral(int literal);

    bool isInList(int literal);
};


#endif //PROJET_LITERALLIST_H
