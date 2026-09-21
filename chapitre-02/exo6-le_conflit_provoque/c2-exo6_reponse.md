## PROVOQUER UN CONFLIT 

la ligne 5 de ;on fichier 2 a ete retire dans les deux endroits. apres un git add . et un git commit -m "git essai" dans les deux endroits au moment de push au 2e endroit j'ai eu ceci dqns le terminal : 

**To https://github.com/ELISABETHNONO/INGNE.git
 ! [rejected]        lisybranch -> lisybranch (non-fast-forward)
error: failed to push some refs to 'https://github.com/ELISABETHNONO/INGNE.git'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. If you want to integrate the remote changes,
hint: use 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.**

et ceci dans l'editeur :
    #include <iostream>
    using namespace std;

        int main (){
<<<<<<< HEAD
         
=======
        
>>>>>>> e6c4aff438642207ff48159060f549990df9cee2
        
    }

pour resoudre le conflit, nous avons fait

. un **git pull**

.ouvert l'editeur de fusion 

. choisi la version du seveur 

. choisi accepter entrant

. un git commit -m "je viens de resoudre le conflit"

        On branch lisybranch
    Your branch is ahead of 'origin/lisybranch' by 2 commits.
    (use "git push" to publish your local commits)


. un git push qui a donné 

    Enumerating objects: 8, done.
    Counting objects: 100% (8/8), done.
    Delta compression using up to 8 threads
    Compressing objects: 100% (4/4), done.
    Writing objects: 100% (4/4), 616 bytes | 102.00 KiB/s, done.
    Total 4 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
    To https://github.com/ELISABETHNONO/INGNE.git
    e6c4aff..2a4a8ed  lisybranch -> lisybranch


