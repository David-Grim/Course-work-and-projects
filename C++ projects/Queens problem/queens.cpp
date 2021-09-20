//David Grim
//CS10C
//Dave Harden
//2/11/19
//queens.cpp



#include <iostream>
#include <vector>
using namespace std;


/*class Queen

  void moveToNextRow()
  Adds 1 to the row. Is void so it returns no values. Also passes in no 
  parameters, only manipulates the data member row.

  void set(int inRow, int inCol)
  Sets the data members row and col to a specified value. Returns no value, only
  manipulates the data members

  int getRow() const 
  Returns the calling objects value stored in row. Has no parameters and returns 
  an integer. Shouldn't manipulate data members so its const

  row
  represents the row the queen is on in the 8x8 board

  col
  represents the column the queen is on in the 8x8 board*/

/*class Board
  Board()
  the default constructor. simply sets the queens vector to a size of 8

  void do8Queens()
  places 8 queens on the board. utilizes the placeQueens function to set the 
  queens on the board until it is full. Returns nothing since it's void.
  simply functions as a driver for the place queens function in the main()
  function

  void display() const
  Displays the locations of the queens in the 8x8 chess board. Works by using 
  using the locations of the queens and displays an X for a queen and _ for 
  where there isn't a queen. Is void so it doesn't return a value, and also 
  has no parameters manipulating no data members since its const

  bool placeQueens(Queen& queen, int row, int col)
  The primary driver function for the program. Uses a recursive algorithm 
  to fill the 8x8 board with queens. Is bool so it returns true/false as 
  stopping points. Has 3 parameters, one being reference. The row and col
  parameters are to keep track of the coordinates of the queen, whereas the 
  queen represents the queen in that spot

  bool findNextNotUnderAttackSquare(int& row, int col)
  Finds the next square that is not in the next diagonal, horizontal or
  vertical of another queen. Has row set as a reference parameter
  so it can change that variable in the placeQueens function. Returns true 
  or false once it has done so.

  bool isUnderAttack(int testRow, int testCol)
  checks if the queen in the passed in coordinates is under attack. If 
  there is it returns true otherwise it returns false. Is passed in parameters 
  representing the row and column of a queen but does not change them.
  */
class Queen {
public:
	void moveToNextRow();
	void set(int inRow, int inCol);
	int getRow() const;
private:
	int row;
	int col;
};




int Queen::getRow() const {
	return row;
}



void Queen::moveToNextRow() {
	row++;
}



void Queen::set(int inRow, int inCol) {
	row = inRow;
	col = inCol;

}






class Board {
public:
	Board();
	void do8Queens();
	void display() const;
private:
	bool placeQueens(Queen& queen, int row, int col);
	bool findNextNotUnderAttackSquare(int& row, int col);
	bool isUnderAttack(int row, int col);
	vector<Queen> queens;
};



Board::Board() {
	queens.resize(8);
}




void Board::do8Queens() {
	placeQueens(queens[0], 0, 0);
}




bool Board::placeQueens(Queen& queen, int row, int col) {
	if (col >= 8)
		return true;
	else
	{
		while (placeQueens(queen,row,col)==false){
			findNextNotUnderAttackSquare(row,col);
				if (!isUnderAttack(row,col)){
					placeQueens(queen, row, col);
						if (col < 7 && !placeQueens(queen, 0, col + 1)){
							queen.moveToNextRow();
							row = queen.getRow();
						}
						else{
								return true;
						}
				}
		}
	}
return false;
}




bool Board::isUnderAttack(int testRow, int testCol) {
	if (queens[testCol].getRow() == testRow)
		return true;
	else
		return false;
	
}




bool Board::findNextNotUnderAttackSquare(int& row, int col) {
	if (isUnderAttack(row, col)) {
		row++;
		return true;
	}
	return false;
}




void Board::display() const {
	
		

}








int main() {
	Board board;
	board.do8Queens();
	board.display();
	system("pause");
	return 0;
}