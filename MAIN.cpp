#include <bits/stdc++.h>
using namespace std;

const int ONE_DAY = 24 * 60 * 60;
const int MAX_BOOKS = 100;
const int MAX_MEMBERS = 100;
const int MAX_RECORDS = 500;
const int MAX_WAIT = 10;
const int MAX_QUEUE = MAX_BOOKS;
const int MAX_STACK = 100;
const int MAX_ACTIVITY = 50;
const int MAX_FIELDS = 10;
const int MAX_TOKENS = 100;
const int HASH_SIZE = 31;
const int SMALL_MATRIX = 12;

class LibraryError
{
private:
    string message;

public:
    LibraryError(string message) { this->message = message; }
    string what() { return message; }
};

string getDate(time_t t)
{
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", localtime(&t));
    return string(buffer);
}

string toLower(string text)
{
    for (int i = 0; i < (int)text.length(); i++)
        text[i] = tolower(text[i]);
    return text;
}

int split(string line, char separator, string parts[], int maxParts)
{
    int count = 0;
    string part = "";
    for (int i = 0; i < (int)line.length(); i++)
    {
        if (line[i] == separator)
        {
            if (count < maxParts)
                parts[count++] = part;
            part = "";
        }
        else
        {
            part += line[i];
        }
    }
    if (count < maxParts)
        parts[count++] = part;
    return count;
}

long long toNumber(string text)
{
    if (text.empty())
        throw LibraryError("empty number");
    long long value = 0;
    int start = 0;
    bool negative = false;
    if (text[0] == '-')
    {
        negative = true;
        start = 1;
    }
    if (start == (int)text.length())
        throw LibraryError("not a number: " + text);
    for (int i = start; i < (int)text.length(); i++)
    {
        if (text[i] < '0' || text[i] > '9')
            throw LibraryError("not a number: " + text);
        value = value * 10 + (text[i] - '0');
    }
    if (negative)
        return -value;
    return value;
}

