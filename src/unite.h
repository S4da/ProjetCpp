#ifndef UNITE_H
#define UNITE_H

#include<vector>

class Unite{
    private:
        int prix;
        int pv;
        int rangeMin;
        int rangeMax;
        int atk;
        int numJoueur;
    public:
        Unite(int prix, int pv, int rangeMin, int rangeMax,int atk,int numJoueur);
        virtual ~Unite();
        virtual void setHp(int vie) { pv=vie;};
        virtual std::string getUnit() { return " ___ ";};
        int getPrix() {return prix;};
        int getId() {return numJoueur;};
        void damage(int dmg) { pv-=dmg;};
        virtual void action1(int pos, std::vector<Unite*> &champ){};
        virtual void action2(int pos, std::vector<Unite*> &champ){};
        virtual void action3(int pos, std::vector<Unite*> &champ){};
        void attaque(Unite* ennemi);
        
};

 #endif
