#include "stdafx.h"
#include "Equip.h"
#include "TIo.h"
#include "map"
#include "CHTCommon.h"

Equip::Equip()
        :m_place_type(UNKNOWN)
        ,m_liliang(0)
        ,m_minjie(0)
        ,m_zhili(0)
        ,m_jingshen(0)
        ,m_gongqiang(0)
        ,m_baoji(0)
        ,m_mingzhong(0)
        ,m_naili(0)
{
}


Equip::~Equip()
{
}

wstring GetPathName(wstring path)
{
        vector<wstring> ls;
        CHTCommon::SplitString(path, L'\\', ls);
        if (ls.size() == 0)
        {
                return L"";
        }
        wstring res = *ls.rbegin();
        res = res.substr(0, res.length() - 4);
        return res;
}

bool Equip::InitFromFile(const wchar_t * file_path)
{
        std::map<wstring, wstring> values;
        if (!TIo::ReadKeyValueFileW(file_path, values))
        {
                return false;
        }
        this->m_name = GetPathName(file_path);
        std::map<wstring, wstring>::iterator it = values.begin();
        for (it; it != values.end(); it++)
        {
                if (it->first == L"��λ")
                {
                        this->m_place_type = ChineseToPlaceType(it->second);
                }
                else if (it->first == L"����")
                {
                        this->m_liliang = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_minjie = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_zhili = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_jingshen = _wtof(it->second.c_str());
                }
                else if (it->first == L"��ǿ")
                {
                        this->m_gongqiang = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_baoji = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_mingzhong = _wtof(it->second.c_str());
                }
                else if (it->first == L"����")
                {
                        this->m_naili = _wtof(it->second.c_str());
                }
                else {
                        printf("unknown value key\n");
                }
        }
        if (this->m_place_type == UNKNOWN)
        {
                return false;
        }
        return true;
}

void FileFind(CString DirPath, std::vector<CString> & files)

{
        CFileFind finder;
        CString NewDirPath = DirPath + L"\\*.*";
        BOOL bWorking = finder.FindFile(NewDirPath);
        while (bWorking)
        {
                bWorking = finder.FindNextFile();
                if (finder.IsDots())

                {
                        continue;
                }
                else
                {
                        files.push_back(finder.GetFilePath());
                }
        }
}

std::wstring PlaceTypeToChinese(Equip::PlaceType pt)
{
        if (pt == Equip::TOU)
        {
                return L"ͷ";
        }
        else if (pt == Equip::XIANGLIAN)
        {
                return L"����";
        }
        else if (pt == Equip::JIANBANG)
        {
                return L"���";
        }
        else if (pt == Equip::PIFENG)
        {
                return L"����";
        }
        else if (pt == Equip::XIONGJIA)
        {
                return L"�ؼ�";
        }
        else if (pt == Equip::HUWAN)
        {
                return L"����";
        }
        else if (pt == Equip::SHOU)
        {
                return L"��";
        }
        else if (pt == Equip::YAODAI)
        {
                return L"����";
        }
        else if (pt == Equip::TUI)
        {
                return L"��";
        }
        else if (pt == Equip::XIE)
        {
                return L"Ь";
        }
        else if (pt == Equip::JIEZHI)
        {
                return L"��ָ";
        }
        printf("PlaceTypeToChinese failed\n");
        return L"";
}

Equip::PlaceType ChineseToPlaceType(std::wstring name)
{
        if (name == L"ͷ")
        {
                return Equip::TOU;
        }
        else if (name == L"����")
        {
                return Equip::XIANGLIAN;
        }
        else if (name == L"���")
        {
                return Equip::JIANBANG;
        }
        else if (name == L"����")
        {
                return Equip::PIFENG;
        }
        else if (name == L"�ؼ�")
        {
                return Equip::XIONGJIA;
        }
        else if (name == L"����")
        {
                return Equip::HUWAN;
        }
        else if (name == L"��")
        {
                return Equip::SHOU;
        }
        else if (name == L"����")
        {
                return Equip::YAODAI;
        }
        else if (name == L"��")
        {
                return Equip::TUI;
        }
        else if (name == L"Ь")
        {
                return Equip::XIE;
        }
        else if (name == L"��ָ")
        {
                return Equip::JIEZHI;
        }
        printf("ChineseToPlaceType failed\n");
        return Equip::UNKNOWN;
}

