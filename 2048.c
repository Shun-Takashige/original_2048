#define height 5
#define width 5
#define key_left 1
#define key_right 2
#define key_up 3
#define key_down 4

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<math.h>

void create_new_square(int board_num[height][width]);
void print_boardgame(int board[height][width]);
void push_zero_side(int board[height][width], int org_board[height][width], int key);
void key_function(int board[height][width], int key);
void print_start_screen();
void print_instruction_screen();
int check_gameover(int board[height][width]);

int main (int argc, char *argv[]) {
    printf("Press any key to conitnue\n");
    int c;
    int board[height][width];
    for(int h = 0; h < height; ++h){
        for(int w = 0; w < width; ++w){
            board[h][w] = 0;
        }
    }

    system("/bin/stty raw onlcr");  // enterを押さなくてもキー入力を受け付けるようになる
    if((c = getchar())!='.'){
        print_start_screen();
        
    }
    if((c = getchar())!='.'){
        system("clear");
        print_instruction_screen();
    }
    if((c = getchar()) != EOF){
        system("clear");
        create_new_square(board);
        print_boardgame(board);
        printf("Press '.' to close\r\n");
    }

    int key;

    while((c = getchar()) != '.') {
        system("clear");
        
        if ((c == 'k')||(c == 'i')||(c == 'j')||(c == 'm')) {
            if (c == 'k'){
                key = key_right;
            } else if (c == 'i'){
                key = key_up;
            } else if (c == 'j'){
                key = key_left;
            } else if (c == 'm'){
                key = key_down;
            }
            key_function(board, key);
            if(check_gameover(board)==1){
                printf("......gameover.....\r\n");
                continue;
            }else{
                create_new_square(board);
            }
        }      
        // system("clear");
        print_boardgame(board);
        printf("You pressed '%c'\r\n", c);
        printf("Press '.' to close\r\n");
    }

    system("/bin/stty cooked");  // 後始末

    return 0;
}


void create_new_square(int board[height][width]){
    int zero_square_position[height*width];
    for(int i = 0; i < height*width; ++i){
        zero_square_position[i] = 0;
    }
    int count_zero_square = 0;
    for(int h = 0; h < height; ++h){
        for(int w = 0; w < width; ++w){
            if(board[h][w] == 0){
                zero_square_position[count_zero_square] = width * h + w;
                ++count_zero_square;
            }
        }
    }
    srand(time(NULL));
    int random_num;
    random_num = rand() % count_zero_square;
    int h_random = zero_square_position[random_num] / width;
    int w_random = zero_square_position[random_num] % width;
    //sleep(1);
    srand(time(NULL));
    if(random_num % 2){
        board[h_random][w_random] = 2;
    }else{
        board[h_random][w_random] = 4;
    }
}

void print_boardgame(int board[height][width]){
    printf("+------+------+------+------+------+\r\n");
    for(int h = 0; h < height; ++h){
        printf("|");
        for(int w = 0; w < width; ++w){
            if(board[h][w] == 0){
                printf("     ");
            }else if(board[h][w] == 2){
                printf("    \e[38;5;168m2\e[0m");
            }else if(board[h][w] == 4){
                printf("    \e[38;5;178m4\e[0m");
            }else if(board[h][w] == 8){
                printf("    \e[38;5;105m8\e[0m");
            }else if(board[h][w] == 16){
                printf("   \e[38;5;32m16\e[0m");
            }else if(board[h][w] == 32){
                printf("   \e[38;5;168m32\e[0m");
            }else if(board[h][w] == 64){
                printf("   \e[38;5;178m64\e[0m");
            }else if(board[h][w] == 128){
                printf("  \e[38;5;105m128\e[0m");
            }else if(board[h][w] == 256){
                printf("  \e[38;5;32m256\e[0m");
            }else if(board[h][w] == 512){
                printf("  \e[38;5;168m512\e[0m");
            }else if(board[h][w] == 1024){
                printf(" \e[38;5;178m1024\e[0m");
            }else if(board[h][w] == 2048){
                printf(" \e[38;5;105m2048\e[0m");
            }else if(board[h][w] == 4096){
                printf(" \e[38;5;32m4096\e[0m");
            }else if(board[h][w] == 2){
                printf(" \e[38;5;168m8192\e[0m");
            }else if(board[h][w] == 2){
                printf("\e[38;5;178m16384\e[0m");
            }else if(board[h][w] == 2){
                printf("\e[38;5;105m32768\e[0m");
            }else if(board[h][w] == 2){
                printf("\e[38;5;32m65538\e[0m");
            }
            printf(" |");            
        }
        printf("\r\n");
        printf("+------+------+------+------+------+\r\n");
    }    
}

