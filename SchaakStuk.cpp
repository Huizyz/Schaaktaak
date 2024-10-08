//  Student: Oktay Beytula Yusuf
//  Rolnummer: 20223522
//  Opmerkingen: (bv aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"

SchaakStuk::SchaakStuk(zw kleur) : kleur(kleur) {}

Piece Pion::piece() const {
    return {Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black};
}

// int direction: -1 = wit, 1 = zwart
vector<pair<int, int>> Pion::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int direction = (getKleur() == zwart ? 1 : -1);
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    // Check if the square in front is within bounds and empty
    if (isWithinBounds(current_row + direction, current_col) &&
        g.getPiece(current_row + direction, current_col) == nullptr) {
        valid_moves.emplace_back(current_row + direction, current_col);
    }

    // Check for the initial double move
    if (current_row == (getKleur() == zwart ? 1 : 6)) {
        if (isWithinBounds(current_row + 2 * direction, current_col) &&
            g.getPiece(current_row + 2 * direction, current_col) == nullptr &&
            g.getPiece(current_row + direction, current_col) == nullptr) {
            valid_moves.emplace_back(current_row + 2 * direction, current_col);
        }
    }

    // Check for capturing diagonally
    if (isWithinBounds(current_row + direction, current_col + 1) &&
        g.getPiece(current_row + direction, current_col + 1) != nullptr &&
        g.getPiece(current_row + direction, current_col + 1)->getKleur() != getKleur()) {
        valid_moves.emplace_back(current_row + direction, current_col + 1);
    }
    if (isWithinBounds(current_row + direction, current_col - 1) &&
        g.getPiece(current_row + direction, current_col - 1) != nullptr &&
        g.getPiece(current_row + direction, current_col - 1)->getKleur() != getKleur()) {
        valid_moves.emplace_back(current_row + direction, current_col - 1);
    }
    return valid_moves;
}


Piece Toren::piece() const {
    return {Piece::Rook,getKleur()==wit?Piece::White:Piece::Black};
}

vector<pair<int, int>> Toren::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    // Check moves to the left
    for (int i = current_col - 1; i >= 0; i--) {
        if (isWithinBounds(current_row, i)) {
            if (g.getPiece(current_row, i) == nullptr) {
                valid_moves.emplace_back(current_row, i);
            } else {
                if (g.getPiece(current_row, i)->getKleur() != getKleur()) {
                    valid_moves.emplace_back(current_row, i);
                }
                break;
            }
        } else {
            break;
        }
    }

    // Check moves to the right
    for (int i = current_col + 1; i < 8; i++) {
        if (isWithinBounds(current_row, i)) {
            if (g.getPiece(current_row, i) == nullptr) {
                valid_moves.emplace_back(current_row, i);
            } else {
                if (g.getPiece(current_row, i)->getKleur() != getKleur()) {
                    valid_moves.emplace_back(current_row, i);
                }
                break;
            }
        } else {
            break;
        }
    }

    // Check moves upwards
    for (int i = current_row - 1; i >= 0; i--) {
        if (isWithinBounds(i, current_col)) {
            if (g.getPiece(i, current_col) == nullptr) {
                valid_moves.emplace_back(i, current_col);
            } else {
                if (g.getPiece(i, current_col)->getKleur() != getKleur()) {
                    valid_moves.emplace_back(i, current_col);
                }
                break;
            }
        } else {
            break;
        }
    }

    // Check moves downwards
    for (int i = current_row + 1; i < 8; i++) {
        if (isWithinBounds(i, current_col)) {
            if (g.getPiece(i, current_col) == nullptr) {
                valid_moves.emplace_back(i, current_col);
            } else {
                if (g.getPiece(i, current_col)->getKleur() != getKleur()) {
                    valid_moves.emplace_back(i, current_col);
                }
                break;
            }
        } else {
            break;
        }
    }

    return valid_moves;
}

Piece Paard::piece() const {
    return {Piece::Knight,getKleur()==wit?Piece::White:Piece::Black};
}

vector<pair<int, int>> Paard::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    // Check moves left
    if (current_col > 1) {
        if (current_row > 0 && isWithinBounds(current_row - 1, current_col - 2)) {
            if (g.getPiece(current_row - 1, current_col - 2) == nullptr ||
                g.getPiece(current_row - 1, current_col - 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - 1, current_col - 2);
            }
        }
        if (current_row < 7 && isWithinBounds(current_row + 1, current_col - 2)) {
            if (g.getPiece(current_row + 1, current_col - 2) == nullptr ||
                g.getPiece(current_row + 1, current_col - 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + 1, current_col - 2);
            }
        }
    }

    // Check moves right
    if (current_col < 6) {
        if (current_row > 0 && isWithinBounds(current_row - 1, current_col + 2)) {
            if (g.getPiece(current_row - 1, current_col + 2) == nullptr ||
                g.getPiece(current_row - 1, current_col + 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - 1, current_col + 2);
            }
        }
        if (current_row < 7 && isWithinBounds(current_row + 1, current_col + 2)) {
            if (g.getPiece(current_row + 1, current_col + 2) == nullptr ||
                g.getPiece(current_row + 1, current_col + 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + 1, current_col + 2);
            }
        }
    }

    // Check moves up
    if (current_row > 0) {
        if (current_col > 0 && isWithinBounds(current_row - 2, current_col - 1)) {
            if (g.getPiece(current_row - 2, current_col - 1) == nullptr ||
                g.getPiece(current_row - 2, current_col - 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - 2, current_col - 1);
            }
        }
        if (current_col < 7 && isWithinBounds(current_row - 2, current_col + 1)) {
            if (g.getPiece(current_row - 2, current_col + 1) == nullptr ||
                g.getPiece(current_row - 2, current_col + 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - 2, current_col + 1);
            }
        }
    }

    // Check moves down
    if (current_row < 7) {
        if (current_col > 0 && isWithinBounds(current_row + 2, current_col - 1)) {
            if (g.getPiece(current_row + 2, current_col - 1) == nullptr ||
                g.getPiece(current_row + 2, current_col - 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + 2, current_col - 1);
            }
        }
        if (current_col < 7 && isWithinBounds(current_row + 2, current_col + 1)) {
            if (g.getPiece(current_row + 2, current_col + 1) == nullptr ||
                g.getPiece(current_row + 2, current_col + 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + 2, current_col + 1);
            }
        }
    }
    return valid_moves;
}