int inputInt(string message)
{
    int number;
    while (true)
    {
        cout << message;
        if (cin >> number)
        {
            cin.ignore(1000, '\n');
            return number;
        }
        if (cin.eof())
            exit(0);
        cout << "Invalid input! Please enter a number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

string inputString(string message)
{
    string text;
    while (true)
    {
        cout << message;
        getline(cin, text);
        if (cin.eof())
            exit(0);
        if (!text.empty())
            return text;
        cout << "Input cannot be empty!\n";
    }
}

inline string line(int length) { return string(length, '-'); }

template <class T>
void swapValues(T &first, T &second)
{
    T temp = first;
    first = second;
    second = temp;
}

template <class T>
void bubbleSort(T list[], int size, bool (*comesAfter)(T &, T &))
{
    for (int i = 0; i < size - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (comesAfter(list[j], list[j + 1]))
            {
                swapValues(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

template <class T>
void insertionSort(T list[], int size, bool (*comesAfter)(T &, T &))
{
    for (int i = 1; i < size; i++)
    {
        T current = list[i];
        int j = i - 1;
        while (j >= 0 && comesAfter(list[j], current))
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = current;
    }
}

template <class T>
void selectionSort(T list[], int size, bool (*comesAfter)(T &, T &))
{
    for (int i = 0; i < size - 1; i++)
    {
        int first = i;
        for (int j = i + 1; j < size; j++)
            if (comesAfter(list[first], list[j]))
                first = j;
        if (first != i)
            swapValues(list[i], list[first]);
    }
}

template <class T>
void mergeHalves(T list[], int left, int mid, int right, bool (*comesAfter)(T &, T &))
{
    int size = right - left + 1;
    T *temp = new T[size];
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        if (comesAfter(list[i], list[j]))
            temp[k++] = list[j++];
        else
            temp[k++] = list[i++];
    }
    while (i <= mid)
        temp[k++] = list[i++];
    while (j <= right)
        temp[k++] = list[j++];
    for (k = 0; k < size; k++)
        list[left + k] = temp[k];
    delete[] temp;
}

template <class T>
void mergeSort(T list[], int left, int right, bool (*comesAfter)(T &, T &))
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort(list, left, mid, comesAfter);
    mergeSort(list, mid + 1, right, comesAfter);
    mergeHalves(list, left, mid, right, comesAfter);
}

template <class T>
int partitionAround(T list[], int low, int high, bool (*comesAfter)(T &, T &))
{
    T pivot = list[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (!comesAfter(list[j], pivot))
        {
            i++;
            swapValues(list[i], list[j]);
        }
    }
    swapValues(list[i + 1], list[high]);
    return i + 1;
}

template <class T>
void quickSort(T list[], int low, int high, bool (*comesAfter)(T &, T &))
{
    if (low >= high)
        return;
    int pivotIndex = partitionAround(list, low, high, comesAfter);
    quickSort(list, low, pivotIndex - 1, comesAfter);
    quickSort(list, pivotIndex + 1, high, comesAfter);
}

class StringStack
{
private:
    string items[MAX_STACK];
    int top;

public:
    StringStack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK - 1; }
    int size() { return top + 1; }

    void push(string item)
    {
        if (isFull())
            throw LibraryError("Stack overflow!");
        items[++top] = item;
    }

    string pop()
    {
        if (isEmpty())
            throw LibraryError("Stack underflow!");
        return items[top--];
    }

    string peek()
    {
        if (isEmpty())
            throw LibraryError("Stack is empty!");
        return items[top];
    }

    void removeBottom()
    {
        if (isEmpty())
            return;
        for (int i = 0; i < top; i++)
            items[i] = items[i + 1];
        top--;
    }
};

class CircularQueue
{
private:
    int items[MAX_QUEUE];
    int front, rear, count, capacity;

public:
    CircularQueue(int capacity = MAX_QUEUE)
    {
        if (capacity > MAX_QUEUE)
            capacity = MAX_QUEUE;
        if (capacity < 1)
            capacity = 1;
        this->capacity = capacity;
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
    int size() { return count; }

    void enqueue(int value)
    {
        if (isFull())
            throw LibraryError("Queue overflow!");
        rear = (rear + 1) % capacity;
        items[rear] = value;
        count++;
    }

    int dequeue()
    {
        if (isEmpty())
            throw LibraryError("Queue underflow!");
        int value = items[front];
        front = (front + 1) % capacity;
        count--;
        return value;
    }

    int peek()
    {
        if (isEmpty())
            throw LibraryError("Queue is empty!");
        return items[front];
    }

    int at(int position) { return items[(front + position) % capacity]; }

    bool contains(int value)
    {
        for (int i = 0; i < count; i++)
            if (at(i) == value)
                return true;
        return false;
    }
};

struct BookNode
{
    int bookId;
    BookNode *next;
};

class BorrowedList
{
private:
    BookNode *head;
    int count;

public:
    BorrowedList()
    {
        head = NULL;
        count = 0;
    }

    ~BorrowedList()
    {
        while (head != NULL)
        {
            BookNode *next = head->next;
            delete head;
            head = next;
        }
    }

    int size() { return count; }
    BookNode *first() { return head; }

    bool contains(int bookId)
    {
        for (BookNode *node = head; node != NULL; node = node->next)
            if (node->bookId == bookId)
                return true;
        return false;
    }

    void insertAtEnd(int bookId)
    {
        BookNode *node = new BookNode;
        node->bookId = bookId;
        node->next = NULL;
        if (head == NULL)
        {
            head = node;
        }
        else
        {
            BookNode *last = head;
            while (last->next != NULL)
                last = last->next;
            last->next = node;
        }
        count++;
    }

    void remove(int bookId)
    {
        BookNode *current = head;
        BookNode *previous = NULL;
        while (current != NULL && current->bookId != bookId)
        {
            previous = current;
            current = current->next;
        }
        if (current == NULL)
            return;
        if (previous == NULL)
            head = current->next;
        else
            previous->next = current->next;
        delete current;
        count--;
    }
};

class Book
{
private:
    CircularQueue waitList;

public:
    int id;
    string title, author, category;
    int totalCopies, availableCopies;
    int timesIssued;

    Book() : waitList(MAX_WAIT)
    {
        id = 0;
        totalCopies = availableCopies = timesIssued = 0;
    }

    Book(int id, string title, string author, string category, int copies) : waitList(MAX_WAIT)
    {
        this->id = id;
        this->title = title;
        this->author = author;
        this->category = category;
        totalCopies = copies;
        availableCopies = copies;
        timesIssued = 0;
    }

    Book(const Book &other) : waitList(other.waitList)
    {
        id = other.id;
        title = other.title;
        author = other.author;
        category = other.category;
        totalCopies = other.totalCopies;
        availableCopies = other.availableCopies;
        timesIssued = other.timesIssued;
    }

    Book &operator=(const Book &other)
    {
        if (this == &other)
            return *this;
        waitList = other.waitList;
        id = other.id;
        title = other.title;
        author = other.author;
        category = other.category;
        totalCopies = other.totalCopies;
        availableCopies = other.availableCopies;
        timesIssued = other.timesIssued;
        return *this;
    }

    int getId() { return id; }

    int waitingCount() { return waitList.size(); }
    int firstWaiting() { return waitList.peek(); }
    int waitingAt(int position) { return waitList.at(position); }
    bool isWaiting(int memberId) { return waitList.contains(memberId); }
    void removeFirstWaiting() { waitList.dequeue(); }

    void addToWaitList(int memberId)
    {
        if (waitList.isFull())
            throw LibraryError("Waiting list is full!");
        waitList.enqueue(memberId);
    }

    Book &operator++()
    {
        timesIssued++;
        return *this;
    }

    Book operator++(int)
    {
        Book old = *this;
        timesIssued++;
        return old;
    }

    friend Book operator+(Book book, int copies);
    friend Book operator-(Book book, int copies);
    friend ostream &operator<<(ostream &out, Book &book);
    friend istream &operator>>(istream &in, Book &book);
};

Book operator+(Book book, int copies)
{
    book.totalCopies += copies;
    book.availableCopies += copies;
    return book;
}

Book operator-(Book book, int copies)
{
    book.totalCopies -= copies;
    book.availableCopies -= copies;
    return book;
}

ostream &operator<<(ostream &out, Book &book)
{
    out << left << setw(6) << book.id << setw(28) << book.title.substr(0, 27) << setw(20)
        << book.author.substr(0, 19) << setw(14) << book.category.substr(0, 13) << setw(10)
        << (to_string(book.availableCopies) + "/" + to_string(book.totalCopies)) << book.timesIssued << endl;
    return out;
}

istream &operator>>(istream &in, Book &book)
{
    book.title = inputString("Enter title: ");
    book.author = inputString("Enter author: ");
    book.category = inputString("Enter category: ");
    book.totalCopies = inputInt("Enter number of copies: ");
    book.availableCopies = book.totalCopies;
    return in;
}

void printBookHeader()
{
    cout << left << setw(6) << "ID" << setw(28) << "Title" << setw(20) << "Author" << setw(14) << "Category"
         << setw(10) << "Avail" << "Issued" << endl;
    cout << line(84) << endl;
}

class Person
{
protected:
    string name, phone;

public:
    Person(string name, string phone)
    {
        this->name = name;
        this->phone = phone;
    }
    virtual ~Person() {}

    string getName() { return name; }
    string getPhone() { return phone; }
    void setName(string name) { this->name = name; }
    void setPhone(string phone) { this->phone = phone; }
};

class Member : public Person
{
protected:
    int id;
    BorrowedList borrowedBooks;

public:
    int fine;
    static int totalMembers;

    Member(int id, string name, string phone) : Person(name, phone)
    {
        this->id = id;
        fine = 0;
        totalMembers++;
    }
    virtual ~Member() { totalMembers--; }

    virtual string getType() = 0;
    virtual int maxBooks() = 0;
    virtual int loanDays() = 0;
    virtual int finePerDay() = 0;

    int getId() { return id; }
    int getBorrowedCount() { return borrowedBooks.size(); }
    BookNode *firstBorrowed() { return borrowedBooks.first(); }
    bool hasBook(int bookId) { return borrowedBooks.contains(bookId); }
    void addBook(int bookId) { borrowedBooks.insertAtEnd(bookId); }
    void removeBook(int bookId) { borrowedBooks.remove(bookId); }

    friend ostream &operator<<(ostream &out, Member &member);
};

int Member::totalMembers = 0;

ostream &operator<<(ostream &out, Member &member)
{
    out << left << setw(7) << member.id << setw(10) << member.getType() << setw(22) << member.name.substr(0, 21)
        << setw(14) << member.phone << setw(10)
        << (to_string(member.getBorrowedCount()) + "/" + to_string(member.maxBooks())) << "Rs." << member.fine
        << endl;
    return out;
}

class Student : public Member
{
public:
    Student(int id, string name, string phone) : Member(id, name, phone) {}
    string getType() { return "Student"; }
    int maxBooks() { return 3; }
    int loanDays() { return 14; }
    int finePerDay() { return 5; }
};

class Faculty : public Member
{
public:
    Faculty(int id, string name, string phone) : Member(id, name, phone) {}
    string getType() { return "Faculty"; }
    int maxBooks() { return 5; }
    int loanDays() { return 30; }
    int finePerDay() { return 2; }
};

void printMemberHeader()
{
    cout << left << setw(7) << "ID" << setw(10) << "Type" << setw(22) << "Name" << setw(14) << "Phone"
         << setw(10) << "Books" << "Fine" << endl;
    cout << line(70) << endl;
}

bool authorComesAfter(Book &first, Book &second) { return toLower(first.author) > toLower(second.author); }
bool categoryComesAfter(Book &first, Book &second) { return toLower(first.category) > toLower(second.category); }
bool fewerCopiesComesAfter(Book &first, Book &second) { return first.availableCopies < second.availableCopies; }
bool nameComesAfter(Member *&first, Member *&second)
{
    return toLower(first->getName()) > toLower(second->getName());
}
bool smallerFineComesAfter(Member *&first, Member *&second) { return first->fine < second->fine; }

class Transaction
{
public:
    int bookId, memberId;
    time_t issueDate;
    int daysKept;
    int fine;
    bool returned;

    Transaction()
    {
        bookId = memberId = 0;
        issueDate = 0;
        daysKept = fine = 0;
        returned = false;
    }

    Transaction(int bookId, int memberId, time_t issueDate)
    {
        this->bookId = bookId;
        this->memberId = memberId;
        this->issueDate = issueDate;
        daysKept = 0;
        fine = 0;
        returned = false;
    }
};

inline int idOf(Book &book) { return book.getId(); }
inline int idOf(Member *member) { return member->getId(); }

template <class T>
int binarySearch(T list[], int low, int high, int id)
{
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (idOf(list[mid]) == id)
        return mid;
    if (idOf(list[mid]) < id)
        return binarySearch(list, mid + 1, high, id);
    return binarySearch(list, low, mid - 1, id);
}

struct PhoneNode
{
    string phone;
    int memberId;
    PhoneNode *next;
};

class PhoneHashTable
{
private:
    PhoneNode *buckets[HASH_SIZE];

    int hash(string phone)
    {
        unsigned long value = 0;
        for (int i = 0; i < (int)phone.length(); i++)
            value = value * 31 + phone[i];
        return value % HASH_SIZE;
    }

public:
    PhoneHashTable()
    {
        for (int i = 0; i < HASH_SIZE; i++)
            buckets[i] = NULL;
    }

    ~PhoneHashTable()
    {
        for (int i = 0; i < HASH_SIZE; i++)
        {
            while (buckets[i] != NULL)
            {
                PhoneNode *next = buckets[i]->next;
                delete buckets[i];
                buckets[i] = next;
            }
        }
    }

    void insert(string phone, int memberId)
    {
        int bucket = hash(phone);
        PhoneNode *node = new PhoneNode;
        node->phone = phone;
        node->memberId = memberId;
        node->next = buckets[bucket];
        buckets[bucket] = node;
    }

    int find(string phone)
    {
        for (PhoneNode *node = buckets[hash(phone)]; node != NULL; node = node->next)
            if (node->phone == phone)
                return node->memberId;
        return -1;
    }

    void remove(string phone)
    {
        int bucket = hash(phone);
        PhoneNode *current = buckets[bucket];
        PhoneNode *previous = NULL;
        while (current != NULL && current->phone != phone)
        {
            previous = current;
            current = current->next;
        }
        if (current == NULL)
            return;
        if (previous == NULL)
            buckets[bucket] = current->next;
        else
            previous->next = current->next;
        delete current;
    }

    int bucketOf(string phone) { return hash(phone); }
};

struct TreeNode
{
    string key;
    int bookIndex;
    TreeNode *left, *right;
};

class TitleTree
{
private:
    TreeNode *root;

    TreeNode *insert(TreeNode *node, string key, int bookIndex)
    {
        if (node == NULL)
        {
            node = new TreeNode;
            node->key = key;
            node->bookIndex = bookIndex;
            node->left = node->right = NULL;
        }
        else if (key < node->key)
        {
            node->left = insert(node->left, key, bookIndex);
        }
        else
        {
            node->right = insert(node->right, key, bookIndex);
        }
        return node;
    }

    void inorder(TreeNode *node, int result[], int &count)
    {
        if (node == NULL)
            return;
        inorder(node->left, result, count);
        result[count++] = node->bookIndex;
        inorder(node->right, result, count);
    }

    void search(TreeNode *node, string key, int result[], int &count)
    {
        if (node == NULL)
            return;
        if (key < node->key)
        {
            search(node->left, key, result, count);
        }
        else if (key > node->key)
        {
            search(node->right, key, result, count);
        }
        else
        {
            result[count++] = node->bookIndex;
            search(node->right, key, result, count);
        }
    }

    int height(TreeNode *node)
    {
        if (node == NULL)
            return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        return rightHeight + 1;
    }

    void destroy(TreeNode *node)
    {
        if (node == NULL)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    TitleTree() { root = NULL; }
    ~TitleTree() { destroy(root); }

    void insert(string title, int bookIndex) { root = insert(root, toLower(title), bookIndex); }

    int inorder(int result[])
    {
        int count = 0;
        inorder(root, result, count);
        return count;
    }

    int search(string title, int result[])
    {
        int count = 0;
        search(root, toLower(title), result, count);
        return count;
    }

    int height() { return height(root); }
};

struct HeapItem
{
    int timesIssued;
    int bookIndex;
};

class MaxHeap
{
private:
    HeapItem items[MAX_BOOKS];
    int count;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (items[parent].timesIssued >= items[index].timesIssued)
                return;
            swapValues(items[parent], items[index]);
            index = parent;
        }
    }

    void heapifyDown(int index)
    {
        while (true)
        {
            int largest = index;
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            if (leftChild < count && items[leftChild].timesIssued > items[largest].timesIssued)
                largest = leftChild;
            if (rightChild < count && items[rightChild].timesIssued > items[largest].timesIssued)
                largest = rightChild;
            if (largest == index)
                return;
            swapValues(items[index], items[largest]);
            index = largest;
        }
    }

public:
    MaxHeap() { count = 0; }

    bool isEmpty() { return count == 0; }

    void insert(int timesIssued, int bookIndex)
    {
        if (count == MAX_BOOKS)
            throw LibraryError("Heap is full!");
        items[count].timesIssued = timesIssued;
        items[count].bookIndex = bookIndex;
        heapifyUp(count);
        count++;
    }

    HeapItem extractMax()
    {
        if (isEmpty())
            throw LibraryError("Heap is empty!");
        HeapItem top = items[0];
        items[0] = items[--count];
        heapifyDown(0);
        return top;
    }
};

struct Term
{
    int row, column, value;
};

class SparseMatrix
{
private:
    Term terms[MAX_RECORDS];
    int termCount;
    int rows, columns;

public:
    SparseMatrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        termCount = 0;
    }

    int getRows() { return rows; }
    int getColumns() { return columns; }
    int getTermCount() { return termCount; }
    Term getTerm(int index) { return terms[index]; }

    void increment(int row, int column)
    {
        for (int i = 0; i < termCount; i++)
        {
            if (terms[i].row == row && terms[i].column == column)
            {
                terms[i].value++;
                return;
            }
        }
        if (termCount == MAX_RECORDS)
            throw LibraryError("Sparse matrix is full!");
        terms[termCount].row = row;
        terms[termCount].column = column;
        terms[termCount].value = 1;
        termCount++;
    }

    int get(int row, int column)
    {
        for (int i = 0; i < termCount; i++)
            if (terms[i].row == row && terms[i].column == column)
                return terms[i].value;
        return 0;
    }
};

class BookGraph
{
private:
    int **adjacency;
    int vertexCount;

public:
    BookGraph(int vertexCount)
    {
        this->vertexCount = vertexCount;
        adjacency = new int *[vertexCount];
        for (int i = 0; i < vertexCount; i++)
        {
            adjacency[i] = new int[vertexCount];
            for (int j = 0; j < vertexCount; j++)
                adjacency[i][j] = 0;
        }
    }

    ~BookGraph()
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] adjacency[i];
        delete[] adjacency;
    }

    void addEdge(int first, int second)
    {
        if (first == second)
            return;
        adjacency[first][second] = 1;
        adjacency[second][first] = 1;
    }

    int degree(int vertex)
    {
        int count = 0;
        for (int i = 0; i < vertexCount; i++)
            count += adjacency[vertex][i];
        return count;
    }

    int breadthFirst(int start, int order[], int level[])
    {
        bool *visited = new bool[vertexCount];
        int *distance = new int[vertexCount];
        for (int i = 0; i < vertexCount; i++)
        {
            visited[i] = false;
            distance[i] = 0;
        }
        CircularQueue queue(vertexCount);
        visited[start] = true;
        queue.enqueue(start);
        int count = 0;
        while (!queue.isEmpty())
        {
            int vertex = queue.dequeue();
            if (vertex != start)
            {
                order[count] = vertex;
                level[count] = distance[vertex];
                count++;
            }
            for (int next = 0; next < vertexCount; next++)
            {
                if (adjacency[vertex][next] == 1 && !visited[next])
                {
                    visited[next] = true;
                    distance[next] = distance[vertex] + 1;
                    queue.enqueue(next);
                }
            }
        }
        delete[] visited;
        delete[] distance;
        return count;
    }

    void depthFirst(int vertex, bool visited[], int group[], int &groupSize)
    {
        visited[vertex] = true;
        group[groupSize++] = vertex;
        for (int next = 0; next < vertexCount; next++)
            if (adjacency[vertex][next] == 1 && !visited[next])
                depthFirst(next, visited, group, groupSize);
    }
};

