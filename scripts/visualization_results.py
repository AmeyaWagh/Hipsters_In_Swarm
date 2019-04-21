import numpy as np 
import os 
import matplotlib.pyplot as plt
import seaborn as sns
import pprint
from scipy.optimize import curve_fit

sns.set()

RESULT_DIR="../results_1"
'''
N_ROBOTS=(10 20 30 40 50) # can go upto 50 
HIPSTER_PERCENTAGE=(5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100)

'''

mean = lambda _list: float(sum(_list))/float(len(_list))
pp = pprint.PrettyPrinter(indent=4)

def fit_sigmoid(xdata,ydata):
    def fsigmoid(x, a, c, d):
        return a*(1.0 / (1.0 + np.exp(-c*x + d )))
    
    def ftanh(x ,a, b):
        return a*(1.0 + np.tanh(b*x-3.14))

    # popt, pcov = curve_fit(fsigmoid, xdata, ydata, method='dogbox', bounds=([0., 2.],[-2.0, 2.0]))

    popt, pcov = curve_fit(ftanh, xdata, ydata, method='dogbox')
    # popt, pcov = curve_fit(fsigmoid, xdata, ydata, method='dogbox')
    print('params',popt)
    x_ = np.linspace(-10, 100, 100)
    # popt=np.array([ 0.51248388,  0.05257527, 4.3083104])
    y_ = ftanh(x_,*popt)
    # y_ = fsigmoid(x_,*popt)

    return x_,y_

def show_results():
    n_robots = [10, 20, 30, 40, 50]
    h_percentage = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]
    plot_data={}
    for n_r_ in n_robots:
        X=[0]
        Y=[0.0]
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
        plot_data[n_r_]={'X':X,'Y':Y}
        plt.plot(X,Y)
        plt.xlabel("Hipster Percentage")
        plt.ylabel("Opposite Opinion Percentage")
    plt.legend(["n_robots:"+str(k) for k in n_robots])
    plt.show()
    
    X_=[]
    Y_=[]
    for idx in range(len(h_percentage)):
        val=[]
        val_x=0
        for n_r_ in n_robots:
            val.append(plot_data[n_r_]['Y'][idx])
            val_x = plot_data[n_r_]['X'][idx]
        Y_.append(mean(val))
        X_.append(val_x)
    # X_ = plot_data[n_robots[0]]['Y']

    X_ = np.array(X_)
    Y_ = np.array(Y_)

    
    # pp.pprint(plot_data)
    print(X_)
    print(Y_)

    # exit() 
    plt.plot(X_,Y_)
    plt.show()

    X_fit,Y_fit = fit_sigmoid(X_,Y_)
    print(X_fit)
    print(Y_fit) 
    plt.plot(X_,Y_)
    plt.plot(X_fit,Y_fit)
    plt.show()


if __name__ == "__main__":
    show_results()
