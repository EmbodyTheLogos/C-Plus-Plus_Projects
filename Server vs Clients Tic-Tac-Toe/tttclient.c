/* HW3 problem 2b
Indu Chabada
Long Nguyen
*/

/* Internet domain, connection-oriented CLIENT   */

#include "tttlocal.h"

int who_won(int board[4][3]); //this function determines the winner of the game. 0 is the server, 1 is the client, and 2 is no one.
int board_full(int board[4][3]); //this function determines if the board is full or not. 0 is not full. 1 is full.

int main ( int argc, char *argv[]) {
  int             orig_sock, /* Original socket descriptor in client */
                  len;       /* Length of server address             */
  struct sockaddr_in
                   serv_adr; /* Internet address of server           */
  struct hostent    *host;   /* The host (server)                    */
  
  int board[4][3]; //board for the game. The first two elements in the last row contains the move of the client.
  				   //The last element of the board indicate whether or not a move has been validated or not. 0 mean invalid. 1 means valid.
  
  //initilize the board
  for (int i = 0; i < 4; i++)
  {
  	for (int j = 0; j < 3; j++)
  	{
  		board[i][j] = -9999;
	}
  }
  
  board[3][2] = 0; //Last element of the board. 0 means the user's move has not been accepted by the server
  
  
  int row; // row of user's move
  
  int column; // column of user's move

  printf("\n");
  
  printf("------Welcome to Socket Tic Tac Toe!------\n");
  printf("----Row and column start with 1, not 0----\n");
  printf("----------------You are X-----------------\n");
  printf("\n");
  

  if (argc != 2 ) {          /* Expect name of host on command line  */
    fprintf(stderr, "usage: %s server\n", argv[0]);
    exit(1);
  }
  host = gethostbyname(argv[1]);              /* Get host info       */
  if (host == (struct hostent *) NULL ) {
    perror("gethostbyname ");
    exit(2);
  }
  memset(&serv_adr, 0, sizeof( serv_adr));    /* Clear the structure */
  serv_adr.sin_family = AF_INET;              /* Set address type    */
  memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);  /* adr  */
  serv_adr.sin_port  = htons( PORT );         /* Use our fake port   */

  if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { /* SOCKET */
    perror("generate error");
    exit(3);
  }

/* CONNECT                                                           */
  if (connect( orig_sock, (struct sockaddr *)&serv_adr,
              sizeof(serv_adr)) < 0) {
    perror("connect error");
    exit(4);
  }
  
  //Changed do-while to while 
  while( buf[0] != '.'){
	write(fileno(stdout), "Enter [row, column] of the board (ex: 1, 1): ", 45);                    	/* Prompt user */
    
	if(len=read(fileno(stdin), buf, BUFSIZ) > 0 ){
    	
    	//process user's input
    	int invalid = 0; //0 meeans input is valid.
    	
    	row = -9999; //row has not been read from the user's new input
		column = -9999;	//column has not been read from the user's new input
		
		for (int i = 0; i < BUFSIZ; i++)
		{
			if (!isspace(buf[i]) && buf[i] != ',')
			{
				if (isdigit(buf[i]))
    				{
    					if (row == -9999){
						row = buf[i] - '0'; //convert char to digit
					}
					else if (column == -9999)
					{
						column = buf[i] - '0';
					}
					else //check if there are more than 2 digits
					{
						invalid = 1;
						break;
					}
					
				}
			}			
		}
		
		
		if (invalid == 0 && row != -9999 && column != -9999) //if the input is valid
		{
			board[3][0] = row-1;
			board[3][1] = column-1;
			
			//send the user's move and the current board to the server
			write(orig_sock, board, sizeof(board));
			
			if ((len=read(orig_sock, board, sizeof(board)) > 0)){       /* If returned */
			
				if (board[3][2] == 0) //check if the move has been accepted by the server
				{
					printf("Invalid Move. Please try again.\n");
				}
	
				//display the current board
				
				for(int i=0; i<3; i++){
					for(int j=0; j<3; j++){
						printf("|");
						
						if (board[i][j] == 1)
						{
							printf("X");
						}
						else if	(board[i][j] == 0)
						{
							printf("O");
						}
						else
						{
							printf(" ");
						}  	
			  			if (j == 2){
			  				printf("|");
						}
			  			
			  		}
			  		printf("\n");
			  	}
			  	
			  	//check the status of the game
				int winner = who_won(board);
				if ( winner == 2 && board_full(board) == 1)
				{
					printf("The game is tie\n");
					break; //end the game
				}
				else if (winner == 0)
				{
					printf("Server won\n");
					break; //end the game
				}
				else if (winner == 1)
				{
					printf("Client won\n");
					break; //end the game
				}
			}
				
		}
		else
		{
			printf("Invalid Input\n");
		}

		// clear up the current buf input
		for (int i = 0; i < sizeof(buf); i++)
		{
			buf[i] = ',';
		}

	}
  }
	close(orig_sock);
    exit(0);
}


/* This function determines the winner of the game. 0 is the server, 1 is the client, and 2 is no one.*/
int who_won(int board[4][3])
{
	
	//traverse the board row-wise    
   for (int i = 0; i < 3; i++)
   {	
   		if (board[i][0] != -9999)
   		{
   			if (board[i][0] == board[i][1] &&  board[i][1] == board[i][2])
   			{
   				if (board[i][0] == 0) //server move is 0
   				{
					return 0;
				}
				else  //client move is 1
				{
					return 1;

				}
				
			}
   			
		}

   }
   
    //traverse the board column-wise
   
   for (int k = 0; k < 3; k++)
   {	
   		if (board[0][k] != -9999)
   		{
   			if (board[0][k] == board[1][k] && board[1][k] == board[2][k])
   			{
   				if (board[0][k] == 0)
   				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
   			
		}

   }
   
   //check the board diagonallly (top to bottom || bottom to top)
   if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[2][0] == board[1][1] && board[1][1] == board[0][2]))
   {
   		if (board[1][1] != -9999)
   		{
   			if (board[1][1] == 0) 
   			{
				return 0;
			}
			else
			{
				return 1;
			}
		}		
	}
	
	return 2; //no one won
}


/* This function determines if the board is full or not.*/
int board_full(int board[4][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int k  = 0; k < 3; k++)
		{
			if (board[i][k] == -9999)
			{
				return 0;
			}
		}
	}
	
	return 1; //board is full	
}



