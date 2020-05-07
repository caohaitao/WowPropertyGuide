#pragma once
#include "vector"
#include "map"
class Equip
{
public:
        enum PlaceType
        {
                UNKNOWN = 0,
                TOU = 1,
                XIANGLIAN = 2,
                JIANBANG = 3,
                PIFENG = 4,
                XIONGJIA = 5,
                HUWAN = 6,
                SHOU = 7,
                YAODAI = 8,
                TUI = 9,
                XIE = 10,
                JIEZHI = 11
        };
        Equip();
        ~Equip();

        bool InitFromFile(const wchar_t * file_path);

        std::wstring m_name;
        PlaceType m_place_type;
        float m_liliang;
        float m_minjie;
        float m_zhili;
        float m_jingshen;
        float m_gongqiang;
        float m_baoji;
        float m_mingzhong;
        float m_naili;
};

std::wstring PlaceTypeToChinese(Equip::PlaceType pt);
Equip::PlaceType ChineseToPlaceType(std::wstring name);

class TaoZhuangPro;
class Equips
{
public:
        void InitFromFolders(const wchar_t * folder_path);

        std::vector<Equip> & GetEquips();
        void CacWholeProperty(
                float & liliang,
                float & minjie,
                float & zhili,
                float & jingshen,
                float & gongqiang,
                float & baoji,
                float & mingzhong,
                float & naili);
        void Print();
        void PrinProperty();
        void GetPrintStrings(
                std::vector<TaoZhuangPro> & tao_pros,
                std::vector<std::wstring> & strs);
protected:
        std::vector<Equip> m_equips;
};

struct TaoPro
{
        std::wstring shuxing;
        float value;
};

class TaoZhuangPro
{
public:
        std::vector<std::wstring> m_names;
        std::map<int, TaoPro> m_pros;
        bool InitFromFile(const wchar_t * file_path);
        int GetNums(Equips & eq);
};

void InitTaoZhuangPros(const wchar_t * folder_path, std::vector<TaoZhuangPro> & pros);

float ZhanShiScoreCac(Equips & eq, float min_minghzong, float baoji_huansuan, std::vector<TaoZhuangPro> & tao_pros);