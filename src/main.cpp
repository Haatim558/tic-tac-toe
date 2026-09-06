#include <iostream>
#define OCCUPIED 15
#define OUT_OF_RANGE 12
int getWinner(const char (&grid)[3][3])
{
    int player1 = 1;
    int player2 = 2;
    // check rows
    for (int row = 0; row < 3; row++)
    {
        if (grid[row][0] == grid[row][1] && grid[row][1] == grid[row][2])
        {
            if (grid[row][0] == 'o')
                return player1;
            else
                return player2;
        }
    }
    // check columns
    for (int col = 0; col < 3; col++)
    {
        if (grid[0][col] == grid[1][col] && grid[1][col] == grid[2][col])
        {
            if (grid[0][col] == 'o')
                return player1;
            else
                return player2;
        }
    }

    bool diagonallyMatched = (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]);
    if (diagonallyMatched)
    {
        if (grid[1][1] == 'o')
            return player1;
        else
            return player2;
    }
    return 0;
}
int processChoice(int choice, char (&grid)[3][3], int player)
{
    if (choice < 1 || choice > 9)
    {
        return OUT_OF_RANGE;
    }
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    if (grid[row][col] == 'x' || grid[row][col] == 'o')
        return OCCUPIED;

    grid[row][col] = player == 1 ? 'o' : 'x';

    return 0;
}

bool isDraw(const char (&grid)[3][3])
{
    int counter = 0;
    for (auto &row : grid)
    {
        for (char c : row)
        {
            if (c == 'x' || c == 'o')
                counter++;
        }
    }
    if (counter == 9)
        return true;
    return false;
}
int main()
{
    std::string gridGraphics = R"(     
     |     |     
  1  |  2  |  3   
_____|_____|_____
     |     |     
  4  |  5  |  6  
_____|_____|_____
     |     |     
  7  |  8  |  9  
     |     |     
)";
    // initialize with different elements to eliminate duplicates
    char gameGrid[3][3]{{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}};
    int positions[] = {26, 32, 38, 81, 87, 93, 135, 141, 147};

    int player1 = 1;
    int player2 = 2;
    int currentPlayer = player1;

    int winner;
    do
    {
        int choice;
        system("cls");
        std::cout << gridGraphics;
        std::printf("player %d choose (%c)\n ", currentPlayer, currentPlayer == player1 ? 'o' : 'x');
        std::cin >> choice;
    
        if (processChoice(choice, gameGrid, currentPlayer) == OCCUPIED || processChoice(choice, gameGrid, currentPlayer) == OUT_OF_RANGE)
            continue;
        
        gridGraphics[positions[choice - 1]] = currentPlayer == player1 ? 'o' : 'x';
    
        if (currentPlayer == player1)
            currentPlayer = player2;
        else
            currentPlayer = player1;

    } while (((winner = getWinner(gameGrid)) != player1 && winner != player2) && !isDraw(gameGrid));
    system("cls");
    std::cout << gridGraphics;
    if (winner == 0)
        std::cout << "Draw.";
    if (winner == player1)
        std::cout << "Player 1 Wins!";
    if (winner == player2)
        std::cout << "Player 2 Wins!";
    return 0;
}
