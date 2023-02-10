#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;


class People {
    protected:
        string id;
        string name;
        string sex;
    public:
        virtual void set_id(string id) {
            if(id < "1" || "9999" < id) {
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
        string get_id() {
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
        int difficulty;
        string grade;
        string school;
        vector<pair<string,int> > courses;
        vector<bool> unavailable_times;
    public:
        bool operator<(const Student &student) const {
            return difficulty < student.difficulty;
        }
        bool operator>(const Student &student) const {
            return difficulty > student.difficulty;
        }
        void set_difficulty(int difficulty) {
            this->difficulty = difficulty;
        }
        void set_grade(string grade) {
            if(grade < "1" || "6" < grade) {
                cout << "学年に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->grade = grade;
            }
        }
        void set_school(string school) {
            if(school != "小学校" && school != "中学校" && school != "高校") {
                cout << "学校名に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->school = school;
            }
        }
        void add_courses(pair<string,int> course) {
            this->courses.push_back(course);
        }
        void add_unavailable_time(bool unavailable_time) {
            if(unavailable_times.size() == 0) {
                unavailable_times.push_back(false);
            }
            this->unavailable_times.push_back(unavailable_time);
        }
        int get_difficulty() {
            return this->difficulty;
        }
        string get_grade() {
            return this->grade;
        }
        string get_school() {
            return this->school;
        }
        vector<pair<string,int> > get_courses() {
            return this->courses;
        }
        vector<bool> get_unavailable_times() {
            return this->unavailable_times;
        }
        void show_information() {
            cout << "番号 : " << id << " 氏名 : " << name << " 性別 : " << sex << endl;
            cout << "学校 : " << school << " 学年 : " << grade << endl;
            cout << endl;
        }
};

class Teacher : public People {
    private:
        int coverage;
        map<string,bool> subject_in_charge;
        vector<bool> available_times;
    public:
        bool operator<(const Teacher &teacher) const {
            return coverage < teacher.coverage;
        }
        bool operator>(const Teacher &teacher) const {
            return coverage > teacher.coverage;
        }
        void set_id(string id) {
            if(id < "10000" || "99999" < id) {
                cout << "講師番号に不適切な入力があります" << endl;
                exit(EXIT_FAILURE);
            } else {
                this->id = id;
            }
        }
        void set_coverage(int coverage) {
            this->coverage = coverage;
        }
        void add_subject_in_charge(string subject, bool ok) {
            this->subject_in_charge[subject] = ok;
        }
        void add_available_time(bool available_time) {
            if(available_times.size() == 0) {
                available_times.push_back(false);
            }
            this->available_times.push_back(available_time);
        }
        int get_coverage() {
            return this->coverage;
        }
        bool get_subject_in_charge(string subject) {
            return this->subject_in_charge[subject];
        }
        bool get_available_times(int time) {
            return this->available_times[time];
        }
        void show_information() {
            cout << "番号 : " << id << " 氏名 : " << name << " 性別 : " << sex << endl;
            cout << endl;
        }
};

class Table {
    private:
        string table_number;
        Student student1;
        Student student2;
        Teacher teacher;
        string subject1;
        string subject2;
    public:
        void set_table_number(string table_number) {
            this->table_number = table_number;
        }
        void set_student1(Student student) {
            this->student1 = student;
        }
        void set_student2(Student student) {
            this->student2 = student;
        }
        void set_teacher(Teacher teacher) {
            this->teacher = teacher;
        }
        void set_subject1(string subject1) {
            this->subject1 = subject1;
        }
        void set_subject2(string subject2) {
            this->subject2 = subject2;
        }
        string get_table_number() {
            return this->table_number;
        }
        Student get_student1() {
            return this->student1;
        }
        Student get_student2() {
            return this->student2;
        }
        Teacher get_teacher() {
            return this->teacher;
        }
        string get_subject1() {
            return this->subject1;
        }
        string get_subject2() {
            return this->subject2;
        }
        void show_information() {
            cout << "番号 : " << table_number << " 生徒1 : " << student1.get_name() << " 講師 : " << teacher.get_name() << endl;
        }
};

//inputをdelimiterで分割する関数
vector<string> split(string &input, char delimiter) {
    istringstream stream(input);
    string field;
    vector<string> result;
    while(getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

//csvファイルを二次元リストに変換する関数
vector<vector<string> > change_csv_to_vector(string csv_file_path) {
    ifstream ifs(csv_file_path); //読み取り用ストリーム
    vector<vector<string> > ret; //読み取ったデータの格納場所
    if(ifs) {
        string line;
        while(getline(ifs,line)) {
            vector<string> splitted_line = split(line, ',');
            ret.push_back(splitted_line);
        }
    }
    return ret;
}

//csvファイルから作成した二次元リストをStudent形式のリストに変換する関数
vector<Student> input_student_data (string student_csv_file_path) {
    vector<Student> student_list;
    vector<vector<string> > student_string_list = change_csv_to_vector(student_csv_file_path);
    int num_of_student = student_string_list.size(); //何人分の生徒情報があるか
    map<char, string> school_int_to_string;
    school_int_to_string['0'] = "小学校"; school_int_to_string['1'] = "中学校"; school_int_to_string['2'] = "高校";
    map<char, string> sex_int_to_string;
    sex_int_to_string['0'] = "男"; sex_int_to_string['1'] = "女";
    for(vector<string> line : student_string_list) {
        Student student;
        student.set_difficulty(100); //初期値として100を入力しておく
        student.set_school(school_int_to_string[char(line[0][0])]);
        student.set_id(line[1]);
        student.set_name(line[2]);
        student.set_grade(line[3]);
        student.set_sex(sex_int_to_string[line[4][0]]);
        for(int i = 5 ; i <= 13 ; i++) {
            if(line[i] == "0") student.add_unavailable_time(true);
            else student.add_unavailable_time(false);
        }
        if(student.get_school() == "小学校") {
            if(line[14] != "0") {student.add_courses(make_pair("こくご",stoi(line[14])));}
            if(line[15] != "0") {student.add_courses(make_pair("さんすう",stoi(line[15])));}
            if(line[16] != "0") {student.add_courses(make_pair("えいご",stoi(line[16])));}
            if(line[17] != "0") {student.add_courses(make_pair("りか",stoi(line[17])));}
            if(line[18] != "0") {student.add_courses(make_pair("しゃかい",stoi(line[18])));}
        } else if(student.get_school() == "中学校") {
            if(line[14] != "0") {student.add_courses(make_pair("国語",stoi(line[14])));}
            if(line[15] != "0") {student.add_courses(make_pair("数学",stoi(line[15])));}
            if(line[16] != "0") {student.add_courses(make_pair("英語",stoi(line[16])));}
            if(line[17] != "0") {student.add_courses(make_pair("理科",stoi(line[17])));}
            if(line[18] != "0") {student.add_courses(make_pair("社会",stoi(line[18])));}
        } else if(student.get_school() == "高校") {
            if(line[14] != "0") {student.add_courses(make_pair("現代文",stoi(line[14])));}
            if(line[15] != "0") {student.add_courses(make_pair("古文",stoi(line[15])));}
            if(line[16] != "0") {student.add_courses(make_pair("漢文",stoi(line[16])));}
            if(line[17] != "0") {student.add_courses(make_pair("小論文",stoi(line[17])));}
            if(line[18] != "0") {student.add_courses(make_pair("高校英語",stoi(line[18])));}
            if(line[19] != "0") {student.add_courses(make_pair("1A",stoi(line[19])));}
            if(line[20] != "0") {student.add_courses(make_pair("2B",stoi(line[20])));}
            if(line[21] != "0") {student.add_courses(make_pair("3",stoi(line[21])));}
            if(line[22] != "0") {student.add_courses(make_pair("物理基礎",stoi(line[22])));}
            if(line[23] != "0") {student.add_courses(make_pair("物理",stoi(line[23])));}
            if(line[24] != "0") {student.add_courses(make_pair("化学基礎",stoi(line[24])));}
            if(line[25] != "0") {student.add_courses(make_pair("化学",stoi(line[25])));}
            if(line[26] != "0") {student.add_courses(make_pair("生物基礎",stoi(line[26])));}
            if(line[27] != "0") {student.add_courses(make_pair("生物",stoi(line[27])));}
            if(line[28] != "0") {student.add_courses(make_pair("日本史",stoi(line[28])));}
            if(line[29] != "0") {student.add_courses(make_pair("世界史",stoi(line[29])));}
            if(line[30] != "0") {student.add_courses(make_pair("英検・TOEIC対策",stoi(line[30])));}
        }
        student_list.push_back(student);
    }
    return student_list;
}

//csvファイルから作成した二次元リストをTeacher形式のリストに変換する関数
vector<Teacher> input_teacher_data (string teacher_csv_file_path) {
    vector<Teacher> teacher_list;
    vector<vector<string> > teacher_string_list = change_csv_to_vector(teacher_csv_file_path);
    int num_of_teacher = teacher_string_list.size(); //何人分の講師情報があるか
    for(vector<string> line : teacher_string_list) {
        Teacher teacher;
        teacher.set_coverage(0); //初期値として0を入力しておく
        teacher.set_id(line[0]);
        teacher.set_name(line[1]);
        teacher.set_sex(line[2]);
        for(int i = 3 ; i <= 11 ; i++) {
            if(line[i] != "1") teacher.add_available_time(true);
            else teacher.add_available_time(false);
        }
        if(line[12] == "1") teacher.add_subject_in_charge("こくご", true);
        else teacher.add_subject_in_charge("こくご", false);
        if(line[13] == "1") teacher.add_subject_in_charge("さんすう", true);
        else teacher.add_subject_in_charge("さんすう", false);
        if(line[14] == "1") teacher.add_subject_in_charge("えいご", true);
        else teacher.add_subject_in_charge("えいご", false);
        if(line[15] == "1") teacher.add_subject_in_charge("りか", true);
        else teacher.add_subject_in_charge("りか", false);
        if(line[16] == "1") teacher.add_subject_in_charge("しゃかい", true);
        else teacher.add_subject_in_charge("しゃかい", false);
        if(line[17] == "1") teacher.add_subject_in_charge("国語", true);
        else teacher.add_subject_in_charge("国語", false);
        if(line[18] == "1") teacher.add_subject_in_charge("数学", true);
        else teacher.add_subject_in_charge("数学", false);
        if(line[19] == "1") teacher.add_subject_in_charge("英語", true);
        else teacher.add_subject_in_charge("英語", false);
        if(line[20] == "1") teacher.add_subject_in_charge("理科", true);
        else teacher.add_subject_in_charge("理科", false);
        if(line[21] == "1") teacher.add_subject_in_charge("社会", true);
        else teacher.add_subject_in_charge("社会", false);
        if(line[22] == "1") teacher.add_subject_in_charge("現代文", true);
        else teacher.add_subject_in_charge("現代文", false);
        if(line[23] == "1") teacher.add_subject_in_charge("古文", true);
        else teacher.add_subject_in_charge("古文", false);
        if(line[24] == "1") teacher.add_subject_in_charge("漢文", true);
        else teacher.add_subject_in_charge("漢文", false);
        if(line[25] == "1") teacher.add_subject_in_charge("小論文", true);
        else teacher.add_subject_in_charge("小論文", false);
        if(line[26] == "1") teacher.add_subject_in_charge("高校英語", true);
        else teacher.add_subject_in_charge("高校英語", false);
        if(line[27] == "1") teacher.add_subject_in_charge("1A", true);
        else teacher.add_subject_in_charge("1A", false);
        if(line[28] == "1") teacher.add_subject_in_charge("2B", true);
        else teacher.add_subject_in_charge("2B", false);
        if(line[29] == "1") teacher.add_subject_in_charge("3", true);
        else teacher.add_subject_in_charge("3", false);
        if(line[30] == "1") teacher.add_subject_in_charge("物理基礎", true);
        else teacher.add_subject_in_charge("物理基礎", false);
        if(line[31] == "1") teacher.add_subject_in_charge("物理", true);
        else teacher.add_subject_in_charge("物理", false);
        if(line[32] == "1") teacher.add_subject_in_charge("化学基礎", true);
        else teacher.add_subject_in_charge("化学基礎", false);
        if(line[33] == "1") teacher.add_subject_in_charge("化学", true);
        else teacher.add_subject_in_charge("化学", false);
        if(line[34] == "1") teacher.add_subject_in_charge("生物基礎", true);
        else teacher.add_subject_in_charge("生物基礎", false);
        if(line[35] == "1") teacher.add_subject_in_charge("生物", true);
        else teacher.add_subject_in_charge("生物", false);
        if(line[36] == "1") teacher.add_subject_in_charge("日本史", true);
        else teacher.add_subject_in_charge("日本史", false);
        if(line[37] == "1") teacher.add_subject_in_charge("世界史", true);
        else teacher.add_subject_in_charge("世界史", false);
        if(line[38] == "1") teacher.add_subject_in_charge("英検・TOEIC対策", true);
        else teacher.add_subject_in_charge("英検・TOEIC対策", false);
        teacher_list.push_back(teacher);
    }
    return teacher_list;
}

//calculate_difficultyで利用する科目リスト
string subjects_list[27] = {"こくご", "さんすう", "えいご", "りか", "しゃかい",
"国語", "数学", "英語", "社会", "理科",
"現代文", "古文", "漢文", "小論文", "高校英語", "1A", "2B",
"3", "物理基礎", "物理", "化学基礎", "化学", "生物基礎", "生物",
"日本史", "世界史", "英検・TOEIC対策"};

//生徒の受講希望科目への対応の難しさを計算する (座席表作成部分で利用)
void calculate_difficulty(vector<Student> student_list, vector<Teacher> teacher_list) {
    map<string, int> subject_difficulty;
    //生徒情報を反映させる
    for(Student student : student_list) {
        vector<pair<string, int> > student_courses = student.get_courses();
        for(pair<string, int> course : student_courses) {
            subject_difficulty[course.first] += course.second;
        }
    }
    //講師情報を反映させる
    for(Teacher teacher : teacher_list) {
        for(string subject : subjects_list) {
            if(teacher.get_subject_in_charge(subject) == true) {
                subject_difficulty[subject] -= 1;
            }
        }
    }
    //subject_difficultyから各生徒のdifficultyを計算する
    for(Student student : student_list) {
        int difficulty = 100;
        vector<pair<string, int> > student_courses = student.get_courses();
        for(pair<string, int> course : student_courses) {
            difficulty += subject_difficulty[course.first] * course.second;
        }
        student.set_difficulty(difficulty);
    }
}

//講師の担当科目への対応範囲の広さを計算する (座席表作成部分で利用)
void calculate_coverage(vector<Teacher> teacher_list) {
    for(Teacher teacher : teacher_list) {
        int coverage = 0;
        for(string subject : subjects_list) {
            if(teacher.get_subject_in_charge(subject) == true) {
                coverage += 1;
            }
        }
        teacher.set_coverage(coverage);
    }
}

//1コマ分の座席表を作成する関数  difficultyが高い生徒から決定していく  coverageが低い講師から決定していく
/*vector<Table> create_table_list(vector<Student> student_list, vector<Teacher> teacher_list, int time) {
    vector<Table> table_list;
    sort(student_list.begin(), student_list.end(), greater<Student>()); //difficultyが高い順に並び替える
    sort(teacher_list.begin(), teacher_list.end()); //coverageが低い順に並び替える
    map<Teacher, bool> is_place_teacher; //講師が既に配置されているかを持つ
    for(Student student : student_list) {
        bool could_place = false;
        for(Table table : table_list) {
            if(table.get_student_name2().size() == 0) {
                vector<pair<string, int> > courses = student.get_courses();
                for(pair<string, int> course : courses) {
                    if(course.second > 0 && teacher.get_subject_in_charge()) {
                        table.set_student_name1(student.get_name());
                        table.set_subject1(course.first);
                    }
                }
            }
        }
    }
    return table_list;
}*/


int main(){
    string student_csv_file_path = "";
    string teacher_csv_file_path = "";
    vector<Student> student_list = input_student_data(student_csv_file_path);
    vector<Teacher> teacher_list = input_teacher_data(teacher_csv_file_path);
    calculate_difficulty(student_list, teacher_list);
    calculate_coverage(teacher_list);
    int time = 1;
    vector<Table> table_list = create_table_list(student_list, teacher_list, time);
    //以下テスト用
    Teacher t1, t2;
    t1.set_coverage(1);
    t2.set_coverage(2);
    if(t1 < t2) {
        cout << "t1の方が小さいです" << endl;
    }
    Student student;
    student.set_id("111");
    student.set_grade("2");
    student.set_name("tanaka");
    student.set_sex("女");
    student.set_school("小学校");
    student.show_information();
    Teacher teacher;
    teacher.set_id("11111");
    teacher.set_name("masato");
    teacher.set_sex("男");
    teacher.show_information();
    Table table;
    table.set_table_number("11");
    table.set_student_name1("akihiko");
    table.set_teacher_name("asako");
    table.show_information();
    return 0;
}