#include <board.h>

Board::Board(int height, int width)
  : grid(height, vector<Cell>(width, { Status::COVERED, 0 })),
    numUncoveredCells(0)
{
  // empty
}

Board::Board(const Board & b)
  : grid(b.grid), numUncoveredCells(b.numUncoveredCells)
{
  // empty
}

Board::Board(Board && b)
  : grid(move(b.grid)), numUncoveredCells(0)
{
  swap(numUncoveredCells, b.numUncoveredCells);
}

Board & Board::operator = (const Board & b) 
{
  if (&b == this) return *this;

  grid = b.grid;
  numUncoveredCells = b.numUncoveredCells;

  return *this;
}

Board & Board::operator = (Board && b)
{
  swap(grid, b.grid);
  swap(numUncoveredCells, b.numUncoveredCells);

  return *this;
}

int Board::rows() const 
{
  return grid.size();
}

int Board::cols() const 
{
  return grid.front().size();
}

Status Board::status(int i, int j) const
{
  return grid[i][j].first;
}

int Board::value(int i, int j) const
{
  return grid[i][j].second;
}

int Board::getNumUncoveredCells() const 
{
  return numUncoveredCells;
}

bool Board::areUncoveredAll() const 
{
  return rows() * cols() == getNumUncoveredCells();
}

void Board::discover() 
{
  string n, m;
  cout << "row: ";
  cin >> n; 
  cout << "col: ";
  cin >> m;
  cout << '\n';
  
  int i, j;
  
  i = stoi(n, nullptr, 10);
  j = stoi(m, nullptr, 10);
  
  i--;
  j--;

  if (i < 0 or j < 0)
    throw invalid_argument("out of range");

  if (i >= rows() or j >= cols()) 
    throw invalid_argument("out of range");

  discover(i, j, value(i,j));
}

void Board::discover(int i, int j, int k)
{
  if (i < 0 or j < 0) 
    return;
  
  if (i >= rows() or j >= cols()) 
    return;
  
  if (value(i,j) != k) 
    return;
  
  if (grid[i][j].first == Status::UNCOVERED) 
    return;
  
  grid[i][j].first = Status::UNCOVERED;
  
  discover(i - 1, j - 1, k);
  discover(i - 1, j, k);
  discover(i - 1, j + 1, k);
  discover(i, j - 1, k);
  discover(i, j + 1, k);
  discover(i + 1, j - 1, k);
  discover(i + 1, j, k);
  discover(i + 1, j + 1, k);
  
  numUncoveredCells++;

}

void Board::print()
{
  for (int i = 0; i < cols() + 2; i++) 
    cout << '-';
  cout << '\n';
  
  for (int i = 0; i < rows(); i++) {
    cout << '|';
    for (int j = 0; j < cols(); j++) {
	    auto st = status(i, j);
      if (st == Status::UNCOVERED) cout << value(i,j);
      else cout << '-';
	  }
    cout << "|\n";
  }

  for (int i = 0; i < cols() + 2; i++)
    cout << '-';
  cout << '\n';
}

void Board::solve() 
{
  int steps = 0;
  for (int i = 0; i < rows(); i++) {
    for (int j = 0; j < cols(); j++) {
      if (status(i,j) == Status::UNCOVERED) continue;
      cout << '(' << i+1 << ',' << j+1 << ')' << ':';
      cout << '\n'; 
      discover(i,j, value(i,j));
      print();
      cout << "Boxes without uncover remaining: " << rows() * cols() - getNumUncoveredCells() << '\n';
      cout << "Enter to continue..." << '\n';
      getchar();
      steps ++;
    }
  }
  cout << "Total steps: " << steps << '\n';
}

void Board::load(ifstream & in)
{
  for (int i = 0; i < rows(); i++) {
    for (int j = 0; j < cols(); j++) {
      int value;
	    in >> value;
	    grid[i][j].first = Status::COVERED;
	    grid[i][j].second = value;
    }
  }
}