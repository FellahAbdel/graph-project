// relations.c�: d�finit le point d'entr�e pour l'application .
//

typedef int bool;
#define false 0
#define true -1

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"

////////////////////////////////////////
// Exercice 1: Classement des Relations

typedef enum
{
    FRERE = 2,
    COUSIN,
    PARENT,
    ONCLE,
    EPOUX,
    AMI,
    VIT,
    CONNAIT,
    CHEF,
    COLLEGUE,
    LOCATAIRE,
    TRAVAILLE,
    PROPRIETAIRE,
    SITUE,
    DECOUVERT
} rtype;

bool est_lien_parente(rtype id)
{
    return id >= FRERE && id <= EPOUX;
}

bool est_lien_professionel(rtype id)
{
    return id >= CHEF && id <= COLLEGUE;
}

bool est_lien_connaissance(rtype id)
{
    return id <= AMI && id <= CONNAIT;
}

char *toStringRelation(rtype id)
{
    //* id = 0 => omega : NULL
    //* id = 1 => INCONNUE
    char *relations[] = {NULL, "INCONNUE", "FRERE", "COUSIN", "PARENT",
                         "ONCLE", "EPOUX", "AMI", "VIT",
                         "CONNAIT", "CHEF",
                         "COLLEGUE", "LOCATAIRE", "TRAVAILLE",
                         "PROPRIETAIRE", "SITUE", "DECOUVERT"};

    return relations[id];
}

////////////////////////////////////////
// Exercice 2: Liste de pointeurs

typedef struct s_node
{
    void *val; // pointeur vers objet quelconque
    struct s_node *suiv;
} *listeg;

listeg listegnouv() { return NULL; }

listeg adjtete(listeg lst, void *x)
{
    //* Création du nouveau noeud
    listeg newNode = (listeg)malloc(sizeof(struct s_node));

    //* On vérifie que le malloc a bien eu lieu.
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur : allocation échouée.\n");
        exit(EXIT_FAILURE);
    }

    newNode->suiv = lst;
    newNode->val = x;

    return newNode;
}

listeg adjqueue(listeg lst, void *x)
{
    //* Création du nouveau noeud
    listeg newNode = (listeg)malloc(sizeof(struct s_node));

    //* On vérifie le malloc
    if (newNode == NULL)
    {
        fprintf(stderr, "Erreur : allocation échouée.\n");
        exit(EXIT_FAILURE);
    }

    newNode->val = x;

    //* Cas de la liste vide
    if (lst == NULL)
    {
        newNode->suiv = NULL;
        return newNode;
    }

    //* Cas où la liste a au moins un élément.
    //* On se positionne sur la queue.
    listeg temp = lst;
    while (temp->suiv != NULL)
    {
        temp = temp->suiv;
    }
    //* On est sur la queue.
    //* On place le noeud à la queue.
    temp->suiv = newNode;
    newNode->suiv = NULL;

    return lst;
}

listeg suptete(listeg lst)
{
    if (lst == NULL)
    {
        return NULL;
    }

    listeg nodeToDestroy = lst;
    //* On recupère le noeud suivant
    lst = lst->suiv;

    //* Destruction du noeud
    free(nodeToDestroy);

    return lst;
}

void *tete(listeg lst)
{
    return lst != NULL ? lst->val : NULL;
}

bool estVide(listeg lst)
{
    return lst == NULL;
}

int longueur(listeg lst)
{
    return estVide(lst) ? 0 : 1 + longueur(lst->suiv);
}

void detruire(listeg lst)
{
    listeg temp = lst;
    while (temp != NULL)
    {
        temp = suptete(temp);
    }
}

int cmp(void *objet1, void *objet2)
{
    return strncmp((char *)objet1, (char *)objet2, 1);
}

