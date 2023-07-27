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
    if (selectedPieceRow == -1 && selectedPieceCol == -1) { //if no piece is selected
        SchaakStuk* s = g.getPiece(r, k);
        if (s != nullptr && s->getKleur() == currentPlayer) {
            selectedPieceRow = r;
            selectedPieceCol = k;
            setTileSelect(r, k, true);
        }
        // Get all valid moves for selected piece
        if (displayMoves()) {
            if(s->getKleur() == currentPlayer){
                vector<pair<int, int>> valid_moves = s->geldige_zetten(g);
                for (auto move: valid_moves) {
                    setTileFocus(move.first, move.second, true);
                    // Check if the destination of the move contains a piece
                    if (g.getPiece(move.first, move.second) != nullptr) {
                        setPieceThreat(move.first, move.second, true);
                    }
                }
            }
        }
    } else { //if a piece is selected
        setTileSelect(selectedPieceRow, selectedPieceCol, false);
        // Get all valid moves for selected piece
        for (int r = 0; r < 8; r++) {
            for (int k = 0; k < 8; k++) {
                setTileFocus(r, k, false);
                setPieceThreat(r,k, false);
            }
        }
        if (r == selectedPieceRow && k == selectedPieceCol) { //if the same piece is clicked again
            selectedPieceRow = -1;
            selectedPieceCol = -1;
        } else { //if a different position is clicked
            if (g.move(g.getPiece(selectedPieceRow, selectedPieceCol), r, k)) {
                currentPlayer = currentPlayer == wit ? zwart : wit;
                update();
            } else {
                message("This move is invalid.");
            }
            selectedPieceRow = -1;
            selectedPieceCol = -1;
        }
    }
}

void SchaakGUI::newGame() {

}


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


void SchaakGUI::visualizationChange() {
    QString visstring = QString(displayMoves()?"T":"F")+(displayKills()?"T":"F")+(displayThreats()?"T":"F");
    message(QString("Visualization changed : ")+visstring);
}


// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
void SchaakGUI::update() {
    clearBoard();
    removeAllMarking();
    for(int r = 0; r < 8; r++) {
        for (int k = 0; k < 8; k++) {
            SchaakStuk* s = this->g.getPiece(r,k);
            if(s != nullptr){
                this->setItem(r,k, s);
            }
        }
    }
}
