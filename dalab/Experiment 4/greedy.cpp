#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Activity {
    int start;
    int end;
};

bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

void activitySelection(vector<Activity>& activities) {
    
    sort(activities.begin(), activities.end(), compare);
  
    int n = activities.size();
    int lastSelected = 0;
    cout << "Selected Activities:\n";
    cout << "Activity " << lastSelected + 1 << " (Start: " << activities[lastSelected].start << ", End: " << activities[lastSelected].end << ")\n";
\
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[lastSelected].end) {
            cout << "Activity " << i + 1 << " (Start: " << activities[i].start << ", End: " << activities[i].end << ")\n";
            lastSelected = i; 
        }
    }
}

int main() {
    
    cout << "Test Case 1: All Activities Overlapping\n";
    vector<Activity> activities1 = {{1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}, {6, 9}};
    activitySelection(activities1);
    cout << "\n";

    
    cout << "Test Case 2: No Overlapping Activities\n";
    vector<Activity> activities2 = {{1, 3}, {4, 5}, {6, 7}, {8, 10}, {11, 12}};
    activitySelection(activities2);
    cout << "\n";

   
    cout << "Test Case 3: Large Activities with Small Gaps\n";
    vector<Activity> activities3 = {{1, 10}, {11, 20}, {21, 30}, {31, 40}, {41, 50}};
    activitySelection(activities3);
    cout << "\n";

    // Test Case 4: All Activities Start at the Same Time
    cout << "Test Case 4: All Activities Start at the Same Time\n";
    vector<Activity> activities4 = {{1, 3}, {1, 5}, {1, 6}, {1, 7}, {1, 4}};
    activitySelection(activities4);
    cout << "\n";

    cout << "Test Case 5: Varying Sizes of Activities\n";
    vector<Activity> activities5 = {{1, 3}, {2, 6}, {5, 7}, {8, 9}, {7, 10}, {9, 12}};
    activitySelection(activities5);
    cout << "\n";

    
    cout << "Test Case 6: Activities with Large Gaps Between Them\n";
    vector<Activity> activities6 = {{1, 3}, {10, 15}, {20, 25}, {30, 35}};
    activitySelection(activities6);
    cout << "\n";

    
    cout << "Test Case 7: Activities with Random Overlap\n";
    vector<Activity> activities7 = {{1, 6}, {2, 8}, {3, 5}, {7, 9}, {8, 10}};
    activitySelection(activities7);
    cout << "\n";

    return 0;
}

