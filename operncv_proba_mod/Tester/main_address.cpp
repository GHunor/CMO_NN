#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

#include <conio.h>
#include <dir.h>
#include <process.h>
#include <stdio.h>
#include <sysinfoapi.h>
#include <synchapi.h>

#include "useful_macros.h"


struct blabla{
    std::ofstream myfile;
    std::string place;
    blabla(){};
    //blabla(std::string fname){myfile.open((place + "/" + fname).c_str());}
    void set_place(std::string Pname){
        place = Pname;
        mkdir(place.c_str());
    }
    void open(std::string fname){
        mkdir(place.c_str());
        myfile.open ((place + "/" + fname).c_str());
        //if(myfile.fail()) {std::cout<<"what is missing???\n";std::cin.ignore();}
    }
    void close(){
        myfile.close();
    }
    void refresh(std::string fname){
        myfile.close();
        myfile.open ((place + "/" + fname).c_str());
    }
    void push(std::string data){
        myfile << data;
    }
};

class file_address{
#define NULL 0
        struct Node{
            struct NP{
                Node* p;
                NP(){
                    p = NULL;
                }
                NP(Node* P){
                    p = P;
                }
                ~NP(){}
                Node * to_pointer() const {
                    return p;
                }
                Node* operator=(NP P){
                    return P.p;
                }
                Node* operator-> ( ){
                    return p;
                }
                Node operator* ( ){
                    return *p;
                }
                operator Node *(){
                    return p;
                }

            };
            friend bool operator<(Node::NP N1, Node::NP N2) {
                return N1->name<N2->name;
            }
            friend bool operator==(Node::NP N1, const std::string& dirname){
                return N1->name==dirname;
            }
            friend bool operator==(Node::NP N1, Node::NP N2){
                return N1->name==N2->name;
            }

            std::string name;
            Node* parent;

            std::set<NP> children;
            Node(){
                parent = NULL;
            }
            Node(std::string Name, Node* Parent){
                parent = Parent;
                name = Name;
            }
            Node::NP find_child(std::string Childname){
                Node* Child = new Node(Childname, this);
                std::set<Node::NP>::iterator cIT = children.find(Child);
                if (cIT == children.end()){
                    delete Child;
                    return NULL;
                }else{
                    delete Child;
                    return *cIT;
                }
            }
            bool is_child(std::string Childname){
                Node *Child = new Node(Childname, this);
                std::set<NP>::iterator cIT = children.find(Child);
                if (cIT == children.end()){
                    delete Child;
                    return 0;
                }else{
                    delete Child;
                    return 1;
                }
            }
            void add_child(Node* Child){
                children.insert(Child);
            }
            void add_child(std::string Childname){
                Node* Child = new Node(Childname, this);
                children.insert(Child);
            }
        };


        Node Master;
        Node* current;
        std::vector<std::string> _break_up(std::string address){
            std::vector<std::string> ret;
            std::string tmp = "";
            int ind = 0;
            for IRANGE(address.length()){
                if (address[i] == '/' && i != 0){
                    ret.push_back(address.substr(ind, i));
                    ind = i+1;
                }
            }
            ret.push_back(address.substr(ind, address.length()-1));
            return ret;
        }
        void help_create(Node::NP Cur){
            for THROUGH_CONTAINER(std::set<Node::NP>, Cur->children){
                help_delete(*IT);
            }
            mkdir((Address(Cur)).c_str());
        }

        void help_delete(Node::NP Cur){
            for THROUGH_CONTAINER(std::set<Node::NP>, Cur->children){
                help_delete(*IT);
            }
            delete Cur;
        }
        public:
        file_address(){current = &Master;};
        file_address(std::string address){
            current = &Master;
            std::vector<std::string> dirs = _break_up(address);
            current->name = dirs[0];
            for IRANGE(dirs.size()-1){
                current->add_child(dirs[i+1]);
                Move_down(dirs[i+1]);
            }
            current = &Master;
        }
        ~file_address(){
            help_delete(&Master);
        }