void push_zero_side(int board[height][width], int org_board[height][width], int key){
    int org_current;
    for(int h = 0; h < height; ++h){
        for(int w = 0; w < width; ++w){
            org_board[h][w] = 0;
        }
    }
    if(key == key_left){//key == 1で左矢印
        for(int h = 0; h < height; ++h){
            org_current = 0;
            for(int w = 0; w < width; ++w){
                if(board[h][w] != 0){
                    org_board[h][org_current] = board[h][w];
                    ++org_current;
                }
            }
        }
    }
    else if(key == key_right){//key == 2で右矢印
        for(int h = 0; h < height; ++h){
            org_current = width - 1;
            for(int w = width - 1; w >= 0; --w){
                if(board[h][w] != 0){
                    org_board[h][org_current] = board[h][w];
                    --org_current;
                }
            }
        }
    }
    else if(key == key_up){//key == 3で上矢印
        for(int w = 0; w < width; ++w){
            org_current = 0;
            for(int h = 0; h < height; ++h){
                if(board[h][w] != 0){
                    org_board[org_current][w] = board[h][w];
                    ++org_current;
                }
            }
        }
    }
    else if(key == key_down){//key == 4で下矢印
        for(int w = 0; w < width; ++w){
            org_current = height - 1;
            for(int h = height -1 ; h >= 0 ; --h){
                if(board[h][w] != 0){
                    org_board[org_current][w] = board[h][w];
                    --org_current;
                }
            }
        }
    }
}

void cal_new_board(int board[height][width], int org_board[height][width], int key){
    int w, h;
    int org_current;
    for(int y = 0; y < height; ++y){
        for(int x = 0; x < width; ++x){
            board[y][x] = 0;
        }
    }
    if(key == key_left){
        h = 0;
        while(h != height){
            w = 0;
            org_current = 0;
            while(org_current != width){
                if(org_current == width - 1){
                    board[h][w] = org_board[h][org_current];
                    ++org_current;
                }
                else if((org_board[h][org_current] != 0)&&(org_board[h][org_current] == org_board[h][org_current + 1])){
                    board[h][w] = org_board[h][org_current] + org_board[h][org_current + 1];
                    org_current += 2;
                }
                else{
                    board[h][w] = org_board[h][org_current];
                    ++org_current;
                }
                ++w;
            }
        ++h;
        }
    }
    else if(key == key_right){
        h = 0;
        while(h != height){
            w = width - 1;
            org_current = width - 1;
            while(org_current != -1){
                if(org_current == 0){
                    board[h][w] = org_board[h][org_current];
                    --org_current;
                }
                else if((org_board[h][org_current] != 0)&&(org_board[h][org_current] == org_board[h][org_current - 1])){
                    board[h][w] = org_board[h][org_current] + org_board[h][org_current - 1];
                    org_current -= 2;
                }
                else{
                    board[h][w] = org_board[h][org_current];
                    --org_current;
                }
                --w;
            }
        ++h;
        }
       
    }
    else if(key == key_up){
        w =0;
        while(w != width){
            h = 0;
            org_current = 0;
            while(org_current != height){
                if(org_current == height - 1){
                    board[h][w] = org_board[org_current][w];
                    ++org_current;
                }
                else if((org_board[org_current][w] != 0)&&(org_board[org_current][w] == org_board[org_current + 1][w])){
                    board[h][w] = org_board[org_current][w] + org_board[org_current + 1][w];
                    org_current += 2;
                }
                else{
                    board[h][w] = org_board[org_current][w];
                    ++org_current;
                }
                ++h;
            }
        ++w;
        }
    }
    else if (key == key_down){
        w = 0;
        while(w != width){
            h = height - 1;
            org_current = height - 1;
            while(org_current != -1){
                if(org_current == 0){
                    board[h][w] = org_board[org_current][w];
                    --org_current;
                }
                else if((org_board[org_current][w] != 0)&&(org_board[org_current][w] == org_board[org_current - 1][w])){
                    board[h][w] = org_board[org_current][w] + org_board[org_current - 1][w];
                    org_current -= 2;
                }
                else{
                    board[h][w] = org_board[org_current][w];
                    --org_current;
                }
                --h;
            }
        ++w;
        }
    }

}

