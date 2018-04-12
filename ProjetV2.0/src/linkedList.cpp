//
// Created by Raphael on 4/10/2018.
//

#include "linkedList.h"

linkedList::linkedList(int element) : element(element) {next = nullptr;}

int linkedList::getElement() const {
    return element;
}

linkedList *linkedList::getNext() const {
    return next;
}

std::ostream &operator<<(std::ostream &os, const linkedList &list) {
    os << list.element;
    if(list.next != nullptr)
        os << ", " << *list.next;
    return os;
}

void linkedList::addElement(int element) {
    if (this->element == -1)
        this->element = element;
    else{
        linkedList *newLink = new linkedList(element);
        getLastElement()->next = newLink;
    }
}

linkedList *linkedList::getLastElement() {
    linkedList* current = this;
    linkedList* pred = this;
    while(current != nullptr){
        pred = current;
        current = current->next;
    }
    return pred;
}

void linkedList::deleteElement(int element) {
    linkedList *current = this;
    linkedList *pred = nullptr;
    while(current->next != nullptr && current->element != element){
        pred = current;
        current = current->next;
    }
    if(current->element == element)
    {
        if(current->next == nullptr){
            if(pred == nullptr){
                current->element = -1;
            }
            else
                pred->next = nullptr;
        }
        else
        {
            if(pred == nullptr){
                this->element = current->next->element;
                this->next = current->next->next;
            }
            else
                pred->next = current->next;
        }
    }
}

bool linkedList::isInList(int element) {
    linkedList *current = this;
    while(current->next != nullptr && current->element != element){
        current = current->next;
    }
    return current->element == element;
}

int linkedList::countElement() {
    linkedList* current = this;
    int count = 0;
    while(current->next != nullptr){
        current = current->next;
        count++;
    }
    return count;
}

linkedList::linkedList() {element = -1;}

void linkedList::deleteList() {
    this->element = -1;
    this->next = nullptr;
}

linkedList linkedList::copy() {
    linkedList l = linkedList(), *c = this;
    while(c != nullptr && c->element != -1)
    {
        l.addElement(c->element);
        c = c->next;
    }
    return l;
}
