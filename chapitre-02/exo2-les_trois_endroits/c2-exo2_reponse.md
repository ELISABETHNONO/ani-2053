## RESULTATS DES 3 SORTIES ET EXPLICATIONS DES CHANGEMENTS

1. la modification a été de mettre le bout de code suivant qui etait dans le fichier 1 et de le mettre dans le fichier 2 :
  
    #include <iostream>
    using namespace std;

    int main (){
        int n=5;
        
    }

2. Après la modification j'ai fait et **git status** et voici le résultat: 


    On branch main
    Your branch is based on 'origin/main', but the upstream is gone.
        (use "git branch --unset-upstream" to fixup)

    Changes not staged for commit:
        (use "git add <file>..." to update what will be committed)
        (use "git restore <file>..." to discard changes in working directory)
            modified:   fichier1
            modified:   fichier2

    no changes added to commit (use "git add" and/or "git commit -a")



3. Puis dans le terminal j'ai tapé cette commande : **git add .** 
le résultat fut:**rien, aucun message,aucun lettre**

4. J'ai encore tapé **git status** et voici le résultat : 

        On branch main

        Your branch is based on 'origin/main', but the upstream is gone.
        (use "git branch --unset-upstream" to fixup)

        Changes to be committed:
            (use "git restore --staged <file>..." to unstage)
                modified:   fichier1
                modified:   fichier2



5. Ensuite,j'ai tapé la commande suivante: **git commit -m "les trois endroits" -m "savoir appliquer les 3 commandes"** et le résultat fut : 

        [main ad0dc5b] les trois endroits
        2 files changed, 6 insertions(+), 6 deletions(-)  

6. et por cloturer j'ai tapé **git status** et voici le résultat : 
 
        On branch main
        Your branch is based on 'origin/main', but the upstream is gone.
            (use "git branch --unset-upstream" to fixup)

        nothing to commit, working tree clean

    ## EXPLICATION
    **Ce qui change dans les 3 sorties de git status et l'état du projet. Au début (la premiere commande) le résultat nous dit clairement que 2 fichiers ont été touché mais pas ajouté et nous donne les commande à taper. Aprés le git add, le résultat du git status nous montre que les 2 fichiers qui doivent etre soumis. Après le commit qui nous dit que 2 fichiers ont été changé, 6 lignes insérées et 6 lignes rétirées; le resultat du git status nous dit que les modifications ont été ajoutées à la branche main**
    