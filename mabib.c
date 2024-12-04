#include "mabib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

USER* allocationUser(int nbUsers){
    USER* tab;
    tab=(USER*)malloc(nbUsers*sizeof(USER));
    if (!tab) exit(-1);
    return tab;
}

BORNE_DE_RECHARGE* allocationBornes(int nbBornes ){
    BORNE_DE_RECHARGE* tab;
    tab=(BORNE_DE_RECHARGE*)malloc(nbBornes*sizeof(BORNE_DE_RECHARGE));
    if (!tab)exit(-2);
    return tab;
}

RESERVATION* allocationReserve(int nb_reserve ){
    RESERVATION* tab;
    tab=(RESERVATION*)malloc(nb_reserve*sizeof(RESERVATION));
    if (!tab)exit(-2);
    return tab;
}

void AjouterBorne(BORNE_DE_RECHARGE *bornes) {
    printf("Entrez le code de la borne de recharge : ");
    scanf("%d", &bornes->Code);

    int type;
    do {
        printf("Entrez le type de la borne (0 = Rapide, 1 = Normal) : ");
        scanf("%d", &type);
    } while (type != 0 && type != 1);
    bornes->type = type;

    printf("Entrez la puissance de la borne de recharge (en kW) : ");
    scanf("%d", &bornes->puissance);

    int status;
    do {
        printf("Entrez le statut de la borne (0 = Disponible, 1 = Occupee, 2 = Hors service) : ");
        scanf("%d", &status);
    } while (status != 0 && status != 1 && status != 2);
    bornes->status = status;

    printf("Entrez la duree estimee d'utilisation (en minutes) : ");
    scanf("%d", &bornes->Duree);

    printf("Entrez le prix d'utilisation pour une minute : ");
    scanf("%lf", &bornes->prix);
}

void ecrireUnBorneDansFichier(BORNE_DE_RECHARGE borne,FILE*fp)
{
  //  fwrite(&borne,sizeof(BORNE_DE_RECHARGE),1,fp);
    fwrite(&borne.Code, sizeof(int), 1, fp);
    fwrite(&borne.type, sizeof(int), 1, fp);
    fwrite(&borne.puissance, sizeof(int), 1, fp);
    fwrite(&borne.status, sizeof(int), 1, fp);
    fwrite(&borne.Duree, sizeof(int), 1, fp);
    fwrite(&borne.prix, sizeof(double), 1, fp);
}

void RemplirBorneDeCharge (BORNE_DE_RECHARGE *bornes, int nbBornes,FILE* fp,FILE* fi){
    int position_file_principale;
    for(int i=0;i<nbBornes;i++){
        printf("\n BORNE DE RECHARGE   NUM° %d \n",i+1);
        AjouterBorne(bornes+i);
        position_file_principale=ftell(fp);
        fwrite(&position_file_principale, sizeof(int),1,fi);
        ecrireUnBorneDansFichier(*(bornes+i),fp);
    }
}

void afficherUneborne(BORNE_DE_RECHARGE borne){
     printf(" le code de la borne de recharge : %d\n",borne.Code);
     printf(" le Type de la borne de recharge : %s\n", borne.type == 0 ? "Rapide" : "Normal");
     printf(" le Puissance de la borne de recharge : %d\n", borne.puissance);
     printf(" la Statut de la borne de recharge : %s\n",  borne.status == 0 ? "Disponible" : borne.status == 1 ? "Occupe" : "Hors_Service");
     printf(" le Puissance de la Duree : %d\n", borne.Duree);
     printf(" le Prix de la Duree : %.2lf\n", borne.prix);
}

void afficherTableauLesBornes(BORNE_DE_RECHARGE* tab,int nb){
        printf("Afficher  Tableau de Borne");
        for(int i=0;i<nb;i++){
            printf("BORNE DE RECHARGE NUM : %d :",i+1);
            afficherUneborne(*(tab+i));
        }
}