class FineCalculator
{
private:
    bool isOperator(string token) { return token == "+" || token == "-" || token == "*" || token == "/"; }

    int precedence(string token)
    {
        if (token == "*" || token == "/")
            return 2;
        if (token == "+" || token == "-")
            return 1;
        return 0;
    }

    int convert(string input[], int count, string output[], bool popOnEqual)
    {
        StringStack stack;
        int outputCount = 0;
        for (int i = 0; i < count; i++)
        {
            string token = input[i];
            if (token == "(")
            {
                stack.push(token);
            }
            else if (token == ")")
            {
                while (!stack.isEmpty() && stack.peek() != "(")
                    output[outputCount++] = stack.pop();
                if (stack.isEmpty())
                    throw LibraryError("Brackets do not match!");
                stack.pop();
            }
            else if (isOperator(token))
            {
                while (!stack.isEmpty() && isOperator(stack.peek()))
                {
                    int topPrecedence = precedence(stack.peek());
                    int currentPrecedence = precedence(token);
                    bool shouldPop = topPrecedence > currentPrecedence;
                    if (popOnEqual && topPrecedence == currentPrecedence)
                        shouldPop = true;
                    if (!shouldPop)
                        break;
                    output[outputCount++] = stack.pop();
                }
                stack.push(token);
            }
            else
            {
                output[outputCount++] = token;
            }
        }
        while (!stack.isEmpty())
        {
            string token = stack.pop();
            if (token == "(")
                throw LibraryError("Brackets do not match!");
            output[outputCount++] = token;
        }
        return outputCount;
    }

public:
    int tokenize(string expression, string tokens[])
    {
        int count = 0;
        int i = 0;
        while (i < (int)expression.length())
        {
            char character = expression[i];
            if (character == ' ')
            {
                i++;
            }
            else if (isdigit(character))
            {
                string number = "";
                while (i < (int)expression.length() && isdigit(expression[i]))
                    number += expression[i++];
                if (count == MAX_TOKENS)
                    throw LibraryError("Expression is too long!");
                tokens[count++] = number;
            }
            else if (character == '+' || character == '-' || character == '*' || character == '/' ||
                     character == '(' || character == ')')
            {
                if (count == MAX_TOKENS)
                    throw LibraryError("Expression is too long!");
                tokens[count++] = string(1, character);
                i++;
            }
            else
            {
                throw LibraryError(string("Invalid character in expression: ") + character);
            }
        }
        if (count == 0)
            throw LibraryError("Expression is empty!");
        return count;
    }

