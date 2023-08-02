//  Student: Oktay Beytula Yusuf
//  Rolnummer: 20223522
//  Opmerkingen: (bv aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"
#include <vector>
#include <map>
#include <utility>

class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    //initiator
    Game();
    //destructor
    ~Game();

    //bool
    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k
    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    bool gameOver();
    bool kingInCheckAfterMove(int from_row, int from_col, int to_row, int to_col);
    void resetGame();

public:
    //getter
    SchaakStuk* getPiece(int r, int k);
    int getPieceRow(SchaakStuk* s);
    int getPieceCol(SchaakStuk* s);

    //setter
    void setStartBord();
    void setPiece(int r, int k, SchaakStuk* s);

    map<pair<int, int>, SchaakStuk*> schaakbord;

private:
    zw currentPlayer;
};


#endif //SCHAKEN_GAME_H