listeg rech(listeg lst, void *x, int (*comp)(void *, void *))
{
    //* objectsFound : contiendra tous les noeuds trouvés.
    listeg objectsFound = NULL;

    while (!estVide(lst))
    {
        if (!comp(x, lst->val))
        {
            //* L'ordre dans lequel les éléments sont placés dans
            //* la listeg n'a pas d'importance
            objectsFound = adjtete(objectsFound, lst->val);
        }
        lst = lst->suiv;
    }

    return objectsFound;
}

////////////////////////////////////////
// Exercice 3: Construction du graphe

#define LONG_NOM_MAX 64
typedef enum
{
    PERSONNE = 1,
    OBJET,
    ADRESSE,
    VILLE
} etype;

typedef struct s_entite
{
    char nom[LONG_NOM_MAX]; // le nom de l�entit� p.ex � Peugeot 106 �
    etype ident;            // l�identifiant associ�, p.ex OBJET
} *Entite;
// 3.1 les structures de donn�es
typedef struct s_sommet
{
    // A DEFINIR
    listeg larcs;
    Entite x;
} *Sommet;

typedef struct s_arc
{
    // A DEFINIR
    rtype t;
    Entite x;
} *Arc;

typedef struct s_relations
{
    // A DEFINIR
    listeg liste;
} *Relations;

// 3.2 les constructeurs
Entite creerEntite(char *s, etype e)
{
    Entite newEntity = (Entite)malloc(sizeof(struct s_entite));

    if (newEntity == NULL)
    {
        fprintf(stderr, "Allocation echouée.\n");
        exit(EXIT_FAILURE);
    }

    //* Il faudra penser utiliser free pour effacer newEntity->nom si l'on veut effacer l'entité
    strdup(newEntity->nom, s);
    newEntity->ident = e;

    return newEntity;
}
Sommet nouvSommet(Entite e)
{
    return NULL;
}
Arc nouvArc(Entite e, rtype type)
{
    return NULL;
}
void relationInit(Relations *g)
{
}
void relationFree(Relations *g)
{
}

// 3.3 les comparaisons
int compEntite(void *e, void *string)
{
    return 0;
}
int compSommet(void *s, void *string)
{
    return 0;
}
int compArc(void *a, void *string)
{
    return 0;
}

// 3.4 ajout d'entites et de relations
void adjEntite(Relations g, char *nom, etype t)
{
}
// PRE CONDITION: id doit �tre coh�rent avec les types des sommets correspondants � x et y
//                p.ex si x est de type OBJET, id ne peut pas etre une relation de parente
// PRE CONDITION: strcmp(nom1,nom2)!=0
void adjRelation(Relations g, char *nom1, char *nom2, rtype id)
{
}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
listeg en_relation(Relations g, char *x)
{
    return NULL;
}
listeg chemin2(Relations g, char *x, char *y)
{
    return NULL;
}
// 4.2 verifier un lien de parente
// PRE CONDITION: strcmp(x,y)!=0
bool ont_lien_parente(Relations g, char *x, char *y)
{
    return false;
}

