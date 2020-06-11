
/*
 * @Description: ���ڶ�ȡini�����ļ�
 * @version:0.0.1
 * @Author: windSnowLi
 * @Date:2020/5/7
 * @LastEditors: windSnowLi
 * @LastEditTime:2020/6/11
 */

#ifndef READWRITE_H_
#define READWRITE_H_
#include <unordered_map>
//Ϊ�˼���MSVC��MingW,�ڴ�������cstring��string
#include <cstring>
#include <string>
#include <sstream>
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
        //�����յ��Ĳ���ת��Ϊ�ַ���
        template <typename Type>
        std::string TypeToString(Type str);
    public:
        //���캯��,����Ϊini�ļ�����·��
        ReadWriteini(const char* inipath);
        //��������
        ~ReadWriteini();
        //����ָ��[section [key,value] ]
        template <typename Type1,typename Type2>
        bool FindValue(const Type1& tempsection, const Type2& tempkey, char* value);
        //����value
        template <typename Type1, typename Type2,typename Type3>
        bool SetValue(const Type1& tempsection, const Type2& tempkey, const Type3& value);
        //����key
        template <typename Type1, typename Type2, typename Type3>
        bool SetKey(const Type1& tempsection, const  Type2& tempoldkey, const  Type3& tempnewkey);
        //����section
        template <typename Type1>
        bool InsertSection(const Type1& tempsection);
        //����key
        template <typename Type1, typename Type2, typename Type3>
        bool InsertKey(const Type2& tempsection, const Type1& tempkey, const Type3& tempvalue);
        //ɾ��section
        template <typename Type1>
        bool DeleteSection(const Type1& tempsection);
        //ɾ��key
        template <typename Type1, typename Type2>
        bool DeleteKey(const Type1& tempsection, const Type2& tempkey);
        //д��ini�ļ�
        bool Writeini();
    };
}


#ifndef READWRITEINI_TEMPLATE_
#define READWRITEINI_TEMPLATE_
/*
 * @name:TypeToString
 * @describe:������ת��Ϊ�ַ�������
 * @param typename Type
 * @return:string
 */
template<typename Type>
std::string rwini::ReadWriteini::TypeToString(Type str)
{
    std::stringstream tempStrStream;
    std::string goalStr;
    tempStrStream << str;
    goalStr = tempStrStream.str();
    return goalStr;
}

/*
 * @name:FindValue
 * @describe:����section��key����value
 * @param const Type1& tempsection, const Type2& tempkey, char* value
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1, typename Type2>
bool rwini::ReadWriteini::FindValue(const Type1& tempsection, const Type2& tempkey, char* value)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    std::string key = TypeToString(tempkey);
    value[0] = '\0';
    if ((!section.empty()) && (!key.empty())) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            auto tempiter = iter->second.find(key);
            if (tempiter != iter->second.end()) {
                const char* tempStr = tempiter->second.c_str();
                memcpy(value, tempStr, sizeof(char) * strlen(tempStr));
                value[strlen(tempStr) + 1] = '\0';
                return true;
            }
        }
    }
    return false;
}

/*
 * @name:SetValue
 * @describe:����section key����value
 * @param const Type1& tempsection, const Type2& tempkey, const Type3& tempvalue
 * @return:bool
 */
 /*
  *2020/6/11�޸ģ�ʹ��ģ����ղ���
  */
template <typename Type1, typename Type2, typename Type3>
bool rwini::ReadWriteini::SetValue(const Type1& tempsection, const Type2& tempkey, const Type3& tempvalue)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    std::string key = TypeToString(tempkey);
    std::string value = TypeToString(tempvalue);
    if ((!section.empty()) && (!key.empty())) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            auto tempiter = iter->second.find(key);
            if (tempiter != iter->second.end()) {
                tempiter->second = value;
                return true;
            }
        }
    }
    return false;
}


/*
 * @name:SetKey
 * @describe:����section����key
 * @param {const char*, const char*,const char*}
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1, typename Type2, typename Type3>
bool rwini::ReadWriteini::SetKey(const Type1& tempsection, const  Type2& tempoldkey, const  Type3& tempnewkey)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    std::string oldkey = TypeToString(tempoldkey);
    std::string newkey = TypeToString(tempnewkey);
    if ((!section.empty()) && (!oldkey.empty()) && (!newkey.empty())) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            auto tempiter = iter->second.find(oldkey);
            if (tempiter != iter->second.end()) {
                char tempvalue[100] = { 0 };
                if (FindValue(section, oldkey, tempvalue)) {
                    iter->second.erase(tempiter);
                    iter->second.insert(std::make_pair(newkey, tempvalue));
                }
                return true;
            }
        }
    }
    return false;
}



/*
 * @name:InsertSection
 * @describe:����section
 * @param {const char*}
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1>
bool rwini::ReadWriteini::InsertSection(const Type1& tempsection)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    if (!section.empty()) {
        iniContent->insert(std::make_pair(section, std::unordered_map<std::string, std::string>()));
        return true;
    }
    return false;
}


/*
 * @name:InsertKey
 * @describe:����Key
 * @param const Type2& tempsection, const Type1& tempkey, const Type3& tempvalue
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1, typename Type2, typename Type3>
bool rwini::ReadWriteini::InsertKey(const Type2& tempsection, const Type1& tempkey, const Type3& tempvalue)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    std::string key = TypeToString(tempkey);
    std::string value = TypeToString(tempvalue);
    if ((!section.empty()) && (!key.empty())) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            iter->second.insert(std::make_pair(key, value));
            return true;
        }
    }
    return false;
}



/*
 * @name:DeleteSection
 * @describe:ɾ��section
 * @param const Type1& tempsection
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1>
bool rwini::ReadWriteini::DeleteSection(const Type1& tempsection)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    if (!section.empty()) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            iniContent->erase(iter);
            return true;
        }
    }
    return false;
}



/*
 * @name:DeleteKey
 * @describe:ɾ��Key
 * @param {const char*}
 * @return:bool
 */
 /*
 *2020/6/11�޸ģ�ʹ��ģ����ղ���
 */
template <typename Type1, typename Type2>
bool rwini::ReadWriteini::DeleteKey(const Type1& tempsection, const Type2& tempkey)
{
    //�����յĲ���ת��Ϊ�ַ���
    std::string section = TypeToString(tempsection);
    std::string key = TypeToString(tempkey);
    if ((!section.empty()) && (!key.empty())) {
        auto iter = iniContent->find(section);
        if (iter != iniContent->end()) {
            auto tempiter = iter->second.find(key);
            if (tempiter != iter->second.end()) {
                iter->second.erase(tempiter);
                return true;
            }
        }
    }
    return false;
}
#endif // !READWRITEINI_TEMPLATE_
#endif // !READWRITE_H_