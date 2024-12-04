#ifndef MABIB_H_INCLUDED
#define MABIB_H_INCLUDED
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct Date{
  int jour;
  int mois;
  int annee;
  int heure;
  int minute;
}DATE;

typedef enum Types {Rapide,Normal} TYPE;

typedef enum Status {Disponible,Occupe,Hors_Service } STATUS;

typedef struct BorneDeRecharge{
  int Code;
  TYPE type;
  int puissance;
  STATUS status;
  int Duree;
  double prix;
}BORNE_DE_RECHARGE;

typedef enum Methode {Sur_Place,En_Ligne} METHODE;

typedef struct Paiment{
  int id;
  double montant;
  METHODE Type;
  char Token[30];
}PAIMENT;

typedef struct Reservation{
  int id;
  BORNE_DE_RECHARGE* BorneDeRechargeReserver;
  PAIMENT paiment;
  DATE date_debut;
  DATE date_fin;
}RESERVATION;

typedef struct user{
   int cin;
   char nom[30];
   char prenom[30];
   int num_tlf;
   int nb_reserves;
   RESERVATION* reserves;
}USER;

typedef struct Resultat{
 char name[30];
 int nbr_reserve;
}RESULTAT;

BORNE_DE_RECHARGE* allocationBornes(int );///allocation du Tab Bornes
USER* allocationUser(int);///allocation du tab user
void AjouterBorne(BORNE_DE_RECHARGE*);///Ajouter une borne de recharge
void RemplirBorneDeCharge (BORNE_DE_RECHARGE *bornes, int nbBornes,FILE*,FILE*);///remplir le tableau de bornes
void afficherUneborne(BORNE_DE_RECHARGE);///afficher un seul Borne de recharge
void afficherTableauLesBornes(BORNE_DE_RECHARGE* ,int);///afficher tab des bornes de recharge
void   AjouterUneNouvelleBorne(BORNE_DE_RECHARGE**,int*);///Redemensionner Tab Borne 
int RechercherPourLeCode(BORNE_DE_RECHARGE*,int,int);///verifier l'existance d'un code dans le tab borne
void SupprimerUneBorneAvecCode(BORNE_DE_RECHARGE**,int*,int);///supprimer une borne avec son code et Redemensionner
void ModifierUneBorne(BORNE_DE_RECHARGE**,int);///Modifier une borne avec son code
void afficherLesBorneAvecStatut(BORNE_DE_RECHARGE*,int,int);///Affciher liste des bornes avec status donne
void AfficherLeBornPlusCher(BORNE_DE_RECHARGE *,int);///Afficher Le Born le Plus Chers
void AjouterUser (USER * ,BORNE_DE_RECHARGE *,int);///Ajouter User
void AfficherTabUser(USER*,int);///Afficher Tableau User
void init_paiment(PAIMENT* );///Remplir Paiment
void init_user(USER* ) ;///Remplir User
void entrer_date(DATE *);///Saisir Date
int RechercherPourLeCode(BORNE_DE_RECHARGE* , int , int );///Rechercher Born par code
void ReserverBorneDeRecharge(USER * ,BORNE_DE_RECHARGE *,int );///Reserver Une borne de recharge pour user
void RemplirTabUsers(USER**,int*,BORNE_DE_RECHARGE*,int,FILE*,FILE*);///Remplir Tableau users
void afficher_details_user(USER );///afficher details user
void afficher_date(DATE );///afficher date
void afficher_paiment(PAIMENT );///afficher paiment
void RemplirTableauResultat(RESULTAT*** , int* , USER* , int , int* );///Remplir Tableau Resultat par Nom et nbr reservation
void maxNbReservation(RESULTAT** , int );///Afficher le user le plus nbr reservation
int RechercherUserAvecCin(USER* user, int nb_user,int cin_donne);///Rechercher User Avec Cin
void ModifierUser(USER** ,int ,BORNE_DE_RECHARGE* ,int );///Modifier User 
void creerFichiersPrincipalIndex(FILE**, FILE**, char[], char[]);
void OpenFichiersPrincipalIndex(FILE**, FILE**, char[], char[]);
void afficherFichierIndex(FILE*fi);
int NbrDansFichierIndex(FILE* );
void copierFichierDansBornes(FILE*, BORNE_DE_RECHARGE*,int );
void copierFichierVersTabUser(FILE* , FILE* , USER* , int , BORNE_DE_RECHARGE* , int );
void afficherMenuPrincipalGlobal();
void afficherMenuPrincipal();
void afficherMenuBornes();
void afficherMenuUtilisateurs();
#endif
