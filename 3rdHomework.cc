#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

class ListOfArrays {
    class ArrayNode {
    public:
        int* data_;
        int size_;
        ArrayNode* prev_;
        ArrayNode* next_;

        ArrayNode(int* data, int size)
            : data_(data)
            , size_(size)
            , next_(0)
            , prev_(0)
        {}

        ~ArrayNode() { delete[] data_; }
    };

    ArrayNode* head_;
    int size_;

public:
    class Iterator {
        friend class ListOfArrays;

        ListOfArrays& list_;
        ArrayNode* current_;

    public:
        Iterator(ListOfArrays& list, ArrayNode* current)
            : list_(list)
            , current_(current)
        {}

        bool operator==(const Iterator& other)
        {
            return current_ == other.current_;
        }

        bool operator!=(const Iterator& other) { return !operator==(other); }

        Iterator& operator++()
        {
            current_ = current_->next_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator previous = *this;
            ++(*this);
            return previous;
        }

        int& operator[](const int& index) { return current_->data_[index]; }

        int size() { return current_->size_; }

        void show()
        {
            int i = 0;
            while (i < size()) {
                if (i != 0) {
                    cout << " ";
                }
                cout << current_->data_[i];
                ++i;
            }
        }

        double average() { return (double)sum() / size(); }

        double median()
        {
            if (size() % 2 == 0) {
                return (current_->data_[(size() / 2) - 1] + current_->data_[size() / 2]) / (double)2;
            }
            else {
                return current_->data_[(size() - 1) / 2];
            }
        }

        int sum()
        {
            int sum = 0;
            int i = 0;
            while (i < size()) {
                sum += current_->data_[i];
                ++i;
            }
            return sum;
        }

