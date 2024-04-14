#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<tuple>
using namespace std;

struct Process {
	int pid; // Process ID
	int bt; // Burst Time
	int art; // Arrival Time
};
void findWaitingTime(Process proc[], int n,int wt[])
{
	int rt[n];

	// Copy the burst time into rt[]
	for (int i = 0; i < n; i++)
		rt[i] = proc[i].bt;
	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;
	// Process until all processes getscompleted
	while (complete != n) {
		for (int j = 0; j < n; j++) {
			if ((proc[j].art <= t) &&
			(rt[j] < minm) && rt[j] > 0) {
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}
		if (check == false) {
			t++;
			continue;
		}
		// Reduce remaining time by one
		rt[shortest]--;
		// Update minimum
		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;
		// If a process gets completely executed
		if (rt[shortest] == 0) {
			// Increment complete
			complete++;
			check = false;
			// Find finish time of current process
			finish_time = t + 1;
			// Calculate waiting time
			wt[shortest] = finish_time -proc[shortest].bt - proc[shortest].art;
			if (wt[shortest] < 0)
				wt[shortest] = 0;
		}
		// Increment time
		t++;
	}
}

void findTurnAroundTime(Process proc[], int n,int wt[], int tat[])
{
	// calculating turnaround time by adding bt[i] + wt[i]
	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}
// Function to calculate average time
void findavgTime(Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0,total_tat = 0;
	findWaitingTime(proc, n, wt);
	findTurnAroundTime(proc, n, wt, tat);
	cout << " P\t\t"
		<< "BT\t\t"
		<< "WT\t\t"
		<< "TAT\t\t\n";
	for (int i = 0; i < n; i++) {
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << proc[i].pid << "\t\t"
			<< proc[i].bt << "\t\t " << wt[i]
			<< "\t\t " << tat[i] << endl;
	}
	cout << "\nAverage waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}
int main()
{
	Process proc[] = { { 1, 2, 3}, { 2, 11, 25 },{ 3, 7, 12 }, { 4, 13, 10}, {5, 10, 14} };
	int n = sizeof(proc) / sizeof(proc[0]);
	findavgTime(proc, n);
	return 0;
}
