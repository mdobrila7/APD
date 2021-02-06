Dobrila Madalin 334CA Tema2

	Task1 - destul de simplu, doar doua printuri, unul care imi spune ca
toate o masina a ajuns la semafor, apoi dupa ce asteapta un timp egal cu WaitingTime,
poate trece mai departe. 

	Task2 - aici am facut un semafor ce permite sa treaca numai simple_n masini 
la un moment de timp, unde simple_n este primul argument de pe ultima linie a fisierului
de intrare. Apoi, dupa ce o masina intra in sensul giratoriu, va sta acolo timp de 
simple_t/1000 secunde dupa care va iesi, unde simple_t este cel de-al doilea argument de
pe ultima linie a fisierului de intrare, primit in milisecunde.

	Task3 - ideea este asemanatoare cu cea de la task2, cu unica diferenta ca aici
semaforul permite sa intre o singura masina de pe fiecare cele simple_strict_1_car_nrLanes lane uri.

	Task4 - la acest task am inceput prin a face un arraylist de semafoare, practic un
semafor pentru fiecare lane pentru a putea permite sa intre in giratoriu numarul de masini
cerut de al treilea argument de pe ultima linie a fisierului de intrare, simple_strict_max_x_car_n la mine.
Apoi, am inceput sa pun bariere pentru a ma asigura ca numarul de masini cerute se sincornizeaza.
Mai intai o bariera barrier1 pentru a ma asigura ca toate masinile ajung la giratoriu. 
Apoi o bariera barrier2 folosita de mai multe ori pentru a sincroniza numarul permis de masini
pentru a trece la un moment dat de pe fiecare cele nrLanes (nr_lanes * nr_cars_passing_at_once).