void   AjouterUneNouvelleBorne(BORNE_DE_RECHARGE** bornes,int* nb_borne){
        int nb_borne_ajouter;
        printf("\n Entrer Combien Borne voulez-vous ajouter ? \n");
        scanf("%d",&nb_borne_ajouter);
        *bornes=(BORNE_DE_RECHARGE*)realloc(*bornes,(*nb_borne+nb_borne_ajouter) * sizeof(BORNE_DE_RECHARGE*));
        if (*bornes==NULL){
                printf("Erreur redimensionnement  tab borne");
                exit(-3);
        }else{
            int total=(*nb_borne+nb_borne_ajouter)-nb_borne_ajouter;///debut de l'indice
            for(int i=total;i<(*nb_borne+nb_borne_ajouter);i++){
                AjouterBorne((*bornes)+i);
            }
            *nb_borne=(*nb_borne)+nb_borne_ajouter;
        }
}

int RechercherPourLeCode(BORNE_DE_RECHARGE* borne, int nb, int code_donne) {
    for (int i = 0; i < nb; i++) {
        if ((*(borne+i)).Code == code_donne) {
            return i; 
        }
    }
    return -1; 
}

void SupprimerUneBorneAvecCode(BORNE_DE_RECHARGE** borne,int* nb_borne,int indice){
        for(int i=indice;i<*nb_borne-1;i++){
                *((*borne)+i)=*((*borne)+i+1);
        }
        *borne = (BORNE_DE_RECHARGE*) realloc(*borne, (*nb_borne - 1) * sizeof(BORNE_DE_RECHARGE));
        (*nb_borne)--;
}

void ModifierUneBorne(BORNE_DE_RECHARGE** borne,int nb_borne){
    afficherTableauLesBornes((*borne),nb_borne);
    int code_donne;
    printf("Donner le code du Borne de recharge  voulez-vous modifier :");
    scanf("%d",&code_donne);
    int indice=RechercherPourLeCode((*borne),nb_borne,code_donne);
    if(indice==-1){
        printf("Code Incorrect");
    }else{
        BORNE_DE_RECHARGE nouvelle_borne;
        AjouterBorne(&nouvelle_borne);
        *((*borne)+indice)=nouvelle_borne;
    }
}

void afficherLesBorneAvecStatut(BORNE_DE_RECHARGE* borne,int nb_borne,int status){
    for(int i=0;i<nb_borne;i++){
            if((*(borne+i)).status==status){
                afficherUneborne(*(borne+i));
            }
    }
}

void AfficherLeBornPlusCher(BORNE_DE_RECHARGE* bornes,int nb_borne){
    BORNE_DE_RECHARGE borne_cher;
    borne_cher.prix=(*(bornes+0)).prix;
    for(int i=1;i<nb_borne;i++){
        if((*(bornes+i)).prix>borne_cher.prix ){
            borne_cher=(*(bornes+i));
        }
    }
    afficherUneborne(borne_cher);
}

void entrer_date(DATE *date) {
    printf("Jour: ");
    scanf("%d", &date->jour);
    printf("Mois: ");
    scanf("%d", &date->mois);
    printf("Annee: ");
    scanf("%d", &date->annee);
    printf("Heure: ");
    scanf("%d", &date->heure);
    printf("Minute: ");
    scanf("%d", &date->minute);
}

void init_paiment(PAIMENT* paiment) {
    paiment->id = rand();
    printf("Details Paiment\n");
    printf("-----------------------------\n");
    printf("Saisir montant:\n");
    scanf("%lf", &paiment->montant);

    printf("TYPE (0=Sur Place, 1=En Ligne):\n");
    int type_paiment;
    scanf("%d", &type_paiment);
    paiment->Type = (METHODE) type_paiment;

    if (type_paiment == 0) {
        strcpy(paiment->Token, "");
    } else {
        sprintf(paiment->Token, "Pass%d", paiment->id);
    }
}

void ReserverBorneDeRecharge(USER * user,BORNE_DE_RECHARGE *borne,int nbr_borne){
    afficherLesBorneAvecStatut(borne,nbr_borne,0);
    DATE date_debut, date_fin;
    RESERVATION* reserve=allocationReserve(user->nb_reserves);
    int indice=-1;
    int code;
    for(int i=0;i<user->nb_reserves;i++){
            do{
                printf("Donner le code de Borne de recharge a reserver pour le user %s  %s ",(user+i)->nom, (user+i)->prenom);
               scanf("%d",&code);
               indice=RechercherPourLeCode(borne,nbr_borne,code);
            }while(indice==-1); 
                (*(reserve+i)).BorneDeRechargeReserver=(borne+indice);
                (*(reserve+i)).id=rand();
                printf("Entrer la date de debut de la reservation :\n");
                entrer_date(&date_debut);
                printf("Entrer la date de fin de la reservation :\n");
                entrer_date(&date_fin);
                (*(reserve+i)).date_debut=date_debut;
                (*(reserve+i)).date_fin=date_fin;  
                
                printf("\n Ajout un paiement pour cette reservation :\n");
               init_paiment(&(*(reserve+i)).paiment);
            
    }
    user->reserves=reserve;
}

