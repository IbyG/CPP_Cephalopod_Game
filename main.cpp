#include<iostream>
#include<time.h>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "Hash.h"

/*
GO TO SETTINGS COMPILER
    tick "Have g++ follow the C++11 ISO C++ language standard [-std = C++11]"
*/


/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

int main()
{


    //we need to set the options
    //1. human v human
    //2. human v random
    //3. random v random
    //4. human v monte carlo
    //5. random v monte carlo

    //random will just be producing random numbers and trying to and then test if
    int row, col, playMode;

    srand(rand()%rand());

    cout<<"1.) player v player"<<endl;
    cout<<"2.) player v Random Computer"<<endl;
    cout<<"3.) Random Computer v Random Computer"<<endl;
    cin >> playMode;

	cout <<"Input the size of board, say (3x3), (3x5) or (5x5): " << endl;


	cin >> row >> col;

    if(row != 3 && row != 5 || col != 3 && col != 5)
    {
        do
        {
            cout<<"What you have typed is invalid, Please try again (3x3), (3x5) or (5x5)"<<endl;
            cin >> row >> col;
        }while(row != 3 && row != 5 || col != 3 && col != 5);

    }

    Board board(row,col);



    if(playMode == 1)
    {
        board.play();
    }
    else if(playMode == 2)
    {
        board.vcomp();
    }
    else if(playMode == 3)
    {
        board.compvcomp();
    }



	return 0;
}
