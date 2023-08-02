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
    if (g.getPiece(current_row + direction, current_col) == nullptr) {
        valid_moves.emplace_back( current_row + direction, current_col );
    }
    if (current_row == (getKleur() == zwart ? 1 : 6)) {
        if (g.getPiece(current_row + direction, current_col) == nullptr &&
            g.getPiece(current_row + 2 * direction, current_col) == nullptr) {
            valid_moves.emplace_back( current_row + 2 * direction, current_col );
        }
    }
    if (g.getPiece(current_row + direction, current_col + 1) != nullptr &&
        g.getPiece(current_row + direction, current_col + 1)->getKleur() != getKleur()) {
        valid_moves.emplace_back( current_row + direction, current_col + 1 );
    }
    if (g.getPiece(current_row + direction, current_col - 1) != nullptr &&
        g.getPiece(current_row + direction, current_col - 1)->getKleur() != getKleur()) {
        valid_moves.emplace_back( current_row + direction, current_col - 1 );
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
        if (g.getPiece(current_row, i) == nullptr) {
            valid_moves.emplace_back(current_row, i);
        } else {
            if (g.getPiece(current_row, i)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row, i);
            }
            break;
        }
    }

    // Check moves to the right
    for (int i = current_col + 1; i < 8; i++) {
        if (g.getPiece(current_row, i) == nullptr) {
            valid_moves.emplace_back(current_row, i);
        } else {
            if (g.getPiece(current_row, i)->getKleur() != getKleur()) {
                valid_moves.emplace_back(current_row, i);
            }
            break;
        }
    }

    // Check moves upwards
    for (int i = current_row - 1; i >= 0; i--) {
        if (g.getPiece(i, current_col) == nullptr) {
            valid_moves.emplace_back(i, current_col);
        } else {
            if (g.getPiece(i, current_col)->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, current_col);
            }
            break;
        }
    }

    // Check moves downwards
    for (int i = current_row + 1; i < 8; i++) {
        if (g.getPiece(i, current_col) == nullptr) {
            valid_moves.emplace_back(i, current_col);
        } else {
            if (g.getPiece(i, current_col)->getKleur() != getKleur()) {
                valid_moves.emplace_back(i, current_col);
            }
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
        if (current_row > 0) {
            if (g.getPiece(current_row - 1, current_col - 2) == nullptr ||
                g.getPiece(current_row - 1, current_col - 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row - 1, current_col - 2 );
            }
        }
        if (current_row < 7) {
            if (g.getPiece(current_row + 1, current_col - 2) == nullptr ||
                g.getPiece(current_row + 1, current_col - 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row + 1, current_col - 2 );
            }
        }
    }

    // Check moves right
    if (current_col < 6) {
        if (current_row > 0) {
            if (g.getPiece(current_row - 1, current_col + 2) == nullptr ||
                g.getPiece(current_row - 1, current_col + 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row - 1, current_col + 2 );
            }
        }
        if (current_row < 7) {
            if (g.getPiece(current_row + 1, current_col + 2) == nullptr ||
                g.getPiece(current_row + 1, current_col + 2)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row + 1, current_col + 2 );
            }
        }
    }

    // Check moves up
    if (current_row > 0) {
        if (current_col > 0) {
            if (g.getPiece(current_row - 2, current_col - 1) == nullptr ||
                g.getPiece(current_row - 2, current_col - 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row - 2, current_col - 1 );
            }
        }
        if (current_col < 7) {
            if (g.getPiece(current_row - 2, current_col + 1) == nullptr ||
                g.getPiece(current_row - 2, current_col + 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row - 2, current_col + 1 );
            }
        }
    }

    // Check moves down
    if (current_row < 7) {
        if (current_col > 0) {
            if (g.getPiece(current_row + 2, current_col - 1) == nullptr ||
                g.getPiece(current_row + 2, current_col - 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row + 2, current_col - 1 );
            }
        }
        if (current_col < 7) {
            if (g.getPiece(current_row + 2, current_col + 1) == nullptr ||
                g.getPiece(current_row + 2, current_col + 1)->getKleur() != getKleur()) {
                valid_moves.emplace_back( current_row + 2, current_col + 1 );
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
    for (int i = 1; current_row - i >= 0 && current_col - i >= 0; i++) {
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
    for (int i = 1; current_row - i >= 0 && current_col + i <= 7; i++) {
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
    for (int i = 1; current_row + i <= 7 && current_col - i >= 0; i++) {
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
    for (int i = 1; current_row + i <= 7 && current_col + i <= 7; i++) {
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

/*
vector<pair<int, int>> Koning::geldige_zetten(Game& g) {
    vector<pair<int, int>> valid_moves;
    int current_row = g.getPieceRow(this);
    int current_col = g.getPieceCol(this);

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the current position
            int new_row = current_row + i;
            int new_col = current_col + j;
            if (new_row < 0 || new_row > 7 || new_col < 0 || new_col > 7) continue; // Skip out of bound positions
            SchaakStuk* piece = g.getPiece(new_row, new_col);
            if (piece == nullptr || piece->getKleur() != getKleur()) {
                // Temporarily try out the move
                SchaakStuk* original_piece = g.getPiece(new_row, new_col);
                g.setPiece(new_row, new_col, this);
                g.setPiece(current_row, current_col, nullptr);

                // Check if the king is in check after the move
                if (!g.schaak(getKleur())) {
                    valid_moves.emplace_back(new_row, new_col);
                }

                // Revert the move
                g.setPiece(current_row, current_col, this);
                g.setPiece(new_row, new_col, original_piece);
            }
        }
    }

    return valid_moves;
}
*/

bool SchaakStuk::possible_move_checker(int r, int k) const {
    return (r>=0 and r < 8) and (k >=0 and k<8);
}

vector<pair<int, int>> Koning::geldige_zetten(Game &game) {
    vector<pair<int,int>> move;
    int current_row = game.getPieceRow((SchaakStuk *) this);
    int current_col = game.getPieceCol((SchaakStuk *) this);
    int new_row;
    int new_col;
    for(int i = -1; i <= 1 ; i++){
        for(int j = -1; j<=1; j++){
            if(i==0 and j ==0){
                continue;
            }
            new_row = current_row + i;
            new_col = current_col + j;
            if(possible_move_checker(new_row, new_col)){
                auto piece = game.getPiece(new_row,new_col);
                if(piece== nullptr){
                    move.push_back({new_row,new_col});
                }else{
                    if(piece->getKleur() != getKleur()){
                        move.push_back({new_row,new_col});
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