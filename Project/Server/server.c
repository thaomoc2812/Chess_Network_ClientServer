#include <stdio.h>		// printf
#include <string.h>             // strlen
#include <stdlib.h>             // strlen
#include <sys/socket.h>		// socket
#include <arpa/inet.h>          // inet_addr
#include <unistd.h>             // write
#include "../Game/communication.c"
#include "../Game/chess.c"

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

// BOARD
int board[8][8] =
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
        if (board[line][column] < 0)
        {
            if (board[line][column] != -13) // ATE A PIECE OF THE OPPONENT
            {
                pieces_gamer2--;
                // PIECE IS KING?
                if(board[line][column] == 11)
                    exists_king_gamer2 = 0;
            }

            board[line][column] = board[line_ori][column_ori];
            board[line_ori][column_ori] = 13; // EMPTY

            for(l = 0; l < 8; l++)
            {
                for(c = 0; c < 8; c++)
                {
                    if(board[l][c] < 0)
                        board[l][c] *= -1;
                }
            }
        }
        else
            printf("Invalidates move!\n");
    }
    else if(gamer_ == 2)
    {
        if (board[line][column] < 0)
        {
            if (board[line][column] != -13) // ATE A PIECE OF THE OPPONENT
            {
                pieces_gamer1--;
                // PIECE IS KING?
                if(board[line][column] == 5)
                    exists_king_gamer1 = 0;
            }

            board[line][column] = board[line_ori][column_ori];
            board[line_ori][column_ori] = 13; // EMPTY

            for(l = 0; l < 8; l++)
            {
                for(c = 0; c < 8; c++)
                {
                    if(board[l][c] < 0)
                         board[l][c] *= -1;
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
    int i = 0;
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
	if(atoi(m[0]) == 1) // GAMER 1
        {
	    // REFRESH BOARD
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
		testMovePiece (c_ori, l_ori, board[l_ori][c_ori], board, 1);
		movePiece (c_ori, l_ori, c_prox, l_prox, 1);
		
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
    system("clear");
    struct sockaddr_in server, client;
    int socket_desc, client_sock, c, read_size, line_ori, column_ori, line_prox, column_prox, test_gamer = 0, test = 0, l, client_gamer;
    char client_message[2000], return_message[2000];
    strcpy(client_message, "1,0,0,0,0,0,0,0,0                    ");

    // Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1) { printf("Could not create socket"); }
    puts("Socket created");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;			// IPv4
    server.sin_addr.s_addr = INADDR_ANY;		// Qualquer endereco
    server.sin_port = htons( atoi(argv[1]) );		// Porta a esperar por conexoes
    client_gamer = 2;					// cliente jogador

    // Bind
    if( bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0) {
	perror("bind failed. Error");			// Print the error message
	return 1;
    }
    puts("bind done");

    listen(socket_desc , 3);//Listen

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    // Accept connection from an incoming client
    client_sock = accept (socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0) {
	perror("accept failed");
	return 1;
    }
    puts("Connection accepted");

    system("clear");
    strcpy(client_message, "");
    printf("\n######################### CHESS #########################");
    printf("\nDeveloper: Daniel Reis");
    printf("\nTeacher: Erick de Britto\n\n");
    printBoard (board, pieces_gamer1, pieces_gamer2); // PRINT BOARD

    // Receive a message from client
    while( (read_size = recv(client_sock, client_message, 2000, 0)) > 0 )
    {
	// Send the message back to client
	puts("\nReceived following message:");
	puts(client_message);
	
	// Verify message
	receivedVerifyMessage (client_message);

	strcpy(client_message, "");
	system("clear");
	printf("\n######################### CHESS #########################");
	printf("\nDeveloper: Daniel Reis");
        printf("\nTeacher: Erik de Britto\n\n");
	printBoard (board, pieces_gamer1, pieces_gamer2); // PRINT BOARD

	if(pieces_gamer1 == 0 || exists_king_gamer1 == 0) { // NOT EXISTS PIECES GAMER 1 OR NOT EXISTS THE KING OF GAMER 1
	    printGamer2 (); // GAMER 2 WIN
	    fflush(stdout);
	} else if(pieces_gamer2 == 0 || exists_king_gamer2 == 0) { // NOT EXISTS PIECES GAMER 2 OR NOT EXISTS THE KING OF GAMER 2
	    printGamer1 (); // GAMER 1 WIN
	    fflush(stdout);
	} else {
	    if(gamer == client_gamer) {
	        do {
	            do {
			system("clear");
			printf("\n######################### CHESS #########################");
			printf("\nDeveloper: Daniel Reis");
			printf("\nTeacher: Erik de Britto\n\n");
			printBoard (board, pieces_gamer1, pieces_gamer2); // PRINT BOARD
	                test = 0;
                        printf("Gamer 2 >>> Source (line column): ");
                    	scanf("%d%d",&line_ori,&column_ori);
                    	line_ori--;
                    	column_ori--;
		
		    	if(gamer == 1) {
		            if(board[line_ori][column_ori] >= 1 && board[line_ori][column_ori] <= 6) // IF PIECE OF GAMER 1
				test = 1;
		            else
				printf("Position invalidates!\n");
		    	}
		    	else if(gamer == 2) {
		            if(board[line_ori][column_ori] >= 7 && board[line_ori][column_ori] <= 12) // IF PIECE OF GAMER 2
				test = 1;
		            else
				printf("Position invalidates!\n");
		    	}
                    }while(line_ori < 0 || line_ori > 7 || column_ori < 0 || column_ori > 7 || test == 0);
		
		    test_gamer = testMovePiece (column_ori, line_ori, board[line_ori][column_ori], board, gamer);
		    if(test_gamer == 0)
		    	printf("Position invalidates!\n");

	    	}while(test_gamer == 0);

	        system("clear");
	        printf("\n######################### CHESS #########################");
	        printf("\nDeveloper: Daniel Reis");
                printf("\nTeacher: Erik de Britto\n\n");
	        printBoard (board, pieces_gamer1, pieces_gamer2); // PRINT BOARD

	        do {
	            do {
	                printf("Gamer 2 >>> Destiny (line column): ");
                        scanf("%d%d",&line_prox,&column_prox);
                        line_prox--;
                        column_prox--;
                    } while(line_prox < 0 || line_prox > 7 || column_prox < 0 || column_prox > 7);

		    if(board[line_prox][column_prox] < 0) {
		        test_gamer = 1;
			movePiece (column_ori, line_ori, column_prox, line_prox, 2);
			system("clear");
			printf("\n######################### CHESS #########################");
			printf("\nDeveloper: Daniel Reis");
			printf("\nTeacher: Erik de Britto\n\n");
			printBoard (board, pieces_gamer1, pieces_gamer2); // PRINT BOARD
		    }
		    else
		        test_gamer = 0;

		    if(test_gamer == 0)
		        printf("Position invalidates!\n");

	        }while(test_gamer == 0);

	        // Create message
	        snprintf (return_message, sizeof(return_message), "2,%d,%d,%d,%d,%d,%d,%d,%d", line_ori, column_ori, line_prox, column_prox, 
		    line_ori + line_prox, column_ori + column_prox, line_ori + column_prox, line_prox + column_prox);
	        // printf("> Sent: %s", message);
	    }
	}

	// Create message return server
	write (client_sock, return_message, strlen(return_message));

	// Clear buffer
	strcpy(client_message, "                              ");
    }

    if(read_size == 0)
    {
	puts("Client disconnected");
	printGamer2();
	fflush(stdout);
    }
    else if(read_size == -1)
	perror("recv failed");

    return 0;
}