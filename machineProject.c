#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "interface.h"

void save_time(int playTime) 
{
    FILE *file = fopen("leaderboard.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%d\n", playTime);
    fclose(file);
}

int load_time() 
{
    FILE *file = fopen("leaderboard.txt", "r");
    int playTime = 0;
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }
    fscanf(file, "%d", &playTime);
    fclose(file);
    return playTime;
}

int getArrowKey() //scans input from keyboard and returns an integer
{
    int ch = _getch();
    if (ch == 0 || ch == 224) {
        ch = _getch();
        switch (ch) {
            case 72: return 1; // Up arrow
            case 80: return 2; // Down arrow
            case 75: return 3; // Left arrow
            case 77: return 4; // Right arrow
            default: return 0; // Invalid arrow
        }
    }
    else if(ch == 13)
    { 
        return 5;
    }
    else if(ch == 27)
    {
        return 6;
    }
    return 0; // Not an arrow key
}

void drawSymbol(int draw) //outputs a symbol from unicode
{
    SetConsoleOutputCP(CP_UTF8); // enable unicode
    if (draw == 0) //circle
    {
        printf("\u25CF");
    }
    else if (draw == 1) //up arrow
    {
        printf("\u2191");
    }
    else if (draw == 2) // down arrow
    {
        printf("\u2193");
    }
    else if (draw == 3) //left arrow
    {
        printf("\u2190");
    }
    else if (draw == 4) //right arrow
    {
        printf("\u2192");
    }
    
    SetConsoleOutputCP(437); //disable unicode
}

void displayMainMenu() //displays main menu interface
{
    int i;
    int j;

	iClear(0, 0, 100, 30);
	printf("    Welcome to Mastermind!\n");
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 29; j++)
        {

            if(i == 0 && j == 0)
            {
                printf("%c", 201);
            }
            else if(i == 0 && j < 28)
            {
                printf("%c", 205);
            }
            else if(i == 0 && j == 28)
            {
                printf("%c\n", 187);
            }
            else if(i < 8 && j == 0 || i < 8 && j == 28)
            {
                printf("%c", 186);
                if (j == 28)
                {
                printf("\n");
                }
            }
            else if(i == 8 && j == 0)
            {
                printf("%c", 200);
            }
            else if(i == 8 && j < 28)
            {
                printf("%c", 205);
            }
            else if(i == 8 && j == 28)
            {
                printf("%c\n", 188);
            }
            else if (i == 3 && j > 9 && j < 18 || i == 5 && j > 9 && j < 18)
            {
                printf("%c", 196);
            }
            else
            {
                printf(" ");
            }
        }
    }
    iClear(12, 3, 1, 1);
    iSetColor(I_COLOR_RED);
	printf("PLAY");
    iClear(11, 5, 1, 1);
    iSetColor(I_COLOR_GREEN);
	printf("OPTION");
    iClear(12, 7, 1, 1);
    iSetColor(I_COLOR_BLUE);
	printf("QUIT");
    iSetColor(I_COLOR_WHITE);
    iClear(0, 10, 1, 1);
    printf("Controls: \n");
    printf("(");
    drawSymbol(1);
    printf(")");
    printf(" Up Arrow key - to go up when selecting\n");
    printf("(");
    drawSymbol(2);
    printf(")");
    printf(" Down Arrow key - to go down when selecting\n");
    printf("(");
    drawSymbol(3);
    printf(")");
    printf(" Left Arrow key - to go left when selecting\n");
    printf("(");
    drawSymbol(4);
    printf(")");
    printf(" Right Arrow key - to go right when selecting\n");
    printf("Enter key - to input your selection\n");
}

void displayOptions() //displays options interface
{
	iClear(0, 0, 100, 10);
	printf("------------------------\n");
	printf(" Game Mode \n");
	printf(" Random Mode - Generates a random secrect code\n");
	printf(" Custom Mode - A user inputs a secret code\n");
	printf("------------------------\n");
	printf(" Number of Rounds (3-15): \n");
	printf("------------------------\n");
    printf(" Return to Main Menu \n");
    printf("------------------------\n");
}

