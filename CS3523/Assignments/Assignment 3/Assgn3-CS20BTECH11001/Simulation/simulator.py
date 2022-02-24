import subprocess
import matplotlib.pyplot as plt
import os

parent_dir_path = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
# for i in range(1, 10):

subprocess.call(
    ["cd .. && g++ -w -I include/ *.cpp -o exec"], shell=True)

output = {
    "rms": {"dead_miss": [], "avg_wait": []},
    "edf": {"dead_miss": [], "avg_wait": []}
}

for c in ["rms", "edf"]:
    for i in range(1, 10):
        sh_output = subprocess.Popen(
            ["../exec "+"-"+c+" "+"inp"+str(i)+"_params.txt"], shell=True, stdout=subprocess.PIPE).stdout.read()
        ind = sh_output.index(',')
        output[c]["avg_wait"].append(float(sh_output[0:ind]))
        output[c]["dead_miss"].append(int(sh_output[ind+1:]))

plt.plot(range(20, 101, 10), output['rms']['dead_miss'], label='RMS')
plt.plot(range(20, 101, 10), output['edf']['dead_miss'], label='EDF')
plt.xlabel("Number of processes")
plt.ylabel("Number of Deadline misses")
plt.title("Deadline missess vs  number of process")
plt.legend()
plt.show()

plt.plot(range(20, 101, 10), output['rms']['avg_wait'], label='RMS')
plt.plot(range(20, 101, 10), output['edf']['avg_wait'], label='EDF')
plt.xlabel("Number of processes")
plt.ylabel("Average waiting time")
plt.title("Average waiting time vs  number of process")
plt.legend()
plt.show()
