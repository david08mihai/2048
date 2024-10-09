#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

void interfata_joc();
void interfata_jocnou();
void interfata_meniu();
void clasament();
void username();

void initializare_tabla(int tabla[][4]){
    int i, j;
    for (i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            tabla[i][j] = 0;
        }
    }
}


void numere_inceput(int tabla[][4]){
    srand(time(NULL));
    int i, j;
    i = rand() % 4;
    j = rand() % 4;
    tabla[i][j] = (rand() % 2 + 1) * 2;
    // tabla este libera, asa ca prima casuta generata
    // cu siguranta va fi libera
    i = rand() % 4;
    j = rand() % 4;
    // generez alta pozitie
    while (tabla[i][j] != 0){
        i = rand() % 4;
        j = rand() % 4;
    }
    // verific daca este libera (sa nu fie ocupata
    // de primul numar generat)
    tabla[i][j] = (rand() % 2 + 1) * 2;

}

void date(){
    time_t t;
    struct tm *current_time;
    time(&t);
    current_time = localtime(&t);
    attron(A_BOLD | A_BLINK);
    mvprintw(11, 150, "Date: %02d.%02d.%d", current_time->tm_mday, current_time->tm_mon + 1, current_time-> tm_year + 1900);
    mvprintw(12, 150, "Time: %02d:%02d", current_time->tm_hour, current_time->tm_min);
    attroff(A_BOLD | A_BLINK);
}

void numar_random(int tabla[][4]){
    srand(time(NULL));
    int i, j, full = 1;
    for (i = 0; i < 4; ++i){
        for (j = 0; j < 4; ++i) {
            if (tabla[i][j] == 0) {
                full = 0;
                break;
            }
        }
    }
    // verific daca tabla este plina pentru
    // a nu fi nevoit sa generez in caz de tabla este full
    i = rand() % 4;
    j = rand() % 4;
    while (tabla[i][j] && !full){
        i = rand() % 4;
        j = rand() % 4;
    }
    tabla[i][j] = (rand() % 2 + 1) * 2;
}  



int mutare_stanga(int tabla[][4], int *scor){
    int i, j, miscare_valida = 0, aux;
    for (i = 0; i < 4; i++) {
        j = 1;
        while (j < 4) {
            while (tabla[i][j] == 0 && j < 4){
                j++;
            }
            aux = tabla[i][j];
            while (j > 0 && j < 4 && ((tabla[i][j-1] == 0) || tabla[i][j-1] == tabla[i][j])) {
                tabla[i][j-1] += tabla[i][j];
                tabla[i][j] = 0;
                j--;
                miscare_valida = 1;
            }
            if (aux != tabla[i][j]){
                *scor += tabla[i][j];
            }
            j++;
        }
    }
    if (miscare_valida) {
        return 1;
    } else {
        return 0;
    }
}

int mutare_dreapta(int tabla[][4], int *scor){
    int i, j, miscare_valida = 0, aux;
    for(i = 0; i < 4; ++i){
        j = 2;
        while (j > -1){
            while (tabla[i][j] == 0 && j > -1) {
                j--;
            }
            aux = tabla[i][j];
            while (j > -1 && j < 3 && (tabla[i][j+1] == 0 || tabla[i][j] == tabla[i][j+1])) {
                tabla[i][j+1] += tabla[i][j];
                tabla[i][j] = 0;
                j++;
                miscare_valida = 1;
            }
            if (aux != tabla[i][j]) {
                *scor += tabla[i][j];
            }
            j--;
        }
    }
    if (miscare_valida) {
        return 1;
    } else {
        return 0;
    }
}

int mutare_sus(int tabla[][4], int *scor){
    int i, j, aux, miscare_valida = 0;
    for (j = 0; j < 4; ++j) {
        i = 1;
        while (i < 4) {
            while (tabla[i][j] == 0 && i < 4) {
                ++i;
            }
            aux = tabla[i][j];
            while (i > 0 && i < 4 && (tabla[i-1][j] == 0 || tabla[i][j] == tabla[i-1][j])) {
                tabla[i-1][j] += tabla[i][j];
                tabla[i][j] = 0;
                i--;
                miscare_valida = 1;
             }
            if (aux != tabla[i][j]) {
                *scor += tabla[i][j];
            }
            ++i;
        }
   }
    if (miscare_valida) {
        return 1;
    } else {
        return 0;
    }
}

