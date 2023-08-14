//
// Created by toonc on 12/17/2021.
//

#include <iostream>
#include "SchaakGUI.h"
#include "game.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"

// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    g.setStartBord();
    selectedPieceRow = -1;
    selectedPieceCol = -1;
    currentPlayer = wit;
    update();
}

void SchaakGUI::clicked(int r, int k) {
    if (noPieceSelected()) {
        handleNoPieceSelected(r, k);
        markThreatenedPositions(r, k);
    } else {
        handlePieceSelected(r, k);
        markThreatenedPieces(r, k);
        removeAllMarking();
    }
}

bool SchaakGUI::noPieceSelected() const {
    return (selectedPieceRow == -1 && selectedPieceCol == -1);
}

//wanneer er nog op niets is gedrukt, de 1ste keer dat je een pion gaat selecteren
void SchaakGUI::handleNoPieceSelected(int r, int k) {
    SchaakStuk* s = g.getPiece(r, k);
    if (s != nullptr && s->getKleur() == currentPlayer) {
        selectPiece(r, k);
        if (displayMoves() && s->getKleur() == currentPlayer) {
            highlightValidMoves(*s);
        }
    }
}

void SchaakGUI::selectPiece(int r, int k) {
    selectedPieceRow = r;
    selectedPieceCol = k;
    setTileSelect(r, k, true);
}

void SchaakGUI::highlightValidMoves(SchaakStuk& piece) {
    vector<pair<int, int>> valid_moves = piece.geldige_zetten(g);
    for (auto move : valid_moves) {
        setTileFocus(move.first, move.second, displayMoves());
        SchaakStuk* targetPiece = g.getPiece(move.first, move.second);
        if (targetPiece != nullptr) {
            setPieceThreat(move.first, move.second, displayKills());
        }
    }
}

void SchaakGUI::markThreatenedPositions(int r, int k) {
    SchaakStuk* selectedPiece = g.getPiece(r, k);
    if (selectedPiece == nullptr) {
        return;
    }

    vector<pair<int, int>> threatened_positions;
    vector<pair<int, int>> valid_moves = selectedPiece->geldige_zetten(g);

    // Check each valid move to see if the opponent can capture the selected piece
    for (const auto& move : valid_moves) {
        int dest_row = move.first;
        int dest_col = move.second;
        SchaakStuk* piece_at_dest = g.getPiece(dest_row, dest_col);

        // Temporarily move the selected piece to the destination and see if it gets captured
        g.setPiece(dest_row, dest_col, selectedPiece);
        g.setPiece(r, k, nullptr);

        // Check if the opponent's pieces can capture the selected piece
        bool is_captured = false;
        for (auto& entry : g.schaakbord) {
            if (entry.second != nullptr && entry.second->getKleur() != currentPlayer) {
                vector<pair<int, int>> opp_valid_moves = entry.second->geldige_zetten(g);
                for (const auto& opp_move : opp_valid_moves) {
                    if (opp_move.first == dest_row && opp_move.second == dest_col) {
                        is_captured = true;
                        break;
                    }
                }
            }
            if (is_captured) {
                break;
            }
        }

        // Restore the position of the selected piece on the board
        g.setPiece(r, k, selectedPiece);
        g.setPiece(dest_row, dest_col, piece_at_dest);

        // If the selected piece can be captured at the destination, mark it as threatened
        if (is_captured) {
            threatened_positions.emplace_back(dest_row, dest_col);
        }
    }

    // Mark the threatened positions in red
    for (const auto& threatened_pos : threatened_positions) {
        setTileThreat(threatened_pos.first, threatened_pos.second, displayThreats());
    }
}

void SchaakGUI::markThreatenedPieces(int r, int k) {
    SchaakStuk* selectedPiece = g.getPiece(r, k);
    if (selectedPiece == nullptr) {
        return;
    }

    // Check if the opponent's pieces can capture the selected piece
    for (auto& entry : g.schaakbord) {
        if (entry.second != nullptr && entry.second->getKleur() != currentPlayer) {
            vector<pair<int, int>> opp_valid_moves = entry.second->geldige_zetten(g);
            for (const auto& opp_move : opp_valid_moves) {
                if (opp_move.first == r && opp_move.second == k) {
                    setPieceThreat(entry.first.first, entry.first.second, displayKills());
                    break;
                }
            }
        }
    }
}

void SchaakGUI::removeAllTileMarking() {
    for (int r = 0; r < 8; r++) {
        for (int k = 0; k < 8; k++) {
            setTileFocus(r, k, false);
            setTileThreat(r, k, false);
        }
    }
}

//met het geselecteerde pion te werkt te gaan
void SchaakGUI::handlePieceSelected(int r, int k) {
    setTileSelect(selectedPieceRow, selectedPieceCol, false);
    removeAllTileMarking();
    if (r == selectedPieceRow && k == selectedPieceCol) {
        deselectPiece();
    } else {
        moveSelectedPiece(r, k);
    }
}

void SchaakGUI::deselectPiece() {
    selectedPieceRow = -1;
    selectedPieceCol = -1;
}

void SchaakGUI::moveSelectedPiece(int r, int k) {
    SchaakStuk* selectedPiece = g.getPiece(selectedPieceRow, selectedPieceCol);
    if (g.move(selectedPiece, r, k)) {
        currentPlayer = (currentPlayer == wit) ? zwart : wit;
        update();
        if (g.schaakmat(currentPlayer)) {
            message("Spel afgelopen. Schaakmat");
        }
        else if(g.schaak(currentPlayer)){
            message("schaak");
        }
        else if (g.pat(currentPlayer)) {
            message("Spel afgelopen. Het is een gelijkspel (pat)!");
        }

    } else {
        message("This move is invalid.");
    }
    deselectPiece();
}

void SchaakGUI::newGame() {
    // Clear the chessboard and reset the GUI
    clearBoard();
    removeAllMarking();
    selectedPieceRow = -1;
    selectedPieceCol = -1;

    // Reset the game object and set the starting positions for the pieces
    g.resetGame();
    // Update the GUI to display the new game state
    currentPlayer = wit;
    update();
}

void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    removeAllMarking();
    for (int r = 0; r < 8; r++) {
        for (int k = 0; k < 8; k++) {
            SchaakStuk *s = this->g.getPiece(r, k);
            if (s != nullptr) {
                this->setItem(r, k, s);
            }
        }
    }
}

//save, open, undo, redo niet aangeraakt (werkt niet)
void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Invalid File Format");
                    }
                }
                debugstring += "\n";
            }
            message(debugstring);
        } catch (QString& Q) {
            message(Q);
        }
    }
    update();
}

void SchaakGUI::undo() {
    message("Je hebt undo gekozen");
}

void SchaakGUI::redo() {
    message("Je hebt redo gekozen");
}
