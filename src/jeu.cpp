#include <iostream>
#include <cstdlib>
#include "jeu.h"
#include "player.h"
#include "ia.h"
#include "unite.h"
#include "archer.h"
#include "fantassin.h"
#include "catapulte.h"
#include "super_soldat.h"

Jeu::Jeu():taille_champ(12),tourMax(100){
    for (int i=0;i<taille_champ;i++) {
        Unite* unit=new Unite(0,0,0,0,0,0);
        champ.push_back(unit);
    }
}

void Jeu::debutJeu(){
    system("clear");
    Player p1=Player(1);
    Player p2=Player(2);
    IA ai=IA();
    std::cout<< "   /$$$$$$   /$$$$$$  /$$$$$$$$        /$$$$$$  /$$$$$$$$       /$$      /$$  /$$$$$$  /$$$$$$$  \n "
                " /$$__  $$ /$$__  $$| $$_____/       /$$__  $$| $$_____/      | $$  /$ | $$ /$$__  $$| $$__  $$ \n "
                "| $$  \\ $$| $$  \\__/| $$            | $$  \\ $$| $$            | $$ /$$$| $$| $$  \\ $$| $$  \\ $$\n "
                "| $$$$$$$$| $$ /$$$$| $$$$$         | $$  | $$| $$$$$         | $$/$$ $$ $$| $$$$$$$$| $$$$$$$/\n "
                "| $$__  $$| $$|_  $$| $$__/         | $$  | $$| $$__/         | $$$$_  $$$$| $$__  $$| $$__  $$\n "
                "| $$  | $$| $$  \\ $$| $$            | $$  | $$| $$            | $$$/ \\  $$$| $$  | $$| $$  \\ $$\n "
                "| $$  | $$|  $$$$$$/| $$$$$$$$      |  $$$$$$/| $$            | $$/   \\  $$| $$  | $$| $$  | $$\n "
                "|__/  |__/ \\______/ |________/       \\______/ |__/            |__/     \\__/|__/  |__/|__/  |__/\n ";
    
    std::cout<<"\n 1) Joueur VS Joueur \t\t 2) Joueur VS IA \t\t 3) Sortie \n";
    int rep=0;
    std::cin>>rep;
    if (rep==1) lancerJeu(&p1,&p2);
    else if (rep==2) lancerJeu(&p1);
}


void Jeu::lancerJeu(Player *p1, Player *p2){
    int cpt=-1;
    active_player=p1;
    
    while(!p1->aPerdu() && !p2->aPerdu() && cpt<=2*tourMax){
        cpt++;
        if (cpt%2==0) active_player=p1;
        else active_player=p2;
        active_player->addOr(remuneration);
        system("clear");
        
        active_player->print();
        afficherMap();
        achat();
        // deroulement du jeu
    }
}



void Jeu::lancerJeu(Player *p1){

}

void Jeu::achat(){
    int tour;
    if (active_player->getId()==1) tour=1;
    else tour=10;
    std::cout<<"\n\n";
    Unite* choix=new Unite(0,0,0,0,0,0);
    if (champ.at(tour)->getId()!=0) {
        int rien;
        std::cout<<" Vous ne pouvez pas ajouter d'unites, appuyez sur n'importe quelle touche puis entrer pour continuer.";
        std::cin>>rien;
    }else {
        int choixAchat;
        
        bool peutAcheter=false;
        while (!peutAcheter){
            std::cout<<" Que voulez vous acheter ? \n 1) Fantassin-10 Po\t\t 2) Archer-12 Po\t\t 3) Catapultes-20 Po \t\t 4) rien"<<std::endl;
            std::cin>>choixAchat;
            while (choixAchat<1 || choixAchat>4)
            {
                std::cout<<" ! Vous devez choisir entre 1, 2 et 3 !"<<std::endl;
                std::cout<<" 1) Fantassin-10 Po \t\t 2) Archer-12 Po\t\t 3) Catapultes-20 Po \t\t 4) rien"<<std::endl;
                std::cin>>choixAchat;
            }
            if (choixAchat==1){ //faire en sorte de check la thune et prelever
                choix=new Fantassin(active_player->getId());
            }else if (choixAchat==2){
                choix=new Archer(active_player->getId());
            }else if (choixAchat==3){
                choix=new Catapulte(active_player->getId());
            }else peutAcheter=true;
            if (active_player->getBalance()>=choix->getPrix()) 
            {
                peutAcheter=true;
                champ.at(tour)=choix;
                active_player->payer(choix->getPrix());
            }else {
                std::cout<<" Vous n'avez pas assez de pieces d'or pour payer !\n";
            }
        }
    }
}

void Jeu::afficherMap(){    
    std::string res="";
    for (int i=1;i<taille_champ-1;i++){
        res+= champ[i]->getUnit();
        //else res+= "___";
    }

    std::string retour =    " |\\/\\/\\/|" "\t\t\t\t\t\t\t" " |\\/\\/\\/| \n"    
                            " |      | "  "\t\t\t\t\t\t\t"  " |      | \n"
                            " |      | "  "\t\t\t\t\t\t\t"  " |      | \n"
                            " |  P1  |   "   + res +      "\t |  P2  | \n";
    std::cout<<retour;
}

Jeu::~Jeu(){
    for (Unite *u: champ) delete u;
}