void init_user(USER* user) {
    printf("Details USER\n");
    
     printf("Saisir le CIN du User ");
    scanf("%d", &user->cin);
    
    printf("-----------------------------\n");

    printf("Donner Le Nom:\n");
    scanf("%s", user->nom);

    printf("Donner Le Prenom:\n");
    scanf("%s", user->prenom);

    printf("Donner Le Numero Telephone:\n");
    scanf("%d", &user->num_tlf);

    printf("Donner Le Nombre Du Reservation:\n");
    scanf("%d", &user->nb_reserves);
}

void AjouterUser (USER * user,BORNE_DE_RECHARGE *borne,int nbr_borne){
    init_user(user);
    ReserverBorneDeRecharge(user,borne,nbr_borne);
}
 
void ecrireUnUserDansFichier(USER user, FILE* fp) {
    fwrite(&user.cin, sizeof(int), 1, fp);
    fwrite(&user.nom, sizeof(char[30]), 1, fp);
    fwrite(&user.prenom, sizeof(char[30]), 1, fp);
    fwrite(&user.num_tlf, sizeof(int), 1, fp);
    fwrite(&user.nb_reserves, sizeof(int), 1, fp);
    for (int i = 0; i < user.nb_reserves; i++) {
        RESERVATION *reservation = user.reserves + i;

        fwrite(&reservation->id, sizeof(int), 1, fp);
        fwrite(&reservation->BorneDeRechargeReserver->Code, sizeof(int), 1, fp); 
        fwrite(&reservation->paiment.id, sizeof(int), 1, fp);
        fwrite(&reservation->paiment.montant, sizeof(double), 1, fp);
        fwrite(&reservation->paiment.Type, sizeof(int), 1, fp);
        fwrite(&reservation->paiment.Token, sizeof(char[30]), 1, fp);
        fwrite(&reservation->date_debut, sizeof(int) * 5, 1, fp);
        fwrite(&reservation->date_fin, sizeof(int) * 5, 1, fp);
    }
}

void RemplirTabUsers(USER** users,int* nbuser,BORNE_DE_RECHARGE* bornes,int nbr_borne,FILE* fp,FILE*  fi){
             printf("donner nombre User");
             scanf("%d",nbuser);
             int position_file_principale;
            *users=allocationUser(*nbuser);
             for(int i=0;i<*nbuser;i++){
                printf("\n User  : %d \n",i+1);
                AjouterUser((*users)+i, bornes, nbr_borne);
                position_file_principale=ftell(fp);
                fwrite(&position_file_principale, sizeof(int),1,fi);
                ecrireUnUserDansFichier(*((*users) + i), fp);     
            }
}

int NbrDansFichierIndex(FILE* fp){
    int taille=ftell(fp);
    printf("taille : %d",taille);
	int te=sizeof(int);
	return  taille/te;
}

void copierFichierVersTabUser(FILE* fp, FILE* fi, USER* user, int nbuser, BORNE_DE_RECHARGE* bornes, int nbr_borne) {
    for (int i = 0; i < nbuser; i++) {
        int position_file_principale;
        fread(&position_file_principale, sizeof(int), 1, fi);
        fseek(fp, position_file_principale, 0);

        fread(&user->cin, sizeof(int), 1, fp);
        fread(&user->nom, sizeof(char[30]), 1, fp);
        fread(&user->prenom, sizeof(char[30]), 1, fp);
        fread(&user->num_tlf, sizeof(int), 1, fp);
        fread(&user->nb_reserves, sizeof(int), 1, fp);

        user->reserves = allocationReserve(user->nb_reserves);

        for (int j = 0; j < user->nb_reserves; j++) {
            RESERVATION* reservation = user->reserves + j;
            fread(&reservation->id, sizeof(int), 1, fp);
            int borneCode;
            fread(&borneCode, sizeof(int), 1, fp);
            int indice=RechercherPourLeCode(bornes,nbr_borne,borneCode);
            reservation->BorneDeRechargeReserver = (bornes + indice);   
            fread(&reservation->paiment.id, sizeof(int), 1, fp);
            fread(&reservation->paiment.montant, sizeof(double), 1, fp);
            fread(&reservation->paiment.Type, sizeof(int), 1, fp);
            fread(&reservation->paiment.Token, sizeof(char[30]), 1, fp);
            fread(&reservation->date_debut, sizeof(int) * 5, 1, fp);
            fread(&reservation->date_fin, sizeof(int) * 5, 1, fp);
        }
    }
}


