/* Inclusion des bibliothèques contenant des fonctions utiles */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************/
/*                                                                            */
/*     Les variables que nous utiliserons seront des variables locales        */
/*            c'est-à-dire des variables propres aux fonctions                */
/* Cependant, l'emploi des pointeurs nous permettra d'voir facilement accès   */
/*            aux données des variables grâce à leur adresse                  */
/*                                                                            */
/*         Notons par ailleurs la création d'autres fonctions afin            */
/*                  de rendre le programme plus optimal                       */
/*                                                                            */
/*                      by GUIRE Elisée Aimé Enoch                            */
/******************************************************************************/

/*============================================
Construction de la structure de type personne
==============================================*/
typedef struct personne
{
  char nom[50], prenom[50], telephone[50], mail[50]; // Tableau de chaîne de caractères
  struct personne *suivant;                          // Pointeur sur la personne suivante
} personne;

/*===============================================
Construction de la structure de la liste chainée
=================================================*/
typedef struct liste
{
  personne *premier; // Pointeur sur la première personne
} listeChainee;

/*=====================================================
Fonction qui initialise la liste avant de la retourner
=======================================================*/
listeChainee *Initialisation()
{
  listeChainee *liste = (listeChainee *)malloc(sizeof(listeChainee)); // Déclaration d'une liste avec une allocation dynamique de l'espace mémoire
  liste->premier = NULL;                                              // Le premier élément de la liste pointe vers NULL car celle-ci est vide
  return liste;                                                       // On retourne la liste nouvellement initialisée
}

/*=========================================================================
Procédure permettant de tronquer une chaine de caractètes à 30 caractères
===========================================================================*/
void Tronquer_Mot(char *mot)
{
  int tailleMot = 0;
  while (*mot != '\0')
  {
    tailleMot++;
    if (tailleMot > 30)
    {
      *mot = NULL;
    }
    mot++;
  }
}

/*===============================================================================
Fonction permettant de convertir une chaine de caractère MAJUSCULE en minuscule
=================================================================================*/
char *Conversion_Minuscule(char *mot)
{
  char *caractere = mot;
  char MAJ[27], min[27], lettre_MAJ = 'A', lettre_min = 'a';
  int casse, i = 0;
  // Initialisation de l'alphabet en minuscule
  while (i < 26 && lettre_min <= 'z')
  {
    min[i] = lettre_min;
    lettre_min++;
    i++;
  }
  i = 0;
  // Initialisation de l'alphabet en MAJUSCULE
  while (i < 26 && lettre_MAJ <= 'Z')
  {
    MAJ[i] = lettre_MAJ;
    lettre_MAJ++;
    i++;
  }
  while (*caractere != '\0')
  {
    if (*caractere >= 'a' && *caractere <= 'z')
    {
      casse = 0; // Si lettre minuscule, casse prend 0
    }
    if (*caractere >= 'A' && *caractere <= 'Z')
    {
      casse = 1; // Si lettre MAJUSCULE, casse prend 1
    }
    if (casse == 1) // Si MAJUSCULE
    {
      for (i = 0; i < 26; i++) // Parcours les 26 lettres de l'alphabet
      {
        if (*caractere == MAJ[i]) // Si la lettre correspond à une lettre en MAJUSCULE
        {
          *caractere = min[i]; // La lettre prend son équivalent en minuscule car les lettres ont exactement la même position
        }
      }
    }
    caractere++; // On avance dans la chaine
  }
  return mot;
}

