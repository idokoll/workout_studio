//
// Created by EyalT on 10/11/2021.
//
#include "Action.h"
#include <iostream>
#include "Studio.h"

extern Studio* backup;
BaseAction :: ~BaseAction() = default;
OpenTrainer :: ~OpenTrainer() = default;
MoveCustomer :: ~MoveCustomer() = default;
Close :: ~Close() = default;
CloseAll :: ~CloseAll() = default;
Order :: ~Order() = default;
PrintWorkoutOptions :: ~PrintWorkoutOptions() = default;
PrintActionsLog :: ~PrintActionsLog() = default;
PrintTrainerStatus :: ~PrintTrainerStatus() = default;
BackupStudio :: ~BackupStudio() = default;
RestoreStudio :: ~RestoreStudio() = default;




BaseAction :: BaseAction():errorMsg(""), status() {}
ActionStatus BaseAction ::getStatus() const {return status;}
void BaseAction ::error(std::string errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
    std::cout << "Error: " + errorMsg;
}
void BaseAction ::complete() {status = COMPLETED;}
std :: string BaseAction ::getErrorMsg() const {return errorMsg;}

BaseAction* OpenTrainer ::clone() {
    OpenTrainer* cl = new OpenTrainer(trainerId, customers);
    std :: string toString = "open " + std ::to_string(trainerId)+" ";
    cl->logstring = logstring;
    return cl;
}
OpenTrainer :: OpenTrainer(int id, std::vector<Customer *> &customersList):trainerId(id), customers(customersList) {logstring = "";}
void OpenTrainer :: act(Studio &studio)
{
    if(studio.getTrainer(trainerId) == nullptr)
        error("Workout session does not exist or is already open.");
    else if(studio.getTrainer(trainerId)->isOpen())
        error("Workout session does not exist or is already open.");
    else{
        for (int i = 0; i < (int)customers.size(); ++i) {
            studio.getTrainer(trainerId)->addCustomer(customers[i]);
        }
        studio.getTrainer(trainerId)->openTrainer();
        std :: string toString = "open " + std ::to_string(trainerId)+" ";
        for (int i = 0; i < (int)customers.size(); ++i) {
            toString += customers[i]->toString();
        }
        logstring = toString;
        complete();
    }
}