int mutare_jos(int tabla[][4], int *scor){
    int i, j, miscare_valida = 0, aux;
    for (j = 0; j < 4; ++j) {
        i = 2;
        while (i > -1) {
            while (tabla[i][j] == 0 && i > -1) {
                i--;
            }
            aux = tabla[i][j];
            while (i > -1 && i < 3 && (tabla[i+1][j] == 0 || tabla[i+1][j] == tabla[i][j])) {
                tabla[i+1][j] += tabla[i][j];
                tabla[i][j] = 0;
                i++;
                miscare_valida = 1;
            }
            if (aux != tabla[i][j]) {
                *scor += tabla[i][j];
            }
            i--;
        }
    }
    if (miscare_valida) {
        return 1;
    } else {
        return 0;
    }
}


void color_initializare_tabla(){
 
    init_color(11, 22, 166, 238); // albastru inchis
    init_color(12, 178, 0, 154); // albastru deschis/
    init_color(13, 255, 153, 255 ); // mov
    init_color(14, 222, 54, 211);  //lila
    init_color(15, 255, 102, 255);
    init_color(16, 225, 28, 232);
    init_color(17, 255, 0, 255);
    init_color(18, 189, 46, 218);
    init_color(19, 180, 73, 192);
    init_color(20, 199, 19, 193);
    init_color(21, 243, 24, 214);
    init_color(22, 202, 91, 242);
    init_color(23, 183, 11, 218);
    init_color(24, 255, 0, 127);
    init_color(25, 230, 113, 243);
    init_pair(1, 11, COLOR_RED);
    init_pair(2, 24, 25);
    init_pair(3, 11, 11);
    init_pair(4, COLOR_BLACK, 12); // background
    init_pair(5, 13, 13); // tabla
    init_pair(6, 14, 14); // tabla
    init_pair(7, 15, 15); // tabla
    init_pair(8, 16, 16); // tabla
    init_pair(9, 17, 17); // tabla
    init_pair(10, 18, 18); // tabla
    init_pair(11, 19, 19); // tabla
    init_pair(12, 20, 20); // tabla
    init_pair(13, 21, 21); // tabla
    init_pair(14, 22, 22); // tabla
    init_pair(15, 23, 23); // tabla
    init_pair(16, 24, 24);
    bkgd(COLOR_PAIR(4));
}

