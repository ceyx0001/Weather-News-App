#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <queue>
#include <iostream>
#include <string.h>
#include <ctime>
#include <sqlite3.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <time.h> 




/*
This structure defines the instances that will be entered 
into the priority queue.
*/

struct Time
{
    Time(std::time_t endTime, int hour, int minute, int second): endTime(endTime),hour(hour),minute(minute), second(second){}
    std::time_t endTime;
    int hour;
    int minute;
    int second;
};

/*
 This function defines the comparator that would sort the 
 datetimes.
 @param: The two Time objects to be sorted.
 @return: Boolean that delineates whether the left Time object is earlier than the right Time object.
 */

struct DereferenceCompareNode : public std::binary_function<Time, Time, bool>
{


     bool operator()(const Time& lhs, const Time& rhs) const
     {

     
     if (lhs.hour!=rhs.hour){
        return lhs.hour>rhs.hour;
     }
     else if (lhs.minute!=rhs.minute){

        return lhs.minute>rhs.minute;
     } 
     else if (lhs.second!=rhs.second){
        return lhs.second>rhs.second;
     }

    else{
        return true;
    }
     };
};


sqlite3_stmt* stmt;
sqlite3* db;
std::priority_queue<Time, std::vector<Time>, DereferenceCompareNode> queue;
std::time_t startTime =  std::time(nullptr);
int num_rows = -1;






 /*
 This function transfers the Time objects that are already 
 in the SQL database to the priority queue.
 @param: current Time, set end time, the priority queue, and 
 the database.
 @return: void.
 */

Time addToQueue(std::time_t startTime,std::time_t endTime,std::priority_queue<Time, std::vector<Time>, DereferenceCompareNode> queue,sqlite3* db)
{

  time_t elapsed = static_cast<time_t>(difftime (endTime, startTime));
  
  struct tm * ptm = gmtime (&elapsed);
  
  int day = ptm->tm_mday;
  
  int hour = ptm->tm_hour;
  
  int minute = ptm->tm_min;
  
  int second = ptm->tm_sec;
  
  if (day>0){
    hour+=(24)*ptm->tm_mday;
  }
 

  return Time(endTime,hour,minute,second);




}






  /*
  This function adds the timer that is inputted from the user.
  It calculates the end time from when the selections of the user's
  selected hour(s),minute(s), and second(s), then adds it to 
  the database and then the priority queue.
  @param: current time, submitted hours, minutes, and seconds.
  @return: void
  */

void addTimer(std::time_t startTime, int hours, int minutes, int seconds,std::priority_queue<Time, std::vector<Time>, DereferenceCompareNode> queue,sqlite3* db)
{

    std::tm *pStart = std::localtime(&startTime);

    pStart->tm_hour += hours;

    pStart->tm_min += minutes;

    pStart->tm_sec += seconds;

    time_t endTime = std::mktime(pStart);

    std::string val = ctime(&endTime);

    std::string sql = "INSERT INTO TIMERS (endtime) VALUES ('"+val+"');";

    sqlite3_exec(db,sql.c_str(),NULL,NULL,NULL);
     
    queue.push(Time(endTime,hours,minutes,seconds));



}

  /*
  This function converts the seconds to hour, minute, and second format.
  @param: seconds .
  @return: hours:minutes:seconds interpretation of the number of seconds.
  */
std::string convertSecondsToHHMMSS (int value) {

  std::string result;

  std::string h = std::to_string(value / 3600);

  std::string m = std::to_string((value % 3600) / 60);

  std::string s = std::to_string(value % 60);

  std::string hh = std::string(2 - h.length(), '0') + h;

  std::string mm = std::string(2 - m.length(), '0') + m;

  std::string ss = std::string(2 - s.length(), '0') + s;

  if (hh.compare("00") != 0) {
    result = hh + ':' + mm + ":" + ss;
  }
  else {
    result =  mm + ":" + ss;
  }
  return result;
}


  /*
  This function deletes a specific timer from the priority queue and database.
  @param: priority queue, database pointer.
  @return: updated queue without the specific timer.
  */

