//
// Created by EyalT on 05/11/2021.
//
#include "Trainer.h"
Trainer :: ~Trainer() {
    clear();
}
void Trainer ::clear() {
    for (int i = 0; i < (int)customersList.size(); ++i) {
        delete customersList[i];
    }
    customersList.clear();
}

Trainer& Trainer ::operator=(Trainer &&other) {
    if(this != &other){
        clear();
        open = other.open;
        for (int i = 0; i < (int)other.customersList.size(); ++i) {
            customersList.push_back(other.customersList[i]);
        }
        for (int i = 0; i < (int)other.orderList.size(); ++i) {
            orderList.push_back(other.orderList[i]);
        }
        other.clear();
    }
    return *this;
}
void Trainer ::copy(const bool &open, const int &capacity, const std::vector<Customer *> &cl,
                    const std::vector<OrderPair> &ol) {
    clear();
    this->open = open;
    this->capacity = capacity;
    for (int i = 0; i < (int)cl.size(); ++i) {
        customersList.push_back(cl[i]->clone());
    }
    for (int i = 0; i < (int)ol.size(); ++i) {
        orderList.push_back(ol[i]);
    }
}
Trainer ::Trainer(const Trainer &other) {
    copy(other.open, other.capacity, other.customersList, other.orderList);
}
Trainer& Trainer ::operator=(const Trainer &other) {
    if(this != &other){
        clear();
        copy(other.open, other.capacity, other.customersList, other.orderList);
    }
    return *this;
}
Trainer ::Trainer(int t_capacity):capacity(t_capacity), open(false), customersList(), orderList() {
}
std::vector<OrderPair>& Trainer :: getOrders() {return orderList;}
int Trainer :: getCapacity() const {return capacity;}
void Trainer :: addCustomer(Customer *customer) {
    customersList.push_back(customer);
}
std :: vector<Customer*>& Trainer :: getCustomers() {
    return customersList;
}
void Trainer ::openTrainer() {
    open = true;
}
void Trainer :: closeTrainer(){
    for (int i = 0; i < (int)customersList.size(); ++i) {
        delete customersList[i];
    }
    customersList.clear();
    open = false;
}
Customer* Trainer ::getCustomer(int id) {
    for (int i = 0; i < (int)customersList.size(); ++i) {
        Customer *c=customersList[i];
        if (customersList[i]->getId() == id)
            return c;
    }
    return nullptr;
}
bool Trainer ::isOpen() {
    return open;
}
int Trainer ::getSalary() {
    int salary=0;
    for (int i = 0; i < (int)orderList.size(); ++i) {
        salary+=orderList[i].second.getPrice();
    }
    return salary;
}
void Trainer ::order(const int customer_id, const std::vector<int> workout_ids,
                     const std::vector<Workout> &workout_options) {
    for (int i = 0; i < (int)workout_ids.size(); ++i) {
        orderList.push_back(OrderPair(customer_id, workout_options[workout_ids[i]]));
    }

}
void Trainer ::removeCustomer(int id) {

    std:: vector<Customer*> :: iterator it= customersList.begin();
    for (int i = 0; i < (int)customersList.size(); ++i) {
        if (customersList[i]->getId() == id) {
            customersList.erase(it);
        }
        it++;
    }
    std::vector<OrderPair> newOrder;
    for (int i = 0; i < (int)orderList.size(); ++i) {
        if (orderList[i].first != id) {
            newOrder.push_back(orderList[i]);
        }
    }
    orderList.clear();
    for (int i = 0; i < (int)newOrder.size(); ++i) {
        orderList.push_back(newOrder[i]);
    }

}
