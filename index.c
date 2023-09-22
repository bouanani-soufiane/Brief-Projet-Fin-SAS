#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// globale variables
int i, j, nbrTaches, choice;
int countID = 1, size,start;

// local time

struct tm today; // Global variable to store today's date
void initTodayDate() {
    time_t t;
    time(&t); // Get current time
    today = *localtime(&t); // Convert to struct tm
}

// les structures
typedef struct Date {
    int jour;
    int mois;
    int an;
} Date;

typedef struct tache {
    int id;
    char titre[30];
    char description[100];
    Date deadline;
    char statut[30];
    int idCollab[100];
} tache;
// menue function
void menue (){
        printf("\n\t\t\t\t#################################################\n");
        printf("\t\t\t\t1. Ajouter une nouvelle tache\n");
        printf("\t\t\t\t2. Afficher la liste de toutes les taches\n");
        printf("\t\t\t\t3. Trier les taches par ordre alphabetique\n");
        printf("\t\t\t\t4. Trier les taches par deadline\n");
        printf("\t\t\t\t5. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
        printf("\t\t\t\t6. Modifier une tache\n");
        printf("\t\t\t\t7. Supprimer une tache par identifiant\n");
        printf("\t\t\t\t8. Rechercher les Taches\n");
        printf("\t\t\t\t9. Afficher les statistiques\n");
        printf("\t\t\t\t0. Quitter\n");
        printf("\n\t\t\t\t#################################################\n");
}
// function for display list of tasks
void displayTasks(tache *task, int nbrTaches) {
    if (nbrTaches < 1 ){
        printf("there is no tasks to display");
    }else{
        printf("\n\t\t\t\t#########################\n");
        printf("\n\t\t\t\t\tTO DO LIST\n");
        printf("\n\t\t\t\t#########################\n");

        printf("\n\t\t--------------------------------------------------------------\n\t\tId\tTitre\tDesc\t\tdeadline\tStatus\n\t\t--------------------------------------------------------------");
        for(i = 0; i < nbrTaches; i++){
            printf("\n\n\t\t%d\t%s\t%s\t\\%d\\%d\\%d\t%s\n\t\t--------------------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline.an, task[i].deadline.mois, task[i].deadline.jour,task[i].statut);
        }
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
    printf("\nLes taches sont triees dans l ordre alphabetique\n");
}
// sort deadline
void sortDeadline(tache task[] ) {
    tache temp;
    for (i = 0; i < nbrTaches - 1; i++) {
        for (j = 0; j < nbrTaches - i - 1; j++) {
            if (task[j].deadline.an > task[j + 1].deadline.an) {
                temp = task[j];
                task[j] = task[j + 1];
                task[j + 1] = temp;
            } else if (task[j].deadline.an == task[j + 1].deadline.an &&
                       task[j].deadline.mois > task[j + 1].deadline.mois) {
                temp = task[j];
                task[j] = task[j + 1];
                task[j + 1] = temp;
            } else if (task[j].deadline.an == task[j + 1].deadline.an &&
                       task[j].deadline.mois == task[j + 1].deadline.mois &&
                       task[j].deadline.jour > task[j + 1].deadline.jour) {
                temp = task[j];
                task[j] = task[j + 1];
                task[j + 1] = temp;
            }
        }
    }
    printf("\nLes taches sont triees avec succes par ordre de deadline\n");

}
//Afficher les tâches dont le deadline est dans 3 jours ou moins.
void deadline3Jours(tache task[], int nbrTaches) {

    if(nbrTaches < 1){
        printf("Aucune tache  avec un delai de 3 jours ou moins . ");
    }else{
        printf("\n\t\t\t\t###########################################\n");
        printf("\n\t\t\t\tTaches avec Echeance dans 3 Jours ou Moins\n");
        printf("\n\t\t\t\t###########################################\n");
        printf("\n\t\t--------------------------------------------------------------\n\t\tId\tTitre\tDesc\t\tdeadline\tStatus\n\t\t--------------------------------------------------------------");

    struct tm deadlineDate;

    for (i = 0; i < nbrTaches; i++) {
        // Convert the task's deadline to a struct tm
        deadlineDate.tm_year = task[i].deadline.an - 1900; // Adjust year
        deadlineDate.tm_mon = task[i].deadline.mois - 1;   // Adjust month
        deadlineDate.tm_mday = task[i].deadline.jour;
        deadlineDate.tm_hour = 0;
        deadlineDate.tm_min = 0;
        deadlineDate.tm_sec = 0;

        // Calculate the time difference in seconds
        time_t currentTime = mktime(&today);
        time_t taskDeadline = mktime(&deadlineDate);
        double diffInSeconds = difftime(taskDeadline, currentTime);

        // Check if the deadline is within 3 days (259200 seconds)
        if (diffInSeconds >= 0 && diffInSeconds <= 259200) {
            printf("\n\n\t\t%d\t%s\t%s\t%d/%d/%d\t%s\n\n\t\t--------------------------------------------------------------", task[i].id, task[i].titre, task[i].description, task[i].deadline.an, task[i].deadline.mois, task[i].deadline.jour, task[i].statut);
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
    printf("La tache a ete modifier avec succes !\n");

    if (!found) {
        printf("Aucun tache trouve pour modifier.\n");
    }

}
// modifier status
void modifierStatus(tache task[], int id, int status) {
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if (task[i].id == id) {
            switch (status) {
                case 1:
                    strcpy(task[i].statut, "todo");
                    break;
                case 2:
                    strcpy(task[i].statut, "doing");
                    break;
                case 3:
                    strcpy(task[i].statut, "done");
                    break;
                default:
                    printf("Choix invalide\n");
                    break;
            }

            found = 1;

            if (status == 1) {
                printf("modified to To Do !");
            } else if (status == 2) {
                printf("modified to Doing");
            } else if (status == 3) {
                printf("modified to Done !");
            }
        }
    }
    printf("La tache a ete modifier avec succes !\n");

    if (!found) {
        printf("Aucune tache trouvee pour modifier.\n");
    }
}


void modifierDeadline(tache task[], int id, Date newDeadline) {
    int found = 0;

    for (int i = 0; i < nbrTaches; i++) {
        if (task[i].id == id) {
            task[i].deadline = newDeadline;
            found = 1;
            break;
        }
    }
    printf("La tache a ete modifier avec succes !\n");

    if (!found) {
        printf("Aucun tache trouve pour modifier la deadline.\n");
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
    printf("La tache a ete supprimee avec succes  \n");

    if (!found) {
        printf("Aucun tache trouve pour supprimer.\n");
    }

}
// Search by id
void searchById(tache task[],int id){
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if ( task[i].id == id) {
        printf("\n\t\t--------------------------------------------------------------\n\t\tId\tTitre\tDesc\t\tdeadline\tStatus\n\t\t--------------------------------------------------------------");
        printf("\n\t\t%d\t%s\t%s\t\\%d\\%d\\%d\t%s\n\t\t--------------------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline.an, task[i].deadline.mois, task[i].deadline.jour,task[i].statut);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun tache trouve.\n");
    }

}
// Search by titre
void searchByTitre(tache task[],char titre[]){
    int found = 0;

    for (i = 0; i < nbrTaches; i++) {
        if (strcmp(titre, task[i].titre) == 0) {
        printf("\n\t\t--------------------------------------------------------------\n\t\tId\tTitre\tDesc\t\tdeadline\tStatus\n\t\t--------------------------------------------------------------");
        printf("\n\t\t%d\t%s\t%s\t\\%d\\%d\\%d\t%s\n\t\t--------------------------------------------------------------",task[i].id,task[i].titre,task[i].description, task[i].deadline.an, task[i].deadline.mois, task[i].deadline.jour,task[i].statut);
        found = 1;
            break;
        }
    }

    if (!found) {
        printf("Aucun tache trouve \n");
    }

}
// display nombre total des taches
void nbrTotal(tache task[]){
    int counter = 0 ;
    for (i = 0; i < nbrTaches; i++) {
      counter ++;
    }

    printf("\t\tNombre total des taches est %d \n", counter);

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

    printf("\t\tNombre total des taches completes est %d \n", counterDone);
    printf("\t\tNombre total des taches incompletes est %d \n", counterTodo);

}

int daysRemaining(Date deadline) {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    // Get the current date
    int currentYear = tm_info->tm_year + 1900;
    int currentMonth = tm_info->tm_mon + 1;
    int currentDay = tm_info->tm_mday;

    // Calculate the difference between the deadline and current date
    int remainingDays = (deadline.an - currentYear) * 365 +
                        (deadline.mois - currentMonth) * 30 +
                        (deadline.jour - currentDay);

    return remainingDays;
}
// Function to display the number of days remaining for each task
void displayDaysRemaining(tache *task, int nbrTaches) {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    // Get the current date
    int currentYear = tm_info->tm_year + 1900;
    int currentMonth = tm_info->tm_mon + 1;
    int currentDay = tm_info->tm_mday;

    if (nbrTaches < 1) {
        printf("\n\t\t##Il n'y a aucune tache a afficher . \n");
    } else {
        printf("\n\t\t--------------------------------------------------------------\n\t\tId\tTitre\tDate d'aujourd'hui\tDeadline\tJours restants\n\t\t--------------------------------------------------------------");
        for (int i = 0; i < nbrTaches; i++) {
            Date todayDate;
            todayDate.an = currentYear;
            todayDate.mois = currentMonth;
            todayDate.jour = currentDay;

            int daysLeft = daysRemaining(task[i].deadline);

            printf("\n\t\t%d\t%s\t%d/%d/%d\t%d/%d/%d\t", task[i].id, task[i].titre,
                   todayDate.jour, todayDate.mois, todayDate.an, // Today's Date
                   task[i].deadline.jour, task[i].deadline.mois, task[i].deadline.an); // Deadline

            if (daysLeft < 0) {
                printf("%d jours (Tache depassee)\n\t\t--------------------------------------------------------------", daysLeft);
            } else {
                printf("%d jours \n\t\t--------------------------------------------------------------", daysLeft);
            }
        }
    }
}



//Ajouter une nouvelle tâche

void addOneTask(tache **task, int *nbrTaches) {
    int status;

    // Reallocate memory for one additional task
    *task = (tache *)realloc(*task, (*nbrTaches + 1) * sizeof(tache));

    int i = *nbrTaches; // Index for the new task
    (*task)[i].id = countID;
    countID++;

    printf("Saisir l'intitule de la tache : ");
    getchar();
    gets((*task)[i].titre);

    printf("Saisir la description de la tache : ");
    gets((*task)[i].description);

    do
    {
        printf("Saisir le deadline de la tache (sous forme yyyy/mm/dd) : ");
        scanf(" %d/%d/%d", &((*task)[i].deadline.an), &((*task)[i].deadline.mois), &((*task)[i].deadline.jour));
        if ((*task)[i].deadline.an < 1990 ||
        (*task)[i].deadline.mois < 1 || (*task)[i].deadline.mois > 12 ||
        (*task)[i].deadline.jour < 1 || (*task)[i].deadline.jour > 31) {
            printf("Erreur de saisie. Veuillez entrer une date valide (yyyy/mm/dd).\n");
        }


    } while ((*task)[i].deadline.an < 1990 ||
         (*task)[i].deadline.mois < 1 || (*task)[i].deadline.mois > 12 ||
         (*task)[i].deadline.jour < 1 || (*task)[i].deadline.jour > 31);


    printf("Saisir le statut de la tache : \n[1] : To Do\n[2] : Doing\n[3] : Done\n");
    scanf("%d", &status);

    switch (status) {
        case 1:
            strcpy((*task)[i].statut, "todo");
            break;
        case 2:
            strcpy((*task)[i].statut, "doing");
            break;
        case 3:
            strcpy((*task)[i].statut, "done");
            break;
        default:
            printf("Choix invalide\n");
            break;
    }

    if (status == 1) {
        printf("added as To Do !");
    } else if (status == 2) {
        printf("added as Doing");
    } else if (status == 3) {
        printf("added as Done !");
    }

    printf("\n------------------------------------------\n");

    (*nbrTaches)++; // Update the total number of tasks
    start = countID;
}

//Ajouter multi tâche
void addTask(tache **task, int *nbrTaches) {
    int status;
    int numTasksToAdd; // Declare a variable to store the number of tasks to add
    printf("Saisir le nombre de taches a ajouter : ");
    scanf("%d", &numTasksToAdd); // Read the number of tasks to add

    // Reallocate memory for the tasks
    *task = (tache *)realloc(*task, (*nbrTaches + numTasksToAdd) * sizeof(tache));

    for (int i = *nbrTaches; i < *nbrTaches + numTasksToAdd; i++) {
        (*task)[i].id = countID;
        countID++;
        printf("Saisir l'intitule de la tache (%d) : ", i + 1);
        getchar();
        gets((*task)[i].titre);
        printf("Saisir la description de la tache (%d) : ", i + 1);
        gets((*task)[i].description);
        do{
            printf("Saisir le deadline de la tache (sous forme yyyy/mm/dd) : ");
            scanf(" %d/%d/%d", &((*task)[i].deadline.an), &((*task)[i].deadline.mois), &((*task)[i].deadline.jour));
            if ((*task)[i].deadline.an < 1990 ||
            (*task)[i].deadline.mois < 1 || (*task)[i].deadline.mois > 12 ||
            (*task)[i].deadline.jour < 1 || (*task)[i].deadline.jour > 31) {
                printf("Erreur de saisie. Veuillez entrer une date valide (yyyy/mm/dd).\n");
            }
        } while ((*task)[i].deadline.an < 1990 ||
                (*task)[i].deadline.mois < 1 || (*task)[i].deadline.mois > 12 ||
                (*task)[i].deadline.jour < 1 || (*task)[i].deadline.jour > 31 );
        printf("Saisir le statut de la tache (%d)  : \n[1] : To Do\n[2] : Doing\n[3] : Done\n", i + 1);
        scanf("%d", &status);
        switch (status) {
            case 1:
                strcpy((*task)[i].statut, "todo");
                break;
            case 2:
                strcpy((*task)[i].statut, "doing");
                break;
            case 3:
                strcpy((*task)[i].statut, "done");
                break;
            default:
                printf("Choix invalide\n");
                break;
        }
        if (status == 1) {
            printf("added as To Do !");
        } else if (status == 2) {
            printf("added as Doing");
        } else if (status == 3) {
            printf("added as Done !");
        }

        printf("\n------------------------------------------\n");
    }

    *nbrTaches += numTasksToAdd;
    start = countID;
}

int main() {
    int choixMod, choixSearch, id, deadline, modifStatus,taskToAdd , choice = -1; // Initialize choice to -1
    char desc[100], status[30], titre[30], suppId;
    tache *task = NULL; // Declare task as a pointer

    do {
        menue();

        printf("Entrez votre choix: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n[1] : pour une seul tache!\n[2] : pour plusieur taches !\n[0] : Pour revenir au menu principal\n");
                scanf("%d",&taskToAdd);
                switch (taskToAdd)
                {
                case 1:
                    addOneTask(&task, &nbrTaches);
                    break;
                case 2:

                    addTask(&task, &nbrTaches); // Pass task and nbrTaches as pointers

                    break;
                case 0:
                    break;

                default:
                    break;
                }
                break;
            case 2:
                displayTasks(task, nbrTaches);
                break;
            case 3:
                sortAlpha(task);
                break;
            case 4:
                sortDeadline(task);
                break;
            case 5:
                if(nbrTaches < 1){
                    printf("there is no tasks to display");
                }else{
                    initTodayDate(); // Initialize today's date
                    deadline3Jours(task, nbrTaches); // Display tasks with deadlines within 3 days
                }
                break;
            case 6:
                printf("[1] : Modifier la description.\n[2] : Modifier le statut\n[3] : Modifier le deadline.\n[0] : Pour revenir au menu principal\n");
                scanf("%d", &choixMod);
                switch (choixMod) {
                    case 0 :
                        break;
                    case 1:
                        if (nbrTaches < 1){
                            printf("there no task to update");
                        }else{
                            printf("entre ID du tache que vous voullez modifier : \n");
                            scanf("%d", &id);
                            printf("voullez vous vraiment modifier description de la tache ID [%d] (O/N) : \n", id);
                            scanf(" %c", &suppId);
                            if(suppId == 'O' || suppId == 'o'){
                                printf("entre la nouvelle description : \n");
                                getchar();
                                gets(desc);
                                modifierDesc(task, id, desc);
                            }else{
                                printf("modification annulee !! \n");
                            }

                            break;
                        }
                    case 2:
                        if (nbrTaches < 1){
                            printf("there no task to update");
                        }else{
                        printf("entre ID du tache que vous voullez modifier : \n");
                        scanf("%d", &id);
                        printf("voullez vous vraiment modifier statut de la tache ID [%d] (O/N) : \n", id);
                        scanf(" %c", &suppId);
                        if(suppId == 'O' || suppId == 'o'){
                            printf("choisi le statut de la tache  : \n[1] : To Do\n[2] : Doing\n[3] : Done\n");
                            scanf("%d", &modifStatus);
                            modifierStatus(task, id, modifStatus);
                        }else{
                            printf("modification annulee !! \n");
                        }

                        break;
                        }
                    case 3:
                    if (nbrTaches < 1){
                        printf("there no task to update");
                    }else{
                        printf("Entrez l'ID de la tâche que vous voulez modifier : \n");
                        scanf("%d", &id);
                        printf("Voulez-vous vraiment modifier la deadline de la tâche ID [%d] (O/N) : \n", id);
                        scanf(" %c", &suppId);
                        if (suppId == 'O' || suppId == 'o') {
                            Date newDeadline;
                            do {
                                printf("Saisir la nouvelle deadline de la tache (sous forme yyyy/mm/dd) : ");
                                scanf("%d/%d/%d", &newDeadline.an, &newDeadline.mois, &newDeadline.jour);
                                if (newDeadline.an < 1990 ||
                                    newDeadline.mois < 1 || newDeadline.mois > 12 ||
                                    newDeadline.jour < 1 || newDeadline.jour > 31) {
                                    printf("Erreur de saisie. Veuillez entrer une date valide (yyyy/mm/dd).\n");
                                }
                            } while (newDeadline.an < 1990 ||
                                    newDeadline.mois < 1 || newDeadline.mois > 12 ||
                                    newDeadline.jour < 1 || newDeadline.jour > 31);
                        modifierDeadline(task, id, newDeadline);
                        } else {
                            printf("Modification annulée !! \n");
                        }
                        break;
                    }
                }
                break;
            case 7:
                printf("entre ID du tache que vous voullez supprimer : \n");
                scanf("%d", &id);
                printf("voullez vous vraiment supprimer la tache ID [%d] (O/N) : \n", id);
                scanf(" %c", &suppId);
                if(suppId == 'O' || suppId == 'o'){
                    supprimerTask(task, id);
                }else{
                    printf("suppression annulee !! \n");
                }

                break;
            case 8:
                printf("[1] : Rechercher par ID.\n[2] : Rechercher par Titre.\n[0] : Pour revenir au menu principal\n");
                scanf("%d", &choixSearch);
                switch (choixSearch) {
                    case 0 :
                        break;
                    case 1:
                        printf("entre ID du tache que vous voullez trouver : \n");
                        scanf("%d", &id);
                        searchById(task, id);
                        break;
                    case 2:
                        printf("entre le titre du tache que vous voullez trouver : \n");
                        getchar();
                        gets(titre);
                        searchByTitre(task, titre);
                        break;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                }
                break;
            case 9:
                printf("[1] : Afficher le nombre total des taches.\n[2] : Afficher le nombre de taches completes et incompletes.\n[3] : Afficher le nombre de jours restants jusqu au delai de chaque tache.\n[0] : Pour revenir au menu principal\n");
                scanf("%d", &choixSearch);
                switch (choixSearch) {
                    case 0 :
                        break;
                    case 1:
                        nbrTotal(task);
                        break;
                    case 2:
                        nbrTotalCompleteIncomplete(task);
                        break;
                    case 3:
                        displayDaysRemaining(task, nbrTaches);
                        break;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                }
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choice != 0);

    free(task); // Free the dynamically allocated memory

    return 0;
}