int RechercherUserAvecCin(USER* user, int nb_user,int cin_donne) {
    for (int i = 0; i < nb_user; i++) {
        if ((*(user+i)).cin == cin_donne) {
            return i; 
        }
    }
    return -1; 
}

void ModifierUser(USER** users,int nbUser,BORNE_DE_RECHARGE* bornes,int nbr_borne){
    AfficherTabUser((*users),nbUser);
    int cin_donne;
    printf("Donner le Cin User voulez-vous modifier :");
    scanf("%d",&cin_donne);
    int indice=RechercherUserAvecCin((*users),nbUser,cin_donne);
    if(indice==-1){
        printf("Code Incorrect");
    }else{
        USER nouvelle_user;
        AjouterUser(&nouvelle_user,bornes,nbr_borne);
        *((*users)+indice)=nouvelle_user;
    }
}

void afficher_date(DATE date) {
    printf("%d/%d/%d %d:%d\n", date.jour, date.mois, date.annee, date.heure, date.minute);
}

void afficher_details_user(USER user) {
    printf("Details USER  ID :  %d\n", user.cin);
    printf("-----------------------------\n");
    printf("Nom : %s \n", user.nom);
    printf("Le Prenom : %s \n", user.prenom);
    printf("Le Numero Telephone: %d \n", user.num_tlf);
    printf("Le Nombre Du Reservation : %d \n", user.nb_reserves);
}

void afficher_paiment(PAIMENT paiment){
        printf("Details du Paiment:\n");
        printf("-----------------------------\n");
        printf("ID : %d\n", paiment.id);
        printf("Montant : %.2lf\n", paiment.montant);
        printf("Type : %s\n", paiment.Type == 0 ? "Sur Place" : "En Ligne");
        if (paiment.Type == 1) {
            printf("Token : %s\n", paiment.Token);
        }
}

void afficherUser(USER user){
    afficher_details_user(user);
    for(int i=0;i<user.nb_reserves;i++){
        afficher_date((user.reserves+i)->date_debut);
        afficher_date((user.reserves+i)->date_fin);
        afficherUneborne(*(user.reserves+i)->BorneDeRechargeReserver);
        afficher_paiment((user.reserves+i)->paiment);
    }
}

void AfficherTabUser(USER* users,int nbUser){
    if(!users){
            printf("Tableau User Vide");
    }else{
        for(  int i=0;i<nbUser;i++){
            printf("\n CLIENT %d",i+1);
            afficherUser(*(users+i));
        }
    }
}

void maxNbReservation(RESULTAT** res, int nbUser) {
    int indexMax = 0;
    int nbMax = (*(res + 0))->nbr_reserve;
    printf("\n----------------------\n");
    for (int i = 1; i < nbUser; i++) {
        if ((*(res + i))->nbr_reserve > nbMax) {
            nbMax = (*(res + i))->nbr_reserve;
            indexMax = i;
        }
    }
    printf("Nom : %s et Nombre de location : %d \n", (*(res + indexMax))->name, (*(res + indexMax))->nbr_reserve);
}

void RemplirTableauResultat(RESULTAT*** res, int* nbResultats, USER* user, int nbUser, int* MaxRes) {
    for (int j = 0; j < nbUser; j++) {
        RESULTAT* nouveauResultat = (RESULTAT*)malloc(sizeof(RESULTAT));
        if (nouveauResultat == NULL) {
            printf("Erreur allocation nouveau resultat \n");
            exit(-2);
        }

        strcpy(nouveauResultat->name, (user + j)->nom);
        nouveauResultat->nbr_reserve = (user + j)->nb_reserves;

        if (*nbResultats >= *MaxRes) {
            *MaxRes *= 2;
            *res = (RESULTAT**)realloc(*res, (*MaxRes) * sizeof(RESULTAT*));
            if (*res == NULL) {
                printf("Erreur redimensionnement tableau resultats \n");
                exit(-3);
            }
        }

        *(*res + *nbResultats) = nouveauResultat;
        (*nbResultats)++;
    }

    maxNbReservation(*res, nbUser);
}

