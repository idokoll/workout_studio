//
// Created by EyalT on 05/11/2021.
//
#include "Customer.h"
#include <algorithm>
Customer :: ~Customer() = default;
SweatyCustomer :: ~SweatyCustomer() = default;
CheapCustomer :: ~CheapCustomer() = default;
HeavyMuscleCustomer :: ~HeavyMuscleCustomer() = default;
FullBodyCustomer :: ~FullBodyCustomer() = default;

Customer :: Customer(std::string c_name, int c_id): name(c_name), id(c_id){}
std::string Customer ::getName() const {return name;}
int Customer::getId() const {return id;}
Customer* CheapCustomer :: clone(){
    return new CheapCustomer(this->getName(),this->getId());
}
CheapCustomer :: CheapCustomer(std::string name, int id): Customer(name, id){}
std::vector<int> CheapCustomer ::order(const std::vector<Workout> &workout_options){
    int minPrice=0;
    int cheapIndex=0;
    std::vector<int> order;
    for (int i = 0; i < (int)workout_options.size(); ++i) {
        if(minPrice==0 || workout_options[i].getPrice()<minPrice) {
            minPrice = workout_options[i].getPrice();
            cheapIndex=i;
        }
    }
    order.push_back(cheapIndex);
    return order;
}
std :: string CheapCustomer::toString() const {
    return  getName() + ",chp ";
}

Customer* FullBodyCustomer :: clone(){
    return new FullBodyCustomer(this->getName(),this->getId());
}
FullBodyCustomer :: FullBodyCustomer(std::string name, int id): Customer(name, id){}
std::vector<int> FullBodyCustomer ::order(const std::vector<Workout> &workout_options)
{
    std :: vector<int> order;
    int c=-1,cPrice=0,m=-1,mPrice=0,a=-1,aPrice=0;
    for (int i = 0; i < (int)workout_options.size(); ++i) {
        if ((workout_options[i].getType() == CARDIO) & (cPrice == 0 || cPrice > workout_options[i].getPrice())){
            c = i;
            cPrice = workout_options[i].getPrice();
        }
        else if ((workout_options[i].getType() == MIXED) & (mPrice == 0 || mPrice < workout_options[i].getPrice())){
            m = i;
            mPrice = workout_options[i].getPrice();
        }
        else if ((workout_options[i].getType() == ANAEROBIC) & (aPrice == 0 || aPrice > workout_options[i].getPrice())){
            a = i;
            aPrice = workout_options[i].getPrice();
        }
    }
    if(c!=-1)
        order.push_back(c);
    if(m!=-1)
        order.push_back(m);
    if(a!=-1)
        order.push_back(a);
    return order;
}
std :: string FullBodyCustomer::toString() const {
    return  getName() + ",fbd ";
}

Customer* SweatyCustomer :: clone(){
    return new SweatyCustomer(this->getName(),this->getId());
}
SweatyCustomer :: SweatyCustomer(std::string name, int id):Customer(name, id) {}
std::vector<int> SweatyCustomer ::order(const std::vector<Workout> &workout_options){
    std :: vector<int> order;
    for (int i = 0; i < (int)workout_options.size(); ++i) {
        if(workout_options[i].getType() == CARDIO)
            order.push_back(workout_options[i].getId());
    }
    return order;
}
std :: string SweatyCustomer::toString() const {
    return  getName() + ",swt ";
}

Customer* HeavyMuscleCustomer :: clone(){
    return new HeavyMuscleCustomer(this->getName(),this->getId());
}
HeavyMuscleCustomer :: HeavyMuscleCustomer(std::string name, int id): Customer(name, id){}
    bool HeavyMuscleCustomer ::compare(const std :: pair<int, int> p1, const std :: pair<int, int> p2) {
    return  p1.second >  p2.second;
}
std::vector<int> HeavyMuscleCustomer ::order(const std::vector<Workout> &workout_options){
    std :: vector<int> order;
    std :: vector<std :: pair<int,int>> copy;
    for (int i = 0; i < (int)workout_options.size(); ++i) {
        if(workout_options[i].getType() == ANAEROBIC)
            copy.push_back(std ::make_pair(workout_options[i].getId(), workout_options[i].getPrice()));
    }
    std ::stable_sort(copy.begin(), copy.end(), compare);
    for (int i = 0; i < (int)copy.size(); ++i) {
            order.push_back(copy[i].first);
    }
    return order;
}

 std :: string HeavyMuscleCustomer::toString() const {
    return getName() + ",mcl ";
}
