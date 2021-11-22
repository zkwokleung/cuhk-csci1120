#include "rat.h"
#include <iostream>

using namespace std;

Rat::Rat(Color color, int y, int x) : Piece(color, y, x) {
    setName(PIECE_NAME[RAT-1]);
    setRank(RAT);
}

bool Rat::isMoveValid(Board* board, int y, int x) {
    // TODO: Override the superclass version of valid move checks
    // e.g., to allow a Rat to move into a square occuppied by an Elephant 
    //       to allow a Rat to enter a water square
    
}

bool Rat::canCapture(Piece* p) {
    // TODO: Override the superclass version of capture checks
    // A Rat can capture an Elephant
}