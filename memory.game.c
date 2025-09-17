
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Maxboard 30
#define Maxplayers 10
#define MaxNames 20

void welcoming(int n, char *argv[]){
    //Printing all the welcoming stuff.
    printf("Welcome to the Memory Card Game!\n");
    printf("The game will be played on the following board:\n\n");
    int i, count = 0;
    printf(" ");
    while (count < n){
        printf(" |  %d ", count);
        count++;
    }
    printf(" |\n");
    count = 0;
    while (count <= n) {
        for (i = 0; i < 6 * n + 3; i++) {
            printf("-");
        }
        printf("\n");
        if (count < n) {
            printf("%d |", count);
            for (int j = 0; j <= n; j++) {
                if (j + 1 <= n){
                    printf("(%d,%d)|", count, j);
                }
            }
        }
        count++;
        printf("\n");
    }
    printf("And the following objects:\n\n");
    int count2 = 0;
    while (count2 < (n * n / 2)){
        printf("%d. %s\n", count2 + 1, argv[4 + count2] );
        count2++;
    }
    printf("\nLet the game begin!\n");
    printf("\nCurrent board state:\n");
    int count3 = 0;
    for (i = 0; i <= n * 16; i++) {
        printf("-");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("|");
        for (int s = 0; s < n; s++) {
            while (count3 <= 15 / 2 - 1) {
                printf(" ");
                count3++;
            }
            printf("X");
            count3 = 0;
            while (count3 <= 15 / 2 - 1) {
                printf(" ");
                count3++;
            }
            count3 = 0;
            printf("|");
        }
        if(i + 1 < n){
        printf("\n");
            for (int j = 0; j <= 16 * n; j++)
                printf("-");
            printf("\n");
            }

    }
    printf("\n");
    for (i = 0; i <= 16 * n; i++){
            printf("-");
    }
}




void boardplace(char *argv[],char board[Maxboard][Maxboard][MaxNames], int n) {
    // This function puts the object in the right places.
    int i;
    int objectsnumber = n * n / 2;
    for (i = 0; i < objectsnumber; i++){
        int k1 = atoi(argv[4 + objectsnumber + 2 * i]);
        strcpy(board[k1 / n][k1 % n], argv[4 + i]);
        int k2 = atoi(argv[5 + objectsnumber + 2 * i]);
        strcpy(board[k2 / n][k2 % n], argv[4 + i]);
    }
}

int namecut(char *cut, char names[Maxplayers][MaxNames]){
    //Tokenizes a string using '#' as a delimiter to extract player names.
    char *token = strtok(cut, "#");
    int count = 0;
    while (token != NULL){
        strcpy(names[count], token);
        count++;
        token = strtok(NULL, "#");
    }
    return count;
}
void xboard(char Newboard[Maxboard][Maxboard][MaxNames], int n){
    //Makeing a 3D array that's all of her members are X.
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            strcpy(Newboard[i][j], "X");

        }
    }
}