    int infixToPostfix(string infix[], int count, string postfix[]) { return convert(infix, count, postfix, true); }

    int infixToPrefix(string infix[], int count, string prefix[])
    {
        string reversed[MAX_TOKENS];
        for (int i = 0; i < count; i++)
        {
            string token = infix[count - 1 - i];
            if (token == "(")
                token = ")";
            else if (token == ")")
                token = "(";
            reversed[i] = token;
        }
        string converted[MAX_TOKENS];
        int convertedCount = convert(reversed, count, converted, false);
        for (int i = 0; i < convertedCount; i++)
            prefix[i] = converted[convertedCount - 1 - i];
        return convertedCount;
    }

    long long evaluatePostfix(string postfix[], int count)
    {
        StringStack stack;
        for (int i = 0; i < count; i++)
        {
            string token = postfix[i];
            if (!isOperator(token))
            {
                stack.push(token);
                continue;
            }
            if (stack.size() < 2)
                throw LibraryError("Invalid expression!");
            long long right = toNumber(stack.pop());
            long long left = toNumber(stack.pop());
            long long result = 0;
            if (token == "+")
                result = left + right;
            else if (token == "-")
                result = left - right;
            else if (token == "*")
                result = left * right;
            else
            {
                if (right == 0)
                    throw LibraryError("Cannot divide by zero!");
                result = left / right;
            }
            stack.push(to_string(result));
        }
        if (stack.size() != 1)
            throw LibraryError("Invalid expression!");
        return toNumber(stack.pop());
    }

    string join(string tokens[], int count)
    {
        string text = "";
        for (int i = 0; i < count; i++)
        {
            if (i > 0)
                text += " ";
            text += tokens[i];
        }
        return text;
    }

    void run()
    {
        cout << "Enter a fine expression using whole numbers, + - * / and brackets.\n";
        cout << "Example: (20-14)*5 means 20 days kept, 14 allowed, Rs.5 per late day.\n";
        string infix[MAX_TOKENS], postfix[MAX_TOKENS], prefix[MAX_TOKENS];
        int count = tokenize(inputString("Expression: "), infix);
        int postfixCount = infixToPostfix(infix, count, postfix);
        int prefixCount = infixToPrefix(infix, count, prefix);
        long long value = evaluatePostfix(postfix, postfixCount);
        cout << "Infix   : " << join(infix, count) << endl;
        cout << "Postfix : " << join(postfix, postfixCount) << endl;
        cout << "Prefix  : " << join(prefix, prefixCount) << endl;
        cout << "Fine    : Rs." << value << endl;
    }
};

class Library
{
private:
    Book books[MAX_BOOKS];
    int bookCount;
    Member *members[MAX_MEMBERS];
    int memberCount;
    Transaction records[MAX_RECORDS];
    int recordCount;
    StringStack activity;
    PhoneHashTable phoneTable;
    int nextBookId;
    int nextMemberId;

    int findBook(int id) { return binarySearch(books, 0, bookCount - 1, id); }
    int findMember(int id) { return binarySearch(members, 0, memberCount - 1, id); }

    int requireBook(int id)
    {
        int index = findBook(id);
        if (index == -1)
            throw LibraryError("Book not found!");
        return index;
    }

    int requireMember(int id)
    {
        int index = findMember(id);
        if (index == -1)
            throw LibraryError("Member not found!");
        return index;
    }

    int findOpenRecord(int bookId, int memberId)
    {
        for (int i = 0; i < recordCount; i++)
            if (records[i].bookId == bookId && records[i].memberId == memberId && !records[i].returned)
                return i;
        return -1;
    }

    string bookTitle(int id)
    {
        int index = findBook(id);
        if (index == -1)
            return "(deleted)";
        return books[index].title;
    }

    string memberName(int id)
    {
        int index = findMember(id);
        if (index == -1)
            return "(deleted)";
        return members[index]->getName();
    }

    int daysSince(time_t t) { return (int)((time(0) - t) / ONE_DAY); }

    void addActivity(string message)
    {
        if (activity.size() == MAX_ACTIVITY)
            activity.removeBottom();
        activity.push(getDate(time(0)) + "  " + message);
    }

    Book *copyBooks()
    {
        Book *list = new Book[bookCount];
        for (int i = 0; i < bookCount; i++)
            list[i] = books[i];
        return list;
    }

    Member **copyMembers()
    {
        Member **list = new Member *[memberCount];
        for (int i = 0; i < memberCount; i++)
            list[i] = members[i];
        return list;
    }

    void buildTitleTree(TitleTree &tree)
    {
        for (int i = 0; i < bookCount; i++)
            tree.insert(books[i].title, i);
    }

    void buildBorrowMatrix(SparseMatrix &matrix)
    {
        for (int i = 0; i < recordCount; i++)
        {
            int memberIndex = findMember(records[i].memberId);
            int bookIndex = findBook(records[i].bookId);
            if (memberIndex != -1 && bookIndex != -1)
                matrix.increment(memberIndex, bookIndex);
        }
    }

    void buildBookGraph(BookGraph &graph, SparseMatrix &matrix)
    {
        int booksOfMember[MAX_BOOKS];
        for (int row = 0; row < matrix.getRows(); row++)
        {
            int count = 0;
            for (int i = 0; i < matrix.getTermCount(); i++)
                if (matrix.getTerm(i).row == row)
                    booksOfMember[count++] = matrix.getTerm(i).column;
            for (int a = 0; a < count; a++)
                for (int b = a + 1; b < count; b++)
                    graph.addEdge(booksOfMember[a], booksOfMember[b]);
        }
    }

public:
    Library()
    {
        bookCount = memberCount = recordCount = 0;
        nextBookId = 1;
        nextMemberId = 1001;
    }

    ~Library()
    {
        for (int i = 0; i < memberCount; i++)
            delete members[i];
    }

    void addBook(string title, string author, string category, int copies)
    {
        if (bookCount == MAX_BOOKS)
            throw LibraryError("Library is full! Cannot add more books.");
        books[bookCount++] = Book(nextBookId, title, author, category, copies);
        addActivity("Added book " + to_string(nextBookId) + " - " + title);
        nextBookId++;
    }

    void addBook()
    {
        Book book;
        cin >> book;
        if (book.totalCopies <= 0)
            throw LibraryError("Copies must be more than 0.");
        addBook(book.title, book.author, book.category, book.totalCopies);
        cout << "Book added successfully! Book ID: " << nextBookId - 1 << endl;
    }

    void updateBook()
    {
        int id = inputInt("Enter book ID: ");
        int i = requireBook(id);
        cout << "1. Title\n2. Author\n3. Category\n4. Total copies\n";
        int choice = inputInt("What do you want to update? ");
        if (choice == 1)
            books[i].title = inputString("Enter new title: ");
        else if (choice == 2)
            books[i].author = inputString("Enter new author: ");
        else if (choice == 3)
            books[i].category = inputString("Enter new category: ");
        else if (choice == 4)
        {
            int issued = books[i].totalCopies - books[i].availableCopies;
            int newTotal = inputInt("Enter new total copies: ");
            if (newTotal <= 0 || newTotal < issued)
                throw LibraryError("Invalid! " + to_string(issued) + " copies are currently issued.");
            int difference = newTotal - books[i].totalCopies;
            if (difference > 0)
                books[i] = books[i] + difference;
            else
                books[i] = books[i] - (-difference);
        }
        else
        {
            throw LibraryError("Invalid choice!");
        }
        cout << "Book updated successfully!\n";
        addActivity("Updated book " + to_string(id));
    }

