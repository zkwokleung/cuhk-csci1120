#ifndef LEOPARD_H
#define LEOPARD_H

#include "piece.h"

class Leopard : public Piece
{
public:
    Leopard(Color color, int y, int x);
    virtual bool isMoveValid(Board *board, int y, int x);
    virtual char getLabel() const;
};

#endif // !LEOPARD_H