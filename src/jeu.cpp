#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
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
    std::cout<< colorTitre+"\n   /$$$$$$   /$$$$$$  /$$$$$$$$        /$$$$$$  /$$$$$$$$       /$$      /$$  /$$$$$$  /$$$$$$$  \n "
                " /$$__  $$ /$$__  $$| $$_____/       /$$__  $$| $$_____/      | $$  /$ | $$ /$$__  $$| $$__  $$ \n "
                "| $$  \\ $$| $$  \\__/| $$            | $$  \\ $$| $$            | $$ /$$$| $$| $$  \\ $$| $$  \\ $$\n "
                "| $$$$$$$$| $$ /$$$$| $$$$$         | $$  | $$| $$$$$         | $$/$$ $$ $$| $$$$$$$$| $$$$$$$/\n "
                "| $$__  $$| $$|_  $$| $$__/         | $$  | $$| $$__/         | $$$$_  $$$$| $$__  $$| $$__  $$\n "
                "| $$  | $$| $$  \\ $$| $$            | $$  | $$| $$            | $$$/ \\  $$$| $$  | $$| $$  \\ $$\n "
                "| $$  | $$|  $$$$$$/| $$$$$$$$      |  $$$$$$/| $$            | $$/   \\  $$| $$  | $$| $$  | $$\n "
                "|__/  |__/ \\______/ |________/       \\______/ |__/            |__/     \\__/|__/  |__/|__/  |__/\n "+colorFin;
    
    std::cout<<"\n 1) Joueur VS Joueur \t\t 2) Joueur VS IA \t\t 3) Sortie \t\t 4) Charger\n";
    
    int rep=0;
    std::cin>>rep;
    if (rep==1) lancerJeu();
    else if (rep==2) lancerJeuIa();
    else if (rep==4) {
        charger();
    }
    //system("clear");
}


void Jeu::lancerJeu(bool continu){
    bool continuGame=continu;

    while(cpt<2*tourMax){
        if (!continuGame) cpt++;
        if (cpt%2==0){
            active_player=p1;
            inactive_player=p2;
        } 
        else {
            active_player=p2;
            inactive_player=p1;
        }
        
        system("clear");
        if (active_player==p1)std::cout<<std::endl<<colorP1DebBold+active_player->print()+colorFin;
        else std::cout<<std::endl<<colorP2DebBold+active_player->print()+colorFin;
        afficherMap();

        if (cpt==0) {
            if (!continuGame)
            {
                active_player->addOr(remuneration);
            }else continuGame=false;
            achat();
            if (fin) break;
        }
        else{
            if (!continuGame){
                active_player->addOr(remuneration);
                lanceAction1();
                lanceAction2();
                lanceAction3();
                checkMort();
            }
            else continuGame=false;
            std::cout<<std::endl<<std::endl;
            afficherMap();
            if (p1->aPerdu() || p2->aPerdu()) break;
            achat();
            if (fin) break;
        }
    }
    if (p1->aPerdu() || p2->aPerdu()){
        std::cout<<"\n\nLe joueur "<<active_player->getId()<<" a gagne... bien joue.\n\nEntrez n'importe quoi pour finir !";
        std::string fini;
        std::cin>>fini;
        std::ofstream fichier("save.txt");
        fichier<<"vide";
        fichier.close();
    } else if (fin){
        /* faire des trucs*/
        sauvegarder();
    }
}



