#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class W {
public:
   int adj_matrix[8][8] = {};
   int dis_matrix[8][8] = {};
   int pred[8][8] = {};
   vector<int> order;
   void print_adj_list();
   void Initialize_dis_matrix(); 
   void Initialize_pred();
   void FloydWarshall(int s, int e);
   void path_checking();
};

void W::print_adj_list() {
   for (int i = 0; i < 8; i++) {
       cout << "Vertex" << i + 1 << " :";
       for (int j = 0; j < 8; j++) {
           if (adj_matrix[i][j] != 0) {
               cout << " -> " << j + 1;
           }
       }
       cout << endl << endl;
   }
}

void W::Initialize_dis_matrix() {
   for (int i = 0; i < 8; i++) {
       for (int j = 0; j < 8; j++) {
           if (dis_matrix[i][j] == 0 && i != j) {
               dis_matrix[i][j] = 999;
           }
       }
   }
}

void W::Initialize_pred() {
   for (int i = 0; i < 8; i++) {
       for (int j = 0; j < 8; j++) {
           if (adj_matrix[i][j] != 0) {
               pred[i][j] = i + 1;
           }
           else {
               pred[i][j] = -1;
           }
       }
   }
}

void W::FloydWarshall(int s, int e) {
   order.clear();
   
   for (int k = 0; k < 8; k++) {
       for (int i = 0; i < 8; i++) {
           for (int j = 0; j < 8; j++) {
               if (dis_matrix[i][j] > dis_matrix[i][k] + dis_matrix[k][j]) {
                   dis_matrix[i][j] = dis_matrix[i][k] + dis_matrix[k][j];
                   pred[i][j] = pred[k][j];
               }
           }
       }
   }
   
   int current = e;
   while (current != s) {
       order.push_back(current);
       current = pred[s-1][current-1];
   }
   order.push_back(s);
}

void W::path_checking() {
   cout << "Enter start point: ";
   int start;
   cin >> start;
   cout << "Enter end point: ";
   int end;
   cin >> end;

   FloydWarshall(start, end);

   cout << "Shortest path order: ";
   for (int i = order.size() - 1; i > 0; i--) {
       cout << order[i] << " -> ";
   }
   cout << order[0] << endl;
   
   cout << "Path length: " << dis_matrix[start - 1][end - 1] << endl;
}

int main() {
   W f;

   ifstream ifs;
   int x;
   ifs.open("/Users/brady/Desktop/Data Structure/adjacency_matrix.txt");
   if (!ifs.is_open()) {
       cout << "Failed to open file.\n";
   }
   else {
       for (int i = 0; i < 8; i++) {
           for (int j = 0; j < 8; j++) {
               ifs >> x;
               f.adj_matrix[i][j] = x;
           }
       }
   }
   ifs.close();

   int y;
   ifs.open("/Users/brady/Desktop/Data Structure/distance_matrix.txt");
   if (!ifs.is_open()) {
       cout << "Failed to open file.\n";
   }
   else {
       for (int i = 0; i < 8; i++) {
           for (int j = 0; j < 8; j++) {
               ifs >> y;
               f.dis_matrix[i][j] = y;
           }
       }
   }
   ifs.close();

   f.print_adj_list();
   f.Initialize_dis_matrix();
   f.Initialize_pred();
  
   f.path_checking();
   cout << "Search again? Y/N" << endl;
   char n;
   cin >> n;
   while (n == 'Y') {
       f.path_checking();
       cout << "Search again? Y/N" << endl;
       cin >> n;
   }

   return 0;
}