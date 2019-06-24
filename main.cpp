#include <board.h>

int main() {
  Board b;
  
  cout << "Enter the filename (with .txt) of the board: ";
  string filename;
  cin >> filename;
  
  ifstream in(filename);
  if (!in.is_open()) {
    cout << "Fail open the file" << '\n';
    return -1;
  }

  cout << "loading..." << '\n';
  b.load(in);
  in.close();  

  b.print();

  cout << "Do you want automatic mode? (y/n): ";
  char c;
  cin >> c;
  cin.ignore();
  cout << '\n';

  if (tolower(c) == 'y')  
    b.solve();
  
  else if (tolower(c) == 'n') {
    int steps = 0;
    while (!b.areUncoveredAll()) {
      try {
        b.discover();
      }
      catch(const invalid_argument & exc) {
        cout << exc.what() << '\n';
        continue;
      }
      b.print();
      cout << "Boxes without uncover remaining: " << b.rows() * b.cols() - b.getNumUncoveredCells() << '\n';
      steps ++;
    }
    cout << "Total steps: " << steps << '\n';
  }
  cout << "Done!" << '\n';
  return 0;
}