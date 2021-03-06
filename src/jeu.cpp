#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
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

    std::string tryRep="";
    int rep=0;
    p1=new Player(1);
    p2=new Player(2);
    p3=new IA();
    do{
        system("clear");
        std::cout<< colorTitre+"\n   /$$$$$$   /$$$$$$  /$$$$$$$$        /$$$$$$  /$$$$$$$$       /$$      /$$  /$$$$$$  /$$$$$$$  \n "
                    " /$$__  $$ /$$__  $$| $$_____/       /$$__  $$| $$_____/      | $$  /$ | $$ /$$__  $$| $$__  $$ \n "
                    "| $$  \\ $$| $$  \\__/| $$            | $$  \\ $$| $$            | $$ /$$$| $$| $$  \\ $$| $$  \\ $$\n "
                    "| $$$$$$$$| $$ /$$$$| $$$$$         | $$  | $$| $$$$$         | $$/$$ $$ $$| $$$$$$$$| $$$$$$$/\n "
                    "| $$__  $$| $$|_  $$| $$__/         | $$  | $$| $$__/         | $$$$_  $$$$| $$__  $$| $$__  $$\n "
                    "| $$  | $$| $$  \\ $$| $$            | $$  | $$| $$            | $$$/ \\  $$$| $$  | $$| $$  \\ $$\n "
                    "| $$  | $$|  $$$$$$/| $$$$$$$$      |  $$$$$$/| $$            | $$/   \\  $$| $$  | $$| $$  | $$\n "
                    "|__/  |__/ \\______/ |________/       \\______/ |__/            |__/     \\__/|__/  |__/|__/  |__/ :RIP OFF\n "+colorFin;
        
        std::cout<<"\n 1) Joueur VS Joueur \t\t 2) Joueur VS IA \t\t 3) Charger \t\t 9) Sortie\n";
        std::cout<<"\n 4) One Shot (Mode PVP ou chaque joueur ne possede qu'1 point de vie)\n";
        
        
        std::cin>>tryRep;
        try{
            rep=stoi(tryRep);
            if (rep==1) lancerJeu();
            else if (rep==2) lancerJeuIa();
            else if (rep==3) {
                rep=charger();
            }else if (rep==4){
                p1->setHp(1);
                p2->setHp(1);
                lancerJeu();
            }
        }catch(...){}
    }while(rep!=9);
    //system("clear");
}


void Jeu::lancerJeu(bool continu){

    bool continuGame=continu;
    std::string affPlayer="";
    std::string next;

    while(cptTour<2*tourMax){
        if (!continuGame) cptTour++;
        if (cptTour%2==0){
            active_player=p1;
            inactive_player=p2;
        } 
        else {
            active_player=p2;
            inactive_player=p1;
        }
        
        system("clear");
        system("clear");
        if (!continuGame)
        {
            active_player->addOr(remuneration);
        }

        if (active_player==p1)affPlayer="\n"+colorP1DebBold+active_player->print()+colorFin;
        else affPlayer="\n"+colorP2DebBold+active_player->print()+colorFin;

        std::cout<<affPlayer;
        afficherMap();

        if (cptTour==0) {
            if (continuGame)
            {
                continuGame=false;
            }
            achat();
            if (fin) break;
        }
        else{
            if (!continuGame){
                lanceAction1();
                lanceAction2();
                lanceAction3();
                checkMort();
            }
            else continuGame=false;
            
            std::cout<<"\n\nEntrez nimporte quoi pour finir de voir vos actions: ";
            std::cin>>next;
            //std::cout<<std::endl<<std::endl;
            system("clear");
            system("clear");
             if (active_player==p1)std::cout<<std::endl<<colorP1DebBold+active_player->print()+colorFin;
            else std::cout<<std::endl<<colorP2DebBold+active_player->print()+colorFin;
            afficherMap();
            if (p1->aPerdu() || p2->aPerdu()) break;
            achat();
            if (fin) break;
        }
    }
    if (p1->aPerdu() || p2->aPerdu()){
        if (p1->aPerdu()) active_player=p2;
        else active_player=p1;
        std::cout<<"\n\nLe joueur "<<active_player->getId()<<" a gagne... bien joue.\n\nEntrez n'importe quoi pour finir !";
        std::string fini;
        std::cin>>fini;
        std::ofstream fichier(saveName);
        fichier<<"vide";
        fichier.close();
    } else if (fin && goSave){
        /* faire des trucs*/
        sauvegarder();
    }
    resetPlateau();
}



