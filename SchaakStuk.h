//  Student: Oktay Beytula Yusuf
//  Rolnummer: 20223522
//  Opmerkingen: (bv aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>

using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    explicit SchaakStuk(zw kleur);

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }

    virtual vector<pair<int, int>> geldige_zetten(Game& g) { return {}; }

private:
    zw kleur;
};

// bekijk oude SchaakStuk.h file als er problemen optreden
// De Piece piece functies zijn anders geschreven

class Pion:public SchaakStuk {
public:
    explicit Pion(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;

    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

class Toren:public SchaakStuk {
public:
    explicit Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;

    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

class Paard:public SchaakStuk {
public:
    explicit Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;


    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

class Loper:public SchaakStuk {
public:
    explicit Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;


    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

class Koning:public SchaakStuk {
public:
    explicit Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;


    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

class Koningin:public SchaakStuk {
public:
    explicit Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override;


    vector<pair<int, int>> geldige_zetten(Game& g) override;

};

#endif //SCHAKEN_SCHAAKSTUK_H