std :: string OpenTrainer ::toString() const {
    std:: string stat = "";
    if(getStatus()==COMPLETED)
        stat = "Completed";
    if(getStatus()==ERROR)
        stat = "Error: "+ getErrorMsg();
    return logstring + stat;
}
BaseAction* Order ::clone() {
    return new Order(trainerId);
}
Order ::Order(int id): trainerId(id) {}
void Order ::act(Studio &studio) {
    if(studio.getTrainer(trainerId) == nullptr)
        error("The trainer does not exist or is not open.");
    else if(!studio.getTrainer(trainerId)->isOpen())
        error("trainer does not exist or is not open.");
    else{
        for (int i = 0; i < (int)studio.getTrainer(trainerId)->getCustomers().size(); ++i) {
            std :: vector<int> orders = studio.getTrainer(trainerId)->getCustomers()[i]->order(studio.getWorkoutOptions());
            studio.getTrainer(trainerId)->order(studio.getTrainer(trainerId)->getCustomers()[i]->getId(), orders, studio.getWorkoutOptions());
            for (int j = 0; j < (int)orders.size(); ++j) {
                std::cout << studio.getTrainer(trainerId)->getCustomers()[i]->getName() << " Is Doing " << studio.getWorkoutOptions()[orders[j]].getName() << std :: endl;

            }
        }
        complete();
    }

}
std :: string Order ::toString() const {
    std:: string tostring="Order " + std::to_string(trainerId)+" ";
    std::string stat="";
    if(getStatus()==COMPLETED)
        stat="Completed";
    if(getStatus()==ERROR)
        stat="Error: "+getErrorMsg();
    tostring+=stat;
    return tostring;
}
Close ::Close(int id):trainerId(id) {}
BaseAction* Close ::clone() {
    return new Close(trainerId);
}
void Close ::act(Studio &studio) {
    if (studio.getTrainer(trainerId) == nullptr)
        error("The trainer does not exist or is not open.");
    else if (!studio.getTrainer(trainerId)->isOpen())
        error("trainer does not exist or is not open.");
    else{
        studio.getTrainer(trainerId)->closeTrainer();
        std :: cout << "Trainer " << std::to_string(trainerId) << " closed. Salary " << std::to_string(studio.getTrainer(trainerId)->getSalary()) << "NIS" << std::endl;
        complete();
    }
}
std :: string Close ::toString() const {
    std:: string tostring="Close " + std::to_string(trainerId)+" ";
    std::string stat="";
    if(getStatus()==COMPLETED)
        stat="Completed";
    if(getStatus()==ERROR)
        stat="Error: "+getErrorMsg();
    tostring+=stat;
    return tostring;
}
BaseAction* PrintTrainerStatus ::clone() {
    return new PrintTrainerStatus(trainerId);
}
PrintTrainerStatus ::PrintTrainerStatus(int id): trainerId(id) {}
void PrintTrainerStatus ::act(Studio &studio){
    if(!studio.getTrainer(trainerId)->isOpen()) {
        std::cout << "Trainer " << std::to_string(trainerId) << " status: Closed" << std::endl;
    }
    else{
        std::cout << "Trainer " << std::to_string(trainerId) << " status: Open" << std::endl;
        std::cout << "Customers: "<< std:: endl;
        for (int i = 0; i < (int)studio.getTrainer(trainerId)->getCustomers().size(); ++i) {
            std::cout << std :: to_string(studio.getTrainer(trainerId)->getCustomers()[i]->getId()) << " " << studio.getTrainer(trainerId)->getCustomers()[i]->getName() << std:: endl;
        }
        std::cout << "Orders: "<< std:: endl;
        for (int i = 0; i < (int)studio.getTrainer(trainerId)->getOrders().size(); ++i) {
            std:: cout << studio.getTrainer(trainerId)->getOrders()[i].second.getName() << " " << std :: to_string(studio.getTrainer(trainerId)->getOrders()[i].second.getPrice()) << " " << std :: to_string(studio.getTrainer(trainerId)->getOrders()[i].first)<<std:: endl;
        }
        std::cout << "Current Trainer's Salary: " << std::to_string(studio.getTrainer(trainerId)->getSalary()) << "NIS"
                  << std::endl;
    }
    complete();
}
std:: string PrintTrainerStatus ::toString() const {
    std:: string tostring="Status " + std::to_string(trainerId)+" Completed";
    return tostring;
}
BaseAction* MoveCustomer ::clone() {
    return new MoveCustomer(srcTrainer, dstTrainer, id);
}
MoveCustomer ::MoveCustomer(int src, int dst, int customerId): srcTrainer(src), dstTrainer(dst), id(customerId) {}
std:: string MoveCustomer ::toString() const {
    std:: string tostring="Move " + std::to_string(srcTrainer)+" " +std::to_string(dstTrainer)+" "+std::to_string(id) + " ";
    std::string stat="";
    if(getStatus()==COMPLETED)
        stat="Completed";
    if(getStatus()==ERROR)
        stat="Error: "+getErrorMsg();
    tostring+=stat;
    return tostring;
}
void MoveCustomer ::act(Studio &studio) {
    if ((studio.getTrainer(dstTrainer) == nullptr) | (studio.getTrainer(srcTrainer) == nullptr) )
        error("Cannot move customer");
    else if (!studio.getTrainer(dstTrainer)->isOpen() | !studio.getTrainer(srcTrainer)->isOpen())
        error("Cannot move customer");
    else if (studio.getTrainer(srcTrainer)->getCustomer(id) == nullptr){
        error("Cannot move customer");
    }
    else if ((int)studio.getTrainer(dstTrainer)->getCustomers().size() >= studio.getTrainer(dstTrainer)->getCapacity()){
        error("Cannot move customer");
    }
    else {
        studio.getTrainer(dstTrainer)->addCustomer(studio.getTrainer(srcTrainer)->getCustomer(id));
        for (int i = 0; i < (int)studio.getTrainer(srcTrainer)->getOrders().size(); ++i) {
            if (studio.getTrainer(srcTrainer)->getOrders()[i].first == id) {
                studio.getTrainer(dstTrainer)->getOrders().push_back(studio.getTrainer(srcTrainer)->getOrders()[i]);
            }
        }
        studio.getTrainer(srcTrainer)->removeCustomer(id);
        complete();
    }
}
CloseAll ::CloseAll() {}
BaseAction* CloseAll :: clone(){
    return new CloseAll();
}
std:: string CloseAll ::toString() const {
    return "closeall Completed";
}
void CloseAll ::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers(); ++i) {
        if(studio.getTrainer(i)->isOpen()){
            Close c(i);
            c.act(studio);
        }
    }
    complete();
}
BaseAction* PrintWorkoutOptions :: clone(){
    return new PrintWorkoutOptions();
}
PrintWorkoutOptions ::PrintWorkoutOptions() {}
std:: string PrintWorkoutOptions ::toString() const {
    return "workout_options Completed";
}
void PrintWorkoutOptions::act(Studio &studio) {
    for (int i = 0; i < (int)studio.getWorkoutOptions().size(); ++i) {
        std :: string type = "";
        if(studio.getWorkoutOptions()[i].getType() == 0){
            type = "Anaerobic";
        }
        if(studio.getWorkoutOptions()[i].getType() == 1){
            type = "Mixed";
        }
        if(studio.getWorkoutOptions()[i].getType() == 2){
            type = "Cardio";
        }
        std :: cout << studio.getWorkoutOptions()[i].getName() <<", " << type << ", " << std::to_string(studio.getWorkoutOptions()[i].getPrice()) << std::endl;
    }

}
BaseAction* PrintActionsLog :: clone(){
    return new PrintActionsLog();
}
PrintActionsLog ::PrintActionsLog() {}
std:: string PrintActionsLog ::toString() const {
    return "log Completed";
}
void PrintActionsLog ::act(Studio &studio) {
    for (int i = 0; i < (int)studio.getActionsLog().size(); ++i) {
        std :: cout << studio.getActionsLog()[i]->toString()<< std:: endl;

    }
    complete();
}
BaseAction* BackupStudio :: clone(){
    return new BackupStudio();
}
BackupStudio :: BackupStudio(){}
std:: string BackupStudio ::toString() const {
    return "backup Completed";
}
void BackupStudio :: act(Studio &studio){
    backup = new Studio(studio);
    complete();
}
BaseAction* RestoreStudio :: clone(){
    return new RestoreStudio();
}
RestoreStudio :: RestoreStudio(){}
std:: string RestoreStudio ::toString() const {
    std::string tostring = "restore ";
    if(getStatus()==COMPLETED)
        tostring+="Completed";
    else if(getStatus()==ERROR)
        tostring+="Error: "+getErrorMsg();
    return tostring;
}
void RestoreStudio :: act(Studio &studio){
    if(backup== nullptr )
        error("No backup available");
    else{
        studio = *backup;
        complete();
    }
}



