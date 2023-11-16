#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 5


typedef struct point {
    int x;  // x座標
    int y;  // y座標
    int v;  // 進化度
} Point;

typedef struct board {
    char field[BOARD_SIZE][BOARD_SIZE + 1];
} Board;


void print_board(Board b, Point p) {
    b.field[p.y][p.x] = p.v + '0';

    for(int i = 0; i < BOARD_SIZE; ++i) {        
        printf("%s\r\n", b.field[i]);
    }    
}


int main (int argc, char *argv[]) {

    Board b = {.field = {
        "-----",
        "-----",
        "-----",
        "-----",
        "-----"        
    }};

    Point p = {.x = 0, .y = 0, .v = 1};  // 現在操作しているオブジェクト
    int c = '_';  // Dummy 
    char status = 0;

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる

    while (1) {
        system("clear");
        printf("Press '.' to close\r\n");        
        printf("You pressed '%c'\r\n", c);
        if (status == 1){
            b.field[p.y][p.x] = p.v + '0';
            p.x = 0;
            p.y = 0;
            status = 0;
        } else if (c == 'd') {
            if (p.x < 4){
                ++p.x;
            }
        } else if(c == 'a'){
            if (p.x > 0){
                --p.x;
            }
        } else if (c == 's'){
            int t = 4;
            while(b.field[t][p.x] != '-'){
                --t;
            }
            p.y = t;
            status = 1;
        } else if (c == 'w'){
            if (p.y > 0){
                --p.y;
            }
        } 

        print_board(b, p);

        if ((c = getchar()) == '.') { // '.' を押すと抜ける
            break;
        }
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}