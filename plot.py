import csv
import matplotlib.pyplot as plt
import numpy as np

x_philo = [1, 2, 4, 8, 16, 32, 64]
y_philo = []

x_prodcons = [2, 4, 8, 16, 32, 64]
y_prodcons = []

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
    plt.ylabel("time [s]")
    plt.grid(True)
    plt.savefig("philo.png")

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
    plt.ylabel("time [s]")
    plt.grid(True)
    plt.savefig("prodcons.png")

    return 0

def plot_lectecre():
    return 0

plot_philo()
plot_prodcons()
