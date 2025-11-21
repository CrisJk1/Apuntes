#include <bits/stdc++.h>
using namespace std;

struct AlignmentResult {
    int score;
    string A_aligned;
    string B_aligned;
};

// Needleman-Wunsch: global alignment
AlignmentResult needlemanWunsch(const string &A, const string &B,
                                int match = 1, int mismatch = -1, int gap = -1) {
    int n = A.size();
    int m = B.size();

    // DP matrix
    vector<vector<int>> dp(n+1, vector<int>(m+1));

    // Build DP base cases
    for(int i = 0; i <= n; i++) dp[i][0] = i * gap;
    for(int j = 0; j <= m; j++) dp[0][j] = j * gap;

    // Fill DP matrix
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int score_diag = dp[i-1][j-1] + (A[i-1] == B[j-1] ? match : mismatch);
            int score_up   = dp[i-1][j] + gap;
            int score_left = dp[i][j-1] + gap;

            dp[i][j] = max({score_diag, score_up, score_left});
        }
    }

    // --- Reconstruction ---
    string A_al, B_al;
    int i = n, j = m;

    while(i > 0 || j > 0) {
        if(i > 0 && j > 0 &&
           dp[i][j] == dp[i-1][j-1] + (A[i-1] == B[j-1] ? match : mismatch)) {
            A_al.push_back(A[i-1]);
            B_al.push_back(B[j-1]);
            i--; j--;
        }
        else if(i > 0 && dp[i][j] == dp[i-1][j] + gap) {
            A_al.push_back(A[i-1]);
            B_al.push_back('-');
            i--;
        }
        else { // j > 0
            A_al.push_back('-');
            B_al.push_back(B[j-1]);
            j--;
        }
    }

    reverse(A_al.begin(), A_al.end());
    reverse(B_al.begin(), B_al.end());

    return { dp[n][m], A_al, B_al };
}

int main() {
    string A, B;
    cin >> A >> B;

    auto res = needlemanWunsch(A, B);
    cout << "Score: " << res.score << endl;
    if (res.A_aligned.size() > 0) {
        cout << "Alineamiento:" << endl;
        cout << res.A_aligned << endl;
        cout << res.B_aligned << endl;
    }
    return 0;
}