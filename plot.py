import csv
import matplotlib.pyplot as plt
import numpy as np

x_philo = [1, 2, 4, 8, 16, 32, 64]
y_philo = []

x_prodcons = [2, 4, 8, 16, 32, 64]
y_prodcons = []

x_lect_ecri = [2, 4, 8, 16, 32, 64]
y_lect_ecri = []

x_test_and_set = [1, 2, 4, 8, 16]
y_test_and_set = []

y_test_test_and_set = []

def mean_std(array):
    array = array[1:]
    n = len(array)
    out = [[] for i in range(2)]
    
    for i in range(0, n, 5):
        tmp = []
        for j in range(i,i+5):
            #print("j:")
            #print(j)
            #print("tmp:")
            tmp.append(float(array[j][2:7]))
        #print(tmp)
        out[0].append(np.mean(tmp))
        out[1].append(np.std(tmp))  
    return out

def plot_philo():
    with open('Philosophe/philosophe.csv') as Philo:
        philo = csv.reader(Philo, delimiter=',')
        for row in philo:
            y_philo.append(row[2])
            #x_philo.append(row[1])
    #print(y_philo[1:])
    
    data_phylo = mean_std(y_philo) #generate mean and std
    
    plt.figure(1)
    
    plt.errorbar(x_philo, data_phylo[0], data_phylo[1], ecolor="r")
    plt.title("Graph of philosophe")
    plt.xlabel("Number of threads")
    plt.ylabel("time [s], lower is better")
    plt.grid(True)
    plt.savefig("Pictures/philo.png")

    return 0

def plot_prodcons():
    with open('Producteur_Consomateur/prodcons.csv') as Prodcons:
        prodcons = csv.reader(Prodcons, delimiter=',')
        for row in prodcons:
            y_prodcons.append(row[4])
    
    data_prodcons = mean_std(y_prodcons)

    plt.figure(2)

    plt.errorbar(x_prodcons, data_prodcons[0], data_prodcons[1], ecolor="r")
    plt.title("Graph of producteur consommateur")
    plt.xlabel("Number of threads")
    plt.ylabel("time [s], lower is better")
    plt.grid(True)
    plt.savefig("Pictures/prodcons.png")

    return 0


def plot_lectecre():
    with open('Lecteurs_écrivains/lect_ecri.csv') as Lect_ecri:
        lect_ecri = csv.reader(Lect_ecri, delimiter=',')
        for row in lect_ecri:
            y_lect_ecri.append(row[4])

    data_lect_ecri = mean_std(y_lect_ecri)

    plt.figure(3)

    plt.errorbar(x_lect_ecri, data_lect_ecri[0], data_lect_ecri[1], ecolor="r")
    plt.title("Graphe of Lecteur Écrivain")
    plt.xlabel("Number of threads")
    plt.ylabel("time [s], lower is better")
    plt.grid(True)
    #plt.legend(["Lecteur écrivain"], loc ="high right")

    plt.savefig("Pictures/lect_ecri.png")
    
    return 0

def plot_test_and_set():
    with open('Test_and_set/test_and_set.csv') as Test_and_set:
        test_and_set = csv.reader(Test_and_set, delimiter=',')
        for row in test_and_set:
            y_test_and_set.append(row[2])
    
    data_test_and_set = mean_std(y_test_and_set)

    plt.figure(4)

    plt.errorbar(x_test_and_set, data_test_and_set[0], data_test_and_set[1], ecolor="r")
    plt.title("Graph of TAS and TTAS")
    plt.xlabel("Number of threads")
    plt.ylabel("time [s], lower is better")
    plt.grid(True)

    return 0

def plot_test_test_and_set():
    with open('Test_test_and_set/test_test_and_set.csv') as Test_test_and_set:
        test_test_and_set = csv.reader(Test_test_and_set, delimiter=',')
        for row in test_test_and_set:
            y_test_test_and_set.append(row[2])
    
    data_test_test_and_set = mean_std(y_test_test_and_set)

    #plt.figure(5)

    plt.errorbar(x_test_and_set, data_test_test_and_set[0], data_test_test_and_set[1], ecolor="r")
    #plt.title("Graph of Test Test and set")
    #plt.xlabel("Number of threads")
    #plt.ylabel("time [s]")
    #plt.grid(True)
    #plt.savefig("Pictures/test_test_and_set.png")
    plt.legend(["tas", "ttas"], loc ="upper right")
    plt.savefig("Pictures/tas_tts.png")


    return 0


plot_philo()
plot_prodcons()
plot_lectecre()
plot_test_and_set()
plot_test_test_and_set()