        Iterator& ordered(bool ascending = true)
        {

            if (ascending == false) {
                for (int i = 0; i < current_->size_; ++i) {
                    for (int j = 0; j < current_->size_ - i - 1; ++j) {
                        if (current_->data_[j] < current_->data_[j + 1]) {
                            current_->data_[j] = current_->data_[j] + current_->data_[j + 1];
                            current_->data_[j + 1] = current_->data_[j] - current_->data_[j + 1];
                            current_->data_[j] = current_->data_[j] - current_->data_[j + 1];
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < current_->size_; ++i) {
                    for (int j = 0; j < current_->size_ - i - 1; ++j) {
                        if (current_->data_[j] > current_->data_[j + 1]) {
                            current_->data_[j] = current_->data_[j] + current_->data_[j + 1];
                            current_->data_[j + 1] = current_->data_[j] - current_->data_[j + 1];
                            current_->data_[j] = current_->data_[j] - current_->data_[j + 1];
                        }
                    }
                }
            }
            return *this;
        }
    };
//16 i 20 popravka mai sa copy constructor
    ListOfArrays()
            : size_(0), head_(new ArrayNode(0, 0)) {
        head_->next_ = head_;
        head_->prev_ = head_;
    }

    ListOfArrays(const ListOfArrays& other)
        : size_(0),
          head_(new ArrayNode(0, 0)) {
      head_->next_ = head_;
      head_->prev_ = head_;     
      int arr[150];
      ArrayNode* point_to_new_node = other.head_->next_;
      for (int count = 0; count < other.size_; count++) {
      int i = 0;
        for (i = 0; i < point_to_new_node->size_; i++) {
          arr[i] = point_to_new_node->data_[i];
        }
        push(arr, 0, i);
        point_to_new_node = point_to_new_node->next_;
      }
    }

    ListOfArrays& operator=(const ListOfArrays& other) { 
      int arr[150];
      ArrayNode* point_to_new_node = other.head_->next_;
      for (int count = 0; count < other.size_; count++) {
      int i = 0;
        for (i = 0; i < point_to_new_node->size_; i++) {
          arr[i] = point_to_new_node->data_[i];
        }
        push(arr, 0, i);
        point_to_new_node = point_to_new_node->next_;
      }
      return *this;
    }


    int size() { return size_; }

    void push(int array[], int position, int length)
    {
        int* tmp = new int[length - position];
        int i = position;
        while (i < length) {
            tmp[i - position] = array[i];
            i++;
        }

        ArrayNode* new_node = new ArrayNode(tmp, length - position);
        head_->prev_->next_ = new_node;
        new_node->prev_ = head_->prev_;
        head_->prev_ = new_node;
        new_node->next_ = head_;

        size_++;
    }

    void averages(double averages[])
    {
        int i = 0;
        Iterator it = begin();
        while (it != end()) {
            averages[i] = it.average();
            it++;
            i++;
        }
    }

    void medians(double medians[])
    {
        int i = 0;
        Iterator it = begin();
        while (it != end()) {
            medians[i] = it.median();
            it++;
            i++;
        }
    }

    void sizes(int sizes[])
    {
        int i = 0;
        Iterator it = begin();
        while (it != end()) {
            sizes[i] = it.size();
            it++;
            i++;
        }
    }

    void sums(int sums[])
    {
        int i = 0;
        Iterator it = begin();
        while (it != end()) {
            sums[i] = it.sum();
            it++;
            i++;
        }
    }

    Iterator begin()
    {
        Iterator tmp(*this, head_->next_);
        return tmp;
    }

    Iterator end()
    {
        Iterator tmp(*this, head_);
        return tmp;
    }

    ListOfArrays& ordered(bool ascending = true)
    {
        Iterator it = begin();
        while( it != end()) {
            it.ordered(ascending);
             it++;
        }
        bool sorted = 0;
        while (!sorted) {
            sorted = 1;
            Iterator tmp = begin();
            Iterator it = ++begin();
            while (it != end()) {
                int min_size;
                if (it.size() > tmp.size()) {
                    min_size = tmp.size();
                }
                else {
                    min_size = it.size();
                }

                int i = 0;
                while (min_size > i) {
                    if ((ascending == 0 && tmp[i] < it[i]) || (ascending == 1 && tmp[i] > it[i])) {
                        int* arr = tmp.current_->data_;
                        int tmp_size = tmp.current_->size_;

                        tmp.current_->data_ = new int[it.size()];
                        for (int counter = 0; counter < it.size(); counter++) {
                            tmp.current_->data_[counter] = it.current_->data_[counter];
                        }
                        tmp.current_->size_ = it.size();

                        it.current_->data_ = new int[tmp_size];
                        for (int counter = 0; counter < tmp_size; counter++) {
                            it.current_->data_[counter] = arr[counter];
                        }
                        it.current_->size_ = tmp_size;

                        sorted = 0;
                        break;
                    }
                    if (tmp[i] != it[i]) {
                        break;
                    }
                    i++;
                }
                if (sorted == 1 && i == min_size) {
                    if ((ascending == 0 && tmp.size() < it.size()) || (ascending == 1 && tmp.size() > it.size())) {
                        int* arr = tmp.current_->data_;
                        int tmp_size = tmp.current_->size_;

                        tmp.current_->data_ = new int[it.size()];
                        for (int counter = 0; counter < it.size(); counter++) {
                            tmp.current_->data_[counter] = it.current_->data_[counter];
                        }
                        tmp.current_->size_ = it.size();

                        it.current_->data_ = new int[tmp_size];
                        for (int counter = 0; counter < tmp_size; counter++) {
                            it.current_->data_[counter] = arr[counter];
                        }
                        it.current_->size_ = tmp_size;

                        sorted = 0;
                    }
                }
                tmp++;
                it++;
            }
        }
        return *this;
    }

    ListOfArrays& operator*=(const int& k)
    {
        Iterator it = begin();
        while (it != end()) {
            for (int i = 0; i < it.size(); i++) {
                it[i] *= k;
            }
            it++;
        }
        return *this;
    }

    ListOfArrays& operator+=(const int& value)
    {
        Iterator it = begin();
        while (it != end()) {
            for (int i = 0; i < it.size(); i++) {
                it[i] += value;
            }
            it++;
        }
        return *this;
    }

    void show()
    {
        Iterator it = begin();
        while (it != end()) {
            it.show();
            if (it.current_->next_ != end().current_) {
                cout << "; ";
            }
            it++;
        }
    }
};

int main(int argc, char const* argv[])
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  //  try {
        string input;

        cout << "> ";
        getline(cin, input);
        if (input == "quit") {
            return 0;
        }