        bool Move_down(const std::string& dirname){
            current=current->find_child(dirname);
            if (current == NULL) {current = &Master; return 1;}
            return 0;
        }
        bool Move_up(){
            current=current->parent;
            if (current == NULL) {current = &Master; return 1;}
            return 0;
        }
        std::string Where_at(){
            return current->name;
        }
        std::vector<std::string> Who_children(Node* Cur = NULL){
            if (Cur == NULL) Cur = current;
            std::vector<std::string> ret;
            for THROUGH_CONTAINER(std::set<Node::NP>, Cur->children) {
                ret.push_back((IT->to_pointer())->name);
            }
            return ret;
        }
        std::string Who_parent(Node* Cur = NULL){
            if (Cur == NULL) Cur = current;
            return Cur->parent->name;
        }
        void Add_child(std::string dirname, Node* Cur = NULL){
            if (Cur == NULL) Cur = current;
            Node* tmp = new Node(dirname, Cur);
            Cur->add_child(tmp);
        }
        void MakeDir(std::string address){
            current = &Master;
            std::vector<std::string> dirs = _break_up(address);
            current->name = dirs[0];
            for IRANGE(dirs.size()-1){
                current->add_child(dirs[i+1]);
                Move_down(dirs[i+1]);
            }
            current = &Master;
        };  /// just creates nodes vased on address
        void MakeDirR(){
            help_create(&Master);

        };  /// goes through tree and makes directories
        std::string Address(Node* Cur = NULL){
            if (Cur == NULL) Cur = current;
            std::string ret = Where_at();
            while(!Move_up()){
                ret = '/' + ret;
                ret = Where_at() + ret;
            }
            return ret;
        };



};

std::vector<std::string> break_up_address(std::string address){
    std::vector<std::string> ret;
    std::string tmp = "";
    int ind = 0;
    int end = address.length()-1;
    bool dot = false;
    for IRANGE(address.length()){
        if(address[i] == '/' && i==address.length()-1){
            end--;
            break;
        }
        if (address[i] == '/' && i != 0 && !dot){
            ret.push_back(address.substr(ind, i));
            ind = i+1;
        }else{
            if (address[i] == '.' && (i != 0 || dot)){
                dot = true;
            }else{
                dot = false;
            }
        }
    }
    ret.push_back(address.substr(ind, end));
    return ret;
}

void create_directories(std::vector<std::string> address){
    std::string tmp = address[0];
    mkdir(tmp.c_str());
    for IRANGE(address.size()-1){
            tmp = tmp + '/' + address[i+1];
            mkdir(tmp.c_str());
    }
}

void create_directories(std::string address){
    create_directories(break_up_address(address));
}

class Interval
{
private:
    unsigned int initial_;

public:
    inline Interval() : initial_(GetTickCount()){}
    virtual ~Interval(){}

    inline unsigned int value() const
    {
        return GetTickCount()-initial_;
    }
};


class time_management{
    unsigned int min;
    unsigned int max;
    //int rps; // run per second;
    unsigned int init, mom, var;
public:
    inline time_management(unsigned int Min = 25, unsigned int Max = 1000): min(Min), max(Max), init(GetTickCount()), mom(GetTickCount()), var(0){};
    inline unsigned int Call(){

        var = mom - GetTickCount();
        mom = GetTickCount();
        return var;
    }
    inline bool Is_wait(){
        return var<min;
    }
    inline void wait(unsigned int i){
        Sleep(i-Call());
    }
    inline unsigned int OValue() const
    {
        return GetTickCount()-init;
    }

};
int main(
        //int argc, char** argv
        ) {
    /*
    int check;
    //std::string String = "../ttt/test";
    std::string String = "tt/test";
    const char *dirname = String.c_str();
    //clrscr();
    check = mkdir(dirname);
    //checking if directory is created
    if (!check){
        printf("Directory created\n");
        std::cout << check;
    }
    else {
        printf("Unable to create directory\n");
        std::cout << check;
        exit(1);
    }
    getch();
    system("dir/p");
    getch();
    return 0;
     */
    /*
    blabla bla;
    mkdir("dier");
    bla.set_place("dier/dier2");
    bla.open("example.txt");
    bla.push("Writing this to a file.\n");
    bla.refresh("example2.txt");
    bla.push("Writing this to a file sjkahfjksd.\n");
    bla.close();
    return 0;
     */
    //create_directories("../dier/dier2");


}