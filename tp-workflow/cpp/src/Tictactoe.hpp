#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <array>
#include <iostream>

/// Statut courant de la partie.
enum class Status { Egalite, RougeGagne, VertGagne, RougeJoue, VertJoue };

/// Contenu d'une case du plateau.
enum class Cell { Vide, Rouge, Vert };

/// \brief Moteur de jeu de Tic-Tac-Toe.
///
/// Rouge joue en premier. Le status est mis à jour après chaque coup.
class Jeu {
    private:
        std::array<std::array<Cell, 3>, 3> _plateau; ///< Plateau 3×3
        Status _status;                               ///< Statut courant

    public:
        /// Constructeur : initialise un jeu vide, Rouge joue en premier.
        Jeu();

        /// Retourne le status du jeu courant (Egalite, RougeGagne, VertGagne, RougeJoue, VertJoue).
        Status getStatus() const;

        /// Retourne l'état d'une case du plateau.
        Cell getCell(int i, int j) const;

        /// \brief Joue un coup pour le joueur courant.
        ///
        /// \param i ligne choisie (0, 1 ou 2)
        /// \param j colonne choisie (0, 1 ou 2)
        /// \return true si le coup est valide et a été joué, false sinon.
        bool jouer(int i, int j);

        /// Réinitialise le jeu (plateau vide, Rouge joue en premier).
        void raz();
};

/// Affiche le plateau sur un flux de sortie.
std::ostream & operator<<(std::ostream & os, const Jeu & jeu);

#endif