        ListOfArrays list;
        string arrays;
        istringstream in(input);

        while (getline(in, arrays, ';')) {
      istringstream members_of_array(arrays);
      int *my_arr = new int[10];
      int size = 0;
      while (members_of_array >> my_arr[size]) {
        size++;
      }
      if (size != 0) {
        list.push(my_arr, 0, size);
      }
    }

        while (true) {
            ListOfArrays l(list);
            ListOfArrays::Iterator it = l.end();

            cout << "> ";
            getline(cin, input);
            if (input == "quit") {
                break;
            }

            istringstream in(input);
            string full_commands;

            while (getline(in, full_commands, '.')) {
                istringstream command(full_commands);

                string post_command;
                getline(command, post_command, ':');
                istringstream command_ws(post_command);
                command_ws >> post_command;

                string spec;
                getline(command, spec);
                istringstream spec_ws(spec);
                spec_ws >> spec;

                if (!post_command.compare("ordered")) {
                    bool ascending = true;

                    if (!spec.compare("true")) {
                        ascending = true;
                    }
                    else if (!spec.compare("false")) {
                        ascending = false;
                    }

                    if (it == l.end()) {
                        l.ordered(ascending);
                    }
                    else {
                        it.ordered(ascending);
                    }
                }
                else if (!post_command.compare("mul")) {
                    int n = stoi(spec);

                    if (it == l.end()) {
                        l *= n;
                    }
                }
                else if (!post_command.compare("add")) {
                    int n = stoi(spec);

                    if (it == l.end()) {
                        l += n;
                    }
                }
                else if (!post_command.compare("show")) {
                    if (it == l.end()) {
                        l.show();
                    }
                    else {
                        it.show();
                    }
                    cout << endl;
                }
                else if (!post_command.compare("size")) {
                    if (it == l.end()) {
                        cout << l.size() << endl;
                    }
                    else {
                        cout << it.size() << endl;
                        ;
                    }
                }
                else if (!post_command.compare("averages")) {
                    double* avrg = new double[l.size()];
                    l.averages(avrg);
                    for (int i = 0; i < l.size(); i++) {
                        cout << avrg[i] << " ";
                    }
                    cout << endl;
                }
                else if (!post_command.compare("medians")) {
                    double* med = new double[l.size()];
                    l.medians(med);
                    for (int i = 0; i < l.size(); i++) {
                        cout << med[i] << " ";
                    }
                    cout << endl;
                }
                else if (!post_command.compare("sums")) {
                    int* sums = new int[l.size()];
                    l.sums(sums);
                    for (int i = 0; i < l.size(); i++) {
                        cout << sums[i] << " ";
                    }
                    cout << endl;
                }
                else if (!post_command.compare("sizes")) {
                    int* sizes = new int[l.size()];
                    l.sizes(sizes);
                    for (int i = 0; i < l.size(); i++) {
                        cout << sizes[i] << " ";
                    }
                    cout << endl;
                }
                else if (!post_command.compare("begin")) {
                    if (it == l.end()) {
                        it++;
                    }
                }
                else if (!post_command.compare("next")) {
                    if (it == l.end() || ++it == l.end()) {
                       // throw "ERROR: End of iteration"; - 1 greshka
                          cout << "ERROR: End of iteration" << endl;
                        	break;
                    }
                }
                else if (!post_command.compare("at")) {
                    int n = stoi(spec);
                    if (n < it.size() && n >= 0) {
                        cout << it[n] << endl;
                    }
                    else {
                        // throw "ERROR: Index out of bounds"; breakva i ne baca po uslovie
                        cout << "ERROR: Index out of bounds" << endl;
                    }
                }
                else if (!post_command.compare("average")) {
                    cout << it.average() << endl;
                }
                else if (!post_command.compare("median")) {
                    cout << it.median() << endl;
                }
                else if (!post_command.compare("sum")) {
                    cout << it.sum() << endl;
                }
                else {
                    // throw "ERROR: Unknown operation"; breakva i ne baca po uslovie
                    cout << "ERROR: Unknown operation" << endl;
                }
            }
        }
    //}
   /* catch (const char* err) {
        cout << err << endl;
    }*/

    return 0;
}
