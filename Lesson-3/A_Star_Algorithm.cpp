//
// Created by Pravin Tripathi on 6/26/2020.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::sort;
using std::vector;
using std::cout;
using std::string;
using std::abs;
using std::istringstream;

enum class BoardState {Open,Obstacle,Closed,Path,Start,Finish};
// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};


vector<BoardState> ParseLine(const string& line) {
    istringstream sLine(line);
    int n;
    char c;
    vector<BoardState> row;
    while (sLine >> n >> c && c == ',') {
        if (n == 0) {
            row.push_back(BoardState::Open);
        } else {
            row.push_back(BoardState::Obstacle);
        }
    }
    return row;
}

string CellString(BoardState cell) {
    switch(cell) {
        case BoardState::Obstacle: return "/\\   ";
        case BoardState::Path: return "P   ";
        case BoardState::Start: return "S   ";
        case BoardState::Finish: return "F   ";
        default: return "0   ";
    }
}

//compare nodes
bool Compare(vector<int> node1,vector<int> node2){
    // f = g + h
    int f_1 = node1[2]+node1[3];
    int f_2 = node2[2]+node2[3];
    return f_1 > f_2;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int Heuristic(int x1,int y1,int x2,int y2){
    return abs(x2-x1)+abs(y2-y1);
}

/**
 * Add a node to the open list and mark it as open.
 */
void AddToOpen(int x, int y, int g, int h,vector<vector<int>> &openList,vector<vector<BoardState>> &board){
    openList.push_back({x,y,g,h});
    board[x][y] = BoardState::Closed;
}

//Check cell is eligible to add for explore
bool CheckValidCell(int x,int  y , vector<vector<BoardState>> &board){
    bool x_on_board = (x>=0 && x<board.size());
    bool y_on_board = (y>=0 && y<board[0].size());

    if (x_on_board && y_on_board){
        return board[x][y] == BoardState::Open;
    }

    return false;
}

/**
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(const vector<int> &current, int goal[2], vector<vector<int>> &openList, vector<vector<BoardState>> &grid) {
    // Get current node's data.
    int x = current[0];
    int y = current[1];
    int g = current[2];

    // Loop through current node's potential neighbors.
    for (auto i : delta) {
        int x2 = x + i[0];
        int y2 = y + i[1];

        // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
        if (CheckValidCell(x2, y2, grid)) {
            // Increment g value and add neighbor to open list.
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, goal[0], goal[1]);
            AddToOpen(x2, y2, g2, h2, openList, grid);
        }
    }
}

/**
 * Implementation of A* search algorithm
 */
vector<vector<BoardState>> search(vector<vector<BoardState>> board, const int init[2], int goal[2]) {
    // Create the vector of open nodes.
    vector<vector<int>> open {};

    // Initialize the starting node.
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0],goal[1]);
    AddToOpen(x, y, g, h, open, board);


    while (!open.empty()){
        //get next nearest node
        CellSort(&open);

        auto nearestNode = open.back();
        open.pop_back();

        x = nearestNode[0];
        y = nearestNode[1];

        board[x][y] = BoardState::Path;

        //check goal state
        if (x==goal[0] && y==goal[1]){
            board[init[0]][init[1]] = BoardState::Start;
            board[goal[0]][goal[1]] = BoardState::Finish;
            return board;
        }

        // If we're not done, expand search to current node's neighbors.
        ExpandNeighbors(nearestNode,goal,open,board);
    }

    cout << "\nNo path found!" << "\n";
    return vector<vector<BoardState>> {};
}

void printBoard(const vector<vector<BoardState>>& board){
    for (const auto& row : board) {
        cout << "\n";
        for(BoardState state : row){
            cout << CellString(state);
        }
    }
}

vector<vector<BoardState>> readBoardFile(const string& filePath){
    std::fstream  boardFile;
    vector<vector<BoardState>> mBoard;
    boardFile.open(filePath);

    if (boardFile){
        cout << "The file stream has been created";
        string  line;

        while (getline(boardFile,line)){
            vector<BoardState> mRow = ParseLine(line);
            mBoard.push_back(mRow);
        }
    } else{
        cout << "File failed to load";
    }

    return mBoard;
}

int main() {
    auto filePath = R"(C:\Users\Pravin Tripathi\CLionProjects\cpp_learning\Lesson-3\files\1.board)";
    auto board = readBoardFile(filePath);
    int init[] = {0,0};
    int goal[] = {4,5};

    auto solution = search(board,init,goal);
    printBoard(solution);
}
