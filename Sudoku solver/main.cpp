#include <iostream>
#include <ctime>
#include <stdlib.h>

int board[9][9][10];    // About the third dimension:
                        // The first slot stands for the number of possible numbers.
                        // The rest slots stands for the possibility of each number.


#include "HelpFunctions.cpp"
#include "Eliminator.cpp"


int main(){

    cleanBoard();
    readBoard();


    long startTime, finishStep1, finishStep2, finishStep3;
    double duration1, duration2, duration3;         // We can use less variables to caculate the time,
                                                    // but this approach is easier to modify for further analyze.

    startTime = clock();


    eliminateCandidate();


    finishStep1 = clock();
    duration1 = double(finishStep1 - startTime) / 1000;
    std::cout << "Time to run pre candidate elimination: " << duration1 << "s." << std::endl;


    eliminateGroup();


    finishStep2 = clock();
    duration2 = double(finishStep2 - finishStep1) / 1000;
    std::cout << "Time to run pre group elimination: " << duration2 << "s." << std::endl;


    bool succeed = makeAssumption();


    finishStep3 = clock();
    duration3 = double(finishStep3 - finishStep2) / 1000;
    std::cout << "Time to run brute force assumption: " << duration3 << "s." << std::endl;


    if(!succeed){
        std::cout << "Error, the problem can not be solved or doesn't need any assumption." << std::endl;
    }



    writeBoard(0);

    std::cout << "Operation finished" << std::endl;



    system("pause");

    return 0;
}