    void deleteBook()
    {
        int id = inputInt("Enter book ID: ");
        int i = requireBook(id);
        if (books[i].availableCopies != books[i].totalCopies)
            throw LibraryError("Cannot delete! Some copies are still issued.");
        addActivity("Deleted book " + to_string(id) + " - " + books[i].title);
        for (int j = i; j < bookCount - 1; j++)
            books[j] = books[j + 1];
        bookCount--;
        cout << "Book deleted successfully!\n";
    }

    void showAllBooks()
    {
        if (bookCount == 0)
        {
            cout << "No books in library.\n";
            return;
        }
        cout << "1. Sort by ID\n2. Sort by Title (binary search tree)\n3. Sort by Author (bubble sort)\n";
        cout << "4. Sort by Category (insertion sort)\n5. Most available copies first (selection sort)\n";
        int choice = inputInt("Enter choice: ");
        printBookHeader();
        if (choice == 2)
        {
            TitleTree tree;
            buildTitleTree(tree);
            int order[MAX_BOOKS];
            int count = tree.inorder(order);
            for (int i = 0; i < count; i++)
                cout << books[order[i]];
            cout << "Tree height: " << tree.height() << endl;
        }
        else if (choice >= 3 && choice <= 5)
        {
            Book *list = copyBooks();
            if (choice == 3)
                bubbleSort(list, bookCount, authorComesAfter);
            else if (choice == 4)
                insertionSort(list, bookCount, categoryComesAfter);
            else
                selectionSort(list, bookCount, fewerCopiesComesAfter);
            for (int i = 0; i < bookCount; i++)
                cout << list[i];
            delete[] list;
        }
        else
        {
            for (int i = 0; i < bookCount; i++)
                cout << books[i];
        }
        cout << "Total books: " << bookCount << endl;
    }

    void searchBookById()
    {
        int id = inputInt("Enter book ID: ");
        int i = requireBook(id);
        printBookHeader();
        cout << books[i];
        cout << "People in waiting list: " << books[i].waitingCount() << endl;
    }

    void searchBookByKeyword()
    {
        string key = toLower(inputString("Enter title / author / category keyword: "));
        bool found = false;
        for (int i = 0; i < bookCount; i++)
        {
            Book &book = books[i];
            if (toLower(book.title).find(key) != string::npos || toLower(book.author).find(key) != string::npos ||
                toLower(book.category).find(key) != string::npos)
            {
                if (!found)
                    printBookHeader();
                cout << book;
                found = true;
            }
        }
        if (!found)
            cout << "No matching book found.\n";
    }

    void searchBookByTitle()
    {
        string title = inputString("Enter exact title: ");
        TitleTree tree;
        buildTitleTree(tree);
        int matches[MAX_BOOKS];
        int count = tree.search(title, matches);
        if (count == 0)
            throw LibraryError("No book with this exact title.");
        printBookHeader();
        for (int i = 0; i < count; i++)
            cout << books[matches[i]];
    }

    void addMember(int type, string name, string phone)
    {
        if (memberCount == MAX_MEMBERS)
            throw LibraryError("Member list is full!");
        int owner = phoneTable.find(phone);
        if (owner != -1)
            throw LibraryError("Phone number is already used by member " + to_string(owner) + ".");
        Member *member;
        if (type == 1)
            member = new Student(nextMemberId, name, phone);
        else
            member = new Faculty(nextMemberId, name, phone);
        members[memberCount++] = member;
        phoneTable.insert(phone, nextMemberId);
        addActivity("Added member " + to_string(nextMemberId) + " - " + name);
        nextMemberId++;
    }

    void addMember()
    {
        cout << "1. Student\n2. Faculty\n";
        int type = inputInt("Enter member type: ");
        if (type != 1 && type != 2)
            throw LibraryError("Invalid type!");
        string name = inputString("Enter name: ");
        string phone = inputString("Enter phone: ");
        addMember(type, name, phone);
        cout << "Member added successfully! Member ID: " << nextMemberId - 1 << endl;
    }

    void updateMember()
    {
        int id = inputInt("Enter member ID: ");
        Member *member = members[requireMember(id)];
        cout << "1. Name\n2. Phone\n";
        int choice = inputInt("What do you want to update? ");
        if (choice == 1)
        {
            member->setName(inputString("Enter new name: "));
        }
        else if (choice == 2)
        {
            string phone = inputString("Enter new phone: ");
            int owner = phoneTable.find(phone);
            if (owner != -1 && owner != id)
                throw LibraryError("Phone number is already used by member " + to_string(owner) + ".");
            phoneTable.remove(member->getPhone());
            member->setPhone(phone);
            phoneTable.insert(phone, id);
        }
        else
        {
            throw LibraryError("Invalid choice!");
        }
        cout << "Member updated successfully!\n";
        addActivity("Updated member " + to_string(id));
    }

    void deleteMember()
    {
        int id = inputInt("Enter member ID: ");
        int i = requireMember(id);
        if (members[i]->getBorrowedCount() > 0)
            throw LibraryError("Cannot delete! Member still has books.");
        if (members[i]->fine > 0)
            throw LibraryError("Cannot delete! Member has unpaid fine of Rs." + to_string(members[i]->fine));
        addActivity("Deleted member " + to_string(id) + " - " + members[i]->getName());
        phoneTable.remove(members[i]->getPhone());
        delete members[i];
        for (int j = i; j < memberCount - 1; j++)
            members[j] = members[j + 1];
        memberCount--;
        cout << "Member deleted successfully!\n";
    }

    void showAllMembers()
    {
        if (memberCount == 0)
        {
            cout << "No members.\n";
            return;
        }
        cout << "1. Sort by ID\n2. Sort by Name (merge sort)\n";
        int choice = inputInt("Enter choice: ");
        printMemberHeader();
        if (choice == 2)
        {
            Member **list = copyMembers();
            mergeSort(list, 0, memberCount - 1, nameComesAfter);
            for (int i = 0; i < memberCount; i++)
                cout << *list[i];
            delete[] list;
        }
        else
        {
            for (int i = 0; i < memberCount; i++)
                cout << *members[i];
        }
        cout << "Total members: " << Member::totalMembers << endl;
    }

    void showMemberDetails()
    {
        int id = inputInt("Enter member ID: ");
        Member *member = members[requireMember(id)];
        cout << "\nID         : " << member->getId() << endl;
        cout << "Name       : " << member->getName() << endl;
        cout << "Type       : " << member->getType() << " (max " << member->maxBooks() << " books, "
             << member->loanDays() << " days, Rs." << member->finePerDay() << "/day fine)" << endl;
        cout << "Phone      : " << member->getPhone() << endl;
        cout << "Fine due   : Rs." << member->fine << endl;
        cout << "Books with member:\n";
        if (member->getBorrowedCount() == 0)
            cout << "  None\n";
        for (BookNode *node = member->firstBorrowed(); node != NULL; node = node->next)
        {
            cout << "  " << node->bookId << " - " << bookTitle(node->bookId);
            int r = findOpenRecord(node->bookId, id);
            if (r != -1)
                cout << " (due " << getDate(records[r].issueDate + member->loanDays() * ONE_DAY) << ")";
            cout << endl;
        }
    }

    void searchMemberByPhone()
    {
        string phone = inputString("Enter phone: ");
        cout << "Hash bucket: " << phoneTable.bucketOf(phone) << endl;
        int id = phoneTable.find(phone);
        if (id == -1)
            throw LibraryError("No member with this phone number.");
        printMemberHeader();
        cout << *members[requireMember(id)];
    }

