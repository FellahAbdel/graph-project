// relations.c�: d�finit le point d'entr�e pour l'application .
//

typedef int bool;
#define false 0
#define true -1

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"

/**
 * @enum rtype
 * Définit un type relationnel.
 */
typedef enum
{
    FRERE = 2,    ///<  Frere
    COUSIN,       ///<  Cousin
    PARENT,       ///<  Parent
    ONCLE,        ///<  Oncle
    EPOUX,        ///<  Epoux
    AMI,          ///<  Ami
    VIT,          ///<  Vit
    CONNAIT,      ///<  Connait
    CHEF,         ///<  Chef
    COLLEGUE,     ///<  Collegue
    LOCATAIRE,    ///<  Locataire
    TRAVAILLE,    ///<  Travaille
    PROPRIETAIRE, ///<  Proprietaire
    SITUE,        ///<  Situe
    DECOUVERT     ///<  Decouvert
} rtype;

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien de parenté sinon faux.
 */
bool est_lien_parente(rtype id)
{
    return id >= FRERE && id <= EPOUX;
}

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien professionel sinon faux.
 */
bool est_lien_professionel(rtype id)
{
    return id >= CHEF && id <= COLLEGUE;
}

/**
 * @param id : un type relationnel.
 * @return true si ce type est un lien de connaissance sinon faux.
 */
bool est_lien_connaissance(rtype id)
{
    return id >= AMI && id <= CONNAIT;
}

/**
 * @param id : un type relationnel.
 * @return la chaine de caractère associée au type relationnel id.
 */
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
/**
 * @struct s_node
 * @brief Cette structure permet de définir un noeud.
 */
typedef struct s_node
{
    void *val; // pointeur vers objet quelconque
    struct s_node *suiv;
} *listeg;

/**
 * @param Aucun.
 * @brief Création d'une nouvelle liste.
 * @return Un pointeur NULL.
 */
listeg listegnouv() { return NULL; }

/**
 * @param lst : Une liste.
 * @param x : Un pointeur générique.
 * @brief Adjonction d'un élément en tête dans la liste.
 * @return Une nouvelle liste.
 */
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

/**
 * @param lst : Une liste.
 * @param x : Un pointeur générique.
 * @brief Adjonction d'un élément en queue dans la liste.
 * @return Une nouvelle liste.
 */
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

/**
 * @param lst : Une liste.
 * @brief Suppression en tête.
 * @return Une nouvelle liste.
 */
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

/**
 * @param lst : Une liste.
 * @brief L'élement en tête de la liste.
 * @return Le pointeur générique en tête de la liste.
 */
void *tete(listeg lst)
{
    return lst != NULL ? lst->val : NULL;
}

/**
 * @param lst : Une liste.
 * @brief Est-ce que la liste est vide?
 * @return true si oui sinon false.
 */
bool estVide(listeg lst)
{
    return lst == NULL;
}

/**
 * @param lst : Une liste.
 * @brief La longueur de la liste.
 * @return Un entier representant la longeur.
 */
int longueur(listeg lst)
{
    return estVide(lst) ? 0 : 1 + longueur(lst->suiv);
}

/**
 * @param lst : Une liste.
 * @brief Destruction de la liste.
 * @return rien.
 */
void detruire(listeg lst)
{
    listeg temp = lst;
    while (temp != NULL)
    {
        temp = suptete(temp);
    }
}

/**
 * @param objet1 : Un pointeur générique.
 * @param objet2 : Un pointeur générique.
 * @brief Comparaison lexicographique des deux objets.
 * @return Un entier representant la longeur.
 */
int cmp(void *objet1, void *objet2)
{
    return strcmp((char *)objet1, (char *)objet2);
}

/**
 * @param lst : Une liste.
 * @param x : Un pointeur générique.
 * @param comp : Un pointeur de fonction.
 * @return Retourne une nouvelle liste avec pour tête le premier élément trouvé.
 */
