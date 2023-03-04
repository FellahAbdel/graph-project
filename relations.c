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

char *toStringRelation(rtype id) { return ""; }

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
    return lst;
}
listeg adjqueue(listeg lst, void *x)
{
    return lst;
}
listeg suptete(listeg lst)
{
    return lst;
}

void *tete(listeg lst)
{
    return NULL;
}
int longueur(listeg lst)
{
    return -1;
}
bool estvide(listeg lst)
{
    return false;
}
void detruire(listeg lst)
{
}
listeg rech(listeg lst, void *x, int (*comp)(void *, void *))
{
    return NULL;
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
} *Sommet;

typedef struct s_arc
{
    // A DEFINIR
} *Arc;

typedef struct s_relations
{
    // A DEFINIR
} *Relations;

// 3.2 les constructeurs
Entite creerEntite(char *s, etype e)
{
    return NULL;
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

void affichelg(listeg l, void (*aff)(void *))
{
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
