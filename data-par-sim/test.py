import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

N = 512

heat = np.zeros((N+2, N+2),dtype=np.float32)

heat[0,:] = 1024
heat[N+1,:] = 1024


fig = plt.figure()

n = 0


def updatefig(*args):
    heat[1:-1,1:-1] = heat[1:-1,1:-1] + 0.01 *\
           (-4.0 * heat[1:-1,1:-1] +  # All Elements except first/last row/column\
            heat[1:-1,:-2]  +  # All elements to the left\
            heat[1:-1,2:]   +  # All elements to the right\
            heat[:-2,1:-1]  +  # All elements to the top\
            heat[2:,1:-1])     # All elements to the bottom
    # heat[0,:] = np.random.random((N+2)) * 256
    # heat[np.random.randint(1,N+1,size=(16)),np.random.randint(1,N+1,size=(16))] = np.random.rand() * 256

    # n_updates = 16
    # coords = np.random.randint(1,N+1,size=(n_updates)),np.random.randint(1,N+1,size=(n_updates))
    # heat[coords] = heat[coords] * (0.5 + 0.5 * np.random.random(n_updates))
    
    # heat[1:-1,1:-1] = heat[1:-1,1:-1] * (0.5 + 0.5 * np.random.random((N,N)))
    # im.set_array(heat)
    # n += 1
    
    # return im,

for n in range(1000000):
    updatefig()
    if n % 1000 == 0:
        print(f'Step {n}')


# ani = animation.FuncAnimation(fig, updatefig, interval=50, blit=True)
im = plt.imshow(heat, animated=True,cmap=plt.cm.hot)
plt.show()