void Jeu::lancerJeuIa(bool continu){
    bool continuGame=continu;
    active_player=p1;
    inactive_player=p3;
    std::string next;
    while(cptTour<2*tourMax){
        if (!continuGame) cptTour++;
        system("clear");
        system("clear");
        if (cptTour%2==0){
            active_player=p1;
            inactive_player=p3;
            system("clear");
            system("clear");
            if (!continuGame)
            {
                active_player->addOr(remuneration);
            }
            std::cout<<std::endl<<colorP1DebBold+active_player->print()+colorFin;
            afficherMap();
            
            if (cptTour==0) {
                
                if (continuGame)
                {
                    continuGame=false;
                }
                achat();
                if (fin) break;
                
            }
            else{
                if (!continuGame){
                    lanceAction1();
                    lanceAction2();
                    lanceAction3();
                    checkMort();
                }
                else continuGame=false;
                std::cout<<"\n\nEntrez nimporte quoi pour finir de voir vos actions: ";
                std::cin>>next;
                system("clear");
                system("clear");
                //std::cout<<std::endl<<std::endl;
                std::cout<<std::endl<<colorP1DebBold+active_player->print()+colorFin;
                afficherMap();
                if (inactive_player->aPerdu()) break;
                achat();
                if (fin) break;
            }
        }else{
            active_player=p3;
            inactive_player=p1;
            system("clear");
            active_player->addOr(remuneration);
            std::cout<< std::endl<<colorP2DebBold+active_player->print()+colorFin;
            afficherMap();
            lanceAction1();
            checkMort();
            lanceAction2();
            checkMort();
            lanceAction3();
            checkMort();
            std::cout<<std::endl;
            std::cout<<std::endl<<std::endl;
            if (inactive_player->aPerdu()) break;
            sleep(2);
            achatIA();
        }
    }
    if (p1->aPerdu() || p3->aPerdu()){
            if (p1->aPerdu()) active_player=p3;
            std::cout<<"\n\nLe joueur "<<active_player->getId()<<" a gagne... bien joue.\n\nEntrez n'importe quoi pour finir !";
            std::string fini;
            std::cin>>fini;
            std::ofstream fichier(saveName);
            fichier<<"vide";
            fichier.close();
            
        } else if (fin && goSave){
            /* faire des trucs*/
            sauvegarder();
        }
    resetPlateau();
}


