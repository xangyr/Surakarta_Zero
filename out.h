#ifndef OUT_H
#define OUT_H
#include "ArrayList.h"
#include "chessboard.h"
#include "search_engine.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <climits>

class Chessboard{
public:
    char *out_;
    char *path;
private:
    ofstream fp;
}
#endif