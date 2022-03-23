/* HW3 problem 2b
Indu Chabada
Long Nguyen
*/

/* Internet domain, connection-oriented SERVER   */

#include "tttlocal.h"


int board_full(int board[4][3]); //this function determines if the board is full or not. 0 is not full. 1 is full.
int who_won(int board[4][3]); //this function determines the winner of the game. 0 is the server, 1 is the client, and 2 is no one.
int make_move(int board[4][3]); //this function determines the next move of the server.

int main ( void )  {
  int            orig_sock,  /* Original socket descriptor in server */
                 new_sock,   /* New socket descriptor from connect   */
                 clnt_len;   /* Length of client address             */
  struct sockaddr_in
                 clnt_adr,   /* Internet address of client & server  */
                 serv_adr;
  int            len, i;     /* Misc counters, etc.                  */
  
  int board[4][3]; //Board of the game. Use this to accept the board sent by the client.
  				   //The first two elements in the last row contains the position of client's move.
  				   //The last element of the board indicate whether or not a move has been validated or not. 0 mean invalid. 1 means valid.
  				
  
  if ((orig_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("generate error");
    exit(1);
  }
  memset ( &serv_adr, 0, sizeof(serv_adr) );  /* Clear structure     */
  serv_adr.sin_family       = AF_INET;        /* Set address type    */
  serv_adr.sin_addr.s_addr  = htonl(INADDR_ANY); /* Any interface    */
  serv_adr.sin_port         = htons(PORT);    /* Use our fake port   */
                                              /* Now BIND            */
  if (bind( orig_sock, (struct sockaddr *) &serv_adr,  
            sizeof(serv_adr)) <0) {
    perror("bind error");
  close(orig_sock);
  exit(2);
  }
  if (listen(orig_sock, 5) <0) {              /* LISTEN              */
    perror("listen error");
    exit(3);
  }
  do {
  clnt_len = sizeof(clnt_adr);
    if ((new_sock = accept ( orig_sock, (struct sockaddr *) &clnt_adr,
                             &clnt_len)) < 0)  {      /* ACCEPT       */
    perror("accept error");
    close(orig_sock);
    exit(4);
  }
  if ( fork( ) == 0)  {                      /* In CHILD process     */

    // In the server, buf is not used to read the input. It is used for ending the game
    // server sets buf[0] = '.' to end the game
    while ( (len=read(new_sock, board, BUFSIZ)) > 0) {
    
	/*  We replace changing the case of the message with our code here.*/ 
 	
	 	//validate user move
    	int row = board[3][0];
      	int column = board[3][1];
      
     	if ( (0 <= row < 3) && (0 <= column < 3) && (board[row][column] == -9999)) //move is valid
      	{
			board[row][column] = 1; //1 is the client's move, 0 is the server move.
			board[3][2] = 1; // this means the user move has been validated
			
			//check the status of the game
			int winner = who_won(board);
			if ( winner == 2 && board_full(board) == 1)
			{
				//printf("The game is tie\n");
				buf[0] = '.'; //end the game
			}
			else if (winner == 0)
			{
				//printf("Server won\n");
				buf[0] = '.'; //end the game
			}
			else if (winner == 1)
			{
				//printf("Client won\n");
				buf[0] = '.'; //end the game
			}
			
			
			//server making move
			if (buf[0] != '.')
			{
				int next_move = make_move(board); //determine the position of the next move
				/*
				    |0|1|2|
					|3|4|5|
					|6|7|8|
					See next_move(int board[4][3]) method for more details.
				*/
	
				column = next_move % 3;
				row = (next_move - column) / 3;
				board[row][column] = 0;
				
				//check the status of the game again since the board has been updated
				winner = who_won(board);
				if ( winner == 2 && board_full(board) == 1)
				{
					//printf("The game is tie\n");
					buf[0] = '.'; //end the game
				}
				else if (winner == 0)
				{
					//printf("Server won\n");
					buf[0] = '.'; //end the game
				}
				else if (winner == 1)
				{
					//printf("Client won\n");
					buf[0] = '.'; //end the game
				}
			}
			
		
	  	}
	  	else //move is invalid
	  	{
	  		board[3][2] = 0; //this means the user move is invalid
	  	}
       
	
	  write(new_sock, board, sizeof(board));             /* write it back        */
      if ( buf[0] == '.' ) break;            /* are we done yet?     */
    }
    close(new_sock);                         /* In CHILD process     */
    exit( 0);
  } else close(new_sock);                    /* In PARENT process    */
  } while( 1 );                              /* FOREVER              */
}


/*this function determines the winner of the game. 0 is the server, 1 is the client, and 2 is no one.*/
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



/*Server making move base on what-if score. Each position in the board has a what-if score associate with it.
	 A score of 4 means we will win the game if we make that move
	 3 means we block the winning move of the enemy (winning move means making that move will win the game).
	 2 means we want to form one 2-adjacent-cell row, column, or diagonal.
	 1 means there is nothing happening. 
	 Heuristics 1 (h1): First move of server will be the middle of the board if possible. Otherwise, pick one of the corner.
				   h1 prevents the corner strategy.
	 See the corner strategy of Tic Tac Toe here: https://www.youtube.com/watch?v=OmC07DvEayY
*/ 

int make_move(int board[4][3])
{
	//From the server perspective, the board has 9 positions as follow:
	/*
	
	|0|1|2|
	|3|4|5|
	|6|7|8|
	
	This function return one position of the above board where position = (row * 3) + column
		
	*/
	
	//check for a what-if score of 4
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (board[i][k] == -9999)
			{
				
				int old_value = board[i][k];
				board[i][k] = 0; //make a what-if move for server
				int winner = who_won(board);
				if (winner == 0)
				{
					return (i * 3) + k;
				}
				

				board[i][k] = old_value; //restore old value of a position in the board.
			
			}
			
		}
	}
	
	//check for a what-if score of 3
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			if (board[i][k] == -9999)
			{
				int old_value = board[i][k];
				board[i][k] = 1; //make a what-if move for client
				int winner = who_won(board);
				if (winner == 1)
				{
					return (i * 3) + k;
				}

				board[i][k] = old_value; //restore old value of a position in the board.
			
			}
			
		}
	}
	
	
	//check for a what-if score of 2

	//row-wise
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 2; k++)
		{
			if(board[i][k] == -9999)
			{
				if(board[i][k+1] == 0)
				{
					return (i * 3) + k;
					
				}
			}
		}
		
	}
	
	//column-wise
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < 2; i++)
		{
			if(board[i][k] == -9999)
			{
				if(board[i+1][k] == 0)
				{
					return (i * 3) + k;

				}
			}
		}
		
	}
	
	//diagonally (top to bottom)
	
	for (int i = 0; i < 2; i++ )
	{
		if (board[i][i] == -9999)
		{
			if(board[i+1][i+1] == 0)
			{
				return (i * 3) + i;
			}
		}
	}
	
	//diagonally (bottom to top)
	for (int i = 1; i >= 0; i-- )
	{
		for (int k = 0; k < 2; k++)
		{
			if (board[i][k] == -9999)
			{
				if (board[i+1][k+1] == 0)
				{
					return (i * 3) + k;
				}
			}
		}
	}

	
	//what-if score of 1. Use heuristic 1:
	
	if(board[1][1] != -9999)
	{
		
		//pick the corner first if mid center is already picked.
		if (board[0][0] == -9999)
		{
			return 0;
		}
		else if(board[0][2] == -9999)
		{
			return 2;
		}
		else if (board[2][0] == -9999)
		{
			return 6;
		}
		else if (board[2][2] == -9999)
		{
			return 8;
		}
		
		//traverse through and pick any position
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (board[i][k] == -9999){
					return (i * 3) + k;
				}
			}
		}
	}
	else
	{
		return 4; //pick the center of the board
	}
		
}
