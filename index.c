#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// globale variables
int i, j, nbrTaches, choice;
int countID = 1;

// les structures


typedef struct Date {
    int jour;
    int mois;
    int an;
} Date;

typedef struct tache {
    int id;
    char titre[20];
    char description[100];
    int deadline;
    char statut[20];
    Date dateN;
    int idCollab[100];
} tache;
// menue function
void menue (){
        printf("\n#################################################\n");
        printf("\nMenu:\n");
        printf("1. Ajouter une nouvelle tache\n");
        printf("2. Afficher la liste de toutes les taches\n");
        printf("3. Trier les taches par ordre alphabetique\n");
        printf("4. Trier les taches par deadline\n");
        printf("5. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
        printf("6. Modifier une tache\n");
        printf("7. Supprimer une tache par identifiant\n");
        printf("8. Rechercher les Taches\n");
        printf("9. Afficher les statistiques\n");
        printf("0. Quitter\n");
        printf("\n#################################################\n");
}

// function for display list of tasks
void displayTasks(tache task[]) {
    printf("--------------------------------------------------------------\nId\tTitre\tDesc\t\tdeadline\tStatus\n--------------------------------------------------------------");
    for(i = 0; i < nbrTaches; i++){
    printf("\n%d\t%s\t%s\t\t%d\t%s\n--------------------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline,task[i].statut);

        }
}
// sort alpha
void sortAlpha (tache task[]){
    tache temp;
    int i,j,compar;
    for (i = 0; i < nbrTaches ; i++) {
        for (j = 0; j < nbrTaches - 1; j++) {
            int compar = strcmp(task[j].titre,task[j+1].titre) ;
            if(compar > 0){
                temp = task[j];
                task[j] = task[j+1];
                task[j+1] = temp;
            }
        }
    }
}

// sort deadline


void sortDeadline(tache task[]) {
    tache temp;
    for (i = 0; i < nbrTaches - 1; i++) {
        for (j = 0; j < nbrTaches - i - 1; j++) {
            if (task[j].deadline > task[j+1].deadline) {
                temp = task[j];
                task[j] = task[j + 1];
                task[j + 1] = temp;
            }
        }
    }
}
// modifier description
void modifierDesc(tache task[],int id, char desc[]){
    int found = 0;
    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
            strcpy(task[i].description, desc);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Aucun tache trouvé pour modifier.\n");
    }

}
// update tache
void modifierStatus(tache task[],int id, char statu[]){
    int found = 0;
    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
            strcpy(task[i].statut, statu);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun tache trouvé pour modifier.\n");
    }

}
// update tache
void modifierDeadline(tache task[],int id, int deadline){
    int found = 0;
    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
            task[i].deadline = deadline ;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun tache trouvé pour modifier.\n");
    }

}
// delete tache
void supprimerTask(tache task[],int id){
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
            for (int j = i; j < nbrTaches - 1; j++) {
                task[j] = task[j + 1];
            }
            nbrTaches--;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun apprenant trouvé pour supprimer.\n");
    }

}
// Search by id
void searchById(tache task[],int id){
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
        printf("--------------------------------------------------------------\nId\tTitre\tDesc\t\tdeadline\tStatus\n-----------------------------------------");
        printf("\n%d\t%s\t%s\t\t%d\t%s\n--------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline,task[i].statut);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun apprenant trouvé pour supprimer.\n");
    }

}
// Search by titre
void searchByTitre(tache task[],char titre[]){
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if (strcmp(titre, task[i].titre) == 0) {
        printf("--------------------------------------------------------------\nId\tTitre\tDesc\t\tdeadline\tStatus\n-----------------------------------------");
        printf("\n%d\t%s\t%s\t\t%d\t%s\n--------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline,task[i].statut);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun apprenant trouvé pour supprimer.\n");
    }

}
// display nombre total des taches
void nbrTotal(tache task[]){
    int counter = 0 ;
    for (i = 0; i < nbrTaches; i++) {
      counter ++;
    }

    printf("Nombre total des taches est %d \n", counter);

}
// display nombre total des taches complètes et incomplètes
void nbrTotalCompleteIncomplete(tache task[]){
    int counterDone = 0 ;
    int counterTodo = 0 ;
    char statusDone[] = "done";
    char statusToDo[] = "todo";
    char statusDoing[] = "doing";
    for (i = 0; i < nbrTaches; i++) {
        if(strcmp(statusDone, task[i].statut) == 0) {
            counterDone ++;
        }
        if(strcmp(statusToDo, task[i].statut) == 0 || strcmp(statusDoing, task[i].statut) == 0) {
            counterTodo ++;
        }


    }

    printf("Nombre total des taches completes est %d \n", counterDone);
    printf("Nombre total des taches incompletes est %d \n", counterTodo);

}

