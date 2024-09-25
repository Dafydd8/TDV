from llenar_maquinas_PD import *
import time

#pesos = [548, 423, 279, 744, 442] #PESOS ALTOS
#pesos = [107, 226, 565, 195, 216] #PESOS BAJOS
#pesos = [673, 989, 588, 658, 628, 630, 369, 370, 785, 220]
pesos = [954, 314, 358, 420, 609, 305, 598, 420, 292, 153, 543, 720, 592, 372, 1002, 619, 162, 673, 415, 812]
maquinas = [500,500,500,500]
maquinas2 = [1000,1000]
#beneficios = [98, 221, 347, 459, 581]
#beneficios = [617, 647, 362, 435, 243, 537, 173, 559, 428, 396]
beneficios = [486, 535, 226, 454, 384, 741, 595, 956, 529, 713, 268, 223, 410, 335, 191, 328, 20, 322, 711, 727]
s = []

t_pd = []
t_pd2 = []

for i in range(10):
    dp = dict()
    a = time.perf_counter()
    res = llenar_maquinas_pd(len(beneficios), maquinas, pesos, beneficios, dp) #llamado a función que resuelve
    best = reconstruir(dp, len(beneficios),maquinas,pesos,beneficios)
    b = time.perf_counter()
    t = b-a
    t = t*1000
    t_pd.append(t)
    dp.clear()
    best.clear()

    a = time.perf_counter()
    res = llenar_maquinas_pd(len(beneficios), maquinas2, pesos, beneficios, dp) #llamado a función que resuelve
    best = reconstruir(dp, len(beneficios),maquinas2,pesos,beneficios)
    b = time.perf_counter()
    t = b-a
    t = t*1000
    t_pd2.append(t)
    dp.clear()
    best.clear()    

f = open("Py_PA_20.csv", "w")
f.write("4M,2M\n")
for i in range(10):
    f.write(str(t_pd[i]) + "," + str(t_pd2[i]) + "\n")
f.close()




