#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"
typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary();
    bool isOpen();
    ~Trainer();
    void clear();
    Trainer& operator=(Trainer&& other);
    void copy(const bool &open, const int &capacity, const std::vector<Customer*> &cl, const std::vector<OrderPair> &ol );
    Trainer(const Trainer &other);
    Trainer& operator=(const Trainer& other);

private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif