#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"
#include <bits/stdc++.h>
class Customer{
public:
    virtual ~Customer();
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual std::string toString() const = 0;
    virtual Customer* clone() = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};


class SweatyCustomer : public Customer {
public:
    ~SweatyCustomer();
	SweatyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* clone();
private:
};


class CheapCustomer : public Customer {
public:
    ~CheapCustomer();
	CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* clone();
private:
};


class HeavyMuscleCustomer : public Customer {
public:
    ~HeavyMuscleCustomer();
	HeavyMuscleCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    static bool compare(const std :: pair<int, int> p1, const std :: pair<int, int> p2);
    Customer* clone();



private:
};


class FullBodyCustomer : public Customer {
public:
    ~FullBodyCustomer();
	FullBodyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* clone();
private:
};


#endif