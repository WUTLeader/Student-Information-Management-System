#include <iostream>
#include <cstring>
#include "Student.h"
#include "SqList.h"
#include<fstream>
using namespace std;

//用来显示学生信息
void VisitStudent(const Student& s) {
    cout << "学号: " << s.id << "\t姓名: " << s.name << "\t绩点: " << s.GPA << endl;
}

//从键盘输入一个学生信息
Student inputStudent() {
    Student s;
    cout << "请输入学号: "; cin >> s.id;
    cout << "请输入姓名: "; cin >> s.name;
    cout << "请输入绩点: "; cin >> s.GPA;
    return s;
}

//用于绩点排序(从高到低)
void sortStudentList(SqList<Student>& list) {
    int len = list.GetLength();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            Student s1, s2;
            list.GetElem(j + 1, s1); // 获取第 j+1 个位置的学生
            list.GetElem(j + 2, s2); // 获取第 j+2 个位置的学生

            // 按绩点从高到低来完成实验要求的排序功能
            if (s2.GPA > s1.GPA) {
                //位置互换
                list.SetElem(j + 1, s2);
                list.SetElem(j + 2, s1);
            }
        }
    }
}
//按绩点从低到高
void sortStudentList1(SqList<Student>& list) {
    int len = list.GetLength();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            Student s1, s2;
            list.GetElem(j + 1, s1); // 获取第 j+1 个位置的学生
            list.GetElem(j + 2, s2); // 获取第 j+2 个位置的学生

            // 按绩点从低到高来完成实验要求的排序功能
            if (s2.GPA < s1.GPA) {
                //位置互换
                list.SetElem(j + 1, s2);
                list.SetElem(j + 2, s1);
            }
        }
    }
}
//按学号从小到大排
void SortStudentListById(SqList<Student>& list) {
    int len = list.GetLength();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            Student s1, s2;
            list.GetElem(j + 1, s1);
            list.GetElem(j + 2, s2);


            if (s2.id < s1.id) {
                list.SetElem(j + 1, s2);
                list.SetElem(j + 2, s1);
            }
        }
    }
}
//按学号从大到小排
void SortStudentListById1(SqList<Student>& list) {
    int len = list.GetLength();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            Student s1, s2;
            list.GetElem(j + 1, s1);
            list.GetElem(j + 2, s2);


            if (s2.id > s1.id) {
                list.SetElem(j + 1, s2);
                list.SetElem(j + 2, s1);
            }
        }
    }
}

//把数据存入文件中
void SaveToFile(SqList<Student>& list, string filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "数据存入失败" << endl;
        return;
    }
    for (int i = 1; i <= list.GetLength(); i++) {
        Student s;
        list.GetElem(i, s);
        outFile << s.id << " " << s.name << " " << s.GPA << endl;
    }
    outFile.close();
}

//把文件数据读会顺序表
void LoadFromFile(SqList<Student>& list, string filename) {
    ifstream inFile(filename);
    if (!inFile) {
        return;
    }
    Student s;
    while (inFile >> s.id >> s.name >> s.GPA) {
        list.InsertElem(list.GetLength() + 1, s);
    }
    inFile.close();
}

