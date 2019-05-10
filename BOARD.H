#ifndef BOARD_H_
#define BOARD_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <list>
#include "Hash.h"
#include <sstream>





using namespace std;


class Board {
private:
	int row, col;
	int **grid; // 1 = black; -1 = white; 0 = empty
	list<int> left;
public:

    //initilising the hash table
    hashes hashy;


	Board(int r, int c) {
		row = r;
		col = c;
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				grid[i][j] = 0;

		for (int i = 0; i < row*col; i++) {
			left.push_back(i);
		}

	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(Board& cboard) {
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				grid[i][j] = cboard.grid[i][j];
	}

	bool addMove(int player, int x, int y);
	bool checkfull();
	void checkNeighbors(int, int);
	void printBoard();
	void play();
	bool checkIfItExists(int x, int y);
	int checkLURD(int x, int y, int player);
	int addingAdj(int,int,int,int,string,string,string,string);
    int xdigit(int);
    int ydigit(int);
    void emptygrid(int);
    void vcomp(); //versing the computer
    void compvcomp(); //computer versus computer
    void winner();


};

//checks the values that are left up right down
//calls addadj to find the total of the dice and returns the total
int Board::checkLURD(int x, int y, int player)
{
    int c,UP,LEFT,RIGHT,DOWN, dice, pipCount = 0;
    UP = LEFT = DOWN = RIGHT = 0;

    std::stringstream ss;

    ostringstream pos;
    pos << x+1 << y+1;
    //std::string p = pos.str();

    //converting back to two digit int
    istringstream iss(pos.str());
    iss >> c;


    std::string up;
    ss<<(c-10);
    up = ss.str();
    if(hashy.GetValue(up) != 0)
    {
        cout<<"Up: "<<hashy.GetValue(up)<<endl;
        //storing the value
        UP = hashy.GetValue(up);

        if(UP < 0)
            pipCount +=(UP * -1);
        else
            pipCount += UP;
    }
    //clearing the stream so it doesn't keep concatenating
    ss.str("");

    std::string down;
    ss<<(c+10);
    down = ss.str();
    if(hashy.GetValue(down) != 0)
    {
        cout<<"Down: "<<hashy.GetValue(down)<<endl;
        DOWN = hashy.GetValue(down);

        if(DOWN < 0)
            pipCount +=(DOWN * -1);
        else
            pipCount += DOWN;
    }
    ss.str("");


    std::string left;
    ss<<(c-1);
    left = ss.str();
    if(hashy.GetValue(left) != 0)
    {
        cout<<"Left: "<<hashy.GetValue(left)<<endl;
        LEFT = hashy.GetValue(left);

        if(LEFT < 0)
            pipCount +=(LEFT * -1);
        else
            pipCount += LEFT;
    }
    ss.str("");

    std::string right;
    ss<<(c+1);
    right = ss.str();
    if(hashy.GetValue(right) != 0)
    {
        cout<<"Right: "<<hashy.GetValue(right)<<endl;
        RIGHT = hashy.GetValue(right);

        if(RIGHT < 0)
            pipCount +=(RIGHT * -1);
        else
            pipCount += RIGHT;
    }
    ss.str("");

    if(pipCount != 0)
    {
        if(player == -1)
            cout<<"Total Pip Counts: "<<pipCount * -1;
        else
            cout<<"Total Pip Counts: "<<pipCount;

        if(pipCount > 6)
            cout<<" Not Capturing";
        cout<<endl;
    }

    //the dice is the value that is captured
    //the first 4 are values the second for are positions
    dice = addingAdj(UP,DOWN,LEFT,RIGHT, down,up,left,right);
    return(dice);

}

//adding adjecent values
int Board::addingAdj(int up, int down, int left, int right, string downpos, string uppos, string leftpos, string rightpos)
{
    int total = 0, tempPos = 0, x, y;

    //converting it into positive
    if(up < 0)
        up *= -1;


    if(down < 0)
        down *= -1;

    if(left < 0)
        left *= -1;

    if(right < 0)
        right *= -1;

    /*
    cout<<"addingadj"<<endl;
    cout<<"UP: "<< up<<endl;
    cout<<"right: "<< right<<endl;
    cout<<"left: "<< left<<endl;
    cout<<"down: "<< down<<endl;
    */

    if(up > 0 && right > 0)
    {
        if(total + up + right <= 6){
            total = up + right;
            hashy.RemoveItem(uppos);
            hashy.RemoveItem(rightpos);

            tempPos = stoi(uppos);
            emptygrid(tempPos);
            tempPos = stoi(rightpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + down) <= 6){
                total += down;
                hashy.RemoveItem(downpos);

                tempPos = stoi(downpos);
                if(down != 0)
                    emptygrid(tempPos);
            }

            if(total <= 6 && (total + left) <= 6){
                total += left;
                hashy.RemoveItem(leftpos);

                tempPos = stoi(leftpos);
                if(left != 0)
                    emptygrid(tempPos);
            }




            //cout<<"UP: "<< up<<endl;
            //cout<<"right: "<< right<<endl;
            cout<<"up right: "<<total<<endl;
            return total;
        }
    }

