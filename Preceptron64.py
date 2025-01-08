maxim = 65536
bitmap = maxim * [0]
weights1 = maxim * [0]
weights2 = maxim * [0]
weights3 = maxim * [0]

def readimg(loc):
    #print(loc)
    tmp = open(loc,"rb")
    img = tmp.read()
    #print(len(img))
    i = 0
    n = 0
    c = 0
    i = len(img) - maxim
    
    while i < len(img):
        n = int(img[i])
        
        if n == 255:
            bitmap[c] = 1
                
        else:
            bitmap[c] = 0
            
        c += 1
        i += 1
    #print(bitmap)
def calculate(weight):
    temp = 0
    i = 0
    
    if weight == 1:
        for i in range(maxim):
            temp = temp + (int(bitmap[i]) * int(weights1[i]))
    elif weight == 2:
        for i in range(maxim):
            temp = temp + (int(bitmap[i]) * int(weights2[i]))
    elif weight == 3:
        for i in range(maxim):
            temp = temp + (int(bitmap[i]) * int(weights3[i]))
    #print(temp)
    return temp

def update(ans,weight):
    temp = int(0)
    i = 0
    
    if weight == 1:
        if ans == 0:
            for i in range(maxim):
                weights1[i] = int(weights1[i]) - int(bitmap[i])
        else:
            for i in range(maxim):
                weights1[i] = int(weights1[i]) + int(bitmap[i])
    if weight == 2:
        if ans == 0:
            for i in range(maxim):
                weights2[i] = int(weights2[i]) - int(bitmap[i])
        else:
            for i in range(maxim):
                weights2[i] = int(weights2[i]) + int(bitmap[i])
    if weight == 3:
        if ans == 0:
            for i in range(maxim):
                weights3[i] = int(weights3[i]) - int(bitmap[i])
        else:
            for i in range(maxim):
                weights3[i] = int(weights3[i]) + int(bitmap[i])
                    
def processimg(ans,weight,ist):

    if weight == 1:
        if ans == 0:
            if calculate(1) > 0:
                ist += 1
                update(0,1)
        elif ans == 1:
            if calculate(1) < 1:
                ist += 1
                update(1,1)
    if weight == 2:
        if ans == 0:
            if calculate(2) > 0:
                ist += 1
                update(0,2)
        elif ans == 1:
            if calculate(2) < 1:
                ist += 1
                update(1,2)
    if weight == 3:
        if ans == 0:
            if calculate(3) > 0:
                ist += 1
                update(0,3)
        elif ans == 1:
            if calculate(3) < 1:
                ist += 1
                update(1,3)
    print(ist)
    return ist

def guessimg():
    if calculate(1) >= 1:
            print("Squre")
    elif calculate(2) >= 1:
            print("Circle")
    #elif calculate(3) >= 1:
            #print("Trianlge")
    else:
            print("Not like anything i had ever seen!")
            
def train():
    istrained = 0
    while istrained != 1:
        istrained = 1
        a = 0
        while a < 10:
            readimg("outc\\" + str(a) + ".bmp")
            istrained = processimg(1, 1, istrained) 
            readimg("outs\\" + str(a) + ".bmp")
            istrained = processimg(0, 1, istrained) 
            #readimg("outt\\" + str(a) + ".bmp")
            #istrained = processimg(0, 1, istrained) 
            
            readimg("outc\\" + str(a) + ".bmp")
            istrained = processimg(0, 2, istrained) 
            readimg("outs\\" + str(a) + ".bmp")
            istrained = processimg(1, 2, istrained) 
            #readimg("outt\\" + str(a) + ".bmp")
            #istrained = processimg(0, 2, istrained) 
            
            #readimg("outc\\" + str(a) + ".bmp")
            #istrained = processimg(0, 3, istrained) 
            #readimg("outs\\" + str(a) + ".bmp")
            #istrained = processimg(0, 3, istrained) 
            #readimg("outt\\" + str(a) + ".bmp")
            #istrained = processimg(1, 3, istrained) 
            
            print(str(a) + " images processed")
            a += 1
        print(istrained)
        
    xtmp = open("outc\\1.bmp","rb")
    x = xtmp.read()
    i = 0
    outp = len(x) * [0]
    for i in range(len(x)):
        outp[i] = int(x[i])
    
    c = 0
    i = len(outp) - maxim
    while i < len(outp):
        outp[i] = weights1[c] + 128
        i += 1
        c += 1
    outf = bytearray(outp)
    f = open("outp1.bmp","wb")
    f.write(outf)
    #-------------------------------------------------------------------
    xtmp = open("outc\\1.bmp","rb")
    x = xtmp.read()
    i = 0
    outp = len(x) * [0]
    for i in range(len(x)):
        outp[i] = int(x[i])
    
    c = 0
    i = len(outp) - maxim
    while i < len(outp):
        outp[i] = weights2[c] + 128
        i += 1
        c += 1
    outf = bytearray(outp)
    f = open("outp2.bmp","wb")
    f.write(outf)
    #-------------------------------------------------------------------
    #xtmp = open("outc\\1.bmp","rb")
    #x = xtmp.read()
    #i = 0
    #outp = len(x) * [0]
    #for i in range(len(x)):
        #outp[i] = int(x[i])
    
    #c = 0
    #i = len(outp) - maxim
    #while i < len(outp):
        #outp[i] = weights3[c] + 128
        #i += 1
        #c += 1
    #outf = bytearray(outp)
    #f = open("outp3.bmp","wb")
    #f.write(outf)
    
def rundef():
    readimg(input("Enter an image:- "))
    guessimg()
    rundef()
    
select_mode = input("Select Mode (train - t / run - r)")
if select_mode == "t":
    train()
    rundef()
else:
    xtmp = open(input("Enter training file 1:- "),"rb")
    x = xtmp.read()
    i = len(x) - maxim
    c = 0
    while i < len(x):
        weights1[c] = int(x[i] - 128)
        c += 1
        i += 1
    #-------------------------------------------------------------------   
    xtmp = open(input("Enter training file 2:- "),"rb")
    x = xtmp.read()
    i = len(x) - maxim
    c = 0
    while i < len(x):
        weights2[c] = int(x[i] - 128)
        c += 1
        i += 1
    #-------------------------------------------------------------------    
    #xtmp = open(input("Enter training file 3:- "),"rb")
    #x = xtmp.read()
    #i = len(x) - maxim
    #c = 0
    #while i < len(x):
        #weights3[c] = int(x[i] - 128)
        #c += 1
        #i += 1
        
    rundef()
