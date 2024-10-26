#include <stdio.h>
#define ROWS 80
#define COLS 25

void input(int* r1_pos_y, int* r2_pos_y, int flag_x, int flag_y, int* ball_x, int* ball_y);
void calculate_ball(int* ball_x, int* ball_y, int r1_pos_y, int r2_pos_y, int* flag_x, int* flag_y);
void calculate_score(int* ball_x, int* ball_y, int* score_left, int* score_right);
void print_field(int r1_pos_x, int r2_pos_x, int r1_pos_y, int r2_pos_y, int ball_x, int ball_y, int score_left, int score_right);

int main(void) {
    int r1_pos_x = 13;
    int r1_pos_y = 12;
    int r2_pos_x = 67;
    int r2_pos_y = 12;
    int ball_x = 39;
    int ball_y = 12;
    int flag_y = 0;
    int flag_x = 0;
    int score_left = 0;
    int score_right = 0;

    print_field(r1_pos_x, r2_pos_x, r1_pos_y, r2_pos_y, ball_x, ball_y, score_left, score_right);

    while (score_left < 21 && score_right < 21) {
        input(&r1_pos_y, &r2_pos_y, flag_x, flag_y, &ball_x, &ball_y);
        calculate_ball(&ball_x, &ball_y, r1_pos_y, r2_pos_y, &flag_x, &flag_y);
        calculate_score(&ball_x, &ball_y, &score_left, &score_right);
        print_field(r1_pos_x, r2_pos_x, r1_pos_y, r2_pos_y, ball_x, ball_y, score_left, score_right);
    }

    printf("Game over! Congratulations to player %d.\n", score_left > score_right ? 1 : 2);
    return 0;
}
void input(int* r1_pos_y, int* r2_pos_y, int flag_x, int flag_y, int* ball_x, int* ball_y) {
    char move = getchar();
    switch (move) {
        case 'a':
            if ((*r1_pos_y - 2) > 0) (*r1_pos_y)--;
            break;
        case 'z':
            if ((*r1_pos_y + 2) < COLS - 1) (*r1_pos_y)++;
            break;
        case 'k':
            if ((*r2_pos_y - 2) > 0) (*r2_pos_y)--;
            break;
        case 'm':
            if ((*r2_pos_y + 2) < COLS - 1) (*r2_pos_y)++;
            break;
        default:
            flag_x == 0 ? (*ball_x)++ : (*ball_x)--;
            flag_y == 0 ? (*ball_y)++ : (*ball_y)--;
            break;
    }
}
void calculate_ball(int* ball_x, int* ball_y, int r1_pos_y, int r2_pos_y, int* flag_x, int* flag_y) {
    if (*ball_y == 23) *flag_y = 1;
    if (*ball_y == 1) *flag_y = 0;
    if (*ball_x == 66 && ((*ball_y == r2_pos_y) || (*ball_y == r2_pos_y - 1) || (*ball_y == r2_pos_y + 1))) *flag_x = 1;
    if (*ball_x == 14 && ((*ball_y == r1_pos_y) || (*ball_y == r1_pos_y - 1) || (*ball_y == r1_pos_y + 1))) *flag_x = 0;
}
void calculate_score(int* ball_x, int* ball_y, int* score_left, int* score_right) {
    if (*ball_x == 78) {
        *ball_x = 39;
        *ball_y = 12;
        (*score_left)++;
    }
    if (*ball_x == 1) {
        *ball_x = 39;
        *ball_y = 12;
        (*score_right)++;
    }
}
void print_field(int r1_pos_x, int r2_pos_x, int r1_pos_y, int r2_pos_y, int ball_x, int ball_y, int score_left, int score_right) {
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (i == 0 || i == COLS - 1) {
                printf("-");
            } else if (j == 0 || j == ROWS - 1) {
                printf("|");
            } else if ((j == r1_pos_x && (i == r1_pos_y || i == r1_pos_y + 1 || i == r1_pos_y - 1))) {
                printf("[");
            } else if ((j == r2_pos_x && (i == r2_pos_y || i == r2_pos_y + 1 || i == r2_pos_y - 1))) {
                printf("]");
            } else if (i == ball_y && j == ball_x) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d - %d\n", score_left, score_right);
}