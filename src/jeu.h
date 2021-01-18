#ifndef JEU_H
#define JEU_H
#include "unite.h"
#include "player.h"
#include<cstdlib>
#include<vector>


class Jeu{
    private:
        const int taille_champ;
        std::vector<Unite*> champ;
        const int tourMax;
        Player *active_player;
        Player *inactive_player;
        Player* p1;
        Player* p2;
        Player* p3;
        int remuneration=8;
        bool fin=false;
        int cptTour=-1;
        std::string colorTitre="\033[1;31m";
        std::string colorP1Deb="\033[36m";
        std::string colorP2Deb="\033[33m";
        std::string colorP1DebBold="\033[1;36m";
        std::string colorP2DebBold="\033[1;33m";
        std::string colorFin="\033[0m";
    public:
        Jeu();
        ~Jeu();
        void lancerJeu(bool continu=false);
        void debutJeu();
        void sauvegarder();
        void lancerJeuIa(bool continu=false);
        void afficherMap();
        void achat();
        void achatIA();
        void lanceAction1();
        void lanceAction2();
        void lanceAction3();
        void checkMort();
        void sauvegarder(int cpt);
        void charger();
};

 #endif
