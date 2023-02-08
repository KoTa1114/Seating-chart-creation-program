#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
using namespace std;

class People {
    private:
        string name;
        string sex;
    protected:
        int id;
    public:
        virtual void set_id(int id) {
            if(id < 1 || 9999 < id) {
                cout << "生徒番号に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->id = id;
            }
        }
        void set_name(string name) {
            if(name.size() > 15) {
                cout << "氏名に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->name = name;
            }
        }
        void set_sex(string sex) {
            if(sex != "男" && sex != "女") {
                cout << "性別に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->sex = sex;
            }
        }
        int get_id() {
            return this->id;
        }
        string get_name() {
            return this->name;
        }
        string get_sex() {
            return this->sex;
        }
};

class Student : public People {
    private:
        int grade;
        string school_name;
        vector<pair<string,int> > courses;
        vector<bool> unavailable_times;
    public:
        void set_grade(int grade) {
            if(grade < 1 || 6 < grade) {
                cout << "学年に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->grade = grade;
            }
        }
        void set_school_name(string school_name) {
            if(school_name != "小学校" && school_name != "中学校" && school_name != "高校") {
                cout << "学校名に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->school_name = school_name;
            }
        }
        void add_courses(pair<string,int> course) {
            this->courses.push_back(course);
        }
        void add_unavailable_time(bool unavailable_time) {
            this->unavailable_times.push_back(unavailable_time);
        }
        int get_grade() {
            return this->grade;
        }
        string get_school_name() {
            return this->school_name;
        }
        vector<pair<string,int> > get_courses() {
            return this->courses;
        }
        vector<bool> get_unavailable_times() {
            return this->unavailable_times;
        }
};

class Teacher : public People {
    private:
        map<string,bool> subject_in_charge;
        vector<bool> available_times;
    public:
        void set_id(int id) {
            if(id < 10000 || 99999 < id) {
                cout << "講師番号に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->id = id;
            }
        }
        void add_subject_in_charge(string subject, int times) {
            this->subject_in_charge[subject] = times;
        }
        void add_available_time(bool available_time) {
            this->available_times.push_back(available_time);
        }
        map<string,bool> get_subject_in_charge() {
            return this->subject_in_charge;
        }
        vector<bool> get_available_times() {
            return this->available_times;
        }
};



int main(){
    Student p;
    p.set_id(10000);
    cout << p.get_id() << endl;
    return 0;
}