// 4.3 tester connaissances
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent(Relations g, char *x, char *y)
{
    return false;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_proba(Relations g, char *x, char *y)
{
    return false;
}
// PRE CONDITION: les sommets correspondants � x et y sont de type PERSONNE
// PRE CONDITION: strcmp(x,y)!=0
bool se_connaissent_peutetre(Relations g, char *x, char *y)
{
    return false;
}

////////////////////////////////////////
// Exercice 5: Affichages
void affiche(void *objet)
{
    //* Dans notre cas, on affiche une chaine
    printf("%s\n", (char *)objet);

    return;
}

void affichelg(listeg l, void (*aff)(void *))
{
    while (!estVide(l))
    {
        aff(l->val);
        l = l->suiv;
    }
}

void afficheEntite(void *x)
{
}
void afficheArc(void *x)
{
}

////////////////////////////////////////
// Exercice 6: Parcours
void affiche_degre_relations(Relations r, char *x)
{
}

int main()
{
    //* Test des fonctions sur la liste.
    listeg maListe = listegnouv();

    if (estVide(maListe))
    {
        printf("Liste vide.\n");
    }
    else
    {
        printf("Liste non vide.\n");
    }

    maListe = adjtete(maListe, (void *)"diallo");
    if (estVide(maListe))
    {
        printf("Liste vide.\n");
    }
    else
    {
        printf("Liste non vide.\n");
    }

    maListe = adjtete(maListe, (void *)"rhaby");

    //* On ajoute en queue.
    maListe = adjqueue(maListe, (void *)"aissata");

    //* On supprime la tête.
    maListe = suptete(maListe);

    affichelg(maListe, affiche);

    //* On affiche la tête
    printf("La tête : ");
    affiche(tete(maListe));

    //* La longueur
    printf("Longueur : %d\n", longueur(maListe));

    //* Recherchons tous les noms commençant par "d";

    listeg names = rech(maListe, (void *)"aissata", cmp);
    printf("Names found :\n ");
    affichelg(names, affiche);

    //* Destruction de la liste.
    detruire(maListe);

    //* On a effacé la liste, du coup on a plus le droit d'y toucher
    // printf("Longueur : %d\n", longueur(maListe));
    //* On sort.
    return 1;
    int i, j;
    Relations r;
    relationInit(&r);
    // ajouter les entites de l'exemple
    char *tabe[] = {"KARL", "LUDOVIC", "CELINE", "CHLOE", "GILDAS", "CEDRIC", "SEVERINE",
                    "PEUGEOT 106", "1, RUE DE LA RUE", "STRASBOURG"};
    for (i = 0; i < 7; i++)
        adjEntite(r, tabe[i], PERSONNE);
    adjEntite(r, tabe[7], OBJET);
    adjEntite(r, tabe[8], ADRESSE);
    adjEntite(r, tabe[9], VILLE);

    // ajouter les relations de l'exemple
    adjRelation(r, tabe[0], tabe[1], FRERE);
    adjRelation(r, tabe[0], tabe[2], AMI);
    adjRelation(r, tabe[0], tabe[3], CONNAIT);
    adjRelation(r, tabe[0], tabe[5], COUSIN);
    adjRelation(r, tabe[0], tabe[7], PROPRIETAIRE);
    adjRelation(r, tabe[0], tabe[8], PROPRIETAIRE);
    adjRelation(r, tabe[3], tabe[4], VIT);
    adjRelation(r, tabe[5], tabe[6], EPOUX);
    adjRelation(r, tabe[5], tabe[8], LOCATAIRE);
    adjRelation(r, tabe[7], tabe[8], DECOUVERT);
    adjRelation(r, tabe[8], tabe[9], SITUE);

    // explorer les relations
    printf("%s est en relation avec:\n", tabe[0]);
    affichelg(en_relation(r, tabe[0]), afficheArc);
    printf("\n");

    for (i = 0; i < 7; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont les relations communes:\n", tabe[i], tabe[j]);
            affichelg(chemin2(r, tabe[i], tabe[j]), afficheEntite);
            printf("\n");
        }
    printf("\n\n");

    for (i = 0; i < 10; i++)
        for (j = i + 1; j < 10; j++)
        {
            printf("<%s> et <%s> ont lien de parente: %s\n",
                   tabe[i], tabe[j], ont_lien_parente(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
    printf("\n");
    for (i = 0; i < 7; i++)
    {
        for (j = i + 1; j < 7; j++)
        {
            printf("<%s> et <%s> se connaissent: %s\n",
                   tabe[i], tabe[j], se_connaissent(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent tres probablement: %s\n",
                   tabe[i], tabe[j], se_connaissent_proba(r, tabe[i], tabe[j]) ? "vrai" : "faux");
            printf("<%s> et <%s> se connaissent peut etre: %s\n",
                   tabe[i], tabe[j], se_connaissent_peutetre(r, tabe[i], tabe[j]) ? "vrai" : "faux");
        }
        printf("\n");
    }

    affiche_degre_relations(r, tabe[3]);

    relationFree(&r);

    printf("\nPRESS RETURN\n");
    char buff[64];
    fscanf(stdin, "%s", buff);
    return 0;
}
