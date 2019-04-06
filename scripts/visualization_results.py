import numpy as np 
import os 
import matplotlib.pyplot as plt

RESULT_DIR="../results"
'''
N_ROBOTS=(10 20 30 40 50) # can go upto 50 
HIPSTER_PERCENTAGE=(5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)

'''

def show_results():
    n_robots = [10, 20, 30, 40, 50]
    h_percentage = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
    for n_r_ in n_robots:
        X=[]
        Y=[]
        for h_p_ in h_percentage:
            res_file_ = "trial_nRobot{}_hPerc{}.txt".format(n_r_,h_p_)
            data=None
            with open(os.path.join(RESULT_DIR,res_file_)) as fp:
                data=np.array([int(i) for i in fp.readline().split()])
            R = data[data > 0].shape[0]
            G = data[data < 0].shape[0]
            Population = len(data)
            print("")
            print("nRobot{} hPercentage{}:".format(n_r_,h_p_))
            print("R",R,"G",G,"P",Population)
            X.append(h_p_)
            Y.append(float(G)/float(Population))
        plt.plot(X,Y)
        plt.xlabel("hipster percentage")
        plt.ylabel("Opposite opinion percentage")
    plt.legend(["n_robots:"+str(k) for k in n_robots])
    plt.show()


if __name__ == "__main__":
    show_results()