void PlayBoard(char board[Maxboard][Maxboard][MaxNames], char Newboard[Maxboard][Maxboard][MaxNames],
               int n, int compare, int dig0, int dig1, int dig2, int dig3) {
    //This function updates the board and prints it according to the player move.
    int i = 0, count2 = 0;
    for (; i <= n * 16; i++) {
        printf("-");
    }
    printf("\n");
    int j;
    long long int leng;
    printf("|");
    if (compare == 0) {
        strcpy(Newboard[dig0][dig1], board[dig0][dig1]);
        strcpy(Newboard[dig2][dig3], board[dig2][dig3]);
        for (i = 0; i < n; i++) {
            for (int s = 0; s <= n; s++) {
                if (count2 > n) {
                    count2 = 0;
                    printf("\n|");
                }
                if (count2 < n) {
                    leng = strlen(Newboard[i][s]);
                    if (leng % 2 != 0) {
                        for (j = 0; j < (15 - leng) / 2; j++) {
                            printf(" ");
                        }
                        printf("%s", Newboard[i][s]);
                        for (int k = 0; k < (15 - leng) / 2 ; k++) {
                            printf(" ");
                        }
                    } else if (leng % 2 == 0) {
                        for (j = 0; j < (16 - leng) / 2; j++) {
                            printf(" ");
                        }
                        printf("%s", Newboard[i][s]);
                        for (int k = 0; k < (16 - leng) / 2 - 1; k++) {
                            printf(" ");
                        }
                    }
                    printf("|");
                } else if (count2 == n) {
                    printf("\n");
                    int count1 = 0;
                    while (count1 <= 16 * n) {
                        printf("-");
                        count1++;
                    }
                }

                count2++;

            }
        }
    }
}
void changingboard(int n, char board[Maxboard][Maxboard][MaxNames], char Newboard[Maxboard][Maxboard][MaxNames],int x, int y, int d,
                  int r){
    //Recives the player input and sends it to Playboard func.
    int digit0 = x;
    int digit1 = y;
    int digit2 = d;
    int digit3 = r;
    int compare = strcmp(board[digit0][digit1], board[digit2][digit3]);
    // We are comparing that if the player puts the same row and colomun twice.
    if (digit0 == digit2 && digit1 == digit3)
        return;
    //Checking if the words are mathcing.
    switch (compare) {
        case 0:
            PlayBoard(board, Newboard, n, compare, digit0, digit1, digit2, digit3);
            break;
        default:
            break;

    }
}
void sameboard(char Newboard[Maxboard][Maxboard][MaxNames], int n){
    //Displays the current state of the board when there is no match.
    int i = 0;
    for (; i <= n * 16; i++) {
        printf("-");
    }
    printf("\n|");
   int count2 = 0, leng, j;
    for (i = 0; i < n; i++) {
        for (int s = 0; s <= n; s++) {
            if (count2 > n) {
                count2 = 0;
                printf("\n|");
            }
            if (count2 < n) {
                leng = strlen(Newboard[i][s]);
                if (leng % 2 != 0) {
                    for (j = 0; j < (15 - leng) / 2; j++) {
                        printf(" ");
                    }
                    printf("%s", Newboard[i][s]);
                    for (int k = 0; k < (15 - leng) / 2 ; k++) {
                        printf(" ");
                    }
                } else if (leng % 2 == 0) {
                    for (j = 0; j < (16 - leng) / 2; j++) {
                        printf(" ");
                    }
                    printf("%s", Newboard[i][s]);
                    for (int k = 0; k < (16 - leng) / 2 - 1; k++) {
                        printf(" ");
                    }
                }
                printf("|");
            } else if (count2 == n) {
                printf("\n");
                int count1 = 0;
                while (count1 <= 16 * n) {
                    printf("-");
                    count1++;
                }
            }

            count2++;

        }
    }
}