void displayEndScreen() //displays the ending screen
{
    int i;
    int j;

    iClear(0, 0, 100, 30);

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 31; j++)
        {
            if (j > 0)
            {
                switch (i)
                {
                    case 1: 
                        iSetColor(I_COLOR_RED);
                        break;
                    case 2: 
                        iSetColor(I_COLOR_YELLOW);
                        break;
                    case 3: 
                        iSetColor(I_COLOR_GREEN);
                        break;
                    case 5: 
                        iSetColor(I_COLOR_CYAN);
                        break;
                    case 6: 
                        iSetColor(I_COLOR_BLUE);
                        break;
                    case 7: 
                        iSetColor(I_COLOR_PURPLE);
                        break;
                    default: 
                        iSetColor(I_COLOR_WHITE);
                        break;
                }
            }
            if (j == 30)
            {
                iSetColor(I_COLOR_WHITE);
            }

            if (i == 0)
            {
                printf("%c", 220);
                if (j == 30)
                {
                printf("\n");
                }
            }
            else if (i == 8)
            {
                printf("%c", 223);
            }
            else 
            {
                printf("%c", 219);
                if (j == 30)
                {
                printf("\n");
                }
            }
        }
    }

    iSetColor(I_COLOR_WHITE);
    iClear(3, 4, 24, 1);
    printf(" Thank you for playing! ");

    iClear(0, 9, 1, 1);
    printf("\nCredits: \n\n");
    printf("Created by: Alfred Na%cawa | S13 | CCPROG1\n\n", 164);
}

void selectOptions(int *gamemode, int *rounds) //user inputs options
{
    int gameMode = *gamemode;
    int numOfRounds = *rounds;
    int input = 0;
    int goBack = 0;
    int option = 1;
    int pass = 0;

    if (gameMode == 0)
    {
        iClear(0, 2, 1, 1);
        printf("[");
        iClear(12, 2, 1, 1);
        printf("]");
    }
    else if (gameMode != 0)
    {
        iClear(0, 3, 1, 1);
        printf("[");
        iClear(12, 3, 1, 1);
        printf("]");
    }

    iClear(26, 5, 6, 1);
    printf("  %d", numOfRounds);

    while(goBack != 1)
    {
        input = 0;
        while(input != 5)
        {
            iClear(0, 1, 1, 1);
            iClear(0, 5, 1, 1);
            iClear(0, 7, 1, 1);

            if (option == 1)
            {
                iClear(0, 1, 1, 1);
                printf(">");
            }
            else if (option == 2)
            {
                iClear(0, 5, 1, 1);
                printf(">");
            }
            else if (option == 3)
            {
                iClear(0, 7, 1, 1);
                printf(">");
            }
            
            input = getArrowKey();

            switch(input)
            {
                case 1: option--;
                        break;
                case 2: option++; 
                        break;
            }
            
            if(option < 1)
            {
                option = 3;
            }
            else if(option > 3)
            {
                option = 1;
            }
        }
        iClear(0, 5, 1, 1);
        iClear(0, 7, 1, 1);
        iClear(0, 1, 1, 1);

        if (option == 1)
        {
            input = 0;
            while(input != 5)
            {
                // iClear(0, 10, 100, 1);
                // printf("%d\n", gameMode);

                iClear(0, 2, 1, 1);
                iClear(12, 2, 1, 1);
                iClear(0, 3, 1, 1);
                iClear(12, 3, 1, 1);

                if (gameMode == 0)
                {
                    iClear(0, 2, 1, 1);
                    printf("[");
                    iClear(12, 2, 1, 1);
                    printf("]");
                }
                else if (gameMode != 0)
                {
                    iClear(0, 3, 1, 1);
                    printf("[");
                    iClear(12, 3, 1, 1);
                    printf("]");
                }
                
                input = getArrowKey();

                switch(input)
                {
                    case 1: gameMode--;
                            break;
                    case 2: gameMode++; 
                            break;
                }
                
            gameMode = gameMode % 2;
            }
        }
        else if (option == 2)
        {
            input = 0;
            while(input != 5)
            {
                iClear(26, 5, 6, 1);
                printf("%c %d %c", 174, numOfRounds, 175);
                
                input = getArrowKey();

                switch(input)
                {
                    case 2:
                    case 3: numOfRounds--;
                            break;
                    case 1:
                    case 4: numOfRounds++; 
                            break;
                }
                
                if(numOfRounds < 3)
                {
                    numOfRounds = 15;
                }
                else if(numOfRounds > 15)
                {
                    numOfRounds = 3;
                }
            }
            iClear(26, 5, 6, 1);
            printf("  %d", numOfRounds);
        }
        else if (option == 3)
        {
            goBack = 1;
        }
    }

    *gamemode = gameMode;
    *rounds = numOfRounds;
}

