#include "Tictactoe.hpp"
#include <sstream>
#include <catch2/catch.hpp>

// ═══════════════════════════════════════════════════════════
// Issue 1 : Affichage de la grille
// ═══════════════════════════════════════════════════════════

TEST_CASE("Issue1 - plateau initial vide") {
    Jeu jeu;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            REQUIRE( jeu.getCell(i, j) == Cell::Vide );
}

TEST_CASE("Issue1 - status initial RougeJoue") {
    Jeu jeu;
    REQUIRE( jeu.getStatus() == Status::RougeJoue );
}

TEST_CASE("Issue1 - affichage produit une sortie non vide") {
    Jeu jeu;
    std::ostringstream oss;
    oss << jeu;
    REQUIRE( !oss.str().empty() );
    // Les cases vides sont représentées par '.'
    REQUIRE( oss.str().find('.') != std::string::npos );
}

TEST_CASE("Issue1 - raz remet le plateau vide") {
    Jeu jeu;
    jeu.jouer(0, 0);
    jeu.raz();
    REQUIRE( jeu.getCell(0, 0) == Cell::Vide );
    REQUIRE( jeu.getStatus() == Status::RougeJoue );
}

// ═══════════════════════════════════════════════════════════
// Issue 2 : Jouer des coups + détection case libre
// ═══════════════════════════════════════════════════════════

TEST_CASE("Issue2 - jouer un coup valide place le bon joueur") {
    Jeu jeu;
    REQUIRE( jeu.jouer(0, 0) == true );
    REQUIRE( jeu.getCell(0, 0) == Cell::Rouge );
}

TEST_CASE("Issue2 - le tour alterne après un coup valide") {
    Jeu jeu;
    jeu.jouer(0, 0);
    REQUIRE( jeu.getStatus() == Status::VertJoue );
    jeu.jouer(1, 1);
    REQUIRE( jeu.getStatus() == Status::RougeJoue );
}

TEST_CASE("Issue2 - jouer sur une case occupée retourne false") {
    Jeu jeu;
    jeu.jouer(1, 1);
    REQUIRE( jeu.jouer(1, 1) == false );
    // La case ne change pas
    REQUIRE( jeu.getCell(1, 1) == Cell::Rouge );
}

TEST_CASE("Issue2 - coordonnées hors limites retournent false") {
    Jeu jeu;
    REQUIRE( jeu.jouer(-1, 0) == false );
    REQUIRE( jeu.jouer(0, 3)  == false );
    REQUIRE( jeu.jouer(3, 3)  == false );
}

TEST_CASE("Issue2 - Vert joue correctement au deuxième tour") {
    Jeu jeu;
    jeu.jouer(0, 0); // Rouge
    jeu.jouer(2, 2); // Vert
    REQUIRE( jeu.getCell(2, 2) == Cell::Vert );
}

// ═══════════════════════════════════════════════════════════
// Issue 3 : Détection de victoire
// ═══════════════════════════════════════════════════════════

TEST_CASE("Issue3 - Rouge gagne sur une ligne") {
    Jeu jeu;
    // R . .     R joue (0,0),(0,1),(0,2) avec V intercalé
    jeu.jouer(0,0); jeu.jouer(1,0);
    jeu.jouer(0,1); jeu.jouer(1,1);
    jeu.jouer(0,2);
    REQUIRE( jeu.getStatus() == Status::RougeGagne );
}

TEST_CASE("Issue3 - Vert gagne sur une colonne") {
    Jeu jeu;
    jeu.jouer(0,0); jeu.jouer(0,2);
    jeu.jouer(1,0); jeu.jouer(1,2);
    jeu.jouer(0,1); jeu.jouer(2,2);
    REQUIRE( jeu.getStatus() == Status::VertGagne );
}

TEST_CASE("Issue3 - Rouge gagne sur la diagonale principale") {
    Jeu jeu;
    jeu.jouer(0,0); jeu.jouer(0,1);
    jeu.jouer(1,1); jeu.jouer(0,2);
    jeu.jouer(2,2);
    REQUIRE( jeu.getStatus() == Status::RougeGagne );
}

TEST_CASE("Issue3 - Rouge gagne sur la diagonale anti") {
    Jeu jeu;
    jeu.jouer(0,2); jeu.jouer(0,0);
    jeu.jouer(1,1); jeu.jouer(0,1);
    jeu.jouer(2,0);
    REQUIRE( jeu.getStatus() == Status::RougeGagne );
}

TEST_CASE("Issue3 - impossible de jouer après une victoire") {
    Jeu jeu;
    jeu.jouer(0,0); jeu.jouer(1,0);
    jeu.jouer(0,1); jeu.jouer(1,1);
    jeu.jouer(0,2); // Rouge gagne
    REQUIRE( jeu.jouer(2,2) == false );
}

// ═══════════════════════════════════════════════════════════
// Issue 4 : Détection d'égalité
// ═══════════════════════════════════════════════════════════

TEST_CASE("Issue4 - egalite sur plateau plein sans gagnant") {
    Jeu jeu;
    // R V R
    // R R V
    // V R V  → aucun alignement complet pour un seul joueur
    jeu.jouer(0,0); jeu.jouer(0,1);
    jeu.jouer(0,2); jeu.jouer(1,2);
    jeu.jouer(1,0); jeu.jouer(2,0);
    jeu.jouer(1,1); jeu.jouer(2,2);
    jeu.jouer(2,1);
    REQUIRE( jeu.getStatus() == Status::Egalite );
}

TEST_CASE("Issue4 - pas egalite sur plateau non plein") {
    Jeu jeu;
    jeu.jouer(0,0);
    REQUIRE( jeu.getStatus() != Status::Egalite );
}