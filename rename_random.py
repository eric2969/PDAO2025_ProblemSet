import sys, os, random

def rename_files(directory):
    os.chdir(directory)
    case_num = 1
    if(os.path.isfile('01.a')):
        type = "Codeforces Polygon"
        case_num += 1
        while True:
            if os.path.isfile(("0" if case_num < 10 else "")+str(case_num)+'.a'):
                case_num += 1
            else:
                break
    elif(os.path.isfile('1.in')):
        type = "PDOGS"
        case_num += 1
        while True:
            if os.path.isfile(str(case_num)+'.in'):
                case_num += 1
            else:
                break
    else:
        print("Invalid testcase format")
        return
    case_num -= 1
    print("Testcase type found:", type)
    print("Testcase amount:", case_num)
    index_mapping = [x for x in range(1, case_num + 1)]
    random.shuffle(index_mapping)
    if type == "PDOGS":
        for i in range(1, case_num + 1):
            os.rename(str(i)+'.in', str(i)+'-tmp.in')
            os.rename(str(i)+'.out', str(i)+'-tmp.out')
        for i in range(1, case_num + 1):
            os.rename(str(i)+'-tmp.in', str(index_mapping[i-1])+'.in')
            os.rename(str(i)+'-tmp.out', str(index_mapping[i-1])+'.out')
    else:
        for i in range(1, case_num + 1):
            os.rename(("0" if i < 10 else "")+str(i), str(index_mapping[i-1])+'.in')
            os.rename(("0" if i < 10 else "")+str(i)+'.a', str(index_mapping[i-1])+'.out')
    print("Rename and testcase randomization finished")

script_type = int(input("Input 1 a single testcase, 2 for whole testcase: "))
if(script_type == 1):
    folder_path = input("Input folder path: ")
    rename_files(folder_path)
elif(script_type == 2):
    folder_path = input("Input folder path: ")
    problem_count = int(input("Input problem amount: "))
    a_chr = ord('A')
    for i in range(0, problem_count):
        problem_folder = folder_path + '/Problem ' + chr(a_chr + i) + '/non_sample_testcase'
        if not os.path.exists(problem_folder):
            print("Problem", chr(i+a_chr), "folder does not exist")
            continue
        print("Renaming and randomizing testcase for problem", chr(i+a_chr))
        rename_files(problem_folder)