    if(up > 0 && left > 0)
    {
        if(total + up + left <= 6){
            total = up + left;
            hashy.RemoveItem(uppos);
            hashy.RemoveItem(leftpos);

            tempPos = stoi(uppos);
            emptygrid(tempPos);
            tempPos = stoi(leftpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + down) <= 6){
                total += down;
                hashy.RemoveItem(downpos);

                tempPos = stoi(downpos);
                if(down != 0)
                    emptygrid(tempPos);
            }


            if(total <= 6 && (total + right) <= 6){
                total += right;
                hashy.RemoveItem(rightpos);

                tempPos = stoi(rightpos);
                if(right != 0)
                    emptygrid(tempPos);
            }



            //cout<<"UP: "<< up<<endl;
            // cout<<"left: "<< left<<endl;
            cout<<"up left: "<<total<<endl;

            return total;
        }
    }

    if(right > 0 && left > 0)
    {
        if(total + right + left <= 6){
            total = right + left;
            hashy.RemoveItem(rightpos);
            hashy.RemoveItem(leftpos);

            tempPos = stoi(rightpos);
            emptygrid(tempPos);
            tempPos = stoi(leftpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + down) <= 6){
            total += down;
            hashy.RemoveItem(downpos);

            tempPos = stoi(downpos);
            if(down != 0)
                emptygrid(tempPos);
            }

            if(total <= 6 && (total + up) <= 6){
                total += up;
                hashy.RemoveItem(uppos);

                tempPos = stoi(uppos);
                if(up != 0)
                    emptygrid(tempPos);
            }



        //cout<<"right: "<< right<<endl;
        //cout<<"left: "<< left<<endl;
            cout<<"right left: "<<total<<endl;
            return total;
        }
    }

     if(down > 0 && left > 0)
    {
        if(total + down + left <= 6){
            total = down + left;
            hashy.RemoveItem(downpos);
            hashy.RemoveItem(leftpos);

            tempPos = stoi(downpos);
            emptygrid(tempPos);
            tempPos = stoi(leftpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + up) <= 6){
            total += up;
            hashy.RemoveItem(uppos);

            tempPos = stoi(uppos);
            if(up != 0)
                emptygrid(tempPos);
            }

            if(total <= 6 && (total + right) <= 6){
                total += right;
                hashy.RemoveItem(rightpos);

                tempPos = stoi(rightpos);
                if(right != 0)
                    emptygrid(tempPos);
            }



        //cout<<"down: "<< down<<endl;
        //cout<<"left: "<< left<<endl;
            cout<<"down left: "<<total<<endl;
            return total;
        }
    }

    if(down > 0 && right > 0)
    {
        if(total + down + right <= 6){
            total = down + right;
            hashy.RemoveItem(rightpos);
            hashy.RemoveItem(downpos);

            tempPos = stoi(rightpos);
            emptygrid(tempPos);
            tempPos = stoi(downpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + up) <= 6){
            total += up;
            hashy.RemoveItem(uppos);

            tempPos = stoi(uppos);
            if(up != 0)
                emptygrid(tempPos);
            }

            if(total <= 6 && (total + left) <= 6){
                total += left;
                hashy.RemoveItem(leftpos);

                tempPos = stoi(leftpos);
                if(left != 0)
                    emptygrid(tempPos);
            }


            cout<<"down right: "<<total<<endl;
            return total;
        }
    }




    if(down > 0 && up > 0)
    {
        if(total + down + up <= 6){
            total = down + up;
            hashy.RemoveItem(uppos);
            hashy.RemoveItem(downpos);

            tempPos = stoi(uppos);
            emptygrid(tempPos);
            tempPos = stoi(downpos);
            emptygrid(tempPos);

            if(total <= 6 && (total + right) <= 6){
            total += right;
            hashy.RemoveItem(rightpos);

            tempPos = stoi(rightpos);
            if(right != 0)
                emptygrid(tempPos);
            }

            if(total <= 6 && (total + left) <= 6){
                total += left;
                hashy.RemoveItem(leftpos);

                tempPos = stoi(leftpos);
                if(left != 0)
                    emptygrid(tempPos);
            }



            cout<<"down up: "<<total<<endl;
            return total;
        }
    }

    //no capture
    return (0);

}


