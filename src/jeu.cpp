#include <iostream>
#include <cstdlib>
#include "jeu.h"
#include "ia.h"
#include "archer.h"
#include "fantassin.h"
#include "catapulte.h"
#include "super_soldat.h"

Jeu::Jeu():taille_champ(12),tourMax(100){
    for (int i=0;i<taille_champ;i++) {
        champ.push_back(nullptr);
    }
}

void Jeu::debutJeu(){
    system("clear");
    p1=new Player(1);
    p2=new Player(2);
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
    if (rep==1) lancerJeu(p1,p2);
    else if (rep==2) lancerJeu(p1);
}


void Jeu::lancerJeu(Player *p1, Player *p2){
    int cpt=-1;
    active_player=p1;
    inactive_player=p2;
    while(!p1->aPerdu() && !p2->aPerdu() && cpt<=2*tourMax){
        cpt++;
        if (cpt%2==0){
            active_player=p1;
            inactive_player=p2;
        } 
        else {
            active_player=p2;
            inactive_player=p1;
        }
        active_player->addOr(remuneration);
        system("clear");
        
        active_player->print();
        afficherMap();
        if (cpt==0) achat();
        else{
            lanceAction1();
            lanceAction2();
            lanceAction3();
            achat();
        }
        // deroulement du jeu
    }
}



void Jeu::lancerJeu(Player *p1){

}

void Jeu::achat(){
    int tour=1;
    if (active_player->getId()==1) tour=1;
    else tour=10;
    std::cout<<"\n\n";
    Unite* choix;
    if (champ.at(tour)!=nullptr) {
        std::string rien;
        std::cout<<" Vous ne pouvez pas ajouter d'unites, appuyez sur n'importe quelle touche puis entrer pour continuer.";
        std::cin>>rien;
    }else {
        int choixAchat=0;
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
            if (choixAchat==4) { break;}
            else {
                if (choixAchat==1){ //faire en sorte de check la thune et prelever
                choix=new Fantassin(active_player);
                }else if (choixAchat==2){
                    choix=new Archer(active_player);
                }else if (choixAchat==3){
                    choix=new Catapulte(active_player);
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
}

void Jeu::afficherMap(){    
    std::string res="";
    std::string pv="";
    std::string vide=" ___ ";

    for (int i=1;i<taille_champ-1;i++){
        if (champ.at(i)==nullptr) {
            res+=vide;
            pv+= "     ";
        }
        else{
            if (champ.at(i)->getPlayer()==p1){
                res+= " _"+champ[i]->getUnit()+"- ";
            }else res+= " -"+champ[i]->getUnit()+"_ ";
            if (champ.at(i)->getHp()!=0) pv+= " "+std::to_string(champ.at(i)->getHp())+" ";
            else pv+= "     ";
        }
    }

    std::string retour =    " |\\/\\/\\/|" "\t\t\t\t\t\t\t" " |\\/\\/\\/| \n"    
                            " |      | "  "\t\t\t\t\t\t\t"  " |      | \n"
                            " |      | "  "\t\t\t\t\t\t\t"  " |      | \n"
                            " |  P1  |   "   + res +      "\t |  P2  | \n"
                            "            "+pv;
    
    std::cout<<retour;
}

void Jeu::lanceAction1(){
    for (int i=1;i<taille_champ-1;i++){
        if (champ.at(i)!=nullptr){
            if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                champ.at(i)->action1(i,champ,inactive_player);
        }
    }
}

void Jeu::lanceAction2(){
    if (active_player->getId()>inactive_player->getId()){
        for (int i=1;i<taille_champ-1;i++){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action2(i,champ,inactive_player);
            }
        }
    } else {
        for (int i=taille_champ-2;i>0;i--){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action2(i,champ,inactive_player);
            }
        }
    }
    
}

void Jeu::lanceAction3(){
    if (active_player->getId()>inactive_player->getId()){
        for (int i=1;i<taille_champ-1;i++){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action3(i,champ,inactive_player);
            }
        }
    } else {
        for (int i=taille_champ-2;i>0;i--){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action3(i,champ,inactive_player);
            }
        }
    }
    
}

Jeu::~Jeu(){
    for (Unite *u: champ) delete u;
}