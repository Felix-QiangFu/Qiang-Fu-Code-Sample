
void eliminateCandidate(){      // Do the elininate opration and update cells if necessary
    for(int rowNum = 0; rowNum < 9; ++rowNum){
        for(int colNum = 0; colNum < 9; ++colNum){


            if(board[rowNum][colNum][0] > 1){
                int tempSlot[10];

                findPossibility(rowNum, colNum, tempSlot);

                writeSlot(rowNum, colNum, tempSlot);

                if(board[rowNum][colNum][0] == 1)
                    updateBoard(rowNum, colNum, findNumber(rowNum, colNum));


            }else if(board[rowNum][colNum][0] == 1){

                updateBoard(rowNum, colNum, findNumber(rowNum, colNum));

            }else if(board[rowNum][colNum][0] == 0){

                std::cout << "Error, no candidate for board[" << rowNum
                    << "][" << colNum << "] in eliminate stage." << std::endl;

            }


        }
    }

}




bool eliminateGroup(){

    for(int currentRow = 0; currentRow < 9; ++currentRow){
        for(int currentCol = 0; currentCol < 9; ++currentCol){

            if(board[currentRow][currentCol][0] == 2){

                for(int i = 0; i < 9; ++i){         // By row
                    if(i != currentCol && board[currentRow][i][0] == 2){
                        if(compareCandidate(currentRow, currentCol, currentRow, i)){
                            if(!updateGroup(currentRow, currentCol, currentRow, i, 1)){
                                return false;
                            }
                        }
                    }
                }

                for(int i = 0; i < 9; ++i){         // By column
                    if(i != currentRow && board[i][currentCol][0] == 2){
                        if(compareCandidate(currentRow, currentCol, i, currentCol)){
                            if(!updateGroup(currentRow, currentCol, i, currentCol, 2)){
                                return false;
                            }
                        }
                    }
                }

                int rowBase, colBase;
                rowBase = (currentRow / 3) * 3;
                colBase = (currentCol / 3) * 3;
                for(int i = 0; i < 3; ++i){         // By square
                    for(int j = 0; j < 3; ++j){
                        if(board[i][currentCol][0] == 2 && (rowBase + i != currentRow || colBase + j != currentCol)){
                            if(compareCandidate(currentRow, currentCol, rowBase + i, colBase + j)){
                                if(!updateGroup(currentRow, currentCol, rowBase + i, colBase + j, 3)){
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}








bool makeAssumption(){

    // Backup the board first at each recursion
    int boardBackup[9][9][10];
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            for(int k = 0; k < 10; ++k){
                boardBackup[i][j][k] = board[i][j][k];
            }
        }
    }

    // Find the start cell to make a assumption
    int lowestPossibility = 9;
    int lowestRow = 10;
    int lowestCol = 10;
    int numOfFixedCell = 0;


    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            if(board[i][j][0] > 1 && board[i][j][0] <= lowestPossibility){
                int tempNOFC = findNumOfFixedCell(i, j);
                if(tempNOFC > numOfFixedCell){
                    lowestRow = i;
                    lowestCol = j;
                    numOfFixedCell = tempNOFC;
                    lowestPossibility = board[i][j][0];
                }
            }
        }
    }

    if(lowestRow == 10){
        lowestRow = 0;
        lowestCol = 0;
        std::cout << "Warning, this board do not needs any assumption" << std::endl;
    }


    // Starts to make an assumption
    bool isSuccess = false;

    int originalCell[10];
    for(int k = 0; k < 10; ++k){
        originalCell[k] = board[lowestRow][lowestCol][k];
    }






    for(int k = 1; k < 10; ++k){

        if(originalCell[k] == 1){

            board[lowestRow][lowestCol][0] = 1;

            for(int localK = 1; localK < 10; ++localK)
                board[lowestRow][lowestCol][localK] = 0;


            board[lowestRow][lowestCol][k] = 1;

            isSuccess = updateBoard(lowestRow, lowestCol, k);

            if(isSuccess){
                // If the board is done, return true
                if(checkFinished()){
                    return true;
                }

                // Preform a forward check by eliminate groups
                if(eliminateGroup()){
                    // Do the recursion, if succeed then return true
                    if(makeAssumption()){
                        return true;
                    }
                }

            }

            for(int i = 0; i < 9; ++i){
                for(int j = 0; j < 9; ++j){
                    for(int k = 0; k < 10; ++k){
                        board[i][j][k] = boardBackup[i][j][k];
                    }
                }
            }

        }


    }

    // Write back the original board, then end this recursion
    for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            for(int k = 0; k < 10; ++k){
                board[i][j][k] = boardBackup[i][j][k];
            }
        }
    }

    return false;
}