void InitTaoZhuangPros(
        const wchar_t * folder_path,
        std::vector<TaoZhuangPro> & pros)
{
        std::vector<CString> files;
        FileFind(folder_path, files);
        for (int i = 0; i < files.size(); i++)
        {
                CString & ci = files[i];
                if (ci.Find(L".tao") != -1)
                {
                        TaoZhuangPro tzp;
                        if (tzp.InitFromFile((LPTSTR)(LPCTSTR)ci))
                        {
                                pros.push_back(tzp);
                        }
                }
        }
}

static void GetTaoProperty(Equips & eq, 
        std::vector<TaoZhuangPro> & tao_pros,
        float & gongqiang,
        float & naili,
        float & baoji,
        float & mingzhong)
{
        for (int i = 0; i < tao_pros.size(); i++)
        {
                TaoZhuangPro & tp = tao_pros[i];
                int ni = tp.GetNums(eq);
                if (ni > 1)
                {
                        std::map<int, TaoPro>::iterator it = tp.m_pros.begin();
                        for (it; it != tp.m_pros.end(); it++)
                        {
                                if (ni >= it->first)
                                {
                                        TaoPro & tpi = it->second;
                                        if (tpi.shuxing == L"��ǿ")
                                        {
                                                gongqiang += tpi.value;
                                        }
                                        else if (tpi.shuxing == L"����")
                                        {
                                                naili += tpi.value;
                                        }
                                        else if (tpi.shuxing == L"����")
                                        {
                                                baoji += tpi.value;
                                        }
                                        else if (tpi.shuxing == L"����")
                                        {
                                                mingzhong += tpi.value;
                                        }
                                }
                        }
                }
        }
}

float ZhanShiScoreCac(
        Equips & eq,
        float min_minghzong,
        float baoji_huansuan,
        std::vector<TaoZhuangPro> & tao_pros)
{
        float liliang = 0;
        float minjie = 0;
        float zhili = 0;
        float jingshen = 0;
        float gongqiang = 0;
        float baoji = 0;
        float mingzhong = 0;
        float naili = 0;
        eq.CacWholeProperty(liliang, minjie, zhili, jingshen, gongqiang, baoji, mingzhong, naili);

        GetTaoProperty(eq, tao_pros, gongqiang, naili, baoji, mingzhong);

        if (mingzhong<min_minghzong - 0.1)
        {
                return -1;
        }
        baoji += minjie / 20.0;
        gongqiang += liliang*2.0;
        gongqiang += baoji*baoji_huansuan;
        return gongqiang;
}

void Equips::InitFromFolders(const wchar_t * folder_path)
{
        std::vector<CString> files;
        FileFind(folder_path,files);
        for (int i = 0; i < files.size(); i++)
        {
                CString & ci = files[i];
                if (ci.Find(L".equ") != -1)
                {
                        Equip equ;
                        if (equ.InitFromFile(ci) == false)
                        {
                                continue;
                        }
                        m_equips.push_back(equ);
                }
        }
}

std::vector<Equip> & Equips::GetEquips()
{
        return m_equips;
}

void Equips::CacWholeProperty(
        float & liliang,
        float & minjie,
        float & zhili,
        float & jingshen,
        float & gongqiang,
        float & baoji,
        float & mingzhong,
        float & naili)
{
        for (int i = 0; i < m_equips.size(); i++)
        {
                Equip & e = m_equips[i];
                liliang += e.m_liliang;
                minjie += e.m_minjie;
                zhili += e.m_zhili;
                jingshen += e.m_jingshen;
                gongqiang += e.m_gongqiang;
                baoji += e.m_baoji;
                mingzhong += e.m_mingzhong;
                naili += e.m_naili;
        }
}