bool Board::addMove(int dice, int x, int y)
{
    int tempdice = 0;

    //checking if the dice should be one or more
    if(dice == -1)
    {
        //checking left up right down values
        tempdice = checkLURD(x,y, -1);
        if(tempdice != 0)
            dice = tempdice *= -1;
    }

    if(dice == 1)
    {
        tempdice = checkLURD(x,y, 1);
        if(tempdice != 0)
            dice = tempdice;

    }

    //combining the two ints x and y
    ostringstream pos;
    pos << x+1 << y+1;
    //cout<<"Comb: "<<pos.str()<<endl;

    ostringstream diceo;
    diceo << dice;
    //cout<<"dice: "<<diceo.str()<<endl;

    //converting from stream to string
    std::string p = pos.str();
    std::string s = diceo.str();



    hashy.AddItem(p,s);
    //hashy.PrintTable();

    //checking left up right down
    //checkLURD(x,y);



	grid[x][y] = dice;




    //returning true or false based on if
    //the table is false
	return(checkfull());






}

//checking if what the user position is empty or not
bool Board::checkIfItExists(int x, int y)
{
    ostringstream pos;
    pos << x << y;
    //cout<<"Comb: "<<pos.str()<<endl;

     std::string p = pos.str();

    if(hashy.FindValue(p))
    {
        //cout<<"This position is taken"<<endl;
        return true;
    }
    else
    {
        //cout<<"This position is NOT taken"<<endl;
        return false;
    }
}

bool Board::checkfull()
{
     //counter keeping track of how many spots are full
	int allFull = 0;

	//checking the board to see if it is full
	for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if (grid[i][j] != 0)
            {
                allFull += 1;

            }

        }
    }
    //printf("\nAll full %d\n col: %d\n row: %d\n multiplied: %d\n", allFull, col, row, (row * col));
	if(allFull == (row * col))
    {
       // cout<<"Board Full"<<endl;
        return false;
    }
    else
    {
        return true;
    }
}


