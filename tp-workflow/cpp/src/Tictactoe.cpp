#include "Tictactoe.hpp"

Jeu::Jeu() {
    raz();
}

void Jeu::raz() {
    for (auto & ligne : _plateau)
        ligne.fill(Cell::Vide);
    _status = Status::RougeJoue;
}

Cell Jeu::getCell(int i, int j) const {
    return _plateau[i][j];
}

Status Jeu::getStatus() const {
    return _status;
}

/// Vérifie si un joueur a aligné 3 cellules identiques.
static bool aGagne(const std::array<std::array<Cell,3>,3> & p, Cell c) {
    // Lignes et colonnes
    for (int k = 0; k < 3; ++k) {
        if (p[k][0]==c && p[k][1]==c && p[k][2]==c) return true;
        if (p[0][k]==c && p[1][k]==c && p[2][k]==c) return true;
    }
    // Diagonales
    if (p[0][0]==c && p[1][1]==c && p[2][2]==c) return true;
    if (p[0][2]==c && p[1][1]==c && p[2][0]==c) return true;
    return false;
}

/// Vérifie si toutes les cases sont occupées.
static bool plateauPlein(const std::array<std::array<Cell,3>,3> & p) {
    for (const auto & ligne : p)
        for (Cell c : ligne)
            if (c == Cell::Vide) return false;
    return true;
}

bool Jeu::jouer(int i, int j) {
    // Coup invalide si la partie est terminée
    if (_status == Status::RougeGagne ||
        _status == Status::VertGagne  ||
        _status == Status::Egalite)
        return false;

    // Coup invalide si hors limites ou case occupée
    if (i < 0 || i >= 3 || j < 0 || j >= 3) return false;
    if (_plateau[i][j] != Cell::Vide) return false;

    // Jouer le coup
    Cell joueurCourant = (_status == Status::RougeJoue) ? Cell::Rouge : Cell::Vert;
    _plateau[i][j] = joueurCourant;

    // Mettre à jour le status
    if (aGagne(_plateau, Cell::Rouge)) {
        _status = Status::RougeGagne;
    } else if (aGagne(_plateau, Cell::Vert)) {
        _status = Status::VertGagne;
    } else if (plateauPlein(_plateau)) {
        _status = Status::Egalite;
    } else {
        _status = (joueurCourant == Cell::Rouge) ? Status::VertJoue : Status::RougeJoue;
    }

    return true;
}

std::ostream & operator<<(std::ostream & os, const Jeu & jeu) {
    os << "  0 1 2\n";
    for (int i = 0; i < 3; ++i) {
        os << i << " ";
        for (int j = 0; j < 3; ++j) {
            switch (jeu.getCell(i, j)) {
                case Cell::Vide:  os << '.'; break;
                case Cell::Rouge: os << 'R'; break;
                case Cell::Vert:  os << 'V'; break;
            }
            if (j < 2) os << ' ';
        }
        os << '\n';
    }
    return os;
}