Piece Loper::piece() const {
    return {Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black};
}

vector<pair<int, int>> Loper::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    // Check moves up-left
    for (int i = 1; isWithinBounds(current_row - i, current_col - i); i++) {
        SchaakStuk* piece = g.getPiece(current_row - i, current_col - i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row - i, current_col - i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - i, current_col - i);
            }
            break;
        }
    }
    // Check moves up-right
    for (int i = 1; isWithinBounds(current_row - i, current_col + i); i++) {
        SchaakStuk* piece = g.getPiece(current_row - i, current_col + i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row - i, current_col + i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row - i, current_col + i);
            }
            break;
        }
    }
    // Check moves down-left
    for (int i = 1; isWithinBounds(current_row + i, current_col - i); i++) {
        SchaakStuk* piece = g.getPiece(current_row + i, current_col - i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row + i, current_col - i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + i, current_col - i);
            }
            break;
        }
    }
    // Check moves down-right
    for (int i = 1; isWithinBounds(current_row + i, current_col + i); i++) {
        SchaakStuk* piece = g.getPiece(current_row + i, current_col + i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row + i, current_col + i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row + i, current_col + i);
            }
            break;
        }
    }
    return valid_moves;
}



Piece Koning::piece() const {
    return {Piece::King,getKleur()==wit?Piece::White:Piece::Black};
}

bool SchaakStuk::isWithinBounds(int r, int k) const {
    return (r>=0 && r < 8) and (k >=0 && k<8);
}

vector<pair<int, int>> Koning::geldige_zetten(Game &g) {
    vector<pair<int,int>> move;
    int current_row = g.getPieceRow((SchaakStuk *) this);
    int current_col = g.getPieceCol((SchaakStuk *) this);
    int new_row;
    int new_col;
    for(int i = -1; i <= 1 ; i++){
        for(int j = -1; j<=1; j++){
            if(i==0 and j ==0){
                continue;
            }
            new_row = current_row + i;
            new_col = current_col + j;
            if(isWithinBounds(new_row, new_col)){
                auto piece = g.getPiece(new_row,new_col);
                if(piece== nullptr){
                    move.emplace_back(new_row,new_col);
                }else{
                    if(piece->getKleur() != getKleur()){
                        move.emplace_back(new_row,new_col);
                    }
                }
            }
        }
    }
    return move;
}


Piece Koningin::piece() const {
    return {Piece::Queen,getKleur()==wit?Piece::White:Piece::Black};
}

vector<pair<int, int>> Koningin::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    // Check moves up
    for (int i = current_row - 1; i >= 0; i--) {
        SchaakStuk* piece = g.getPiece(i, current_col);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, current_col);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, current_col);
            }
            break;
        }
    }
    // Check moves down
    for (int i = current_row + 1; i <= 7; i++) {
        SchaakStuk* piece = g.getPiece(i, current_col);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, current_col);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, current_col);
            }
            break;
        }
    }
    // Check moves left
    for (int i = current_col - 1; i >= 0; i--) {
        SchaakStuk* piece = g.getPiece(current_row, i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row, i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row, i);
            }
            break;
        }
    }
    // Check moves right
    for (int i = current_col + 1; i <= 7; i++) {
        SchaakStuk* piece = g.getPiece(current_row, i);
        if (piece == nullptr) {
            valid_moves.emplace_back(current_row, i);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row, i);
            }
            break;
        }
    }
    // Check moves up-left
    for (int i = current_row - 1, j = current_col - 1; i >= 0 && j >= 0; i--, j--) {
        SchaakStuk* piece = g.getPiece(i, j);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, j);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, j);
            }
            break;
        }
    }
    // Check moves up-right
    for (int i = current_row - 1, j = current_col + 1; i >= 0 && j <= 7; i--, j++) {
        SchaakStuk* piece = g.getPiece(i, j);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, j);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, j);
            }
            break;
        }
    }
    // Check moves down-left
    for (int i = current_row + 1, j = current_col - 1; i <= 7 && j >= 0; i++, j--) {
        SchaakStuk* piece = g.getPiece(i, j);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, j);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, j);
            }
            break;
        }
    }
    // Check moves down-right
    for (int i = current_row + 1, j = current_col + 1; i <= 7 && j <= 7; i++, j++) {
        SchaakStuk* piece = g.getPiece(i, j);
        if (piece == nullptr) {
            valid_moves.emplace_back(i, j);
        } else {
            if (piece->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, j);
            }
            break;
        }
    }
    return valid_moves;
}