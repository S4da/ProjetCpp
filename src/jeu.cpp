#include <iostream>
#include <fstream>
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
    //system("clear");
}


void Jeu::lancerJeu(Player *p1, Player *p2){

    active_player=p1;
    inactive_player=p2;

    while(cpt<=2*tourMax){
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
            checkMort();
            std::cout<<std::endl<<std::endl;
            afficherMap();
            if (p1->aPerdu() || p2->aPerdu()) break;
            achat();
            if (fin) break;
        }
    }
    if (p1->aPerdu() || p2->aPerdu()){
        std::cout<<"\n\nLe joueur "<<active_player->getId()<<" a gagne... bien joue.\n\nEntrez n'importe quoi pour finir !";
        std::string fin;
        std::cin>>fin;
    } else if (fin){
        /* faire des trucs*/
        sauvegarder();
    }
}



void Jeu::lancerJeu(Player *p1){
    active_player=p1;
}

void Jeu::achat(){
    int tour=0;
    std::string choixAction=" 1) Fantassin-10 Po \t 2) Archer-12 Po\t 3) Catapultes-20 Po \t 4) rien \t 5) Sauvegarder et quitter";
    if (active_player->getId()<inactive_player->getId()) tour=0;
    else tour=taille_champ-1;
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
            std::string entree="";
            std::cout<<choixAction<<std::endl;
            std::cin>>entree;
            try{
                choixAchat=std::stoi(entree);
            }catch(...){
                choixAchat=-1;
            }
            
            while (choixAchat<1 || choixAchat>5)
            {
                std::cout<<" ! Vous devez choisir entre 1, 2 et 3 !"<<std::endl;
                std::cout<<choixAction<<std::endl;
                std::cin>>entree;
                try{
                    choixAchat=std::stoi(entree);
                }catch(...){
                    choixAchat=-1;
                }
            }
            if (choixAchat==4) { break;}
            else if (choixAchat==5) {
                 fin=true;
                 break;}
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

    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)==nullptr) {
            res+=vide;
            pv+= "     ";
        }
        else{
            if (champ.at(i)->getPlayer()==p1){
                res+= " _"+champ[i]->getUnit()+"- ";
            }else res+= " -"+champ[i]->getUnit()+"_ ";
            if (champ.at(i)->getHp()!=0) {
                if (champ.at(i)->getHp()>=10) pv+= "  "+std::to_string(champ.at(i)->getHp())+" ";
                else pv+= "  "+std::to_string(champ.at(i)->getHp())+"  ";
            }
        }
    }

    std::string retour =    " |\\/\\/\\/|""\t\t\t\t\t\t\t " "|\\/\\/\\/| \n"    
                            " |      | "  "\t\t\t\t\t\t\t "  "|      | \n"
                            " |      | "  "\t\t\t\t\t\t\t "  "|      | \n"
                            " |  P1 "   + res +      " P2  | \n"
                            "       "+pv;
    
    std::cout<<retour;
}

void Jeu::lanceAction1(){
    if (active_player->getId()<inactive_player->getId()){
        for (int i=0;i<taille_champ;i++){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()==active_player){
                    champ.at(i)->action1(i,champ,inactive_player);
                }
            }
        }
    }
    else {
        for (int i=taille_champ-1;i>=0;i--){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()==active_player){
                    champ.at(i)->action1(i,champ,inactive_player);
                }
            }
        }
    }
}

void Jeu::lanceAction2(){
    if (active_player->getId()>inactive_player->getId()){
        for (int i=0;i<taille_champ;i++){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()==active_player)
                    {
                        champ.at(i)->action2(i,champ,inactive_player);
                    }
            }
        }
    } else {
        for (int i=taille_champ-1;i>=0;i--){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()==active_player)
                {
                    champ.at(i)->action2(i,champ,inactive_player);
                }
            }
        }
    }
    
}

void Jeu::lanceAction3(){
    if (active_player->getId()>inactive_player->getId()){
        for (int i=0;i<taille_champ;i++){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action3(i,champ,inactive_player);
            }
        }
    } else {
        for (int i=taille_champ-1;i>=0;i--){
            if (champ.at(i)!=nullptr){
                if (champ.at(i)->getPlayer()->getId()==active_player->getId())
                    champ.at(i)->action3(i,champ,inactive_player);
            }
        }
    }
    
}

void Jeu::checkMort(){
    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)!=nullptr){
            if (champ.at(i)->getHp()<=0) {
                active_player->addOr(champ.at(i)->getPrix()/2);
                champ.at(i)=nullptr;
            }
        }
    }
}

void Jeu::sauvegarder(){
    std::string save="";
    save+=std::to_string(cpt)+"\n";
    save+=std::to_string(active_player->getId())+";"+std::to_string(active_player->getVie())+";"+std::to_string(active_player->getBalance())+"\n";
    save+=std::to_string(inactive_player->getId())+";"+std::to_string(inactive_player->getVie())+";"+std::to_string(inactive_player->getBalance())+"\n";

    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)!=nullptr){
            save+=std::to_string(champ.at(i)->getPlayer()->getId())+";"+std::to_string(champ.at(i)->getHp())+";"+champ.at(i)->getType()+";"+std::to_string(i)+"\n";
        }
    }
    std::ofstream fichier("save.txt");
    fichier<<save;
    fichier.close();
}


Jeu::~Jeu(){
    for (Unite *u: champ) delete u;
}