/*======================================================================================================
Fonction en remplacement à 'stricmp' qui compare sans sensibilité à la casse deux chaînes de caractères
========================================================================================================*/
int Comparaison(char *entree, char *sortie)
{
  char *p_entree = entree, *p_sortie = sortie; // Pointeurs vers les variables qui vont recevoir les chaines converties avec la fonction Conversion()
  char tmp_entree[30], tmp_sortie[30];
  int count_entree = 0, count_sortie = 0, trouver = 0, j = 0;
  // Récupération des deux chaines passées en paramètre dans des variables 'tmp'
  while (*p_entree != '\0')
  {
    tmp_entree[j] = *p_entree;
    count_entree++; // Taille de la chaine
    p_entree++;
    j++;
  }
  j = 0;
  while (*p_sortie != '\0')
  {
    tmp_sortie[j] = *p_sortie;
    count_sortie++; // Taille de la chaine
    p_sortie++;
    j++;
  }
  // Conversion des deux chaines en minuscule
  p_entree = Conversion_Minuscule(tmp_entree);
  p_sortie = Conversion_Minuscule(tmp_sortie);
  if (count_entree == count_sortie) // Si les deux chaines ont la même taille il se pourrait qu'elles soient pareilles dont on continue
  {
    while (*p_entree != '\0' && *p_sortie != '\0') // Tandis qu'on n'est pas à la fin des deux chaines
    {
      if (*p_entree == *p_sortie) // Si chaque lettre des deux chaines sont identiques
      {
        trouver++; // On incrémente la variable 'trouver'
      }
      p_entree++;
      p_sortie++;
    }
    if (count_entree == trouver) // Si la taille équivaut au nombre de 'trouver' alors elles sont identiques
    {
      return 0;
    }
    // Autrement elles ne sont pas identiques
    else if (trouver == 0)
    {
      return 1;
    }
  }
  else
  {
    return 1;
  }
}

