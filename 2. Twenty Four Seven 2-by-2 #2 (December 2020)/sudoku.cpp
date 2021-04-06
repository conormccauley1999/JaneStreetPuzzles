#include <bits/stdc++.h>
using namespace std;
#define N 7

int GRID[N][N] = {
    { -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1, -1, -1,  3},
    { -1, -1, -1, -1, -1, -1, -1},
    { -1, -1, -1, -1,  4, -1, -1},
    { -1, -1, -1, -1, -1, -1, -1},
    { -1, -1,  3, -1, -1, -1, -1}
};
int HTOP[N] = {0, 0, 0, 0, 0, 0, 0};
int HLEF[N] = {1, 2, 3, 4, 5, 6, 7};
int HBOT[N] = {0, 6, 0, 5, 0, 4, 0};
int HRIG[N] = {0, 6, 0, 4, 0, 2, 0};
pair<int, int> CSTART = make_pair(6, 2);

int cnt = 0;

void disp() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (GRID[i][j] == -1) cout << "  ";
            else cout << GRID[i][j] << " ";
        }
        cout << endl;
    }
    cout << string(13, '=') << endl;
}

bool validate(int row, int col, int num) {
    GRID[row][col] = num;

    // standard checks
    int rowCounts[N] = {0};
    int rowZCounts[N] = {0};
    int colCounts[N] = {0};
    int colZCounts[N] = {0};
    int rowSums[N] = {0};
    int colSums[N] = {0};
    int numCounts[N] = {0};
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int n = GRID[r][c];
            if (n > 0) {
                rowCounts[r]++;
                colCounts[c]++;
                rowSums[r] += n;
                colSums[c] += n;
                numCounts[n - 1]++;
            } else if (n == 0) {
                rowZCounts[r]++;
                colZCounts[c]++;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        if (rowCounts[i] > 4) return false;
        if (rowZCounts[i] > 3) return false;
        if (colCounts[i] > 4) return false;
        if (colZCounts[i] > 3) return false;
        if (rowSums[i] > 20) return false;
        if (colSums[i] > 20) return false;
        if (numCounts[i] > i + 1) return false;
        if (rowCounts[i] == 4 && rowZCounts[i] == 3 && rowSums[i] != 20) return false;
        if (colCounts[i] == 4 && colZCounts[i] == 3 && colSums[i] != 20) return false;
    }

    // hint checks
    for (int i = 0; i < N; i++) {
        // should have made these a single loop over each side instead of four ifs
        int t = HTOP[i], l = HLEF[i], b = HBOT[i], r = HRIG[i];
        if (t != 0) {
            bool f = false;
            for (int j = 0; j < N; j++) {
                int v = GRID[j][i];
                if (v == t || v == -1) {
                    f = true;
                    break;
                } else if (v != 0) {
                    break;
                }
            }
            if (!f) return false;
        }
        if (l != 0) {
            bool f = false;
            for (int j = 0; j < N; j++) {
                int v = GRID[i][j];
                if (v == l || v == -1) {
                    f = true;
                    break;
                } else if (v != 0) {
                    break;
                }
            }
            if (!f) return false;
        }
        if (b != 0) {
            bool f = false;
            for (int j = 0; j < N; j++) {
                int v = GRID[N - j - 1][i];
                if (v == b || v == -1) {
                    f = true;
                    break;
                } else if (v != 0) {
                    break;
                }
            }
            if (!f) return false;
        }
        if (r != 0) {
            bool f = false;
            for (int j = 0; j < N; j++) {
                int v = GRID[i][N - j - 1];
                if (v == r || v == -1) {
                    f = true;
                    break;
                } else if (v != 0) {
                    break;
                }
            }
            if (!f) return false;
        }
    }
    
    // subsquare checks
    // should have used 2D prefix sums here
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            int c = 0;
            if (GRID[i][j] > 0) c++;
            if (GRID[i + 1][j] > 0) c++;
            if (GRID[i][j + 1] > 0) c++;
            if (GRID[i + 1][j + 1] > 0) c++;
            if (c == 4) return false;
        }
    }

    // connected check
    set<pair<int, int>> vis;
    queue<pair<int, int>> Q;
    Q.push(CSTART);
    while (!Q.empty()) {
        pair<int, int> pnt = Q.front();
        int r = pnt.first, c = pnt.second;
        Q.pop();
        if (GRID[r][c] != 0 && !vis.count(pnt)) {
            vis.insert(pnt);
            if (r > 0) Q.push(make_pair(r - 1, c));
            if (c > 0) Q.push(make_pair(r, c - 1));
            if (r < N - 1) Q.push(make_pair(r + 1, c));
            if (c < N - 1) Q.push(make_pair(r, c + 1));
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pair<int, int> pnt = make_pair(i, j);
            if (GRID[i][j] > 0 && !vis.count(pnt)) {
                return false;
            }
        }
    }

    return true;
}

bool solve(int row, int col) {
    cnt++;
    if (!(cnt % 500)) disp();
    if (row == N - 1 && col == N) return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (GRID[row][col] >= 0) return solve(row, col + 1);
    for (int num = 0; num <= N; num++) {
        if (validate(row, col, num)) {
            GRID[row][col] = num;
            if (solve(row, col + 1)) return true;
        }
        GRID[row][col] = -1;
    }
    return false;
}

int main() {
    solve(0, 0);
    disp();
    return 0;
}
