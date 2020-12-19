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
        int remuneration=8;
        bool fin=false;
    public:
        Jeu();
        ~Jeu();
        void lancerJeu(Player *p1, Player *p2);
        void debutJeu();
        void sauvegarder();
        void lancerJeu(Player *p1);
        void afficherMap();
        void achat();
        void lanceAction1();
        void lanceAction2();
        void lanceAction3();
        void checkMort();
};

 #endif