void creerFichiersPrincipalIndex(FILE**fe, FILE**fi,char namePrincipale[],char nameIndex[])
{
	*fe= fopen(namePrincipale,"wb+");
	if(!*fe) exit(-1);
	*fi= fopen(nameIndex,"wb+");
	if(!*fi) exit(-1);
}

void OpenFichiersPrincipalIndex(FILE**fe, FILE**fi,char namePrincipale[],char nameIndex[])
{
	*fe= fopen(namePrincipale,"r+");
	if(!*fe) exit(-1);
	*fi= fopen(nameIndex,"r+");
	if(!*fi) exit(-1);
}

void afficherFichierIndex(FILE*fi)
{
	int x;
    rewind(fi);
	printf("\n affichage fichier index \n");
	while(1)
	{
		fread(&x, sizeof(int), 1, fi);
		if(feof(fi)) break;
		printf("\n %d", x);
	}
}

BORNE_DE_RECHARGE lireUnborneDuFichier(FILE*fp)
{
	BORNE_DE_RECHARGE borne;
    fread(&borne,sizeof(BORNE_DE_RECHARGE),1,fp);
    /*fread(&borne.Code, sizeof(int), 1, fp);
    fread(&borne.type, sizeof(int), 1, fp);
    fread(&borne.puissance, sizeof(int), 1, fp);
    fread(&borne.status, sizeof(int), 1, fp);
    fread(&borne.Duree, sizeof(int), 1, fp);
    fread(&borne.prix, sizeof(double), 1, fp);*/
	return borne;
}

void copierFichierDansBornes(FILE*fb, BORNE_DE_RECHARGE*bornes,int nb_born)
{
	rewind(fb);
	for(int i=0; i<nb_born; i++)
		*(bornes+i)=lireUnborneDuFichier(fb);
}

void afficherMenuPrincipalGlobal() {
    printf("\n");
    printf("***********************************************\n");
    printf("*               MENU PRINCIPAL GLOBAL          *\n");
    printf("***********************************************\n");
    printf("*  1 - Charger les donnees depuis les fichiers *\n");
    printf("*  2 - Initialiser de nouvelles bornes         *\n");
    printf("*  3 - Quitter                                 *\n");
    printf("***********************************************\n");
    printf("Entrez votre choix (1-3) : ");
}

void afficherMenuPrincipal() {
    printf("\n");
    printf("***********************************************\n");
    printf("*                 MENU PRINCIPAL              *\n");
    printf("***********************************************\n");
    printf("*  1 - Gestion des bornes de recharge         *\n");
    printf("*  2 - Gestion des utilisateurs               *\n");
    printf("*  3 - Quitter                                *\n");
    printf("***********************************************\n");
    printf("Entrez votre choix (1-3) : ");
}

void afficherMenuBornes() {
    printf("\n");
    printf("***********************************************\n");
    printf("*           MENU BORNES DE RECHARGE          *\n");
    printf("***********************************************\n");
    printf("*  1 - Afficher les bornes de recharge        *\n");
    printf("*  2 - Ajouter une borne de recharge          *\n");
    printf("*  3 - Supprimer une borne de recharge        *\n");
    printf("*  4 - Mettre a jour une borne de recharge    *\n");
    printf("*  5 - Afficher les bornes par statut donne   *\n");
    printf("*  6 - Afficher la borne la plus chere        *\n");
    printf("*  7 - Revenir au menu principal              *\n");
    printf("***********************************************\n");
    printf("Entrez votre choix (1-7) : ");
}

void afficherMenuUtilisateurs() {
    printf("\n");
    printf("***********************************************\n");
    printf("*             MENU UTILISATEURS              *\n");
    printf("***********************************************\n");
    printf("*  1 - Ajouter utilisateur                    *\n");
    printf("*  2 - Afficher les utilisateurs              *\n");
    printf("*  3 - Afficher l'utilisateur avec le plus    *\n");
    printf("*      de reservations                        *\n");
    printf("*  4 - Modifier un utilisateur                *\n");
    printf("*  5 - Revenir au menu principal              *\n");
    printf("***********************************************\n");
    printf("Entrez votre choix (1-5) : ");
}