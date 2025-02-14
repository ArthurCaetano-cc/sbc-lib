#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Activity {
    int start, end;
};

bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

// Function to find the maximum number of non-overlapping activities
void activitySelection(vector<Activity>& activities) {
    // Sort activities by end time
    sort(activities.begin(), activities.end(), compare);

    cout << "Selected activities:\n";
    int count = 1; 
    cout << "(" << activities[0].start << ", " << activities[0].end << ")\n";
    
    int lastEnd = activities[0].end;

    for (size_t i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastEnd) {
            cout << "(" << activities[i].start << ", " << activities[i].end << ")\n";
            lastEnd = activities[i].end;
            count++;
        }
    }

    cout << count << endl;
}

int main() {
    int n;
    cin >> n;

    vector<Activity> activities(n);
    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].end;
    }

    activitySelection(activities);

    return 0;
}
