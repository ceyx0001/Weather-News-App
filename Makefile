CC := g++
FLAGS := -lwthttp -lwt -lsqlite3 -L/usr/local/lib -lcurlpp -lcurl -I/usr/local/include -lboost_date_time
TARGET := Assistant
DATA := Database.o NoteMap.o Note.o Logger.o LogMessage.o LoginInfo.o LocationInfo.o
UTIL := Authenticate.o Calculator.o Request.o NewsRequester.o WeatherRequester.o GeoRequester.o Subject.o GetRequest.o
GUI := MainUI.o LoginForm.o NoteUI.o ClockUI.o SettingsUI.o ClockPage.o LocationUI.o CalculatorUI.o ConversionUI.o WeatherUI.o NewsUI.o AccountUI.o

all: $(TARGET)

$(TARGET): $(DATA) $(UTIL) $(GUI)
	$(CC) -o $(TARGET) Assistant.cpp $^ $(FLAGS)
	make clean

MainUI.o: gui/main/MainUI.h gui/main/MainUI.cpp
	$(CC) -c gui/main/MainUI.cpp

Authenticate.o: auth/Authenticate.h auth/Authenticate.cpp
	$(CC) -c auth/Authenticate.cpp

LoginForm.o: gui/login/LoginForm.h gui/login/LoginForm.cpp
	$(CC) -c gui/login/LoginForm.cpp

LoginInfo.o: data/login/LoginInfo.h data/login/LoginInfo.cpp
	$(CC) -c data/login/LoginInfo.cpp

Database.o: data/db/Database.h data/db/Database.cpp
	$(CC) -c data/db/Database.cpp

Logger.o: data/logger/Logger.h data/logger/Logger.cpp
	$(CC) -c data/logger/Logger.cpp

LogMessage.o: data/logger/LogMessage.h data/logger/LogMessage.cpp
	$(CC) -c data/logger/LogMessage.cpp

NoteUI.o: gui/note/NoteUI.h gui/note/NoteUI.cpp
	$(CC) -c gui/note/NoteUI.cpp

NoteMap.o: data/note/NoteMap.h data/note/NoteMap.cpp
	$(CC) -c data/note/NoteMap.cpp

Note.o: data/note/Note.h data/note/Note.cpp
	$(CC) -c data/note/Note.cpp

ClockUI.o: gui/clock/ClockUI.h gui/clock/ClockUI.cpp
	$(CC) -c gui/clock/ClockUI.cpp

ClockPage.o:  gui/clock/ClockPage.h gui/clock/ClockPage.cpp
	$(CC) -c gui/clock/ClockPage.cpp

SettingsUI.o: gui/settings/SettingsUI.h gui/settings/SettingsUI.cpp
	$(CC) -c gui/settings/SettingsUI.cpp

LocationUI.o: gui/settings/LocationUI.h gui/settings/LocationUI.cpp
	$(CC) -c gui/settings/LocationUI.cpp

CalculatorUI.o: gui/math/CalculatorUI.h gui/math/CalculatorUI.cpp
	$(CC) -c gui/math/CalculatorUI.cpp

ConversionUI.o: gui/math/ConversionUI.h gui/math/ConversionUI.cpp
	$(CC) -c gui/math/ConversionUI.cpp

Calculator.o: calculator/Calculator.h calculator/Calculator.cpp
	$(CC) -c calculator/Calculator.cpp

WeatherUI.o: gui/feed/WeatherUI.h gui/feed/WeatherUI.cpp
	$(CC) -c gui/feed/WeatherUI.cpp

NewsUI.o: gui/feed/NewsUI.h gui/feed/NewsUI.cpp
	$(CC) -c gui/feed/NewsUI.cpp

LocationInfo.o: data/location/LocationInfo.h data/location/LocationInfo.cpp
	$(CC) -c data/location/LocationInfo.cpp

GetRequest.o: web/GetRequest.h web/GetRequest.cpp
	$(CC) -c web/GetRequest.cpp

Request.o: web/Request.h web/Request.cpp
	$(CC) -c web/Request.cpp

NewsRequester.o: web/NewsRequester.h web/NewsRequester.cpp
	$(CC) -c web/NewsRequester.cpp

WeatherRequester.o: web/WeatherRequester.h web/WeatherRequester.cpp
	$(CC) -c web/WeatherRequester.cpp

GeoRequester.o: web/GeoRequester.h web/GeoRequester.cpp
	$(CC) -c web/GeoRequester.cpp

Subject.o: gui/settings/Subject.h gui/settings/Subject.cpp
	$(CC) -c gui/settings/Subject.cpp

AccountUI.o: gui/account/AccountUI.h gui/account/AccountUI.cpp
	$(CC) -c gui/account/AccountUI.cpp

clean:
	-rm *.o $(objects)
