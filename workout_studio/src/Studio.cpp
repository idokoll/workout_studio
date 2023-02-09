//
// Created by EyalT on 05/11/2021.
//
#include "Studio.h"
#include <sstream>
extern Studio* backup;
Studio ::Studio():open(false){}
Studio :: ~Studio(){
    clear();
}
Studio& Studio :: operator=(const Studio &other){
    if(this != &other){
        clear();
        copy(other.open, other.trainers, other.workout_options, other.actionsLog);
    }
    return *this;
}
void Studio:: clear(){
    for (int i = 0; i < (int)trainers.size(); ++i) {
        delete trainers[i];
    }
    trainers.clear();
    for (int i = 0; i < (int)actionsLog.size(); ++i) {
        delete actionsLog[i];
    }
    actionsLog.clear();
}
void Studio ::copy(const bool &open, const std::vector<Trainer *> &tr, const std::vector<Workout> &wo,
                   const std::vector<BaseAction *> &al) {
    clear();
    this->open = open;
    for (int i = 0; i < (int)tr.size(); ++i) {
        trainers.push_back(new Trainer(*tr[i]));
    }
    for (int i = 0; i < (int)wo.size(); ++i) {

        workout_options.push_back(wo[i]);
    }
    for (int i = 0; i < (int)al.size(); ++i) {
        actionsLog.push_back(al[i]->clone());
    }
}
Studio ::Studio(const Studio &other) {
    copy(other.open, other.trainers, other.workout_options, other.actionsLog);
}
Studio& Studio :: operator=(Studio&& other){
    if(this != &other){
        clear();
        open = other.open;
        for (int i = 0; i < (int)other.trainers.size(); ++i) {
            trainers.push_back(other.trainers[i]);
        }
        for (int i = 0; i < (int)other.workout_options.size(); ++i) {
           workout_options.push_back(other.workout_options[i]);
        }
        for (int i = 0; i < (int)other.actionsLog.size(); ++i) {
            actionsLog.push_back(other.actionsLog[i]);
        }
        other.clear();
    }
    return *this;
}
Studio ::Studio(const std::string &configFilePath) :open(false), trainers(), workout_options(),actionsLog() {
    std :: ifstream MyReadFile;
    MyReadFile.open(configFilePath);
    std :: string mytext;
    int rowCount=0;
    int numOfTrainers=0;
    if(!MyReadFile){
        std :: cout << " error";
    }
    while (getline (MyReadFile, mytext)) {
        if((mytext[0]!='#') & (mytext!="")){
            if(rowCount==0) {
                numOfTrainers = std::stoi(mytext);
                rowCount++;
            }
            else if(rowCount==1){
                for (int i = 0; i < numOfTrainers; ++i) {
                    char currentChar = mytext[2*i];
                    int cap = currentChar-'0';
                    Trainer* t = new Trainer(cap);
                    trainers.push_back(t);
                }
                rowCount++;
            }
            else if(rowCount>=2){
                std::string substring = "";
                std::string name="";
                WorkoutType wt;
                int price = 0;
                int workoutCounter = 0;
                for (int i = 0; i < (int)mytext.size(); ++i) {
                    if(mytext[i] != ','){
                        substring += mytext[i];
                    }
                    else if((mytext[i] == ',') & (workoutCounter == 0)){
                        name = substring;
                        substring = "";
                        i++;
                        workoutCounter++;
                    }
                    else if((mytext[i] == ',') & (workoutCounter == 1)){
                        if(substring[0] == 'A')
                            wt = ANAEROBIC;
                        else if(substring[0] == 'M')
                            wt = MIXED;
                        else if(substring[0] == 'C')
                            wt = CARDIO;
                        substring = "";
                        i++;
                        workoutCounter++;
                    }
                }
                price = std::stoi(substring);
                Workout w(rowCount - 2, name, price, wt);
                workout_options.push_back(w);
                rowCount++;
            }
        }
    }
        MyReadFile.close();
}
Trainer *Studio::getTrainer(int tid)
{
    if ((int)trainers.size() < tid)
        return nullptr;
    return trainers[tid];
}
int Studio::getNumOfTrainers() const {return trainers.size();}
const std::vector<BaseAction *> &Studio::getActionsLog() const {return actionsLog;}
std::vector<Workout> &Studio::getWorkoutOptions() {return workout_options;}
void Studio::start() {
    open = true;
    std :: cout << "The Studio is now open!" << std :: endl;
    std :: string input ;
    std :: getline(std::cin, input);
    int customerCounter = 0;
    while (open){
        if(input.substr(0,input.find(' ')) == "open"){
            int trainerId = input[input.find(' ') + 1] - '0';
            std:: string subs = "";
            std :: vector<Customer*> customers;
            int customerCap=0;
            for (int i = 7; (i <= (int)input.size()) & (customerCap< getTrainer(trainerId)->getCapacity()); ++i) {
                if((input[i] != ' ') & (i != (int)input.size())){
                    subs += input[i];
                }
                else{
                    std :: string name = subs.substr(0,subs.find(','));
                    std::string  type = subs.substr(subs.find(',') + 1, subs.size());
                    if(type == "swt"){
                        customers.push_back(new SweatyCustomer(name,customerCounter));
                        customerCap++;
                    }
                    else if(type == "chp"){
                        customers.push_back(new CheapCustomer(name,customerCounter));
                        customerCap++;
                    }
                    else if(type == "mcl"){
                        customers.push_back(new HeavyMuscleCustomer(name,customerCounter));
                        customerCap++;
                    }
                    else if(type == "fbd"){
                        customers.push_back(new FullBodyCustomer(name,customerCounter));
                        customerCap++;
                    }
                    customerCounter++;
                    subs = "";
                }
            }
            OpenTrainer* op= new OpenTrainer(trainerId, customers);
            op -> act(*this);
            actionsLog.push_back(op);
        }
        else if(input.substr(0,input.find(' ')) == "order"){
            int trainerId = input[input.find(' ') + 1] - '0';
            Order* o = new Order(trainerId);
            o->act(*this);
            actionsLog.push_back(o);
        }
        else if(input.substr(0,input.find(' ')) == "close"){
            int trainerId = input[input.find(' ') + 1] - '0';
            Close* c = new Close(trainerId);
            c->act(*this);
            actionsLog.push_back(c);
        }
        else if(input.substr(0,input.find(' ')) == "status"){
            int trainerId = input[input.find(' ') + 1] - '0';
            PrintTrainerStatus* pts = new PrintTrainerStatus(trainerId);
            pts->act(*this);
            actionsLog.push_back(pts);
        }
        else if(input.substr(0,input.find(' ')) == "move"){
            int srcId = input[input.find(' ') + 1] - '0';
            int dstId = input[input.find(' ') + 3] - '0';
            int customerId = input[input.find(' ') + 5] - '0';
            MoveCustomer* mc = new MoveCustomer(srcId, dstId, customerId);
            mc->act(*this);
            actionsLog.push_back(mc);
        }
        else if(input.substr(0,input.find(' ')) == "workout_options"){
            PrintWorkoutOptions* pwo = new PrintWorkoutOptions();
            pwo->act(*this);
            actionsLog.push_back(pwo);
        }
        else if(input.substr(0,input.find(' ')) == "log"){
            PrintActionsLog* lo = new PrintActionsLog();
            lo->act(*this);
            actionsLog.push_back(lo);
        }
        else if(input.substr(0,input.find(' ')) == "backup"){
            BackupStudio* bs = new BackupStudio();
            bs->act(*this);
            actionsLog.push_back(bs);
        }
        else if(input.substr(0,input.find(' ')) == "restore"){
            RestoreStudio* rs = new RestoreStudio();
            rs->act(*this);
            actionsLog.push_back(rs);
        }
        else if(input.substr(0,input.find(' ')) == "closeall"){
            CloseAll* cl = new CloseAll();
            cl->act(*this);
            actionsLog.push_back(cl);
            open = false;
            break;
        }

        std :: getline(std::cin, input);
    }
}