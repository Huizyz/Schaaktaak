//  Student: Oktay Beytula Yusuf
//  Rolnummer: 20223522
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include "guicode/message.h"

Game::Game() {
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {
    // Set black pawns
    for (int i = 0; i < 8; i++) {
        setPiece(1, i, new Pion(zwart));
    }

    // Set white pawns
    for (int i = 0; i < 8; i++) {
        setPiece(6, i, new Pion(wit));
    }

    // Set black pieces

    setPiece(0, 0, new Toren(zwart));
    setPiece(0, 1, new Paard(zwart));
    setPiece(0, 2, new Loper(zwart));
    setPiece(0, 3, new Koningin(zwart));
    setPiece(0, 4, new Koning(zwart));
    setPiece(0, 5, new Loper(zwart));
    setPiece(0, 6, new Paard(zwart));
    setPiece(0, 7, new Toren(zwart));

    // Set white pieces
    setPiece(7, 0, new Toren(wit));
    setPiece(7, 1, new Paard(wit));
    setPiece(7, 2, new Loper(wit));
    setPiece(7, 3, new Koningin(wit));
    setPiece(7, 4, new Koning(wit));
    setPiece(7, 5, new Loper(wit));
    setPiece(7, 6, new Paard(wit));
    setPiece(7, 7, new Toren(wit));

}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    // Get the current position of the piece
    int current_row = getPieceRow(s);
    int current_col = getPieceCol(s);
    zw color = s->getKleur();
    auto saved = getPiece(r,k);
    bool valid = false;
    // Check if the move is valid
    vector<pair<int, int>> valid_moves = s->geldige_zetten(*this);
    for (auto& move : valid_moves) {
        if (move.first == r && move.second == k) {
            // Remove the piece from the current position
            schaakbord.erase(make_pair(current_row, current_col));
            // Place the piece in the new position
            setPiece(r, k, s);
            valid = true;
        }
    }
    if(!valid){
        return false;
    }

    if(schaak(color)){
        setPiece(r,k, nullptr);
        setPiece(current_row,current_col,s);
        setPiece(r,k,saved);
        return false;
    }

    return true;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    // Get the position of the king of the given color
    int king_row = -1;
    int king_col = -1;
    for (auto& pair : schaakbord) {
        if (pair.second != nullptr && dynamic_cast<Koning*>(pair.second) != nullptr) {
            if (pair.second->getKleur() == kleur) {
                king_row = pair.first.first;
                king_col = pair.first.second;
                break;
            }
        }
    }

    // If king's position not found, return false (king is not on the board)
    if (king_row == -1 || king_col == -1) {
        return false;
    }

    // Check if any of the opponent's pieces can attack the king's position
    zw opponent_color = (kleur == wit) ? zwart : wit;
    for (auto& entry : schaakbord) {
        if (entry.second != nullptr && entry.second->getKleur() == opponent_color) {
            vector<pair<int, int>> valid_moves = entry.second->geldige_zetten(*this);
            for (auto& move : valid_moves) {
                if (move.first == king_row && move.second == king_col) {
                    // The king is in check, return true
                    return true;
                }
            }
        }
    }

    // If no opponent's piece can attack the king, return false
    return false;
}


// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    // Check if the king is in check
    if (!schaak(kleur)) {
        return false; // The king is not in checkmate
    }

    // Get the position of the king of the given color
    int king_row = -1;
    int king_col = -1;
    for (auto& entry : schaakbord) {
        if (entry.second != nullptr && dynamic_cast<Koning*>(entry.second) != nullptr) {
            if (entry.second->getKleur() == kleur) {
                king_row = entry.first.first;
                king_col = entry.first.second;
                break;
            }
        }
    }

    // If king's position not found, return false (king is not on the board)
    if (king_row == -1 || king_col == -1) {
        return false;
    }

    Game copy(*this);
    vector<SchaakStuk*> zelfdeKleur;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (copy.getPiece(i,j) != nullptr and copy.getPiece(i,j)->getKleur() == kleur){
                zelfdeKleur.emplace_back(copy.getPiece(i,j));
            }
        }
    }
    // Iterate over valid moves of pieces
    for (auto i : zelfdeKleur) {
        for (auto j : i->geldige_zetten(*this)) {
            int save_row = getPieceRow(i);
            int save_col = getPieceCol(i);
            SchaakStuk* saved_piece = getPiece(j.first, j.second);

                copy.setPiece(save_row, save_col, nullptr);
                copy.setPiece(j.first, j.second, i);
                // Check if the king is still in check after the move
                if (!copy.schaak(kleur)) {
                    copy.setPiece(save_row, save_col, i);
                    copy.setPiece(j.first, j.second, saved_piece);
                    return false;// The king can get out of check, not checkmate
                }
        }
    }
    return true;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    /*
    // Check if the king of the given color is in check
    if (schaak(kleur)) {
        return false; // The king is in check, so it's not pat
    }

    // Check if there is any valid move for any piece of the given color
    for (auto& entry : schaakbord) {
        if (entry.second != nullptr && entry.second->getKleur() == kleur) {
            vector<pair<int, int>> valid_moves = entry.second->geldige_zetten(*this);
            if (!valid_moves.empty()) {
                return false; // At least one piece has a valid move, so it's not pat
            }
        }
    }

    // If no piece of the given color has valid moves, it's pat
    return true;
     */
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


void Game::resetGame() {
    // Remove all pieces from the chessboard
    for (auto& entry : schaakbord) {
        delete entry.second; // Free memory of the piece object
    }
    schaakbord.clear(); // Clear the chessboard

    // Call setStartBord() to set the starting positions for the pieces
    setStartBord();
}