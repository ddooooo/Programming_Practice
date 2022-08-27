all: Student.exe

Student.exe: Student.o TestMain.cpp
	g++ -o $@ -std=c++11 Student.o TestMain.cpp

%.o: %.cpp
	g++ -std=c++11 -c $< -o $@ 

clean:
  del *.o *.exe