void afisare_tabla(int tabla[][4], int scor){
    clasament();
    attron(A_BOLD | A_BLINK);
    mvprintw(10, 150, "Score: %d", scor);
    attroff(A_BOLD | A_BLINK);
    mvaddstr(0, 0, "   _____  _____ ____  _____  ______ ____   ____          _____  _____  ");
    mvaddstr(1, 0, "  / ____|/ ____/ __ \\|  __ \\|  ____|  _ \\ / __ \\   /\\   |  __ \\|  __ \\ ");
    mvaddstr(2, 0, " | (___ | |   | |  | | |__) | |__  | |_) | |  | | /  \\  | |__) | |  | |");
    mvaddstr(3, 0, "  \\___ \\| |   | |  | |  _  /|  __| |  _ <| |  | |/ /\\ \\ |  _  /| |  | |");
    mvaddstr(4, 0, "  ____) | |___| |__| | | \\ \\| |____| |_) | |__| / ____ \\| | \\ \\| |__| |");
    mvaddstr(5, 0, " |_____/ \\_____\\____/|_|  \\_\\______|____/ \\____/_/    \\_\\_|  \\_\\_____/ ");
    mvaddstr(0, 140, "   _____ _______    _______ _____ ");
    mvaddstr(1, 140, "  / ____|__   __|/\\|__   __/ ____|");
    mvaddstr(2, 140, " | (___    | |  /  \\  | | | (___  ");
    mvaddstr(3, 140, "  \\___ \\   | | / /\\ \\ | |  \\___ \\ ");
    mvaddstr(4, 140, "  ____) |  | |/ ____ \\| |  ____) |");
    mvaddstr(5, 140, " |_____/   |_/_/    \\_\\_| |_____/ ");
    int i, j, valori[] = {0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
    short culori[] = {COLOR_PAIR(5), COLOR_PAIR(6), COLOR_PAIR(7), COLOR_PAIR(8),
    COLOR_PAIR(9), COLOR_PAIR(10), COLOR_PAIR(11), COLOR_PAIR(12), COLOR_PAIR(13),
    COLOR_PAIR(14), COLOR_PAIR(15), COLOR_PAIR(16)};
    int maxY, maxX, inaltime, latime, y, x, cymax, cxmax;
    srand(time(NULL));
    refresh();
    getmaxyx(stdscr, maxY, maxX);
    WINDOW *casuta, *patrat;
    patrat = newwin(24, 50, 10, 63);
    wbkgd(patrat, COLOR_PAIR(2));
    wrefresh(patrat);
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            inaltime = 5;
            latime = 10;
            y = maxY / 2 - (4 * inaltime) / 2 + i * inaltime ;
            x = maxX / 2 - (4 * latime) / 2 + j * latime;
            casuta = newwin(inaltime, latime, y, x);
            getmaxyx(casuta, cymax, cxmax);
            int index = 0;
            while(tabla[i][j] != valori[index]) {
                index++;
            }
            wbkgd(casuta, culori[index]);
            attron(A_BOLD | A_BLINK);
            mvwprintw(casuta, cymax / 2, cxmax / 2 - 1, "%d", tabla[i][j]);
            attroff(A_BOLD | A_BLINK);
            wrefresh(casuta);
            wclear(casuta);
        }
    }
    refresh();
    attron(A_BOLD | A_BLINK);
    mvaddstr(13, 150, "W - move up");
    mvaddstr(14, 150, "S - move down");
    mvaddstr(15, 150, "A - move left");
    mvaddstr(16, 150, "D - move right");
    mvaddstr(17, 150, "Z - undo");
    attroff(A_BOLD | A_BLINK);
    refresh();
    wclear(patrat);
    refresh();
}
 
int validare(int tabla[][4], int *win) {
    int i, j,  jos = 0, sus = 0, dreapta = 0, stanga = 0, miscare = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; ++j) { 
            if (tabla[i][j] == 0) {
                miscare = 1;
            }
            if (tabla[i][j] == 2048) { 
                *win = 1;
                return 1;
            }
        }
    }   
    if (!miscare) {
        for (j = 0; j < 4; ++j) {
            i = 2;
            while (i > -1) {
                while (tabla[i][j] == 0 && i > -1) {
                    i--;
                }
                while (i > -1 && i < 3 && tabla[i+1][j] == tabla[i][j]) {
                    jos = 1;
                    break;
                }
                i--;
                if (jos) { 
                    break;
                }
            }
            if (jos) {
                break;
            }
        }
    
        for (j = 0; j < 4; ++j) {
            i = 1;
            while (i < 4) {
                while (tabla[i][j] == 0 && i < 4) {
                    ++i;
                }
                while (i > 0 && i < 4 && tabla[i][j] == tabla[i-1][j]) {
                    sus = 1;
                    break;
                }
                i++;
                if (sus) {
                    break;
                }
            }
            if (sus) {
                break;
            }
        }

        for(i = 0; i < 4; ++i){
            j = 2;
            while (j > -1){
                while (tabla[i][j] == 0 && j > -1) {
                    j--;
                }
                while (j > -1 && j < 3 && tabla[i][j] == tabla[i][j+1]){
                    dreapta = 1;
                    break;
                }
                j--;
                if (dreapta) {
                    break;
                }
            }
            if (dreapta) {
                    break;
            }
        }

        for (i = 0; i < 4; i++) {
            j = 1;
            while (j < 4) {
                while (tabla[i][j] == 0 && j < 4){
                    j++;
                }
                while (j > 0 && j < 4 && tabla[i][j-1] == tabla[i][j]) {
                    stanga = 1;
                    break;
                }
                j++;
                if (stanga) {
                    break;
                }
            }
            if (stanga) {
                break;
            }
        }
        if (!sus && !jos && !stanga && !dreapta) {
          return 1;
        }
    }
    return 0;
}

