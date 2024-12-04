#include <stdio.h>
#include <stdlib.h>
#include "mabib.h"

int main()
{
    int nbBornes, nbUser;
    BORNE_DE_RECHARGE* bornes;
    USER* users;
    RESULTAT** resultats;
    int nbResultats = 0;
    int MaxResultat = 3;
    resultats = (RESULTAT **) malloc(MaxResultat * sizeof(RESULTAT*));
    printf("\n Bienvenue Dans Une Station De Recharge Electrique \n\n");
    int code_borne;
    int status_donne;
    ///Fichiers
    FILE *fp_user, *fi_user, *fp_borne, *fi_borne;
    int choix_global, choix, choix_user_menu, choix_borne_menu;
    do {
       afficherMenuPrincipalGlobal();
        scanf("%d", &choix_global);

        switch (choix_global) {
            case 1:
                OpenFichiersPrincipalIndex(&fp_borne, &fi_borne, "BornePrincipal", "BorneIndex");
                //OpenFichiersPrincipalIndex(&fp_user, &fi_user, "UserPrincipal", "UserIndex");
                nbBornes = NbrDansFichierIndex(fi_borne);
                afficherFichierIndex(fi_borne);
                printf("nbBornes : %d",nbBornes);
               // nbUser=NbrDansFichierIndex(fi_user);
                if (nbBornes <= 0) {
                    //creerFichiersPrincipalIndex(&fp_borne, &fi_borne, "BornePrincipal", "BorneIndex");
                   // creerFichiersPrincipalIndex(&fp_user, &fi_user, "UserPrincipal", "UserIndex");
                    printf("\n************* Ajout des Bornes de Recharge *************\n");
                    printf(" Entrez le nombre des Bornes de recharge que vous souhaitez ajouter :  ");
                    scanf("%d", &nbBornes);
                    RemplirBorneDeCharge(bornes, nbBornes, fp_borne, fi_borne);
                } else {
                    bornes = allocationBornes(nbBornes);
                    copierFichierDansBornes(fp_borne, bornes, nbBornes);
                    //users=allocationUser(nbUser);
                   // copierFichierVersTabUser( fp_user,  fi_user,  users, nbUser, bornes,  nbBornes);
                }
                break;
            case 2:
                creerFichiersPrincipalIndex(&fp_borne, &fi_borne, "BornePrincipal", "BorneIndex");
                //creerFichiersPrincipalIndex(&fp_user, &fi_user, "UserPrincipal", "UserIndex");
                printf("Entrez le nombre de bornes a initialiser : ");
                scanf("%d", &nbBornes);
                bornes = allocationBornes(nbBornes);
                RemplirBorneDeCharge(bornes, nbBornes, fp_borne, fi_borne);
                printf("Bornes initialisees avec succes !\n");
                break;
            case 3:
                printf("Au revoir.\n");
                break;
            default:
                printf("Choix non valide. Veuillez reessayer.\n");
                break;
        }
    } while (choix_global != 1 && choix_global != 2 && choix_global != 3);

    do {
        afficherMenuPrincipal();
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                do {
                    afficherMenuBornes();
                    scanf("%d", &choix_borne_menu);

                    switch (choix_borne_menu) {
                        case 1: afficherTableauLesBornes(bornes, nbBornes); break;
                        case 2: AjouterUneNouvelleBorne(&bornes, &nbBornes); break;
                        case 3:
                            afficherTableauLesBornes(bornes, nbBornes);
                            printf("Entrez le code de la borne a supprimer : ");
                            scanf("%d", &code_borne);
                            SupprimerUneBorneAvecCode(&bornes, &nbBornes, RechercherPourLeCode(bornes, nbBornes, code_borne));
                            break;
                        case 4: ModifierUneBorne(&bornes, nbBornes); break;
                        case 5:
                            printf("Entrez le statut des bornes (0 = Disponible, 1 = Occupee, 2 = Hors service) : ");
                            scanf("%d", &status_donne);
                            afficherLesBorneAvecStatut(bornes, nbBornes, status_donne);
                            break;
                        case 6: AfficherLeBornPlusCher(bornes, nbBornes); break;
                        case 7: break;
                        default: printf("Choix non valide.\n"); break;
                    }
                } while (choix_borne_menu != 7);
                break;
                
            case 2:
                do {
                    afficherMenuUtilisateurs();
                    scanf("%d", &choix_user_menu);

                    switch (choix_user_menu) {
                        case 1: //RemplirTabUsers(&users, &nbUser, bornes, nbBornes,fp_user,fi_user);
                             break;
                        case 2: 
                            AfficherTabUser(users, nbUser); break;
                        case 3:
                            RemplirTableauResultat(&resultats, &nbResultats, users, nbUser, &MaxResultat);
                            break;
                        case 4: ModifierUser(&users, nbUser, bornes, nbBornes); break;
                        case 5: break;
                        default: printf("Choix non valide.\n"); break;
                    }
                } while (choix_user_menu != 5);
                break;

            case 3:
                printf("Au revoir.\n");
                break;

            default:
                printf("Choix non valide. Veuillez reessayer.\n");
                break;
        }
    } while (choix != 3);

    free(bornes);
    free(users);
    free(resultats);
    fclose(fp_borne);
    fclose(fi_borne);

    return 0;
}