void Board::play() {
	int x, y, player = 0, dice = 1;

	do {

		cout << "Game board:" << endl;
		this->printBoard();

		cout << "Input your move with row and column numbers:" << endl;
		cin >> x >> y;

        //checking if what the user typed is valid
        if(x == 0 || x > row || y == 0 || y > col)
        {
            do
            {
                cout<<"what you have typed is invalid please try again:"<<endl;
                cin >> x >> y;
            }while(x == 0 || x > row || y == 0 || y > col);
        }

        while(checkIfItExists(x,y))
        {
            cout<<"The position is taken, type a new one\n";
            cin >> x >> y;

            if(x == 0 || x > row || y == 0 || y > col)
                {
                    do
                    {
                        cout<<"what you have typed is invalid please try again:"<<endl;
                        cin >> x >> y;
                    }while(x == 0 || x > row || y == 0 || y > col);
                }
        }


        //here changing players
        if(player == 0)
        {
            dice = 1;
            player = 1;
        }
        else
        {
            dice = -1;
            player = 0;
        }



	} while(addMove(dice, x-1, y-1));

	cout << "Game board:" << endl;
    this->printBoard();
    winner();
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

//first digit of the combination
int Board::xdigit(int num)
{
    //removing the last digit from the int
     while (num >= 10)
        num /= 10;


    return num;
}

//last digit of the combination
int Board::ydigit(int num)
{
    return (num % 10);
}

void Board::emptygrid(int temp)
{
    int x, y;
    x = xdigit(temp);
    y = ydigit(temp);
    grid[x-1][y-1] = NULL;
}

void Board::vcomp()
{
    int x, y, player = 0, dice = 1;
    srand(rand()%rand());

	do {
            if(player == 0)
            {
                cout << "Game board:" << endl;
                this->printBoard();

                cout << "Input your move with row and column numbers:" << endl;
                cin >> x >> y;

                //checking if what the user typed is valid
                if(x == 0 || x > row || y == 0 || y > col)
                {
                    do
                    {
                        cout<<"what you have typed is invalid please try again:"<<endl;
                        cin >> x >> y;
                    }while(x == 0 || x > row || y == 0 || y > col);
                }

                while(checkIfItExists(x,y))
                {
                    cout<<"The position is taken, type a new one\n";
                    cin >> x >> y;

                    if(x == 0 || x > row || y == 0 || y > col)
                    {
                        do
                        {
                            cout<<"what you have typed is invalid please try again:"<<endl;
                            cin >> x >> y;
                        }while(x == 0 || x > row || y == 0 || y > col);
                    }
                }

            }

            if(player == 1)
            {
                cout << "Game board:" << endl;
                this->printBoard();

                cout << "Computer's  Move" << endl;
                x = rand();
                y = rand();

                //checking if what the user typed is valid
                if(x == 0 || x > row || y == 0 || y > col)
                {
                    do
                    {
                        //cout<<"what you have typed is invalid please try again:"<<endl;
                        x = rand()+1;
                        y = rand()+1;
                    }while(x == 0 || x > row || y == 0 || y > col);
                }

                while(checkIfItExists(x,y))
                {
                    //cout<<"The position is taken, type a new one\n";
                    x = rand();
                    y = rand();

                    if(x == 0 || x > row || y == 0 || y > col)
                    {
                        do
                        {
                            //cout<<"what you have typed is invalid please try again:"<<endl;
                            x = rand()+1;
                            y = rand()+1;
                        }while(x == 0 || x > row || y == 0 || y > col);
                    }
                }
                cout<<"X: :"<<x<<" Y: "<<y<<endl;

            }




        //here changing players
        if(player == 0)
        {
            dice = 1;
            player = 1;
        }
        else
        {
            dice = -1;
            player = 0;
        }



	} while(addMove(dice, x-1, y-1));
    cout << "Game board:" << endl;
    this->printBoard();
    winner();
}

void Board::compvcomp()
{
     int x, y, player = 0, dice = 1;
     //srand(rand()%rand()*2.3);
     srand (time(NULL));

	do {
            if(player == 0)
            {
                cout << "Game board:" << endl;
                this->printBoard();

                cout << "Computer's  Move" << endl;
                x = rand();
                y = rand();

                //checking if what the user typed is valid
                if(x == 0 || x > row || y == 0 || y > col)
                {
                    do
                    {
                        //cout<<"what you have typed is invalid please try again:"<<endl;
                        x = rand() % row+ 1;
                        y = rand() % col+ 1;
                    }while(x == 0 || x > row || y == 0 || y > col);
                }

                while(checkIfItExists(x,y))
                {
                    //cout<<"The position is taken, type a new one\n";
                    x = rand() % row;
                    y = rand() % col;

                    if(x == 0 || x > row || y == 0 || y > col)
                    {
                        do
                        {
                            //cout<<"what you have typed is invalid please try again:"<<endl;
                            x = rand() % row+ 1;
                            y = rand() % col+ 1;
                        }while(x == 0 || x > row || y == 0 || y > col);
                    }
                }
                cout<<"X: "<<x<<" Y: "<<y<<endl;
            }

            if(player == 1)
            {
                cout << "Game board:" << endl;
                this->printBoard();

                cout << "Computer's  Move" << endl;
                x = rand() % row+ 1;
                y = rand() % col+ 1;

                //checking if what the user typed is valid
                if(x == 0 || x > row || y == 0 || y > col)
                {
                    do
                    {
                        //cout<<"what you have typed is invalid please try again:"<<endl;
                        x = rand() % row+ 1;
                        y = rand() % col+ 1;
                    }while(x == 0 || x > row || y == 0 || y > col);
                }

                while(checkIfItExists(x,y))
                {
                    //cout<<"The position is taken, type a new one\n";
                    x = rand() % row+ 1;
                    y = rand() % col+ 1;

                    if(x == 0 || x > row || y == 0 || y > col)
                    {
                        do
                        {
                            //cout<<"what you have typed is invalid please try again:"<<endl;
                            x = rand() % row + 1;
                            y = rand() % col + 1;
                        }while(x == 0 || x > row || y == 0 || y > col);
                    }
                }
                cout<<"X: "<<x<<" Y: "<<y<<endl;

            }




        //here changing players
        if(player == 0)
        {
            dice = 1;
            player = 1;
        }
        else
        {
            dice = -1;
            player = 0;
        }



	} while(addMove(dice, x-1, y-1));
    cout << "Game board:" << endl;
    this->printBoard();
    winner();
}

void Board::winner()
{
 //counter keeping track of how many spots are full
    int p1,p2;
    p1 = p2 = 0;

	//checking the board to see if it is full
	for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if (grid[i][j] > 0)
            {
                p1 += grid[i][j];

            }else if(grid[i][j] < 0)
            {
                p2 += (grid[i][j] * -1);
            }

        }
    }

    if (p1 > p2)
        cout<<"Winner is White: "<<p1<<endl;
    else
        cout<<"Winner is Black: "<<p2 * -1<<endl;
}

#endif /* BOARD_H_ */
