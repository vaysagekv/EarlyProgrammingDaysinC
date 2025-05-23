#include <stdio.h>
#include <limits.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the minimum of two integers
int min(int a, int b) {
    return (a < b) ? a : b;
}

// MinMax function
// scores[]: Array of scores
// n: Number of scores
// depth: Current depth in the game tree (0 for the initial call)
// isMaximizingPlayer: True if current move is of maximizing player, else false
int minimax(int depth, int nodeIndex, int isMaximizingPlayer, int scores[], int h) {
    // Terminating condition. i.e leaf node is reached
    if (depth == h) {
        return scores[nodeIndex];
    }

    if (isMaximizingPlayer) {
        int best = INT_MIN;
        // Recur for left and right children
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, 0, scores, h);
            best = max(best, val);
        }
        return best;
    } else {
        int best = INT_MAX;
        // Recur for left and right children
        for (int i = 0; i < 2; i++) {
            int val = minimax(depth + 1, nodeIndex * 2 + i, 1, scores, h);
            best = min(best, val);
        }
        return best;
    }
}

// Helper function to calculate log base 2
int log2_val(int n) {
    int res = 0;
    while (n >>= 1) {
        res++;
    }
    return res;
}

// Driver code
int main() {
    int scores[] = {3, 5, 2, 9, 12, 5, 23, 23};
    int n = sizeof(scores) / sizeof(scores[0]);
    int h = log2_val(n); // Height of the game tree

    printf("Optimal value is : %d\n", minimax(0, 0, 1, scores, h));
    return 0;
} 