import os
import sys
import statistics


def main():
  if len(sys.argv) != 2:
      print("Usage: python stat_maker_3000.py <dataSet>")
      return
  
  dataSet = sys.argv[1]

  out_dir = '../out/' + dataSet + '/'

  for folder in os.listdir(out_dir):
      folder_path = os.path.join(out_dir, folder)

      if os.path.isdir(folder_path):
          values = []
          times = []
          num_of_iterations = []
          files = {}

          for file in os.listdir(folder_path):
              file_path = os.path.join(folder_path, file)

              with open(file_path, 'r') as f:
                  lines = f.readlines()
                  result = int(lines[0].strip())
                  time = int(lines[3].strip())
                  iterations = int(lines[4].strip())

                  values.append(result)
                  times.append(time)
                  num_of_iterations.append(iterations)
                  files[result] = file

          max_value = max(values)
          min_value = min(values)
          mean_value = statistics.mean(values)
          min_value_file = files[min_value]

          max_time = max(times)
          min_time = min(times)
          mean_time = statistics.mean(times)

          max_iterations = max(num_of_iterations)
          min_iterations = min(num_of_iterations)
          mean_iterations = statistics.mean(num_of_iterations)


          print(f'Statistics for folder {folder}:')
          print(f'  Values: Max = {max_value}, Min = {min_value} (file: {min_value_file}), Mean = {mean_value}')
          print(f'  Times: Max = {max_time}, Min = {min_time}, Mean = {mean_time}')
          print(f'  Iterations: Max = {max_iterations}, Min = {min_iterations}, Mean = {mean_iterations}')

if __name__ == '__main__':
    main()