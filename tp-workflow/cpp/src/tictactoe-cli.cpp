#include "Tictactoe.hpp"
#include <iostream>
#include <limits>

using namespace std;

/// \brief Demande et valide la saisie d'un coup.
/// \param jeu Le jeu courant (pour vérifier case libre)
/// \return Paire {i, j} du coup valide saisi
static pair<int,int> saisirCoup(const Jeu & jeu) {
    int i, j;
    while (true) {
        cout << "Entrez ligne et colonne (ex: 1 2) : ";
        if (!(cin >> i >> j)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Saisie invalide, recommencez.\n";
            continue;
        }
        if (i < 0 || i >= 3 || j < 0 || j >= 3) {
            cout << "Coordonnées hors limites (0-2), recommencez.\n";
            continue;
        }
        if (jeu.getCell(i, j) != Cell::Vide) {
            cout << "Case occupée, choisissez une autre.\n";
            continue;
        }
        break;
    }
    return {i, j};
}

int main() {
    Jeu jeu;

    cout << "=== Tic-Tac-Toe ===\n";
    cout << "Rouge = R, Vert = V\n\n";
    cout << jeu;

    while (true) {
        Status s = jeu.getStatus();

        // Afficher quel joueur doit jouer
        if (s == Status::RougeJoue)
            cout << "\nTour de Rouge (R)\n";
        else
            cout << "\nTour de Vert (V)\n";

        // Saisir et jouer le coup
        auto [i, j] = saisirCoup(jeu);
        jeu.jouer(i, j);
        cout << jeu;

        // Vérifier fin de partie
        s = jeu.getStatus();
        if (s == Status::RougeGagne) { cout << "\nRouge a gagné !\n"; break; }
        if (s == Status::VertGagne)  { cout << "\nVert a gagné !\n";  break; }
        if (s == Status::Egalite)    { cout << "\nÉgalité !\n";       break; }
    }

    return 0;
}