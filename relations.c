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

char *toString(rtype id)
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

void checkMalloc(void *objet)
{
    if (objet == NULL)
    {
        fprintf(stderr, "Erreur : allocation echouée.\n");
        exit(EXIT_FAILURE);
    }
}

// 3.2 les constructeurs
Entite creerEntite(char *s, etype e)
{
    Entite newEntity = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc((Entite)newEntity);

    strncpy(newEntity->nom, s, LONG_NOM_MAX);
    newEntity->ident = e;

    return newEntity;
}

Sommet nouvSommet(Entite e)
{
    Sommet newSommet = (Sommet)malloc(sizeof(struct s_sommet));

    checkMalloc((Sommet)newSommet);

    newSommet->larcs = listegnouv();
    newSommet->x = e;

    return newSommet;
}

Arc nouvArc(Entite e, rtype type)
{
    Arc newArc = (Arc)malloc(sizeof(struct s_arc));

    checkMalloc((Arc)newArc);

    newArc->t = type;
    newArc->x = e;

    return newArc;
}

void relationInit(Relations *g)
{
    *g = (Relations)malloc(sizeof(struct s_relations));

    checkMalloc((Relations)*g);

    (*g)->liste = listegnouv();
}

void freeEntity(Entite entity)
{
    free(entity);
}

void freeArc(Arc arc)
{
    free(arc);
}

void freeLarcs(listeg larcs)
{
    if (estVide(larcs))
    {
        return;
    }

    //* On recupère le premier arc.
    Arc firstArc = (Arc)larcs->val;

    //* On supprime l'entite.
    freeEntity(firstArc->x);

    //* On supprime l'arc.
    free(firstArc);

    //* On supprime la tête de la liste des arcs.
    larcs = suptete(larcs);

    //* Et on refait le même traitement sur l'arc suivant.
    freeLarcs(larcs);
}

void freeListeNoeuds(listeg lg)
{
    if (estVide(lg))
    {
        return;
    }
    //* On recupère le 1er sommet.
    Sommet sommet = (Sommet)lg->val;

    //* On recupère la liste des arcs du 1er sommet.
    listeg larcs = sommet->larcs;

    //* On efface tous ces arcs.
    freeLarcs(larcs);

    //* On efface le 1er sommet.
    //* On efface l'entite du sommet avant.
    freeEntity(sommet->x);
    free(sommet);

    //* On efface la tête de la liste des noeuds.
    lg = suptete(lg);

    //* On refait le même traitement sur la tête suivante
    freeListeNoeuds(lg);
    //
}

void relationFree(Relations *g)
{
    Relations r = *g;

    if (r == NULL)
    {
        return;
    }

    listeg liste = r->liste;

    freeListeNoeuds(liste);

    return;
}

// 3.3 les comparaisons
int compEntite(void *e, void *string)
{
    Entite entity = (Entite)e;

    return strcmp(entity->nom, (char *)string);
}

int compSommet(void *s, void *string)
{
    Sommet som = (Sommet)s;

    return strcmp(som->x->nom, (char *)string);
}

int compArc(void *a, void *string)
{
    Arc arc = (Arc)a;

    return strcmp(arc->x->nom, (char *)string);
}

bool searchSommet(Relations g, char *nom)
{
    listeg currList = g->liste;

    //* Tanque la liste n'est pas vide et que les deux entités sont pas les mêmes
    //* on part au suivant.
    while (currList != NULL && compSommet((Sommet)currList->val, (char *)nom) != 0)
    {
        currList = currList->suiv;
    }

    if (currList == NULL)
    {
        //* on a pas trouvé l'entité.
        return false;
    }

    //* on l'a trouvé.
    return true;
}
// 3.4 ajout d'entites et de relations
void adjEntite(Relations g, char *nom, etype t)
{
    Entite entityToAdd = creerEntite(nom, t);
    Sommet sommetToAdd = nouvSommet(entityToAdd);

    if (estVide(g->liste))
    {
        g->liste = adjtete(g->liste, (Sommet)sommetToAdd);
    }
    else
    {
        //* On parcours g->liste et on cherche à savoir s'il y a déjà une entité
        //* du même nom
        //* si non, on l'ajoute.
        //* si oui, on l'ajoute pas.
        if (!searchSommet(g, nom))
        {
            //* On a pas trouvé l'entité, on l'ajoute.
            g->liste = adjqueue(g->liste, (Sommet)sommetToAdd);
        }
        //* Sinon on fait rien.
    }
}

void afficheEntites(Relations g)
{
    listeg curr = g->liste;
    int i = 0;
    while (curr != NULL)
    {
        printf("%d => %p\n", i, curr);
        Sommet som = (Sommet)curr->val;
        Entite entity = (Entite)som->x;
        printf("%s\n", entity->nom);
        curr = curr->suiv;
        i++;
    }
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

    // return 1;
    int i, j;
    Relations r;
    Relations *ptrR = &r;
    relationInit(ptrR);

    // ajouter les entites de l'exemple
    char *tabe[] = {"KARL", "LUDOVIC", "CELINE", "CHLOE", "GILDAS", "CEDRIC", "SEVERINE",
                    "PEUGEOT 106", "1, RUE DE LA RUE", "STRASBOURG"};
    //* On ajoute les personnes.
    for (i = 0; i < 7; i++)
        adjEntite(r, tabe[i], PERSONNE);

    //* On ajoute les objets.
    adjEntite(r, tabe[7], OBJET);
    adjEntite(r, tabe[8], ADRESSE);
    adjEntite(r, tabe[9], VILLE);
    adjEntite(r, tabe[9], VILLE);

    afficheEntites(r);
    return 0;
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
