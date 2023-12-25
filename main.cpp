#include "FQueue.h"

int main() {
	try {
		FQueue fifoQueue;

		// Enqueue elements
		for (int i = 1; i <= 5; ++i) {
			FQInfo* pInfo = new FQInfo(i * 10);
			fifoQueue.FQEnqueue(pInfo);
		}

		// Display elements in the queue
		cout << "Queue elements: ";
		while (!fifoQueue.FQEmpty()) {
			FQInfo* pInfo = fifoQueue.FQDequeue();
			cout << *pInfo << " ";
			delete pInfo;
		}

		cout << endl;
	} catch (const FifoException& ex) {
		cerr << "Exception caught: " << ex.getReason() << endl;
	}

	return 0;
}
