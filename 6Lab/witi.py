#from __future__ import print_function
from ortools.sat.python import cp_model
from pathlib import Path

class RPQ():
    def __init__(self, p, w, d):
        self.P = p
        self.w = w
        self.D = d

def CP(jobs, instanceName):

    
    model = cp_model.CpModel()
    variablesMaxValue = 0
    for i in range(len(jobs)):
        variablesMaxValue += (jobs[i].P + jobs[i].D) * jobs[i].w * jobs[i].D

    solver = cp_model.CpSolver()

    # variables:

    alfasMatrix = {} #attention! dictionary - not list!
    for i in range(len(jobs)):
        for j in range(len(jobs)):
            alfasMatrix[i,j] = model.NewIntVar(0,1,"alfa"+str(i)+"_"+str(j))
    starts = []
    ends = []
    delays = []
    intervals = []

    for i in range(len(jobs)):
        starts.append(model.NewIntVar(0,variablesMaxValue,"starts"+str(i)))
        ends.append(model.NewIntVar(0,variablesMaxValue,"ends"+str(i)))
        delays.append(model.NewIntVar(0,variablesMaxValue,"delays"+str(i)))
        intervals.append(model.NewIntervalVar(starts[i],jobs[i].P, ends[i],"interval"+str(i)))
    cmax = model.NewIntVar(0,variablesMaxValue,"cmax")

    # constraints
    for i in range(len(jobs)):
        #model.Add(ends[i]==starts[i]+jobs[i].P)
        model.Add(delays[i]>=0)
        model.Add(delays[i]>=(ends[i]-jobs[i].D)*jobs[i].w)

    model.AddNoOverlap(intervals)

    if False:
        for i in range(len(jobs)):
            for j in range(i+1,len(jobs)):
                model.Add(starts[i]+jobs[i].P <= starts[j]
                    + alfasMatrix[i,j] * variablesMaxValue)
                model.Add(starts[j]+jobs[j].P <= starts[i]
                    + alfasMatrix[j,i] * variablesMaxValue)
                model.Add(alfasMatrix[i,j] + alfasMatrix[j,i] == 1)
    # solver:
    
    totalDelay = model.NewIntVar(0,variablesMaxValue,"totalDelay")
    model.Add(totalDelay==sum(delays))

    model.Minimize(totalDelay)
    status = solver.Solve(model)
    if(status is not cp_model.OPTIMAL):
        print("Not_optimal!")
    print(instanceName, "Cmax", solver.Value(totalDelay))
    pi = []
    for i in range(len(starts)):
        pi.append((i,solver.Value(starts[i])))
    pi.sort(key=lambda x: x[1])
    print(pi)

def GetRPQsFromFile(pathToFile):

    fullTextFromFile = Path(pathToFile).read_text()
    words = fullTextFromFile.replace("\n"," ").split(" ")
    words_cleaned = list(filter(None, words))
    numbers = list(map(int, words_cleaned))

    numberOfJobs = numbers[0]
    numbers.pop(0)
    #numbers.pop(0)

    jobs = []
    for i in range(numberOfJobs):
        jobs.append(RPQ(numbers[0],numbers[1],numbers[2]))
        numbers.pop(0)
        numbers.pop(0)
        numbers.pop(0)

    return jobs

if __name__ == '__main__':

    file_paths = ["instancje/data.002"]

    for i in range(len(file_paths)):
        jobs = GetRPQsFromFile(file_paths[i])
        CP(jobs, file_paths[i])