void Jeu::achat(){
    int tour=0;
    std::string choixAction=" 1) Fantassin-10 Po \t 2) Archer-12 Po\t 3) Catapultes-20 Po \t 4) rien \t 5) Sauvegarder et quitter \t 6) Quitter sans sauvegarder\n 7) Abandonner";
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
            
            while (choixAchat<1 || choixAchat>7)
            {
                std::cout<<" ! Vous devez choisir entre 1, 2, 3, 4, 5, 6et 7 !"<<std::endl;
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
                 goSave=true;
                 break;
                 }
            else if (choixAchat==6) {
                fin=true;
                break;
                }
            else if (choixAchat==7) {
                fin=true;
                active_player->setHp(-1);
                break;
            }
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

void Jeu::achatIA(){
    int tour=taille_champ-1;
    Unite* choix;
    if (champ.at(tour)==nullptr) {
        
        int choixAchat=p3->jouer();
        bool achete=true;
        if (choixAchat==1){
        choix=new Fantassin(active_player);
        }else if (choixAchat==2){
            choix=new Archer(active_player);
        }else if (choixAchat==3){
            choix=new Catapulte(active_player);
        }else achete=false;
        if (achete) 
        {
            champ.at(tour)=choix;
            p3->payer(choix->getPrix());
        }
    }
}


void Jeu::afficherMap(){    
    std::string res1="", res2="", res3="";
    std::string pv="";
    std::string vide=" ___ ";
    std::string prems1,prems2,prems3,der1,der3,der2;
    std::string pvPrems,pvDer;
    std::string normeEspace= "     ";
    std::string pvP1="   ",pvP2="   ";

    if (inactive_player==p3 || active_player==p3){
        if (p3->getVie()<10 && p3->getVie()>=0) pvP2=" "+std::to_string(p3->getVie())+" ";
        else if (p3->getVie()<100) pvP2=std::to_string(p3->getVie())+" "; 
        else pvP2=std::to_string(p3->getVie());
        pvP2=colorP2DebBold+pvP2+colorFin;
    }else {
        if (p2->getVie()<10 && p2->getVie()>=0) pvP2=" "+std::to_string(p2->getVie())+" ";
        else if (p2->getVie()<100) pvP2=std::to_string(p2->getVie())+" "; 
        else pvP2=std::to_string(p2->getVie());
        pvP2=colorP2DebBold+pvP2+colorFin;
    }
    if (p1->getVie()<10 && p1->getVie()>=0) pvP1=" "+std::to_string(p1->getVie())+" ";
    else if (p1->getVie()<100) pvP1=std::to_string(p1->getVie())+" ";
    else pvP1=std::to_string(p1->getVie()); 
    pvP1=colorP1DebBold+pvP1+colorFin;
    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)==nullptr) {
            if (i==0) {
                prems1="     ";
                prems2="     ";
                prems3="     ";
                pvPrems="     ";
            }
            else if (i==taille_champ-1) {
                der1="     ";
                der2="     ";
                der3="     ";
                pvDer="     ";
            }
            else 
            {
                res1+=normeEspace;
                res2+=normeEspace;
                res3+=vide;
                pv+= "     ";
            }
        }
        else{
            if (champ.at(i)->getPlayer()==p1){
                if (i==0) {
                    prems1=colorP1DebBold+"  "+champ[i]->getUnitp11()+""+colorFin;
                    prems2=colorP1DebBold+" "+champ[i]->getUnitp12()+" "+colorFin;
                    prems3=colorP1DebBold+""+champ[i]->getUnitp13()+"  "+colorFin;
                }
                else {
                    res1+= colorP1DebBold+" "+champ[i]->getUnitp11()+" "+colorFin;
                    res2+= colorP1DebBold+" "+champ[i]->getUnitp12()+" "+colorFin;
                    res3+= colorP1DebBold+" "+champ[i]->getUnitp13()+" "+colorFin;
                }
            }else {
                if (i==taille_champ-1) {
                    der1=colorP2DebBold+" "+champ[i]->getUnitp21()+" "+colorFin;
                    der2=colorP2DebBold+" "+champ[i]->getUnitp22()+" "+colorFin;
                    der3=colorP2DebBold+"  "+champ[i]->getUnitp23()+""+colorFin;
                }
                else {
                    res1+= colorP2DebBold+" "+champ[i]->getUnitp21()+" "+colorFin;
                    res2+= colorP2DebBold+" "+champ[i]->getUnitp22()+" "+colorFin;
                    res3+= colorP2DebBold+" "+champ[i]->getUnitp23()+" "+colorFin;
                }
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
                        colorP1Deb+" /   \\             /"+colorFin+pvP1+colorP1Deb+"\\ "+colorFin+  "\t\t\t    "   +colorP2Deb+          " /"+colorFin+pvP2+colorP2Deb+"\\             /   \\"+colorFin+"\n"+
                        colorP1Deb+"(_____)           (_____)  "+colorFin+  "\t\t\t    "   +colorP2Deb+          "(_____)           (_____)"+colorFin+"\n"+
                        colorP1Deb+" |   |  _   _   _  |   |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |  _   _   _  |   |"+colorFin+"\n"+
                        colorP1Deb+" | O |_| |_| |_| |_| O |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " | O |_| |_| |_| |_| O |"+colorFin+"\n"+
                        colorP1Deb+" |-  |          _  | - |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |-  |          _  | - |"+colorFin+"\n"+
                        colorP1Deb+" |   |   - _^_     |   |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   - _^_     |   |"+colorFin+"\n"+
                        colorP1Deb+" |  _|    //|\\\\  - |   | "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |  _|    //|\\\\  - |   |"+colorFin+"\n"+
                        colorP1Deb+" |   |   ///|\\\\\\   |  -|"+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   ///|\\\\\\   |  -|"+colorFin+"\n"+
                        colorP1Deb+" |   |   |||||||   |-  |   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |   |   |||||||   |-  |"+colorFin+"\n"+
                        colorP1Deb+" |___|___| "+colorP1DebBold+ +"P1-"+colorFin+colorP1Deb+" |___|___|   "+colorFin+  "\t\t\t    "   +colorP2Deb+          " |___|___| "+colorP2DebBold+ "-P2"+colorFin+colorP2Deb+" |___|___|"+colorFin+"\n"+
                        colorP1Deb+"         ("+colorFin+prems1+colorP1Deb+"(          "+colorFin+  "\t\t\t    "   +colorP2Deb+          "         )"+colorFin+ der1+colorP2Deb+")"+colorFin+"\n"+
                        colorP1Deb+"          \\"+colorFin+prems2+colorP1Deb+" \\       "+colorFin+  "\t\t\t    " +colorP2Deb+ "        / "+colorFin+ der2+colorP2Deb+"/"+colorFin+"\n"+
                        colorP1Deb+"           )"+colorFin+prems3+colorP1Deb+" )        "+colorFin+  "\t\t\t    "  +colorP2Deb+           "       ( "+colorFin+ der3+colorP2Deb+"("+colorFin+"\n"+
                        colorP1Deb+"           )"+colorFin+pvPrems+colorP1Deb+" )        "+colorFin+  "\t\t\t    "  +colorP2Deb+           "       ( "+colorFin+pvDer+colorP2Deb+"("+colorFin+"\n\n"
                        "              "+ res1 +      "         \n"
                        "              "+ res2 +      "         \n"
                        "              "+ res3 +      "         \n"
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
    save+=std::to_string(cptTour)+"\n";
    save+=std::to_string(p1->getId())+";"+std::to_string(p1->getVie())+";"+std::to_string(p1->getBalance())+"\n";
    if (inactive_player==p2 || active_player==p2) save+=std::to_string(p2->getId())+";"+std::to_string(p2->getVie())+";"+std::to_string(p2->getBalance())+"\n";
    else save+=std::to_string(p3->getId())+";"+std::to_string(p3->getVie())+";"+std::to_string(p3->getBalance())+"\n";

    for (int i=0;i<taille_champ;i++){
        if (champ.at(i)!=nullptr){
            save+=std::to_string(champ.at(i)->getPlayer()->getId())+";"+std::to_string(champ.at(i)->getHp())+";"+champ.at(i)->getType()+";"+std::to_string(i)+"\n";
        }
    }
    std::ofstream fichier(saveName);
    fichier<<save;
    fichier.close();
}

int Jeu::charger(){
    std::ifstream save(saveName);
    bool pvp=true;
    if (save){
        std::string contenu;
        getline(save,contenu);
        if (contenu!="vide"){
            std::string mot;
            cptTour=stoi(contenu);

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
            if (stoi(j2.at(0))==2){
                p2=new Player(stoi(j2.at(0)));
                p2->setHp(stoi(j2.at(1)));
                p2->setBalance(stoi(j2.at(2)));
            }else{
                p3=new IA();
                p3->setHp(stoi(j2.at(1)));
                p3->setBalance(stoi(j2.at(2)));
                pvp=false;
            }

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
                else if (idP==p2->getId()) joueur=p2;
                else joueur=p3;
                if (type=="Fantassin") unite=new Fantassin(joueur);
                else if (type=="Archer") unite=new Archer(joueur);
                else if (type=="Catapulte") unite=new Catapulte(joueur);
                else unite=new SuperSoldat(hp,joueur);
                unite->setHp(hp);
                champ.at(pos)=unite;
                
            }
            if (pvp) lancerJeu(true);
            else lancerJeuIa(true);
        }else{
            std::cout<<"Il n'y a pas de partie a charger.\n";
        }
    }else std::cout<<"Il n'y a pas de partie a charger.\n";
    sleep(2);
    return -1;
}

void Jeu::resetPlateau(){
    p1=new Player(1);
    p2=new Player(2);
    p3=new IA();
    fin=false;
    goSave=false;
    for (int i=0;i<taille_champ;i++) champ.at(i)=nullptr;
    cptTour=-1;
}


Jeu::~Jeu(){
    for (Unite *u: champ) delete u;
}
