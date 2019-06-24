/*
 *  Diego Martinez 
 *  diegomartinez6c@gmail.com
 * 
 *  Oscar Albornoz
 *  oalbornoz08@gmail.com
 */
#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include <utility>
#include <cctype>
#include <vector>

using namespace std;

enum Status { COVERED, UNCOVERED };

// Tipo que representa una casilla, la primera posicion es el estado y la segunda el valor
using Cell = pair<Status, int>;

class Board
{
  public:
    Board(int height = 64, int width = 64);

    Board(const Board &);

    Board(Board &&);

    Board & operator = (const Board &);
    
    Board & operator = (Board &&);

    // retorna la cantidad de filas
    int rows() const;

    // retorna la cantidad de columnas
    int cols() const;

    // retorna el estado de la casilla (i,j)
    Status status(int ,int) const;

    // retorna el valor de la casilla (i,j)
    int value(int, int) const;

    // retorna la cantidad de casillas que se han destapado
    int getNumUncoveredCells() const;

    // verifica si se destaparon todas las casillas
    bool areUncoveredAll() const;

    // arropa discover(int,int,int) para destapar una casilla
    void discover();

    // soluciona el puzzle 
    void solve();

    // imprime la matriz
    void print();

    // carga la matriz de un archivo
    void load(ifstream & in);

  private:
    vector<vector<Cell>> grid;
    int numUncoveredCells;
    
    // destapa recursivamente la casilla (i,j) con valor k
    void discover(int, int, int);
};

#endif