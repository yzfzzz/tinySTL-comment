#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class MyString
{
public:
    static size_t CCtor; //ͳ�Ƶ��ÿ������캯���Ĵ���
    static size_t MCtor; //ͳ�Ƶ����ƶ����캯���Ĵ���
    static size_t CAsgn; //ͳ�Ƶ��ÿ�����ֵ�����Ĵ���
    static size_t MAsgn; //ͳ�Ƶ����ƶ���ֵ�����Ĵ���

public:
    // ���캯��
   MyString(const char* cstr=0){
       if (cstr) {
          m_data = new char[strlen(cstr)+1];
          strcpy(m_data, cstr);
       }
       else {
          m_data = new char[1];
          *m_data = '\0';
       }
   }

   // �������캯��
   MyString(const MyString& str) {
       CCtor ++;
       m_data = new char[ strlen(str.m_data) + 1 ];
       strcpy(m_data, str.m_data);
   }
   // �ƶ����캯��
   MyString(MyString&& str) noexcept
       :m_data(str.m_data) {
       MCtor ++;
       str.m_data = nullptr; //����ָ��֮ǰ����Դ��
   }

   // ������ֵ���� =������
   MyString& operator=(const MyString& str){
       CAsgn ++;
       if (this == &str) // �������Ҹ�ֵ!!
          return *this;

       delete[] m_data;
       m_data = new char[ strlen(str.m_data) + 1 ];
       strcpy(m_data, str.m_data);
       return *this;
   }

   // �ƶ���ֵ���� =������
   MyString& operator=(MyString&& str) noexcept{
       MAsgn ++;
       if (this == &str) // �������Ҹ�ֵ!!
          return *this;

       delete[] m_data;
       m_data = str.m_data;
       str.m_data = nullptr; //����ָ��֮ǰ����Դ��
       return *this;
   }

   ~MyString() {
       delete[] m_data;
   }

   char* get_c_str() const { return m_data; }
private:
   char* m_data;
};
size_t MyString::CCtor = 0;
size_t MyString::MCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MAsgn = 0;
int main()
{
    vector<MyString> vecStr;
    vecStr.reserve(1000); //�ȷ����1000���ռ�
    for(int i=0;i<1000;i++){
        MyString s = MyString("hello");
        vecStr.push_back(std::move(s));
    }
    cout << "CCtor = " << MyString::CCtor << endl;
    cout << "MCtor = " << MyString::MCtor << endl;
    cout << "CAsgn = " << MyString::CAsgn << endl;
    cout << "MAsgn = " << MyString::MAsgn << endl;
}

/* ���
CCtor = 0
MCtor = 1000
CAsgn = 0
MAsgn = 0
*/
