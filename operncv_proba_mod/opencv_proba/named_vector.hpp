//
// Created by ghuno on 2022-03-22.
//

#ifndef TESTER_NAMED_VECTOR_HPP
#define TESTER_NAMED_VECTOR_HPP

#include <map>

struct complex_id{
    std::string* name_ID;
    int num_ID;
};
template<typename T>
class named_vector: public std::vector<T>{
    std::map<std::string,size_t> names;
    std::map<size_t,std::string*> reverse_connect;
public:
    bool push_back(T data, std::string new_name){
        if(names.find(new_name) == names.end()){
            return true;
        }
        push_back(data);
        names.insert(new_name, std::vector<T>::size()-1);
        reverse_connect.insert(std::vector<T>::size()-1,(std::string*)names[new_name]);
    }
    T at(std::string name){
        std::map<std::string, size_t>::iterator IT = names.find(name);
        if( IT == names.end()){
            return std::vector<T>::operator[](std::vector<T>::size());
        }
        return at(IT->second);
    }
    T operator[](std::string name){
        return at(name);
    }
    std::string Get_name(size_t I){
        if(I>=std::vector<T>::size()){
            return "";
        }
        std::map<size_t, std::string* >::iterator IT = reverse_connect.find(I);
        if( IT == reverse_connect.end()){
            return std::vector<T>::operator[](std::vector<T>::size());
        }
        return *(IT->second);
    }
};


#endif //TESTER_NAMED_VECTOR_HPP
