#ifndef UNITE_H
#define UNITE_H


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
        void action1();
        void action2();
        void action3();
        void attaque(Unite& ennemis)
        
};

 #endif
