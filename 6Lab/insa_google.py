from __future__ import print_function

import collections
from pathlib import Path

# Import Python wrapper for or-tools CP-SAT solver.
from ortools.sat.python import cp_model


def MinimalJobshopSat(jobs_data):
    """Minimal jobshop problem."""
    # Create the model.
    model = cp_model.CpModel()

    """
    jobs_data = [  # task = (machine_id, processing_time).
        [(2, 54), (0, 34), (3, 61), (1, 2)],  # Job0
        [(3, 9), (0, 15), (1, 89), (2,70)],  # Job1
        [(0, 38), (1, 19), (2,28), (3,87)], # Job2
        [(0, 95), (2, 34), (1,7), (3,29)]  # Job3
    ]
    """

    #fullTextFromFile = Path("instancje/data.13").read_text()
    #print(fullTextFromFile)
    #tmp = []
    #x = ['1', '2', '3']
    #y = ['a', 'b', 'c']
    #tmp.append(list(zip(x,y)))
    #tmp.append(list(zip(x,y)))
    #x.append(21)
    #print(x)
    #print(type(jobs_data[0][0]))


    machines_count = 1 + max(task[0] for job in jobs_data for task in job)
    all_machines = range(machines_count)

    # Computes horizon dynamically as the sum of all durations.
    horizon = sum(task[1] for job in jobs_data for task in job)

    # Named tuple to store information about created variables.
    task_type = collections.namedtuple('task_type', 'start end interval')
    # Named tuple to manipulate solution information.
    assigned_task_type = collections.namedtuple('assigned_task_type',
                                                'start job index duration')

    # Creates job intervals and add to the corresponding machine lists.
    all_tasks = {}
    machine_to_intervals = collections.defaultdict(list)

    for job_id, job in enumerate(jobs_data):
        for task_id, task in enumerate(job):
            machine = task[0]
            duration = task[1]
            suffix = '_%i_%i' % (job_id, task_id)
            start_var = model.NewIntVar(0, horizon, 'start' + suffix)
            end_var = model.NewIntVar(0, horizon, 'end' + suffix)
            interval_var = model.NewIntervalVar(start_var, duration, end_var,
                                                'interval' + suffix)
            all_tasks[job_id, task_id] = task_type(
                start=start_var, end=end_var, interval=interval_var)
            machine_to_intervals[machine].append(interval_var)

    # Create and add disjunctive constraints.
    for machine in all_machines:
        model.AddNoOverlap(machine_to_intervals[machine])

    # Precedences inside a job.
    for job_id, job in enumerate(jobs_data):
        for task_id in range(len(job) - 1):
            model.Add(all_tasks[job_id, task_id +
                                1].start >= all_tasks[job_id, task_id].end)

    # Makespan objective.
    obj_var = model.NewIntVar(0, horizon, 'makespan')
    model.AddMaxEquality(obj_var, [
        all_tasks[job_id, len(job) - 1].end
        for job_id, job in enumerate(jobs_data)
    ])
    model.Minimize(obj_var)

    # Solve model.
    solver = cp_model.CpSolver()
    solver.parameters.max_time_in_seconds = 30
    status = solver.Solve(model)

    if status == cp_model.OPTIMAL:
        # Create one list of assigned tasks per machine.
        assigned_jobs = collections.defaultdict(list)
        for job_id, job in enumerate(jobs_data):
            for task_id, task in enumerate(job):
                machine = task[0]
                assigned_jobs[machine].append(
                    assigned_task_type(
                        start=solver.Value(all_tasks[job_id, task_id].start),
                        job=job_id,
                        index=task_id,
                        duration=task[1]))

        # Create per machine output lines.
        output = ''
        for machine in all_machines:
            # Sort by starting time.
            assigned_jobs[machine].sort()
            sol_line_tasks = 'Machine ' + str(machine) + ': '
            sol_line = '           '

            for assigned_task in assigned_jobs[machine]:
                name = 'job_%i_%i' % (assigned_task.job, assigned_task.index)
                # Add spaces to output to align columns.
                sol_line_tasks += '%-10s' % name

                start = assigned_task.start
                duration = assigned_task.duration
                sol_tmp = '[%i,%i]' % (start, start + duration)
                # Add spaces to output to align columns.
                sol_line += '%-10s' % sol_tmp

            sol_line += '\n'
            sol_line_tasks += '\n'
            output += sol_line_tasks
            output += sol_line

        # Finally print the solution found.
        print('Optimal Schedule Length: %i' % solver.ObjectiveValue())
        print(output)

def ReadFromFile(filename):
    with open(filename) as f:
        lines = f.readlines()
    liczba_operacji = lines[0].split(" ")[0]
    liczba_maszyn = lines[0].split(" ")[1]
    liczba_suma = lines[0].split(" ")[2]
    lista_tupli = []
    lista_list = []
    counter1 = 0
    for i in range(int(liczba_operacji)):
        for j in range(0, int(liczba_maszyn)*2, 2):
            nr_zad = lines[i+1].split(" ")[j+1]
            wartosc = lines[i+1].split(" ")[j+2]
            counter1 += 1
            lista_tupli.append( (int(nr_zad)-1, int(wartosc)) )
            if counter1==int(liczba_operacji):
                counter1 = 0
                lista_list.append(list(lista_tupli))
                lista_tupli = []
    return lista_list

if __name__ == '__main__':

    file_paths = "insa/data.001"
    data = ReadFromFile(file_paths)
    MinimalJobshopSat(data)