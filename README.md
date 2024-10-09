Pentru a fi pozitionat perfect, jocul trebuie sa fie rulat pe un terminal
cu inaltimea de 45 si latimea de 177.
  Durata totala de implementare a fost de 12 zile, unele zile neavand
aproape deloc lucru, iar altele ajungand pana la 7-8 ore.
  In prima faza am folosit functia "initializare_tabla" pentru a seta
toate elementele jocului cu 0.
  Functia "numere_inceput" este apelata doar o data si are ca scop generarea
a doua numere random(2, 4) pe pozitii random. Prima data generez
o pozitie aleatoare, plasez elementul random pe acea pozitie, intrucat
tabla este goala. Mai apoi, mai generez inca o pozitie si verific ca acea
pozitie sa nu fie pozitia in care am generat primul numar. Asigurandu-ma
ca nu e pe aceeasi pozitie, ies din while si plasez 2 sau 4 pe acea pozitie.
  Functia "date" este una simplista, creez o variabila de tip time_t(t), apelez 
functia time pentru a modifica in adresa de memorie variabila t ce imi ofera
numarul de secunde de la 1 ianuarie 1970. Mai apoi, cu ajutorul structurii 
timp pot afisa ziua, luna, anul etc.
  Functia "numar_random" se apeleaza de fiecare data cand exista o mutare valida
si merge pe principiul descris la functia "numere_inceput", doar ca aici
generez pozitia si testez daca acea pozitie este libera, ca mai apoi sa adaug
elemntul generat tot random, 2 sau 4.
  Functiile "mutare_stanga", "mutare_dreapta", "mutare_jos", "mutare_sus"
functioneaza dupa acelasi principiu, asa ca voi descrie pe larg principiul
mutarii la stanga, fiind prima dintre toate.
  In primul rand, functia e de tip int pentru a imi intoarce daca este o miscare
valida sau invalida. La inceput, miscare_valida este 0, urmand a fi modificata
in caz de se muta orice element de pe orice linie, macar o data la stanga.
Pentru mutarea la stanga, pornesc cu un for ce va parcurge toate liniile
si pornesc de pe prima coloana. Daca elementul de pe prima coloana este 0,
nu pot sa mut nimic, asa ca ma voi muta la dreapta pana cand gasesc un element
diferit de 0, pentru a verifica daca il pot muta la stanga. 
  Daca am gasit un element nenul, il salvez intr-un auxiliar pentru a vedea
daca mutarea a produs imbinari sau doar a mutat elementul printre 0 uri. 
Verific daca in stanga elementului este ori 0, ori daca elementul respectiv este
egal cu cel din stanga. Daca una dintre cele doua se indeplineste, adaug la 
elementul din stanga, elementul meu, pozitia curenta o resetez la 0 si merg
pe coloana unde am adaugat elementul. Aici, verific din nou, daca in stanga este
un 0 sau acel element este egal cu elementul meu. Daca da, se repeta procedeul.
Cand ajunge la ultima imbinare posibila, j ul este pe o pozitie diferita de 0, asa
ca, dupa ce ies din while, trebuie sa l cresc pentru a fi pe o pozitie egala cu 0,
altfel, se va intra intr-o bucla infinita. 
Daca elementul rezultat ultima data nu este egal cu elementul de la care am 
pornit, cresc scorul, fiind rezultat al imbinarii.
  Functia "initializre_culori" creeaza toate culorile si perechile de culori
cu ajutorul RGB.
  Functia "afisare_tabela" este apelata de fiecare data cand exista
o modificare a tablei, fie a copiei(in caz de undo), fie a jocului propriu
zis. Creez un vectori de valori si unul de culori, ale caror elemente
au pe aceleasi pozitii numarul in concordanta cu a sa culoare. 
Pentru fiecare element din matrice, creez un WINDOW(casuta), pe
care o voi colora in functie de numarul de la pozitia respectiva.
Pentru a verifica ce numar este, verific pozitie cu pozitie numarul din
tabla cu numarul din vectorul "valori", iar cand gasesc pozitia, o retin, si 
colorez background-ul cu acea culoare de la aceeasi pozitie din vectorul
de culori(fiind corelate pozitiile din vectorul "valori" si din cel "culori").
  In functia "validare" se verifica dupa fiecare mutare daca exista castigator
sau pierzator. In prima faza, verific daca exista cel putin un zero, pentru ca
daca exista, inseamna ca sigur se mai poate realiza o mutare, deci nu mai trebuie
sa verific asta. Daca se gaseste un 2048, iese automat cu variabila castigator = 1.
Daca toate casutele sunt pline, trebuie sa verific daca e o miscare valida
(algoritm de la mutari). Daca gasesc cel putin o mutare jos, sus, stanga,
dreapta, ies din fiecare while pentru ca nu mai are rost sa continui,
se poate efectua cel putin o miscare. Daca nu se poate efectua nicio
miscare, returnez 1(joc incheiat).
  Meniul afiseaza pe ecran cele 3 optiuni, iar cu ajutorul sagetilor, se 
actualizeaza variabila highlight, care, in functie de numar, highlightuieste 
optiunea. Daca se apasa insa Resume de la inceput, neexistand un joc precedent, 
aceasta nu va fi executata.
  In functia "mutare_automata" se creeaza o masca a tablei de fiecare data
cand nu a fost apasata nicio tasta in cele 8 secunde. Dupa crearea mastii,
se va face pe aceasta fiecare mutare si se va incrementa un vector de frecventa
ce are 4 elemente:
0 - mutare stanga;
1 - mutare dreapta;
2 - mutare sus;
3 - mutare jos;
  La sfarsit, avand stocat in vector cate castue nenule sunt, se va returna
minimul, in speta, miscarea in care exista cele mai multe patrate libere.
In functia "interfata_jocnou" se afiseaza, in prima faza, tabla initializata
cu cele doua valori random, urmand, apasand tastele, sa fie facute mutarile
specifice. 
  Dupa fiecare mutare, verific daca se mai pot face miscari/exista 2048, iar
in acest afirmativ, salvez scorul, pentru a fi afisat in runda urmatoare.
Daca se apasa q, presupun ca se va da resume, deci salvez matricea intr-un
fisier pentru a o restabili in caz de resume.
  Functia "interfata_resume" este aceeasi cu cea prezentata mai sus, cu observatia
ca aici se va citi matricea din fisier, cea salvata mai devreme, cand s-a apasat
tasta Q. Aceasta functie nu poate fi accesata daca nu exista o matrice in fisier.
BONSURI: 
- culori diferite in functie de valoare(procedeu explicat mai sus)
- undo:
    Am retinut o copie a matricei inaintea fiecarei miscari si scorul aferent,
iar la apasarea tastei Z se transfera matricea copie in matricea curenta
si scorul copie in scorul veridic.
- clasament:
  In functia "username" se introduce de la tastatura un username,
pentru a fi pus in fisier alaturi de scorul care va iesi la final, dupa
infrangere/castig. La inceput, neexistand un scor, nu va aparea nimic in 
timpul jocului, dar mai apoi, dupa ce se va salva un jucator cu un scor
 in clasament, vor fi afisati pe ecran.
  Am retinut username ul si scorul intr-un fisier. In functia "clasament"
am creat un struct pe care l am sortat in mod descrescator si am ales
sa afisez primii 10, daca exista, iar daca nu exista 10, numarul lor
efectiv.

  