void Equips::Print()
{
        for (int i = 0; i < m_equips.size();i++)
        {
                Equip & eq = m_equips[i];
                std::wstring wplace = PlaceTypeToChinese(eq.m_place_type);

                std::string cplace = CHTCommon::ANSIWStringtoANSIString(wplace);

                std::string cname = CHTCommon::ANSIWStringtoANSIString(eq.m_name);

                printf("%s:%s\n", cplace.c_str(), cname.c_str());

        }
}

void Equips::PrinProperty()
{
        float liliang = 0;
        float minjie = 0;
        float zhili = 0;
        float jingshen = 0;
        float gongqiang = 0;
        float baoji = 0;
        float mingzhong = 0;
        float naili = 0;
        CacWholeProperty(liliang, minjie, zhili, jingshen, gongqiang, baoji, mingzhong, naili);
        printf("����=%0.4f\n", liliang);
        printf("����=%0.4f\n", minjie);
        printf("����=%0.4f\n", zhili);
        printf("����=%0.4f\n", jingshen);
        printf("��ǿ=%0.4f\n", gongqiang);
        printf("����=%0.4f\n", baoji);
        printf("����=%0.4f\n", mingzhong);
        printf("����=%0.4f\n", naili);
}

static std::wstring MakeWstr(const wchar_t * pre, float value)
{
        wchar_t wstr[1024] = { 0 };
        swprintf_s(wstr, L"%s=%0.4f", pre, value);
        return std::wstring(wstr);
}

void Equips::GetPrintStrings(
        std::vector<TaoZhuangPro> & tao_pros,
        std::vector<std::wstring> & strs)
{
        for (int i = 0; i < m_equips.size(); i++)
        {
                Equip & eq = m_equips[i];
                std::wstring wplace = PlaceTypeToChinese(eq.m_place_type);

                wchar_t wstr[1024] = { 0 };
                swprintf_s(wstr,L"%s:%s", wplace.c_str(), eq.m_name.c_str());
                strs.push_back(wstr);
        }

        float liliang = 0;
        float minjie = 0;
        float zhili = 0;
        float jingshen = 0;
        float gongqiang = 0;
        float baoji = 0;
        float mingzhong = 0;
        float naili = 0;
        CacWholeProperty(liliang, minjie, zhili, jingshen, gongqiang, baoji, mingzhong, naili);
        GetTaoProperty(*this, tao_pros, gongqiang, naili, baoji, mingzhong);
        strs.push_back(MakeWstr(L"����", liliang));
        strs.push_back(MakeWstr(L"����", minjie));
        strs.push_back(MakeWstr(L"����", zhili));
        strs.push_back(MakeWstr(L"����", jingshen));
        strs.push_back(MakeWstr(L"��ǿ", gongqiang));
        strs.push_back(MakeWstr(L"����", baoji));
        strs.push_back(MakeWstr(L"����", mingzhong));
        strs.push_back(MakeWstr(L"����", naili));
}

bool TaoZhuangPro::InitFromFile(const wchar_t * file_path)
{
        std::vector<std::wstring> wss;
        bool b = TIo::ReadFileW(file_path, wss);
        if (!b)
        {
                return false;
        }
        CHTCommon::SplitString(wss[0], L',', m_names);
        for (int i = 1; i < wss.size();i++)
        {
                std::vector<std::wstring> wsi;
                CHTCommon::SplitString(wss[i], L'=', wsi);
                if (wsi.size() != 2)
                {
                        continue;
                }
                int index = _wtof(wsi[0].c_str());
                std::vector<std::wstring> wsi2;
                CHTCommon::SplitString(wsi[1], L',', wsi2);
                TaoPro tp;
                tp.shuxing = wsi2[0];
                tp.value = _wtof(wsi2[1].c_str());
                m_pros[index] = tp;
        }
        return true;
}

int TaoZhuangPro::GetNums(Equips & eq)
{
        int nums = 0;
        for (int i = 0; i < eq.GetEquips().size();i++)
        {
                Equip & e = eq.GetEquips()[i];
                std::vector<std::wstring>::iterator find_it =
                        std::find(m_names.begin(), m_names.end(), e.m_name);
                if (find_it != m_names.end())
                {
                        nums++;
                }
        }
        return nums;
}
