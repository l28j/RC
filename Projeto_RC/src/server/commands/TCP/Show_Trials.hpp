
#ifndef __SHOW_TRIALS_HPP__ 
#define __SHOW_TRIALS_HPP__

#include "../command.hpp"
#include "../../storage.hpp"

class Show_Trials : public Command{
    string PLID; 
public:
    Show_Trials(vector<string> args) ;
    void execute() override;
};

#endif