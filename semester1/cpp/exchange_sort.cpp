#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    cout << "Please input 8 players' name with their height and weight."
         << endl;
    /*char name[8][20];*/
    string name[8];
    int height[8], weight[8];
    for (int i = 0; i < 8; i++) {
        /*cin>>name[i][20]>>height[i]>>weight[i];*/
        cin >> name[i] >> height[i] >> weight[i];
    }

    //
    cout << "===============" << endl;
    cout << "Sort by height:" << endl;
    cout << "===============" << endl;
    //

    int index_height[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }, temp_height;
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (height[index_height[j]] > height[index_height[i]]) {
                temp_height = index_height[i];
                index_height[i] = index_height[j];
                index_height[j] = temp_height;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        /*cout<<setw(12)<<name[index[i]][20]<<setw(7)<<height[index[i]]<<setw(8)<<endl;*/
        cout << setw(12) << name[index_height[i]] << setw(7)
             << height[index_height[i]] << setw(8) << weight[index_height[i]]
             << endl;
    }

    //
    cout << "===============" << endl;
    cout << "Sort by weight:" << endl;
    cout << "===============" << endl;
    //

    int index_weight[8] = { 0, 1, 2, 3, 4, 5, 6, 7 }, temp_weight;
    for (int i = 0; i < 7; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (weight[index_weight[j]] > weight[index_weight[i]]) {
                temp_weight = index_weight[i];
                index_weight[i] = index_weight[j];
                index_weight[j] = temp_weight;
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        cout << setw(12) << name[index_weight[i]] << setw(7)
             << height[index_weight[i]] << setw(8) << weight[index_weight[i]]
             << endl;
    }

    //
    cout << "===============" << endl;
    cout << "Original input order:" << endl;
    cout << "===============" << endl;
    //

    for (int i = 0; i < 8; i++) {
        cout << setw(12) << name[i] << setw(7) << height[i] << setw(8)
             << weight[i] << endl;
    }

    return 0;
}
