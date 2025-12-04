#include <bits/stdc++.h>
using namespace std;

struct Point { double x, y; };

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}

pair<Point,Point> bruteForce(Point* P, int n) {
    double d = 1e100;
    pair<Point,Point> best;
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(dist(P[i],P[j]) < d) {
                d = dist(P[i],P[j]);
                best = {P[i],P[j]};
            }
    return best;
}

pair<Point,Point> closestPairRec(Point* Px, Point* Py, int n) {
    if(n <= 3) return bruteForce(Px, n);

    int mid = n/2;
    Point midPoint = Px[mid];

    vector<Point> Qy, Ry;
    Qy.reserve(n); Ry.reserve(n);
    for(int i=0;i<n;i++)
        (Py[i].x < midPoint.x || (Py[i].x == midPoint.x && Py[i].y < midPoint.y) ? Qy : Ry).push_back(Py[i]);

    pair<Point,Point> q = closestPairRec(Px, Qy.data(), Qy.size());
    pair<Point,Point> r = closestPairRec(Px+mid, Ry.data(), Ry.size());

    double dq = dist(q.first, q.second);
    double dr = dist(r.first, r.second);
    double delta = min(dq, dr);
    pair<Point,Point> best = (dq < dr ? q : r);

    vector<Point> Sy;
    Sy.reserve(n);
    for(int i=0;i<n;i++)
        if(abs(Py[i].x - midPoint.x) <= delta)
            Sy.push_back(Py[i]);

    double d = delta;
    for(int i=0;i<(int)Sy.size();i++)
        for(int j=i+1;j<(int)Sy.size() && j<=i+8;j++) {
            double cur = dist(Sy[i], Sy[j]);
            if(cur < d) {
                d = cur;
                best = {Sy[i], Sy[j]};
            }
        }

    return best;
}

pair<Point,Point> closestPair(vector<Point>& P) {
    vector<Point> Px = P, Py = P;
    sort(Px.begin(), Px.end(), [](auto&a,auto&b){return a.x<b.x;});
    sort(Py.begin(), Py.end(), [](auto&a,auto&b){return a.y<b.y;});
    return closestPairRec(Px.data(), Py.data(), P.size());
}

vector<Point> readDataset(const string& filename) {
    ifstream infile(filename);
    if(!infile.is_open()) {
        cerr << "Error: Cannot open dataset file " << filename << endl;
        exit(1);
    }
    vector<Point> points;
    double x, y;
    while(infile >> x >> y) {
        points.push_back({x, y});
    }
    infile.close();
    return points;
}

void appendToCSV(const string& filename, const string& dataset, 
                 const Point& p1, const Point& p2, double distance, double time_ms) {
    ofstream outfile;
    ifstream testfile(filename);
    bool fileExists = testfile.good();
    testfile.close();
    
    outfile.open(filename, ios::app);
    if(!outfile.is_open()) {
        cerr << "Error: Cannot open results file " << filename << endl;
        exit(1);
    }
    
    if(!fileExists) {
        outfile << "Dataset,Point1_X,Point1_Y,Point2_X,Point2_Y,Distance,Time_ms\n";
    }
    
    outfile << fixed << setprecision(6);
    outfile << dataset << "," 
            << p1.x << "," << p1.y << "," 
            << p2.x << "," << p2.y << "," 
            << distance << "," << time_ms << "\n";
    
    outfile.close();
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cerr << "Usage: " << argv[0] << " <dataset_file> <results_file>\n";
        return 1;
    }
    
    string datasetFile = argv[1];
    string resultsFile = argv[2];
    
    vector<Point> P = readDataset(datasetFile);
    
    if(P.size() < 2) {
        cerr << "Error: Dataset must contain at least 2 points\n";
        return 1;
    }
    
    auto start = chrono::high_resolution_clock::now();
    auto ans = closestPair(P);
    auto end = chrono::high_resolution_clock::now();
    
    double time_ms = chrono::duration<double, milli>(end - start).count();
    double distance = dist(ans.first, ans.second);
    
    appendToCSV(resultsFile, datasetFile, ans.first, ans.second, distance, time_ms);
    
    cout << "Dataset: " << datasetFile << "\n";
    cout << "Points: " << P.size() << "\n";
    cout << "Closest pair: (" << ans.first.x << ", " << ans.first.y << ") and ("
         << ans.second.x << ", " << ans.second.y << ")\n";
    cout << "Distance: " << distance << "\n";
    cout << "Execution time: " << time_ms << " ms\n";
    
    return 0;
}
