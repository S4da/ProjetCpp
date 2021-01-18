#ifndef UNITE_H
#define UNITE_H
#include<vector>
#include "player.h"
#define UNUSED(x) (void)(x)

class Unite{
    private:
        int prix;
        int pv;
        int rangeMin;
        int rangeMax;
        int atk;
        int numJoueur;
        Player* player=nullptr;
        std::string type="";
    public:
        Unite(int prix, int pv, int rangeMin, int rangeMax,int atk,Player* player);
        virtual ~Unite();
        virtual void setHp(int vie) { pv=vie;};
        virtual std::string getUnitp11()=0;
        virtual std::string getUnitp12() =0;
        virtual std::string getUnitp13() =0;

        virtual std::string getUnitp21() =0;
        virtual std::string getUnitp22() =0;
        virtual std::string getUnitp23() =0;
        int getPrix() {return prix;};
        Player* getPlayer() {return player;};
        void damage(int dmg) { pv-=dmg;};
        int getHp() {return pv;};
        int getAtk() {return atk;};
        int getRangeMax() { return rangeMax;};
        int getRangeMin() { return rangeMin;};
        std::string getType() { return type;};
        void setType(std::string type) { this->type=type;};
        virtual void action1(int pos, std::vector<Unite*> &champ, Player* ennemi)=0;
        virtual void action2(int pos, std::vector<Unite*> &champ, Player* ennemi);
        virtual void action3(int pos, std::vector<Unite*> &champ, Player* ennemi){ UNUSED(pos); UNUSED(champ); UNUSED(ennemi);};
        void afficherActionAtk(int pos) {std::cout<< "\nL'unite a la position "<<pos<<" attaque.";};
        void afficherActionAvance(int pos) { std::cout<< "\nL'unite a la position "<<pos<<" avance.";};
        void attaque(Unite* ennemi);
        void setPlayer(Player* p) { player=p;};
        
};

 #endif