//Ajouter une nouvelle tâche
void addTask(tache task[]){
    printf("saisir le nomber des taches a ajouter : ");
    scanf("%d",&nbrTaches);
    for(i = 0; i < nbrTaches; i++){
        task[i].id = countID;
        countID +=countID;
        printf("saisir l intituler de tache (%d) : ", i+1);
        getchar();
        gets(task[i].titre);
        printf("saisir la description de tache (%d) : ", i+1);
        getchar();
        gets(task[i].description);
        printf("Saisir le deadline de la tache (%d) : ", i+1);
        scanf("%d", &task[i].deadline);
        printf("saisir l statut de tache (%d) : ", i+1);
        getchar();
        gets(task[i].statut);
        printf("\n------------------------------------------\n");
    }
}

int main() {
    int choixMod,choixSearch,id,deadline;
    char desc[100],status[30],titre[30];
    tache task[nbrTaches];
    do {
        menue ();

        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(task);
                break;
            case 2:
                displayTasks(task);
                break;
            case 3:
                sortAlpha(task);
                break;
            case 4:
                sortDeadline(task);
                break;
            case 5:

                break;
            case 6:
                printf("1 => Modifier la description .\n2 => Modifier le statut\n3 => Modifier le deadline.\n");
                scanf("%d",&choixMod);
                switch (choixMod) {
                    case 1:
                        printf("entre ID du tache que vous voullez modifier : \n");
                        scanf("%d",&id);
                        printf("entre la nouvelle description : \n");
                        scanf("%s",&desc);
                        modifierDesc(task, id, desc);

                        break;
                    case 2:
                        printf("entre ID du tache que vous voullez modifier : \n");
                        scanf("%d",&id);
                        printf("entre le nouvelle statut  : \n");
                        scanf("%s",&status);
                        modifierStatus(task, id, status);
                        break;
                    case 3:
                        printf("entre ID du tache que vous voullez modifier : \n");
                        scanf("%d",&id);
                        printf("entre le nouvelle deadline  : \n");
                        scanf("%d",&deadline);
                        modifierDeadline(task, id, deadline);
                        break;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                }
                break;
            case 7: {
                    printf("entre ID du tache que vous voullez supprimer : \n");
                    scanf("%d",&id);
                    supprimerTask(task, id);
                break;
            }
            case 8: {
                printf("1 => Rechercher par ID.\n2 => Rechercher par Titre.\n");
                scanf("%d",&choixSearch);

                switch (choixSearch) {
                    case 1:
                        printf("entre ID du tache que vous voullez trouver : \n");
                        scanf("%d",&id);
                        searchById(task, id);

                        break;
                    case 2:
                        printf("entre le titre du tache que vous voullez trouver : \n");
                        scanf("%d",titre);
                        searchByTitre(task, titre);
                        break;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                }
                break;
            }
            case 9: {
                printf("1 => Afficher le nombre total des taches.\n2 => Afficher le nombre de taches completes et incompletes.\n => Afficher le nombre de jours restants jusqu au delai de chaque tache.");
                scanf("%d",&choixSearch);
                switch (choixSearch) {
                    case 1:
                        nbrTotal(task);
                        break;
                    case 2:
                        nbrTotalCompleteIncomplete(task);
                        break;
                    case 3:
                        //nbrTotalCompleteIncomplete(task);
                        break;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                }
            }
                break;

            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

} while (choice != 0);

    return 0;
}
