#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

char ordercheck(char turn)
{
    system("cls");

    printf("\tКрестики-нолики.\n");

    printf("\nX -- первый игрок.");
    printf("\nO -- второй игрок.\n\n");

    printf("\t  1 | 2 | 3  \n\n");

    printf("\t  4 | 5 | 6  \n\n");

    printf("\t  7 | 8 | 9  \n");

    if (turn != '1' && turn != '2')
    {
        printf("\nНеверный ввод! Повтори ввод очереди хода: ");
        fflush(stdin);
        scanf("%c", &turn);

        turn = ordercheck(turn);
    }

    fflush(stdin);

    return turn;
}

void update(char board[9])
{
    system("cls");

    printf("\tКрестики-нолики.\n");

    printf("\nX -- первый игрок.");
    printf("\nO -- второй игрок.\n\n");

    printf("\t  %c | %c | %c  \n\n", board[0], board[1], board[2]);

    printf("\t  %c | %c | %c  \n\n", board[3], board[4], board[5]);

    printf("\t  %c | %c | %c  \n", board[6], board[7], board[8]);
}

void outfield(int field[9], char board[9], int order)
{
    for (int i = 0; i < 9; ++i)
        switch (field[i])
        {
        case 1:
            if (order == 1)
                board[i] = 'O';
            if (order == 2)
                board[i] = 'X';
            break;
        case -1:
            if (order == 1)
                board[i] = 'X';
            if (order == 2)
                board[i] = 'O';
            break;
        }
}

int win(int field[9])
{
    int row[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    int i;
    for (i = 0; i < 8; ++i)
    {
        if (field[row[i][0]] == field[row[i][1]] && field[row[i][1]] == field[row[i][2]] && field[row[i][0]] != 0)
            return field[row[i][0]];
    }

    return 0;
}

char usercheck(char move, int field[9], char board[9], int order)
{
    int mv;

    if (move >= '1' && move <= '9')
    {
        mv = move - '0';
        mv = mv - 1;

        if (field[mv] != 0)
        {
            outfield(field, board, order);
            update(board);

            printf("\nКлетка занята! Повтори ввод номера клетки 1..9: ");
            fflush(stdin);
            scanf("%c", &move);

            move = usercheck(move, field, board, order);
        }
    }
    else
    {
        outfield(field, board, order);
        update(board);

        printf("\nНеверный ввод! Повтори ввод номера клетки 1..9: ");
        fflush(stdin);
        scanf("%c", &move);

        move = usercheck(move, field, board, order);
    }

    return move;
}

void user(int field[9], char board[9], int order)
{
    char move;
    int mv;

    fflush(stdin);
    printf("\nВведи номер клетки 1..9: ");
    scanf("%c", &move);

    move = usercheck(move, field, board, order);

    mv = move - '0';
    mv = mv - 1;

    field[mv] = -1;
}

int minimax(int field[9], int player)
{
    int step;
    int lots = 0;
    int maxscore = -9;
    int i;
    int score;
    int sss = -1;

    for (i = 0; i < 9; ++i)
        if (field[i] == 0)
            lots = lots + 1;

    if (win(field) != 0)
        return player * win(field) * (lots + 1);

    for (step = 0; step < 9; ++step)
    {
        if (field[step] == 0)
        {
            field[step] = player;
            score = -minimax(field, -1 * player);
            field[step] = 0;

            if (score > maxscore)
            {
                maxscore = score;
                sss = step;
            }
        }
    }

    if (sss == -1)
        return 0;

    if (lots == 0)
        return player * win(field) * (lots + 1);

    return maxscore;
}

void computer(int field[9], int turn)
{
    int copyfield[9] = {field[0], field[1], field[2],
                        field[3], field[4], field[5],
                        field[6], field[7], field[8]};

    int score;
    int maxscore = -9;
    int step;
    int maxslot = -1;

    for (step = 0; step < 9; ++step)
    {
        if (copyfield[step] == 0)
        {
            copyfield[step] = 1;
            score = -minimax(copyfield, -1);
            copyfield[step] = 0;

            if (score > maxscore)
            {
                maxscore = score;
                maxslot = step;
            }
        }
    }

    if (turn == 0)
        maxslot = rand() % (9);

    field[maxslot] = 1;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    int field[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int order = 1;
    int step;

    system("cls");

    printf("\tКрестики-нолики.\n");

    printf("\nX -- первый игрок.");
    printf("\nO -- второй игрок.\n\n");

    printf("\t  1 | 2 | 3  \n\n");

    printf("\t  4 | 5 | 6  \n\n");

    printf("\t  7 | 8 | 9  \n");

    printf("\n Игроки по очереди ставят на свободные клетки поля 3х3 знаки (один всегда крестики, другой всегда нолики).");
    printf("\n Первый, выстроивший в ряд 3 своих фигуры по вертикали, горизонтали или диагонали, выигрывает. ");
    printf("\n Внимание! При вводе строки считывается только первый символ. ");

    printf("\n\n Введите любой символ, чтобы продолжить ");
    getchar();
    fflush(stdin);

    char turn;
    printf("\n Выберите очередь хода. 1 или 2: ");
    scanf("%c", &turn);

    turn = ordercheck(turn);

    order = turn - '0';

    for (step = 0; step < 9 && win(field) == 0; ++step)
    {
        outfield(field, board, order);
        update(board);
        if ((step + order) % 2 == 0)
            computer(field, step);
        else
            user(field, board, order);
    }

    fflush(stdin);

    switch (win(field))
    {
    case 1:
        outfield(field, board, order);
        update(board);
        printf("\nПроигрыш! Удачи в следующий раз!\n\nДля выхода из игры введите любой символ ");
        getchar();
        return 0;
    case -1:
        outfield(field, board, order);
        update(board);
        printf("\nПобеда!\n\nДля выхода из игры введите любой символ ");
        getchar();
        return 0;
    case 0:
        outfield(field, board, order);
        update(board);
        printf("\nНичья! Удачи в следующий раз!\n\nДля выхода из игры введите любой символ ");
        getchar();
        return 0;
    }

    return 1;
}
