main : main.cpp
	g++ main.cpp -o main.exe -leasyx
.POINT : clean
clean :
	del main.exe