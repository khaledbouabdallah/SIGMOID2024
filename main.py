from fast_ivf import FastIVF

ndim = 2
nlist = 3
nprobe = 10

def main():
    fast_ivf = FastIVF(ndim=ndim, nlist=nlist, nprobe=nprobe)
    print("main!")


if __name__ == '__main__':
    main()