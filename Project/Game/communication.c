#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void printBoard(int board[8][8], int pieces_gamer1, int pieces_gamer2)
{
    int line, column;
    for(line = -1; line < 8; line++)
    {
        if(line >= 0)
            printf("  %d ", line + 1);
        else
            printf("   ");

        for(column = 0; column < 8; column++)
        {
            if(line >= 0)
            {
                switch(board[line][column])
                {
                case 1: printf("  H "); break; 		// HORSE_G1
                case 2: printf("  T "); break; 		// TOWER_G1
                case 3: printf("  B "); break;		// BISPE_G1
                case 4: printf("  Q "); break;		// QUEEN_G1
                case 5: printf("  K "); break;		// KING_G1
                case 6: printf("  P "); break;		// PEON_G1

                case 7: printf("  h "); break; 		// HORSE_G2
                case 8: printf("  t "); break; 		// TOWER_G2
                case 9: printf("  b "); break;		// BISPE_G2
                case 10: printf("  q "); break;		// QUEEN_G2
                case 11: printf("  k "); break;		// KING_G2
                case 12: printf("  p ");break;		// PEON_G2

                case 13: printf("    "); break;		// EMPTY

                case -1: printf(" -H "); break; 	// HORSE_G1
                case -2: printf(" -T "); break; 	// TOWER_G1
                case -3: printf(" -B "); break;		// BISPE_G1
                case -4: printf(" -Q "); break;		// QUEEN_G1
                case -5: printf(" -K "); break;		// KING_G1
                case -6: printf(" -P "); break;		// PEON_G1

                case -7: printf(" -h "); break; 	// HORSE_G2
                case -8: printf(" -t "); break; 	// TOWER_G2
                case -9: printf(" -b "); break;		// BISPE_G2
                case -10: printf(" -q "); break;	// QUEEN_G2
                case -11: printf(" -k "); break;	// KING_G2
                case -12: printf(" -p "); break;	// PEON_G2

                case -13: printf(" -- "); break;	// EMPTY
                }
            }
            else
                printf("   %d", column + 1);
            if(column == 7 && line == -1)
                printf("                           -----------------------------");
            else if(column == 7 && line == 0)
                printf("                          |           SCORE           |");
            else if(column == 7 && line == 1)
                printf("                          |                           |");
            else if(column == 7 && line == 2) // CONSIDERS HOW MANY PARTS THE GAMER 1 GAMER COME 2 (16 = TOTAL PIECES)
            {
                if((16 - pieces_gamer2) <= 10)
                    printf("                          |        GAMER 1 = %d        |", (16 - pieces_gamer2));
                else
                    printf("                          |        GAMER 1 = %d       |", (16 - pieces_gamer2));
            }
            else if(column == 7 && line == 3) // CONSIDERS HOW MANY PARTS THE GAMER 1 GAMER COME 2 (16 = TOTAL PIECES)
            {
                if((16 - pieces_gamer2) <= 10)
                    printf("                          |        GAMER 2 = %d        |", (16 - pieces_gamer1));
                else
                    printf("                          |        GAMER 2 = %d       |", (16 - pieces_gamer1));
            }
            else if(column == 7 && line == 4)

                printf("                          |                           |");
            else if(column == 7 && line == 5)
                printf("                          -----------------------------");
        }
        printf("\n");
    }
    printf("\n\n");
}

char** strSplit(char* a_str, const char a_delim)
{
    char** result = 0;
    if(a_str != NULL)
    {
        size_t count = 0;
        char* tmp = a_str;
        char* last_comma = 0;
        char delim[2];
        delim[0] = a_delim;
        delim[1] = 0;

        // Count how many elements will be extracted
        while (*tmp)
        {
            if (a_delim == *tmp)
            {
                count++;
                last_comma = tmp;
            }
            tmp++;
        }
        count += last_comma < (a_str + strlen(a_str) - 1); // Add space for trailing token
        count++; // Add space for terminating null string so caller knows where the list of returned strings ends
        result = (char **)malloc(sizeof(char*) * count);

        if (result)
        {
            size_t idx = 0;
            char* token = strtok(a_str, delim);

            while (token)
            {
                assert(idx < count);
                *(result + idx++) = strdup(token);
                token = strtok(0, delim);
            }
            assert(idx == count - 1);
            *(result + idx) = 0;
        }
    }
    return result;
}

void printGamer1()
{
    printf("-------------------------------");
    printf("           GAMER 1 WIN         ");
    printf("-------------------------------\n");
}

void printGamer2()
{
    printf("-------------------------------");
    printf("          GAMER 2 WIN          ");
    printf("-------------------------------\n");
}
