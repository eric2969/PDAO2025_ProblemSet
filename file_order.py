import sys, os, random

def rename_files(directory):
    os.chdir(directory)
    cnt = int(input("Input the number of max cases number: "))
    st = int(input("Input the start case number: "))
    case_num = 0
    for i in range(st, cnt + st):
        if(os.path.isfile(str(i) + '.in')):
            case_num += 1
            os.rename(str(i)+'.in', str(case_num)+'.in')
            os.rename(str(i)+'.out', str(case_num)+'.out')
    print("Reorderd finished cases amount:", case_num)

folder_path = input("Input folder path: ")
rename_files(folder_path)
