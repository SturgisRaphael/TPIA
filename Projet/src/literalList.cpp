//
// Created by raphael on 3/14/18.
//

#include "literalList.h"

literalList::literalList(int literal) : literal(literal) {}

int literalList::getLiteral() const {
    return literal;
}

void literalList::setLiteral(int literal) {
    literalList::literal = literal;
}

void literalList::setNext(literalList *next) {
    literalList::next = next;
}

bool literalList::isInList(int literal) {
    if(literal == this->literal)
        return true;
    else if(this->next == nullptr)
        return false;
    else
        return next->isInList(literal);
}

void literalList::addLiteral(int literal) {
    if(!this->isInList(literal)){
        literalList *currentList = this;
        while(currentList->next != nullptr){
            currentList = currentList->next;
        }

        currentList->next = new literalList(literal);
    }
}

int literalList::getNextLiteral() const {
    return this->next->literal;
}

void literalList::deleteLiteral(int literal) {
    if(this->isInList(literal)){
        literalList *currentList = this;
        while(currentList->literal != literal){
            currentList = currentList->next;
        }

        currentList->next = currentList->next->next;
    }
}

literalList::literalList(int literal, literalList *next) : literal(literal), next(next) {}

literalList literalList::copyLiteralList()const {
    literalList next;
    if(this->next != nullptr)
        next = this->next->copyLiteralList();
    else
        next = nullptr;

    return literalList(this->literal, &next);
}

literalList::literalList() : literal(-1){}

literalList *literalList::getNext() const {
    return next;
}

std::ostream &operator<<(std::ostream &os, const literalList &list) {
    os << list.literal;

    if(list.next != nullptr)
        os << ", " << list.next;

    return os;
}