void Jeu::lancerJeuIa(){
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
                if (choixAchat==1){
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
    std::string prems,der;
    std::string pvPrems,pvDer;
    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)==nullptr) {
            if (i==0) {
                prems="     ";
                pvPrems="     ";
            }
            else if (i==taille_champ-1) {
                der="     ";
                pvDer="     ";
            }
            else 
            {
                res+=vide;
                pv+= "     ";
            }
        }
        else{
            if (champ.at(i)->getPlayer()==p1){
                if (i==0) {
                    prems=" _"+champ[i]->getUnit()+"- ";
                    prems=colorP1DebBold+prems+colorFin;
                }
                else res+= colorP1DebBold+" _"+champ[i]->getUnit()+"- "+colorFin;
            }else {
                if (i==taille_champ-1) {
                    der= " -"+champ[i]->getUnit()+"_ ";
                    der=colorP2DebBold+der+colorFin;
                }
                else res+= colorP2DebBold+" -"+champ[i]->getUnit()+"_ "+colorFin;
            }
            if (champ.at(i)->getHp()!=0) {
                std::string pvCourant="";
                if (champ.at(i)->getHp()>=10) pvCourant= "  "+std::to_string(champ.at(i)->getHp())+" ";
                else pvCourant= "  "+std::to_string(champ.at(i)->getHp())+"  ";

                if (i==0) pvPrems=colorP1DebBold+pvCourant+colorFin;
                else if (i==taille_champ-1) pvDer=colorP2DebBold+pvCourant+colorFin;
                else {
                    if (champ.at(i)->getPlayer()==p1) pv=pv+colorP1DebBold+pvCourant+colorFin;
                    else pv=pv+colorP2DebBold+pvCourant+colorFin;
                }
            }
        }
    }
    std::string retour= colorP1Deb+"  / \\               / \\  "+colorFin+  "\t\t\t    "   +colorP2Deb+          "  / \\               / \\ "+colorFin+"\n"+
                        colorP1Deb+" /   \\             /   \\ "+colorFin+  "\t\t\t    "   +colorP2Deb+          " /   \\             /   \\"+colorFin+"\n"+
                        colorP1Deb+"(_____)           (_____)  "+colorFin+  "\t\t\t    "   +colorP2Deb+          "(_____)           (_____)"+colorFin+"\n"+
                        colorP1Deb+" |   |  _   _   _  |   |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |  _   _   _  |   |"+colorFin+"\n"+
                        colorP1Deb+" | O |_| |_| |_| |_| O |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " | O |_| |_| |_| |_| O |"+colorFin+"\n"+
                        colorP1Deb+" |-  |          _  | - |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |-  |          _  | - |"+colorFin+"\n"+
                        colorP1Deb+" |   |   - _^_     |   |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   - _^_     |   |"+colorFin+"\n"+
                        colorP1Deb+" |  _|    //|\\\\  - |   | "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |  _|    //|\\\\  - |   |"+colorFin+"\n"+
                        colorP1Deb+" |   |   ///|\\\\\\   |  -|"+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   ///|\\\\\\   |  -|"+colorFin+"\n"+
                        colorP1Deb+" |   |   |||||||   |-  |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   |||||||   |-  |"+colorFin+"\n"+
                        colorP1Deb+" |___|___| "+colorP1DebBold+ +"P1-"+colorFin+colorP1Deb+" |___|___|   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |___|___| "+colorP2DebBold+ "-P2"+colorFin+colorP2Deb+" |___|___|"+colorFin+"\n"+
                        colorP1Deb+"         (      (          "+colorFin+  "\t\t\t    "   +colorP2Deb+          "         )      )"+colorFin+"\n"+
                        colorP1Deb+"          \\"+colorFin+prems+colorP1Deb+" \\       "+colorFin+  "\t\t\t    " +colorP2Deb+ "        / "+colorFin+ der+colorP2Deb+"/"+colorFin+"\n"+
                        colorP1Deb+"           )"+colorFin+pvPrems+colorP1Deb+" )        "+colorFin+  "\t\t\t    "  +colorP2Deb+           "       ( "+colorFin+pvDer+colorP2Deb+"("+colorFin+"\n"
                        "              "+ res +      "         \n"
                        "              "+pv;
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
    save+=std::to_string(p1->getId())+";"+std::to_string(p1->getVie())+";"+std::to_string(p1->getBalance())+"\n";
    save+=std::to_string(p2->getId())+";"+std::to_string(p2->getVie())+";"+std::to_string(p2->getBalance())+"\n";

    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)!=nullptr){
            save+=std::to_string(champ.at(i)->getPlayer()->getId())+";"+std::to_string(champ.at(i)->getHp())+";"+champ.at(i)->getType()+";"+std::to_string(i)+"\n";
        }
    }
    std::ofstream fichier("save.txt");
    fichier<<save;
    fichier.close();
}

void Jeu::charger(){
    std::ifstream save("save.txt");
    if (save){
        std::string contenu;
        getline(save,contenu);
        if (contenu!="vide"){
            std::string mot;
            cpt=stoi(contenu);

            getline(save,contenu); 
            std::vector<std::string> j1;
            std::stringstream ss(contenu);
            while (std::getline(ss,mot,';')){
                j1.push_back(mot);
            }

            getline(save,contenu);
            std::vector<std::string> j2;
            std::stringstream ss1(contenu);
            while (std::getline(ss1,mot,';')){
                j2.push_back(mot);
            }

            p1=new Player(stoi(j1.at(0)));
            p1->setHp(stoi(j1.at(1)));
            p1->setBalance(stoi(j1.at(2)));
            p2=new Player(stoi(j2.at(0)));
            p2->setHp(stoi(j2.at(1)));
            p2->setBalance(stoi(j2.at(2)));

            while (getline(save,contenu)){
                std::vector<std::string> unit;
                std::string res;
                std::stringstream ss2(contenu);
                while (std::getline(ss2,res,';')){
                    unit.push_back(res);
                }
            
                int idP=stoi(unit.at(0));
                int hp=stoi(unit.at(1));
                std::string type=unit.at(2);
                int pos=stoi(unit.at(3));
                Unite* unite;
                Player* joueur;
                if (idP==p1->getId()) joueur=p1;
                else joueur=p2;
                if (type=="Fantassin") unite=new Fantassin(joueur);
                else if (type=="Archer") unite=new Archer(joueur);
                else if (type=="Catapulte") unite=new Catapulte(joueur);
                else unite=new SuperSoldat(hp,joueur);
                unite->setHp(hp);
                champ.at(pos)=unite;
                
            }
            lancerJeu(true);
        }else{
            std::cout<<"Il n'y a pas de partie a charger.\n";
        }
    }else std::cout<<"Il n'y a pas de partie a charger.\n";
}


Jeu::~Jeu(){
    for (Unite *u: champ) delete u;
}