void username() {
    clear();
    echo();
    FILE *fisier = fopen("clasament.txt", "a");
    char username[50];
    mvaddstr(0, 50, "  _    _    _____   ______   _____    _   _              __  __   ______ ");
    mvaddstr(1, 50, " | |  | |  / ____| |  ____| |  __ \\  | \\ | |     /\\     |  \\/  | |  ____|");
    mvaddstr(2, 50, " | |  | | | (___   | |__    | |__) | |  \\| |    /  \\    | \\  / | | |__   ");
    mvaddstr(3, 50, " | |  | |  \\___ \\  |  __|   |  _  /  | . ` |   / /\\ \\   | |\\/| | |  __|  ");
    mvaddstr(4, 50, " | |__| |  ____) | | |____  | | \\ \\  | |\\  |  / ____ \\  | |  | | | |____ ");
    mvaddstr(5, 50, "  \\____/  |_____/  |______| |_|  \\_\\ |_| \\_| /_/    \\_\\ |_|  |_| |______|");
    attron(A_BOLD);
    mvprintw(17,36, "INSERT A USERNAME: ");
    scanw("%s", username);
    attroff(A_BOLD);
    fprintf(fisier, "\n%s ", username);
    fclose(fisier);
    interfata_jocnou();
}

void interfata_meniu(){
    int yMax, xMax, highlight = 0, i;
    getmaxyx(stdscr, yMax, xMax);
    noecho();
    WINDOW *meniu = newwin(yMax, xMax, 0, 0);
    mvwaddstr(meniu, 3, 58,"                                              ,---.-,    ");
    mvwaddstr(meniu, 4, 58,"                                      ,--,   '   ,'  '.  ");
    mvwaddstr(meniu, 5, 58,"      ,----,       ,----..          ,--.'|  /   /      \\ ");
    mvwaddstr(meniu, 6, 58,"    .'   .' \\     /   /   \\      ,--,  | : .   ;  ,/.  : ");
    mvwaddstr(meniu, 7, 58,"  ,----,'    |   /   .     :  ,---.'|  : ' '   |  | :  ; ");
    mvwaddstr(meniu, 8, 58,"  |    :  .  ;  .   /   ;.  \\ ;   : |  | ; '   |  ./   : ");
    mvwaddstr(meniu, 9, 58,"  ;    |.'  /  .   ;   /  ` ; |   | : _' | |   :       , ");
    mvwaddstr(meniu, 10, 58,"  `----'/  ;   ;   |  ; \\ ; | :   : |.'  |  \\   \\     /  ");
    mvwaddstr(meniu, 11, 58,"    /  ;  /    |   :  | ; | ' |   ' '  ; :   ;   ,   '\\  ");
    mvwaddstr(meniu, 12, 58,"   ;  /  /-,   .   |  ' ' ' : \\   \\  .'. |  /   /      \\ ");
    mvwaddstr(meniu, 13, 58,"  /  /  /.`|   '   ;  \\; /  |  `---`:  | ' .   ;  ,/.  : ");
    mvwaddstr(meniu, 14, 58,"./__;      :    \\   \\  ',  /        '  ; | '   |  | :  ; ");
    mvwaddstr(meniu, 15, 58,"|   :    .'      ;   :    /         |  : ; '   |  ./   : ");
    mvwaddstr(meniu, 16, 58,";   | .'          \\   \\ .'          '  ,/  |   :      /  ");
    mvwaddstr(meniu, 17, 58, "`---'              `---`            '--'    \\   \\   .'   ");
    mvwaddstr(meniu, 18, 58, "                                             `---`-'     ");
    wbkgd(meniu, COLOR_PAIR(4));
    wrefresh(meniu);
    keypad(meniu, TRUE);
    int ch;
    char *options[] = {"New game", "Resume", "Quit"};
    while (1) {
        for (i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(meniu, A_REVERSE | A_BOLD | COLOR_PAIR(1));
            }
            mvwaddstr(meniu, yMax/2 + 4 + i, xMax/ 2 -4, options[i]);
            wattroff(meniu, A_REVERSE | A_BOLD | COLOR_PAIR(1));
        }
        ch = wgetch(meniu);
        switch (ch) {
            case KEY_UP:
                if(highlight != 0) {
                    highlight--;
                }
                break;
            case KEY_DOWN:
                if(highlight != 2) {
                    highlight++;
                }
            default:
                break;
        }
            if (ch == 10)
                break;
    }
        if (highlight == 0) {
            wclear(meniu);
            wrefresh(meniu);
            username();
        }
        if (highlight == 1){
            wclear(meniu);
            interfata_joc();
            refresh();
        }
        if(highlight == 2){
            wclear(meniu);
            refresh();
        }
        wclear(meniu);
}

