//
// Created by Raphael on 4/10/2018.
//

#ifndef PROJETV2_0_LINKEDLIST_H
#define PROJETV2_0_LINKEDLIST_H


#include <ostream>

class linkedList {
private:
    int element;
    linkedList *next = nullptr;
    linkedList *getLastElement();
public:
    explicit linkedList(int element);

    linkedList();

    int getElement() const;

    linkedList *getNext() const;

    friend std::ostream &operator<<(std::ostream &os, const linkedList &list);

    void addElement(int element);

    void deleteElement(int element);

    void deleteList();

    bool isInList(int element);

    int countElement();

    linkedList copy();
};


#endif //PROJETV2_0_LINKEDLIST_H