int codeSize(int size) //tweak code length
{
    int input;

    size = 4;

	iClear(0, 0, 100, 30);
    printf("Enter the size of code (2-6): ");
    
    input = 0;
    while(input != 5)
    {
        iClear(30, 0, 4, 1);
        printf("%c %d %c", 174, size, 175);
        
        input = getArrowKey();

        switch(input)
        {
            case 2:
            case 3: size--;
                    break;
            case 1:
            case 4: size++; 
                    break;
        }
        
        if(size < 2)
        {
            size = 6;
        }
        else if(size > 6)
        {
            size = 2;
        }
    }

	return size;
}

void makeCode(int code [], int size, int numColors) // function that creates a random code for the game
{
	srand(time(0));

	for (int i = 0; i < size; i++) // assigns the random number to a color
	{
		code [i] = rand() % numColors;
        
	}
}

void checkGuess(int guess [],int code [], int correctPositions [], int correctColors [], int size) //function that checks the user input to the code 
{
	int i;
	int j;
	int matchedPosition [size];
	int matchedColors [size];

	for (i = 0; i < size; i++) //initializes the variables
	{
		correctPositions [i] = 0;
		correctColors [i] = 0;
		matchedPosition [i] = 0;
		matchedColors [i] = 0;
	}

	for (i = 0; i < size; i++) //checks for correct position
	{
		if (guess [i] == code [i])
		{
		correctPositions [i] = 1;
		matchedPosition [i] = 1;
		matchedColors [i] = 1;
		}
	}

	for (i = 0; i < size; i++) //checks for correct colors
	{
		if (matchedPosition [i] != 1)
		{
			for (j = 0; j < size; j++)
			{
				if (matchedPosition [j] != 1 && guess [i] == code [j] && matchedColors [j] != 1)
				{
					correctColors [i] = 1;
					matchedColors [j] = 1;
                    break;
				}
			}
		}
	}
}

void textColor(char colorSet) //changes text color based on the input
{

    switch(colorSet)
    {
        case 0: iSetColor(I_COLOR_RED);
                break;
        case 1: iSetColor(I_COLOR_YELLOW);
                break;
        case 2: iSetColor(I_COLOR_GREEN);
                break;
        case 3: iSetColor(I_COLOR_BLUE);
                break;
        case 4: iSetColor(I_COLOR_CYAN);
                break;
        case 5: iSetColor(I_COLOR_PURPLE);
                break;
        case 6: iSetColor(I_COLOR_WHITE);
                break;
    }
}

int confirmMenu() //function for an escape sequence during the game
{
    int input;
    int goMainMenu;

    iClear(0, 6, 100, 1);
    printf("Are you sure you want to quit?");
    iClear(0, 7, 100, 1);
    printf(" Yes    No");

    input = 0;
    goMainMenu = 0;
    while(input != 5)
    {
        iClear(0, 7, 1, 1);
        iClear(7, 7, 1, 1);

        if (goMainMenu == 0)
        {
            iClear(0, 7, 1, 1);
            printf(">");
        }
        else if (goMainMenu != 0)
        {
            iClear(7, 7, 1, 1);
            printf(">");
        }
        
        input = getArrowKey();

        switch(input)
        {
            case 3: goMainMenu--;
                    break;
            case 4: goMainMenu++; 
                    break;
        }
        
        goMainMenu = goMainMenu % 2;
    }

    if (goMainMenu == 0)
    {
        return 1;
    }
    else if (goMainMenu != 0)
    {
        return 0;
    }
}