int main(int argc, char *argv[]) {
    // If there are less than 3 argc then the game will not work.
    if (argc < 3) {
        printf("INVALID INPUT");
        return 0;
    }
    // Puting the number of players in "m" and the board length and width in "n".
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    char *cut = argv[3];
    char names[Maxplayers][MaxNames];
    char board[Maxboard][Maxboard][MaxNames];
    char Newboard[Maxboard][Maxboard][MaxNames];
    int objectnum = n * n / 2;
    for (int i = 0; i < n * n; i++) {
     for (int j = i + 1; j < n * n; j++){
         // Checking if there are tow of the same positions.
         if (atoi(argv[4 + objectnum + i]) == atoi(argv[4 + objectnum + j])) {
             printf("INVALID INPUT");
             return 0;
         }
     }// Checking if there is a position that is equal or bigger than n * n or smaller than zero.
        if (atoi(argv[4 + objectnum + i]) >= n * n || atoi(argv[4 + objectnum + i]) < 0){
            printf("INVALID INPUT");
            return 0;
        }
    }
    int countnames = namecut(cut, names);
    if (countnames < m){
        // If Names count is smaller than m that means that there are lost players.
        printf("INVALID INPUT");
        return  0;
    }
    boardplace( argv, board, n);
    xboard(Newboard, n);
    welcoming(n, argv);
    int z, f, d, r, j;
    int count1 = 0, count2 = 0, count3 = 0, count4 =0, arr[m];
    char printedarr[Maxboard][Maxboard][MaxNames];
    for (int i =0; i < m; i++){
        arr[i] = 0;
    }
    int place = count2 % m;
    printf("\n\nIt is %s's turn.", names[place]);
    while (count1 < n * n / 2) {
        place = count2 % m;
        printf("\nEnter the coordinates of the first card (row col): ");
        scanf("%d", &z);
        scanf("%d", &f);
        printf("Enter the coordinates of the second card (row col): ");
        scanf("%d", &d);
        scanf("%d", &r);
        int check;
        for (int i = 0; i < n; i++) {
            //Checking whether a specific card has been revealed twice during a single player's turn.
            for (int k = 0; k < n; k++) {
                if (strcmp(printedarr[i][k], board[z][f]) == 0)
                    count4++;
            }
        }
        int countobject = 0;
        for (int i = 4; i < n * n /2 ; i++) {
            //Counting the objects to check it in the next if.
            if (argv[i] != NULL)
                countobject++;
        }

        if (z >= n || f >= n || d >= n || r >= n || z == d && f == r || count4 == 2 || countobject > n * n / 2) {
            // Checking whether the input is larger than n
            printf("Invalid move. Try again.");
            count4 = 0;
        }
        else {
            count4 = 0;
            check = strcmp(board[z][f], board[d][r]);
            if (check == 0) {
                printf("Match!");
                if (count1 + 1 == n * n / 2)
                {
                    count1++;
                    printf("\n\nThe scores are:\n");
                    arr[count2 % m]++;
                    for (int i = 0; i < m; i++) {
                        printf("%s: %d", names[i], arr[i]);
                        if (i + 1 < m)
                            printf(", ");
                    }
                }
                else {
                    printf("\n\nThe scores are:\n");
                    arr[count2 % m]++;
                    for (int i = 0; i < m; i++) {
                        printf("%s: %d", names[i], arr[i]);
                        if (i + 1 < m)
                            printf(", ");
                    }
                    printf("\n");
                    printf("Current board state:\n");
                    changingboard(n, board, Newboard, z, f, d, r);
                    count1++;
                    strcpy(printedarr[z][f], Newboard[z][f]);
                    strcpy(printedarr[d][r], Newboard[d][r]);
                    printf("\n\nIt is %s's turn.", names[place]);
                }
            } else {
                printf("No match. Try again.");
                count2++;
                printf("\n\nThe scores are:\n");
                for (int i = 0; i < m; i++) {
                    printf("%s: %d", names[i], arr[i]);
                    if (i + 1 < m)
                        printf(", ");
                }
                printf("\n");
                printf("Current board state:\n");
                sameboard(Newboard, n);
                place = count2 % m;
                printf("\n\nIt is %s's turn.", names[place]);

            }
        }
    }
    int sum1 = 0, sum2 = 0;
    for (j = 0; j < m; j++){
        //Checks if the current player's score (arr[j]) is greater than the current maximum (sum1).
        if (sum1 < arr[j]) {
            sum1 = arr[j];
            count3 = j;
            //count3 contain the position of the player with the higher score.
        }//If the score is equal to the current maximum, it sets sum2 to the same value as sum1.
        else if (sum1 == arr[j])
            sum2 = sum1;

    }
    if (sum1 > sum2)
        printf("\nCongratulations %s! You won!", names[count3]);
    if (sum1 == sum2)
        printf("\nIt's a tie!");
    return 0;
}