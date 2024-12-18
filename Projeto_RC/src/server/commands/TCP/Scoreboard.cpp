#include "Scoreboard.hpp"

Scoreboard::Scoreboard(){
    this->socketType = "TCP";
    this->returnCode = RSS;
}


void Scoreboard::execute(){


    string file_name = "SCOREBOARD_" + string(".txt");
    
    string data = " ";

    data += "\t" + string("--- Current Scoreboard (TOP10) ---") + "\n";
    
    SCORELIST list;
    int result = findTopScores(&list);
    
    sortScores(list);

    if (result <= 0) {
        data += "No scores available.\n";
        this->status = EMPTY;
    } else {
        this->status = OK;
        // 4. Append scores to the data string
        for (int i = 0; i < result; i++) {

            data += (i < 9 ? "0" : "") + std::to_string(i + 1) + "   " +
            (list.score[i] < 100 ? (list.score[i] < 10 ? "00" : "0") : "") +
            std::to_string(list.score[i]) + "   " +
            std::string(list.PLID[i]) + "   " +
            std::string(list.colcode[i]) + "   " +
            std::to_string(list.ntries[i]) + "   " +
            std::string(list.mode[i]) + "\n";
        }
    }

    string size = to_string(data.length());

    this->send(this->status + " " + file_name + " " + size + " " + data);

}
