#include <iostream>
#include <vector>
#include <algorithm>

class Date
{
private:
//public:
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;

public:
    Date(int year = int(), int month = int(), int day = int(), int hour = int(), int min = int(), int sec = int())
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->min = min;
        this->sec = sec;
    }
    /*void set(int year, int month, int day, int hour, int minute, int second)
    {
        year = year, month = month, day = day, hour = hour, minute = minute, second = second;
    }*/
    friend bool operator> (const Date&, const Date&);
    friend bool operator< (const Date&, const Date&);
    friend bool operator== (const Date&, const Date&);
    friend Date operator+ (const Date&, const Date&);
    friend Date operator- (const Date&, const Date&);
    friend std::ostream& operator<< (std::ostream&, const Date&);
    friend std::istream& operator>> (std::istream& , Date&);
    Date& operator= (const Date&);
    int daysInMonth(int month, int leap);
    int dayInYear();
    int numberOfWeakInMonth();
    int numberOfWeakInYear();
    bool check();
};

bool leapYear(int year)
{
    if (!(year % 4) && (year % 100) || !(year % 400)) return true;
    else return false;
}

std::string day(int day)
{
    switch (day)
    {
    case 1:
        return "Monday";
        break;
    case 2:
        return "Tuesday";
        break;
    case 3:
        return "Wednesday";
        break;
    case 4:
        return "Thursday";
        break;
    case 5:
        return "Friday";
        break;
    case 6:
        return "Saturday";
        break;
    case 7:
        return "Sunday";
        break;
    }
}

bool Date::check()
{
    if (year < 0 || month < 1 || month > 12 || hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59)
    {
        return false;
    }
    bool leap = leapYear(year);
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day > 31) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day > 30) return false;
    }
    else if (month == 2)
    {
        if (leap && day > 29) return false;
        else if (!leap && day > 28) return false;
    }
    return true;
}

int Date::daysInMonth(int month, int leap)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return 30;
    }
    else if (month == 2)
    {
        if (leap) return 29;
        else if (!leap) return 28;
    }
}

int countLeaps(int year1, int year2)
{
    if (year2 < year1) return countLeaps(year2, year1);
    int c = 0;
    for (int i = year1; i < year2; ++i) c += leapYear(i);
    return c;
}

int numberOfDayInYear(int month, int day, bool leap)
{
    switch (month)
    {
    case 1:
        return day;
        break;
    case 2:
        return 31 + day;
        break;
    case 3:
        return 59 + day + leap;
        break;
    case 4:
        return 90 + day + leap;
        break;
    case 5:
        return 120 + day + leap;
        break;
    case 6:
        return 151 + day + leap;
        break;
    case 7:
        return 181 + day + leap;
        break;
    case 8:
        return 212 + day + leap;
        break;
    case 9:
        return 243 + day + leap;
        break;
    case 10:
        return 273 + day + leap;
        break;
    case 11:
        return 304 + day + leap;
        break;
    case 12:
        return 334 + day + leap;
        break;
    }
}

int Date::dayInYear()
{
    int leap = countLeaps(year, 2021);
    int dif = abs(2021 - year);
    int defYears = dif - leap;
    int tmp = defYears + 2 * leap, cur;
    if (year > 2021) cur = (4 + tmp) % 7;
    else cur = (tmp * 7 + 4 - tmp) % 7;
    return (cur + numberOfDayInYear(month, day, leapYear(year)) - 1) % 7 + 1;
}

int Date::numberOfWeakInMonth()
{
    Date tmpp(year, month, 1, 0, 0, 0);
    int tmp = tmpp.dayInYear(), cur = 1;
    if (tmp != 1) cur += (8 - tmp);
    if (cur == 1) return day / 7 + 1;
    else if (day - cur < 0) return 1;
    else return (day - cur) / 7 + 2;
}

int Date::numberOfWeakInYear()
{
    int ans = 0;
    for (int i = 1; i < month; ++i)
    {
        Date tmp(year, i, daysInMonth(i, leapYear(year)), 0, 0, 0);
        ans += tmp.numberOfWeakInMonth();
    }
    ans += numberOfWeakInMonth();
    return ans;
}

bool operator< (const Date& date1, const Date& date2)
{
    if ((date1.year < date2.year) || ((date1.year == date2.year) && ((date1.month < date2.month) || ((date1.month == date2.month) && ((date1.day < date2.day) 
        || ((date1.day == date2.day) && ((date1.hour < date2.hour) || ((date1.hour == date2.hour) && ((date1.min < date2.min) || (date1.min == date2.min && date1.sec < date2.sec))))))))))
        return true;
    else
        return false;
}

