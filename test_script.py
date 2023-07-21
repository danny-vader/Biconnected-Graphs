import os
import subprocess

valid = True

tarjan_time_sum, schmidt_time_sum = 0, 0
file_ct = 0

for dirname, _, filenames in os.walk('./connected_graphs'):
    for filename in filenames:
        if not filename.endswith(".mtx"):
            continue
        print("Running for", filename)

        time_output_tarjan = subprocess.check_output(f'/usr/bin/time -f "%e" ./tarjan.out {dirname}/{filename}', stderr=subprocess.STDOUT, shell=True).decode('utf-8')
        time_output_schmidt = subprocess.check_output(f'/usr/bin/time -f "%e" ./schmidt.out {dirname}/{filename}', stderr=subprocess.STDOUT, shell=True).decode('utf-8')

        if time_output_tarjan.split()[0] != time_output_schmidt.split()[0]:
            print("Non-matching outputs on file", filename)
            print("---------------------------\n\n\n\n")
            print("ERROR!!!\n")
            print("ERROR!!!\n")
            print("ERROR!!!\n")
            print("---------------------------")
            valid = False
            break

        tarjan_time_sum += float(time_output_tarjan.split()[1])
        schmidt_time_sum += float(time_output_schmidt.split()[1])

        file_ct += 1

        print(tarjan_time_sum / file_ct, schmidt_time_sum / file_ct)

    if not valid:
        break

print("Average Tarjan Time:", tarjan_time_sum / file_ct)
print("Average Schmidt Time:", schmidt_time_sum / file_ct)
