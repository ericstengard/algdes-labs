def get_num_from_string(string):
    num = ''
    for i in string:
        if i in '1234567890':
            num+=i
    integer = int(num)
    return integer
def get_name_from_string(string):
    num = ''
    for i in string:
        if i in 'qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM':
            num+=i
    return num
def get_pure_from_string(string):
    num = ''
    for i in string:
        if i in '1234567890 ':
            num+=i
    return num
line = raw_input()
while line.find("#") != -1:
    line = raw_input()
n = get_num_from_string(line)
namesM = [""]*n
namesF = ["none"]*n
prefM = [[-1]]*n
prefF = [[-1]]*n
temp = 0
index = 0
while temp < n*2:
    line = raw_input()
    name = get_name_from_string(line)
    number = get_num_from_string(line)
    if number % 2 != 0:
        namesM[index] = name
    else:
        namesF[index] = name
        index +=1
    temp += 1
temp = 0
index = 0
raw_input()
while temp < n*2:
    line = raw_input()
    line = get_pure_from_string(line)
    pref = [int(s) for s in line.split() if s.isdigit()]
    number = pref.pop(0)
    test = 0
    while test < len(pref):
        numb = pref[test]
        if number % 2 != 0:
            pref[test] = pref[test] / 2 - 1;
        else:
            pref[numb/2] = test;
        test += 1
    if number % 2 != 0:
        prefM[index] = pref
    else:
        prefF[index] = pref
        index +=1
    temp += 1
couples = [-1]*n
queue = range(n)
trial = [0]*n
while len(queue) > 0:
    male = queue.pop(0)
    target = prefM[male].pop(0)
    prev = -1
    if couples[target] == -1:
        couples[target] = male
    else:
        if prefF[target][male] < prefF[target][couples[target]]:
            prev = couples[target]
            couples[target] = male
        else:
            prev = male
    if prev != -1:
        queue.append(prev)
temp = 0
while temp < len(couples):
    trial[couples[temp]] = temp
    temp += 1
temp = 0
while temp < n:
    print namesM[temp] + ' -- ' + namesF[trial[temp]]
    temp += 1