bool operator> (const Date& date1, const Date& date2)
{
    return (date2 < date1);
}

bool operator== (const Date& date1, const Date& date2)
{
    if (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day && date1.hour == date2.hour && date1.min == date2.min && date1.sec == date2.sec)
        return true;
    return false;
}

Date operator+ (const Date& date1, const Date& date2)
{
    Date ans;
    ans = date1;

    ans.sec += date2.sec;

    ans.min += (date2.min + ans.sec / 60);
    ans.sec %= 60;

    ans.hour += (date2.hour + ans.min / 60);
    ans.min %= 60;

    ans.day += (date2.day + ans.hour / 24);
    ans.hour %= 24;

    ans.day--;
    int months = ans.day / (ans.daysInMonth(ans.month, leapYear(ans.year)));
    ans.day %= ans.daysInMonth(ans.month, leapYear(ans.year));
    ans.month += (date2.month + months);
    ans.month--;
    ans.year += (date2.year + ans.month / 12);
    ans.month %= 12;
    ans.day++;
    ans.month++;

    return ans;
}

Date operator- (const Date& date1, const Date& date2)
{
    Date ans;
    ans = date1;

    ans.sec -= date2.sec;
    while (ans.sec < 0)
    {
        ans.sec += 60;
        ans.min--;
    }
    
    ans.min -= date2.min;
    while (ans.min < 0)
    {
        ans.min += 60;
        ans.hour--;
    }
    
    ans.hour -= date2.hour;
    while (ans.hour < 0)
    {
        ans.hour += 24;
        ans.day--;
    }

    ans.day -= date2.day;
    while (ans.day < 0)
    {
        ans.month--;
        ans.day += ans.daysInMonth(ans.month, leapYear(ans.year));
    }

    ans.month -= date2.month;
    while (ans.month < 0)
    {
        ans.month += 12;
        ans.year--;
    }

    ans.year -= (date2.year);

    return ans;
}

Date& Date::operator= (const Date& date)
{
    if (this == &date)
        return *this;
    year = date.year;
    month = date.month;
    day = date.day;
    hour = date.hour;
    min = date.min;
    sec = date.sec;

    return *this;
}

std::ostream& operator<< (std::ostream& out, const Date& date)
{
    out << "Year: " << date.year << " month: " << date.month << " day: " << date.day
        << " hour: " << date.hour << " minute: " << date.min << " second: " << date.sec << '\n';
    return out;
}

std::istream& operator>> (std::istream& in, Date& input)
{
    /*in >> input.year;
    in >> input.month;
    in >> input.day;
    in >> input.hour;
    in >> input.min;
    in >> input.sec;*/
    in >> input.year >> input.month >> input.day >> input.hour >> input.min >> input.sec;
    return in;
}

//-------------------------------------------------------------------------------------

template<typename T>
class Graph
{
private:
    class Edge
    {
    public:
        T start;
        T end;
        T weight;
        int nums;
        int nume;
        Edge(T start = T(), T end = T(), T weight = T(), int nums = int(), int nume = int())
        {
            this->start = start;
            this->end = end;
            this->weight = weight;
            this->nums = nums;
            this->nume = nume;
        }
    };
    class Node
    {
    public:
        T val;
        int num;
        Node(T val = T(), int num = int())
        {
            this->val = val;
            this->num = num;
        }
    };
    std::vector<Edge> G;
    std::vector<Edge> MST;
    std::vector<Node> nodes;
    std::vector<int> parent;
    int n = 0;

public:
    void addEdge(int, int, T);
    void delEdge(int, int);
    void addNode();
    void delNode(int);
    int findSet(int);
    void unionSet(int, int);
    void kruskal();
    void print();
    void printvec();
    void addNodeVec();
    void parentnum();
};

template<typename T>
void Graph<T>::parentnum()
{
    for (int i = 0; i < n; i++)
        parent.push_back(i);
}

template<typename T>
void Graph<T>::addEdge(int nums, int nume, T w)
{
    bool fls = false, fle = false;
    T s, e;
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i].num == nums)
        {
            s = nodes[i].val;
            fls = true;
        }
        if (nodes[i].num == nume)
        {
            e = nodes[i].val;
            fle = true;
        }
        if (fls && fle) break;
    }
    Edge tmp(s, e, w, nums, nume);
    G.push_back(tmp);
}

