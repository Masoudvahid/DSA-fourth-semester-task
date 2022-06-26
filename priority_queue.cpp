// https://contest.yandex.ru/contest/38500/run-report/69151589/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::swap;

class PriorityQueue {
private:
    // return parent of `A[index]`
    // don't call this function if `index` is already a root node
    static int Parent(int index) {
        return (index - 1) / 2;
    }

    // return left child of `A[index]`
    static int Left(int index) {
        return (2 * index + 1);
    }

    // return right child of `A[index]`
    static int Right(int index) {
        return (2 * index + 2);
    }

    int Sift(int index) {
        int final_index = index;
        while (index && queue[Parent(index)] < queue[index]) {
            swap(queue[Parent(index)], queue[index]);
            index = Parent(index);
            final_index = index;
        }
        return final_index;
    }

    int Heapify(int index) {
        if (queue.size() - 1 < Left(index)) {
            return index;
        }

        int final_index = index;
        int left = Left(index);

        if (Right(index) < queue.size() && queue[Right(index)] > queue[left]) {
            left = Right(index);
        }
        if (queue[left] > queue[index]) {
            std::swap(queue[index], queue[left]);
            Heapify(left);
        } else {
            return final_index;
        }
    }


public:
    explicit PriorityQueue(int queue_size) : queue_size(queue_size) {}


    int AddElement(int value) {
        if (queue.size() == queue_size) {
            return -2;
        }
        queue.push_back(value);
        int index = Sift(queue.size() - 1);
        return index;
    }

    int ExtractMax() {
        if (queue.empty()) {
            return -1;
        }
        // Max element is always the root
        int max_element = queue[0];
        swap(queue[0], queue[queue.size() - 1]);
        queue.pop_back();
        if (!queue.empty()) {
            cout << Heapify(0) + 1 << " ";
        } else {
            cout << 0 << " ";
        }
        return max_element;
    }

    ~PriorityQueue() {
        for (const auto &item: queue) {
            cout << item << " ";
        }
    }

private:
    int queue_size;
    vector<int> queue;

};

int main() {
    int queue_size;
    int number_of_requests;

    cin >> queue_size;
    cin >> number_of_requests;

    PriorityQueue priorityQueue(queue_size);

    for (int i = 0; i < number_of_requests; i++) {
        int request_type;
        cin >> request_type;

        if (request_type == 1) { // Extract max
            cout << priorityQueue.ExtractMax() << "\n";

        } else if (request_type == 2) { // Add item to queue
            int value;
            cin >> value;
            cout << priorityQueue.AddElement(value) + 1 << "\n";
        }
    }
}