/*=============================================================================
Fonction de contrôle qui vérifie si la chaine saisie est bien un digit(entier)
===============================================================================*/
int Controle_Entier(char *mot)
{
  char *ptr = mot; // ptr pointe sur l'adresse du premier caractère de 'mot' c'est-à-dire ->&mot[0]
  int i = 0, trouver = 0, count = 0;
  while (*ptr != '\0')
  {
    count++; // Taille du mot. Pareil que count = strlen(mot);
    ptr++;
  }
  ptr = mot;           // ->&mot[0]
  while (*ptr != '\0') // Tant qu'on n'est pas à la fin du mot
  {
    if (*ptr == '0' || *ptr == '1' || *ptr == '2' || *ptr == '3' || *ptr == '4' || *ptr == '5' || *ptr == '6' || *ptr == '7' || *ptr == '8' || *ptr == '9')
    {
      trouver++; // On incrémente trouver si le caractère correspond
    }
    ptr++; // Et on avance au caractère suivant
  }
  if (count == trouver) // Si c'est la même taille alors il y a correspondance
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*=================================================================================
Fonction de contrôle qui vérifie si la chaine saisie est bien une suite d'alphabet
===================================================================================*/
int Controle_Alphabet(char *mot)
{
  char MAJ[27], min[27], lettre_MAJ = 'A', lettre_min = 'a';
  char *ptr = mot;
  int i = 0, trouver = 0, count = 0;
  // Initialisation de l'alphabet en minuscule
  while (i < 26 && lettre_min <= 'z')
  {
    min[i] = lettre_min;
    lettre_min++;
    i++;
  }
  i = 0;
  // Initialisation de l'alphabet en MAJUSCULE
  while (i < 26 && lettre_MAJ <= 'Z')
  {
    MAJ[i] = lettre_MAJ;
    lettre_MAJ++;
    i++;
  }
  i = 0;
  while (*ptr != '\0')
  {
    count++; // Taille de la chaine de caractère
    ptr++;
  }
  ptr = mot;
  while (*ptr != '\0')
  {
    for (i = 0; i < 26; i++)
    {
      if (*ptr == min[i] || *ptr == MAJ[i]) // Si le caractère correspond à une lettre de l'alphabet
      {
        trouver++; // On incrémente 'trouver'
      }
    }
    ptr++; // Et on avance au caractère suivant
  }
  if (count == trouver) // Il y a correspondance
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*=================================================================================
Fonction de contrôle qui vérifie si la chaine saisie est bien une adresse mail
===================================================================================*/
int Controle_Mail(char *mot)
{
  char *ptr = mot;
  int i = 0, trouver = 0, count = 0;
  while (*ptr != '\0')
  {
    if (*ptr == '@') // Si le caractère correspond @ : signe caractéristique d'une adresse mail
    {
      trouver++; // On incrémente 'trouver'
    }
    ptr++; // Et on avance au caractère suivant
  }
  if (trouver != 0) // Il y a correspondance
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*=================================================================
Procédure pour sauvegarder les données de la liste dans un fichier
===================================================================*/
void Sauvegarder_Dans_Fichier(listeChainee *liste)
{
  FILE *fichier;
  personne *courant = liste->premier;
  char rep[50];
  system("clear");
  printf("\nSauvegarder vos données dans un fichier ?(o/n) ");
  scanf("%s", rep);
  while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O' || Controle_Alphabet(rep) == 1 || Controle_Entier(rep) == 0)
  {
    printf("\n Votre réponse(o/n): ");
    scanf("%s", rep);
  }
  if (rep[0] == 'n' || rep[0] == 'N')
  {
    system("clear");
    printf("\nSauvegarde échouée !\n\n");
    exit(EXIT_FAILURE);
  }
  if (rep[0] == 'o' || rep[0] == 'O')
  {
    fichier = fopen("Repertoire.txt", "w"); // Ouverture du fichier en mode d'écriture
    while (courant != NULL)                 // Parcours de la liste jusqu'à la fin matérialisée par NULL
    {
      fprintf(fichier, "%s\t%s\t%s\t%s\n", courant->nom, courant->prenom, courant->telephone, courant->mail);
      courant = courant->suivant;
    }
    system("clear");
    printf("\nSauvegarde réussie !\n\n");
    fclose(fichier);
    exit(EXIT_SUCCESS);
  }
}

/*=======================================================
Procédure pour insérer les éléments à la fin de la liste
=========================================================*/
void Insertion(listeChainee *liste, personne *nouveau)
{
  personne *courant = liste->premier;
  if (courant != NULL) // Si la première personne existe
  {
    while (courant->suivant != NULL) // Si le suivant de la personne courante n'est pas NULL
    {
      courant = courant->suivant; // On avance jusqu'à la fin qui est NULL
    }
    // On quitte la boucle while si le suivant de la personne courante est NULL: c'est la fin
    courant->suivant = nouveau; // On insère donc la nouvelle personne à la fin
    nouveau->suivant = NULL;    // Et le suivant de la nouvelle personne pointe sur NULL
  }
  else // Il n'y a pas de personne dans la liste
  {
    nouveau->suivant = liste->premier; // La nouvelle personne est la première sur la liste
    liste->premier = nouveau;          // Et pour ne pas perdre la liste de vue, le pointeur de premier pointe sur 'nouveau'
  }
}

/*=================================================================================================================================================================
Initialiser la liste avec les données du fichier. Cette fonction est pratique dans la mesure ou elle permet de récupérer les données déjà stockées dans le fichier
===================================================================================================================================================================*/
void Initialiser_Repertoire(listeChainee *liste)
{
  personne *nouveau = (personne *)malloc(sizeof(personne));
  int count = 0;
  FILE *fichier = fopen("Repertoire.txt", "r"); // Ouverture du fichier en mode lecture
  if (fichier != NULL)
  {
    while (fscanf(fichier, "%s\t%s\t%s\t%s\n", nouveau->nom, nouveau->prenom, nouveau->telephone, nouveau->mail) != EOF)
    {
      Insertion(liste, nouveau);
      nouveau = (personne *)malloc(sizeof(personne)); // On alloue un nouvel espace pour l'élément suivant
    }
    fclose(fichier);
  }
}

/*====================================================
Procédure pour enregistrer une personne dans la liste
======================================================*/
void Creer_Enregistrement(listeChainee *liste)
{
  personne *nouveau = (personne *)malloc(sizeof(personne));
  personne *courant = liste->premier;
  char rep[50];
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  printf("\n\nNom: ");
  scanf("%s", nouveau->nom);
  Tronquer_Mot(nouveau->nom);
  while (Controle_Alphabet(nouveau->nom) == 1)
  {
    printf("\nSaisi non alphabétique. Réessayez !\n");
    printf("\n\nNom: ");
    scanf("%s", nouveau->nom);
    Tronquer_Mot(nouveau->nom);
  }
  printf("\nPrénom: ");
  scanf("%s", nouveau->prenom);
  Tronquer_Mot(nouveau->prenom);
  while (Controle_Alphabet(nouveau->prenom) == 1)
  {
    printf("\nSaisi non alphabétique. Réessayez !\n");
    printf("\nPrénom: ");
    scanf("%s", nouveau->prenom);
    Tronquer_Mot(nouveau->prenom);
  }
  printf("\nTéléphone: ");
  scanf("%s", nouveau->telephone);
  Tronquer_Mot(nouveau->telephone);
  while (Controle_Entier(nouveau->telephone) == 1)
  {
    printf("\nSaisi non numérique. Réessayez !\n");
    printf("\nTéléphone: ");
    scanf("%s", nouveau->telephone);
    Tronquer_Mot(nouveau->telephone);
  }
  printf("\nMail: ");
  scanf("%s", nouveau->mail);
  Tronquer_Mot(nouveau->mail);
  while (Controle_Mail(nouveau->mail) == 1)
  {
    printf("\nMail incorrect. Réessayez !\n");
    printf("\nMail: ");
    scanf("%s", nouveau->mail);
    Tronquer_Mot(nouveau->mail);
  }
  Insertion(liste, nouveau);
  system("clear");
  printf("\n----------ENREGISTREMENT----------\n");
  printf("\nAjout réussi !\n");
  printf("\nAjouter une autre personne ? (o/n): ");
  scanf("%s", rep);
  while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O' || Controle_Alphabet(rep) == 1 || Controle_Entier(rep) == 0)
  {
    printf("\n Votre réponse(o/n): ");
    scanf("%s", rep);
  }
  if (rep[0] == 'n' || rep[0] == 'N')
  {
    return;
  }
  if (rep[0] == 'o' || rep[0] == 'O')
  {
    Creer_Enregistrement(liste); // Rappel de la fonction pour ajouter une autre personne
  }
}

/*=================================================
Procédure permettant d'afficher tout le repertoire
===================================================*/
void Afficher_Repertoire(listeChainee *liste)
{
  personne *courant = liste->premier;
  int count = 0;
  system("clear");
  printf("\n----------AFFICHAGE----------\n");
  if (courant == NULL)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    while (courant != NULL)
    {
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      courant = courant->suivant;
      count++;
      printf("\n----------------------------");
    }
    printf("\n\nTotal: %d\n", count);
  }
}

/*================================================
Procédure pour rechercher par le nom et le prenom
==================================================*/
void Recherche_Nom_Prenom(personne *courant)
{
  char nomSearch[50], prenomSearch[50];
  int trouver = 0;
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  printf("\nNom: ");
  scanf("%s", nomSearch);
  Tronquer_Mot(nomSearch);
  printf("\nPrénom: ");
  scanf("%s", prenomSearch);
  Tronquer_Mot(prenomSearch);
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  while (courant != NULL)
  {
    if (Comparaison(courant->nom, nomSearch) == 0 && Comparaison(courant->prenom, prenomSearch) == 0)
    {
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      printf("\n----------------------------");
      trouver++;
    }
    courant = courant->suivant;
  }
  if (trouver == 0)
  {
    printf("\nPersonne non trouvée !\n");
  }
  else
  {
    printf("\n\n%d personne(s) trouvée(s)\n", trouver);
  }
}

/*===================================================
Procédure pour rechercher par le numero de téléphone
=====================================================*/
void Recherche_Telephone(personne *courant)
{
  char telSearch[50];
  int trouver = 0;
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  printf("\nTéléphone: ");
  scanf("%s", telSearch);
  Tronquer_Mot(telSearch);
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  while (courant != NULL)
  {
    if (strcmp(courant->telephone, telSearch) == 0)
    {
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      printf("\n----------------------------");
      trouver++;
    }
    courant = courant->suivant;
  }
  if (trouver == 0)
  {
    printf("\nPersonne non trouvée !\n");
  }
  else
  {
    printf("\n\n%d personne(s) trouvée(s)\n", trouver);
  }
}

/*===========================================
Procédure pour rechercher par l'adresse mail
=============================================*/
void Recherche_Mail(personne *courant)
{
  char mailSearch[50];
  int trouver = 0;
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  printf("\nMail: ");
  scanf("%s", mailSearch);
  Tronquer_Mot(mailSearch);
  system("clear");
  printf("\n----------RECHERCHE----------\n");
  while (courant != NULL)
  {
    if (strcmp(courant->mail, mailSearch) == 0) // J'utilise strcmp ici car l'adresse mail est sensible à la casse
    {
      printf("\nNom: %s", courant->nom);
      printf("\nPrénom: %s", courant->prenom);
      printf("\nTéléphone: %s", courant->telephone);
      printf("\nMail: %s", courant->mail);
      printf("\n----------------------------");
      trouver++;
    }
    courant = courant->suivant;
  }
  if (trouver == 0)
  {
    printf("\nPersonne non trouvée !\n");
  }
  else
  {
    printf("\n\n%d personne(s) trouvée(s)\n", trouver);
  }
}

/*=======================================================
Procédure qui appelle les autres procédures de recherche
=========================================================*/
void Recherche(listeChainee *liste)
{
  char rep[50];
  personne *courant = liste->premier;

  system("clear");
  printf("\n----------RECHERCHE----------\n");
  if (courant == NULL)
  {
    printf("\nRépertoire vide\n");
  }
  else
  {
    printf("\n(1)\tPar le nom et le prénom\n");
    printf("\n(2)\tPar le numéro de téléphone\n");
    printf("\n(3)\tPar l'adresse mail\n");
    printf("\n\tChoix: ");
    scanf("%s", rep);
    while (rep[0] != '1' && rep[0] != '2' && rep[0] != '3' || Controle_Entier(rep) == 1)
    {
      printf("\n Votre réponse: ");
      scanf("%s", rep);
    }
    switch (atoi(rep))
    {
    case 1:
      Recherche_Nom_Prenom(courant);
      break;
    case 2:
      Recherche_Telephone(courant);
      break;
    case 3:
      Recherche_Mail(courant);
      break;
    }
  }
}

/*==============================================================================================
Fonction qui récupère la liste, supprime l'élément s'il existe et retourne le reste de la liste
================================================================================================*/
listeChainee *Retirer(listeChainee *liste)
{
  personne *courant = liste->premier;
  personne *next;
  char nomDelete[50], prenomDelete[50], rep[50];
  int trouver = 0;
  system("clear");
  printf("\n----------SUPPRESSION----------\n");
  if (courant == NULL)
  {
    printf("\nRepertoire vide\n");
    return liste;
  }
  else
  {
    printf("\nNom: ");
    scanf("%s", nomDelete);
    Tronquer_Mot(nomDelete);
    printf("\nPrénom: ");
    scanf("%s", prenomDelete);
    Tronquer_Mot(prenomDelete);
    if (Comparaison(courant->nom, nomDelete) == 0 && Comparaison(courant->prenom, prenomDelete) == 0)
    {
      trouver++;
      printf("\nVoulez-vous vraiment supprimer la personne ?(o/n) ");
      scanf("%s", rep);
      while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O' || Controle_Alphabet(rep) == 1 || Controle_Entier(rep) == 0)
      {
        printf("\n Votre réponse(o/n): ");
        scanf("%s", rep);
      }
      if (rep[0] == 'n' || rep[0] == 'N')
      {
        return liste;
      }
      if (rep[0] == 'o' || rep[0] == 'O')
      {
        liste->premier = courant->suivant;
        free(courant);
        system("clear");
        printf("\n----------SUPPRESSION----------\n");
        printf("\nSuppression réussie !\n");
        return liste;
      }
    }
    else
    {
      next = courant->suivant;
      while (next != NULL)
      {
        if (Comparaison(next->nom, nomDelete) == 0 && Comparaison(next->prenom, prenomDelete) == 0 && next != NULL)
        {
          trouver++;
          printf("\nVoulez-vous vraiment supprimer la personne ?(o/n) ");
          scanf("%s", rep);
          while (rep[0] != 'n' && rep[0] != 'N' && rep[0] != 'o' && rep[0] != 'O' || Controle_Alphabet(rep) == 1 || Controle_Entier(rep) == 0)
          {
            printf("\n Votre réponse(o/n): ");
            scanf("%s", rep);
          }
          if (rep[0] == 'n' || rep[0] == 'N')
          {
            return liste;
          }
          if (rep[0] == 'o' || rep[0] == 'O')
          {
            courant->suivant = next->suivant;
            free(next);
            system("clear");
            printf("\n----------SUPPRESSION----------\n");
            printf("\nSuppression réussie !\n");
            return liste;
          }
        }
        if (next == NULL)
        {
          trouver = 0;
        }
        courant = next;
        next = next->suivant;
      }
    }
    if (trouver == 0)
    {
      system("clear");
      printf("\n----------SUPPRESSION----------\n");
      printf("\nPersonne non trouvée !\n");
      return liste;
    }
  }
  return liste;
}

/*=======================================
Procédure qui affiche les options du menu
=========================================*/
void Menu()
{
  system("clear");
  printf("\n----------MENU PRINCIPAL----------\n");
  printf("\n(1)\tAjouter une personne\n");
  printf("\n(2)\tAfficher le répertoire\n");
  printf("\n(3)\tFaire une recherche\n");
  printf("\n(4)\tRetirer une personne\n");
  printf("\n(5)\tTerminer\n");
  printf("\nVotre choix: ");
}

/*=================================
Fonction pour quitter le programme
===================================*/
int Quitter(listeChainee *liste)
{
  char rep[50];
  do
  {
    system("clear");
    printf("\nAttention vous risquez de perdre vos données!\n");
    printf("\n\t Que voulez-vous faire ?\n");
    printf("\n(1)\t| REVENIR AU MENU\n");
    printf("\n(2)\t| ENREGISTRER AVANT DE QUITTER\n");
    printf("\n(3)\t| QUITTER SANS ENREGISTRER\n");
    printf("\nReponse: ");
    scanf("%s", rep);
  } while (Controle_Entier(rep) == 1);
  switch (atoi(rep))
  {
  case 1:
    return 1;
    break;
  case 2:
    Sauvegarder_Dans_Fichier(liste);
    exit(EXIT_SUCCESS);
    break;
  case 3:
    system("clear");
    printf("\n\nAurevoir\n\n");
    exit(EXIT_SUCCESS);
  default:
    printf("\nChoix inexistant\n");
    break;
  }
}

/*=====================
FONCTION PRINCIPALE
=======================*/
int main()
{
  int Action, choice;
  listeChainee *Repertoire = Initialisation();
  char rep[50];
  Initialiser_Repertoire(Repertoire);
  do
  {
    Menu();
    scanf("%s", rep);
    while (Controle_Entier(rep) == 1)
    {
      Menu();
      scanf("%s", rep);
    }
    Action = atoi(rep);
    switch (Action)
    {
    case 1:
      Creer_Enregistrement(Repertoire);
      break;
    case 2:
      Afficher_Repertoire(Repertoire);
      break;
    case 3:
      Recherche(Repertoire);
      break;
    case 4:
      Repertoire = Retirer(Repertoire);
      break;
    case 5:
      choice = Quitter(Repertoire);
      break;
    default:
      system("clear");
      printf("\nChoix inexistant !\n");
      break;
    }
    printf("\n\nAppuyer sur Entrée pour revenir au menu ");
    getchar();
  } while (getchar() == '\n' || choice == 1);
  free(Repertoire);
  return 0;
}
