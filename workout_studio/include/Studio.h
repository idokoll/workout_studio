#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"
#include <iostream>
#include <fstream>
#include <sstream>


//Forward declaration
class BaseAction;


class Studio{		
public:
	Studio();
    ~Studio();
    void clear();
    Studio& operator=(Studio&& other);
    void copy(const bool &open, const std::vector<Trainer*> &tr, const std::vector<Workout> &wo, const std::vector<BaseAction*> &al);
    Studio(const std::string &configFilePath);
    Studio(const Studio &other);
    Studio& operator=( const Studio& other);
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};

#endif