void key_function(int board[height][width], int key){
    int org_board[height][width];
    push_zero_side(board, org_board, key);
    cal_new_board(board, org_board, key);
    
}

void print_start_screen(){
    printf("          _________________________________________________________________                 \r\n");
    printf("         |                                                               |                 \r\n");
    printf("         |    _______ ______ ______  _  _     _____ _    __ __      __   |                 \r\n");
    printf("         |   /_  __ //  ___//  >  / / |/ |   /_ __// \\  / //  \\    / /   |                 \r\n");
    printf("         |    / /   /  /_  /  *--' /     |    //  /   \\/ // <  \\  / /    |                 \r\n");
    printf("         |   / /   /  __/ / /\\ \\  / /|/| |  _//_ / /\\   //  _   \\/ /__   |                 \r\n");
    printf("         |  /_/   /_____//_/  \\_\\/_/   |_|/____//_/  \\_//__/ \\__/____/   |                 \r\n");
    printf("         |                                                               |                 \r\n");
    printf("         |         _________   _________   ___   ___    _________        |                 \r\n");
    printf("         |        /_____   /  /  __    /  /  /  /  /   /  ___   /        |                 \r\n");
    printf("         |        _____/  /  /  /  /  /  /  /__/  /_  /  /__/  /         |                 \r\n");
    printf("         |       /  _____/  /  /  /  /  /____     _/ /  ___   /          |                 \r\n");
    printf("         |      /  /_____  /  /__/  /       /   /   /  /__/  /           |                 \r\n");
    printf("         |     /________/ /________/       /___/   /________/            |                 \r\n");
    printf("         |_______________________________________________________________|                 \r\n");
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    printf("                     \e[38;5;166mPlay game!!(push any key to continue)\e[0m                                      \r\n");
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
}


void print_instruction_screen(){
    printf("Instruction\r\n");
    printf("-----------------------------------------------\r\n");
    printf("In this game, you can move figures in four direction.\r\n");
    printf("Every turn, a new tile will randomly appear in an empty spot on the board with a value of either 2 or 4.\r\n");
    printf("If two tiles of the same number collide while moving, they will merge into a tile with the total value \r\n") ;
    printf("of the two tiles that collided.\r\n");
    printf("Also, when two tiles merge, you get points of the total value.\r\n");
    printf("Let's get as many points as possible!!\r\n");
    printf("(partly from Wikipedia)\r\n");
    printf("-----------------------------------------------\r\n");
    printf("key_function:\r\n'k' : left\r\n'j' : right\r\n'i' : up\r\n'm' : down\r\n-----------------------------------------------\r\nthe evaluation\r\npoints\r\n\r\n\r\n\r\n\r\n\r\n");
}



int check_gameover(int board[height][width]){
    int check;
    int check_zero = 0;
    for(int h = 0; h < height; ++h){
        for(int w = 0; w < width; ++w){
            if(board[h][w] == 0){
                ++check_zero;
            }
        }
    }
    if(check_zero == 0){
        check = 1;
    }else{
        check = 0;
    }
    return check;
}