std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> deleteTimer(std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> queue,int placeInLine,sqlite3* db){
   
    std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> iterator = queue;

    std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> newQueue;

    bool found = false;

    int count=1;
    while (!iterator.empty() && !found) {


       Time currObj = iterator.top();
   
       time_t curr = currObj.endTime;
      
       
       if (count == placeInLine){


            
            std::string val = ctime(&curr);
            std::string sql = "DELETE FROM TIMERS WHERE endtime = '"+val+";"; 
            sqlite3_exec(db, sql.c_str(), NULL,NULL,NULL);

            found = true;

            iterator.pop();

            while (!iterator.empty()){

              newQueue.push(iterator.top());
              iterator.pop();

            }


        

       } 
       else{

          newQueue.push(currObj);
          iterator.pop();
          count++;
         

       }  
               
    }

    return newQueue;

};


  /*
  This function iterates through the priority queue
  to check if the time is up for any of the timers.
  @param: priority queue, database.
  @return: updated priority queue which will not contain
  any of the timers that are up.
  */
std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> checkIfDone(std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> queue,sqlite3* db){
    
    std::time_t t = std::time(0);   // get time now
    std::tm *now = std::localtime(&t);
    std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> iterator = queue;
     std::priority_queue<Time,std::vector<Time>, DereferenceCompareNode> newQueue;

    while (!iterator.empty()) {

      
       int timeDifference = std::difftime(t,iterator.top().endTime);
       
       if (timeDifference==0){
       
        std::cout << "Time is up!\n"<< std::endl;
        std::string val = ctime(&iterator.top().endTime);

        std::string sql = "DELETE FROM TIMERS WHERE endtime = '"+val+"';"; 
        sqlite3_exec(db, sql.c_str(), NULL,NULL,NULL);
        
       

       
       }

       else if (timeDifference<0){
   
        std::string val = ctime(&iterator.top().endTime);

        std::string sql = "DELETE FROM TIMERS WHERE endtime = '"+val+"';"; 
        
        sqlite3_exec(db, sql.c_str(), NULL,NULL,NULL);
      
        
       }
        else{
        
        std::cout << convertSecondsToHHMMSS(std::difftime(iterator.top().endTime,t))+" remaining.\n"<< std::endl;

        newQueue.push(iterator.top());

        }
       
       iterator.pop();                    // Remmove highest priority string
    }
    return newQueue;
}









/*
This function starts the instance of the startProgram class. 
The instance opens the timer SQL database that will be used 
to log all of the timers, and create the table if it is
not already populated. Else, it will take all of the 
timers that already exist in the database and add them
to the priority queue. 
*/

void startProgram(){

  
  sqlite3_open("timers.db", &db);

  std::string sql= "SELECT COUNT(*) FROM timers;";

  sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,NULL);

  sqlite3_step(stmt);

  num_rows = sqlite3_column_int(stmt, 0);
  
  sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS timers (endtime varchar(50));",NULL,NULL,NULL);
  
  int curr_row=1;
 

  if (num_rows>1){


    std::string result;

    std::string sql = "SELECT * FROM timers;";

    sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,NULL);

   while (sqlite3_step(stmt)==SQLITE_ROW){

    std::string curr = (reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
 
    struct std::tm tm;

    std::istringstream ss(curr);

    ss >> std::get_time(&tm, "%a %m %d %H:%M:%S %Y"); // or just %T in this case
    
    std::time_t time = mktime(&tm);     

    Time result = addToQueue(startTime,time,queue,db);
    
    queue.push(result);
  
   }

   for (;;){
  
    queue = checkIfDone(queue,db);
    sleep(1);
    


  }

  };
  

  
  


}



int main()  
{

startProgram();


}
  // int main()
  // {

  //   //startProgram *start = new startProgram();
  //   std::cout << "e";
  //   startProgram *start = new startProgram();
  //   // queue.push(addTimer(startTime, 14, 30, 30,queue,db));
  //   // queue.push(addTimer(startTime, 0, 0, 2,queue,db));
  //   // queue.push(addTimer(startTime, 0, 40, 20,queue,db));

  //   // int count=0;
  //   // for(;;) 
  //   // {
  //   // if (count==5){

  //   //   queue = deleteTimer(queue,2,db);

  //   // }
  //   // queue=checkIfDone(queue,db);
  //   // sleep(1);
  //   // count++;
  //   // }

  // }

