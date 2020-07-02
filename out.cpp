#include "out.h"

void Chessboard::OUT(int round_num, ArrayList movelist, double *win_array, stack s){
    out_ = (char *)malloc(100*sizeof(singleMove));
    
    path = "resource/rl/output" + char(round_num) + ".txt";
    
    fp.open(path, ios::out | ios::app);
    if (fp.is_open()) {
        //TODO: write in
        //use out_ as buffer to read in all datas
        s.pop(out_);
        movelist.print(win_array, out_);
        fp << out_;
    }
}