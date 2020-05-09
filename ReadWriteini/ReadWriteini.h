
/*
 * @Description: ���ڶ�ȡini�����ļ�
 * @version:0.0.1
 * @Author: windSnowLi
 * @Date:2020/5/7
 * @LastEditors: windSnowLi
 * @LastEditTime:2020/5/9
 */

#ifndef READWRITE_H_
#define READWRITE_H_
#include <unordered_map>
#include <string>
#ifndef MAX_PATH
#define MAX_PATH 260
#endif // !MAX_PATH
namespace rwini {


    class ReadWriteini {
    private:
        //�����ļ�·��ȫ��
        char iniPath[MAX_PATH];
        //[section [key,value] ]
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* iniContent = new std::unordered_map<std::string, std::unordered_map<std::string, std::string>>();
    public:
        //���캯��,����Ϊini�ļ�����·��
        ReadWriteini(const char* inipath);
        //��������
        ~ReadWriteini();
        //����ָ��[section [key,value] ]
        bool FindValue(const char* section, const char* key, char* value);
        //����value
        bool SetValue(const char* section, const char* key, const char* value);
        //����key
        bool SetKey(const char* section, const char* oldkey, const char* newkey);
        //����section
        bool InsertSection(const char* section);
        //����key
        bool InsertKey(const char* section, const char* key, const char* value);
        //ɾ��section
        bool DeleteSection(const char* section);
        //ɾ��key
        bool DeleteKey(const char* section, const char* key);
        //д��ini�ļ�
        bool Writeini();
        //�������
        void show();
    };
}
#endif // !READWRITE_H_