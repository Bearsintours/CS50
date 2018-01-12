/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    int counter = (d*d) - 1;
    //Print numbers from d*d-1 to 0
    for(int i = 0; i < d; i++){
        for(int j = 0; j < d; j++){
            board[i][j] = counter;
            counter--;
        }
    }
    // Swap position of tile 1 and 2 if board contains odd numbers of tiles
    if((d*d - 1) % 2 != 0){
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Draw board columns
    for(int i = 0; i < d; i++){

        // Draw board rows
        for(int j = 0; j < d; j++){

            // Print "-" on board instead of 0
            if(board[i][j] == 0){
                printf(" -");
            }

            // Align numbers if 2 digits
            else{
                printf("%2i ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    int tile_value;

    // Iterate over rows
    for(int i = 0; i < d; i++){

        // Iterate over columns
        for(int j = 0; j < d; j++){

            // Get tile position if found
            if(board[i][j] == tile){

                // If blank below tile -> swap
                if(j < d-1 && board[i][j+1] == 0){
                    tile_value = tile;
                    board[i][j+1] = tile_value;
                    board[i][j] = 0;
                    return true;
                }
                // If blank above tile -> swap
                if(j > 0 && board[i][j-1] == 0){
                    tile_value = tile;
                    board[i][j-1] = tile_value;
                    board[i][j] = 0;
                    return true;
                }
                // If blank on the right -> swap
                if(i < d-1 && board[i+1][j] == 0){
                    tile_value = tile;
                    board[i+1][j] = tile_value;
                    board[i][j] = 0;
                    return true;
                }
                // If blank on the left -> swap
                if(i > 0 && board[i-1][j] == 0){
                    tile_value = tile;
                    board[i-1][j] = tile_value;
                    board[i][j] = 0;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    for(int i = 0; i < d-1; i++){
        for(int j = 0; j < d-1; j++){

            // Check if tiles are in increasing order from left to right and top to bottom
            if(board[i][j] > board[i][j+1] || board[i][j] > board[i+1][j]){
                return false;
            }
        }
    }
    return true;
}
