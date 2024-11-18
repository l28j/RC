#include "database.hpp"

int userIsRegistered(string uid){
  // Build the path to the password file
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_pass.txt";

  // Check if the directory exists
  return filesystem::exists(path);
}

int userIsLoggedIn(string uid){
  // Build the path to the login file
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_login.txt";

  // Check if the directory exists
  return filesystem::exists(path);
}


void logoutUser(string uid){
  // Build the path to the login file
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_login.txt";

  // Remove the login file
  filesystem::remove(path);
}

void registerUser(string uid, string password){
  // Build the paths to the user directory and password file
  string userPath = "ASDIR/USERS/" + uid;
  string passwordPath = userPath + "/" + uid + "_pass.txt";

  // Build the paths to the hosted and bidded directories
  string hostedPath = userPath + "/HOSTED";
  string biddedPath = userPath + "/BIDDED";

  // Create the directories if they dont exist
  filesystem::create_directories(userPath);
  filesystem::create_directories(hostedPath);
  filesystem::create_directories(biddedPath);

  // Store the password
  ofstream file(passwordPath);
  file << password;

  //close the file
  file.close();
}

void unregisterUser(string uid){
  // Build the path to the user directory
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_pass.txt";

  // Remove the password file
  filesystem::remove_all(path);
}


int passwordMatches(string uid, string password){
  // Build the path to the password file
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_pass.txt";

  // Open the file
  ifstream file(path);
  if (!file) { throw runtime_error("Could not open file"); }
  
  // Read the password from the file
  string filePassword;
  getline(file, filePassword);

  //close the file
  file.close();

  // Compare the passwords
  return filePassword == password;
}

void createLoginFile(string uid){
  // Build the path to the login file
  string path = "ASDIR/USERS/" + uid + "/" + uid + "_login.txt";

  // Create the login file
  ofstream file(path);
}


string getUserBids(string uid){
  // Build the path to the bidded directory
  string bidsDirPath = "ASDIR/USERS/" + uid + "/BIDDED";
  string bids = "";

  for (const auto &entry : filesystem::directory_iterator(bidsDirPath)){
    string aid_filename = entry.path().filename(); // get the filename
    string aid = aid_filename.substr(0, aid_filename.length() - 4); // remove .txt
    
    // Get the auction state
    int state = !auctionIsFinished(aid);

    // Format bid message and add it to the string
    bids += " " + aid + " " + to_string(state);
  }

  return bids;
}

string getUserAuctions(string uid){
  // Build the path to the hosted directory
  string hostedDirPath = "ASDIR/USERS/" + uid + "/HOSTED";
  string auctions = "";

  for (const auto &entry : filesystem::directory_iterator(hostedDirPath)){
    // Get the auction state
    string aid_filename = entry.path().filename(); // remove .txt
    string aid = aid_filename.substr(0, aid_filename.length() - 4);
    int state = !auctionIsFinished(aid);

    // Format auction message and add it to the string
    auctions += " " + aid + " " + to_string(state);
  }

  return auctions;
}

string getAllAuctions(){
  // Build the path to the auctions directory
  string auctionsDirPath = "ASDIR/AUCTIONS";
  string auctions = "";

  for (const auto &entry : filesystem::directory_iterator(auctionsDirPath)){
    // Get the auction aid
    string aid = entry.path().filename(); // remove .txt
    
    // Get the auction state
    int state = !auctionIsFinished(aid);

    // Format auction message and add it to the string
    auctions += " " + aid + " " + to_string(state);
  }

  return auctions;
}

