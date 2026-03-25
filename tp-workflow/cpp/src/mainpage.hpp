/// \mainpage Tic-Tac-Toe — Documentation
///
/// \section intro Introduction
/// Ce projet implémente un jeu de Tic-Tac-Toe en C++ avec :
/// - un moteur de jeu (classe \ref Jeu)
/// - une interface en ligne de commande (`tictactoe-cli`)
/// - des tests unitaires avec Catch2 (`tictactoe-test`)
/// - un binding Python via pybind11 (`tictactoe-binding`)
///
/// \section regles Règles
/// - Le joueur **Rouge** commence toujours.
/// - Les joueurs jouent à tour de rôle en choisissant une case libre (ligne, colonne).
/// - Le premier à aligner 3 symboles (ligne, colonne ou diagonale) gagne.
/// - Si le plateau est plein sans gagnant, c'est une égalité.
///
/// \section utilisation Utilisation
/// \code
/// cmake -B build && cmake --build build
/// ./build/tictactoe-cli       # jouer
/// ./build/tictactoe-test      # lancer les tests
/// \endcode