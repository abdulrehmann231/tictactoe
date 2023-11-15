#include <stdio.h>

const int size=3;

void printboard(char arr[size][size]) {
    int i,j;
	for ( i=0; i<size;i++) {
        for (j=0; j<size; j++) {
            printf("%c", arr[i][j]);
            if (j <size - 1) {
                printf(" | ");
            }
        }
        printf("\n");
        if (i < size - 1) {
            printf("---------\n");
        }
    }
    printf("\n");
}


int checkwinner(char arr[size][size], char player) {

    int i,j;
    for (i=0; i<size; i++) {
        if ((arr[i][0] == player && arr[i][1] == player && arr[i][2] == player) || (arr[0][i] == player && arr[1][i] == player && arr[2][i] == player)) {
            return 1;
        }
    }
    if ((arr[0][0] == player && arr[1][1] == player && arr[2][2] == player) || (arr[0][2] == player && arr[1][1] == player && arr[2][0] == player)) {
        return 1;
    }

    return 0;
}

int checkdraw(char arr[size][size]) 
 { 
     int i,j;  
    for (i=0; i<size; i++) {
        for (j=0; j<size; j++) {
            if (arr[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}


int evaluate(char arr[size][size]) {
    if (checkwinner(arr, 'O')) {
        return 1;  
    } 
	else if (checkwinner(arr, 'X')) {
        return -1;  
    } 
	else if (checkdraw(arr)) {
        return 0;  
    }
    return -2; 
}


int minimax(char arr[size][size], int depth, int Player) {
    int score = evaluate(arr);

    if (score != -2) {
        return score;
    }

    if (Player) {
        int max = -1000;
        int i ,j;
        for (i = 0; i < size; i++) {
            for (j=0; j < size; j++) {
                if (arr[i][j] == ' ') {
                    arr[i][j] = 'O';
                    int eval = minimax(arr, depth + 1, 0);
                    arr[i][j] = ' ';
                    if (eval > max) {
                        max = eval;
                    }
                }
            }
        }
        return max;
    }
	 else {
        int min = 1000;
            int i,j;
        for (i=0; i<size; i++) {
            for (j=0; j<size; j++) {
                if (arr[i][j] == ' ') {
                    arr[i][j] = 'X';
                    int eval = minimax(arr, depth + 1, 1);
                    arr[i][j] = ' ';
                    if (eval < min) {
                        min = eval;
                    }
                }
            }
        }
        return min;
    }
}


void findBestMove(char arr[size][size]) {
    int best = -1000;
    int Move[2] = {-1, -1};
     int i,j;
    for (i=0;i< size; i++) {
        for (j =0;j<size; j++) {
            if (arr[i][j] == ' ') {
                arr[i][j] = 'O';
                int moveVal = minimax(arr, 0, 0);
                arr[i][j] = ' ';

                if (moveVal > best) {
                    Move[0] = i;
                    Move[1] = j;
                    best = moveVal;
                }
            }
        }
    }

    arr[Move[0]][Move[1]] = 'O';
}


void play() {
    char arr[size][size];

    int i,j;
    for (i=0; i<size; i++) {
        for (j=0; j<size; j++) {
            arr[i][j] = ' ';
        }
    }

    int end = 0;

    while (!end) {
        
        printboard(arr);
        int Row, Col;
        printf("Enter row : ");
        scanf("%d", &Row);
        printf("Enter column : ");
        scanf("%d", &Col);

        if (arr[Row][Col] == ' ' && Row >= 0 && Row < size && Col >= 0 && Col < size) {
            arr[Row][Col] = 'X';

            
            if (checkwinner(arr, 'X')) {
                printboard(arr);
                printf("You win!\n");
                end = 1;
                break;
            }
        }
		 else {
            printf("Invalid move. Try again.\n");
            continue;
        }

        if (checkdraw(arr)) {
            printboard(arr);
            printf("Its a tie!\n");
            end = 1;
            break;
        }

        
        findBestMove(arr);

        
        if (checkwinner(arr, 'O')) {
            printboard(arr);
            printf("bot wins!\n");
            end = 1;
            break;
        }

        
        if (checkdraw(arr)) {
            printboard(arr);
            printf("Its a tie!\n");
            end = 1;
        }
    }
}

int main() {
    play();
    return 0;
}

