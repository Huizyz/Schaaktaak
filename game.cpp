//  Student: Oktay Beytula Yusuf
//  Rolnummer: 20223522
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    currentPlayer = zwart;
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {

    const int numPions = 8;

    SchaakStuk* p1=new Pion(zwart);
    SchaakStuk* p2=new Pion(zwart);
    SchaakStuk* p3=new Pion(zwart);
    SchaakStuk* p4=new Pion(zwart);
    SchaakStuk* p5=new Pion(zwart);
    SchaakStuk* p6=new Pion(zwart);
    SchaakStuk* p7=new Pion(zwart);
    SchaakStuk* p8=new Pion(zwart);
    setPiece(1,0,p1);
    setPiece(1,1,p2);
    setPiece(1,2,p3);
    setPiece(1,3,p4);
    setPiece(1,4,p5);
    setPiece(1,5,p6);
    setPiece(1,6,p7);
    setPiece(1,7,p8);

    SchaakStuk* wp1=new Pion(wit);
    SchaakStuk* wp2=new Pion(wit);
    SchaakStuk* wp3=new Pion(wit);
    SchaakStuk* wp4=new Pion(wit);
    SchaakStuk* wp5=new Pion(wit);
    SchaakStuk* wp6=new Pion(wit);
    SchaakStuk* wp7=new Pion(wit);
    SchaakStuk* wp8=new Pion(wit);
    setPiece(6,0,wp1);
    setPiece(6,1,wp2);
    setPiece(6,2,wp3);
    setPiece(6,3,wp4);
    setPiece(6,4,wp5);
    setPiece(6,5,wp6);
    setPiece(6,6,wp7);
    setPiece(6,7,wp8);

    SchaakStuk* Q=new Koningin(zwart);
    SchaakStuk* wQ=new Koningin(wit);
    setPiece(0,3,Q);
    setPiece(7,3,wQ);

    SchaakStuk* K=new Koning(zwart);
    SchaakStuk* wK=new Koning(wit);
    setPiece(0,4,K);
    setPiece(7,4,wK);

    SchaakStuk* P=new Paard(zwart);
    SchaakStuk* wP=new Paard(wit);
    setPiece(0,1,P);
    setPiece(7,1,wP);
    SchaakStuk* P2=new Paard(zwart);
    SchaakStuk* wP2=new Paard(wit);
    setPiece(0,6,P2);
    setPiece(7,6,wP2);

    SchaakStuk* L=new Loper(zwart);
    SchaakStuk* wL=new Loper(wit);
    setPiece(0,2,L);
    setPiece(7,2,wL);
    SchaakStuk* L2=new Loper(zwart);
    SchaakStuk* wL2=new Loper(wit);
    setPiece(0,5,L2);
    setPiece(7,5,wL2);

    SchaakStuk* T=new Toren(zwart);
    SchaakStuk* wT=new Toren(wit);
    setPiece(0,0,T);
    setPiece(7,0,wT);
    SchaakStuk* T2=new Toren(zwart);
    SchaakStuk* wT2=new Toren(wit);
    setPiece(0,7,T2);
    setPiece(7,7,wT2);
}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    // Get the current position of the piece
    int current_row = getPieceRow(s);
    int current_col = getPieceCol(s);

    // Check if the move is valid
    vector<pair<int, int>> valid_moves = s->geldige_zetten(*this);
    bool is_valid = false;
    for (auto& move : valid_moves) {
        if (move.first == r && move.second == k) {
            is_valid = true;
            break;
        }
    }

    // If the move is valid, update the board
    if (is_valid) {
        // remove the piece from the current position
        schaakbord.erase(make_pair(current_row, current_col));
        // place the piece in the new position
        setPiece(r, k, s);
        return true;
    } else {
        return false;
    }
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    return schaakbord[{r,k}];
}

// Itereert de map op zoek naar het gevraagde schaakstuk.
// Wanneer het het stuk vindt, retourneert het de overeenkomstige rij of kolom.
// Als het opgegeven schaakstuk niet wordt gevonden, wordt -1 geretourneerd.
int Game::getPieceRow(SchaakStuk* s) {
    for (auto i : schaakbord) {
        if (i.second == s) {
            return i.first.first;
        }
    }
    return -1;
}

int Game::getPieceCol(SchaakStuk* s) {
    for (auto i : schaakbord) {
        if (i.second == s) {
            return i.first.second;
        }
    }
    return -1;
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s) {
    schaakbord[{r, k}] = s;
}

bool Game::gameOver() {
    // Check if current player is in checkmate
    if (schaakmat(currentPlayer)) {
        return true;
    }
    // Check if current player is in stalemate
    if (schaak(currentPlayer)) {
        return true;
    }
    return false;
}