string createAuction(string uid, string name, string startValue, string timeActive, string fName, string fData){
  try {
  // Build the path to the auctions directory
  string auctionsDirPath = "ASDIR/AUCTIONS";

  // Create the auctions directory if it doesn't exist
  filesystem::create_directories(auctionsDirPath);

  //get the current auctions aid's and increment by one
  int aid = 0;
  for (const auto &entry : filesystem::directory_iterator(auctionsDirPath)){
    // Get the auction aid
    string aid_filename = entry.path().filename(); // remove .txt
    string aid_str = aid_filename.substr(0, aid_filename.length() - 4);
    int aid_int = stoi(aid_str);

    // Update the aid if the current aid is greater
    if (aid_int > aid){
      aid = aid_int;
    }
  }

  aid++; //increment to get the next aid

  //add the leading zeros aid needs to be 3 digits
  stringstream ss;
  ss << setw(3) << setfill('0') << aid;
  string aid_str = ss.str();

  // Build the path to the auction directory
  string auctionDirPath = auctionsDirPath + "/" + aid_str;

  // Create the auction directory
  filesystem::create_directories(auctionDirPath);

  // Create the BIDS directory
  filesystem::create_directories(auctionDirPath + "/BIDS");

  // Create the ASSET directory
  filesystem::create_directories(auctionDirPath + "/ASSET");

  // Create inside USERS/UID/HOSTED a file with the name of the auction
  string hostedDirPath = "ASDIR/USERS/" + uid + "/HOSTED";
  string hostedFilePath = hostedDirPath + "/" + aid_str + ".txt";
  ofstream hostedFile(hostedFilePath);

  // Build the path to the auction file
  string auctionFilePath = auctionDirPath + "/START_" + aid_str + ".txt";

  // Store the auction data
  ofstream startFile(auctionFilePath);
  startFile << uid << " ";
  startFile << name << " ";
  startFile << fName << " ";
  startFile << startValue << " ";
  startFile << timeActive << " ";

  // Get the current date and time
  // start fulltime ´e a data de in´ıcio do leil˜ao em segundos contados a partir de 1970 - 01 - 01 00 : 00 : 00 tal como obtido pela chamada da fun¸c˜ao time().
  time_t now = time(0);
  tm *ltm = localtime(&now);

  // Store the start date and time
  startFile << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " ";
  startFile << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":";
  startFile << std::setw(2) << std::setfill('0') << ltm->tm_min << ":";
  startFile << std::setw(2) << std::setfill('0') << ltm->tm_sec << " ";
  startFile << now; // time in seconds since 1970-01-01 00:00:00

  // Close the file
  startFile.close();

  // Build the path to the file
  string assetFilePath = auctionDirPath + "/ASSET/" + fName;

  // Store the asset data
  ofstream assetFile(assetFilePath);
  assetFile << fData;

  // Close the file
  assetFile.close();

  return aid_str;
  }
  catch (const exception& e) { // if an error occurs return ""
    return "";
  }
}


bool closeAuction(string aid){
  try{
    // Build the path to the end file
    string endFilePath = "ASDIR/AUCTIONS/" + aid + "/END_" + aid + ".txt";

    // create the file
    ofstream endFile(endFilePath);

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Store the end date and time
    endFile << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " ";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_min << ":";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_sec << " ";

    int timeActive = getAuctionTimeActive(aid);

    // save time active
    endFile << timeActive;

    // Close the file
    endFile.close();

    return true;
  }
  catch (const exception& e) { // if an error occurs return false
    return false;
  }
}

int isOwnerAuction(string uid, string aid){
  // Build the path to the hosted file
  string hostedFilePath = "ASDIR/USERS/" + uid + "/HOSTED/" + aid + ".txt";

  // Check if the file exists
  return filesystem::exists(hostedFilePath);
}

int auctionIsFinished(string aid){
  // Build the path to the auction file
  string endendAuctionPath = "ASDIR/AUCTIONS/" + aid + "/END_" + aid + ".txt";

  // auction has ended
  if (filesystem::exists(endendAuctionPath)){
    return 1;
  }

  string startAuctionPath = "ASDIR/AUCTIONS/" + aid + "/START_" + aid + ".txt";

  // Get auction info
  ifstream file(startAuctionPath);

  string uid, name, asset_fname, start_value, timeactive, start_date, start_time, start_fulltime;
  file >> uid >> name >> asset_fname >> start_value >> timeactive >> start_date >> start_time >> start_fulltime;

  // Close the file
  file.close();

  // Get the current date and time
  time_t now = time(0);
  time_t endedTime = stoi(start_fulltime) + stoi(timeactive);

  // check if time is up
  if (endedTime < now)
  {
    // create the end file
    ofstream endFile(endendAuctionPath);

    tm *ltm = localtime(&endedTime);

    // Store the end date and time
    endFile << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " ";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_min << ":";
    endFile << std::setw(2) << std::setfill('0') << ltm->tm_sec << " ";

    // store the time active, that is equal to timeActive in the start file
    endFile << timeactive;

    // Close the file
    endFile.close();

    return 1; // auction has ended
  }

  return 0; // auction has not ended
}