template<typename T>
void Graph<T>::delEdge(int nums, int nume)
{
    for (int i = 0; i < G.size(); i++)
    {
        if ((G[i].nums == nums && G[i].nume == nume) || (G[i].nums == nume && G[i].nume == nums))
        {
            G.erase(G.begin() + i);
            break;
        }
    }
}

template<typename T>
void Graph<T>::addNode()
{
    int i = parent.size();
    parent.push_back(i);
    n++;

    int num, nums = i, nume;
    T s, w;

    std::cout << "enter node:\n";
    std::cin >> s;

    Node tmp(s, i);
    nodes.push_back(tmp);

    do
    {
        std::cout << "how many edges will the node has?\n";
        std::cin >> num;
        if (num >= nodes.size())
        {
            std::cout << "Incorect input\n";
            continue;
        }
        break;
    } while (true);

    for (int j = 0; j < num; j++)
    {
        std::cout << "\nenter number of end (your node: " << i << ", enum from 0)\n";
        std::cin >> nume;
        std::cout << "enter weight:\n";
        std::cin >> w;
        addEdge(nums, nume, w);
    }
}

template<typename T>
void Graph<T>::addNodeVec()
{
    int i = parent.size();
    parent.push_back(i);
    n++;

    int num, nums = i, nume, cs;
    T s, w;

    std::cout << "\nenter number of start node elements\n";
    std::cin >> cs;
    std::cout << "\nenter elements\n";
    for (int js = 0; js < cs; js++)
    {
        int tmp;
        std::cin >> tmp;
        s.push_back(tmp);
    }

    Node tmp(s, i);
    nodes.push_back(tmp);

    do
    {
        std::cout << "how many edges will the node has?\n";
        std::cin >> num;
        if (num >= nodes.size())
        {
            std::cout << "Incorect input\n";
            continue;
        }
        break;
    } while (true);

    for (int j = 0; j < num; j++)
    {
        std::cout << "\nenter number of end node (your node: " << i << ", enum from 0)\n";
        std::cin >> nume;
        std::cout << "enter number of weight elements:\n";
        int num, tmp;
        std::cin >> num;
        std::cout << "enter elements\n";
        for (int jw = 0; jw < num; jw++)
        {
            std::cin >> tmp;
            w.push_back(tmp);
        }
        addEdge(nums, nume, w);
        w.clear();
    }
}

template<typename T>
void Graph<T>::delNode(int id)
{
    parent.erase(parent.begin() + id);
    n--;
    bool fl = false;

    for (int i = 0; i <= G.size(); i++)
    {
        if (fl)
        {
            i--;
            fl = false;
        }

        if (i != G.size() && (G[i].nums == id || G[i].nume == id))
        {
            G.erase(G.begin() + i);
            fl = true;
        }
    }

    for (int i = 0; i < G.size(); i++)
    {
        if (G[i].nums > id)
        {
            G[i].nums--;
        }
        if (G[i].nume > id)
        {
            G[i].nume--;
        }
    }
}

template<typename T>
int Graph<T>::findSet(int i)
{
    if (i == parent[i])
        return i;
    else
        return findSet(parent[i]);
}

template<typename T>
void Graph<T>::unionSet(int nums, int nume)
{
    for (int i = 0; i < parent.size(); i++)
    {
        if (parent[i] == nume)
            parent[i] = nums;
    }
}

template<typename T>
void Graph<T>::kruskal()
{
    MST.clear();
    parent.clear();
    parentnum();

    std::sort(G.begin(), G.end(), [](Edge a, Edge b) {return a.weight < b.weight; });
    int a, b;

    for (int i = 0; i < G.size(); i++)
    {
        a = findSet(G[i].nums);
        b = findSet(G[i].nume);
        if (a != b)
        {
            MST.push_back(G[i]);
            unionSet(a, b);
        }
    }
}

template<typename T>
void Graph<T>::print()
{
    std::cout << "Edge : Weight" << std::endl;
    for (int i = 0; i < MST.size(); i++)
    {
        //std::cout << MST[i].start + 1 << " " << MST[i].end + 1 << " : " << MST[i].weight << std::endl;
        std::cout << MST[i].start << " " << MST[i].end << " : " << MST[i].weight << std::endl;
    }
}

