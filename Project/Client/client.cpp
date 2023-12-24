#include <stdio.h>          // printf
#include <string.h>         // strcpy
#include <stdlib.h>         // atoi
#include <string.h>         // strlen
#include <sys/socket.h>     // socket
#include <arpa/inet.h>      // inet_addr
#include <unistd.h>         // for close
#include "../Game/communication.c"
#include "../Game/chess.c"
#include "Home/home.hpp"

int HORSE_G1 = 1;
int TOWER_G1 = 2;
int BISPE_G1 = 3;
int QUEEN_G1 = 4;
int KING_G1 = 5;
int PEON_G1 = 6;
// PIECES >>> GAMER 1

int HORSE_G2 = 7;
int TOWER_G2 = 8;
int BISPE_G2 = 9;
int QUEEN_G2 = 10;
int KING_G2 = 11;
int PEON_G2 = 12;
// PIECES >>> GAMER 2

int EMPTY = 13;

// SCORE
int pieces_gamer1 = 16;
int pieces_gamer2 = 16;

// EXISTS KING
int exists_king_gamer1 = 1;
int exists_king_gamer2 = 1;

// MESSAGE
char* message;

// board1
int board1[8][8] =
{
    {/*TOWER_G2*/ 8, /*HORSE_G2*/ 7, /*BISPE_G2*/ 9, /*KING_G2*/ 11, /*QUEEN_G2*/ 10, /*BISPE_G2*/ 9, /*HORSE_G2*/ 7, /*TOWER_G2*/ 8},
    {/*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12, /*PEON_G2*/ 12},
    {/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
    {/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
    {/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
    {/*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13, /*EMPTY*/ 13},
    {/*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6, /*PEON_G1*/ 6},
    {/*TOWER_G1*/ 2, /*HORSE_G1*/ 1, /*BISPE_G1*/ 3, /*QUEEN_G1*/ 4, /*KING_G1*/ 5, /*BISPE_G1*/ 3, /*HORSE_G1*/ 1, /*TOWER_G1*/ 2}
};

int gamer = 1;

void movePiece(int column_ori, int line_ori, int column, int line, int gamer_)
{
    int l, c;

    if (gamer_ == 1)
    {
        if (board1[line][column] < 0)
        {
            if (board1[line][column] != -13) // ATE A PIECE OF THE OPPONENT
            {
                pieces_gamer2--;
                // PIECE IS KING?
                if(board1[line][column] == 11)
                    exists_king_gamer2 = 0;
            }

            board1[line][column] = board1[line_ori][column_ori];
            board1[line_ori][column_ori] = 13; // EMPTY

            for(l = 0; l < 8; l++)
            {
                for(c = 0; c < 8; c++)
                {
                    if(board1[l][c] < 0)
                        board1[l][c] *= -1;
                }
            }
        }
        else
            printf("Invalidates move!\n");
    }
    else if(gamer_ == 2)
    {
        if (board1[line][column] < 0)
        {
            if (board1[line][column] != -13) // ATE A PIECE OF THE OPPONENT
            {
                pieces_gamer1--;
                // PIECE IS KING?
                if(board1[line][column] == 5)
                    exists_king_gamer1 = 0;
            }

            board1[line][column] = board1[line_ori][column_ori];
            board1[line_ori][column_ori] = 13; // EMPTY

            for(l = 0; l < 8; l++)
            {
                for(c = 0; c < 8; c++)
                {
                    if(board1[l][c] < 0)
                         board1[l][c] *= -1;
                }
            }
        }
        else
            printf("Invalidates move!\n");
    }
}

int receivedVerifyMessage (char* message)
{
    char** m;
    m = strSplit(message, ',');
    int i;
    if(m != NULL)
    {
        if (m)
        {
            for (i = 0; *(m + i); i++)
                *(m + i);
        }
    }

    if(i == 9)
    {
	if(atoi(m[0]) == 2) // GAMER 2
        {
	    // REFRESH board1
	    int l_ori = atoi(m[1]);
	    int c_ori = atoi(m[2]);
	    int l_prox = atoi(m[3]);
	    int c_prox = atoi(m[4]);
	    int l_ori_s_l_prox = atoi(m[5]);
	    int c_ori_s_c_prox = atoi(m[6]);
	    int l_ori_s_c_prox = atoi(m[7]);
	    int l_prox_s_c_prox = atoi(m[8]);

	    if( l_ori_s_l_prox == (l_ori + l_prox) && c_ori_s_c_prox == (c_ori + c_prox) && l_ori_s_c_prox == (l_ori + c_prox) && l_prox_s_c_prox == (l_prox + c_prox) )
	    {
		testMovePiece (c_ori, l_ori, board1[l_ori][c_ori], board1, 2);
		movePiece (c_ori, l_ori, c_prox, l_prox, 2);
		
		// REFRESH GAMER
		if(gamer == 1)
		    gamer = 2;
		else if(gamer == 2)
		    gamer = 1;

		return 1;
	    }
	}
    }
    return 0;
}

int main(int argc , char *argv[]) {
    struct sockaddr_in server;
    int sock, r_connect, r_send, r_recv, line_ori, column_ori, line_prox, column_prox, test_gamer = 0, test = 0, l, c, client_gamer;
    char message[1000], server_reply[2000];

    // criando o socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
	printf("ERRO: nao foi possivel criar o socket");
	return 1;
    }

    printf("# SOCKET CRIADO #\n");

    // configurando o servidor de destino da conexao
    server.sin_family = AF_INET;				// IPv4
    server.sin_addr.s_addr = inet_addr(argv[1]); 		// endereco IP do servidor
    server.sin_port = htons(atoi(argv[2]));			// porta en que servidor irá aguardar conexoes
    client_gamer = 1;						// cliente jogador

    // conectando com o servidor


    if (r_connect < 0) {
	printf("ERRO: conexao com o servidor falhou");
	return 2;
    }
    printf("# CONNECTADO #\n");

    // comunicando com o servidor
    while(1) {
 	system("clear");
	strcpy(server_reply, "");
	printf("\n######################### CHESS #########################");
	
        home();
	printBoard (board1, pieces_gamer1, pieces_gamer2); // PRINT board1

	if(pieces_gamer1 == 0 || exists_king_gamer1 == 0) {// NOT EXISTS PIECES GAMER 1 OR NOT EXISTS THE KING OF GAMER 1
	    printGamer2 (); // GAMER 2 WIN
	    close(sock);
	} else if(pieces_gamer2 == 0 || exists_king_gamer2 == 0) {// NOT EXISTS PIECES GAMER 2 OR NOT EXISTS THE KING OF GAMER 2
	    printGamer1 (); // GAMER 1 WIN
	    close(sock);
	} else {
	    if(gamer == client_gamer) {
	        do {
	            do {
			system("clear");
			printf("\n######################### CHESS #########################");
			
            home();
			printBoard (board1, pieces_gamer1, pieces_gamer2); // PRINT board1
	                test = 0;
                        printf("Gamer 1 >>> Source (line column): ");
                    	scanf("%d%d",&line_ori,&column_ori);
                    	line_ori--;
                    	column_ori--;
		
		    	if(gamer == 1) {
		            if(board1[line_ori][column_ori] >= 1 && board1[line_ori][column_ori] <= 6) // IF PIECE OF GAMER 1
				test = 1;
		            else
				printf("Position invalidates!\n");
		    	}
		    	else if(gamer == 2) {
		            if(board1[line_ori][column_ori] >= 7 && board1[line_ori][column_ori] <= 12) // IF PIECE OF GAMER 2
				test = 1;
		            else
				printf("Position invalidates!\n");
		    	}
                    }while(line_ori < 0 || line_ori > 7 || column_ori < 0 || column_ori > 7 || test == 0);
		
		    test_gamer = testMovePiece (column_ori, line_ori, board1[line_ori][column_ori], board1, gamer);
		    if(test_gamer == 0)
		    	printf("Position invalidates!\n");

	    	}while(test_gamer == 0);

	        system("clear");
	        printf("\n######################### CHESS #########################");
	        
                home();
	        printBoard (board1, pieces_gamer1, pieces_gamer2); // PRINT board1

	        do {
	            do {
	                printf("Gamer 1 >>> Destiny (line column): ");
                        scanf("%d%d",&line_prox,&column_prox);
                        line_prox--;
                        column_prox--;
                    } while(line_prox < 0 || line_prox > 7 || column_prox < 0 || column_prox > 7);

		    if(board1[line_prox][column_prox] < 0) {
		        test_gamer = 1;
			movePiece (column_ori, line_ori, column_prox, line_prox, 1);
			system("clear");
			printf("\n######################### CHESS #########################");
			
            home();
			printBoard (board1, pieces_gamer1, pieces_gamer2); // PRINT board1
		    }
		    else
		        test_gamer = 0;

		    if(test_gamer == 0)
		        printf("Position invalidates!\n");

	        }while(test_gamer == 0);

	        // Create message
	        snprintf (message, sizeof(message), "1,%d,%d,%d,%d,%d,%d,%d,%d", line_ori, column_ori, line_prox, column_prox, 
		    line_ori + line_prox, column_ori + column_prox, line_ori + column_prox, line_prox + column_prox);
	        // printf("> Sent: %s", message);
	    }
	}

	// Send some data
	r_send = send(sock, message, strlen(message), 0);
	if(r_send < 0) {
	    printf("ERRO: envio falhou");
	    return 1;
	}

	// Receive a reply from the server
	r_recv = recv(sock , server_reply , 2000 , 0);
	if(r_recv < 0) {
	    printf("ERRO: recebimento falhou");
	    break;
	}

	// printf("\n> Received: %s", server_reply);

	// Verify message
	receivedVerifyMessage (server_reply);

	// Clear buffer
	strcpy(server_reply, "                              ");
    }

    printGamer1();
    close(sock);
    return 0;
}