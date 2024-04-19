#include "SortUtils.hpp"
#include "DataBase.hpp"
#include "DataPoint.hpp"
#include <vector>

using namespace std;

int CompareByCatAndTS(const DataPoint& p1, const DataPoint& p2){
     if ((p1.GetC()>p2.GetC()) || (p1.GetC()==p2.GetC() && p1.GetTS()>p2.GetTS()))
          return 1;
     return 0;
}

int CompareByTS(const DataPoint& p1, const DataPoint& p2){
     if (p1.GetTS()>p2.GetTS())
          return 1;
     return 0;
}

void SwapIndices(int* indicesArray, int ind1, int ind2) {
     int aux = indicesArray[ind1]; 
     indicesArray[ind1] = indicesArray[ind2];
     indicesArray[ind2] = aux;
}

void SiftIndices(int* indices, const vector<DataPoint>& points, int i, int n, int (*funccomp)(const DataPoint&, const DataPoint&)){
     while (1) {
          int indmax = i;
          if (2*i+1<n && funccomp(points[indices[2*i+1]], points[indices[indmax]]))
               indmax = 2*i+1;
          if (2*i+2<n && funccomp(points[indices[2*i+2]], points[indices[indmax]]))
               indmax = 2*i+2;
          if (indmax == i) break;
          SwapIndices(indices, indmax, i);
          i = indmax;
     } 
}

void SortIndices(int* indices, const vector<DataPoint>& points, int n, int (*funccomp)(const DataPoint&, const DataPoint&)) {
     for (int i =n/2; i>=0; i--)
          SiftIndices(indices,points, i,n,funccomp);
          
     //check
     /*
     for (int i = 0; i<_countPoints/2; ++i) {
         DataPoint& dp1 = _data_points[indices[i]];
         if (2*i+1>=_countPoints) continue; 
         DataPoint& dp2 = _data_points[indices[2*i+1]];
         if (funccomp(dp2,dp1)) cout<<"error child left"<<endl;
         if (2*i+2>=_countPoints) continue; 
         DataPoint& dp3 = _data_points[indices[2*i+1]];
         if (funccomp(dp3,dp1)) cout<<"error child right"<<endl;
     }
     */

     for (int i = n-1; i>=1; i--) {
         SwapIndices(indices, 0, i);
         SiftIndices(indices,points, 0,i,funccomp);
     }
     
     //check
     /*
     for (int i = 0; i<_countPoints-1; ++i) {
         DataPoint& dp1 = _data_points[indices[i]];
         DataPoint& dp2 = _data_points[indices[i+1]];
         if (funccomp(dp1, dp2)) {
               cout<<"not sorted"<<endl;
               cout<<dp1.GetTS()<<endl;
               cout<<dp2.GetTS()<<endl;
         }
     }
     */
}

int GetFirstPositionGETS(float ts, int* indices, const vector<DataPoint>& points, int start, int end) {
     /*int i = start;
     while (ts>_data_points[indices[i]].GetTS())
          i++;
     */

     // the range from start to end (inc start, exc end) is sorted by ts
     while (start<end) {
          int mid = (start+end)/2;
          if (ts>points[indices[mid]].GetTS()) 
               start = mid+1;
          else
               end = mid;
     }
     
   
     int toreturn = end;
     /*if (i!=toreturn)
          cout<<"ERROR"<<" "<<i<<" "<<toreturn<<endl;*/
     return toreturn;
}

int GetLastPositionLETS(float ts, int* indices, const vector<DataPoint>& points, int start, int end)  {
     // the range from start to end (inc start, exc end) is sorted by ts
     
     /* int i = end-1;
     while (ts<_data_points[indices[i]].GetTS())
          i--;
     */
     while (start<end) {
          int mid = (start+end)/2;
          if (ts>=points[indices[mid]].GetTS()) 
               start = mid+1;
          else
               end = mid;
     }
          
     int toreturn = start-1;
     /*if (i!=toreturn)
          cout<<"ERROR"<<" "<<i<<" "<<toreturn<<endl;*/
     return toreturn;
     
}