template<typename T>
void Graph<T>::printvec()
{
    std::cout << "Start; End : Weight" << std::endl;
    for (int i = 0; i < MST.size(); i++)
    {
        //std::cout << MST[i].start + 1 << " " << MST[i].end + 1 << " : " << MST[i].weight << std::endl;
        //std::cout << MST[i].start << " " << MST[i].end << " : " << MST[i].weight << std::endl;
        for (int js = 0; js < MST[i].start.size(); js++)
        {
            std::cout << MST[i].start[js] << " ";
        }
        std::cout << "; ";
        for (int je = 0; je < MST[i].end.size(); je++)
        {
            std::cout << MST[i].end[je] << " ";
        }
        std::cout << ": ";
        for (int jw = 0; jw < MST[i].weight.size(); jw++)
        {
            std::cout << MST[i].weight[jw] << " ";
        }
        std::cout << "\n";
    }
}

//----------------------------------------------------------

void commands()
{
    do
    {
        int com1;
        std::cout << "1)Test Graph\n2)Test Dates\n3)Exit\n";
        std::cin >> com1;
        if (com1 == 1)
        {
            std::cout << "Choose type of Graph:\n1.int\n2.double\n3.string\n4.vector of ints\n5.Date\n";
            int com2;
            std::cin >> com2;
            if (com2 == 1)
            {
                Graph<int> g;
                do
                {
                    std::cout << "1)Add Edge\n2)Add Node\n3)Delete Edge\n4)Delete Node\n5)Print MST\n6)Back\n";
                    int com3;
                    std::cin >> com3;
                    if (com3 == 1)
                    {
                        int s, e, w;
                        std::cout << "Enter start, end and weight: \n";
                        std::cin >> s >> e >> w;
                        g.addEdge(s, e, w);
                    }
                    else if (com3 == 2)
                        g.addNode();
                    else if (com3 == 3)
                    {
                        int nums, nume;
                        std::cout << "Enter numbers of start and end: \n";
                        std::cin >> nums >> nume;
                        g.delEdge(nums, nume);
                    }
                    else if (com3 == 4)
                    {
                        int id;
                        std::cout << "Enter number of node: \n";
                        std::cin >> id;
                        g.delNode(id);
                    }
                    else if (com3 == 5)
                    {
                        g.kruskal();
                        g.print();
                    }
                    else if (com3 == 6) break;
                    else std::cout << "Incorrect input (1-6)\n";
                } while (true);
            }
            else if (com2 == 2)
            {
                Graph<double> g;
                do
                {
                    std::cout << "1)Add Edge\n2)Add Node\n3)Delete Edge\n4)Delete Node\n5)Print MST\n6)Back\n";
                    int com3;
                    std::cin >> com3;
                    if (com3 == 1)
                    {
                        double s, e, w;
                        std::cout << "Enter start, end and weight: \n";
                        std::cin >> s >> e >> w;
                        g.addEdge(s, e, w);
                    }
                    else if (com3 == 2)
                        g.addNode();
                    else if (com3 == 3)
                    {
                        int nums, nume;
                        std::cout << "Enter numbers of start and end: \n";
                        std::cin >> nums >> nume;
                        g.delEdge(nums, nume);
                    }
                    else if (com3 == 4)
                    {
                        int id;
                        std::cout << "Enter number of node: \n";
                        std::cin >> id;
                        g.delNode(id);
                    }
                    else if (com3 == 5)
                    {
                        g.kruskal();
                        g.print();
                    }
                    else if (com3 == 6) break;
                    else std::cout << "Incorrect input (1-6)\n";
                } while (true);
            }
            else if (com2 == 3)
            {
                Graph<std::string> g;
                do
                {
                    std::cout << "1)Add Edge\n2)Add Node\n3)Delete Edge\n4)Delete Node\n5)Print MST\n6)Back\n";
                    int com3;
                    std::cin >> com3;
                    if (com3 == 1)
                    {
                        std::string w;
                        int nums, nume;
                        std::cout << "Enter number of start and end: \n";
                        std::cin >> nums >> nume;
                        std::cout << "Enter number weight (string): \n";
                        std::cin >> w;
                        g.addEdge(nums, nume, w);
                    }
                    else if (com3 == 2)
                        g.addNode();
                    else if (com3 == 3)
                    {
                        int nums, nume;
                        std::cout << "Enter numbers of start and end: \n";
                        std::cin >> nums >> nume;
                        g.delEdge(nums, nume);
                    }
                    else if (com3 == 4)
                    {
                        int id;
                        std::cout << "Enter number of node: \n";
                        std::cin >> id;
                        g.delNode(id);
                    }
                    else if (com3 == 5)
                    {
                        g.kruskal();
                        g.print();
                    }
                    else if (com3 == 6) break;
                    else std::cout << "Incorrect input (1-6)\n";
                } while (true);
            }
            else if (com2 == 4)
            {
                Graph<std::vector<int>> g;
                do
                {
                    std::cout << "1)Add Edge\n2)Add Node\n3)Delete Edge\n4)Delete Node\n5)Print MST\n6)Back\n";
                    int com3;
                    std::cin >> com3;
                    if (com3 == 1)
                    {
                        std::vector<int> tmpw;
                        int nums, nume;
                        
                        std::cout << "Enter the number of start and end nodes:\n";
                        
                        std::cin>> nums >> nume;

                        std::cout << "Enter the number of weight elements:\n";
                        int numw, tmp;
                        std::cin >> numw;
                        std::cout << "Enter the elements:\n";

                        for (int i = 0; i < numw; i++)
                        {
                            std::cin >> tmp;
                            tmpw.push_back(tmp);
                        }

                        g.addEdge(nums, nume, tmpw);
                    }
                    else if (com3 == 2) 
                        g.addNodeVec();
                    else if (com3 == 3)
                    {
                        int s, e;
                        std::cout << "Enter numbers of start and end: \n";
                        std::cin >> s >> e;
                        g.delEdge(s, e);
                    }
                    else if (com3 == 4)
                    {
                        int id;
                        std::cout << "Enter number of node: \n";
                        std::cin >> id;
                        g.delNode(id);
                    }
                    else if (com3 == 5)
                    {
                        g.kruskal();
                        g.printvec();
                    }
                    else if (com3 == 6) break;
                    else std::cout << "Incorrect input (1-6)\n";
                } while (true);
            }
            else if (com2 == 5)
            {
                Graph<Date> g;
                do
                {
                    std::cout << "1)Add Edge\n2)Add Node\n3)Delete Edge\n4)Delete Node\n5)Print MST\n6)Back\n";
                    int com3;
                    std::cin >> com3;
                    if (com3 == 1)
                    {
                        Date tmpw;
                        int nums, nume;

                        std::cout << "Enter number of start:\n";
                        std::cin >> nums;

                        std::cout << "Enter number of end:\n";
                        std::cin >> nume;

                        std::cout << "Enter weight (date):\n";
                        std::cin >> tmpw;

                        g.addEdge(nums, nume, tmpw);
                    }
                    else if (com3 == 2) g.addNode();
                    else if (com3 == 3)
                    {
                        int s, e;
                        std::cout << "Enter numbers of start and end: \n";
                        std::cin >> s >> e;
                        g.delEdge(s, e);
                    }
                    else if (com3 == 4)
                    {
                        int id;
                        std::cout << "Enter number of node: \n";
                        std::cin >> id;
                        g.delNode(id);
                    }
                    else if (com3 == 5)
                    {
                        g.kruskal();
                        g.print();
                    }
                    else if (com3 == 6) break;
                    else std::cout << "Incorrect input (1-6)\n";
                } while (true);
            }
            else std::cout << "Incorrect input\n";
        }
        else if (com1 == 2)
        {
            std::cout << "Enter the date:\n";
            Date date;//(2021, 11, 12, 20, 20, 20);
            std::cin >> date;

            bool fl = true;
            do
            {
                std::cout << "1.Add another date\n2.Subtract another date\n3.Check correct\n4.Which day of the week\n5.Witch number of the weak in month\n6.Whitch number of the weak in year\n7.Print the date\n8.Back\n";
                int com3;
                std::cin >> com3;
                if (com3 == 1 || com3 == 2)
                    do
                    {
                        std::cout << "Enter the date:\n";
                        Date date2;
                        std::cin >> date2;
                        if (!date2.check())
                        {
                            std::cout << "Incorrect date\n";
                            continue;
                        }
                        if (com3 == 1)
                            date = date + date2;
                        else
                            date = date - date2;
                        break;
                    } while (true);
                    switch (com3)
                    {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        if (date.check())
                            std::cout << "Correct\n";
                        else
                            std::cout << "Incorect\n";
                        break;
                    case 4:
                        std::cout << day(date.dayInYear()) << "\n";
                        break;
                    case 5:
                        std::cout << date.numberOfWeakInMonth() << "\n";
                        break;
                    case 6:
                        std::cout << date.numberOfWeakInYear() << "\n";
                        break;
                    case 7:
                        std::cout << date << "\n";
                        break;
                    case 8:
                        fl = false;
                        break;
                    default:
                        std::cout << "Wrong input\n";
                    }
            } while (fl);
        }
        else if (com1 == 3)
            return;
        else
            std::cout << "Wrong input\n";
    } while (true);
}

int main()
{
    commands();
    return 0;
}