int auctionExists(string aid){
  // Build the path to the auction file
  string startAuctionPath = "ASDIR/AUCTIONS/" + aid + "/START_" + aid + ".txt";
  
  return filesystem::exists(startAuctionPath);
}

string getAuctionAsset(string aid){
  try {
    // Build the path to the asset file
    string assetFilePath = "ASDIR/AUCTIONS/" + aid + "/ASSET";

    //get the name of the file that is inside the asset directory
    string assetFileName;
    for (const auto &entry : filesystem::directory_iterator(assetFilePath)){
      assetFileName = entry.path().filename();
    }

    //get the data of the file
    ifstream assetFile(assetFilePath + "/" + assetFileName);

    //get the size of the file
    assetFile.seekg(0, ios::end);
    int size = assetFile.tellg();
    assetFile.seekg(0, ios::beg);

    //read the file
    char buffer[size];
    assetFile.read(buffer, size);
    buffer[size] = '\0'; // add the null terminator to the end of the buffer

    // Close the file
    assetFile.close();

    //format the data
    string assetData = assetFileName + " " + to_string(size) + " " + buffer;

    return assetData;
  } 
  catch (const exception& e) { // if an error occurs return ""
    return "";
  }
}

string getAuctionInfo(string aid){
  // Build the path to the auction file
  string auctionFilePath = "ASDIR/AUCTIONS/" + aid + "/START_" + aid + ".txt";
  
  // Get auction info
  ifstream file(auctionFilePath);

  string uid, name, asset_fname, start_value, timeactive, start_date, start_time, start_fulltime;
  file >> uid >> name >> asset_fname >> start_value >> timeactive >> start_date >> start_time >> start_fulltime;
  string auctionInfo = uid + " " + name + " " + asset_fname + " " + start_value + " " + start_date + " " + start_time + " " + timeactive;

  // Close the file
  file.close();

  return auctionInfo;
}

string getAuctionBidsInfo(string aid){
  // Build the path to the bids directory
  string bidsDirPath = "ASDIR/AUCTIONS/" + aid + "/BIDS";
  string bids = "";

  // Create a priority queue to store the top 50 bids
  priority_queue<int, vector<int>, greater<int>> topBids;
  for (const auto &entry : filesystem::directory_iterator(bidsDirPath)){
    // Get the bid value from the file name
    string filename = entry.path().filename().string();
    int bidValue = stoi(filename.substr(0, filename.find(".txt")));

    // Add the bid value to the queue
    topBids.push(bidValue);

    // If the size of the queue exceeds 50, pop the top element
    if (topBids.size() > 50){
      topBids.pop();
    }
  }

  // Now, topBids contains the top 50 bids with the highest at the top
  // Pop elements from the priority queue into a vector
  vector<int> sortedBids;
  while (!topBids.empty()){
    sortedBids.push_back(topBids.top());
    topBids.pop();
  }

  // Process the bids in the order of bid value
  for (const auto &bidValue : sortedBids){
    // Convert the bid value to a string with 6 digits and leading zeros
    stringstream ss;
    ss << setw(6) << setfill('0') << bidValue;
    string bidValueStr = ss.str();

    // Open the corresponding file
    string bidFilePath = bidsDirPath + "/" + bidValueStr + ".txt";

    ifstream file(bidFilePath);

    // TODO: throw exception or just continue?
    if (!file){ throw runtime_error("Could not open file"); }

    // Get the bid data
    string bidData;
    getline(file, bidData);

    // Close the file
    file.close();

    // Format bid message and add it to the string
    bids += " B " + bidData;
  }

  return bids;
}

