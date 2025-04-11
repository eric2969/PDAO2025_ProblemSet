import sys, os, random

def rename_files(directory, rnd = 0):
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
    if rnd == 1:
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

rnd = int(input("Input 1 for randomize, 0 for no randomize: "))
folder_path = input("Input folder path: ")
rename_files(folder_path, rnd)