    void issueBook()
    {
        int memberId = inputInt("Enter member ID: ");
        Member *member = members[requireMember(memberId)];
        int bookId = inputInt("Enter book ID: ");
        Book &book = books[requireBook(bookId)];

        if (member->fine > 0)
            throw LibraryError("Member has unpaid fine of Rs." + to_string(member->fine) +
                               ". Please pay the fine first.");
        if (member->getBorrowedCount() >= member->maxBooks())
            throw LibraryError("Limit reached! A " + member->getType() + " can borrow only " +
                               to_string(member->maxBooks()) + " books.");
        if (member->hasBook(bookId))
            throw LibraryError("Member already has this book.");
        if (book.availableCopies == 0)
            throw LibraryError("No copies available. You can reserve this book.");
        if (recordCount == MAX_RECORDS)
            throw LibraryError("Record list is full!");

        if (book.waitingCount() > 0)
        {
            if (book.firstWaiting() == memberId)
            {
                book.removeFirstWaiting();
            }
            else if (book.availableCopies <= book.waitingCount())
            {
                throw LibraryError("This book is reserved for member " + to_string(book.firstWaiting()) + " (" +
                                   memberName(book.firstWaiting()) + ").");
            }
        }

        time_t now = time(0);
        book.availableCopies--;
        ++book;
        member->addBook(bookId);
        records[recordCount++] = Transaction(bookId, memberId, now);

        cout << "Book issued successfully!\n";
        cout << "Issue date: " << getDate(now) << "   Due date: " << getDate(now + member->loanDays() * ONE_DAY)
             << endl;
        addActivity("Issued book " + to_string(bookId) + " to member " + to_string(memberId));
    }

    void returnBook()
    {
        int memberId = inputInt("Enter member ID: ");
        Member *member = members[requireMember(memberId)];
        int bookId = inputInt("Enter book ID: ");
        Book &book = books[requireBook(bookId)];

        int r = findOpenRecord(bookId, memberId);
        if (r == -1)
            throw LibraryError("This member has not borrowed this book.");

        int actualDays = daysSince(records[r].issueDate);
        int days = inputInt("Enter number of days book was kept (-1 for actual = " + to_string(actualDays) + "): ");
        if (days < 0)
            days = actualDays;

        int lateDays = days - member->loanDays();
        int fine = 0;
        if (lateDays > 0)
            fine = lateDays * member->finePerDay();

        records[r].returned = true;
        records[r].daysKept = days;
        records[r].fine = fine;
        member->fine += fine;
        member->removeBook(bookId);
        book.availableCopies++;

        if (fine > 0)
            cout << "Book returned " << lateDays << " day(s) late. Fine: Rs." << fine << endl;
        else
            cout << "Book returned on time. No fine.\n";

        if (book.waitingCount() > 0)
        {
            cout << "Note: This book is reserved. Please inform member " << book.firstWaiting() << " ("
                 << memberName(book.firstWaiting()) << ").\n";
        }
        addActivity("Returned book " + to_string(bookId) + " by member " + to_string(memberId));
    }

    void reserveBook()
    {
        int memberId = inputInt("Enter member ID: ");
        Member *member = members[requireMember(memberId)];
        int bookId = inputInt("Enter book ID: ");
        Book &book = books[requireBook(bookId)];

        if (member->hasBook(bookId))
            throw LibraryError("Member already has this book.");
        if (book.availableCopies > book.waitingCount())
            throw LibraryError("Book is available. You can issue it directly.");
        if (book.isWaiting(memberId))
            throw LibraryError("Member is already in the waiting list.");

        book.addToWaitList(memberId);
        cout << "Book reserved! Position in waiting list: " << book.waitingCount() << endl;
        addActivity("Member " + to_string(memberId) + " reserved book " + to_string(bookId));
    }

    void showWaitList()
    {
        int bookId = inputInt("Enter book ID: ");
        Book &book = books[requireBook(bookId)];
        if (book.waitingCount() == 0)
        {
            cout << "No one is waiting for this book.\n";
            return;
        }
        cout << "Waiting list for " << book.title << ":\n";
        for (int i = 0; i < book.waitingCount(); i++)
            cout << "  " << i + 1 << ". " << book.waitingAt(i) << " - " << memberName(book.waitingAt(i)) << endl;
    }

    void checkFine()
    {
        int id = inputInt("Enter member ID: ");
        Member *member = members[requireMember(id)];
        cout << member->getName() << " has fine of Rs." << member->fine << endl;
    }

    void payFine()
    {
        int id = inputInt("Enter member ID: ");
        Member *member = members[requireMember(id)];
        if (member->fine == 0)
            throw LibraryError("No fine to pay.");
        cout << "Fine due: Rs." << member->fine << endl;
        int amount = inputInt("Enter amount to pay: ");
        if (amount <= 0 || amount > member->fine)
            throw LibraryError("Invalid amount!");
        member->fine -= amount;
        cout << "Payment successful! Remaining fine: Rs." << member->fine << endl;
        addActivity("Member " + to_string(id) + " paid fine Rs." + to_string(amount));
    }

    void showPendingFines()
    {
        Member **list = copyMembers();
        quickSort(list, 0, memberCount - 1, smallerFineComesAfter);
        bool found = false;
        for (int i = 0; i < memberCount; i++)
        {
            if (list[i]->fine > 0)
            {
                if (!found)
                    printMemberHeader();
                cout << *list[i];
                found = true;
            }
        }
        delete[] list;
        if (!found)
            cout << "No pending fines.\n";
    }

    void showFineRules()
    {
        cout << "Student : max 3 books, 14 days, Rs.5 per late day\n";
        cout << "Faculty : max 5 books, 30 days, Rs.2 per late day\n";
        cout << "A member with unpaid fine cannot borrow books.\n";
    }

