#include <bits/stdc++.h>
using namespace std;

char logic(char c, int *flag){
 if (c == 'S') {*flag = 1; return 'S';}
 else return c;
 //else if (c == '.'){ *flag = 0; return 'D';}
}

int main(){
 int m, n;
 cin >> m >> n;
 char a[m][n];
 vector < pair<int,int> > v;

 for (int i = 0; i < m; i++){
   for (int j = 0; j < n; j++){
     cin >> a[i][j];
     if (a[i][j] == 'W') v.push_back(make_pair(i,j));
    }
  }
 int flag = 0;
 for (size_t i = 0; i < v.size(); i++){
   if (v[i].first - 1 >= 0){
     a[v[i].first - 1][v[i].second] = logic(a[v[i].first - 1][v[i].second], &flag);
    }
   if (v[i].first + 1 <= m-1 && flag != 1){
     a[v[i].first + 1][v[i].second] = logic(a[v[i].first + 1][v[i].second], &flag); }
   if (v[i].second - 1 >= 0 && flag != 1){
     a[v[i].first][v[i].second - 1] = logic(a[v[i].first][v[i].second - 1], &flag);}
   if (v[i].second + 1 <= n-1 && flag != 1){
     a[v[i].first][v[i].second +1] = logic(a[v[i].first][v[i].second +1], &flag);}
   if (flag == 1){ cout << "No" << endl; return 0;}
  }
 if (flag == 0){
   cout << "Yes" << endl;
   for (int i = 0; i < m; i++){
     for (int j = 0; j < n; j++){
       if (a[i][j] == '.') a[i][j] = 'D';
       cout << a[i][j];
      }
     cout << endl;
    }
  }
 return 0;
}