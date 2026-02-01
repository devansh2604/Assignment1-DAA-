#include <bits/stdc++.h>
using namespace std;


// ============================================================
// 1) Binary Search
// ============================================================
int binarySearch(const vector<int> &arr, int target) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ============================================================
// 2) Merge Sort
// ============================================================
void mergeVec(vector<int> &a, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}

void mergeSort(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    mergeVec(a, l, m, r);
}

// ============================================================
// 3) Quick Sort
// ============================================================
int partitionVec(vector<int> &a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[high]);
    return i + 1;
}

void quickSort(vector<int> &a, int low, int high) {
    if (low < high) {
        int pi = partitionVec(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

// ============================================================
// 4) Maximum Subarray Sum (Divide & Conquer)
// ============================================================
long long maxCrossingSum(const vector<int> &a, int l, int m, int r) {
    long long leftSum = LLONG_MIN, sum = 0;
    for (int i = m; i >= l; i--) {
        sum += a[i];
        leftSum = max(leftSum, sum);
    }

    long long rightSum = LLONG_MIN;
    sum = 0;
    for (int i = m + 1; i <= r; i++) {
        sum += a[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

long long maxSubArraySumDC(const vector<int> &a, int l, int r) {
    if (l == r) return a[l];
    int m = l + (r - l) / 2;
    long long left = maxSubArraySumDC(a, l, m);
    long long right = maxSubArraySumDC(a, m + 1, r);
    long long cross = maxCrossingSum(a, l, m, r);
    return max({left, right, cross});
}

// ============================================================
// Additional Q1:
// ============================================================
bool canSplitWithMaxOR(const vector<int> &A, int M, int X) {
    int segments = 1;
    int curOR = 0;

    for (int v : A) {
        int newOR = (curOR | v);
        if (newOR <= X) {
            curOR = newOR;
        } else {
            segments++;
            curOR = v;
            if (segments > M) return false;
            if (curOR > X) return false;
        }
    }
    return true;
}

int minimizeMaxOR(const vector<int> &A, int M) {
    int lo = 0, hi = 0;
    for (int v : A) hi |= v;

    int ans = hi;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (canSplitWithMaxOR(A, M, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return ans;
}

// ============================================================
// Additional Q2:
// ============================================================
int longestGoodSubsequence(vector<int> A) {
    sort(A.begin(), A.end());
    int n = (int)A.size();
    int ans = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        while (A[r] - A[l] > 10) l++;
        ans = max(ans, r - l + 1);
    }
    return ans;
}

// ============================================================
// Additional Q3:
// ============================================================
long long medianRemovalFinalSum(const vector<int> &A) {
    int mn = *min_element(A.begin(), A.end());
    int mx = *max_element(A.begin(), A.end());
    return 1LL * mn + mx;
}

// ============================================================
// Additional Q4:
// ============================================================
long long specialitySum(vector<int> A, int K) {
    int n = (int)A.size();
    vector<int> sorted = A;
    sort(sorted.begin(), sorted.end());

    // for each value x, count greater = n - upper_bound(sorted,x)
    long long sum = 0;
    for (int x : A) {
        int greater = n - (int)(upper_bound(sorted.begin(), sorted.end(), x) - sorted.begin());
        if (greater >= K) sum += x;
    }
    return sum;
}

// ============================================================
// Additional Q5:
// ============================================================
long long minSquareSide(long long N, long long W, long long H) {
    long long lo = 0, hi = 1;
    while ((hi / W) * (hi / H) < N) {
        hi *= 2;
    }
    while (lo + 1 < hi) {
        long long mid = lo + (hi - lo) / 2;
        if ((mid / W) * (mid / H) >= N) hi = mid;
        else lo = mid;
    }
    return hi;
}

// ============================================================
// Additional Q6:
// ============================================================
struct Point {
    double x, y;
};

double distPts(const Point &a, const Point &b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteClosest(vector<Point> &pts, int l, int r, pair<Point, Point> &bestPair) {
    double mn = 1e18;
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            double d = distPts(pts[i], pts[j]);
            if (d < mn) {
                mn = d;
                bestPair = {pts[i], pts[j]};
            }
        }
    }
    return mn;
}

double stripClosest(vector<Point> &strip, double d, pair<Point, Point> &bestPair) {
    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) {
        return a.y < b.y;
    });

    double mn = d;
    for (int i = 0; i < (int)strip.size(); i++) {
        for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < mn; j++) {
            double dd = distPts(strip[i], strip[j]);
            if (dd < mn) {
                mn = dd;
                bestPair = {strip[i], strip[j]};
            }
        }
    }
    return mn;
}

double closestUtil(vector<Point> &pts, int l, int r, pair<Point, Point> &bestPair) {
    if (r - l <= 3) {
        return bruteClosest(pts, l, r, bestPair);
    }

    int mid = l + (r - l) / 2;
    Point midPoint = pts[mid];

    pair<Point, Point> leftPair, rightPair;
    double dl = closestUtil(pts, l, mid, leftPair);
    double dr = closestUtil(pts, mid + 1, r, rightPair);

    double d;
    if (dl < dr) {
        d = dl;
        bestPair = leftPair;
    } else {
        d = dr;
        bestPair = rightPair;
    }

    vector<Point> strip;
    strip.reserve(r - l + 1);
    for (int i = l; i <= r; i++) {
        if (fabs(pts[i].x - midPoint.x) < d)
            strip.push_back(pts[i]);
    }

    pair<Point, Point> stripPair = bestPair;
    double ds = stripClosest(strip, d, stripPair);

    if (ds < d) {
        bestPair = stripPair;
        return ds;
    }
    return d;
}

pair<double, pair<Point, Point>> closestPair(vector<Point> pts) {
    sort(pts.begin(), pts.end(), [](const Point &a, const Point &b) {
        return a.x < b.x;
    });

    pair<Point, Point> bestPair;
    double bestDist = closestUtil(pts, 0, (int)pts.size() - 1, bestPair);
    return {bestDist, bestPair};
}

// ============================================================
// Helpers
// ============================================================
void printVector(const vector<int> &a) {
    for (int x : a) cout << x << " ";
    cout << "\n";
}

// ============================================================
// MAIN (runs all  questions)
// ============================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "============================\n";
    cout << "UCS415 Lab Assignment 1\n";
    cout << "All Questions Combined\n";
    cout << "============================\n\n";

    // --------------------------------------------------------
    // Core Q1: Binary Search
    // --------------------------------------------------------
    cout << "Q1) Binary Search\n";
    vector<int> arr1 = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int target = 23;
    int idx = binarySearch(arr1, target);
    cout << "Array: ";
    printVector(arr1);
    cout << "Target = " << target << "\n";
    cout << "Found at index: " << idx << "\n\n";

    // --------------------------------------------------------
    // Core Q2: Merge Sort (two arrays)
    // --------------------------------------------------------
    cout << "Q2) Merge Sort\n";
    vector<int> m1 = {12, 11, 13, 5, 6, 7};
    vector<int> m2 = {38, 27, 43, 3, 9, 82, 10};

    cout << "Before sort arr1: ";
    printVector(m1);
    mergeSort(m1, 0, (int)m1.size() - 1);
    cout << "After sort arr1:  ";
    printVector(m1);

    cout << "Before sort arr2: ";
    printVector(m2);
    mergeSort(m2, 0, (int)m2.size() - 1);
    cout << "After sort arr2:  ";
    printVector(m2);
    cout << "\n";

    // --------------------------------------------------------
    // Core Q3: Quick Sort
    // --------------------------------------------------------
    cout << "Q3) Quick Sort\n";
    vector<int> q = {4, 2, 6, 9, 2};
    cout << "Before: ";
    printVector(q);
    quickSort(q, 0, (int)q.size() - 1);
    cout << "After:  ";
    printVector(q);
    cout << "\n";

    // --------------------------------------------------------
    // Core Q4: Maximum Subarray Sum
    // --------------------------------------------------------
    cout << "Q4) Maximum Subarray Sum (Divide & Conquer)\n";
    vector<int> ms = {-2, -5, 6, -2, -3, 1, 5, -6};
    cout << "Array: ";
    printVector(ms);
    long long maxSum = maxSubArraySumDC(ms, 0, (int)ms.size() - 1);
    cout << "Maximum Subarray Sum = " << maxSum << "\n\n";

    // --------------------------------------------------------
    // Additional Q1
    // --------------------------------------------------------
    cout << "Additional Q1) Minimize Maximum Bitwise OR of at-most M segments\n";
    // Example demo (You can change A and M)
    vector<int> A1 = {5, 1, 2, 7, 3};
    int M = 2;
    cout << "Array: ";
    printVector(A1);
    cout << "M = " << M << "\n";
    cout << "Minimum possible maximum OR = " << minimizeMaxOR(A1, M) << "\n\n";

    // --------------------------------------------------------
    // Additional Q2
    // --------------------------------------------------------
    cout << "Additional Q2) Longest Good Subsequence (abs diff <= 10)\n";
    vector<int> A2 = {1, 15, 6, 9, 12, 3, 8, 20};
    cout << "Array: ";
    printVector(A2);
    cout << "Answer = " << longestGoodSubsequence(A2) << "\n\n";

    // --------------------------------------------------------
    // Additional Q3
    // --------------------------------------------------------
    cout << "Additional Q3) Repeated Median Removal => Final Sum\n";
    vector<int> A3 = {1, 2, 3, 4};
    cout << "Array: ";
    printVector(A3);
    cout << "Final Sum (min + max) = " << medianRemovalFinalSum(A3) << "\n\n";

    // --------------------------------------------------------
    // Additional Q4
    // --------------------------------------------------------
    cout << "Additional Q4) Speciality of sequence\n";
    vector<int> A4 = {3, 1, 5, 2, 4};
    int K = 2;
    cout << "Array: ";
    printVector(A4);
    cout << "K = " << K << "\n";
    cout << "Speciality Sum = " << specialitySum(A4, K) << "\n\n";

    // --------------------------------------------------------
    // Additional Q5
    // --------------------------------------------------------
    cout << "Additional Q5) Minimum Square Size to fit N rectangles (W x H)\n";
    // Demo testcases:
    // Format: N H W (as per screenshot)
    vector<tuple<long long, long long, long long>> tests = {
        {10, 2, 3},
        {5, 4, 4},
        {20, 1, 2}
    };

    for (int i = 0; i < (int)tests.size(); i++) {
        auto [N, H, W] = tests[i];
        cout << "Test " << (i + 1) << ": N=" << N << ", H=" << H << ", W=" << W
             << " => min square side = " << minSquareSide(N, W, H) << "\n";
    }
    cout << "\n";

    // --------------------------------------------------------
    // Additional Q6
    // --------------------------------------------------------
    cout << "Additional Q6) Closest Pair of Points (Divide & Conquer)\n";
    vector<Point> pts = {
        {9,3},{2,6},{15,3},{5,1},
        {1,2},{12,4},{7,2},{4,7},
        {16,5},{3,3},{10,5},{6,4},
        {14,6},{8,6},{11,1},{13,2}
    };

    auto res = closestPair(pts);
    double d = res.first;
    Point p1 = res.second.first;
    Point p2 = res.second.second;

    cout << "Closest Pair: (" << p1.x << "," << p1.y << ") and (" << p2.x << "," << p2.y << ")\n";
    cout << "Minimum Distance = " << fixed << setprecision(6) << d << "\n\n";

    cout << "✅ Done. Copy-paste this entire file into your GitHub.\n";
    return 0;
}
