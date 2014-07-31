
#include <iostream>
#include <cstdlib>
#include <fstream>			// For file operation
#include <cstring>          // For strtok
#include <string>



void printOutCell(int i, int j){
    std::cout<<"Printing out cell ["<<i<<"]["<<j<<"]: ";
    for(int k = 0; k < 10; ++k){
        std::cout<<board[i][j][k]<<" ";
    }
    std::cout<<std::endl;
}

void findMistake(float pos){    // This function is for test only

    int mistakeCounter1 = 0;    // Possibility not in range
    int mistakeCounter2 = 0;    // Invalid value
    int mistakeCounter3 = 0;    // Numbers of possibility doesnt match
    for(int i=0; i<9; ++i){
        for(int j=0; j<9; ++j){
            if(board[i][j][0]<1 || board[i][j][0]>9){
                ++mistakeCounter1;
                //std::cout<<"Error in ["<<i<<"]["<<j<<"][0]"<<std::endl;
            }
            int tempCounter = 0;
            for(int k=1; k<10; ++k){
                if(board[i][j][k] == 1){
                    ++tempCounter;
                }else if(board[i][j][k] != 0){
                    ++mistakeCounter2;
                    //std::cout<<"Error in ["<<i<<"]["<<j<<"]["<<k<<"]"<<std::endl;
                }
            }
            if(tempCounter != board[i][j][0]){
                ++mistakeCounter3;
                //std::cout<<"Error in ["<<i<<"]["<<j<<"][0]"<<std::endl;
            }
        }
    }
    std::cout<<"Total mistakes in Pos "<<pos<<": "<<mistakeCounter1<<" "<<mistakeCounter2<<" "<<mistakeCounter3<<std::endl;
}










void readBoard(){
    std::ifstream file("input.txt");
    std::string singleLine;

    for(int i = 0; i < 9; ++i){
        if(!getline(file, singleLine))
            std::cout << "Unfinished board!" << std::endl;

        char* token = strtok(const_cast<char*>(singleLine.c_str()), " ");
        int tempNum = 0;

        for(int j = 0; j < 9; ++j){
            tempNum = atoi(token);

            if(tempNum != 0){
                board[i][j][0] = 1;
                for(int k = 1; k < 10; ++k)
                    board[i][j][k] = 0;
                board[i][j][tempNum] = 1;
            }

            token = strtok(NULL, " ");
        }

    }

    file.close();
}



void writeBoard(int state){     // State: 0- Final, 1- Original board, 2- Number of possibility
    std::ofstream file("output.txt");

    if(!state){
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(board[i][j][0] != 1){
                    file << "0 ";
                }else{
                    for(int k = 1; k < 10; ++k){
                        if(board[i][j][k] == 1)
                            file << k << " ";
                            //break;
                    }
                }
            }
            file << std::endl;
        }

    }else if(state == 1){

        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(board[i][j][0] == 9){
                    file << "0 ";
                }else{
                    for(int k = 1; k < 10; ++k){
                        if(board[i][j][k] == 1)
                            file << k << " ";
                    }
                }

                file << " | ";
            }

            file << std::endl;
        }

    }else if(state == 2){

        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                file << board[i][j][0] << " ";
            }

            file << std::endl;
        }

    }



    file.close();
}



void cleanBoard(){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            board[i][j][0] = 9;
            for(int k = 1; k < 10; ++k)
                board[i][j][k] = 1;
        }
    }
}



int findNumber(int rowNum, int colNum){
    if(board[rowNum][colNum][0] != 1){
        std::cout << "Error, finding wrong slot" << std::endl;
        return 0;
    }

    for(int k = 1; k < 10; ++k){
        if(board[rowNum][colNum][k] == 1){
            return k;
        }
    }


printOutCell(rowNum, colNum);
    return 0;
}



void writeSlot(int rowNum, int colNum, int* tempSlot){      // Copy a temporary slot to the board
    for(int k = 0; k < 10; ++k){
        board[rowNum][colNum][k] = tempSlot[k];
    }
}




void findPossibility(int rowNum, int colNum, int* tempPossibility){   // Find all possibility for one slot
    tempPossibility[0] = 9;
    for(int i = 1; i < 10; ++i)
        tempPossibility[i] = 1;



    for(int i = 0; i < 9; ++i){     // Eliminate possibility by row
        if(i != colNum){
            if(board[rowNum][i][0] == 1){
                for(int k = 1; k < 10; ++k){
                    if(board[rowNum][i][k] == 1 && tempPossibility[k] == 1){
                        tempPossibility[k] = 0;
                        --tempPossibility[0];
                        break;
                    }
                }
            }
        }
    }



    for(int i = 0; i < 9; ++i){     // Eliminate possibility by column
        if(i != rowNum){
            if(board[i][colNum][0] == 1){
                for(int k = 1; k < 10; ++k){
                    if(board[i][colNum][k] == 1 && tempPossibility[k] == 1){
                        tempPossibility[k] = 0;
                        --tempPossibility[0];
                        break;
                    }
                }
            }
        }
    }



    int rowBase, colBase;
    rowBase = (rowNum / 3) * 3;
    colBase = (colNum / 3) * 3;
    for(int i = 0; i < 3; ++i){     // Eliminate possibility by square
        for(int j = 0; j < 3; ++j){
            if(rowBase + i != rowNum || colBase + j != colNum){
                if(board[rowBase + i][colBase + j][0] == 1){
                    for(int k = 1; k < 10; ++k){
                        if(board[rowBase + i][colBase + j][k] == 1 && tempPossibility[k] == 1){
                            tempPossibility[k] = 0;
                            --tempPossibility[0];
                            break;
                        }
                    }
                }
            }
        }
    }
    if(tempPossibility[0] <= 0)
        std::cout << "Error, no possible value for board["
            << rowNum << "][" << colNum << "]" << std::endl;


    return;
}





