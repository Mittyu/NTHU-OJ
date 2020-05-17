#include <bits/stdc++.h>
#include "function.h"

extern int main();

namespace oj{

Employee::Employee(const std::string &name):name_(name), id_(ID_++){}


void Vector::erase(size_type pos){
  if (pos < size() && pos>=0){
    // for size=1
    if(size()==1)
      last_ = begin_;
    // for other cases
    else{
//      std::copy(begin_+pos+1,last_,begin_+pos);
      for(size_type i=pos+1; i<size();i++){
        begin_[i-1].~value_type();
        new (begin_+i-1) value_type(begin_[i]);
      }
      begin_[size()-1].~value_type();
      last_ -= 1;
    }
  }
}
//
void Vector::push_back(const_reference val){
  if (size() == capacity() ){
    reserve(std::max(capacity()+1,capacity()*3));
  }

  /** �n��placement new **/
  new (last_) value_type(val);
  last_ += 1;
}

void Vector::reserve(size_type new_capacity){
  size_type old_size = size();
  size_type old_capacity = capacity();
  if(new_capacity>old_capacity){
    /** �����m�߭��I�G�ϥ�static_cast **/
    pointer new_begin_(static_cast<pointer>(operator new[](new_capacity * sizeof(value_type))));

    for(size_type i=0;i<old_size;i++){
      new (new_begin_+i) value_type(begin_[i]);
      begin_[i].~value_type();
    }
    if(begin_!=nullptr)
      operator delete(begin_);
    // reassign the pointers
    begin_ = new_begin_;
    last_ = begin_+old_size;  // ���]�Ŷ� ���פ���
    end_ = begin_+new_capacity; // ���]�Ŷ� �Ŷ�����
  }
}

Vector::~Vector(){
  for(size_type i=0;i<size();i++)
    begin_[i].~value_type();
  if(begin_!=nullptr)
    operator delete(begin_);
}


struct God{
  typedef std::size_t size_type;
  void hire(Vector &vec, const std::string &name);
  void show(const Vector &vec);
  void fire(Vector &vec,unsigned id);
  void fire(Vector &vec,const std::string &name);
};

God boss; /// An interface to access class-Employee

// add_employee -> boss.hire()
void God::hire(Vector &vec, const std::string &name){
  vec.push_back(Employee(name));
}
void add_employee(Vector &vec, const std::string &name){
  boss.hire(vec,name);
}

// print -> boos.show()
void God::show(const Vector &vec){
  using std::cout;
  for (int i=0;i<vec.size();i++){
    cout<<vec[i].id_<<" "<<vec[i].name_<<"\n";
  }
}
void print(const Vector &vec){
  boss.show(vec);
}

// quit -> boss.fire()
void God::fire(Vector &vec, unsigned id){
  for (int i=0;i<vec.size();i++){
    if (vec[i].id_ == id){
      vec.erase(i);
      return ;
    }
  }
}
void God::fire(Vector &vec, const std::string &name){
  int i=0;
  while(i<vec.size()){
    if (vec[i].name_ == name){
      vec.erase(i);
    }
    else
      i++;
  }
}
void quit(Vector &vec, unsigned id){
  boss.fire(vec,id);
}
void quit (Vector &vec, const std::string &name){
  boss.fire(vec,name);
}




}// namespace OJ