void transferare_numere(int tabla[][4], int masca_tabla[][4]){
    int i, j;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            masca_tabla[i][j] = tabla[i][j];
        }
    }
}

int mutare_automata(int tabla[][4]){
    int i, j, masca_tabla[4][4], fr[4] = {0};
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            masca_tabla[i][j] = tabla[i][j];
        }
    }
    for (i = 0; i < 4; i++) {
        j = 1;
        while (j < 4) {
            while (masca_tabla[i][j] == 0 && j < 4){
                j++;
            }
            while (j > 0 && j < 4 && ((masca_tabla[i][j-1] == 0) || masca_tabla[i][j-1] == masca_tabla[i][j])) {
                masca_tabla[i][j-1] += masca_tabla[i][j];
                masca_tabla[i][j] = 0;
                j--;
            }
            j++;
        }
    }
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (masca_tabla[i][j] != 0) {
                fr[0]++;
            }
        }
    }
    transferare_numere(tabla, masca_tabla);
    for (i = 0; i < 4; ++i) {
        j = 2;
        while (j > -1) {
            while (masca_tabla[i][j] == 0 && j > -1) {
                j--;
            }
            while (j > -1 && j < 3 && (masca_tabla[i][j+1] == 0 || masca_tabla[i][j] == masca_tabla[i][j+1])) {
                masca_tabla[i][j+1] += masca_tabla[i][j];
                masca_tabla[i][j] = 0;
                j++;
            }
            j--;
        }
    }
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (masca_tabla[i][j] != 0) {
                fr[1]++;
            }
        }
    }    
    transferare_numere(tabla, masca_tabla);
    for (j = 0; j < 4; ++j) {
        i = 1;
        while (i < 4) {
            while (masca_tabla[i][j] == 0 && i < 4) {
                ++i;
            }
            while (i > 0 && i < 4 && (masca_tabla[i-1][j] == 0 || masca_tabla[i][j] == masca_tabla[i-1][j])) {
                masca_tabla[i-1][j] += masca_tabla[i][j];
                masca_tabla[i][j] = 0;
                i--;
            }
            ++i;
        }
    }
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (masca_tabla[i][j] != 0) {
                fr[2]++;
            }
        }
    }    
    transferare_numere(tabla, masca_tabla);
    for (j = 0; j < 4; ++j) {
        i = 2;
        while (i > -1) {
            while (masca_tabla[i][j] == 0 && i > -1) {
                i--;
            }
            while (i > -1 && i < 3 && (masca_tabla[i+1][j] == 0 || masca_tabla[i+1][j] == masca_tabla[i][j])) {
                masca_tabla[i+1][j] += masca_tabla[i][j];
                masca_tabla[i][j] = 0;
                i++;
            }
            i--;
        }
    }
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (masca_tabla[i][j] != 0) {
                fr[3]++;
            }
        }
    }    
    int min_i = 0, min_miscari = fr[0];
    for (i = 1; i < 4; ++i) {
        if (fr[i] < min_miscari) {
            min_i = i;
            min_miscari = fr[i];
        }
    }
    return min_i;

}