    void summaryReport()
    {
        int totalCopies = 0, available = 0, issuedNow = 0, overdue = 0, students = 0, faculty = 0;
        int fineCharged = 0, finePending = 0;
        for (int i = 0; i < bookCount; i++)
        {
            totalCopies += books[i].totalCopies;
            available += books[i].availableCopies;
        }
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i]->getType() == "Student")
                students++;
            else
                faculty++;
            finePending += members[i]->fine;
        }
        for (int i = 0; i < recordCount; i++)
        {
            Transaction &record = records[i];
            fineCharged += record.fine;
            if (!record.returned)
            {
                issuedNow++;
                int m = findMember(record.memberId);
                if (m != -1 && daysSince(record.issueDate) > members[m]->loanDays())
                    overdue++;
            }
        }
        cout << "\n----- LIBRARY SUMMARY (" << getDate(time(0)) << ") -----\n";
        cout << "Total book titles   : " << bookCount << endl;
        cout << "Total copies        : " << totalCopies << " (available " << available << ")\n";
        cout << "Total members       : " << Member::totalMembers << " (students " << students << ", faculty "
             << faculty << ")\n";
        cout << "Total transactions  : " << recordCount << endl;
        cout << "Books issued now    : " << issuedNow << endl;
        cout << "Overdue books       : " << overdue << endl;
        cout << "Total fine charged  : Rs." << fineCharged << endl;
        cout << "Fine collected      : Rs." << fineCharged - finePending << endl;
        cout << "Fine pending        : Rs." << finePending << endl;
    }

    void issuedBooksReport(bool onlyOverdue)
    {
        bool found = false;
        for (int i = 0; i < recordCount; i++)
        {
            Transaction &record = records[i];
            if (record.returned)
                continue;
            int m = findMember(record.memberId);
            int loanDays = 0;
            if (m != -1)
                loanDays = members[m]->loanDays();
            int days = daysSince(record.issueDate);
            bool isOverdue = days > loanDays;
            if (onlyOverdue && !isOverdue)
                continue;

            if (!found)
            {
                cout << left << setw(26) << "Book" << setw(20) << "Member" << setw(12) << "Issued" << setw(12)
                     << "Due" << "Status" << endl;
                cout << line(80) << endl;
            }
            found = true;
            cout << left << setw(26) << (to_string(record.bookId) + " " + bookTitle(record.bookId)).substr(0, 25)
                 << setw(20) << (to_string(record.memberId) + " " + memberName(record.memberId)).substr(0, 19)
                 << setw(12) << getDate(record.issueDate) << setw(12)
                 << getDate(record.issueDate + loanDays * ONE_DAY);
            if (isOverdue)
                cout << "Overdue " << days - loanDays << " days" << endl;
            else
                cout << "On time" << endl;
        }
        if (!found)
        {
            if (onlyOverdue)
                cout << "No overdue books.\n";
            else
                cout << "No books are issued right now.\n";
        }
    }

    void popularBooksReport()
    {
        MaxHeap heap;
        for (int i = 0; i < bookCount; i++)
            heap.insert(books[i].timesIssued, i);
        cout << "\n----- TOP 5 MOST ISSUED BOOKS -----\n";
        printBookHeader();
        for (int i = 0; i < 5 && !heap.isEmpty(); i++)
            cout << books[heap.extractMax().bookIndex];
    }

    void memberHistory()
    {
        int id = inputInt("Enter member ID: ");
        Member *member = members[requireMember(id)];
        cout << "\nHistory of " << member->getName() << ":\n";
        bool found = false;
        for (int i = 0; i < recordCount; i++)
        {
            Transaction &record = records[i];
            if (record.memberId != id)
                continue;
            found = true;
            cout << "  Book " << record.bookId << " - " << bookTitle(record.bookId) << " | issued "
                 << getDate(record.issueDate);
            if (record.returned)
                cout << " | kept " << record.daysKept << " days | fine Rs." << record.fine << endl;
            else
                cout << " | not returned yet\n";
        }
        if (!found)
            cout << "  No records.\n";
    }

    void allRecords()
    {
        if (recordCount == 0)
        {
            cout << "No records yet.\n";
            return;
        }
        cout << left << setw(5) << "No." << setw(8) << "Book" << setw(9) << "Member" << setw(12) << "Issued"
             << setw(12) << "Status" << "Fine" << endl;
        cout << line(55) << endl;
        for (int i = 0; i < recordCount; i++)
        {
            Transaction &record = records[i];
            string status = "Issued";
            if (record.returned)
                status = "Returned";
            cout << left << setw(5) << i + 1 << setw(8) << record.bookId << setw(9) << record.memberId << setw(12)
                 << getDate(record.issueDate) << setw(12) << status << "Rs." << record.fine << endl;
        }
    }

    void recentActivity()
    {
        if (activity.isEmpty())
        {
            cout << "No activity yet.\n";
            return;
        }
        StringStack temp = activity;
        int count = 0;
        cout << "\n----- RECENT ACTIVITY (latest first) -----\n";
        while (!temp.isEmpty() && count < 10)
        {
            cout << temp.pop() << endl;
            count++;
        }
    }

    void borrowMatrixReport()
    {
        SparseMatrix matrix(memberCount, bookCount);
        buildBorrowMatrix(matrix);
        int cells = memberCount * bookCount;
        int nonZero = matrix.getTermCount();
        cout << "\n----- BORROWING MATRIX (SPARSE) -----\n";
        cout << "Size: " << memberCount << " members x " << bookCount << " books = " << cells << " cells, "
             << nonZero << " non-zero\n";
        if (nonZero == 0)
        {
            cout << "No books borrowed yet.\n";
            return;
        }
        cout << "Zero cells: " << (cells - nonZero) * 100 / cells << "%\n\n";

        cout << "Triplet form:\n";
        cout << left << setw(6) << "Row" << setw(6) << "Col" << setw(7) << "Value" << "Member -> Book" << endl;
        cout << line(60) << endl;
        for (int i = 0; i < nonZero; i++)
        {
            Term term = matrix.getTerm(i);
            cout << left << setw(6) << term.row << setw(6) << term.column << setw(7) << term.value
                 << members[term.row]->getName().substr(0, 18) << " -> " << books[term.column].title.substr(0, 25)
                 << endl;
        }

        if (bookCount <= SMALL_MATRIX)
        {
            cout << "\nFull matrix (rows = member IDs, columns = book IDs):\n";
            cout << setw(7) << " ";
            for (int col = 0; col < bookCount; col++)
                cout << setw(4) << books[col].id;
            cout << endl;
            for (int row = 0; row < memberCount; row++)
            {
                cout << setw(7) << members[row]->getId();
                for (int col = 0; col < bookCount; col++)
                    cout << setw(4) << matrix.get(row, col);
                cout << endl;
            }
        }
    }

    void recommendBooks()
    {
        int bookId = inputInt("Enter book ID: ");
        int start = requireBook(bookId);
        SparseMatrix matrix(memberCount, bookCount);
        buildBorrowMatrix(matrix);
        BookGraph graph(bookCount);
        buildBookGraph(graph, matrix);

        int order[MAX_BOOKS], level[MAX_BOOKS];
        int count = graph.breadthFirst(start, order, level);
        if (count == 0)
        {
            cout << "No recommendations yet. Nobody who borrowed this book has borrowed another book.\n";
            return;
        }
        cout << "\nReaders of \"" << books[start].title << "\" may also like:\n";
        for (int i = 0; i < count; i++)
        {
            cout << "  " << books[order[i]].id << " - " << books[order[i]].title;
            if (level[i] == 1)
                cout << "  (borrowed by the same readers)\n";
            else
                cout << "  (related, " << level[i] << " steps away)\n";
        }
    }

    void bookGroups()
    {
        SparseMatrix matrix(memberCount, bookCount);
        buildBorrowMatrix(matrix);
        BookGraph graph(bookCount);
        buildBookGraph(graph, matrix);

        bool *visited = new bool[bookCount];
        for (int i = 0; i < bookCount; i++)
            visited[i] = false;
        int group[MAX_BOOKS];
        int groupNumber = 0;
        cout << "\n----- BOOK GROUPS (books connected through common readers) -----\n";
        for (int i = 0; i < bookCount; i++)
        {
            if (visited[i] || graph.degree(i) == 0)
                continue;
            int groupSize = 0;
            graph.depthFirst(i, visited, group, groupSize);
            groupNumber++;
            cout << "Group " << groupNumber << ":\n";
            for (int j = 0; j < groupSize; j++)
                cout << "  " << books[group[j]].id << " - " << books[group[j]].title << endl;
        }
        delete[] visited;
        if (groupNumber == 0)
            cout << "No groups yet. A member must borrow at least two different books.\n";
    }

    void saveData()
    {
        ofstream bookFile("books.txt");
        for (int i = 0; i < bookCount; i++)
        {
            Book &book = books[i];
            bookFile << book.id << "|" << book.title << "|" << book.author << "|" << book.category << "|"
                     << book.totalCopies << "|" << book.availableCopies << "|" << book.timesIssued << "\n";
        }
        bookFile.close();

        ofstream memberFile("members.txt");
        for (int i = 0; i < memberCount; i++)
        {
            Member *member = members[i];
            memberFile << member->getType() << "|" << member->getId() << "|" << member->getName() << "|"
                       << member->getPhone() << "|" << member->fine << "\n";
        }
        memberFile.close();

        ofstream recordFile("records.txt");
        for (int i = 0; i < recordCount; i++)
        {
            Transaction &record = records[i];
            recordFile << record.bookId << "|" << record.memberId << "|" << record.issueDate << "|"
                       << record.daysKept << "|" << record.fine << "|" << record.returned << "\n";
        }
        recordFile.close();
    }

    void loadBookLine(string text)
    {
        string fields[MAX_FIELDS];
        if (split(text, '|', fields, MAX_FIELDS) < 7)
            throw LibraryError("missing fields");
        if (bookCount == MAX_BOOKS)
            throw LibraryError("too many books");
        Book book((int)toNumber(fields[0]), fields[1], fields[2], fields[3], (int)toNumber(fields[4]));
        book.availableCopies = (int)toNumber(fields[5]);
        book.timesIssued = (int)toNumber(fields[6]);
        books[bookCount++] = book;
        if (book.id + 1 > nextBookId)
            nextBookId = book.id + 1;
    }

    void loadMemberLine(string text)
    {
        string fields[MAX_FIELDS];
        if (split(text, '|', fields, MAX_FIELDS) < 5)
            throw LibraryError("missing fields");
        if (memberCount == MAX_MEMBERS)
            throw LibraryError("too many members");
        int id = (int)toNumber(fields[1]);
        int fine = (int)toNumber(fields[4]);
        Member *member;
        if (fields[0] == "Student")
            member = new Student(id, fields[2], fields[3]);
        else
            member = new Faculty(id, fields[2], fields[3]);
        member->fine = fine;
        members[memberCount++] = member;
        phoneTable.insert(fields[3], id);
        if (id + 1 > nextMemberId)
            nextMemberId = id + 1;
    }

    void loadRecordLine(string text)
    {
        string fields[MAX_FIELDS];
        if (split(text, '|', fields, MAX_FIELDS) < 6)
            throw LibraryError("missing fields");
        if (recordCount == MAX_RECORDS)
            throw LibraryError("too many records");
        Transaction record((int)toNumber(fields[0]), (int)toNumber(fields[1]), (time_t)toNumber(fields[2]));
        record.daysKept = (int)toNumber(fields[3]);
        record.fine = (int)toNumber(fields[4]);
        record.returned = (fields[5] == "1");
        records[recordCount++] = record;
        if (!record.returned)
        {
            int m = findMember(record.memberId);
            if (m != -1)
                members[m]->addBook(record.bookId);
        }
    }

    void loadData()
    {
        string text;

        ifstream bookFile("books.txt");
        while (getline(bookFile, text))
        {
            try
            {
                loadBookLine(text);
            }
            catch (LibraryError &error)
            {
                cout << "books.txt: skipped a bad line (" << error.what() << ")\n";
            }
        }
        bookFile.close();

        ifstream memberFile("members.txt");
        while (getline(memberFile, text))
        {
            try
            {
                loadMemberLine(text);
            }
            catch (LibraryError &error)
            {
                cout << "members.txt: skipped a bad line (" << error.what() << ")\n";
            }
        }
        memberFile.close();

        ifstream recordFile("records.txt");
        while (getline(recordFile, text))
        {
            try
            {
                loadRecordLine(text);
            }
            catch (LibraryError &error)
            {
                cout << "records.txt: skipped a bad line (" << error.what() << ")\n";
            }
        }
        recordFile.close();

        if (bookCount == 0 && memberCount == 0)
        {
            addSampleData();
            cout << "No saved data found. Sample books and members added.\n";
        }
    }

    void addSampleData()
    {
        addBook("Clean Code", "Robert C. Martin", "Programming", 3);
        addBook("Introduction to Algorithms", "Cormen", "Programming", 2);
        addBook("Let Us C", "Yashavant Kanetkar", "Programming", 2);
        addBook("To Kill a Mockingbird", "Harper Lee", "Fiction", 1);
        addBook("1984", "George Orwell", "Fiction", 2);
        addBook("A Brief History of Time", "Stephen Hawking", "Science", 1);
        addMember(1, "Aarav Sharma", "9000000001");
        addMember(1, "Priya Patel", "9000000002");
        addMember(2, "Dr. Meera Iyer", "9000000003");
    }
};