bool updateBoard(int rowNum, int colNum, int fixedNum){             // Update the board onece a new slot is fixed

    for(int i = 0; i < 9; ++i){     // Update current row
        if(i != colNum){

            if(board[rowNum][i][fixedNum] == 1){
                board[rowNum][i][fixedNum] = 0;
                --board[rowNum][i][0];
                if(board[rowNum][i][0] <= 0){

                    return false;
                }

                if(board[rowNum][i][0] == 1){

                    if(!updateBoard(rowNum, i, findNumber(rowNum, i))){

                        return false;
                    }

                }
            }
        }
    }

    for(int i = 0; i < 9; ++i){     // Update current column
        if(i != rowNum){
            if(board[i][colNum][fixedNum] == 1){
                board[i][colNum][fixedNum] = 0;
                --board[i][colNum][0];
                if(board[i][colNum][0] <= 0){
                    return false;
                }

                if(board[i][colNum][0] == 1){
                    if(!updateBoard(i, colNum, findNumber(i, colNum))){
                        return false;
                    }
                }
            }
        }
    }

    int rowBase, colBase;
    rowBase = (rowNum / 3) * 3;
    colBase = (colNum / 3) * 3;
    for(int i = 0; i < 3; ++i){     // Update current square
        for(int j = 0; j < 3; ++j){
            if(rowBase + i != rowNum || colBase + j != colNum){
                if(board[rowBase + i][colBase + j][fixedNum] == 1){
                    board[rowBase + i][colBase + j][fixedNum] = 0;
                    --board[rowBase + i][colBase + j][0];
                    if(board[rowBase + i][colBase + j][0] <= 0){
                        return false;
                    }

                    if(board[rowBase + i][colBase + j][0] == 1){
                        if(!updateBoard(rowBase + i, colBase + j, findNumber(rowBase + i, colBase + j))){
                            return false;
                        }
                    }
                }
            }
        }
    }


    return true;
}



bool batchUpdateForGroup(int rowNum1, int colNum1, int rowNum2, int colNum2){   // Eliminate all numbers from slot 2 in slot 1
    for(int k = 1; k < 10; ++k){
        if(board[rowNum2][colNum2][k] == 1 && board[rowNum1][colNum1][k] == 1){
            board[rowNum1][colNum1][k] = 0;
            --board[rowNum1][colNum1][0];
            if(board[rowNum1][colNum1][0] <= 0)
                return false;
        }
    }

    if(board[rowNum1][colNum1][0] == 1){
        if(!updateBoard(rowNum1, colNum1, findNumber(rowNum1, colNum1)))
            return false;
    }

    return true;
}


bool updateGroup(int rowNum1, int colNum1, int rowNum2, int colNum2, int direction){  // Like updateBoard basically, but in a group scale. 1-row 2-column 3-square
    if(direction == 1){         // By row
        for(int i = 0; i < 9; ++i){
            if(i != colNum1 && i != colNum2){
                if(!batchUpdateForGroup(rowNum1, i, rowNum1, colNum1)){
                    return false;
                }
            }
        }
    }else if(direction == 2){   // By column
        for(int i = 0; i < 9; ++i){
            if(i != rowNum1 && i != rowNum2){
                if(!batchUpdateForGroup(i, colNum1, rowNum1, colNum1)){
                    return false;
                }
            }
        }
    }else if(direction == 3){   // By square
        int rowBase = (rowNum1 / 3) * 3;
        int colBase = (colNum1 / 3) * 3;

        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if((rowBase + i != rowNum1 || colBase + j != colNum1) && (rowBase + i != rowNum2 || colBase + j != colNum2)){
                    if(!batchUpdateForGroup(rowBase + i, colBase + j, rowNum1, colNum1)){
                        return false;
                    }
                }
            }
        }
    }

    return true;
}




bool compareCandidate(int row1, int col1, int row2, int col2){
    for(int k = 1; k < 10; ++k){
        if(board[row1][col1][k] != board[row2][col2][k]){
            return false;
        }
    }

    return true;
}



int findNumOfFixedCell(int rowNum, int colNum){ // Return the number of fixed number within the relevant cells
    int numOfFixedCell = 0;

    for(int i = 0; i < 9; ++i){
        if(i != colNum && board[rowNum][i][0] == 1){
            ++numOfFixedCell;
        }
    }
    for(int i = 0; i < 9; ++i){
        if(i != rowNum && board[i][colNum][0] == 1){
            ++numOfFixedCell;
        }
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(i != rowNum && j != colNum && board[i][j][0] == 1){
                ++numOfFixedCell;
            }
        }
    }

    return numOfFixedCell;
}










bool checkFinished(){
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            if(board[i][j][0] != 1){
                return false;
            }
        }
    }

    return true;
}





