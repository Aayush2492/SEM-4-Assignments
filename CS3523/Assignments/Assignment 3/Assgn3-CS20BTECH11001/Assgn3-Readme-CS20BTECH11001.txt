To compile the code the code, cd into the directory and run: g++ -w -I include/ *.cpp -o exec
Run: ./exec -rms inp-params.txt to execute the rate monotonic scheduler
Run: ./exec -edf inp-params.txt to execute the Earliest Deadline First scheduler

inp-params.txt is the input file in required format.
Four .txt files will be generated in the same directory.

To apply context switch, go to line 17 set the macro CONTEXT_SWITCH_TIME to 1.

To run the simulation, so to the Simulation directory and run: python3 simulator.py

If the code does not run:
I wrote this code on Mac.
Previously I have faced situations where the codes run on my system but gives a fault on Linux. 
Although I have checked this on my friends system, if such a problem occurs, try to run the code I have uploaded here https://replit.com/@Aayush2492/OS-Assignment-3#Assgn3-CS20BTECH11001/RMS-Log.txt . 
This is same as the code I have submitted and you can compare using diff -rq folder1 folder 2