arr = []

def construct2(soln):
    soln[len(arr)-1] = 1
    for i in range(len(arr)-2, -1, -1):
        max = 0
        for j in range(i+1, len(arr)):
            if arr[j]>arr[i]:
                if soln[j] > max:
                    max = soln[j]
        soln[i] = 1+max

def construct(soln):
    for i in range(0, len(arr)+1):
        soln[i][len(arr)] = 0
    for j in range(len(arr)-1, -1, -1):
        for i in range(0, len(arr)):
            if arr[j] <= arr[i]:
                soln[i][j] = soln[i][j+1]
            else:
                soln[i][j] = max(1+soln[j][j+1], soln[i][j+1])

def main():
    global arr
    arr = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6]
    arr.insert(0, -10)
    soln = [[None]*(len(arr)+1)]*(len(arr)+1)
    construct(soln)
    print(soln[0][1])
    soln2 = [None]*len(arr)
    construct2(soln2)
    print(soln2[0]-1)
    pass


if __name__ == "__main__":
    main()