void startGame(int gamemode, int rounds, int *menuPos) //starts the game
{
    int size;
	char colors[] = {'R', 'Y', 'G', 'B', 'C', 'P'};
	int numColors = sizeof(colors);
	int win = 0;

	size = codeSize(size);

	int guess [size];
	int code [size];
	int correctPositions [size];
	int correctColors [size];
    int input;
	int positionNum;
	int colorNum;
    int cursorPos;
    int codePos;
    int codeClear;
    int guessClear;
    int goMainMenu;
    int guesses = 0;
	int i;
	int j;

    iClear(0, 0, 100, 2);
	printf("Colors: ");
	for(i = 0; i < numColors; i++)
	{
        textColor(i);
		printf("%c", colors [i]);
        switch(i)
        {
            case 0:
                printf("ED ");
                break;
            case 1:
                printf("ELLOW ");
                break;
            case 2:
                printf("REEN ");
                break;
            case 3:
                printf("LUE ");
                break;
            case 4:
                printf("YAN ");
                break;
            case 5:
                printf("URPLE ");
                break;
        }
	}
    iSetColor(I_COLOR_WHITE);
    printf("\n");

    if(gamemode == 0)
    {
        printf("Gamemode: Random Mode\n");
    }
    else if(gamemode == 1)
    {
        printf("Gamemode: Custom Mode\n");
    }

	printf("Number of rounds: %d\n", rounds);

    if(gamemode == 0)
    {
        makeCode(code, size, numColors);
    }
    else if(gamemode == 1)
    {
        printf("Enter Secret Code: ");

        input = 0;
        codePos = 0;

        for (i = 0; i < size; i++)
        {
            code [i] = 0;
        }

        for (i = 0; i < size; i++)
        {
            textColor(code [i]);
            drawSymbol(0);
            printf("  ");
        }
        iSetColor(I_COLOR_WHITE);

        while(input != 5)
        {
            codeClear = 19 + 3 * codePos;

            iClear(codeClear + 2, 3, 1, 1);
            iClear(codeClear + 4, 3, 1, 1);

            if (codeClear == 19)
            {
                iClear(18 + 3 * (size - 1), 3, 1, 1);
                iClear(20 + 3 * (size - 1), 3, 1, 1);
            }
            else if(codeClear == (19 + 3 * (size - 1)))
            {
                iClear(18, 3, 1, 1);
                iClear(20, 3, 1, 1);
                iClear(codeClear - 2, 3, 1, 1);
                iClear(codeClear - 4, 3, 1, 1);
            } 
            else 
            {
                iClear(codeClear - 2, 3, 1, 1);
                iClear(codeClear - 4, 3, 1, 1);
            }
            iClear(codeClear - 1, 3, 1, 1);
            printf("[");
            iClear(codeClear + 1, 3, 1, 1);
            printf("]");

            switch (code [codePos])
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    iClear(codeClear, 3, 1, 1);    
                    textColor(code [codePos]);
                    drawSymbol(0);
                    iSetColor(I_COLOR_WHITE);
                    break;
            }
            
            input = getArrowKey();

            switch(input)
            {
                case 1: 
                    code [codePos]--;
                    break;
                case 2: 
                    code [codePos]++; 
                    break;
                case 3:
                    codePos--;
                    break;
                case 4:
                    codePos++;
                    break;
                
            }
            
            if(codePos < 0)
            {
                codePos = size - 1;
            }
            else if(codePos > size - 1)
            {
                codePos = 0;
            }

            if(code [codePos] < 0)
            {
                code [codePos] = numColors - 1;
            }
            else if(code [codePos] > numColors - 1)
            {
                code [codePos] = 0;
            }
        }
    }

    iClear(0, 3, 100, 3);
    
    printf("\bcode colors: ");
    for(i = 0; i < size; i++)
    {
    	printf("%c ", colors [code [i]]);
    }
    printf("\n");
    // printf("\n");

    for (i = 0; i < size; i++)
    {
        guess [i] = 0;
    }
    
	while(guesses < rounds && win != 1) //loop the game until number of guesses reached or user wins
	{
		cursorPos = 13 + guesses;

        iClear(0, 4, 100, 2);
        printf("Round %d\n", guesses + 1);
        printf("-----------------");
        for (i = 0; i < size ; i++)
        {
            printf("---");
        }
		printf("\nEnter your guess: ");

        for (i = 0; i < size; i++)
        {
            textColor(guess [i]);
            drawSymbol(0);
            printf("  ");
            // if(i != size - 1)
            // {
            //     iSetColor(I_COLOR_WHITE);
            //     printf("|");
            // }
        }
        iSetColor(I_COLOR_WHITE);


        input = 0;
        codePos = 0;
        while(input != 5 && input != 6)
        {
            guessClear = 18 + 3 * codePos;

            iClear(guessClear + 2, 6, 1, 1);
            iClear(guessClear + 4, 6, 1, 1);

            if (guessClear == 18)
            {
                iClear(17 + 3 * (size - 1), 6, 1, 1);
                iClear(19 + 3 * (size - 1), 6, 1, 1);
            }
            else if(guessClear == (18 + 3 * (size - 1)))
            {
                iClear(guessClear - 4, 6, 1, 1);
                iClear(guessClear - 2, 6, 1, 1);
                iClear(17, 6, 1, 1);
                iClear(19, 6, 1, 1);
            }
            else
            {
                iClear(guessClear - 4, 6, 1, 1);
                iClear(guessClear - 2, 6, 1, 1);
            }
            iClear(guessClear - 1, 6, 1, 1);
            printf("[");
            iClear(guessClear + 1, 6, 1, 1);
            printf("]");

            switch (guess [codePos])
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    iClear(guessClear, 6, 1, 1);    
                    textColor(guess [codePos]);
                    drawSymbol(0);
                    iSetColor(I_COLOR_WHITE);
                    break;
            }
            
            input = getArrowKey();

            switch(input)
            {
                case 1: 
                    guess [codePos]--;
                    break;
                case 2: 
                    guess [codePos]++; 
                    break;
                case 3:
                    codePos--;
                    break;
                case 4:
                    codePos++;
                    break;
                case 6:
                    goMainMenu = confirmMenu();
                    break;
            }

            if (goMainMenu == 1)
            {
                input = 5;
                guesses = rounds;
            }
            else if(goMainMenu != 1 && input == 6)
            {
                iClear(0, 6, 100, 1);
                printf("Enter your guess: ");
            
                iSetColor(I_COLOR_RED);
                for (i = 0; i < size; i++)
                {
                    textColor(guess [i]);
                    drawSymbol(0);
                    printf("  ");
                }
                iSetColor(I_COLOR_WHITE);

                iClear(0, 7, 100, 1);
                printf("-----------------");
                for (i = 0; i < size ; i++)
                {
                    printf("---");
                }

                input = 0;
            }
            
            if(codePos < 0)
            {
                codePos = size - 1;
            }
            else if(codePos > size - 1)
            {
                codePos = 0;
            }

            if(guess [codePos] < 0)
            {
                guess [codePos] = numColors - 1;
            }
            else if(guess [codePos] > numColors - 1)
            {
                guess [codePos] = 0;
            }
        }

        iClear(guessClear - 1, 6, 1, 1);
        iClear(guessClear + 1, 6, 1, 1);

        iClear(0, 7, 100, 5);
        printf("-----------------");
        for (i = 0; i < size ; i++)
        {
            printf("---");
        }
		printf("\nYou have entered: ");
		for(i = 0; i < size; i++)
		{
            textColor(guess [i]);
            drawSymbol(0);
			printf(" ");
		}
        iSetColor(I_COLOR_WHITE);
		printf("\n");

		checkGuess(guess, code, correctPositions, correctColors, size);

		positionNum = 0;
		colorNum = 0;

		for(i = 0; i < size; i++)
		{
			positionNum += correctPositions [i];
			colorNum += correctColors [i];
		}

		if (positionNum == size) //user wins the game
		{
			cursorPos += 1;

			win = 1;
            *menuPos = cursorPos + 4;
            iClear(0, cursorPos, 100, 4);
            iSetColor(I_COLOR_RED);
			printf("Con");
            iSetColor(I_COLOR_YELLOW);
            printf("grat");
            iSetColor(I_COLOR_GREEN);
            printf("u");
            iSetColor(I_COLOR_BLUE);
            printf("la");
            iSetColor(I_COLOR_CYAN);
            printf("tions");
            iSetColor(I_COLOR_PURPLE);
            printf("! ");
            iSetColor(I_COLOR_WHITE);
            printf("You won the game.");
            printf("\nGame ended on round %d\n", guesses + 1);
		}
		if (win != 1)
		{
			printf("Correct Positions: %d\n", positionNum);
			printf("Correct Colors: %d\n", colorNum);

			if (guesses == 0)
			{
				printf("\nPrevious Attempts:    Positions:  Colors:\n");
			}

			iMoveCursor(0, cursorPos);
			printf("Round %d: ", guesses + 1);
			for(i = 0; i < size; i++)
			{
				textColor(guess [i]);
                drawSymbol(0);
				printf(" ");
			}
			iSetColor(I_COLOR_WHITE);
			iMoveCursor(22, cursorPos);
			printf("%d", positionNum);
			iMoveCursor(34, cursorPos);
			printf("%d\n", colorNum);

			guesses++;
		}
	}

	if (win == 0) //player lost the game
	{
        iClear(0, 0, 100, 30);
		printf("Game Over! You lost. \nThe code was: ");
		for(i = 0; i < size; i++)
		{
            textColor(code [i]);
            drawSymbol(0);
			printf(" ");
		}
        iSetColor(I_COLOR_WHITE);
        printf("\n");

        *menuPos = 4;
	}
}