listeg rech(listeg lst, void *x, int (*comp)(void *, void *))
{
    //* objectsFound : contiendra tous les noeuds trouvés.
    listeg objectsFound = NULL;

    while (!estVide(lst))
    {
        if (!comp(lst->val, x))
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

/**
 * @enum etype
 * Définit un type d'objet.
 */
typedef enum
{
    PERSONNE = 1, ///< Personne
    OBJET,        ///<  Objet
    ADRESSE,      ///< Adresse
    VILLE         ///<  Ville
} etype;

/**
 * @struct s_entite
 * @brief Cette structure permet de définir une entité.
 */
typedef struct s_entite
{
    char nom[LONG_NOM_MAX]; // le nom de l�entit� p.ex � Peugeot 106 �
    etype ident;            // l�identifiant associ�, p.ex OBJET
} *Entite;
// 3.1 les structures de donn�es

/**
 * @struct s_sommet
 * @brief Cette structure permet de définir un sommet.
 */
typedef struct s_sommet
{
    listeg larcs;
    Entite x;
} *Sommet;

/**
 * @struct s_node
 * @brief Cette structure permet de définir un arc.
 */
typedef struct s_arc
{
    rtype t;
    Entite x;
} *Arc;

/**
 * @struct s_relations
 * @brief Cette structure permet de définir l'ensemble des relations.
 */
typedef struct s_relations
{
    listeg liste;
} *Relations;

/**
 * @param objet : un pointeur génerique
 * @brief Vérifie juste si l'allocation a bien fonctionné.
 */
void checkMalloc(void *objet)
{
    if (objet == NULL)
    {
        fprintf(stderr, "Erreur : allocation echouée.\n");
        exit(EXIT_FAILURE);
    }
}

// 3.2 les constructeurs
/**
 * @param s chaîne de caractère;
 * @param e le type de l'objet.
 * @brief Construction d'une entité.
 * @return une entité.
 */
Entite creerEntite(char *s, etype e)
{
    Entite newEntity = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc((Entite)newEntity);

    strncpy(newEntity->nom, s, LONG_NOM_MAX);
    newEntity->ident = e;

    return newEntity;
}

/**
 * @param e Une entité
 * @brief Construction d'un sommet.
 * @return Un sommet.
 */
Sommet nouvSommet(Entite e)
{
    Sommet newSommet = (Sommet)malloc(sizeof(struct s_sommet));

    checkMalloc((Sommet)newSommet);

    newSommet->x = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc(newSommet->x);

    newSommet->larcs = listegnouv();

    memcpy(newSommet->x, e, sizeof(struct s_entite));

    return newSommet;
}

/**
 * @param e Une entité.
 * @param type le type de la relation.
 * @brief Construction d'un arc.
 * @return Un arc.
 */
Arc nouvArc(Entite e, rtype type)
{
    Arc newArc = (Arc)malloc(sizeof(struct s_arc));

    checkMalloc((Arc)newArc);

    newArc->x = (Entite)malloc(sizeof(struct s_entite));

    checkMalloc(newArc->x);

    newArc->t = type;
    memcpy(newArc->x, e, sizeof(struct s_entite));

    return newArc;
}

/**
 * @param g Pointeur de pointeur vers la relation
 * @brief Initialisation du graphe.
 * @return Rien.
 */
void relationInit(Relations *g)
{
    *g = (Relations)malloc(sizeof(struct s_relations));

    checkMalloc((Relations)*g);

    (*g)->liste = listegnouv();
}

/**
 * @param ptrListeOfArcs Un pointeur vers la liste des arcs;
 * @brief Nettoyage d'une liste d'arcs.
 * @return rien.
 */
void freeLarcs(listeg *ptrlisteOfArcs)
{
    if (estVide(*ptrlisteOfArcs))
    {
        return;
    }
    //* Destruction : mais avant on a bésoin de supprimer l'entité
    //* Dans l'arc, c'est pourquoi on ne peut pas utiliser la fonction
    //* detruire() ici.
    while ((*ptrlisteOfArcs) != NULL)
    {
        //* On nettoie l'entite dans l'arc.
        free(((Arc)(*ptrlisteOfArcs)->val)->x);

        //* On nettoie l'arc lui-même.
        free((Arc)(*ptrlisteOfArcs)->val);

        //* Après on supprime la tête courrante.
        (*ptrlisteOfArcs) = suptete(*ptrlisteOfArcs);
    }
}

/**
 * @param ptrSommet Un pointeur vers le sommet à supprimer;
 * @brief Supression d'un sommet.
 * @return rien.
 */
void freeSommet(Sommet *ptrSommet)
{
    if (*ptrSommet == NULL)
    {
        return;
    }

    //* On efface l'entite dans le sommet.
    free((*ptrSommet)->x);

    //* On efface le sommet lui-même.
    free(*ptrSommet);
}

/**
 * @param g Un pointeur vers le graphe;
 * @brief Suppression de tout le graphe.
 * @return rien.
 */
void relationFree(Relations *g)
{
    if (*g == NULL)
    {
        return;
    }

    // listeg curr = (*g)->liste;
    while ((*g)->liste != NULL)
    {
        //* On recupère le sommet courrant.
        Sommet som = ((Sommet)((*g)->liste)->val);
        // listeg listeConnaissance = som->larcs;

        //* On efface la liste des rélations.
        freeLarcs(&((Sommet)((*g)->liste)->val)->larcs);

        //* On efface le sommet.
        freeSommet((Sommet *)&((*g)->liste->val));

        // freeSommet(&((Sommet)((*g)->liste)->val));

        //* On efface la tête.
        (*g)->liste = suptete((*g)->liste);
    }

    free(*g);
    *g = NULL;
    return;
}

// 3.3 les comparaisons
/**
 * @param e Un pointeur générique vers un objet;
 * @param string Un pointeur générique vers une chaine;
 * @brief Comparaison d'entité.
 * @return booleen.
 */
int compEntite(void *e, void *string)
{
    Entite entity = (Entite)e;

    return strcmp(entity->nom, (char *)string);
}

/**
 * @param s Un pointeur générique vers un sommet;
 * @param string Un pointeur générique vers une chaine;
 * @brief Comparaison de sommet.
 * @return booleen.
 */
int compSommet(void *s, void *string)
{
    Sommet som = (Sommet)s;

    return strcmp(som->x->nom, (char *)string);
}

/**
 * @param a Un pointeur générique vers un arc;
 * @param string Un pointeur générique vers une chaine;
 * @brief Comparaison d'arc.
 * @return booleen.
 */
int compArc(void *a, void *string)
{
    Arc arc = (Arc)a;

    return strcmp(arc->x->nom, (char *)string);
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
        //* le nom est unique. (Pas de doublons).
        //* On parcours g->liste et on cherche à savoir s'il y a déjà une entité
        //* du même nom
        //* si non, on l'ajoute.
        //* si oui, on l'ajoute pas.
        if (rech(g->liste, (char *)nom, compSommet) == NULL)
        {
            g->liste = adjqueue(g->liste, (Sommet)sommetToAdd);
        }
        //* Sinon on fait rien.
    }

    //* ça été copié, nous en avons plus bésoin.
    free(entityToAdd);
}

/**
 * @param listeArcs  liste des arcs du sommet.
 * @param nom clé.
 * @return NULL ou l'arc trouvé.
 */
listeg searchArc(listeg listeArcs, char *nom)
{
    while (listeArcs != NULL && compArc(listeArcs->val, nom) != 0)
    {
        listeArcs = listeArcs->suiv;
    }

    return listeArcs;
}

/**
 *    @brief Adjonction des relations.
 *    @param g le graphe
 *    @param nom1 clé 1
 *    @param nom2 clé 2
 *    @param id type rélationnel.
 *    @pre id doit être cohérent avec les types des sommets correspondants à nom1 et nom2, par exemple si nom1 est de type OBJET, id ne peut pas être une relation de parenté.
 *    @pre nom1 et nom2 doivent être des clés distinctes.
 */
void adjRelation(Relations g, char *nom1, char *nom2, rtype id)
{
    //* Les sommets sont déjà ajoutés, ici on ajoute juste les arcs (relations).
    //* On cherche le sommet portant le nom : nom1
    listeg curr = g->liste;
    Sommet s1 = NULL;
    while (curr != NULL && s1 == NULL)
    {
        Sommet som = (Sommet)curr->val;
        if (compSommet(som, nom1) == 0)
        {
            s1 = som;
        }
        curr = curr->suiv;
    }

    //* On cherche le sommet 2 portant le nom : nom2
    curr = g->liste;
    Sommet s2 = NULL;
    while (curr != NULL && s2 == NULL)
    {
        Sommet som = (Sommet)curr->val;
        if (compSommet(som, nom2) == 0)
        {
            s2 = som;
        }
        curr = curr->suiv;
    }

    listeg nodeArc1 = searchArc(s1->larcs, nom2);
    if (nodeArc1 != NULL)
    {
        //* L'arc existe déjà, on met à jour l'id.
        Arc arcFound = (Arc)nodeArc1->val;
        arcFound->t = id;
    }
    else
    {
        //* Ajout du premier arc de nom1 à nom2
        Arc newArc = nouvArc(s2->x, id);
        s1->larcs = adjtete(s1->larcs, (Arc)newArc);
    }

    listeg nodeArc2 = searchArc(s2->larcs, nom1);
    if (nodeArc2 != NULL)
    {
        //* L'arc existe déjà, on met à jour l'id.
        Arc arcFound = (Arc)nodeArc2->val;
        arcFound->t = id;
    }
    else
    {
        //* Ajout du second arc de nom2 à nom1
        Arc newArc = nouvArc(s1->x, id);
        s2->larcs = adjtete(s2->larcs, (Arc)newArc);
    }

    return;
}

////////////////////////////////////////
// Exercice 4: Explorer les relations entre personnes

// 4.1 listes de relations
/**
    @brief Renvoie la liste des arcs adjacents au sommet de nom x dans le graphe g.
    @param g Le graphe.
    @param x Le nom du sommet dont on cherche les arcs adjacents.
    @return La liste des arcs adjacents au sommet de nom x, ou NULL si le sommet n'existe pas dans le graphe.
    Cette fonction parcourt la liste de sommets du graphe g pour trouver le sommet de nom x. Si le sommet est trouvé,
    la fonction retourne la liste des arcs adjacents à ce sommet. Si le sommet n'existe pas dans le graphe, la fonction
    retourne NULL.
    La liste retournée doit être détruite après utilisation en appelant la fonction detruire(listeg liste).
    */
listeg en_relation(Relations g, char *x)
{
    listeg listSommet = g->liste;
    listeg listeOfArcs = NULL;

    listeg sommetFound = rech(listSommet, (char *)x, compSommet);

    if (sommetFound != NULL)
    {
        //* Le sommet de nom x a été trouvé.
        Sommet som = (Sommet)sommetFound->val;
        listeOfArcs = som->larcs;

        //* On n'oublie pas de detruire la liste.
        detruire(sommetFound);
    }

    return listeOfArcs;
}

/**
    @param g le graphe
    @param x nom du premier sommet
    @param y nom du deuxième sommet
    @return une liste de sommets qui constitue un chemin entre x et y, ou NULL si x et y ne sont pas reliés dans le graphe.
    La fonction cherche un chemin entre deux sommets x et y dans le graphe en utilisant la méthode de recherche en largeur.
    Elle retourne une liste de sommets qui constitue un chemin entre x et y si un chemin est trouvé, ou NULL sinon.
    Cette fonction utilise la fonction en_relation pour récupérer la liste des arcs sortants de chaque sommet, puis elle cherche si l'un des arcs sortants du premier sommet est connecté à l'un des arcs entrants du deuxième sommet.
    */
listeg chemin2(Relations g, char *x, char *y)
{
    listeg listOfArcsX = en_relation(g, x);
    listeg listOfArcsY = en_relation(g, y);
    listeg cheminList = listegnouv();

    //* On parcourt listOfArcsX
    while (listOfArcsX != NULL)
    {
        //* On recupère le premier arc.
        Arc currArcX = (Arc)listOfArcsX->val;

        //* On recupère l'entité.
        Entite entity = currArcX->x;

        listeg arcFound = searchArc(listOfArcsY, entity->nom);

        if (arcFound != NULL)
        {
            Arc arc = (Arc)arcFound->val;
            cheminList = adjtete(cheminList, (Entite)arc->x);
            // printf("found : %s\n", arc->x->nom);
        }

        listOfArcsX = listOfArcsX->suiv;
    }
    return cheminList;
}

// 4.2 verifier un lien de parente
/**
    @brief Vérifie si deux entités ont un lien de parenté direct.
    @param g Le graphe contenant les entités.
    @param x Le nom de la première entité.
    @param y Le nom de la deuxième entité.
    @return true si une relation de parenté existe entre x et y, false sinon.
    @pre g doit être initialisé et non NULL.
    @pre x et y doivent correspondre à des noms d'entités existantes dans g.
*/
bool ont_lien_parente(Relations g, char *x, char *y)
{
    listeg listOfArcs = en_relation(g, x);
    bool isFamily = false;
    listeg arcNodeFound = searchArc(listOfArcs, y);

    if (arcNodeFound != NULL)
    {
        Arc arc = (Arc)arcNodeFound->val;
        isFamily = est_lien_parente(arc->t);
    }

    return isFamily;
}
// 4.3 tester connaissances

/**
    @param g le graphe
    @param x le nom du premier sommet
    @param y le nom du deuxième sommet
    @pre Les sommets correspondants à x et y sont de type PERSONNE.
    @pre x et y sont différents.
    @return true si x et y ont une relation de parenté, de connaissance ou professionnelle,
    ou s'ils ont un chemin commun passant par un sommet de relation de parenté avec x et y.
    Sinon, retourne false.
*/
bool se_connaissent(Relations g, char *x, char *y)
{
    //* On recupère la liste des rélations de x.
    listeg listOfArcsX = en_relation(g, x);
    bool isRelationship = false;

    listeg arcNodeFound = searchArc(listOfArcsX, y);

    if (arcNodeFound != NULL)
    {
        //* On l'a trouvé parmis ses voisins.
        Arc arc = (Arc)arcNodeFound->val;
        rtype type = arc->t;
        bool estParenteOk = est_lien_parente(type);
        bool estConaissanceOk = est_lien_connaissance(type);
        bool estProfessionelOk = est_lien_professionel(type);
        isRelationship = estParenteOk || estConaissanceOk || estProfessionelOk;
    }
    else
    {
        //* Sinon, on regarde parmis les voisins communs.
        listeg commonNeighbours = chemin2(g, x, y);
        listeg temp = commonNeighbours;
        while (temp != NULL)
        {
            Entite entity = (Entite)temp->val;
            char *z = entity->nom;
            if (ont_lien_parente(g, x, z) && ont_lien_parente(g, z, y))
            {
                isRelationship = true;
            }
            temp = temp->suiv;
        }
        detruire(commonNeighbours);
    }

    return isRelationship;
}

/**
 *  @brief Vérifie si une relation directe existe entre deux sommets d'un graphe de relations.
 *  @param g le graphe de relations
 *  @param x le nom du premier sommet
 *  @param y le nom du deuxième sommet
 *  @return true si une relation directe existe entre x et y, false sinon.
 *  @pre Les sommets correspondants à x et y doivent appartenir au graphe et être de type Entite.
 *  @pre strcmp(x,y) != 0
 *  @post Retourne true si une relation directe existe entre x et y, false sinon.
 */
bool _isRelationDirecte(Relations g, char *x, char *y)
{
    listeg listOfArcsX = en_relation(g, x);
    bool isDirectRelationship = false;

    listeg arcNodeFound = searchArc(listOfArcsX, y);

    if (arcNodeFound != NULL)
    {
        //* On l'a trouvé parmis ses voisins. Donc  c'est une relation directe.
        isDirectRelationship = true;
    }

    return isDirectRelationship;
}
/**
 * @brief Détermine si deux personnes se connaissent probablement, c'est-à-dire s'il existe une relation entre eux de manière indirecte via un autre contact en commun.
 * @param g Le graphe contenant les relations.
 * @param x Le nom de la première personne.
 * @param y Le nom de la deuxième personne.
 * @return true s'il est probable que x et y se connaissent, false sinon.
 * @pre Les sommets correspondants à x et y sont de type PERSONNE.
 * @pre strcmp(x,y)!=0
 */
bool se_connaissent_proba(Relations g, char *x, char *y)
{
    bool probablyRelation = false;
    if (_isRelationDirecte(g, x, y))
    {
        probablyRelation = false;
    }
    else
    {
        listeg commonNeighbours = chemin2(g, x, y);
        listeg temp = commonNeighbours;
        while (temp != NULL)
        {
            Entite entity = (Entite)temp->val;
            char *z = entity->nom;
            if ((ont_lien_parente(g, x, z) && !ont_lien_parente(g, y, z)) || (!ont_lien_parente(g, x, z) && ont_lien_parente(g, y, z)))
            {
                probablyRelation = true;
            }
            temp = temp->suiv;
        }
        detruire(commonNeighbours);
    }

    return probablyRelation;
}

/**
 *  @brief Vérifie si deux personnes peuvent se connaître potentiellement, c'est-à-dire
 *  s'il existe une chaîne de relations entre elles, ou si elles ont des voisins
 *  en commun qui ne sont pas liés par un lien de parenté.
 *  @param g le graphe de relations
 *  @param x le nom de la première personne
 *  @param y le nom de la deuxième personne
 *  @return vrai si les deux personnes peuvent se connaître potentiellement, faux sinon
 *  @pre les sommets correspondants à x et y sont de type PERSONNE
 *  @pre strcmp(x, y) != 0
 */
bool se_connaissent_peutetre(Relations g, char *x, char *y)
{
    if (_isRelationDirecte(g, x, y))
    {
        return false;
    }
    else if (se_connaissent_proba(g, x, y))
    {
        return false;
    }
    else
    {
        listeg commonNeighbours = chemin2(g, x, y);
        if (commonNeighbours != NULL)
        {
            detruire(commonNeighbours);
            return true;
        }
        else
        {
            return false;
        }
    }
}
////////////////////////////////////////
// Exercice 5: Affichages
/**
 *  @brief Affiche une chaîne de caractères passée en paramètre.
 *  @param objet Un pointeur void qui pointe vers la chaîne de caractères à afficher.
 *  @return void.
 */
void affiche(void *objet)
{
    //* Dans notre cas, on affiche une chaine
    printf("%s\n", (char *)objet);

    return;
}

/**
 *  @brief Affiche chaque élément de la liste chaînée.
 *  @param l La liste chaînée à afficher.
 *  @param aff Un pointeur vers une fonction qui prend un pointeur void en entrée et ne renvoie rien. Cette fonction sera appelée pour chaque élément de la liste pour afficher son contenu.
 *  @note La fonction affichera chaque élément de la liste en appelant la fonction aff passée en paramètre.
 */
void affichelg(listeg l, void (*aff)(void *))
{
    while (!estVide(l))
    {
        aff(l->val);
        l = l->suiv;
    }
}

/**
 *  @brief Affiche une entité.
 *  @param x Un pointeur vers l'entité à afficher.
 */
void afficheEntite(void *x)
{
    Entite entity = (Entite)x;
    printf("%s : ", entity->nom);
    switch (entity->ident)
    {
    case PERSONNE:
        printf("PERSONNE");
        break;
    case OBJET:
        printf("OBJET");
        break;
    case ADRESSE:
        printf("ADRESSE");
        break;
    case VILLE:
        printf("VILLE");
        break;
    default:
        printf("Type d'entité inconnu");
    }
    printf("\n");
}

/**
 *  @brief Affiche un arc avec sa transition et son entité associée.
 *  @param x Un pointeur vers l'arc à afficher.
 */
void afficheArc(void *x)
{
    Arc arc = (Arc)x;
    printf("-- %s -->", toString(arc->t));
    void *entity = arc->x;
    afficheEntite(entity);
}

////////////////////////////////////////
// Exercice 6: Parcours
/**
 *  @brief Affiche les entités qui ont un certain degré de relation avec une entité donnée.
 *  @param r Le graphe de relations.
 *  @param x Le nom de l'entité dont on veut afficher les relations.
 *  @return void
 *  Cette fonction parcourt le graphe de relations à partir de l'entité donnée et affiche toutes les entités qui ont un lien
 *  de relation avec elle à un certain degré. Le degré de relation est déterminé par la distance à l'entité d'origine dans le graphe.
 *  Les entités sont affichées par degré, de façon à regrouper celles qui ont la même distance à l'entité d'origine.
 */
void affiche_degre_relations(Relations r, char *x)
{
    listeg visitedList = listegnouv();
    listeg queueNext = listegnouv();
    listeg queueSecondNext = listegnouv();
    listeg relations = en_relation(r, x);
    listeg sommetX = rech(r->liste, x, compSommet);
    visitedList = adjtete(visitedList, ((Sommet)sommetX->val)->x);
    detruire(sommetX);
    for (; !estVide(relations); relations = relations->suiv)
    {
        queueNext = adjqueue(queueNext, ((Arc)relations->val)->x);
    }
    printf("%s\n", x);
    int degre = 1;
    while (!estVide(queueNext))
    {
        printf("-- %d\n", degre++);
        listeg queueNextTemp = queueNext;
        for (; !estVide(queueNextTemp); queueNextTemp = queueNextTemp->suiv)
        {
            printf("%s\n", ((Entite)queueNextTemp->val)->nom);
        }
        while (!estVide(queueNext))
        {
            char *next = ((Entite)tete(queueNext))->nom;
            queueNext = suptete(queueNext);
            listeg relations = en_relation(r, next);
            for (; !estVide(relations); relations = relations->suiv)
            {
                listeg visitedComparison = rech(visitedList, ((Arc)relations->val)->x->nom, compEntite);
                listeg queueComparison = rech(queueNext, ((Arc)relations->val)->x->nom, compEntite);
                listeg queueSecondComparison = rech(queueSecondNext, ((Arc)relations->val)->x->nom, compEntite);
                if (estVide(visitedComparison) && estVide(queueComparison) && estVide(queueSecondComparison))
                {
                    listeg sommetFils = rech(r->liste, ((Arc)relations->val)->x->nom, compSommet);
                    queueSecondNext = adjqueue(queueSecondNext, ((Sommet)sommetFils->val)->x);
                    detruire(sommetFils);
                }
                detruire(visitedComparison);
                detruire(queueComparison);
            }
            listeg nextSom = rech(r->liste, next, compSommet);
            visitedList = adjtete(visitedList, ((Sommet)nextSom->val)->x);
            detruire(nextSom);
        }

        queueNext = queueSecondNext;
        queueSecondNext = listegnouv();
    }
    detruire(visitedList);
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
            listeg ch = chemin2(r, tabe[i], tabe[j]);
            affichelg(ch, afficheEntite);
            printf("\n");
            detruire(ch);
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
