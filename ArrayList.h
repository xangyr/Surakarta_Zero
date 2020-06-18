//
// Created by Blue Sky on 4/4/20.
//

#ifndef SURAKARTA_ZERO_ARRAYLIST_H
#define SURAKARTA_ZERO_ARRAYLIST_H
using namespace std;
#include <iostream>
#include "basic.h"

class ArrayList{
public:
    ArrayList();
    void clear();
    int size();
    bool unempty();
    void push(int from_x,int from_y,int to_x,int to_y);
    void push_unrepeat(int from_x,int from_y,int to_x,int to_y);
    void pop(singleMove &x);
    void pull(singleMove &x,int index);
    void print();
    bool find(int from_x,int from_y,int to_x,int to_y);
private:
    singleMove *array;
    int length;
    int start;
};
#endif //SURAKARTA_ZERO_ARRAYLIST_H