void bookMenu(Library &library)
{
    while (true)
    {
        cout << "\n----- BOOK MANAGEMENT -----\n";
        cout << "1. Add Book\n2. Update Book\n3. Delete Book\n4. Show All Books\n";
        cout << "5. Search Book by ID\n6. Search Book by Title/Author/Category\n7. Search Book by Exact Title\n";
        cout << "0. Back\n";
        int choice = inputInt("Enter your choice: ");
        try
        {
            switch (choice)
            {
            case 1:
                library.addBook();
                break;
            case 2:
                library.updateBook();
                break;
            case 3:
                library.deleteBook();
                break;
            case 4:
                library.showAllBooks();
                break;
            case 5:
                library.searchBookById();
                break;
            case 6:
                library.searchBookByKeyword();
                break;
            case 7:
                library.searchBookByTitle();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (LibraryError &error)
        {
            cout << error.what() << endl;
        }
        library.saveData();
    }
}

void memberMenu(Library &library)
{
    while (true)
    {
        cout << "\n----- MEMBER MANAGEMENT -----\n";
        cout << "1. Add Member\n2. Update Member\n3. Delete Member\n4. Show All Members\n5. Member Details\n";
        cout << "6. Search Member by Phone\n0. Back\n";
        int choice = inputInt("Enter your choice: ");
        try
        {
            switch (choice)
            {
            case 1:
                library.addMember();
                break;
            case 2:
                library.updateMember();
                break;
            case 3:
                library.deleteMember();
                break;
            case 4:
                library.showAllMembers();
                break;
            case 5:
                library.showMemberDetails();
                break;
            case 6:
                library.searchMemberByPhone();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (LibraryError &error)
        {
            cout << error.what() << endl;
        }
        library.saveData();
    }
}

void issueMenu(Library &library)
{
    while (true)
    {
        cout << "\n----- ISSUE / RETURN / RESERVE -----\n";
        cout << "1. Issue Book\n2. Return Book\n3. Reserve Book\n4. Show Waiting List\n0. Back\n";
        int choice = inputInt("Enter your choice: ");
        try
        {
            switch (choice)
            {
            case 1:
                library.issueBook();
                break;
            case 2:
                library.returnBook();
                break;
            case 3:
                library.reserveBook();
                break;
            case 4:
                library.showWaitList();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (LibraryError &error)
        {
            cout << error.what() << endl;
        }
        library.saveData();
    }
}

void fineMenu(Library &library)
{
    FineCalculator calculator;
    while (true)
    {
        cout << "\n----- FINE MANAGEMENT -----\n";
        cout << "1. Check Fine\n2. Pay Fine\n3. All Pending Fines\n4. Fine Rules\n5. Fine Calculator\n0. Back\n";
        int choice = inputInt("Enter your choice: ");
        try
        {
            switch (choice)
            {
            case 1:
                library.checkFine();
                break;
            case 2:
                library.payFine();
                break;
            case 3:
                library.showPendingFines();
                break;
            case 4:
                library.showFineRules();
                break;
            case 5:
                calculator.run();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (LibraryError &error)
        {
            cout << error.what() << endl;
        }
        library.saveData();
    }
}

void reportMenu(Library &library)
{
    while (true)
    {
        cout << "\n----- RECORDS & REPORTS -----\n";
        cout << "1. Library Summary\n2. Currently Issued Books\n3. Overdue Books\n4. Most Popular Books\n";
        cout << "5. Member History\n6. All Records\n7. Recent Activity\n8. Borrowing Matrix\n";
        cout << "9. Recommend Books\n10. Book Groups\n0. Back\n";
        int choice = inputInt("Enter your choice: ");
        try
        {
            switch (choice)
            {
            case 1:
                library.summaryReport();
                break;
            case 2:
                library.issuedBooksReport(false);
                break;
            case 3:
                library.issuedBooksReport(true);
                break;
            case 4:
                library.popularBooksReport();
                break;
            case 5:
                library.memberHistory();
                break;
            case 6:
                library.allRecords();
                break;
            case 7:
                library.recentActivity();
                break;
            case 8:
                library.borrowMatrixReport();
                break;
            case 9:
                library.recommendBooks();
                break;
            case 10:
                library.bookGroups();
                break;
            case 0:
                return;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (LibraryError &error)
        {
            cout << error.what() << endl;
        }
    }
}

int main()
{
    Library *library = new Library();
    library->loadData();

    while (true)
    {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Book Management\n2. Member Management\n3. Issue / Return / Reserve\n";
        cout << "4. Fine Management\n5. Records & Reports\n0. Save & Exit\n";
        int choice = inputInt("Enter your choice: ");
        switch (choice)
        {
        case 1:
            bookMenu(*library);
            break;
        case 2:
            memberMenu(*library);
            break;
        case 3:
            issueMenu(*library);
            break;
        case 4:
            fineMenu(*library);
            break;
        case 5:
            reportMenu(*library);
            break;
        case 0:
            library->saveData();
            delete library;
            cout << "Data saved. Thank you!\n";
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}
