#include <bits/stdc++.h>
using namespace std;

int pagesize;
class record
{
private:
    int key;
    int recordsize;
    int pageid;
    int slotid;

public:
    void setpageid(int k)
    {
        pageid = k;
    }
    int getpageid()
    {
        return pageid;
    }
    void setslotid(int l)
    {
        slotid = l;
    }
    int getslotid()
    {
        return slotid;
    }
    void setkey(int data)
    {
        key = data;
    }
    int getkey()
    {
        return key;
    }
    void setrecordsize(int siz)
    {
        recordsize = siz;
    }
    int getrecordsize()
    {
        return recordsize;
    }
};

class page
{
private:
    int sizeofpage;
    int spaceleft;
    int pageid;
    vector<record> recordsvector;
    // book keeping records
    page *nextpageaddr;
    page *prevpageaddr;
    int numofrecords;
    int freespacebaseaddr;

public:
    // this constructor is for the root page
    page(int size)
    {
        this->sizeofpage = size;
        this->freespacebaseaddr = 0;
        this->numofrecords = 0;
        this->spaceleft = size;
        this->pageid = 0;
        this->prevpageaddr = nullptr;
        this->nextpageaddr = nullptr;
    }

    void newpage(page *lastpage)
    {
        this->sizeofpage = lastpage->sizeofpage;
        this->freespacebaseaddr = 0;
        this->numofrecords = 0;
        this->spaceleft = lastpage->sizeofpage;
        this->pageid = lastpage->pageid + 1;
        this->nextpageaddr = nullptr;
        this->prevpageaddr = lastpage;
        lastpage->nextpageaddr = this;
    }

    int getpageid()
    {
        return pageid;
    }

    void setpageid(int j)
    {
        pageid = j;
    }

    int getnumofrecords()
    {
        return numofrecords;
    }

    void setnextpage(page *n)
    {
        this->nextpageaddr = n;
    }

    void setprevpage(page *p)
    {
        this->prevpageaddr = p;
    }

    page *getprevpage()
    {
        return this->prevpageaddr;
    }

    page *getnextpage()
    {
        return this->nextpageaddr;
    }

    vector<record> getrecordsvector()
    {
        return recordsvector;
    }

    bool has_space(record r)
    {
        if (r.getrecordsize() + 4 + 16 <= this->spaceleft)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int getspacebaseaddr()
    {
        return freespacebaseaddr;
    }

    void insertrecord(record r)
    {
        this->recordsvector.push_back(r);
        numofrecords++;
        freespacebaseaddr = sizeofpage - spaceleft + 1;
        spaceleft -= r.getrecordsize()+4;
    }
};

class heapfile
{
private:
    page *root;
    int numofpages;

public:
    heapfile()
    {
        root = nullptr;
        numofpages = 0;
    }

    void setroot(page *p)
    {
        numofpages = 1;
        root = p;
    }

    int getnumofpages()
    {
        return numofpages;
    }

    void setnumofpages()
    {
        numofpages = 0;
        page *p = root;
        while (p != nullptr)
        {
            numofpages++;
            p = p->getnextpage();
        }
    }

    void showstatus()
    {
        this->setnumofpages();
        cout << numofpages << " ";
        page *p = root;
        while (p != nullptr)
        {
            cout << p->getnumofrecords() << " ";
            p = p->getnextpage();
        }
        cout << endl;
    }

    void search(int t)
    {
        page *r = root;
        while (r != nullptr)
        {
            for (auto i = r->getrecordsvector().begin(); i < r->getrecordsvector().end(); i++)
            {
                if (i->getkey() == t)
                {
                    cout << i->getpageid() << " " << i->getslotid() << endl;
                    return;
                }
            }
            r = r->getnextpage();
        }
        cout << -1 << " " << -1 << endl;
    }

    void insert(int rsize, int rdata)
    {
        page *m = root;
        record ri;
        ri.setkey(rdata);
        ri.setrecordsize(rsize);
        bool flag = false;
        page *lastpage;
        while (m != nullptr)
        {
            if (m->has_space(ri))
            {
                ri.setpageid(m->getpageid());
                ri.setslotid(m->getspacebaseaddr());
                m->insertrecord(ri);
                flag = true;
            }
            lastpage = m;
            m = m->getnextpage();
        }
        if (flag == false)
        {
            // newpage and insert the data here as the data hasn't been inserted in the prev page
            page *np = new page(pagesize);
            np->newpage(lastpage);
            np->insertrecord(ri);
        }
    }
};

heapfile hf;
int main()
{
    // int pagesize;
    cin >> pagesize;
    int a = 0;
    int cnt = 0;
    while (a != 4)
    {
        cin >> a;
        if (a == 2)
        {
            hf.showstatus();
        }
        else if (a == 3)
        {
            int tosearch;
            cin >> tosearch;
            hf.search(tosearch);
        }
        else if (a == 1)
        {
            cnt++;
            if (cnt == 1)
            {
                page *root = new page(pagesize);
                hf.setroot(root);
                int recsize, recdata;
                cin >> recsize >> recdata;
                hf.insert(recsize, recdata);
            }
            else
            {
                int recsize, recdata;
                cin >> recsize >> recdata;
                hf.insert(recsize, recdata);
            }
        }
    }

    return 0;
}