int main()
{
    int input;
    int selectMenu = 1;
    int quit = 0;
    int gamemode = 0;
    int rounds = 10;
    int goMainMenu;
    int menuPos;

/*
	int playTime;

	int loaded_time = load_time(); // Load score from file
    printf("Loaded time: %d\n", loaded_time);

	printf("Input time: ");
	scanf("%d", &playTime);
    save_time(playTime); // Save score to file
*/
	system("cls");
    SetConsoleOutputCP(437);

	while(quit != 1)
    {
        displayMainMenu();
        input = 0;

        while(input != 5)
        {
            iHideCursor();

            iClear(9, 5, 1, 1);
            iClear(18, 5, 1, 1);
            iClear(10, 7, 1, 1);
            iClear(17, 7, 1, 1);
            iClear(10, 3, 1, 1);
            iClear(17, 3, 1, 1);
            if (selectMenu == 1)
            {
                iClear(10, 3, 1, 1);
                printf("[");
                iClear(17, 3, 1, 1);
                printf("]");
            }
            else if (selectMenu == 2)
            {
                iClear(9, 5, 1, 1);
                printf("[");
                iClear(18, 5, 1, 1);
                printf("]");
            }
            else if (selectMenu == 3)
            {
                iClear(10, 7, 1, 1);
                printf("[");
                iClear(17, 7, 1, 1);
                printf("]");
            }
            
            input = getArrowKey();

            switch(input)
            {
                case 1: selectMenu--;
                        break;
                case 2: selectMenu++; 
                        break;
            }
            
            if(selectMenu < 1)
            {
                selectMenu = 3;
            }
            else if(selectMenu > 3)
            {
                selectMenu = 1;
            }
        }


	    if (selectMenu == 1)
	    {
            startGame(gamemode, rounds, &menuPos);

            printf("\nGo back to Main Menu?\n");
            printf(" Yes    No");

            input = 0;
            goMainMenu = 0;
            while(input != 5)
            {
                iClear(0, menuPos, 1, 1);
                iClear(7, menuPos, 1, 1);

                if (goMainMenu == 0)
                {
                    iClear(0, menuPos, 1, 1);
                    printf(">");
                }
                else if (goMainMenu != 0)
                {
                    iClear(7, menuPos, 1, 1);
                    printf(">");
                }
                
                input = getArrowKey();

                switch(input)
                {
                    case 3: goMainMenu--;
                            break;
                    case 4: goMainMenu++; 
                            break;
                }
                
                goMainMenu = goMainMenu % 2;
            }

            if (goMainMenu != 0)
            {
                displayEndScreen();
                quit = 1;
            }
            else if (goMainMenu == 0)
            {
                iClear(0, 8, 100, 30);
            }
	    }
	    else if(selectMenu == 2)
    	{
			iClear(0, 0, 100, 30);
    		displayOptions();
            selectOptions(&gamemode, &rounds);
    	}
    	else if(selectMenu == 3)
    	{
			iClear(0, 2, 100, 30);
            displayEndScreen();
    		quit = 1;
            printf("Press any key to exit...");
            getArrowKey();
    	}
    }
    return 0;
}