void interfata_jocnou(){
    clear();
    noecho();
    FILE *fisier;
    FILE *clasament = fopen("clasament.txt", "a"); 
    int i,j, ch, win = 0, tabla[4][4], copie[4][4], scor = 0, scor_copie = 0;
    initializare_tabla(tabla);
    numere_inceput(tabla);
    afisare_tabla(tabla, scor);
    refresh();
    afisare_tabla(tabla, scor);
    refresh();
    while (1) {
            refresh();
            date();
            halfdelay(80);
            ch = getch();
            if (ch != ERR) {
                switch (tolower(ch)) {
                    case 'w':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_sus(tabla, &scor)) {
                            numar_random(tabla);

                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'a':
                        scor_copie = scor;  
                        transferare_numere(tabla, copie);
                        if (mutare_stanga(tabla, &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 's':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_jos(tabla,  &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'd':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_dreapta(tabla, &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'z':
                        afisare_tabla(copie, scor_copie);
                        refresh();
                        break;
                    default:
                        break;    
                }
            } else {
                date();
                int miscare = mutare_automata(tabla);
                refresh();
                if (miscare == 0) {
                    mutare_stanga(tabla, &scor);
                    numar_random(tabla);
                    refresh();
                } else if (miscare == 1) {
                        mutare_dreapta(tabla, &scor);
                        numar_random(tabla);
                        refresh();
                } else if (miscare == 2) {
                        mutare_sus(tabla, &scor);
                        numar_random(tabla);
                        refresh(); 
                } else if (miscare == 3) {
                        mutare_jos(tabla, &scor);
                        numar_random(tabla);
                        refresh();
                }
                afisare_tabla(tabla, scor);
            } 
        if (validare(tabla, &win)) {
            fprintf(clasament, "%d", scor);
            fclose(clasament);
            if(win == 0) {
                clear();
                refresh();
                mvaddstr(15, 50, "   _____          __  __ ______    ______      ________ _____  ");
                mvaddstr(16, 50, "  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
                mvaddstr(17, 50, " | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
                mvaddstr(18, 50, " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ");
                mvaddstr(19, 50, " | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
                mvaddstr(20, 50, "  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
                refresh();
                sleep(5);
                break;
            } else {
                clear();
                refresh();
                mvaddstr(15, 65, " __          _______ _   _ ");
                mvaddstr(16, 65, " \\ \\        / /_   _| \\ | |");
                mvaddstr(17, 65, "  \\ \\  /\\  / /  | | |  \\| |");
                mvaddstr(18, 65, "   \\ \\/  \\/ /   | | | . ` |");
                mvaddstr(19, 65, "    \\  /\\  /   _| |_| |\\  |");
                mvaddstr(20, 65, "     \\/  \\/   |_____|_| \\_|");
                refresh();
                sleep(5);
                break;
            }
        }
        int q = 'q';
        if (tolower(ch) == (int)q) {
            clear();
            refresh();
            fisier = fopen("tabla.txt", "w");
            for (i = 0; i < 4; ++i) {
                for (j = 0; j < 4; ++j) {
                    fprintf(fisier, "%d ", tabla[i][j]);
                }
            }
            fprintf(fisier, "%d ", scor);
            fclose(fisier);
            interfata_meniu();
            refresh();
            break;
        }
        cbreak();
    }
}


void clasament() {
    typedef struct{
        char username[100];
        int scor;
    } jucator;
    jucator juc[100];
    FILE *clasament = fopen("clasament.txt", "r");
    int i = 0, numar_jucatori, j;
    while (fscanf(clasament, "%s %d", juc[i].username, &juc[i].scor) == 2) {
        i++;
    }
    fclose(clasament);
    numar_jucatori = i;
    for (i = 0; i < numar_jucatori - 1; i++) {
            for (j = i + 1 ; j < numar_jucatori; ++j) {
                if (juc[i].scor < juc[j].scor) {
                    char auxc[100];
                    strcpy(auxc, juc[i].username);
                    strcpy(juc[i].username, juc[j].username);
                    strcpy(juc[j].username, auxc);
                    int aux;
                    aux = juc[i].scor;
                    juc[i].scor = juc[j].scor;
                    juc[j].scor = aux;
                }
            }
    }
    if(numar_jucatori < 10) {
        j = numar_jucatori;
    } else {
        j = 10;
    }
    i = 0;
    int pozy = 10;
    attron(A_BLINK | A_BOLD);
    while (i < j) {
        mvprintw(pozy, 10, "%s %d", juc[i].username, juc[i].scor);
        pozy++;
        i++;
    }
    attroff(A_BLINK | A_BOLD);
}

void interfata_joc(){
    clear();
    noecho();
    int i, j, tabla[4][4], scor = 0, ch, win = 0, copie[4][4], scor_copie = 0;
    FILE *fisier = fopen("tabla.txt", "r");
    FILE *clasament = fopen("clasament.txt", "a");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(fisier, "%d", &tabla[i][j]);
        }
    }
    fscanf(fisier, "%d", &scor);
    afisare_tabla(tabla, scor);
    refresh();
    afisare_tabla(tabla, scor);
    refresh();
    while (1) {
            refresh();
            halfdelay(80);
            date();
            ch = getch();
            if (ch != ERR) {
                switch (tolower(ch)) { 
                case 'w':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_sus(tabla, &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'a':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_stanga(tabla, &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 's':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_jos(tabla,  &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'd':
                        scor_copie = scor;
                        transferare_numere(tabla, copie);
                        if (mutare_dreapta(tabla, &scor)) {
                            numar_random(tabla);
                        }
                        afisare_tabla(tabla, scor);
                        break;
                    case 'z':
                        afisare_tabla(copie, scor_copie);
                    default:
                        break;
                }
            } else {
                date();            
                int miscare = mutare_automata(tabla);
                refresh();
                if (miscare == 0) {
                    mutare_stanga(tabla, &scor);
                    numar_random(tabla);
                    refresh();
                } else if (miscare == 1) {
                        mutare_dreapta(tabla, &scor);
                        numar_random(tabla);
                        refresh();
                } else if (miscare == 2) {
                        mutare_sus(tabla, &scor);
                        numar_random(tabla);
                        refresh(); 
                } else if (miscare == 3) {
                        mutare_jos(tabla, &scor);
                        numar_random(tabla);
                        refresh();
                }
            afisare_tabla(tabla, scor);
        }
        if (validare(tabla, &win)) {
            fprintf(clasament,"%d\n", scor);
            fclose(clasament); 
            if(win == 0) {
                clear();
                sleep(0);
                refresh();
                mvaddstr(15, 50, "   _____          __  __ ______    ______      ________ _____  ");
                mvaddstr(16, 50, "  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
                mvaddstr(17, 50, " | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
                mvaddstr(18, 50, " | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ");
                mvaddstr(19, 50, " | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
                mvaddstr(20, 50, "  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\");
                refresh();
                sleep(5);
                break;
            } else {
                clear();
                refresh();
                mvaddstr(15, 65, " __          _______ _   _ ");
                mvaddstr(16, 65, " \\ \\        / /_   _| \\ | |");
                mvaddstr(17, 65, "  \\ \\  /\\  / /  | | |  \\| |");
                mvaddstr(18, 65, "   \\ \\/  \\/ /   | | | . ` |");
                mvaddstr(19, 65, "    \\  /\\  /   _| |_| |\\  |");
                mvaddstr(20, 65, "     \\/  \\/   |_____|_| \\_|");
                refresh();
                sleep(5);
                break;
            }
        }
        int q = 'q';
        if (tolower(ch) == (int)q) {
            clear();
            refresh();
            fisier = fopen("tabla.txt", "w");
            for (i = 0; i < 4; ++i) {
                for (j = 0; j < 4; ++j) {
                    fprintf(fisier, "%d ", tabla[i][j]);
                }
            }
            fprintf(fisier, "%d ", scor);
            fclose(fisier);
            interfata_meniu();
            refresh();
            break;
        }
        cbreak();
    }
}

int main(){
    initscr();
    start_color();
    color_initializare_tabla();
    curs_set(0);
    raw();
    noecho();
    refresh();
    interfata_meniu();
    refresh();
    endwin();
    return 0;
}