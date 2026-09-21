## CREATION D'UNE BRANCHE ET CALCUL DE L'ESPACE RESTANT DU DISQUE


POUR Savoir l'espace initial du depot j4ai fait un **du -sh .git**
 et voici le resultat:
        
        127K    .git

pour creer la branche j'ai fait un **git checkout -b lisybranch**
et voici le resultat :
        
        Switched to a new branch 'lisybranch'

 
j'ai tape **ls** pour voir le nombre de fichiers de la branche et voicinle resultat : 

        fichier1  fichier2  fichier3
 
  ## LES 3 COMMITS


 
Un  git status pour voir l'etat des lieux  :

        On branch lisybranch
        Changes not staged for commit:
                (use "git add <file>..." to update what will be committed)
                (use "git restore <file>..." to discard changes in working directory)
                        modified:   fichier1
                        modified:   fichier2
                        modified:   fichier3

        no changes added to commit (use "git add" and/or "git commit -a")
  **LES 3 COMMITS**

**1er commit**

 Commande: git add fichier1

 commande commit :**git commit -m "modification1"**
 resultat : 
        
        [lisybranch 343b0c0] modification1
         1 file changed, 1 insertion(+), 104 deletions(-)

 **2e commit**
 commande: git add fichier2

 commande commit :**git commit -m "modification2"**
 resultat : 

        [lisybranch e5fc7d7] modification2
        1 file changed, 3 insertions(+), 1 deletion(-)

 **3e commit**
 commande:  git add fichier3

 commande commit: **git commit -m "modification3"**

resultat: 

        [lisybranch 881f502] modification3
                1 file changed, 2 insertions(+)

 
 
 
 pour voir l'etat de la branche j'ai fait un  **git status** et voici le resultat:

        On branch lisybranch
        nothing to commit, working tree clean

pour voir la capacite le disque apres le depot 

 j'ai fait un **du -sh .git**
 voici le resultat :
        
        144K    .git

**le depot a gagne 17k**
