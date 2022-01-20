import subprocess
import matplotlib.pyplot as plt

subprocess.call(["gcc -w Assgn1Src-CS20BTECH11001.c -o exec2"], shell=True)

n_sim = 100

n_threads = [1,2,4,8,16]
n_element = 5000
times = []
y1 = []
for n_thread in n_threads:
    for i in range(n_sim):
        output = subprocess.Popen(["./exec2 "+str(n_element)+" "+str(n_thread)], shell=True, stdout=subprocess.PIPE)
        times.append(float(output.stdout.read()))
    y1.append(sum(times)/n_sim)
    print("For "+str(n_thread)+" threads and "+str(n_element)+" elements, the average time is "+str(sum(times)/n_sim))
    times = []
print(y1)

m_elements = [1,2,3,4,5]
m_thread = 16
y2 = []
for m_element in m_elements:
    for i in range(n_sim):
        output = subprocess.Popen(["./exec2 "+str(m_element)+"000 "+str(m_thread)], shell=True, stdout=subprocess.PIPE)
        times.append(float(output.stdout.read()))
    y2.append(sum(times)/n_sim)
    print("For "+str(m_element)+"000 elements and "+str(m_thread)+" threads, the average time is "+str(sum(times)/n_sim))
    times = []
print(y2)

plt.scatter(n_threads,y1)
plt.plot(n_threads, y1)
plt.xlabel("Number of threads")
plt.ylabel("Time of execution(in milliseconds)")
plt.title("Time of execution vs Number of threads(for 5000 points)")
for i_x, i_y in zip(n_threads, y1):
    plt.text(i_x+1, i_y, '({}, {})'.format(i_x, i_y))
plt.show()

plt.plot(m_elements, y2)
plt.scatter(m_elements, y2)
plt.xlabel("Size of the array (*10^3)")
plt.ylabel("Time of execution(in milliseconds)")
plt.title("Time of execution vs Size of the array(*10^3) for 16 threads")
for i_x, i_y in zip(m_elements, y2):
    plt.text(i_x, i_y, '({}, {})'.format(i_x, i_y))
plt.show()