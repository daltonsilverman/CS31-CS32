bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    if(maze[sr][sc] == maze[er][ec])
        return true;
    maze[sr][sc] = '/';
    if(maze[sr][sc+1] == '.'){ //check east
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    }
    if(maze[sr-1][sc] == '.'){ //check north
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    }
    if(maze[sr][sc-1] == '.'){ //Check west
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    }
    if(maze[sr+1][sc] == '.'){ //check south
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    }
    return false;
}
         // Return true if there is a path from (sr,sc) to (er,ec)
         // through the maze; return false otherwise