int main() {
    SqList<Student> List;
    int choice;

    // ⭐ 1. 程序一启动，先去文件里把上次存的数据读出来
    LoadFromFile(List, "students_data.txt");

    while (true) {
        // 打印菜单界面
        cout << "\n欢迎使用本学生信息管理系统,以下是该系统的功能:" << endl;
        cout << "1. 显示所有学生信息" << endl;
        cout << "2. 录入学生信息" << endl;
        cout << "3. 按学号或姓名查找学生" << endl;
        cout << "4. 删除指定位置的学生" << endl;
        cout << "5. 更新指定位置的学生信息" << endl;
        cout << "6. 统计学生人数" << endl;
        cout << "7. 按绩点或学号排序" << endl;
        cout << "8. 清空所有记录" << endl;
        cout << "0. 退出系统" << endl;
        cout << endl;
        cout << "请输入你的选择: ";


        // 判断读取是否成功
        if (!(cin >> choice)) {
            cin.clear();               // 清除错误状态，让 cin 重新工作
            cin.ignore(10000, '\n');   // 把刚才输入的字母和回车从缓冲区清空

            cout << "输入无效，请输入整数！" << endl;

            continue;
        }

        // 只有上面成功通过了，才会执行这里
        if (choice == 0) {
            // ⭐ 2. 用户选择退出时，把数据全存进文件
            SaveToFile(List, "students_data.txt");
            cout << "数据已保存，感谢使用，再见！" << endl;
            break;
        }

        if (choice == 0) {
            cout << "感谢使用,再见!" << endl;
            break;
        }
        else if (choice >= 1 && choice <= 8) {
            switch (choice) {
            case 1: { //显示
                if (List.IsEmpty()) {
                    cout << "该系统暂无任何学生数据" << endl;
                }
                else {
                    cout << "以下是所有学生数据" << endl;
                    List.Traverse(VisitStudent);
                }
                break; //
            }

            case 2: { //录入
                Student s = inputStudent();
                int pos;
                cout << "请输入要插入的位置 (1-" << List.GetLength() + 1 << "): ";
                cin >> pos;

                if (List.InsertElem(pos, s) == 1) {
                    cout << "录入成功！" << endl;
                }
                else {
                    cout << "录入失败！位置无效或表已满。" << endl;
                }
                break;
            }

            case 3: { //查找
                cout << "请选择查找方式:1.按学号查找 2.按名字查找" << endl;
                cout << "请输入选项(1或2)";
                int Type;
                cin >> Type;
                string key;
                if (Type == 1) {
                    cout << "请输入要查找的学号: "; cin >> key;
                }
                else if (Type == 2) {
                    cout << "请输入要查找的姓名: "; cin >> key;
                }
                else {
                    cout << "输入不符合规范" << endl;
                    break;
                }
                cout << endl;
                int found = 0;
                for (int i = 1; i <= List.GetLength(); i++) {
                    Student s;
                    List.GetElem(i, s);

                    if ((Type == 1 && s.id == key) || (Type == 2 && s.name == key)) {
                        cout << "找到了！该学生信息在第 " << i << " 个位置。" << endl;
                        cout << "学号: " << s.id
                            << "\t姓名: " << s.name
                            << "\t绩点: " << s.GPA << endl;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    cout << "该系统里不存在所查找的学生信息！" << endl;
                }
                break;
            }

            case 4: { //删除
                int pos;
                cout << "请输入要删除的位置 (1-" << List.GetLength() << "): " << endl;
                cin >> pos;

                Student deleted;
                if (List.DeleteElem(pos, deleted) == 1) {
                    cout << "删除成功！被删除的学生是: " << endl;
                    cout << "学号: " << deleted.id << "\t姓名: " << deleted.name << "\t绩点: " << deleted.GPA << endl;
                }
                else {
                    cout << "删除失败！请检查你的输入是否正确" << endl;
                }
                break;
            }
            case 5: {//更新
                int pos1;
                cout << "请输入想要更新的数据位置(1-" << List.GetLength() << "):" << endl;
                cin >> pos1;
                Student update;
                if (List.GetElem(pos1, update) == 1) {
                    cout << "已找到要被更新的学生信息!" << endl;
                    cout << "请输入新的学生信息:" << endl;
                    Student update1 = inputStudent();
                    if (List.SetElem(pos1, update1) == 1) {
                        cout << "恭喜,更新信息成功!" << endl;
                    }
                }
                else {
                    cout << "更新失败!请检查更新位置是否存在!" << endl;
                }
                break;
            }
            case 6: {//统计
                cout << "本系统此时统计学生人数为" << List.GetLength() << "人" << endl;
                break;
            }
            case 7: {//排序
                int type1, type2;
                cout << "请选择排序方式:1.按学号排 2.按绩点排:";
                cin >> type1;
                cout << endl;
                if (type1 == 1) {
                    cout << "请选择按学号排序方式:1.从大到小 2.从小到大:";
                    cin >> type2;
                    cout << endl;
                    if (type2 == 1) {
                        cout << "已为您按学号从大到小排序,可通过显示功能查看!" << endl;
                        SortStudentListById1(List);
                    }
                    else if (type2 == 2) {
                        cout << "已为您按学号从小到大排序,可通过显示功能查看!" << endl;
                        SortStudentListById(List);
                    }
                }
                else if (type1 == 2) {
                    cout << "请选择按绩点排序方式:1.从高到低 2.从低到高:";
                    cin >> type2;
                    cout << endl;
                    if (type2 == 1) {
                        cout << "已为您按绩点从高到低排序,可通过显示功能查看!" << endl;
                        sortStudentList(List);
                    }
                    else if (type2 == 2) {
                        cout << "已为您按绩点从低到高排序,可通过显示功能查看!" << endl;
                        sortStudentList1(List);
                    }
                }
                break;
            }
            case 8: {//清空
                List.Clear();
                cout << "已清空本系统所有学生信息,可使用显示功能查看" << endl;
                break;
            }

            }

        }
        else {
            cout << "您输入不正确,请重新输入" << endl;

        }
    }
}

