string getAuctionEndInfo(string aid){
  // Build the path to the auction file
  string endendAuctionPath = "ASDIR/AUCTIONS/" + aid + "/END_" + aid + ".txt";
  string endInfo = "";

  // if the auction has not ended 
  if (!filesystem::exists(endendAuctionPath)){ 
    return endInfo; // empty string
  }

  // if the auction has ended
  ifstream file(endendAuctionPath);

  // TODO: throw exception or just continue?
  if (!file) { throw runtime_error("Could not open file");}

  // Get the end data
  string endData;
  getline(file, endData);

  // Close the file
  file.close();

  // Format end message and add it to the string
  endInfo = " E " + endData;

  return endInfo;
}

int getAuctionTimeActive(string aid){
  // get the seconds since 1970-01-01 00:00:00 of the start of the auction
  string startFilePath = "ASDIR/AUCTIONS/" + aid + "/START_" + aid + ".txt";
  ifstream startFile(startFilePath);

  // from the start file get the last element that is the first line
  string startedSeconds;
  string startFileData;
  getline(startFile, startFileData);

  // get the last element of the line
  startedSeconds = startFileData.substr(startFileData.find_last_of(" ") + 1);

  // Close the file
  startFile.close();

  // get the current time
  time_t now = time(0);

  // calculate the time the auction was active
  return now - stoi(startedSeconds);
}

bool isHigherBid(string aid, string value){
  // get the start value of the auction
  string startFilePath = "ASDIR/AUCTIONS/" + aid + "/START_" + aid + ".txt";
  ifstream startFile(startFilePath);

  // from the start file get the 4th element that is the start value
  string startValue;
  string startFileData;
  getline(startFile, startFileData);

  // Close the file
  startFile.close();

  // get the 4th element of the line
  startValue = startFileData.substr(startFileData.find(" ", startFileData.find(" ", startFileData.find(" ") + 1) + 1) + 1);

  // if the value is lower than the start value return false
  if (stoi(value) <= stoi(startValue)){
    return false;
  }

  // Build the path to the bids directory
  string bidsDirPath = "ASDIR/AUCTIONS/" + aid + "/BIDS";

  // Get the highest bid
  string highestBid;
  for (const auto &entry : filesystem::directory_iterator(bidsDirPath)){
    highestBid = entry.path().filename().string();
  }

  // If there are no bids, return true
  if (highestBid.empty()){
    return true;
  }

  // Get the bid value from the file name
  int highestBidValue = stoi(highestBid.substr(0, highestBid.find(".txt")));

  // Compare the bid value to the value received
  return highestBidValue < stoi(value);
}

void placeBid(string uid, string aid, string value){
  //add leading zeros to the value, VVVVVV
  stringstream ss;
  ss << setw(6) << setfill('0') << value;
  value = ss.str();

  //create the bid file
  string bidFilePath = "ASDIR/AUCTIONS/" + aid + "/BIDS/" + value + ".txt";

  //create the file
  ofstream bidFile(bidFilePath);

  // store inside the file the following format: ID bid_value bid_datetime bid_sec_time
  // get the current date and time
  time_t now = time(0);
  tm *ltm = localtime(&now);

  // store the bid data
  bidFile << uid << " " << value << " ";
  bidFile << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " ";
  bidFile << std::setw(2) << std::setfill('0') << ltm->tm_hour << ":";
  bidFile << std::setw(2) << std::setfill('0') << ltm->tm_min << ":";
  bidFile << std::setw(2) << std::setfill('0') << ltm->tm_sec << " ";

  // get auction time active
  int timeActive = getAuctionTimeActive(aid);

  // store the bid time active
  bidFile << timeActive;

  // Close the file
  bidFile.close();

  // Create a aid.txt file inside the bidded directory of the user
  string biddedDirPath = "ASDIR/USERS/" + uid + "/BIDDED";
  string biddedFilePath = biddedDirPath + "/" + aid + ".txt";
  ofstream biddedFile(biddedFilePath);

  // Close the file
  biddedFile.close();
}